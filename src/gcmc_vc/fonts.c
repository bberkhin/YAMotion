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
#include "config.h"

#include <string.h>
#include <assert.h>

#include "utils.h"
#include "value.h"
#include "fonts.h"

/* Imported fonts from the generated files */
extern font_data_t font_hsans_1;
extern font_data_t font_hsans_1_rs;
extern font_data_t font_hsans_2;
extern font_data_t font_hscript_1;
extern font_data_t font_hscript_2;
extern font_data_t font_htimes;
extern font_data_t font_htimes_bold;
extern font_data_t font_htimes_italic;
extern font_data_t font_htimes_italic_bold;

static font_list_t fontlist[] = {
	{ FONT_HSANS_1,					&font_hsans_1},
	{ FONT_HSANS_1_RS,				&font_hsans_1_rs},
	{ FONT_HSANS_2,					&font_hsans_2},
	{ FONT_HSCRIPT_1,				&font_hscript_1},
	{ FONT_HSCRIPT_2,				&font_hscript_2},
	{ FONT_HTIMES,					&font_htimes},
	{ FONT_HTIMES | FONTF_BOLD,			&font_htimes_bold},
	{ FONT_HTIMES | FONTF_ITALIC,			&font_htimes_italic},
	{ FONT_HTIMES | FONTF_BOLD | FONTF_ITALIC,	&font_htimes_italic_bold}
};

/*
 * UTF-8 to UCS-32 conversion
 *
 * It includes 1, 2, 3, 4, 5 and 6 byte sequences. The 5 and 6 byte sequences
 * are deprecated by RFC 3629, but they are possible encodings for specials if
 * we ever wanted to (we are not doing the internet here).
 */
