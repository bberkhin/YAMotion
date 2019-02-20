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
#include <string.h>

#include "utils.h"
#include "builtin_dxf.h"
#include "value.h"
#include "checkarg.h"

#define MMTOPX	(90.0/25.4)
#define INTOPX	(90.0)

extern const char dxfhdr1[];
extern const char dxfhdr2[];
extern const char dxfhdr_lstart[];
extern const char dxfhdr_leach[];
extern const char dxfhdr_lend[];
extern const char dxfftr[];
static int dxfhdrdone = 0;

typedef enum {
	PATH_START,
	PATH_LINE,
	PATH_FLUSH,
} path_et;

typedef struct __path_t {
	path_et	type;
	double	x;
	double	y;
	double	z;
} path_t;

static path_t *gpaths;
static int ngpaths;
static int nagpaths;

static double tagpos[3];

static int pathactive;
static int npath = 1;

static inline double topxl(double d)
{
	return d;
}

static const char dxfline_start[] =
	"  0\nLINE\n"
	"  5\npath%d\n"		/* Path ID */
	"100\nAcDbEntity\n"
	"100\nAcDbLine\n"
	"  8\n%ls\n"		/* The layer */
	" 62\n256\n"
	"370\n-1\n"
	"  6\nByLayer\n"
/*
 * start point
	" 10\n0.0\n"
	" 20\n0.0\n"
	" 30\n0.0\n"
 * end point
	" 11\n100.0\n"
	" 21\n100.0\n"
	" 31\n0.0\n"
*/
	;

static const char dxfarc_start[] =
	"  0\nARC\n"
	"  5\npath%d\n"		/* Path ID */
	"100\nAcDbEntity\n"
	"100\nAcDbCircle\n"
	"  8\n%ls\n"		/* The layer */
	" 62\n256\n"
	"370\n-1\n"
	"  6\nByLayer\n"
	;

static const wchar_t *dxflayername(void)
{
	return currentlayer >= 0 ? layername(currentlayer) : L"0";
}

static void printheader(void)
{
	static int handle = 100;
	if(dxfhdrdone)
		return;

	if(cl_inch)
		fprintf(ofp, dxfhdr1, 1, 210.0/25.4, 297.0/25.4);
	else
		fprintf(ofp, dxfhdr1, 4, 210.0, 297.0);

	if(nlayers) {
		int i;
		int hasdef = 0;
		fprintf(ofp, dxfhdr_lstart, nlayers+1);
		for(i = 0; i < nlayers; i++) {
			if(!wcscmp(L"0", layername(i)))		/* Check for presence of default layer */
				hasdef = 1;
			fprintf(ofp, dxfhdr_leach, handle++, layername(i));
		}
		if(!hasdef)
			fprintf(ofp, dxfhdr_leach, handle++, "0");	/* The default layer "0" */
	} else {
		fprintf(ofp, dxfhdr_lstart, 1);
		fprintf(ofp, dxfhdr_leach, handle++, "0");	/* The default layer "0" */
	}
	fprintf(ofp, "%s", dxfhdr_lend);
	fprintf(ofp, "%s", dxfhdr2);

	dxfhdrdone = 1;
}

static void path_start(void)
{
	if(pathactive)
		return;
	tagpos[0] = topxl(*global_pos[0] + *global_offs[0] + relative_offs[0]);
	tagpos[1] = topxl(*global_pos[1] + *global_offs[1] + relative_offs[1]);
	tagpos[2] = topxl(*global_pos[2] + *global_offs[2] + relative_offs[2]);
	pathactive = 1;
}

static void path_line(void)
{
	double x = topxl(*global_pos[0] + *global_offs[0] + relative_offs[0]);
	double y = topxl(*global_pos[1] + *global_offs[1] + relative_offs[1]);
	double z = topxl(*global_pos[2] + *global_offs[2] + relative_offs[2]);
	assert(pathactive != 0);
	printheader();
	fprintf(ofp, dxfline_start, npath++, dxflayername());
	fprintf(ofp, " 10\n%.16f\n", tagpos[0]);
	fprintf(ofp, " 20\n%.16f\n", tagpos[1]);
	fprintf(ofp, " 30\n%.16f\n", tagpos[2]);
	fprintf(ofp, " 11\n%.16f\n", x);
	fprintf(ofp, " 21\n%.16f\n", y);
	fprintf(ofp, " 31\n%.16f\n", z);
	tagpos[0] = x;
	tagpos[1] = y;
	tagpos[2] = z;
}

