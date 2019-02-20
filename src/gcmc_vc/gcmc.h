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
#ifndef __GCMC_GCMC_H
#define __GCMC_GCMC_H

#include <stdio.h>
#include <stdarg.h>

#include "grammartypes.h"
#include "value.h"

#ifdef _MSC_VER
#define __attribute__(A) /* do nothing */
#endif

#define EPSILON	1e-12	/* This is where doubles lose precision */
#define MAXAXES	9	/* We support 6 axes by default XYZABCUVW */

typedef enum {
	PLANE_XY,
	PLANE_XZ,
	PLANE_YZ,
} plane_et;

typedef enum {
	FMT_NONE = 0,
	FMT_GCODE,
	FMT_SVG,
	FMT_DXF,
} format_et;

int yyerror(const char *fmt, ...) __attribute__((format (printf, 1, 2)));
int yyfatal(const char *fmt, ...) __attribute__((format (printf, 1, 2)));
int rterror(const node_t *n, const char *fmt, ...) __attribute__((format (printf, 2, 3)));
int rtwarning(const node_t *n, const char *fmt, ...) __attribute__((format (printf, 2, 3)));
int rtdeprecated(const node_t *n, const char *fmt, ...) __attribute__((format (printf, 2, 3)));
int rtinternal(const node_t *n, const char *fmt, ...) __attribute__((format (printf, 2, 3)));
const char *includepath_get(int idx);

extern FILE *ofp;
extern int cl_decimals;
extern int cl_relative;
extern int cl_inch;
extern int cl_svg_movelayer;
extern int cl_svg_grid;
extern int cl_svg_flip;
extern double cl_svg_toolwidth;
extern double cl_svg_opacity;
extern format_et cl_format;
extern int cl_pedantic;
extern int runtimeerrors;
extern int runtimewarnings;
extern int naxes;

extern double *global_offs[MAXAXES];
extern double relative_offs[MAXAXES];
extern double *global_pos[MAXAXES];
extern plane_et global_plane;

#endif
