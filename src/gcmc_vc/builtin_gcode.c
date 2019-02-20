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
#include <string.h>
#include <math.h>
#include <assert.h>
#include <time.h>

#include "utils.h"
#include "builtin_svg.h"
#include "value.h"
#include "checkarg.h"

#pragma warning(disable:4996)

static const char axes[MAXAXES] = "XYZABCUVW";

void gcode_prologue(FILE *fp)
{
	char str[64];
	time_t t;
	struct tm *tm;
	t = time(NULL);
	tm = localtime(&t);
	strftime(str, sizeof(str), "%Y-%m-%d %H:%M:%S", tm);
	fprintf(fp, "(gcmc compiled code, do not change)\n");
	fprintf(fp, "(%s)\n", str);
	fprintf(fp, "(-- prologue begin --)\n");
	switch(global_plane) {
	case PLANE_XY:	fprintf(fp, "G17 ( Use XY plane )\n"); break;
	case PLANE_XZ:	fprintf(fp, "G18 ( Use XZ plane )\n"); break;
	case PLANE_YZ:	fprintf(fp, "G19 ( Use YZ plane )\n"); break;
	}
	if(cl_inch)
		fprintf(fp, "G20 ( Use inch )\n");
	else
		fprintf(fp, "G21 ( Use mm )\n");
	fprintf(fp, "G40 ( Cancel cutter radius compensation )\n");
	fprintf(fp, "G49 ( Cancel tool length compensation )\n");
	fprintf(fp, "G54 ( Default coordinate system )\n");
	fprintf(fp, "G80 ( Cancel canned cycle )\n");
	if(cl_relative)
		fprintf(fp, "G91 ( Use relative distance mode )\n");
	else
		fprintf(fp, "G90 ( Use absolute distance mode )\n");
	fprintf(fp, "G94 ( Units Per Minute feed rate mode )\n");
	fprintf(fp, "G64 ( Enable path blending for best speed )\n");
	fprintf(fp, "(-- prologue end --)\n");
}

void gcode_epilogue(FILE *fp)
{
	fprintf(fp, "(-- epilogue begin --)\n");
	fprintf(fp, "M30 (-- epilogue end --)\n");
}

static int printscalarval(const value_t *v, char tag, int globalref, int relative, int force, int angular)
{
	int rv = 0;
	double coord;
	double offs = 0.0;
	double *gpref = NULL;
	if(globalref >= 0 && globalref < naxes) {
		offs = *global_offs[globalref] + relative_offs[globalref];
		gpref = global_pos[globalref];
	}
	switch(v->type) {
	default:
		return 0;
	case VAL_INT:
	case VAL_FLOAT:
		if(angular)
			coord = value_to_deg(v);
		else
			coord = value_to_dist(v);
		if(gpref) {
			if(!cl_relative && relative) {
				coord += *gpref;
				/*
				 * The coordinate is present and must be output
				 * to prevent a second call to this function,
				 * which would cause the absolute position to
				 * move twice.
				 * This would happen on relative moves with a
				 * target coordinate within EPSILON of zero.
				 */
				force = 1;
			} else if(cl_relative && !relative)
				coord -= *gpref;
		}
		if(force || !relative || !gpref || fabs(coord + offs) >= EPSILON) {
			fprintf(ofp, " %c%.*f", tag, cl_decimals, coord + offs);
			rv = 1;
		}
		if(gpref) {
			if(cl_relative)
				*gpref += coord;
			else
				*gpref = coord;
		}
		return rv;
	}
}

static void movegoto(const node_t *ref, const value_t *arg, int mv, const char *fn, int relative, double feed)
{
	int i;
	int nax = 0;
	fprintf(ofp, "%s", mv ? "G1" : "G0");
	for(i = 0; i < arg->v.n && i < naxes; i++) {
		if(i < 3 || i >= 6)
			check_arg_unit_distance(ref, fn, arg->v.vals[i], 0);
		else
			check_arg_unit_angle(ref, fn, arg->v.vals[i], 0);
		if(printscalarval(arg->v.vals[i], axes[i], i, relative, 0, i >= 3 && i < 6))
			nax++;
	}
	/* If we did not get any output on relative movement, force it */
	if(!nax && relative) {
		for(i = 0; i < arg->v.n && i < naxes; i++) {
			if(printscalarval(arg->v.vals[i], axes[i], i, relative, 1, i >= 3 && i < 6))
				nax++;
		}
	}
	if(feed > 0.0)
		fprintf(ofp, " F%.*f", cl_decimals, feed);
	fprintf(ofp, "\n");
	if(!nax)
		rterror(ref, "All coordinates in %s() undefined", fn);
}

