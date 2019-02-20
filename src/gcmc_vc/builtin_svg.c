/*
 * G-code meta compiler
 *
 * Copyright (C) 2013  B. Stultiens
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "config.h"

#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "utils.h"
#include "builtin_svg.h"
#include "value.h"
#include "checkarg.h"

#define MMTOPX	(90.0/25.4)
#define INTOPX	(90.0)

typedef enum {
	PATH_START,
	PATH_LINE,
	PATH_ARC,
	PATH_CLOSE,
	PATH_FLUSH,
} path_et;

typedef struct __path_t {
	path_et	type;
	double	x;	/* Coordinate */
	double	y;
	double	z;
	double	xang;	/* Ellipse axis angle */
	double	rad;	/* Arc radius */
	int	la;	/* Long arc flag */
	int	ccw;	/* CW, CCW */
	int	layer;
} path_t;

static path_t *gpaths;
static int ngpaths;
static int nagpaths;

static path_t *mpaths;
static int nmpaths;
static int nampaths;

static int pathactive;
static int npath = 1;

static double minx = HUGE_VAL;		/* To calculate the bounding box */
static double maxx = -HUGE_VAL;
static double miny = HUGE_VAL;
static double maxy = -HUGE_VAL;
static double minz = HUGE_VAL;
static double maxz = -HUGE_VAL;

static inline double topxl(double d)
{
	return d * (cl_inch ? INTOPX : MMTOPX);
}

static void minmax(double x, double y, double z)
{
	if(x < minx) minx = x;
	if(x > maxx) maxx = x;
	if(y < miny) miny = y;
	if(y > maxy) maxy = y;
	if(z < minz) minz = z;
	if(z > maxz) maxz = z;
}

static inline void swapdouble(double *a, double *b)
{
	double x = *a;
	*a = *b;
	*b = x;
}

/* Test if angle a is within the arc begin/end angles ab and ae */
static inline int hasangle(double a, double ab, double ae)
{
	/* Relocate the start angle to zero */
	/* Then the angle must simply be within the boundary */
	ae -= ab;
	a -= ab;
	if(a < 0.0)
		a += 2.0*M_PI;
	if(ae < 0.0)
		ae += 2.0*M_PI;
	return a >= 0.0 && a <= ae;
}

/* Calculate the BBox of an arc */
static void arcbbox(double x1, double y1, double x2, double y2, double phi, double rad, int la, int cw, double *xmin, double *ymin, double *xmax, double *ymax)
{
	double xchc, ychc;
	double xchv, ychv;
	double xchn, ychn;
	double xcp, ycp;
	double len;
	double ab, ae;

	/* Minimal BBox based on the start-/end-point */
	*xmin = x1 < x2 ? x1 : x2;
	*xmax = x1 < x2 ? x2 : x1;
	*ymin = y1 < y2 ? y1 : y2;
	*ymax = y1 < y2 ? y2 : y1;

	rad = fabs(rad);
	if(rad < EPSILON)
		return;

	/* Make the arc always CCW */
	if(cw) {
		swapdouble(&x1, &x2);
		swapdouble(&y1, &y2);
	}

	/* Chord center point */
	xchc = (x1 + x2) / 2.0;
	ychc = (y1 + y2) / 2.0;

	/* Half-chord vector */
	xchv = (x2 - x1) / 2.0;
	ychv = (y2 - y1) / 2.0;

	/* Chord normal unity length */
	len = sqrt(xchv*xchv + ychv*ychv);
	if(len < EPSILON)
		return;
	if(la) {
		/* Flip the normlized nornal to the correct side, depending "large arc", we're already CCW */
		xchn = ychv / len;
		ychn = -xchv / len;
	} else {
		xchn = -ychv / len;
		ychn = xchv / len;
	}

	/* The arc (circle) center is a normal on the chord center scaled by the */
	/* triangle proportions where the hypotonuse is the radius. */
	if(fabs(len - rad) < EPSILON)
		len = 0.0;
	else if(len > rad)
		rterror(NULL, "arcbbox(): Radius of arc does not match start-/end-point distance (len=%f rad=%f difference=%g).", len, rad, len - rad);
	else
		len = sqrt(rad*rad - len*len);
	xcp = xchc + len * xchn;
	ycp = ychc + len * ychn;

	/* Angles of the arc sides */
	ab = atan2(y1 - ycp, x1 - xcp);
	ae = atan2(y2 - ycp, x2 - xcp);

	/* Assure positive progressive angles (to prevent mod(2pi) problems) */
	if(ab < 0.0) {
		ab += 2.0*M_PI;
		ae += 2.0*M_PI;
	}
	if(ae < 0.0)
		ae += 2.0*M_PI;

	/* Check the circle's extremes whether the arc crosses them */
	if(hasangle(0.0, ab, ae))
		*xmax = xcp + rad;
	if(hasangle(0.5*M_PI, ab, ae))
		*ymax = ycp + rad;
	if(hasangle(M_PI, ab, ae))
		*xmin = xcp - rad;
	if(hasangle(3.0*M_PI/2.0, ab, ae))
		*ymin = ycp - rad;
}