static void path_arc(double cx, double cy, double cz, double rad, double sa, double ea)
{
	assert(pathactive != 0);
	cx = topxl(cx + *global_pos[0] + *global_offs[0] + relative_offs[0]);
	cy = topxl(cy + *global_pos[1] + *global_offs[1] + relative_offs[1]);
	cz = topxl(cz + *global_pos[2] + *global_offs[2] + relative_offs[2]);
	printheader();
	fprintf(ofp, dxfarc_start, npath++, dxflayername());
	fprintf(ofp, " 10\n%.16f\n", cx);
	fprintf(ofp, " 20\n%.16f\n", cy);
	fprintf(ofp, " 30\n%.16f\n", cz);
	fprintf(ofp, " 40\n%.16f\n", rad);
	fprintf(ofp, " 50\n%.16f\n", sa);
	fprintf(ofp, " 51\n%.16f\n", ea);
	pathactive = 0;
}

static void path_circle(double cx, double cy, double cz, double rad)
{
	assert(pathactive != 0);
	cx = topxl(cx + *global_pos[0] + *global_offs[0] + relative_offs[0]);
	cy = topxl(cy + *global_pos[1] + *global_offs[1] + relative_offs[1]);
	cz = topxl(cz + *global_pos[2] + *global_offs[2] + relative_offs[2]);
	printheader();
	fprintf(ofp, dxfarc_start, npath++, dxflayername());
	fprintf(ofp, " 10\n%.16f\n", cx);
	fprintf(ofp, " 20\n%.16f\n", cy);
	fprintf(ofp, " 30\n%.16f\n", cz);
	fprintf(ofp, " 40\n%.16f\n", rad);
	pathactive = 0;
}

static void path_flush(void)
{
	if(pathactive) {
		pathactive = 0;
	}
}

static void path_stack(path_et type)
{
	testalloc((void **)&gpaths, ngpaths, &nagpaths, sizeof(gpaths[0]));
	gpaths[ngpaths].type = type;
	gpaths[ngpaths].x = topxl(*global_pos[0] + *global_offs[0] + relative_offs[0]);
	gpaths[ngpaths].y = topxl(*global_pos[1] + *global_offs[1] + relative_offs[1]);
	gpaths[ngpaths].z = topxl(*global_pos[2] + *global_offs[2] + relative_offs[2]);
	ngpaths++;
}

void dxf_prologue(FILE *fp)
{
	(void)fp;
}

void dxf_epilogue(FILE *fp)
{
	printheader();		/* Just to make sure if no paths were output */
	fprintf(fp, "%s", dxfftr);
}

