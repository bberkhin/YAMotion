/*
 * G-code meta compiler - Font conversion
 *
 * Copyright (C) 2015  B. Stultiens
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
#ifndef __GCMCFONT_GLYPHDATA_H
#define __GCMCFONT_GLYPHDATA_H

#define CFL_DISCONT	0x01	/* Vertex is discontinuous */

/* Simple coordinate */
typedef struct __coord_t {
	unsigned	flags;
	int		x;
	int		y;
} coord_t;

/* A list of coordinates forming a stroke */
typedef struct __stroke_t {
	unsigned	ncoords;
	unsigned	nacoords;
	coord_t		*coords;
} stroke_t;

/* A bounding box with sizes */
typedef struct __bbox_t {
	int	l, r, b, t;
	int	w, h;
} bbox_t;

/* Glyph meta data */
typedef struct __glyph_t {
	int		unicode;	/* Codepoint */
	char		utf8[8];	/* Codepoint in UTF-8 */
	int		left;		/* Left spacing */
	int		right;		/* Right spacing */
	coord_t		bblb;		/* Bbox left-bottom */
	coord_t		bbrt;		/* Bbox right-top */
	bbox_t		cbb;		/* Calculated */
	unsigned	nstrokes;
	unsigned	nastrokes;
	stroke_t	**strokes;	/* Strokes of the glyph */
} glyph_t;

extern unsigned nglyphs;
extern unsigned naglyphs;
extern glyph_t **glyphs;
extern bbox_t gbbox;

#endif