static void path_mstack(path_et type, double xang, double rad, int la, int cw)
{
	testalloc((void **)&mpaths, nmpaths, &nampaths, sizeof(mpaths[0]));
	mpaths[nmpaths].type = type;
	mpaths[nmpaths].x = *global_pos[0] + *global_offs[0] + relative_offs[0];
	mpaths[nmpaths].y = *global_pos[1] + *global_offs[1] + relative_offs[1];
	mpaths[nmpaths].z = *global_pos[2] + *global_offs[2] + relative_offs[2];
	minmax(mpaths[nmpaths].x, mpaths[nmpaths].y, mpaths[nmpaths].z);
	mpaths[nmpaths].xang = xang;
	mpaths[nmpaths].rad = rad;
	mpaths[nmpaths].la = la;
	mpaths[nmpaths].ccw = !cw;		/* Because the SVG is Y-mirrored by default we must invert the CW/CCW direction */
	mpaths[nmpaths].layer = currentlayer;
	if(type == PATH_ARC) {
		/* Find the BBox of the arc */
		double xl, yb, xr, yt;
		assert(nmpaths > 0);
		arcbbox(mpaths[nmpaths-1].x, mpaths[nmpaths-1].y, mpaths[nmpaths].x, mpaths[nmpaths].y, xang, rad, la, cw, &xl, &yb, &xr, &yt);
		minmax(xl, yb, mpaths[nmpaths].z);
		minmax(xr, yt, mpaths[nmpaths].z);
	}
	nmpaths++;
}

static void path_start(void)
{
	if(pathactive)
		return;
	path_mstack(PATH_START, 0.0, 0.0, 0, 0);
	pathactive = 1;
}

static void path_line(void)
{
	assert(pathactive != 0);
	path_mstack(PATH_LINE, 0.0, 0.0, 0, 0);
}

/* The arc is always in the XY plane */
static void path_arc(double xangle, double rad, int la, int cw)
{
	assert(pathactive != 0);
	path_mstack(PATH_ARC, xangle, rad, la, cw);
}

static void path_flush(void)
{
	if(pathactive) {
		path_mstack(PATH_FLUSH, 0.0, 0.0, 0, 0);
		pathactive = 0;
	}
}

static void path_close(void)
{
	if(pathactive) {
		path_mstack(PATH_CLOSE, 0.0, 0.0, 0, 0);
		path_flush();
	}
}

static void path_gstack(path_et type)
{
	testalloc((void **)&gpaths, ngpaths, &nagpaths, sizeof(gpaths[0]));
	gpaths[ngpaths].type = type;
	gpaths[ngpaths].x = *global_pos[0] + *global_offs[0] + relative_offs[0];
	gpaths[ngpaths].y = *global_pos[1] + *global_offs[1] + relative_offs[1];
	gpaths[ngpaths].z = *global_pos[2] + *global_offs[2] + relative_offs[2];
	minmax(gpaths[ngpaths].x, gpaths[ngpaths].y, gpaths[ngpaths].z);
	ngpaths++;
}

static const char svg_hdr[] =
	"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n"
	"<!-- Created with gcmc (http://www.vagrearg.org/content/gcmc) -->\n"
	"<svg\n"
	"  xmlns=\"http://www.w3.org/2000/svg\"\n"
	"  xmlns:sodipodi=\"http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd\"\n"
	"  xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\"\n"
	"  version=\"1.1\"\n"
	"  width=\"%f%s\"\n"
	"  height=\"%f%s\"\n"
	"  viewBox=\"0.0 0.0 %f %f\"\n"
	">\n"
	"<sodipodi:namedview\n"
	"  inkscape:document-units=\"%s\"\n"
	"  units=\"%s\"\n"
	"  showgrid=\"%s\">\n"
	"  <inkscape:grid\n"
	"    type=\"xygrid\"\n"
	"    units=\"%s\"\n"
	"    empspacing=\"4\"\n"
	"    visible=\"true\"\n"
	"    enabled=\"true\"\n"
	"    snapvisiblegridlinesonly=\"true\" />\n"
	"</sodipodi:namedview>\n"
	;

void svg_prologue(FILE *fp)
{
	(void)fp;
}