static value_t *gcode_move(const node_t *ref, int argc)
{
	value_t *p = bi_position(ref, 0);
	const value_t *arg;
	double feed = -1.0;
	int i;
	check_arg_one(ref, "move", argc);
	arg = value_get(argc, 0);
	if(argc > 1) {
		const value_t *ff = value_get(argc, 1);
		check_arg_scalar(ref, "move", ff, 1);
		feed = value_to_dist(ff);
	}
	if(isvectorlist(arg)) {
		if(arg->vl.n <= 0)
			rtwarning(ref, "move(): Vectorlist contains no vectors");
		for(i = 0; i < arg->vl.n; i++) {
			movegoto(ref, arg->vl.vecs[i], 1, "move", 0, feed);
		}
	} else if(isvector(arg))
		movegoto(ref, arg, 1, "move", 0, feed);
	else
		rterror(ref, "move(): First argument must be a vector or a vectorlist");
	return p;
}

static value_t *gcode_move_r(const node_t *ref, int argc)
{
	value_t *p = bi_position(ref, 0);
	const value_t *arg;
	double feed = -1.0;
	int i;
	check_arg_one(ref, "move_r", argc);
	arg = value_get(argc, 0);
	if(argc > 1) {
		const value_t *ff = value_get(argc, 1);
		check_arg_scalar(ref, "move_r", ff, 1);
		feed = value_to_dist(ff);
	}
	if(isvectorlist(arg)) {
		if(arg->vl.n <= 0)
			rtwarning(ref, "move_r(): Vectorlist contains no vectors");
		for(i = 0; i < arg->vl.n; i++) {
			movegoto(ref, arg->vl.vecs[i], 1, "move_r", 1, feed);
		}
	} else if(isvector(arg))
		movegoto(ref, arg, 1, "move_r", 1, feed);
	else
		rterror(ref, "move_r(): First argument must be a vector or a vectorlist");
	return p;
}

static value_t *gcode_goto(const node_t *ref, int argc)
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
			movegoto(ref, arg->vl.vecs[i], 0, "goto", 0, -1.0);
		}
	} else if(isvector(arg))
		movegoto(ref, arg, 0, "goto", 0, -1.0);
	else
		rterror(ref, "goto(): Argument must be a vector or a vectorlist");
	return p;
}

static value_t *gcode_goto_r(const node_t *ref, int argc)
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
			movegoto(ref, arg->vl.vecs[i], 0, "goto_r", 1, -1.0);
		}
	} else if(isvector(arg))
		movegoto(ref, arg, 0, "goto_r", 1, -1.0);
	else
		rterror(ref, "goto_r(): Argument must be a vector or a vectorlist");
	return p;
}

static value_t *gcode_feedmode(const node_t *ref, int argc)
{
	int i = -1;
	const value_t *arg;
	check_arg_one(ref, "feedmode", argc);
	arg = value_get(argc, 0);
	if(isscalar(arg)) {
		i = value_to_int(arg);
	} else if(isstring(arg)) {
		if(!wcscasecmp(arg->str.chs, L"inverse"))
			i = 0;
		else if(!wcscasecmp(arg->str.chs, L"upm"))
			i = 1;
		else if(!wcscasecmp(arg->str.chs, L"upr"))
			i = 2;
	}
	switch(i) {
	case 0: fprintf(ofp, "G93\n"); break;	/* FIXME: G1/G2/G3 should all have F words added */
	case 1: fprintf(ofp, "G94\n"); break;
	case 2:	fprintf(ofp, "G95\n"); break;
	default:
		rterror(ref, "Feed mode must be one of 0 (\"inverse\"), 1 (\"upm\") or 2 (\"upr\")");
	}
	return value_new(VAL_UNDEF);
}

