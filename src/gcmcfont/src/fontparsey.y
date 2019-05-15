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
%{
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#include "utils.h"
#include "glyphdata.h"
#include "fontparsey.h"
#include "gcmcfont.h"

int yylex(void);

unsigned nglyphs;
unsigned naglyphs;
glyph_t **glyphs;
bbox_t gbbox = { INT_MAX, INT_MIN, INT_MAX, INT_MIN, 0, 0 };

#define GF_LEFT		0x01
#define GF_RIGHT	0x02
#define GF_ALL		(GF_LEFT | GF_RIGHT)

static glyph_t *curglyph;
static unsigned curflags;

static void glyph_new(int id);
static void glyph_add(glyph_t *g);
static stroke_t *coords_new(coord_t c);
static stroke_t *coords_add(stroke_t *s, coord_t c);
static void stroke_add(stroke_t *s);
static void glyph_check(void);

%}

%union{
	int		i;
	glyph_t		*g;
	coord_t		c;
	stroke_t	*s;
}

%token tGLYPH tLEFT tRIGHT tSTROKE
%token <i> tNUMBER

%type <c> coord
%type <s> coords
%type <g> glyph

%%
file	: /* Empty */
	| glyphs
	;

glyphs	: glyph			{ glyph_add($1); }
	| glyphs glyph		{ glyph_add($2); }
	;

glyph	: glyphid '{' bodies '}'	{ $$ = curglyph; glyph_check(); curglyph = NULL; }
	;

glyphid	: tGLYPH tNUMBER	{ glyph_new($2); }
	;

bodies	: body
	| bodies body
	;

body	: tLEFT tNUMBER		{ curglyph->left = $2; curflags |= GF_LEFT; }
	| tRIGHT tNUMBER	{ curglyph->right = $2; curflags |= GF_RIGHT; }
	| tSTROKE coords	{ stroke_add($2); }
	;

coords	: coord			{ $$ = coords_new($1); }
	| coords coord		{ $$ = coords_add($1, $2); }
	;

coord	: '(' tNUMBER ',' tNUMBER ')'	{ $$.x = $2; $$.y = $4; $$.flags = CFL_DISCONT; }
	| '[' tNUMBER ',' tNUMBER ']'	{ $$.x = $2; $$.y = $4; $$.flags = 0; }
	;

%%

static void glyph_new(int id)
{
	curglyph = calloc(1, sizeof(*curglyph));
	assert(curglyph != NULL);
	curglyph->unicode = id;
	curflags = 0;

	//if((id & (-1 << 31)) != 0)
	if(id < 0 || id > 0x10ffff)
		yyerror("Unicode id is negative or out of range (%d, 0x%08x)", id, id);

	if(id <= 0x7f) {
		// 7-bit data
		curglyph->utf8[0] = id;
	} else if(id <= 0x7ff) {
		// 11-bit data
		curglyph->utf8[0] = (id >> 6) | 0xc0;
		curglyph->utf8[1] = (id & 0x3f) | 0x80;
	} else if(id <= 0xffff) {
		// 16-bit data
		curglyph->utf8[0] = (id >> 12) | 0xe0;
		curglyph->utf8[1] = ((id >> 6) & 0x3f) | 0x80;
		curglyph->utf8[2] = (id & 0x3f) | 0x80;
	} else if(id <= 0x1fffff) {
		// 21-bit data
		curglyph->utf8[0] = (id >> 18) | 0xf0;
		curglyph->utf8[1] = ((id >> 12) & 0x3f) | 0x80;
		curglyph->utf8[2] = ((id >> 6) & 0x3f) | 0x80;
		curglyph->utf8[3] = (id & 0x3f) | 0x80;
	} else if(id <= 0x3ffffff) {
		// 26-bit data
		curglyph->utf8[0] = (id >> 24) | 0xf8;
		curglyph->utf8[1] = ((id >> 18) & 0x3f) | 0x80;
		curglyph->utf8[2] = ((id >> 12) & 0x3f) | 0x80;
		curglyph->utf8[3] = ((id >> 6) & 0x3f) | 0x80;
		curglyph->utf8[4] = (id & 0x3f) | 0x80;
	} else /*if(id <= 0x7fffffff)*/ {
		// 31-bit data
		curglyph->utf8[0] = (id >> 30) | 0xfc;
		curglyph->utf8[1] = ((id >> 24) & 0x3f) | 0x80;
		curglyph->utf8[2] = ((id >> 18) & 0x3f) | 0x80;
		curglyph->utf8[3] = ((id >> 12) & 0x3f) | 0x80;
		curglyph->utf8[4] = ((id >> 6) & 0x3f) | 0x80;
		curglyph->utf8[5] = (id & 0x3f) | 0x80;
	}
}