static void svg_printlayer(FILE *fp, int l, const wchar_t *lname, double tx, double ty)
{
	int i;

	fprintf(fp, "<g inkscape:label=\"%ls\" inkscape:groupmode=\"layer\" id=\"%ls\" transform=\"scale(%f) translate(%f %f) scale(1 %d)\">\n",
			lname, lname, cl_inch ? INTOPX : MMTOPX, tx, ty, cl_svg_flip ? -1 : 1);
	for(i = 0; i < nmpaths; i++) {
		if(mpaths[i].layer != l)
			continue;
		switch(mpaths[i].type) {
		case PATH_START:
			fprintf(ofp, "<path "
				"style=\"stroke:#000000;stroke-width:%f;fill:none;stroke-linecap:round;stroke-linejoin:round;stroke-opacity:%f\" "
				"id=\"path%d\" "
				"d=\"M %f,%f",
				cl_svg_toolwidth, cl_svg_opacity, npath++, mpaths[i].x, mpaths[i].y);
			break;
		case PATH_LINE:
			fprintf(ofp, " L %f,%f", mpaths[i].x, mpaths[i].y);
			break;
		case PATH_ARC:
			fprintf(ofp, " A %f,%f %f %d,%d %f,%f", mpaths[i].rad, mpaths[i].rad, mpaths[i].xang, mpaths[i].la, mpaths[i].ccw, mpaths[i].x, mpaths[i].y);
			break;
		case PATH_CLOSE:
			fprintf(ofp, " Z");
			break;
		case PATH_FLUSH:
			fprintf(ofp, "\"/>\n");
			break;
		default:
			rtinternal(NULL, "Invalid path ID %d while flushing cut layer", mpaths[i].type);
			break;
		}
	}
	fprintf(fp, "</g>\n");
}

void svg_epilogue(FILE *fp)
{
	int i;
	int openpath = 0;
	int cc = 0xff;
	double tx, ty;
	double sw = 0.1 / (cl_inch ? INTOPX : MMTOPX);	/* Stroke width of move path 0.1 px */
	const char *u = cl_inch ? "in" : "mm";
	const char *grid = cl_svg_grid ? "true" : "false";

	path_flush();	/* Make sure to terminate all paths */

	/* Correct for line width of drawing */
	maxx += cl_svg_toolwidth / 2.0;
	minx -= cl_svg_toolwidth / 2.0;
	maxy += cl_svg_toolwidth / 2.0;
	miny -= cl_svg_toolwidth / 2.0;

	ty = cl_svg_flip ? maxy : -miny;
	tx = -minx;

	/* Print header with svg-size */
	fprintf(fp, svg_hdr, fabs(maxx-minx), u, fabs(maxy-miny), u, topxl(maxx-minx), topxl(maxy-miny), u, u, grid, u);

	/* Output all moves */
	if(nlayers) {
		for(i = 0; i < nlayers; i++) {
			svg_printlayer(fp, i, layername(i), tx, ty);
		}
	} else
		svg_printlayer(fp, -1, L"cutpath", tx, ty);

	/* Output move layer */
	if(ngpaths && cl_svg_movelayer) {
		fprintf(fp, "<g inkscape:label=\"Move Path\" inkscape:groupmode=\"layer\" id=\"movepath\" transform=\"scale(%f) translate(%f %f) scale(1 %d)\">\n",
				cl_inch ? INTOPX : MMTOPX, tx, ty, cl_svg_flip ? -1 : 1);
		for(i = 0; i < ngpaths; i++) {
			switch(gpaths[i].type) {
			case PATH_START:
				if(openpath)
					fprintf(ofp, "\"/>\n");
				openpath = 1;
				fprintf(ofp, "<path style=\"stroke:#%02x0000;stroke-width:%f;fill:none\" id=\"path%d\" d=\"M %f,%f",
					cc, sw, npath++, gpaths[i].x, gpaths[i].y);
				cc = 0;
				break;
			case PATH_LINE:
				fprintf(ofp, " L %f,%f", gpaths[i].x, gpaths[i].y);
				break;
			case PATH_FLUSH:
				if(openpath) {
					fprintf(ofp, "\"/>\n");
					openpath = 0;
				}
				break;
			default:
				rtinternal(NULL, "Invalid path ID %d while flushing move layer", gpaths[i].type);
				break;
			}
		}
		if(openpath)
			fprintf(ofp, "\"/>\n");
		fprintf(fp, "</g>\n");
	}
	fprintf(fp, "</svg>\n");
}

static void movegoto(const node_t *ref, const value_t *arg, int mg, const char *fn, int relative)
{
	int i;
	int nax = 0;
	double d;

	if(!mg) {
		if(pathactive || !ngpaths)
			path_gstack(PATH_START);
		path_flush();
	} else {
		path_start();
	}

	for(i = 0; i < arg->v.n && i < naxes; i++) {
		if(i < 3 || i >= 6) {
			check_arg_unit_distance(ref, fn, arg->v.vals[i], 0);
			d = value_to_dist(arg->v.vals[i]);
		} else {
			check_arg_unit_angle(ref, fn, arg->v.vals[i], 0);
			d = value_to_deg(arg->v.vals[i]);
		}

		if(!isundef(arg->v.vals[i])) {
			if(relative)
				*global_pos[i] += d;
			else
				*global_pos[i] = d;
			nax++;
		}
	}
	if(mg)
		path_line();
	else
		path_gstack(PATH_LINE);
	if(!nax)
		rterror(ref, "All coordinates in %s() undefined", fn);
}

