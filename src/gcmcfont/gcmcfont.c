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
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include "getopt.h"

#include "gcmcfont.h"
#include "glyphdata.h"
#include "utils.h"

#define CHSW	16	// Number of chars next to each other in SVG image

static int chsw = CHSW;
static int cl_rapid = 0;
static int cl_intermediate = 0;

static const char *license_strings[] = {
	"This is a generated file, please DO NOT EDIT",
	"",
	"The original data is derived from the Hershey fonts, which comes with the",
	"following license:",
	"",
	"USE RESTRICTION:",
	"This distribution of the Hershey Fonts may be used by anyone for any purpose,",
	"commercial or otherwise, providing that:",
	"1. The following acknowledgements must be distributed with the font data:",
	"   - The Hershey Fonts were originally created by Dr. A. V. Hershey while",
	"     working at the U. S. National Bureau of Standards.",
	"   - The format of the Font data in this distribution was originally created by",
	"     James Hurt",
	"     Cognition, Inc.",
	"     900 Technology Park Drive",
	"     Billerica, MA 01821",
	"     (mit-eddie!ci-dandelion!hurt)",
	"2. The font data in this distribution may be converted into any other format",
	"   *EXCEPT* the format distributed by the U.S. NTIS (which organization holds",
	"   the rights to the distribution and use of the font data in that particular",
	"   format). Not that anybody would really *want* to use their format... each",
	"   point is described in eight bytes as \"xxx yyy:\", where xxx and yyy are the",
	"   coordinate values as ASCII numbers.",
	"",
	"",
	"",
	"All modifications and extensions to the fonts and font-data are distruted under",
	"the Creative Commons Attribution 4.0 International license (CC-BY-4.0,",
	"see: http://creativecommons.org/licenses/by/4.0/). The modified format and font",
	"data ((c) 2015) are provided by Bertho Stultiens (gcmc@vagrearg.org).",
	"",
	"Modifications include:",
	"- rename files for better understanding",
	"- put all single- and multi-stroke font-data into files to have all glyphs of",
	"  the same family in one file",
	"- integrate greek, cyrillic and symbols into one font file",
	"- assign unicode codepoints to the glyphs",
	"- reformat the data to be more readable and useful",
	"- realign all glyphs onto the baseline and the coordinates where right and up",
	"  are positive",
	"- add accented characters",
	""
};

extern FILE *yyin;
int yyparse(void);

void yyerror(const char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	fprintf(stderr, "%s:%d:%d: ", filename, linenr, charnr);
	vfprintf(stderr, fmt, va);
	fprintf(stderr, "\n");
	va_end(va);
	exit(1);
}