static value_t *gcode_feedrate(const node_t *ref, int argc)
{
	const value_t *arg;
	check_arg_one(ref, "feedrate", argc);
	arg = value_get(argc, 0);
	check_arg_scalar(ref, "feedrate", arg, 0);
	check_arg_unit_distance(ref, "feedrate", arg, 0);
	fprintf(ofp, "F%.*f\n", cl_decimals, value_to_dist(arg));
	return value_new(VAL_UNDEF);
}

static value_t *gcode_spindle(const node_t *ref, int argc)
{
	const value_t *arg;
	check_arg_one(ref, "spindle", argc);
	arg = value_get(argc, 0);
	check_arg_scalar(ref, "spindle", arg, 0);
	double d = value_to_double(arg);
	if(fabs(d) < EPSILON)
		fprintf(ofp, "M5\n");			/* Stop */
	else if(d < 0.0)
		fprintf(ofp, "S%.*f\nM4\n", cl_decimals, -d);	/* CCW */
	else
		fprintf(ofp, "S%.*f\nM3\n", cl_decimals, d);	/* CW */
	return value_new(VAL_UNDEF);
}

static value_t *gcode_spindlespeed(const node_t *ref, int argc)
{
	const value_t *arg;
	check_arg_one(ref, "spindlespeed", argc);
	arg = value_get(argc, 0);
	check_arg_scalar(ref, "spindlespeed", arg, 0);
	check_arg_unit_none(ref, "spindlespeed", arg, 0);
	double d = value_to_double(arg);
	if(d < 0.0)
		rterror(ref, "Spindle speed must be >= 0");
	fprintf(ofp, "S%.*f\n", cl_decimals, d);
	return value_new(VAL_UNDEF);
}

static value_t *gcode_toolchange(const node_t *ref, int argc)
{
	int j = 0;
	const value_t *arg;
	check_arg_one(ref, "toolchange", argc);
	arg = value_get(argc, 0);
	check_arg_scalar(ref, "toolchange", arg, 0);
	check_arg_unit_none(ref, "toolchange", arg, 0);
	int i = value_to_int(arg);
	if(i < 0)
		rterror(ref, "Tool index must be >= 0");
	if(argc > 1) {
		arg = value_get(argc, 1);
		check_arg_unit_none(ref, "toolchange", arg, 1);
		j = value_to_boolean(arg);
	}
	fprintf(ofp, "T%d\n", i);	/* Tool ID to change to */
	fprintf(ofp, "M6\n");		/* Actually perform the change */
	if(j)
		fprintf(ofp, "G43 H%d\n", i);
	return value_new(VAL_UNDEF);
}

static value_t *gcode_coolant(const node_t *ref, int argc)
{
	int i = -1;
	const value_t *arg;
	check_arg_one(ref, "coolant", argc);
	arg = value_get(argc, 0);
	check_arg_unit_none(ref, "coolant", arg, 0);
	if(isscalar(arg)) {
		i = value_to_int(arg);
	} else if(isstring(arg)) {
		if(!wcscasecmp(arg->str.chs, L"off"))
			i = 0;
		else if(!wcscasecmp(arg->str.chs, L"mist"))
			i = 1;
		else if(!wcscasecmp(arg->str.chs, L"flood"))
			i = 2;
		else if(!wcscasecmp(arg->str.chs, L"mist+flood"))
			i = 3;
	}

	switch(i) {
	case 0: fprintf(ofp, "M9\n"); break;		/* Coolant off */
	case 1: fprintf(ofp, "M7\n"); break;		/* Coolant mist */
	case 2: fprintf(ofp, "M8\n"); break;		/* Coolant flood */
	case 3: fprintf(ofp, "M7\nM8\n"); break;	/* Coolant mist and flood */
	default:
		rterror(ref, "Coolant must be on of: 0 (\"off\"), 1 (\"mist\"), 2 (\"flood\") or 3 (\"mist+flood\")");
	}
	return value_new(VAL_UNDEF);
}