static void movegoto(const node_t *ref, const value_t *arg, int mg, const char *fn, int relative)
{
	int i;
	int nax = 0;
	double d;

	if(!mg) {
		if(pathactive || !ngpaths)
			path_stack(PATH_START);
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
		path_stack(PATH_LINE);
	if(!nax)
		rterror(ref, "All coordinates in %s() undefined", fn);
}

static value_t *dxf_move(const node_t *ref, int argc)
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

static value_t *dxf_move_r(const node_t *ref, int argc)
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

static value_t *dxf_goto(const node_t *ref, int argc)
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

static value_t *dxf_goto_r(const node_t *ref, int argc)
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
	double a, b, c, d;
	int turns = 0;
	double sangle;
	double eangle;
	int ccw = 0;

	if(argc > 2) {
		const value_t *t = value_get(argc, 2);
		check_arg_scalar(ref, fn, t, 2);
		check_arg_unit_none(ref, fn, t, 2);
		turns = value_to_int(t);
		if(turns < 1)
			rterror(ref, "%s() Number of turns must be >= 1", fn);
	}

	if(ft == FN_arc_ccw || ft == FN_arc_ccw_r) {
		radius *= -1.0;
		ccw = 1;
	}

	/*
	 * A: startpoint
	 * B: endpoint
	 * R: Circle center point
	 * n: normal to AB
	 * l: scale factor for n
	 * r: radius
	 *
	 * AR = 0.5 * AB + ln
	 * |AR| = r
	 *
	 * Relocate to origin --> A = (0,0)
	 * then l is a quadratic function in B, n and r from:
	 *   R(x) = 0.5 * B(x) + ln(x)
	 *   R(y) = 0.5 * B(y) + ln(y)
	 *   R(x)^2 + R(y)^2 = r^2
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

	/* Check endpoint coordinates */
	switch(global_plane) {
	case PLANE_XY:
		if(endp->v.n < 1 || (isundef(endp->v.vals[0]) && endp->v.n >= 2 && isundef(endp->v.vals[1])))
			rterror(ref, "%s() in plane %s is missing both plane coordinates", fn, planename(global_plane));
		len = sqrt(vecab[0] * vecab[0] + vecab[1] * vecab[1]);
		if(len < EPSILON)
			rterror(ref, "%s() distance between start and endpoint zero (%e)", fn, len);
		if(radius < 0.0) {
			normal[0] = -0.5 * vecab[1] / len;
			normal[1] = 0.5 * vecab[0] / len;
		} else {
			normal[0] = 0.5 * vecab[1] / len;
			normal[1] = -0.5 * vecab[0] / len;
		}
		a = normal[0]*normal[0] + normal[1]*normal[1];
		b = 0.5 * vecab[0] * normal[0] + 0.5 * vecab[1] * normal[1];
		c = 0.25 * vecab[0] * vecab[0] + 0.25 * vecab[1] * vecab[1] - radius * radius;
		d = b*b - 4.0*a*c;
		if(d < 0.0 && fabs(d) < EPSILON)	/* Fix rounding error */
			d = 0.0;
		if(d < 0.0)
			rterror(ref, "%s() radius (%e) is less than two times distance from start to end (D=%e)", fn, radius, d);
		lambda = (-b + sqrt(d)) / (2.0*a);
		center[0] = 0.5 * vecab[0] + lambda * normal[0];
		center[1] = 0.5 * vecab[1] + lambda * normal[1];
		break;
	case PLANE_XZ:
		if(endp->v.n < 1 || (isundef(endp->v.vals[0]) && endp->v.n >= 3 && isundef(endp->v.vals[2])))
			rterror(ref, "%s() in plane %s is missing both plane coordinates", fn, planename(global_plane));
		len = sqrt(vecab[0] * vecab[0] + vecab[2] * vecab[2]);
		if(len < EPSILON)
			rterror(ref, "%s() distance between start and endpoint zero (%e)", fn, len);
		if(radius < 0.0) {
			normal[0] = -0.5 * vecab[2];
			normal[2] = 0.5 * vecab[0];
		} else {
			normal[0] = 0.5 * vecab[2];
			normal[2] = -0.5 * vecab[0];
		}
		a = normal[0]*normal[0] + normal[2]*normal[2];
		b = 0.5 * vecab[0] * normal[0] + 0.5 * vecab[2] * normal[2];
		c = 0.25 * vecab[0] * vecab[0] + 0.25 * vecab[2] * vecab[2] - radius * radius;
		d = b*b - 4.0*a*c;
		if(d < 0.0 && fabs(d) < EPSILON)	/* Fix rounding error */
			d = 0.0;
		if(d < 0.0)
			rterror(ref, "%s() radius (%e) is less than two times distance from start to end (D=%e)", fn, radius, d);
		lambda = (-b + sqrt(d)) / (2.0*a);
		center[0] = 0.5 * vecab[0] + lambda * normal[0];
		center[2] = 0.5 * vecab[2] + lambda * normal[2];
		break;
	case PLANE_YZ:
		if(endp->v.n < 2 || (isundef(endp->v.vals[1]) && endp->v.n >= 3 && isundef(endp->v.vals[2])))
			rterror(ref, "%s() in plane %s is missing both plane coordinates", fn, planename(global_plane));
		len = sqrt(vecab[1] * vecab[1] + vecab[2] * vecab[2]);
		if(len < EPSILON)
			rterror(ref, "%s() distance between start and endpoint zero (%e)", fn, len);
		if(radius < 0.0) {
			normal[1] = -0.5 * vecab[2];
			normal[2] = 0.5 * vecab[1];
		} else {
			normal[1] = 0.5 * vecab[2];
			normal[2] = -0.5 * vecab[1];
		}
		a = normal[1]*normal[1] + normal[2]*normal[2];
		b = 0.5 * vecab[1] * normal[1] + 0.5 * vecab[2] * normal[2];
		c = 0.25 * vecab[1] * vecab[1] + 0.25 * vecab[2] * vecab[2] - radius * radius;
		d = b*b - 4.0*a*c;
		if(d < 0.0 && fabs(d) < EPSILON)	/* Fix rounding error */
			d = 0.0;
		if(d < 0.0)
			rterror(ref, "%s() radius (%e) is less than two times distance from start to end (D=%e)", fn, radius, d);
		lambda = (-b + sqrt(d)) / (2.0*a);
		center[0] = 0.5 * vecab[1] + lambda * normal[1];
		center[2] = 0.5 * vecab[2] + lambda * normal[2];
		break;
	}

	if(fabs(radius) - (len / 2.0) < -EPSILON)
		rterror(ref, "%s() radius (%e) is less than two times start-to-endpoint distance (%e)", fn, radius, len / 2.0);

	sangle = atan2(-center[1], -center[0]) / M_PI * 180.0;
	eangle = atan2(vecab[1]-center[1], vecab[0]-center[0]) / M_PI * 180.0;
	if(!ccw) {
		double tmp = sangle;
		sangle = eangle;
		eangle = tmp;
	}
	path_start();

	switch(global_plane) {
	case PLANE_XY:
		if(turns > 1) {
			/* FIXME */
		}

		path_arc(center[0], center[1], center[2], fabs(radius), sangle, eangle);
		break;
	case PLANE_XZ:
	case PLANE_YZ:
		path_line();
		break;
	}

	/* Calculate global endpoint */
	for(i = 0; i < endp->v.n && i < 3; i++) {
		if(relative)
			*global_pos[i] += vecep[i];
		else
			*global_pos[i] = vecep[i];
	}

	return value_dup(endp);
}