uint32_t *font_utf8_to_ucs32(const node_t *ref, const char *s)
{
	uint32_t *ucs = NULL;
	int nucs = 0;
	int naucs = 0;
	int len, ns;

	assert(s != NULL);

	ns = len = strlen(s);

	while(len > 0) {
		uint32_t val = 0;

		if((*s & 0xff) <= 0x7f) {
			/* 1-byte sequence */
			val = *s & 0x7f;
			len--;
			s++;
		} else if((*s & 0xfe) == 0xfc) {
			/* 6-byte sequence */
			if(len < 6)
				rterror(ref, "Invalid 6-byte UTF-8 sequence at %d/%d, missing bytes", ns-len, nucs);
			if((s[1] & 0xc0) != 0x80)
				rterror(ref, "Invalid 6-byte UTF-8 sequence at %d/%d, invalid second byte", ns-len, nucs);
			if((s[2] & 0xc0) != 0x80)
				rterror(ref, "Invalid 6-byte UTF-8 sequence at %d/%d, invalid third byte", ns-len, nucs);
			if((s[3] & 0xc0) != 0x80)
				rterror(ref, "Invalid 6-byte UTF-8 sequence at %d/%d, invalid fourth byte", ns-len, nucs);
			if((s[4] & 0xc0) != 0x80)
				rterror(ref, "Invalid 6-byte UTF-8 sequence at %d/%d, invalid fifth byte", ns-len, nucs);
			if((s[5] & 0xc0) != 0x80)
				rterror(ref, "Invalid 6-byte UTF-8 sequence at %d/%d, invalid sixth byte", ns-len, nucs);
			val = ((s[0] & 0x01) << 30) | ((s[1] & 0x3f) << 24) | ((s[2] & 0x3f) << 18) | ((s[3] & 0x3f) << 12) | ((s[4] & 0x3f) << 6) | (s[5] & 0x3f);
			if(val < 0x4000000)
				rtwarning(ref, "Degenerate 6-byte UTF-8 encoding at %d/%d", ns-len, nucs);
			len -= 6;
			s += 6;
		} else if((*s & 0xfc) == 0xf8) {
			/* 5-byte sequence */
			if(len < 5)
				rterror(ref, "Invalid 5-byte UTF-8 sequence at %d/%d, missing bytes", ns-len, nucs);
			if((s[1] & 0xc0) != 0x80)
				rterror(ref, "Invalid 5-byte UTF-8 sequence at %d/%d, invalid second byte", ns-len, nucs);
			if((s[2] & 0xc0) != 0x80)
				rterror(ref, "Invalid 5-byte UTF-8 sequence at %d/%d, invalid third byte", ns-len, nucs);
			if((s[3] & 0xc0) != 0x80)
				rterror(ref, "Invalid 5-byte UTF-8 sequence at %d/%d, invalid fourth byte", ns-len, nucs);
			if((s[4] & 0xc0) != 0x80)
				rterror(ref, "Invalid 5-byte UTF-8 sequence at %d/%d, invalid fifth byte", ns-len, nucs);
			val = ((s[0] & 0x03) << 24) | ((s[1] & 0x3f) << 18) | ((s[2] & 0x3f) << 12) | ((s[3] & 0x3f) << 6) | (s[4] & 0x3f);
			if(val < 0x200000)
				rtwarning(ref, "Degenerate 5-byte UTF-8 encoding at %d/%d", ns-len, nucs);
			len -= 5;
			s += 5;
		} else if((*s & 0xf8) == 0xf0) {
			/* 4-byte sequence */
			if(len < 4)
				rterror(ref, "Invalid 4-byte UTF-8 sequence at %d/%d, missing bytes", ns-len, nucs);
			if((s[1] & 0xc0) != 0x80)
				rterror(ref, "Invalid 4-byte UTF-8 sequence at %d/%d, invalid second byte", ns-len, nucs);
			if((s[2] & 0xc0) != 0x80)
				rterror(ref, "Invalid 4-byte UTF-8 sequence at %d/%d, invalid third byte", ns-len, nucs);
			if((s[3] & 0xc0) != 0x80)
				rterror(ref, "Invalid 4-byte UTF-8 sequence at %d/%d, invalid fourth byte", ns-len, nucs);
			val = ((s[0] & 0x07) << 18) | ((s[1] & 0x3f) << 12) | ((s[2] & 0x3f) << 6) | (s[3] & 0x3f);
			if(val < 0x10000)
				rtwarning(ref, "Degenerate 4-byte UTF-8 encoding at %d/%d", ns-len, nucs);
			len -= 4;
			s += 4;
		} else if((*s & 0xf0) == 0xe0) {
			/* 3-byte sequence */
			if(len < 3)
				rterror(ref, "Invalid 3-byte UTF-8 sequence at %d/%d, missing bytes", ns-len, nucs);
			if((s[1] & 0xc0) != 0x80)
				rterror(ref, "Invalid 3-byte UTF-8 sequence at %d/%d, invalid second byte", ns-len, nucs);
			if((s[2] & 0xc0) != 0x80)
				rterror(ref, "Invalid 3-byte UTF-8 sequence at %d/%d, invalid third byte", ns-len, nucs);
			val = ((s[0] & 0x0f) << 12) | ((s[1] & 0x3f) << 6) | (s[2] & 0x3f);
			if(val < 0x800)
				rtwarning(ref, "Degenerate 3-byte UTF-8 encoding at %d/%d", ns-len, nucs);
			len -= 3;
			s += 3;
		} else if((*s & 0xe0) == 0xc0) {
			/* 2-byte sequence */
			if(len < 2)
				rterror(ref, "Invalid 2-byte UTF-8 sequence at %d/%d, missing bytes", ns-len, nucs);
			if((s[1] & 0xc0) != 0x80)
				rterror(ref, "Invalid 2-byte UTF-8 sequence at %d/%d, invalid second byte", ns-len, nucs);
			val = ((s[0] & 0x1f) << 6) | (s[1] & 0x3f);
			if(val < 0x80)
				rtwarning(ref, "Degenerate 2-byte UTF-8 encoding at %d/%d", ns-len, nucs);
			len -= 2;
			s += 2;
		} else {
			rterror(ref, "Invalid UTF-8 character at %d/%d, out-of-sequence byte", ns-len, nucs);
		}

		if(val) {
			testalloc((void **)&ucs, nucs, &naucs, sizeof(*ucs));
			ucs[nucs++] = val;
		} else
			rtwarning(ref, "Skipping embedded UTF-8 NUL embedding %d/%d", ns-len, nucs);
	}

	testalloc((void **)&ucs, nucs, &naucs, sizeof(*ucs));
	ucs[nucs] = 0;	/* Zero terminate */

	return ucs;
}