static void svg_glyph(FILE *fp, glyph_t *g, int x0, int y0)
{
	int j, k;
	int pathid = 0;
	fprintf(fp, "\t<g id=\"glyph_%d\" transform=\"translate(%d,%d)\">\n", g->unicode, x0, y0 + gbbox.h);
	fprintf(fp, "\t<text x=\"%d\" y=\"%d\" font-family=\"sans\" font-size=\"5\" fill=\"black\">U+%04x</text>\n", 1, -gbbox.h-1, g->unicode);
	fprintf(fp, "\t<g transform=\"scale(1,-1) translate(%d,%d)\">\n", -gbbox.l, -gbbox.b);
	// Font BBox
	fprintf(fp, "\t\t<path id=\"fbbox_%d\" style=\"stroke:#00ff00;stroke-width:0.1;fill:none\" d=\"M%d,%d L%d,%d L%d,%d L%d,%d Z\" />\n",
		g->unicode,
		gbbox.l, gbbox.b,
		gbbox.r, gbbox.b,
		gbbox.r, gbbox.t,
		gbbox.l, gbbox.t);
	// Center the glyph in the global bbox
	j = g->right - g->left;
	if(g->cbb.w > j)
		j = g->cbb.w;
	fprintf(fp, "\t\t<g transform=\"translate(%d,0)\">\n", gbbox.l - g->left + (gbbox.w - j)/2);
	// Glyph BBox
	fprintf(fp, "\t\t<path id=\"gbbox_%d\" style=\"stroke:#ff0000;stroke-width:0.1;fill:none\" d=\"M%d,%d L%d,%d L%d,%d L%d,%d Z\" />\n",
		g->unicode,
		g->cbb.l, g->cbb.b,
		g->cbb.r, g->cbb.b,
		g->cbb.r, g->cbb.t,
		g->cbb.l, g->cbb.t);
	// Glyph left/right spacing
	if(!g->cbb.h) {
		fprintf(fp, "\t\t<path id=\"left_%d\" style=\"stroke:#0000ff;stroke-width:0.1;fill:none\" d=\"M%d,%.1f L%d,%.1f\" />\n",
			g->unicode,
			g->left, (float)g->cbb.t - 0.2,
			g->left, (float)g->cbb.t + 0.2);
		fprintf(fp, "\t\t<path id=\"right_%d\" style=\"stroke:#0000ff;stroke-width:0.1;fill:none\" d=\"M%d,%.1f L%d,%.1f\" />\n",
			g->unicode,
			g->right, (float)g->cbb.t - 0.2,
			g->right, (float)g->cbb.b + 0.2);
	} else {
		fprintf(fp, "\t\t<path id=\"left_%d\" style=\"stroke:#0000ff;stroke-width:0.1;fill:none\" d=\"M%d,%d L%d,%d\" />\n",
			g->unicode,
			g->left, g->cbb.t,
			g->left, g->cbb.b);
		fprintf(fp, "\t\t<path id=\"right_%d\" style=\"stroke:#0000ff;stroke-width:0.1;fill:none\" d=\"M%d,%d L%d,%d\" />\n",
			g->unicode,
			g->right, g->cbb.t,
			g->right, g->cbb.b);
	}
	// Glyph base
	fprintf(fp, "\t\t<path id=\"base_%d\" style=\"stroke:#0000ff;stroke-width:0.1;fill:none\" d=\"M%d,%d L%d,%d\" />\n",
		g->unicode,
		g->left, 0,
		g->right, 0);

	// Show the stroke-entry
	if(cl_rapid && g->nstrokes && g->strokes[0]->ncoords) {
		int x1 = g->strokes[0]->coords[0].x;
		int y1 = g->strokes[0]->coords[0].y;
		fprintf(fp, "\t\t<path style=\"stroke:#808080;stroke-width:0.1;fill:none;stroke-linecap:round;stroke-linejoin:round\" id=\"estroke_%d_%d\" d=\"M%d,%d L%d,%d\" />", g->unicode, pathid++, g->cbb.l, 0, x1, y1);
	}
	// Glyph strokes
	for(j = 0; j < g->nstrokes; j++) {
		if(g->strokes[j]->ncoords > 0) {
			/* Mark the start point */
			int x = g->strokes[j]->coords[0].x;
			int y = g->strokes[j]->coords[0].y;
			fprintf(fp, "\t\t<circle style=\"stroke:#ff0000;stroke-width:0.1;fill:none\" id=\"cstroke_%d_%d\" cx=\"%d\" cy=\"%d\" r=\"0.5\"/>\n", g->unicode, pathid, x, y);
			/* Output the stroke */
			fprintf(fp, "\t\t<path style=\"stroke:#000000;stroke-width:0.5;fill:none;stroke-linecap:round;stroke-linejoin:round\" id=\"stroke_%d_%d\" d=\"M%d,%d", g->unicode, pathid++, x, y);
			for(k = 1; k < g->strokes[j]->ncoords; k++) {
				x = g->strokes[j]->coords[k].x;
				y = g->strokes[j]->coords[k].y;
				fprintf(fp, " L%d,%d", x, y);
			}
			fprintf(fp, "\" />\n");
			/* Mark the end point */
			fprintf(fp, "\t\t<circle style=\"stroke:#00ff00;stroke-width:0.1;fill:none\" id=\"estroke_%d_%d\" cx=\"%d\" cy=\"%d\" r=\"0.5\"/>\n", g->unicode, pathid, x, y);
			/* Mark the rapid move too */
			if(cl_rapid && j < g->nstrokes-1) {
				int x1 = g->strokes[j+1]->coords[0].x;
				int y1 = g->strokes[j+1]->coords[0].y;
				if(!(x == x1 && y == y1))
				fprintf(fp, "\t\t<path style=\"stroke:#808080;stroke-width:0.1;fill:none;stroke-linecap:round;stroke-linejoin:round\" id=\"mstroke_%d_%d\" d=\"M%d,%d L%d,%d\" />", g->unicode, pathid++, x, y, x1, y1);
			}
			if(cl_intermediate) {
				/* Mark the intermediate points */
				for(k = 1; k < g->strokes[j]->ncoords-1; k++) {
					x = g->strokes[j]->coords[k].x;
					y = g->strokes[j]->coords[k].y;
					fprintf(fp, "\t\t<circle style=\"stroke:#808080;stroke-width:0.1;fill:none\" id=\"estroke_%d_%d_%d\" cx=\"%d\" cy=\"%d\" r=\"0.5\"/>\n", g->unicode, pathid, k, x, y);
				}
			}
		}
	}
	fprintf(fp, "\t\t</g>\n\t</g>\t</g>\n");
}