static value_t *dxf_arc_cw(const node_t *ref, int argc)
{
	return allarcs(ref, argc, "arc_cw", FN_arc_cw, 1, 0);
}

static value_t *dxf_arc_cw_r(const node_t *ref, int argc)
{
	return allarcs(ref, argc, "arc_cw_r", FN_arc_cw_r, 1, 1);
}

static value_t *dxf_arc_ccw(const node_t *ref, int argc)
{
	return allarcs(ref, argc, "arc_ccw", FN_arc_ccw, 0, 0);
}

static value_t *dxf_arc_ccw_r(const node_t *ref, int argc)
{
	return allarcs(ref, argc, "arc_ccw_r", FN_arc_ccw_r, 0, 1);
}

static value_t *dxf_plane(const node_t *ref, int argc)
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

static value_t *dxf_drill(const node_t *ref, int argc)
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

	path_start();

	/* Place the centerpoint coordinates */
	switch(global_plane) {
	case PLANE_XY:
		path_circle(coor1, coor2, endp[2] - *global_pos[2], radius);
		break;
	case PLANE_XZ:
		*global_pos[0] += 2.0*coor1;
		*global_pos[2] += 2.0*coor2;
		path_line();
		*global_pos[0] = endp[0];
		*global_pos[1] = endp[1];
		*global_pos[2] = endp[2];
		path_line();
		break;
	case PLANE_YZ:
		*global_pos[1] += 2.0*coor1;
		*global_pos[2] += 2.0*coor2;
		path_line();
		*global_pos[0] = endp[0];
		*global_pos[1] = endp[1];
		*global_pos[2] = endp[2];
		path_line();
		break;
	}

	return value_new(VAL_UNDEF);
}

