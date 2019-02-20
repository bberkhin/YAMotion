/*
 * G-code meta compiler
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
#ifndef __GCMC_FONTS_H
#define __GCMC_FONTS_H

#include <stdint.h>

/* Data definition of the imported fonts */
typedef struct __glyph_stroke_t {
	int8_t	x, y;
} glyph_stroke_t;

typedef struct __glyph_data_t {
	uint32_t		unicode;
	int8_t			bbl, bbb, bbr, bbt;
	int8_t			left, right;
	uint8_t			reserved;
	uint8_t			nstrokes;
	const glyph_stroke_t	**strokes;
	uint8_t			*ncoords;
} glyph_data_t;

typedef struct __font_data_t {
	const char		*name;
	int			height;
	unsigned		nglyphs;
	const glyph_data_t	*glyphs;
} font_data_t;

/* Local handling */
#define FONTF_BOLD	0x0100
#define FONTF_ITALIC	0x0200

#define FONT_HSANS_1	0x0001
#define FONT_HSANS_2	0x0002
#define FONT_HSCRIPT_1	0x0003
#define FONT_HSCRIPT_2	0x0004
#define FONT_HTIMES	0x0005
#define FONT_HSANS_1_RS	0x0006

typedef struct __font_list_t {
	int	id;
	font_data_t	*font;
} font_list_t;

value_t *font_typeset(const node_t *ref, wchar_t *ucs, int fontid);

#endif