static value_t *svg_move(const node_t *ref, int argc)
{
	value_t *p = bi_position(ref, 0);
	const value_t *arg;
	int i;
	check_arg_one(ref, "move", argc);
	arg = value_get(argc, 0);
	/* The optional feed argument is ignored */
	if(isvectorlist(arg)) {
		if(arg->vl.n <= 0)
			rtwarning(ref, "move(): Vectorlist contains no vectors");
		for(i = 0; i < arg->vl.n; i++) {
			movegoto(ref, arg->vl.vecs[i], 1, "move", 0);
		}
	} else if(isvector(arg))
		movegoto(ref, arg, 1, "move", 0);
	else
		rterror(ref, "move(): First argument must be a vector or a vectorlist");
	return p;
}

static value_t *svg_move_r(const node_t *ref, int argc)
{
	value_t *p = bi_position(ref, 0);
	const value_t *arg;
	int i;
	check_arg_one(ref, "move_r", argc);
	arg = value_get(argc, 0);
	/* The optional feed argument is ignored */
	if(isvectorlist(arg)) {
		if(arg->vl.n <= 0)
			rtwarning(ref, "move_r(): Vectorlist contains no vectors");
		for(i = 0; i < arg->vl.n; i++) {
			movegoto(ref, arg->vl.vecs[i], 1, "move_r", 1);
		}
	} else if(isvector(arg))
		movegoto(ref, arg, 1, "move_r", 1);
	else
		rterror(ref, "move_r(): First argument must be a vector or a vectorlist");
	return p;
}

static value_t *svg_goto(const node_t *ref, int argc)
{
	value_t *p = bi_position(ref, 0);
	const value_t *arg;
	int i;
	check_arg_one(ref, "goto", argc);
	arg = value_get(argc, 0);
	if(isvectorlist(arg)) {
		if(arg->vl.n <= 0)
			rtwarning(ref, "goto(): Vectorlist contains no vectors");
		for(i = 0; i < arg->vl.n; i++) {
			movegoto(ref, arg->vl.vecs[i], 0, "goto", 0);
		}
	} else if(isvector(arg))
		movegoto(ref, arg, 0, "goto", 0);
	else
		rterror(ref, "goto(): Argument must be a vector or a vectorlist");
	return p;
}

static value_t *svg_goto_r(const node_t *ref, int argc)
{
	value_t *p = bi_position(ref, 0);
	const value_t *arg;
	int i;
	check_arg_one(ref, "goto_r", argc);
	arg = value_get(argc, 0);
	if(isvectorlist(arg)) {
		if(arg->vl.n <= 0)
			rtwarning(ref, "goto_r(): Vectorlist contains no vectors");
		for(i = 0; i < arg->vl.n; i++) {
			movegoto(ref, arg->vl.vecs[i], 0, "goto_r", 1);
		}
	} else if(isvector(arg))
		movegoto(ref, arg, 0, "goto_r", 1);
	else
		rterror(ref, "goto_r(): Argument must be a vector or a vectorlist");
	return p;
}

typedef enum {
	FN_arc_cw,
	FN_arc_cw_r,
	FN_arc_ccw,
	FN_arc_ccw_r,
} arcfns_et;