static value_t *gcode_dwell(const node_t *ref, int argc)
{
	const value_t *arg;
	double d;
	check_arg_one(ref, "dwell", argc);
	arg = value_get(argc, 0);
	check_arg_scalar(ref, "dwell", arg, 0);
	check_arg_unit_none(ref, "dwell", arg, 0);
	d = value_to_double(arg);
	if(d < 0.0)
		rterror(ref, "Dwell cannot have negative seconds (%f)", d);
	fprintf(ofp, "G4 P%.*f\n", cl_decimals, d);
	return value_new(VAL_UNDEF);
}

static value_t *gcode_plane(const node_t *ref, int argc)
{
	value_t *v;
	const value_t *arg;
	check_arg_one(ref, "plane", argc);
	arg = value_get(argc, 0);
	if(isundef(arg))
		return value_new_int(global_plane, UNIT_NONE);
	v = bi_plane(ref, argc);	/* Let the builtin function handle the args and globals */
	switch(global_plane) {
	case PLANE_XY:	fprintf(ofp, "G17\n"); break;
	case PLANE_XZ:	fprintf(ofp, "G18\n"); break;
	case PLANE_YZ:	fprintf(ofp, "G19\n"); break;
	}
	return v;
}

typedef enum {
	FN_arc_cw,
	FN_arc_cw_r,
	FN_arc_ccw,
	FN_arc_ccw_r,
} arcfns_et;

static value_t *allarcs(const node_t *ref, int argc, const char *fn, arcfns_et ft, const char *gcode, int relative)
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
	double orgradius;
	double radius = orgradius = value_to_dist(rad);
	double vecep[3] = {0.0, 0.0, 0.0};
	double vecab[3];
	double normal[3] = {0.0, 0.0, 0.0};
	double center[3] = {0.0, 0.0, 0.0};
	double len = 0.0;
	double lambda;
	double a, b, c, d;
	int turns = 0;
	int coormask = 0;

	if(argc > 2) {
		const value_t *t = value_get(argc, 2);
		check_arg_scalar(ref, fn, t, 2);
		check_arg_unit_none(ref, fn, t, 2);
		turns = value_to_int(t);
		if(turns < 1)
			rterror(ref, "%s() Number of turns must be >= 1", fn);
	}

	if(ft == FN_arc_ccw || ft == FN_arc_ccw_r)
		radius *= -1.0;

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
	 *   R(x) = 0.5 * B(x) + l * n(x)
	 *   R(y) = 0.5 * B(y) + l * n(y)
	 *   R(x)^2 + R(y)^2 = r^2
	 */
	/* endpoint coordinates */
	if(endp->v.n >= 1) {
		check_arg_unit_distance(ref, fn, endp->v.vals[0], 0);
		if(!isundef(endp->v.vals[0])) {
			vecep[0] = value_to_dist(endp->v.vals[0]);
			coormask |= 0x1;
		} else
			vecep[0] = *global_pos[0];
	}
	if(endp->v.n >= 2) {
		check_arg_unit_distance(ref, fn, endp->v.vals[1], 0);
		if(!isundef(endp->v.vals[1])) {
			vecep[1] = value_to_dist(endp->v.vals[1]);
			coormask |= 0x2;
		} else
			vecep[1] = *global_pos[1];
	}
	if(endp->v.n >= 3) {
		check_arg_unit_distance(ref, fn, endp->v.vals[2], 0);
		if(!isundef(endp->v.vals[2])) {
			vecep[2] = value_to_dist(endp->v.vals[2]);
			coormask |= 0x4;
		} else
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
			rterror(ref, "%s() radius (%e) is less than two times distance from start to end (D=%e)", fn, orgradius, d);
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
			rterror(ref, "%s() radius (%e) is less than two times distance from start to end (D=%e)", fn, orgradius, d);
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
			rterror(ref, "%s() radius (%e) is less than two times distance from start to end (D=%e)", fn, orgradius, d);
		lambda = (-b + sqrt(d)) / (2.0*a);
		center[1] = 0.5 * vecab[1] + lambda * normal[1];
		center[2] = 0.5 * vecab[2] + lambda * normal[2];
		break;
	}

	if(fabs(radius) - (len / 2.0) < -EPSILON)
		rterror(ref, "%s() radius (%e) is less than two times start-to-endpoint distance (%e)", fn, orgradius, len / 2.0);

	/* This is the endpoint */
	fprintf(ofp, "%s", gcode);
	for(i = 0; i < endp->v.n && i < 3; i++) {
		if(coormask & 1)	/* Only output coordinates defined in endpoint */
			fprintf(ofp, " %c%.*f", axes[i], cl_decimals, vecab[i] + *global_offs[i] + relative_offs[i] + (cl_relative ? 0.0 : *global_pos[i]));
		coormask >>= 1;
		if(relative)
			*global_pos[i] += vecep[i];
		else
			*global_pos[i] = vecep[i];
	}

	/* Place the centerpoint coordinates */
	switch(global_plane) {
	case PLANE_XY:	fprintf(ofp, " I%.*f J%.*f", cl_decimals, center[0], cl_decimals, center[1]); break;
	case PLANE_XZ:	fprintf(ofp, " I%.*f K%.*f", cl_decimals, center[0], cl_decimals, center[2]); break;
	case PLANE_YZ:	fprintf(ofp, " J%.*f K%.*f", cl_decimals, center[1], cl_decimals, center[2]); break;
	}

	if(turns)
		fprintf(ofp, " P%d", turns);

	fprintf(ofp, "\n");

	return value_dup(endp);
}