static const char svgnamespace_str[] =
	" xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\n"
	" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
	" xmlns:svg=\"http://www.w3.org/2000/svg\"\n"
	" xmlns=\"http://www.w3.org/2000/svg\"\n"
	;

static void write_svg(FILE *fp, const char *fontnname)
{
	unsigned i;

	fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
	fprintf(fp, "<svg\n%s width=\"%d\" height=\"%d\">\n", svgnamespace_str, 2*(chsw*(gbbox.w+1)+4), 2*(((nglyphs+(chsw-1))/chsw)*(gbbox.h+6)+4+12));
	for(i = 0; i < NELEM(license_strings); i++) {
		fprintf(fp, "<!-- %s -->\n", license_strings[i]);
	}
	fprintf(fp, "<g transform=\"scale(2,2) translate(2,19)\">\n");
	fprintf(fp, "<text x=\"0\" y=\"-10\" font-family=\"sans\" font-size=\"7\" fill=\"black\">%s</text>\n", fontnname);
	for(i = 0; i < nglyphs; i++) {
		svg_glyph(fp, glyphs[i], (i%chsw)*(gbbox.w+1), (i/chsw)*(gbbox.h+6));
	}
	fprintf(fp, "</g>\n</svg>\n");
}

static void c_strokes(FILE *fp, glyph_t *g)
{
	unsigned j, k;
	for(j = 0; j < g->nstrokes; j++) {
		if(g->strokes[j]->ncoords > 0) {
			int x = g->strokes[j]->coords[0].x;
			int y = g->strokes[j]->coords[0].y;
			fprintf(fp, "static const glyph_stroke_t stroke_%d_%u[%d] = {{%d,%d}", g->unicode, j, g->strokes[j]->ncoords, x, y);
			for(k = 1; k < g->strokes[j]->ncoords; k++) {
				x = g->strokes[j]->coords[k].x;
				y = g->strokes[j]->coords[k].y;
				fprintf(fp, ",{%d,%d}", x, y);
			}
			fprintf(fp, "};\n");
		}
	}
	if(g->nstrokes > 0) {
		fprintf(fp, "static const glyph_stroke_t *strokes_%d[%d] = {", g->unicode, g->nstrokes);
		for(j = 0; j < g->nstrokes; j++) {
			fprintf(fp, "stroke_%d_%u%s", g->unicode, j, j < g->nstrokes-1 ? ", " : "");
		}
		fprintf(fp, "};\n");
		fprintf(fp, "static const uint8_t ncoords_%d[%d] = {", g->unicode, g->nstrokes);
		for(j = 0; j < g->nstrokes; j++) {
			fprintf(fp, "%u%s", g->strokes[j]->ncoords, j < g->nstrokes-1 ? ", " : "");
		}
		fprintf(fp, "};\n");
	}
}


static const char chdr[] =
	"#include <stdint.h>\n"
	"\n"
	"typedef struct __glyph_stroke_t {\n"
	"	int8_t	x, y;\n"
	"} glyph_stroke_t;\n"
	"\n"
	"typedef struct __glyph_data_t {\n"
	"	uint32_t		unicode;\n"
	"	int8_t			bbl, bbb, bbr, bbt;\n"
	"	int8_t			left, right;\n"
	"	uint8_t			reserved;\n"
	"	uint8_t			nstrokes;\n"
	"	const glyph_stroke_t	**strokes;\n"
	"	const uint8_t		*ncoords;\n"
	"} glyph_data_t;\n"
	"\n"
	"typedef struct __font_data_t {\n"
	"	const char		*name;\n"
	"	int			height;\n"
	"	unsigned		nglyphs;\n"
	"	const glyph_data_t	*glyphs;\n"
	"} font_data_t;\n"
	"\n"
	;

static int sortglyphs(const void *l, const void *r)
{
	return (*(const glyph_t **)l)->unicode - (*(const glyph_t **)r)->unicode;
}

static int findglyph(const void *l, const void *r)
{
	return *(int *)l - (*(const glyph_t **)r)->unicode;
}