static value_t *dxf_circle_cw(const node_t *ref, int argc)
{
	return allcircles(ref, argc, "circle_cw", 0, 0);
}

static value_t *dxf_circle_cw_r(const node_t *ref, int argc)
{
	return allcircles(ref, argc, "circle_cw_r", 0, 1);
}

static value_t *dxf_circle_ccw(const node_t *ref, int argc)
{
	return allcircles(ref, argc, "circle_ccw", 1, 0);
}

static value_t *dxf_circle_ccw_r(const node_t *ref, int argc)
{
	return allcircles(ref, argc, "circle_ccw_r", 1, 1);
}

static value_t *dxf_layer(const node_t *ref, int argc)
{
	path_flush();			/* Layer switching must end the current path */
	if(dxfhdrdone && -1 == currentlayer)
		rtwarning(ref, "layer(): layer change after data output; some moves may be absent in output.");
	return bi_layer(ref, argc);	/* Handle upstream */
}

static value_t *dxf_relocate(const node_t *ref, int argc)
{
	value_t *v;
	path_stack(PATH_FLUSH);		/* Ensure proper relocation of the goto layer */
					/* Not ending the path would cause an extra line */
	v = bi_relocate(ref, argc);	/* Call upstream */
	path_stack(PATH_START);
	return v;
}

static value_t *dxf_dummy(const node_t *ref, int argc)
{
	(void)ref;
	(void)argc;
	return value_new(VAL_UNDEF);
}

const builtins_t builtins_dxf[] = {
	{ L"arc_ccw",		dxf_arc_ccw },
	{ L"arc_ccw_r",		dxf_arc_ccw_r },
	{ L"arc_cw",		dxf_arc_cw },
	{ L"arc_cw_r",		dxf_arc_cw_r },
	{ L"circle_ccw",	dxf_circle_ccw },
	{ L"circle_ccw_r",	dxf_circle_ccw_r },
	{ L"circle_cw",		dxf_circle_cw },
	{ L"circle_cw_r",	dxf_circle_cw_r },
	{ L"comment",		dxf_dummy },
	{ L"coolant",		dxf_dummy },
	{ L"drill",		dxf_drill },
	{ L"dwell",		dxf_dummy },
	{ L"feedmode",		dxf_dummy },
	{ L"feedrate",		dxf_dummy },
	{ L"goto",		dxf_goto },
	{ L"goto_r",		dxf_goto_r },
	{ L"layer",		dxf_layer },
	{ L"literal",		dxf_dummy },
	{ L"move",		dxf_move },
	{ L"move_r",		dxf_move_r },
	{ L"pathmode",		dxf_dummy },
	{ L"plane",		dxf_plane },
	{ L"relocate",		dxf_relocate },
	{ L"spindle",		dxf_dummy },
	{ L"spindlespeed",	dxf_dummy },
	{ L"toolchange",	dxf_dummy },
};

const int nbuiltins_dxf = NELEM(builtins_dxf);