static value_t *gcode_arc_cw(const node_t *ref, int argc)
{
	return allarcs(ref, argc, "arc_cw", FN_arc_cw, "G2", 0);
}

static value_t *gcode_arc_cw_r(const node_t *ref, int argc)
{
	return allarcs(ref, argc, "arc_cw_r", FN_arc_cw_r, "G2", 1);
}

static value_t *gcode_arc_ccw(const node_t *ref, int argc)
{
	return allarcs(ref, argc, "arc_ccw", FN_arc_ccw, "G3", 0);
}

static value_t *gcode_arc_ccw_r(const node_t *ref, int argc)
{
	return allarcs(ref, argc, "arc_ccw_r", FN_arc_ccw_r, "G3", 1);
}

static value_t *gcode_drill(const node_t *ref, int argc)
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

	fprintf(ofp, "G73");
	for(i = 0; i < vec->v.n && i < 3; i++) {
		check_arg_unit_distance(ref, "drill", vec->v.vals[i], 0);
		printscalarval(vec->v.vals[i], axes[i], i, cl_relative, 0, 0);
	}
	printscalarval(retract, 'R', 2, cl_relative, 1, 0);
	printscalarval(delta, 'Q', -1, 0, 0, 0);
	if(rep)
		fprintf(ofp, " L%d", rep);
	fprintf(ofp, "\n");
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
static value_t *allcircles(const node_t *ref, int argc, const char *fn, const char *gcode, int relative)
{
	int i;
	const value_t *arg0;
	int turns = 0;
	double endp[3] = {0.0, 0.0, 0.0};
	double coor1 = 0.0;
	double coor2 = 0.0;
	int coormask = 0;

	check_arg_one(ref, fn, argc);
	arg0 = value_get(argc, 0);

	if(!cl_relative) {
		endp[0] = *global_pos[0] + *global_offs[0] + relative_offs[0];
		endp[1] = *global_pos[1] + *global_offs[1] + relative_offs[1];
		endp[2] = *global_pos[2] + *global_offs[2] + relative_offs[2];
	}

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
			coormask = 0x3;
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
				endp[2] = value_to_dist(arg0->v.vals[2]) - (cl_relative ? 0.0 : (*global_offs[2] + relative_offs[2]));
				coormask |= 0x4;
			}
			break;
		case PLANE_XZ:
			if(arg0->v.n < 3 || isundef(arg0->v.vals[0]) || isundef(arg0->v.vals[2]))
				rterror(ref, "%s() in plane %s is missing plane coordinates", fn, planename(global_plane));
			coormask = 0x5;
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
			if(!isundef(arg0->v.vals[1])) {
				endp[1] = value_to_dist(arg0->v.vals[1]) - (cl_relative ? 0.0 : (*global_offs[1] + relative_offs[1]));
				coormask |= 0x2;
			}
			break;
		case PLANE_YZ:
			if(arg0->v.n < 3 || isundef(arg0->v.vals[1]) || isundef(arg0->v.vals[2]))
				rterror(ref, "%s() in plane %s is missing plane coordinates", fn, planename(global_plane));
			coormask = 0x6;
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
			if(!isundef(arg0->v.vals[0])) {
				endp[0] = value_to_dist(arg0->v.vals[0]) - (cl_relative ? 0.0 : (*global_offs[0] + relative_offs[0]));
				coormask |= 0x1;
			}
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
		/*
		 * With a radius only we could ommit the coordinates entirely,
		 * but it is nicer to have the active plane's coordinates in
		 * the output.
		 */
		switch(global_plane) {
		case PLANE_XY: coormask = 0x3; break;
		case PLANE_XZ: coormask = 0x5; break;
		case PLANE_YZ: coormask = 0x6; break;
		}
	} else {
		rterror(ref, "%s(): First argument neither vector nor scalar", fn);
		return value_new(VAL_UNDEF);
	}

	/* Here we have coor1,coor2 to point to relative center from current position */
	if(sqrt(coor1*coor1 + coor2*coor2) < EPSILON)
		rterror(ref, "%s() radius of circle is zero", fn);

	/* The end-point is the same as the start-point, except, maybe, for the out-of-plane coordinate */
	fprintf(ofp, "%s", gcode);
	for(i = 0; i < 3; i++) {
		if(coormask & 1)	/* Only output coordinates defined in source */
			fprintf(ofp, " %c%.*f", axes[i], cl_decimals, endp[i]);
		coormask >>= 1;
	}

	/* Place the centerpoint coordinates */
	switch(global_plane) {
	case PLANE_XY:	fprintf(ofp, " I%.*f J%.*f", cl_decimals, coor1, cl_decimals, coor2); break;
	case PLANE_XZ:	fprintf(ofp, " I%.*f K%.*f", cl_decimals, coor1, cl_decimals, coor2); break;
	case PLANE_YZ:	fprintf(ofp, " J%.*f K%.*f", cl_decimals, coor1, cl_decimals, coor2); break;
	}

	if(turns)
		fprintf(ofp, " P%d", turns);

	fprintf(ofp, "\n");

	return value_new(VAL_UNDEF);
}