static void write_c(FILE *fp, const char *fontnname, const char *fontcname)
{
	unsigned i;
	int key = 'X';
	int h;
	glyph_t **g;

	fprintf(fp, "/*\n");
	for(i = 0; i < NELEM(license_strings); i++) {
		fprintf(fp, " * %s\n", license_strings[i]);
	}
	fprintf(fp, " */\n");

	// Write file header
	fprintf(fp, "%s", chdr);

	// Output all the strokes
	for(i = 0; i < nglyphs; i++) {
		c_strokes(fp, glyphs[i]);
	}

	qsort(glyphs, nglyphs, sizeof(glyphs[0]), sortglyphs);

	// Output all the glyphs in a sorted array
	fprintf(fp, "static const glyph_data_t glyph_data[%u] = {\n", nglyphs);
	for(i = 0; i < nglyphs; i++) {
		glyph_t *g = glyphs[i];
		fprintf(fp, "\t{ 0x%08x, ", g->unicode);
		fprintf(fp, "%d, %d, %d, %d, ", g->cbb.l, g->cbb.b, g->cbb.r, g->cbb.t);
		fprintf(fp, "%d, %d, ", g->left, g->right);
		fprintf(fp, "0, %u, ", g->nstrokes);
		if(g->nstrokes)
			fprintf(fp, "strokes_%d, ncoords_%d", g->unicode, g->unicode);
		else
			fprintf(fp, "(const glyph_stroke_t **)0, (const uint8_t *)0");
		fprintf(fp, " }%s", i < nglyphs-1 ? ",\n" : "");
	}
	fprintf(fp, "\n};\n");

	g = (glyph_t **)bsearch(&key, glyphs, nglyphs, sizeof(*glyphs), findglyph);

	if(!g) {
		fprintf(stderr, "Character 'X' not defined in set. Cannot determine height, setting to 21\n");
		h = 21;
	} else
		h = (*g)->cbb.t;

	// Output font description
	fprintf(fp, "const font_data_t %s = {\n", fontcname);
	fprintf(fp, "\t\"%s\",\n", fontnname);
	fprintf(fp, "\t%d,\n", h);
	fprintf(fp, "\t%u,\n", nglyphs);
	fprintf(fp, "\tglyph_data\n");
	fprintf(fp, "};\n");
}

const char usagestr[] =
	"Usage: gcmcfont [options] <inputfont>\n"
	"Options:\n"
	"  -h        This message\n"
	"  -c name   Font structure name; should be a valid C-identifier\n"
	"  -n name   Font readable name\n"
	"  -o fname  Output to 'fname'\n"
	"  -r        Show rapids in SVG\n"
	"  -s        Write SVG data (default is C)\n"
	"  -V        Print version and exit\n"
	"  -x        Show intermediate points in SVG\n"
	"  -w num    Set width of SVG display in chars (1...256)\n"
	;

int main(int argc, char *argv[])
{
	int optc;
	int lose = 0;
	char *outfile = NULL;
	FILE *ofp = stdout;
	int svg = 0;
	char *fontnname = "Gcmc Generated Vector Font, Please Rename This";
	char *fontcname = NULL;

	while(EOF != (optc = getopt(argc, argv, "hc:n:o:rsVw:x"))) {
		switch(optc) {
		case 'V':
			printf("Gcmc vector font converter version " VERSION "\n");
			return 0;

		case 'h':
			printf("%s", usagestr);
			return 0;

		case 'c':
			fontcname = strdup(optarg);
			break;

		case 'n':
			fontnname = strdup(optarg);
			break;

		case 'r':
			cl_rapid = 1;
			break;

		case 's':
			svg = 1;
			break;

		case 'o':
			outfile = strdup(optarg);
			break;

		case 'w':
			chsw = strtol(optarg, NULL, 0);
			if(chsw <= 0 || chsw > 256) {
				fprintf(stderr, "Character width must be between 1 and 256\n");
				lose++;
			}

		case 'x':
			cl_intermediate = 1;
			break;

		default:
			lose++;
			break;
		}
	}

	if(!fontnname) {
		fprintf(stderr, "Font (readable) name error -n option (NULL)\n");
		lose++;
	}
	if(!svg && !fontcname) {
		fprintf(stderr, "Font (c-ident) name must be set with -c option\n");
		lose++;
	}

	if(optind >= argc) {
		filename = "<stdin>";
		yyin = stdin;
	} else {
		filename = argv[optind];
		yyin = fopen(argv[optind], "r");
		if(!yyin) {
			perror(argv[optind]);
			lose++;
		}
	}

	if(lose)
		return 1;

	if(yyparse())
		return 1;

	if(outfile) {
		ofp = fopen(outfile, "w");
		if(!ofp) {
			perror(outfile);
			return 1;
		}
	}

	if(svg)
		write_svg(ofp, fontnname);
	else
		write_c(ofp, fontnname, fontcname);

	return 0;
}