const char dxfhdr1[] =
	"999\ngcmc " PACKAGE_VERSION "\n"
	"  0\nSECTION\n"
		"  2\nHEADER\n"
		"  9\n$ACADVER\n  1\nAC1015\n"
		"  9\n$HANDSEED\n  5\nFFFF\n"
		"  9\n$INSUNITS\n 70\n%d\n"		/* 1=inch, 4=mm */
		"  9\n$PLIMMAX\n 10\n%f\n 20\n%f\n"	/* Page size (A4) in above units */
		"  9\n$PLIMMIN\n 10\n0.0\n 20\n0.0\n"
	"  0\nENDSEC\n"
	"  0\nSECTION\n"
		"  2\nTABLES\n"
		"  0\nTABLE\n"
			"  2\nVPORT\n"
			"  5\n8\n"
			"100\nAcDbSymbolTable\n"
			" 70\n1\n"
			"  0\nVPORT\n"
			"  5\n30\n"
			"100\nAcDbSymbolTableRecord\n"
			"100\nAcDbViewportTableRecord\n"
			"  2\n*Active\n"
			" 70\n0\n"
			" 10\n0.0\n"
			" 20\n0.0\n"
			" 11\n1.0\n"
			" 21\n1.0\n"
			" 12\n286.3055555555554861\n"
			" 22\n148.5\n"
			" 13\n0.0\n"
			" 23\n0.0\n"
			" 14\n10.0\n"
			" 24\n10.0\n"
			" 15\n10.0\n"
			" 25\n10.0\n"
			" 16\n0.0\n"
			" 26\n0.0\n"
			" 36\n1.0\n"
			" 17\n0.0\n"
			" 27\n0.0\n"
			" 37\n0.0\n"
			" 40\n297.0\n"
			" 41\n1.92798353909465\n"
			" 42\n50.0\n"
			" 43\n0.0\n"
			" 44\n0.0\n"
			" 50\n0.0\n"
			" 51\n0.0\n"
			" 71\n0\n"
			" 72\n100\n"
			" 73\n1\n"
			" 74\n3\n"
			" 75\n1\n"
			" 76\n1\n"
			" 77\n0\n"
			" 78\n0\n"
			"281\n0\n"
			" 65\n1\n"
			"110\n0.0\n"
			"120\n0.0\n"
			"130\n0.0\n"
			"111\n1.0\n"
			"121\n0.0\n"
			"131\n0.0\n"
			"112\n0.0\n"
			"122\n1.0\n"
			"132\n0.0\n"
			" 79\n0\n"
			"146\n0.0\n"
		"  0\nENDTAB\n"
		"  0\nTABLE\n"
			"  2\nLTYPE\n"
			"  5\n5\n"
			"100\nAcDbSymbolTable\n"
			" 70\n3\n"
			"  0\nLTYPE\n"
			"  5\n14\n"
			"100\nAcDbSymbolTableRecord\n"
			"100\nAcDbLinetypeTableRecord\n"
			"  2\nByBlock\n"
			" 70\n0\n"
			"  3\n\n"
			" 72\n65\n"
			" 73\n0\n"
			" 40\n0.0\n"
			"  0\nLTYPE\n"
			"  5\n15\n"
			"100\nAcDbSymbolTableRecord\n"
			"100\nAcDbLinetypeTableRecord\n"
			"  2\nByLayer\n"
			" 70\n0\n"
			"  3\n\n"
			" 72\n65\n"
			" 73\n0\n"
			" 40\n0.0\n"
			"  0\nLTYPE\n"
			"  5\n16\n"
			"100\nAcDbSymbolTableRecord\n"
			"100\nAcDbLinetypeTableRecord\n"
			"  2\nCONTINUOUS\n"
			" 70\n0\n"
			"  3\nSolid line\n"
			" 72\n65\n"
			" 73\n0\n"
			" 40\n0.0\n"
			" 74\n0\n"
		"  0\nENDTAB\n"
	;

const char dxfhdr_lstart[] =
		"  0\nTABLE\n"
			"  2\nLAYER\n"
			"  5\n2\n"
			"100\nAcDbSymbolTable\n"
			" 70\n%d\n"
	;

const char dxfhdr_leach[] =
			"  0\nLAYER\n"
			"  5\n%d\n"	/* Handle */
			"100\nAcDbSymbolTableRecord\n"
			"100\nAcDbLayerTableRecord\n"
			"  2\n%s\n"
			" 70\n0\n"
			" 62\n7\n"
			"  6\nCONTINUOUS\n"
			"370\n0\n"
			"390\nF\n"
	;

const char dxfhdr_lend[] =
		"  0\nENDTAB\n"
	;