static value_t *allarcs(const node_t *ref, int argc, const char *fn, arcfns_et ft, int cw, int relative)
{
	int i;
	const value_t *endp;
	const value_t *rad;
	check_arg_two(ref, fn, argc);
	endp = value_get(argc, 0);	/* Endpoint */
	rad = value_get(argc, 1);	/* Radius */
	check_arg_vector(ref, fn, endp, 0);
	check_arg_scalar(ref, fn, rad, 1);
	check_arg_unit_distance(ref, fn, rad, 1);
	double radius = value_to_dist(rad);
	double vecep[3] = {0.0, 0.0, 0.0};
	double vecab[3];
	double normal[3] = {0.0, 0.0, 0.0};
	double center[3] = {0.0, 0.0, 0.0};
	double len = 0.0;
	double lambda;
	double d;
	int turns = 0;
	int la = radius < 0.0 ? 1 : 0;	/* Large arc is negative radius */
	double xangle;

	if(argc > 2) {
		const value_t *t = value_get(argc, 2);
		check_arg_scalar(ref, fn, t, 2);
		check_arg_unit_none(ref, fn, t, 2);
		turns = value_to_int(t);
		if(turns < 1)
			rterror(ref, "%s() Number of turns must be >= 1", fn);
	}

	if(fabs(radius) < EPSILON)
		rterror(ref, "%s() Absolute radius must be greater than zero", fn);


	/*
	 * A: startpoint (relocated to 0,0)
	 * B: endpoint
	 * AB is the chord
	 * C: Circle center point
	 * N: normal of AB at half-way AB in the direction of the center
	 * l: scale factor for N
	 * r: radius
	 *
	 * Triangle:
	 * - hypotenuse: is of length radius from startpoint to center
	 * - adjecent:   0.5*AB is from start point to halfway at the chord
	 * - opposite:   l * normal bisects the arc to the center
	 *
	 * l = sqrt(r^2 - |0.5*AB|^2)
	 * C = 0.5*AB + l * N
	 */

	/* endpoint coordinates */
	if(endp->v.n >= 1) {
		check_arg_unit_distance(ref, fn, endp->v.vals[0], 0);
		if(!isundef(endp->v.vals[0]))
			vecep[0] = value_to_dist(endp->v.vals[0]);
		else
			vecep[0] = *global_pos[0];
	}
	if(endp->v.n >= 2) {
		check_arg_unit_distance(ref, fn, endp->v.vals[1], 0);
		if(!isundef(endp->v.vals[1]))
			vecep[1] = value_to_dist(endp->v.vals[1]);
		else
			vecep[1] = *global_pos[1];
	}
	if(endp->v.n >= 3) {
		check_arg_unit_distance(ref, fn, endp->v.vals[2], 0);
		if(!isundef(endp->v.vals[2]))
			vecep[2] = value_to_dist(endp->v.vals[2]);
		else
			vecep[2] = *global_pos[2];
	}

	/* endpoint - position */
	if(relative) {
		vecab[0] = vecep[0];
		vecab[1] = vecep[1];
		vecab[2] = vecep[2];
	} else {
		vecab[0] = vecep[0] - *global_pos[0];
		vecab[1] = vecep[1] - *global_pos[1];
		vecab[2] = vecep[2] - *global_pos[2];
	}

	switch(global_plane) {
	case PLANE_XY:
		if(endp->v.n < 1 || (isundef(endp->v.vals[0]) && endp->v.n >= 2 && isundef(endp->v.vals[1])))
			rterror(ref, "%s() in plane %s is missing both plane coordinates", fn, planename(global_plane));
		vecab[0] *= 0.5;	/* Half chord */
		vecab[1] *= 0.5;
		len = sqrt(vecab[0] * vecab[0] + vecab[1] * vecab[1]);
		if(len < EPSILON)
			rterror(ref, "%s() in plane %s has equal startpoint and endpoint", fn, planename(global_plane));
		/* normalized normal on the correct side of the arc */
		if((cw && radius < 0.0) || (!cw && radius > 0.0)) {
			normal[0] = -vecab[1] / len;
			normal[1] = vecab[0] / len;
		} else {
			normal[0] = vecab[1] / len;
			normal[1] = -vecab[0] / len;
		}
		d = radius*radius - (vecab[0]*vecab[0] + vecab[1]*vecab[1]);
		if(fabs(d) < EPSILON) {
			radius = sqrt(vecab[0]*vecab[0] + vecab[1]*vecab[1]);
		} else if(d < 0.0)
			rterror(ref, "%s() in plane %s has radius too small", fn, planename(global_plane));
		lambda = sqrt(d);
		center[0] = vecab[0] + lambda * normal[0];
		center[1] = vecab[1] + lambda * normal[1];
		break;

	case PLANE_XZ:
		if(endp->v.n < 1 || (isundef(endp->v.vals[0]) && endp->v.n >= 3 && isundef(endp->v.vals[2])))
			rterror(ref, "%s() in plane %s is missing both plane coordinates", fn, planename(global_plane));
		vecab[0] *= 0.5;	/* Half chord */
		vecab[2] *= 0.5;
		len = sqrt(vecab[0] * vecab[0] + vecab[2] * vecab[2]);
		if(len < EPSILON)
			rterror(ref, "%s() in plane %s has equal startpoint and endpoint", fn, planename(global_plane));
		/* normalized normal on the correct side of the arc */
		if((cw && radius < 0.0) || (!cw && radius > 0.0)) {
			normal[0] = -vecab[2] / len;
			normal[2] = vecab[0] / len;
		} else {
			normal[0] = vecab[2] / len;
			normal[2] = -vecab[0] / len;
		}
		d = radius*radius - (vecab[0]*vecab[0] + vecab[2]*vecab[2]);
		if(fabs(d) < EPSILON) {
			radius = sqrt(vecab[0]*vecab[0] + vecab[2]*vecab[2]);
		} else if(d < 0.0)
			rterror(ref, "%s() in plane %s has radius too small", fn, planename(global_plane));
		lambda = sqrt(d);
		center[0] = vecab[0] + lambda * normal[0];
		center[2] = vecab[2] + lambda * normal[2];
		break;

	case PLANE_YZ:
		if(endp->v.n < 2 || (isundef(endp->v.vals[1]) && endp->v.n >= 3 && isundef(endp->v.vals[2])))
			rterror(ref, "%s() in plane %s is missing both plane coordinates", fn, planename(global_plane));
		vecab[1] *= 0.5;	/* Half chord */
		vecab[2] *= 0.5;
		len = sqrt(vecab[1] * vecab[1] + vecab[2] * vecab[2]);
		if(len < EPSILON)
			rterror(ref, "%s() in plane %s has equal startpoint and endpoint", fn, planename(global_plane));
		/* normalized normal on the correct side of the arc */
		if((cw && radius < 0.0) || (!cw && radius > 0.0)) {
			normal[1] = -vecab[2] / len;
			normal[2] = vecab[1] / len;
		} else {
			normal[1] = vecab[2] / len;
			normal[2] = -vecab[1] / len;
		}
		d = radius*radius - (vecab[1]*vecab[1] + vecab[2]*vecab[2]);
		if(fabs(d) < EPSILON) {
			radius = sqrt(vecab[1]*vecab[1] + vecab[2]*vecab[2]);
		} else if(d < 0.0)
			rterror(ref, "%s() in plane %s has radius too small", fn, planename(global_plane));
		lambda = sqrt(d);
		center[1] = vecab[1] + lambda * normal[1];
		center[2] = vecab[2] + lambda * normal[2];
		break;
	}

	xangle = atan2(center[1], center[0]) / M_PI * 180.0;

	path_start();

	/* Calculate global endpoint */
	for(i = 0; i < endp->v.n && i < 3; i++) {
		if(relative)
			*global_pos[i] += vecep[i];
		else
			*global_pos[i] = vecep[i];
	}

	switch(global_plane) {
	case PLANE_XY:
		if(turns > 1) {
			// FIXME
		}

		path_arc(xangle, fabs(radius), la, cw);
		break;
	case PLANE_XZ:
	case PLANE_YZ:
		path_line();
		break;
	}

	return value_dup(endp);
}