static value_t *gcode_circle_cw(const node_t *ref, int argc)
{
	return allcircles(ref, argc, "circle_cw", "G2", 0);
}

static value_t *gcode_circle_cw_r(const node_t *ref, int argc)
{
	return allcircles(ref, argc, "circle_cw_r", "G2", 1);
}

static value_t *gcode_circle_ccw(const node_t *ref, int argc)
{
	return allcircles(ref, argc, "circle_ccw", "G3", 0);
}

static value_t *gcode_circle_ccw_r(const node_t *ref, int argc)
{
	return allcircles(ref, argc, "circle_ccw_r", "G3", 1);
}

static value_t *gcode_pause(const node_t *ref, int argc)
{
	int b = 0;
	if(argc > 0) {
		const value_t *arg0 = value_get(argc, 0);
		check_arg_scalar(ref, "pause", arg0, 0);
		check_arg_unit_none(ref, "pause", arg0, 0);
		b = value_to_boolean(arg0);
	}
	if(!b)
		fprintf(ofp, "M0\n");
	else
		fprintf(ofp, "M1\n");
	return value_new(VAL_UNDEF);
}

static value_t *gcode_fixpos_restore(const node_t *ref, int argc)
{
	const value_t *arg;
	int b;
	int i;
	check_arg_one(ref, "fixpos_restore", argc);
	arg = value_get(argc, 0);
	check_arg_scalar(ref, "fixpos_restore", arg, argc);
	check_arg_unit_none(ref, "fixpos_restore", arg, argc);
	b = value_to_boolean(arg);

	if(argc > 1) {
		arg = value_get(argc, 1);
		check_arg_vector(ref, "fixpos_restore", arg, 1);
	} else
		arg = NULL;
	fprintf(ofp, "%s", b ? "G30" : "G28");
	for(i = 0; arg && i < arg->v.n; i++) {
		if(arg->v.vals[i]->type == VAL_INT || arg->v.vals[i]->type == VAL_FLOAT) {
			if(i < 3 || i >= 6)
				check_arg_unit_distance(ref, "fixpos_restore", arg->v.vals[i], 1);
			else
				check_arg_unit_angle(ref, "fixpos_restore", arg->v.vals[i], 1);
			printscalarval(arg->v.vals[i], axes[i], -1, 0, 0, i >= 3 && i < 6);
		}
	}
	fprintf(ofp, "\n");
	return bi_fixpos_restore(ref, argc);	/* Call upstream to restore the actual coordinate */
}