const char dxfhdr2[] =
		"  0\nTABLE\n"
			"  2\nSTYLE\n"
			"  5\n3\n"
			"100\nAcDbSymbolTable\n"
			" 70\n1\n"
			"  0\nSTYLE\n"
			"  5\n11\n"
			"100\nAcDbSymbolTableRecord\n"
			"100\nAcDbTextStyleTableRecord\n"
			"  2\nStandard\n"
			" 70\n0\n"
			" 40\n0.0\n"
			" 41\n0.75\n"
			" 50\n0.0\n"
			" 71\n0\n"
			" 42\n2.5\n"
			"  3\ntxt\n"
			"  4\n\n"
		"  0\nENDTAB\n"
		"  0\nTABLE\n"
			"  2\nVIEW\n"
			"  5\n6\n"
			"100\nAcDbSymbolTable\n"
			" 70\n0\n"
		"  0\nENDTAB\n"
		"  0\nTABLE\n"
			"  2\nUCS\n"
			"  5\n7\n"
			"100\nAcDbSymbolTable\n"
			" 70\n0\n"
		"  0\nENDTAB\n"
		"  0\nTABLE\n"
			"  2\nAPPID\n"
			"  5\n9\n"
			"100\nAcDbSymbolTable\n"
			" 70\n1\n"
			"  0\nAPPID\n"
			"  5\n12\n"
			"100\nAcDbSymbolTableRecord\n"
			"100\nAcDbRegAppTableRecord\n"
			"  2\nACAD\n"
			" 70\n0\n"
		"  0\nENDTAB\n"
		"  0\nTABLE\n"
			"  2\nDIMSTYLE\n"
			"  5\nA\n"
			"100\nAcDbSymbolTable\n"
			" 70\n1\n"
			"100\nAcDbDimStyleTable\n"
			" 71\n0\n"
			"  0\nDIMSTYLE\n"
			"105\n27\n"
			"100\nAcDbSymbolTableRecord\n"
			"100\nAcDbDimStyleTableRecord\n"
			"  2\nStandard\n"
			" 41\n2.5\n"
			" 42\n0.625\n"
			" 43\n3.75\n"
			" 44\n1.25\n"
			" 70\n0\n"
			" 73\n0\n"
			" 74\n0\n"
			" 77\n1\n"
			" 78\n8\n"
			"140\n2.5\n"
			"141\n2.5\n"
			"143\n0.03937007874016\n"
			"147\n0.625\n"
			"171\n3\n"
			"172\n1\n"
			"271\n2\n"
			"272\n2\n"
			"274\n3\n"
			"278\n44\n"
			"283\n0\n"
			"284\n8\n"
			"340\n11\n"
		"  0\nENDTAB\n"
		"  0\nTABLE\n"
			"  2\nBLOCK_RECORD\n"
			"  5\n1\n"
			"100\nAcDbSymbolTable\n"
			" 70\n1\n"
			"  0\nBLOCK_RECORD\n"
			"  5\n1F\n"
			"100\nAcDbSymbolTableRecord\n"
			"100\nAcDbBlockTableRecord\n"
			"  2\n*Model_Space\n"
			"340\n22\n"
			"  0\nBLOCK_RECORD\n"
			"  5\n1B\n"
			"100\nAcDbSymbolTableRecord\n"
			"100\nAcDbBlockTableRecord\n"
			"  2\n*Paper_Space\n"
			"340\n1E\n"
		"  0\nENDTAB\n"
	"  0\nENDSEC\n"
	"  0\nSECTION\n"
		"  2\nBLOCKS\n"
		"  0\nBLOCK\n"
			"  5\n20\n"
			"100\nAcDbEntity\n"
			"  8\n0\n"
			"100\nAcDbBlockBegin\n"
			"  2\n*Model_Space\n"
			" 70\n0\n"
			" 10\n0.0\n"
			" 20\n0.0\n"
			" 30\n0.0\n"
			"  3\n*Model_Space\n"
			"  1\n\n"
		"  0\nENDBLK\n"
		"  5\n21\n"
		"100\nAcDbEntity\n"
		"  8\n0\n"
		"100\nAcDbBlockEnd\n"
		"  0\nBLOCK\n"
			"  5\n1C\n"
			"100\nAcDbEntity\n"
			" 67\n1\n"
			"  8\n0\n"
			"100\nAcDbBlockBegin\n"
			"  2\n*Paper_Space\n"
			" 70\n0\n"
			" 10\n0.0\n"
			" 20\n0.0\n"
			" 30\n0.0\n"
			"  3\n*Paper_Space\n"
			"  1\n\n"
		"  0\nENDBLK\n"
		"  5\n1D\n"
		"100\nAcDbEntity\n"
		" 67\n1\n"
		"  8\n0\n"
		"100\nAcDbBlockEnd\n"
	"  0\nENDSEC\n"
	"  0\nSECTION\n"
	"  2\nENTITIES\n"
	/* Here follow LINEs */
	;