static value_t *svg_arc_cw(const node_t *ref, int argc)
{
	return allarcs(ref, argc, "arc_cw", FN_arc_cw, 1, 0);
}

static value_t *svg_arc_cw_r(const node_t *ref, int argc)
{
	return allarcs(ref, argc, "arc_cw_r", FN_arc_cw_r, 1, 1);
}

static value_t *svg_arc_ccw(const node_t *ref, int argc)
{
	return allarcs(ref, argc, "arc_ccw", FN_arc_ccw, 0, 0);
}

static value_t *svg_arc_ccw_r(const node_t *ref, int argc)
{
	return allarcs(ref, argc, "arc_ccw_r", FN_arc_ccw_r, 0, 1);
}

static value_t *svg_plane(const node_t *ref, int argc)
{
	value_t *v;
	const value_t *arg;
	check_arg_one(ref, "plane", argc);
	arg = value_get(argc, 0);
	if(isundef(arg))
		return value_new_int(global_plane, UNIT_NONE);
	v = bi_plane(ref, argc);	/* Let the generic builtin do the tests and global setting */
	if(global_plane != PLANE_XY)
		rtwarning(ref, "Planes other than XY not mapped in svg output");
	return v;
}

static value_t *svg_drill(const node_t *ref, int argc)
{
	int i;
	const value_t *vec;
	const value_t *retract;
	const value_t *delta;
	int rep = 0;
	check_arg_three(ref, "drill", argc);
	vec = value_get(argc, 0);
	retract = value_get(argc, 1);
	delta = value_get(argc, 2);
	check_arg_vector(ref, "drill", vec, 0);
	check_arg_scalar(ref, "drill", retract, 1);
	check_arg_unit_distance(ref, "drill", retract, 1);
	check_arg_scalar(ref, "drill", delta, 2);
	check_arg_unit_distance(ref, "drill", delta, 2);
	if(argc > 3) {
		const value_t *repeat = NULL;
		repeat = value_get(argc, 3);
		check_arg_scalar(ref, "drill", repeat, 3);
		check_arg_unit_none(ref, "drill", repeat, 3);
		if((rep = value_to_int(repeat)) < 1)
			rterror(ref, "Drill-cycle repeat (fourth argument) must be >0");
	}

	if(vec->v.n < 3 || !isscalar(vec->v.vals[2]))
		rterror(ref, "Drill-cycle must have a scalar Z-coordinate in first argument");

	path_start();
	for(i = 0; i < vec->v.n && i < 3; i++) {
		check_arg_unit_distance(ref, "drill", vec->v.vals[i], 0);
		if(cl_relative)
			*global_pos[i] += value_to_dist(vec->v.vals[i]);
		else
			*global_pos[i] = value_to_dist(vec->v.vals[i]);
	}
	path_line();
	if(cl_relative)
		*global_pos[2] += value_to_dist(retract);
	else
		*global_pos[2] = value_to_dist(retract);
	path_line();
	return value_new(VAL_UNDEF);
}

/*
 * circle_cw(vector [, scalar]);
 * circle_cw(scalar, scalar [, scalar]);
 * circle_cw_r(vector [, scalar]);
 * circle_ccw(vector [, scalar]);
 * circle_ccw(scalar, scalar [, scalar]);
 * circle_ccw_r(vector [, scalar]);
 */