static void glyph_add(glyph_t *g)
{
	unsigned i, j;
	int minx = INT_MAX;
	int maxx = INT_MIN;
	int miny = INT_MAX;
	int maxy = INT_MIN;
	for(i = 0; i < g->nstrokes; i++) {
		for(j = 0; j < g->strokes[i]->ncoords; j++) {
			if(g->strokes[i]->coords[j].x < minx)	minx = g->strokes[i]->coords[j].x;
			if(g->strokes[i]->coords[j].x > maxx)	maxx = g->strokes[i]->coords[j].x;
			if(g->strokes[i]->coords[j].y < miny)	miny = g->strokes[i]->coords[j].y;
			if(g->strokes[i]->coords[j].y > maxy)	maxy = g->strokes[i]->coords[j].y;
		}
	}
	if(!i) {
		/* This happens if the char has no strokes */
		minx = miny = maxx = maxy = 0;
	}
	g->cbb.l = minx;
	g->cbb.r = maxx;
	g->cbb.b = miny;
	g->cbb.t = maxy;
	g->cbb.w = maxx - minx;
	g->cbb.h = maxy - miny;

	if(g->left < minx)	minx = g->left;
	if(g->right < minx)	minx = g->right;
	if(g->left > maxx)	maxx = g->left;
	if(g->right > maxx)	maxx = g->right;

	if(minx < gbbox.l)	gbbox.l = minx;
	if(maxx > gbbox.r)	gbbox.r = maxx;
	if(miny < gbbox.b)	gbbox.b = miny;
	if(maxy > gbbox.t)	gbbox.t = maxy;
	gbbox.w = gbbox.r - gbbox.l;
	gbbox.h = gbbox.t - gbbox.b;

	testalloc((void **)&glyphs, nglyphs, &naglyphs, sizeof(*glyphs));
	glyphs[nglyphs++] = g;
}

static stroke_t *coords_new(coord_t c)
{
	stroke_t *s = calloc(1, sizeof(*s));
	assert(s != NULL);
	testalloc((void **)&s->coords, s->ncoords, &s->nacoords, sizeof(*s->coords));
	s->coords[s->ncoords++] = c;
	return s;
}

static stroke_t *coords_add(stroke_t *s, coord_t c)
{
	assert(s != NULL);
	testalloc((void **)&s->coords, s->ncoords, &s->nacoords, sizeof(*s->coords));
	s->coords[s->ncoords++] = c;
	return s;
}

static void stroke_add(stroke_t *s)
{
	assert(curglyph != NULL);
	testalloc((void **)&curglyph->strokes, curglyph->nstrokes, &curglyph->nastrokes, sizeof(*curglyph->strokes));
	curglyph->strokes[curglyph->nstrokes++] = s;
}

static void glyph_check(void)
{
	if(!(curflags & GF_LEFT))
		yyerror("Glyph 0x%08x (%d) missing left spacing", curglyph->unicode, curglyph->unicode);
	if(!(curflags & GF_RIGHT))
		yyerror("Glyph 0x%08x (%d) missing right spacing", curglyph->unicode, curglyph->unicode);
	if((curflags & GF_ALL) != GF_ALL)
		yyerror("Glyph 0x%08x (%d) missing a mandatory element", curglyph->unicode, curglyph->unicode);
}