const char dxfftr[] =
	"  0\nENDSEC\n"	/* End of ENTITIES section */
	"  0\nSECTION\n"
		"  2\nOBJECTS\n"
		"  0\nDICTIONARY\n"
		"  5\nC\n"
		"100\nAcDbDictionary\n"
		"280\n0\n"
		"281\n1\n"
		"  3\nACAD_GROUP\n"
		"350\nD\n"
		"  3\nACAD_LAYOUT\n"
		"350\n1A\n"
		"  3\nACAD_MLINESTYLE\n"
		"350\n17\n"
		"  3\nACAD_PLOTSETTINGS\n"
		"350\n19\n"
		"  3\nACAD_PLOTSTYLENAME\n"
		"350\nE\n"
		"  3\nAcDbVariableDictionary\n"
		"350\n44\n"
		"  0\nDICTIONARY\n"
		"  5\nD\n"
		"100\nAcDbDictionary\n"
		"280\n0\n"
		"281\n1\n"
		"  0\nACDBDICTIONARYWDFLT\n"
		"  5\nE\n"
		"100\nAcDbDictionary\n"
		"281\n1\n"
		"  3\nNormal\n"
		"350\nF\n"
		"100\nAcDbDictionaryWithDefault\n"
		"340\nF\n"
		"  0\nACDBPLACEHOLDER\n"
		"  5\nF\n"
		"  0\nDICTIONARY\n"
		"  5\n17\n"
		"100\nAcDbDictionary\n"
		"280\n0\n"
		"281\n1\n"
		"  3\nStandard\n"
		"350\n18\n"
		"  0\nMLINESTYLE\n"
		"  5\n18\n"
		"100\nAcDbMlineStyle\n"
		"  2\nSTANDARD\n"
		" 70\n0\n"
		"  3\n\n"
		" 62\n256\n"
		" 51\n90.0\n"
		" 52\n90.0\n"
		" 71\n2\n"
		" 49\n0.5\n"
		" 62\n256\n"
		"  6\nBYLAYER\n"
		" 49\n-0.5\n"
		" 62\n256\n"
		"  6\nBYLAYER\n"
		"  0\nDICTIONARY\n"
		"  5\n19\n"
		"100\nAcDbDictionary\n"
		"280\n0\n"
		"281\n1\n"
		"  0\nDICTIONARY\n"
		"  5\n1A\n"
		"100\nAcDbDictionary\n"
		"281\n1\n"
		"  3\nLayout1\n"
		"350\n1E\n"
		"  3\nLayout2\n"
		"350\n26\n"
		"  3\nModel\n"
		"350\n22\n"
		"  0\nDICTIONARY\n"
		"  5\n44\n"
		"100\nAcDbDictionary\n"
		"281\n1\n"
		"  3\nDIMASSOC\n"
		"350\n46\n"
		"  3\nHIDETEXT\n"
		"350\n45\n"
		"  0\nDICTIONARYVAR\n"
		"  5\n45\n"
		"100\nDictionaryVariables\n"
		"280\n0\n"
		"  1\n2\n"
		"  0\nDICTIONARYVAR\n"
		"  5\n46\n"
		"100\nDictionaryVariables\n"
		"280\n0\n"
		"  1\n1\n"
	"  0\nENDSEC\n"
	"  0\nEOF\n"
	;