static value_t *allcircles(const node_t *ref, int argc, const char *fn, int ccw, int relative)
{
	const value_t *arg0;
	int turns = 0;
	double endp[3] = {0.0, 0.0, 0.0};
	double coor1 = 0.0;
	double coor2 = 0.0;
	double radius;
	double xangle;

	check_arg_one(ref, fn, argc);
	arg0 = value_get(argc, 0);

	endp[0] = *global_pos[0];
	endp[1] = *global_pos[1];
	endp[2] = *global_pos[2];

	if(isvector(arg0)) {
		/* Center is vector based */
		if(argc > 1) {
			const value_t *t = value_get(argc, 1);
			check_arg_scalar(ref, fn, t, 1);
			check_arg_unit_none(ref, fn, t, 1);
			turns = value_to_int(t);
			if(turns < 1)
				rterror(ref, "%s() Number of turns must be >= 1", fn);
		}
		switch(global_plane) {
		case PLANE_XY:
			if(arg0->v.n < 2 || isundef(arg0->v.vals[0]) || isundef(arg0->v.vals[1]))
				rterror(ref, "%s() in plane %s is missing plane coordinates", fn, planename(global_plane));
			check_arg_unit_distance(ref, fn, arg0->v.vals[0], 0);
			check_arg_unit_distance(ref, fn, arg0->v.vals[1], 0);
			if(relative) {
				coor1 = value_to_dist(arg0->v.vals[0]);
				coor2 = value_to_dist(arg0->v.vals[1]);
			} else {
				coor1 = value_to_dist(arg0->v.vals[0]) - *global_pos[0];
				coor2 = value_to_dist(arg0->v.vals[1]) - *global_pos[1];
			}
			if(arg0->v.n > 2 && !isundef(arg0->v.vals[2])) {
				check_arg_unit_distance(ref, fn, arg0->v.vals[2], 0);
				endp[2] = value_to_dist(arg0->v.vals[2]);
			}
			break;
		case PLANE_XZ:
			if(arg0->v.n < 3 || isundef(arg0->v.vals[0]) || isundef(arg0->v.vals[2]))
				rterror(ref, "%s() in plane %s is missing plane coordinates", fn, planename(global_plane));
			check_arg_unit_distance(ref, fn, arg0->v.vals[0], 0);
			check_arg_unit_distance(ref, fn, arg0->v.vals[1], 0);
			check_arg_unit_distance(ref, fn, arg0->v.vals[2], 0);
			if(relative) {
				coor1 = value_to_dist(arg0->v.vals[0]);
				coor2 = value_to_dist(arg0->v.vals[2]);
			} else {
				coor1 = value_to_dist(arg0->v.vals[0]) - *global_pos[0];
				coor2 = value_to_dist(arg0->v.vals[2]) - *global_pos[2];
			}
			if(!isundef(arg0->v.vals[1]))
				endp[1] = value_to_dist(arg0->v.vals[1]);
			break;
		case PLANE_YZ:
			if(arg0->v.n < 3 || isundef(arg0->v.vals[1]) || isundef(arg0->v.vals[2]))
				rterror(ref, "%s() in plane %s is missing plane coordinates", fn, planename(global_plane));
			check_arg_unit_distance(ref, fn, arg0->v.vals[0], 0);
			check_arg_unit_distance(ref, fn, arg0->v.vals[1], 0);
			check_arg_unit_distance(ref, fn, arg0->v.vals[2], 0);
			if(relative) {
				coor1 = value_to_dist(arg0->v.vals[1]);
				coor2 = value_to_dist(arg0->v.vals[2]);
			} else {
				coor1 = value_to_dist(arg0->v.vals[1]) - *global_pos[1];
				coor2 = value_to_dist(arg0->v.vals[2]) - *global_pos[2];
			}
			if(!isundef(arg0->v.vals[0]))
				endp[0] = value_to_dist(arg0->v.vals[0]);
			break;
		}
	} else if(isscalar(arg0)) {
		const value_t *arg1;
		double rad;
		double ang;
		/* Center is radius/angle based */
		check_arg_two(ref, fn, argc);
		check_arg_unit_distance(ref, fn, arg0, 0);
		arg1 = value_get(argc, 1);
		check_arg_scalar(ref, fn, arg1, 1);
		check_arg_unit_angle(ref, fn, arg1, 1);
		rad = value_to_dist(arg0);
		ang = value_to_rad(arg1);
		coor1 = rad * cos(ang);
		coor2 = rad * sin(ang);
		if(argc > 2) {
			const value_t *t = value_get(argc, 2);
			check_arg_scalar(ref, fn, t, 2);
			check_arg_unit_none(ref, fn, t, 2);
			turns = value_to_int(t);
			if(turns < 1)
				rterror(ref, "%s() Number of turns must be >= 1", fn);
		}
	} else {
		rterror(ref, "%s(): First argument neither vector nor scalar", fn);
		return value_new(VAL_UNDEF);
	}

	/* Here we have coor1,coor2 to point to relative center from current position */
	if((radius = sqrt(coor1*coor1 + coor2*coor2)) < EPSILON)
		rterror(ref, "%s() radius of circle is zero", fn);

	xangle = atan2(coor2, coor1);

	path_start();

	switch(global_plane) {
	case PLANE_XY:
		*global_pos[0] = endp[0] + 2.0*coor1;
		*global_pos[1] = endp[1] + 2.0*coor2;
		*global_pos[2] += (endp[2] - *global_pos[2]) / 2.0;
		path_arc(xangle, radius, 0, !ccw);
		*global_pos[0] = endp[0];
		*global_pos[1] = endp[1];
		*global_pos[2] = endp[2];
		path_arc(xangle, radius, 0, !ccw);
		break;
	case PLANE_XZ:
		*global_pos[0] = endp[0] + 2.0*coor1;
		*global_pos[1] += (endp[1] - *global_pos[1]) / 2.0;
		*global_pos[2] = endp[1] + 2.0*coor2;
		path_line();
		*global_pos[0] = endp[0];
		*global_pos[1] = endp[1];
		*global_pos[2] = endp[2];
		path_line();
	case PLANE_YZ:
		*global_pos[0] += (endp[0] - *global_pos[0]) / 2.0;
		*global_pos[1] = endp[1] + 2.0*coor1;
		*global_pos[2] = endp[1] + 2.0*coor2;
		path_line();
		*global_pos[0] = endp[0];
		*global_pos[1] = endp[1];
		*global_pos[2] = endp[2];
		path_line();
		break;
	}

	return value_new(VAL_UNDEF);
}