static value_t *gcode_fixpos_store(const node_t *ref, int argc)
{
	const value_t *arg;
	int b;
	check_arg_one(ref, "fixpos_store", argc);
	arg = value_get(argc, 0);
	check_arg_scalar(ref, "fixpos_store", arg, argc);
	check_arg_unit_none(ref, "fixpos_store", arg, argc);
	b = value_to_boolean(arg);
	fprintf(ofp, "%s\n", b ? "G30.1" : "G28.1");
	return bi_fixpos_store(ref, argc);		/* Call upstream to save the actual coordinate */
}

static value_t *gcode_pathmode(const node_t *ref, int argc)
{
	if(argc == 1) {
		const value_t *arg = value_get(argc, 0);
		int b;
		check_arg_scalar(ref, "pathmode", arg, argc);
		check_arg_unit_none(ref, "pathmode", arg, argc);
		b = value_to_boolean(arg);
		fprintf(ofp, "%s\n", b ? "G61" : "G64");
	} else if(argc == 2) {
		const value_t *arg0 = value_get(argc, 0);
		const value_t *arg1 = value_get(argc, 1);
		double p, q;
		check_arg_scalar(ref, "pathmode", arg0, argc);
		check_arg_unit_distance(ref, "pathmode", arg0, argc);
		if(!isundef(arg1)) {
			check_arg_scalar(ref, "pathmode", arg1, argc);
			check_arg_unit_distance(ref, "pathmode", arg1, argc);
		}
		p = value_to_dist(arg0);
		if(!isundef(arg1)) {
			q = value_to_dist(arg1);
			fprintf(ofp, "G64 P%*f Q%*f\n", cl_decimals, p, cl_decimals, q);
		} else {
			fprintf(ofp, "G64 P%*f\n", cl_decimals, p);
		}
	} else {
		rterror(ref, "pathmode(): expects one or two arguments");
	}
	return value_new(VAL_UNDEF);
}

const builtins_t builtins_gcode[] = {
	{ L"arc_ccw",		gcode_arc_ccw },
	{ L"arc_ccw_r",		gcode_arc_ccw_r },
	{ L"arc_cw",		gcode_arc_cw },
	{ L"arc_cw_r",		gcode_arc_cw_r },
	{ L"circle_ccw",	gcode_circle_ccw },
	{ L"circle_ccw_r",	gcode_circle_ccw_r },
	{ L"circle_cw",		gcode_circle_cw },
	{ L"circle_cw_r",	gcode_circle_cw_r },
	{ L"coolant",		gcode_coolant },
	{ L"drill",		gcode_drill },
	{ L"dwell",		gcode_dwell },
	{ L"feedmode",		gcode_feedmode },
	{ L"feedrate",		gcode_feedrate },
	{ L"fixpos_restore",	gcode_fixpos_restore },
	{ L"fixpos_store",	gcode_fixpos_store },
	{ L"goto",		gcode_goto },
	{ L"goto_r",		gcode_goto_r },
	{ L"move",		gcode_move },
	{ L"move_r",		gcode_move_r },
	{ L"pathmode",		gcode_pathmode },
	{ L"pause",		gcode_pause },
	{ L"plane",		gcode_plane },
	{ L"spindle",		gcode_spindle },
	{ L"spindlespeed",	gcode_spindlespeed },
	{ L"toolchange",	gcode_toolchange },
};

const int nbuiltins_gcode = NELEM(builtins_gcode);