static const glyph_data_t *find_char(wchar_t glyph, font_data_t *font)
{
	unsigned spos = 0;
	unsigned epos = font->nglyphs - 1;

	if((uint32_t)glyph < font->glyphs[0].unicode || (uint32_t)glyph > font->glyphs[font->nglyphs - 1].unicode)
		return NULL;	/* glyph outside defined range for font */

	while(epos >= spos) {
		unsigned c = (spos + epos) / 2;
		if(font->glyphs[c].unicode == (uint32_t)glyph)
			return &font->glyphs[c];
		if(font->glyphs[c].unicode < (uint32_t)glyph)
			spos = c + 1;
		else
			epos = c - 1;
	}
	return NULL;
}

static void font_penup(value_t *vl)
{
	value_t *vec = value_new(VAL_VECTOR);
	value_vector_add_undef(vec);
	value_vector_add_undef(vec);
	value_vector_add(vec, value_new_flt(1.0, UNIT_NONE));
	value_vectorlist_add(vl, vec);
}

static void font_pendown(value_t *vl)
{
	value_t *vec = value_new(VAL_VECTOR);
	value_vector_add_undef(vec);
	value_vector_add_undef(vec);
	value_vector_add(vec, value_new_flt(0.0, UNIT_NONE));
	value_vectorlist_add(vl, vec);
}

static void font_move(value_t *vl, double x, double y)
{
	value_t *vec = value_new(VAL_VECTOR);
	value_vector_add(vec, value_new_flt(x, UNIT_NONE));
	value_vector_add(vec, value_new_flt(y, UNIT_NONE));
	value_vector_add_undef(vec);
	value_vectorlist_add(vl, vec);
}

/*
 * Typeset an UCS-32 string with specified font.
 *
 * Returns a vectorlist with the movements in XYZ for engraving.
 *
 * The first two vectors in the returned vectorlist are always [-, -, 1.0] and
 * [0.0, 0.0, -] to ensure proper positioning (pen-up at 0,0) when starting.
 *
 * The last vector in the returned vectorlist is always the position on the
 * baseline where the next character would go. This ensures that you can use
 * the last position as an offset for additional typeset strings and it will
 * fit typographically.
 *
 * Pen-up level is at Z = 1.0
 * Pen-down level is at Z = 0.0
 *
 * The font has a standard height of 1.0, which is derived from the height of
 * the (upper case) 'X' character. No units are attached to the vectorlist to
 * make final scaling easy.
 */
value_t *font_typeset(const node_t *ref, wchar_t *ucs, int fontid)
{
	int i;
	font_data_t *fd = NULL;
	value_t *vl;
	double height;		/* Scaling */
	int xpos = 0;		/* Position tracking */
	double lasty = 0.0;	/* Progress tracking */

	/* Find the font data */
	for(i = 0; i < NELEM(fontlist); i++) {
		if(fontlist[i].id == fontid) {
			fd = fontlist[i].font;
			break;
		}
	}
	if(!fd) {
		rtwarning(ref, "Font id 0x%08x not found", fontid);
		return value_new(VAL_UNDEF);
	}

	height = fd->height;

	/* Create a vectorlist with [-, -, 1.0] and [0.0, 0.0, -] as first two entries */
	vl = value_new(VAL_VECTORLIST);
	font_penup(vl);
	font_move(vl, 0.0, 0.0);

	/* Trace all glyphs */
	for(; *ucs; ucs++) {
		unsigned s;
		unsigned c;
		const glyph_data_t *gd = find_char(*ucs, fd);
		if(!gd) {
			rtwarning(ref, "Glyph for codepoint 0x%08x not available, replacing with ' '", *ucs);
			if(!(gd = find_char(0x20, fd)))
				rterror(ref, "Replacement glyph not found, fontdata may be incomplete or corrupt");
		}

		/* Trace the glyph's strokes */
		for(s = 0; s < gd->nstrokes; s++) {
			if(gd->ncoords[s] > 0) {
				font_move(vl, (double)(xpos - gd->left + gd->strokes[s][0].x)/height, (double)gd->strokes[s][0].y/height);
				font_pendown(vl);
				for(c = 1; c < gd->ncoords[s]; c++) {
					font_move(vl, (double)(xpos - gd->left + gd->strokes[s][c].x)/height, lasty = (double)gd->strokes[s][c].y/height);
				}
				font_penup(vl);
			}
		}
		xpos += gd->right - gd->left;	/* Position at glyph's width */
		font_move(vl, (double)xpos/height, lasty);
	}

	/* Add endpoint at [xpos, 0.0, -] so we know where the text ends */
	font_move(vl, (double)xpos/height, 0.0);

	return vl;
}