static value_t *svg_circle_cw(const node_t *ref, int argc)
{
	return allcircles(ref, argc, "circle_cw", 0, 0);
}

static value_t *svg_circle_cw_r(const node_t *ref, int argc)
{
	return allcircles(ref, argc, "circle_cw_r", 0, 1);
}

static value_t *svg_circle_ccw(const node_t *ref, int argc)
{
	return allcircles(ref, argc, "circle_ccw", 1, 0);
}

static value_t *svg_circle_ccw_r(const node_t *ref, int argc)
{
	return allcircles(ref, argc, "circle_ccw_r", 1, 1);
}

static value_t *svg_closepath(const node_t *ref, int argc)
{
	check_arg_none(ref, "svg_closepath", argc);
	if(!pathactive)
		rtwarning(ref, "svg_closepath() no active path");
	else
		path_close();
	return value_new(VAL_UNDEF);
}

static value_t *svg_layer(const node_t *ref, int argc)
{
	path_flush();			/* Layer switching must end the current path */
	if(nmpaths && -1 == currentlayer)
		rtwarning(ref, "layer(): layer change after data output; some moves may be absent in output.");
	return bi_layer(ref, argc);	/* Handle upstream */
}

static value_t *svg_relocate(const node_t *ref, int argc)
{
	value_t *v;
	path_gstack(PATH_FLUSH);	/* Ensure proper relocation of the goto layer */
	path_flush();			/* Not ending the path would cause an extra line */
	v = bi_relocate(ref, argc);	/* Call upstream */
	//path_gstack(PATH_START);
	return v;
}

static value_t *svg_dummy(const node_t *ref, int argc)
{
	(void)ref;
	(void)argc;
	return value_new(VAL_UNDEF);
}

const builtins_t builtins_svg[] = {
	{ L"arc_ccw",		svg_arc_ccw },
	{ L"arc_ccw_r",		svg_arc_ccw_r },
	{ L"arc_cw",		svg_arc_cw },
	{ L"arc_cw_r",		svg_arc_cw_r },
	{ L"circle_ccw",	svg_circle_ccw },
	{ L"circle_ccw_r",	svg_circle_ccw_r },
	{ L"circle_cw",		svg_circle_cw },
	{ L"circle_cw_r",	svg_circle_cw_r },
	{ L"comment",		svg_dummy },
	{ L"coolant",		svg_dummy },
	{ L"drill",		svg_drill },
	{ L"dwell",		svg_dummy },
	{ L"feedmode",		svg_dummy },
	{ L"feedrate",		svg_dummy },
	{ L"goto",		svg_goto },
	{ L"goto_r",		svg_goto_r },
	{ L"layer",		svg_layer },
	{ L"literal",		svg_dummy },
	{ L"move",		svg_move },
	{ L"move_r",		svg_move_r },
	{ L"pathmode",		svg_dummy },
	{ L"plane",		svg_plane },
	{ L"relocate",		svg_relocate },
	{ L"spindlespeed",	svg_dummy },
	{ L"spindle",		svg_dummy },
	{ L"svg_closepath",	svg_closepath },
	{ L"toolchange",	svg_dummy },
};

const int nbuiltins_svg = NELEM(builtins_svg);
