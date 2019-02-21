/*
 * This is a generated file, please DO NOT EDIT
 * 
 * The original data is derived from the Hershey fonts, which comes with the
 * following license:
 * 
 * USE RESTRICTION:
 * This distribution of the Hershey Fonts may be used by anyone for any purpose,
 * commercial or otherwise, providing that:
 * 1. The following acknowledgements must be distributed with the font data:
 *    - The Hershey Fonts were originally created by Dr. A. V. Hershey while
 *      working at the U. S. National Bureau of Standards.
 *    - The format of the Font data in this distribution was originally created by
 *      James Hurt
 *      Cognition, Inc.
 *      900 Technology Park Drive
 *      Billerica, MA 01821
 *      (mit-eddie!ci-dandelion!hurt)
 * 2. The font data in this distribution may be converted into any other format
 *    *EXCEPT* the format distributed by the U.S. NTIS (which organization holds
 *    the rights to the distribution and use of the font data in that particular
 *    format). Not that anybody would really *want* to use their format... each
 *    point is described in eight bytes as "xxx yyy:", where xxx and yyy are the
 *    coordinate values as ASCII numbers.
 * 
 * 
 * 
 * All modifications and extensions to the fonts and font-data are distruted under
 * the Creative Commons Attribution 4.0 International license (CC-BY-4.0,
 * see: http://creativecommons.org/licenses/by/4.0/). The modified format and font
 * data ((c) 2015) are provided by Bertho Stultiens (gcmc@vagrearg.org).
 * 
 * Modifications include:
 * - rename files for better understanding
 * - put all single- and multi-stroke font-data into files to have all glyphs of
 *   the same family in one file
 * - integrate greek, cyrillic and symbols into one font file
 * - assign unicode codepoints to the glyphs
 * - reformat the data to be more readable and useful
 * - realign all glyphs onto the baseline and the coordinates where right and up
 *   are positive
 * - add accented characters
 * 
 */
#include <stdint.h>

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
	const uint8_t		*ncoords;
} glyph_data_t;

typedef struct __font_data_t {
	const char		*name;
	int			height;
	unsigned		nglyphs;
	const glyph_data_t	*glyphs;
} font_data_t;

static const glyph_stroke_t stroke_33_0[3] = {{6,21},{5,20},{3,8}};
static const glyph_stroke_t stroke_33_1[2] = {{6,20},{3,8}};
static const glyph_stroke_t stroke_33_2[3] = {{6,21},{7,20},{3,8}};
static const glyph_stroke_t stroke_33_3[5] = {{1,2},{0,1},{1,0},{2,1},{1,2}};
static const glyph_stroke_t *strokes_33[4] = {stroke_33_0, stroke_33_1, stroke_33_2, stroke_33_3};
static const uint8_t ncoords_33[4] = {3, 2, 3, 5};
static const glyph_stroke_t stroke_34_0[2] = {{2,21},{0,14}};
static const glyph_stroke_t stroke_34_1[2] = {{3,21},{0,14}};
static const glyph_stroke_t stroke_34_2[2] = {{11,21},{9,14}};
static const glyph_stroke_t stroke_34_3[2] = {{12,21},{9,14}};
static const glyph_stroke_t *strokes_34[4] = {stroke_34_0, stroke_34_1, stroke_34_2, stroke_34_3};
static const uint8_t ncoords_34[4] = {2, 2, 2, 2};
static const glyph_stroke_t stroke_35_0[2] = {{8,25},{1,-7}};
static const glyph_stroke_t stroke_35_1[2] = {{14,25},{7,-7}};
static const glyph_stroke_t stroke_35_2[2] = {{1,12},{15,12}};
static const glyph_stroke_t stroke_35_3[2] = {{0,6},{14,6}};
static const glyph_stroke_t *strokes_35[4] = {stroke_35_0, stroke_35_1, stroke_35_2, stroke_35_3};
static const uint8_t ncoords_35[4] = {2, 2, 2, 2};
static const glyph_stroke_t stroke_36_0[2] = {{10,25},{2,-4}};
static const glyph_stroke_t stroke_36_1[2] = {{15,25},{7,-4}};
static const glyph_stroke_t stroke_36_2[16] = {{16,17},{15,16},{16,15},{17,16},{17,17},{16,19},{15,20},{12,21},{8,21},{5,20},{3,18},{3,16},{4,14},{5,13},{12,9},{14,7}};
static const glyph_stroke_t stroke_36_3[17] = {{3,16},{5,14},{12,10},{13,9},{14,7},{14,4},{13,2},{12,1},{9,0},{5,0},{2,1},{1,2},{0,4},{0,5},{1,6},{2,5},{1,4}};
static const glyph_stroke_t *strokes_36[4] = {stroke_36_0, stroke_36_1, stroke_36_2, stroke_36_3};
static const uint8_t ncoords_36[4] = {2, 2, 16, 17};
static const glyph_stroke_t stroke_37_0[2] = {{18,21},{0,0}};
static const glyph_stroke_t stroke_37_1[16] = {{5,21},{7,19},{7,17},{6,15},{4,14},{2,14},{0,16},{0,18},{1,20},{3,21},{5,21},{7,20},{10,19},{13,19},{16,20},{18,21}};
static const glyph_stroke_t stroke_37_2[11] = {{14,7},{12,6},{11,4},{11,2},{13,0},{15,0},{17,1},{18,3},{18,5},{16,7},{14,7}};
static const glyph_stroke_t *strokes_37[3] = {stroke_37_0, stroke_37_1, stroke_37_2};
static const uint8_t ncoords_37[3] = {2, 16, 11};
static const glyph_stroke_t stroke_38_0[37] = {{21,13},{20,12},{21,11},{22,12},{22,13},{21,14},{20,14},{18,13},{16,11},{11,3},{9,1},{7,0},{4,0},{1,1},{0,3},{0,5},{1,7},{2,8},{4,9},{9,11},{11,12},{13,14},{14,16},{14,18},{13,20},{11,21},{9,20},{8,18},{8,15},{9,9},{10,6},{12,3},{14,1},{16,0},{18,0},{19,2},{19,3}};
static const glyph_stroke_t stroke_38_1[7] = {{4,0},{2,1},{1,3},{1,5},{2,7},{3,8},{9,11}};
static const glyph_stroke_t stroke_38_2[8] = {{8,15},{9,10},{10,7},{12,4},{14,2},{16,1},{18,1},{19,2}};
static const glyph_stroke_t *strokes_38[3] = {stroke_38_0, stroke_38_1, stroke_38_2};
static const uint8_t ncoords_38[3] = {37, 7, 8};
static const glyph_stroke_t stroke_39_0[7] = {{2,19},{1,20},{2,21},{3,20},{3,19},{2,17},{0,15}};
static const glyph_stroke_t *strokes_39[1] = {stroke_39_0};
static const uint8_t ncoords_39[1] = {7};
static const glyph_stroke_t stroke_40_0[10] = {{12,25},{8,22},{5,19},{3,16},{1,12},{0,7},{0,3},{1,-2},{2,-5},{3,-7}};
static const glyph_stroke_t stroke_40_1[8] = {{8,22},{5,18},{3,14},{2,11},{1,6},{1,1},{2,-4},{3,-7}};
static const glyph_stroke_t *strokes_40[2] = {stroke_40_0, stroke_40_1};
static const uint8_t ncoords_40[2] = {10, 8};
static const glyph_stroke_t stroke_41_0[10] = {{9,25},{10,23},{11,20},{12,15},{12,11},{11,6},{9,2},{7,-1},{4,-4},{0,-7}};
static const glyph_stroke_t stroke_41_1[8] = {{9,25},{10,22},{11,17},{11,12},{10,7},{9,4},{7,0},{4,-4}};
static const glyph_stroke_t *strokes_41[2] = {stroke_41_0, stroke_41_1};
static const uint8_t ncoords_41[2] = {10, 8};
static const glyph_stroke_t stroke_42_0[2] = {{5,21},{5,9}};
static const glyph_stroke_t stroke_42_1[2] = {{0,18},{10,12}};
static const glyph_stroke_t stroke_42_2[2] = {{10,18},{0,12}};
static const glyph_stroke_t *strokes_42[3] = {stroke_42_0, stroke_42_1, stroke_42_2};
static const uint8_t ncoords_42[3] = {2, 2, 2};
static const glyph_stroke_t stroke_43_0[2] = {{9,18},{9,0}};
static const glyph_stroke_t stroke_43_1[2] = {{0,9},{18,9}};
static const glyph_stroke_t *strokes_43[2] = {stroke_43_0, stroke_43_1};
static const uint8_t ncoords_43[2] = {2, 2};
static const glyph_stroke_t stroke_44_0[7] = {{2,0},{1,1},{2,2},{3,1},{3,0},{2,-2},{0,-4}};
static const glyph_stroke_t *strokes_44[1] = {stroke_44_0};
static const uint8_t ncoords_44[1] = {7};
static const glyph_stroke_t stroke_45_0[2] = {{0,9},{18,9}};
static const glyph_stroke_t *strokes_45[1] = {stroke_45_0};
static const uint8_t ncoords_45[1] = {2};
static const glyph_stroke_t stroke_46_0[5] = {{1,2},{0,1},{1,0},{2,1},{1,2}};
static const glyph_stroke_t *strokes_46[1] = {stroke_46_0};
static const uint8_t ncoords_46[1] = {5};
static const glyph_stroke_t stroke_47_0[2] = {{26,25},{0,-7}};
static const glyph_stroke_t *strokes_47[1] = {stroke_47_0};
static const uint8_t ncoords_47[1] = {2};
static const glyph_stroke_t stroke_48_0[21] = {{9,21},{6,20},{4,18},{2,15},{1,12},{0,8},{0,5},{1,2},{2,1},{4,0},{6,0},{9,1},{11,3},{13,6},{14,9},{15,13},{15,16},{14,19},{13,20},{11,21},{9,21}};
static const glyph_stroke_t stroke_48_1[9] = {{9,21},{7,20},{5,18},{3,15},{2,12},{1,8},{1,5},{2,2},{4,0}};
static const glyph_stroke_t stroke_48_2[9] = {{6,0},{8,1},{10,3},{12,6},{13,9},{14,13},{14,16},{13,19},{11,21}};
static const glyph_stroke_t *strokes_48[3] = {stroke_48_0, stroke_48_1, stroke_48_2};
static const uint8_t ncoords_48[3] = {21, 9, 9};
static const glyph_stroke_t stroke_49_0[2] = {{6,17},{1,0}};
static const glyph_stroke_t stroke_49_1[2] = {{8,21},{2,0}};
static const glyph_stroke_t stroke_49_2[4] = {{8,21},{5,18},{2,16},{0,15}};
static const glyph_stroke_t stroke_49_3[3] = {{7,18},{3,16},{0,15}};
static const glyph_stroke_t *strokes_49[4] = {stroke_49_0, stroke_49_1, stroke_49_2, stroke_49_3};
static const uint8_t ncoords_49[4] = {2, 2, 4, 3};
static const glyph_stroke_t stroke_50_0[19] = {{6,17},{7,16},{6,15},{5,16},{5,17},{6,19},{7,20},{10,21},{13,21},{16,20},{17,18},{17,16},{16,14},{14,12},{11,10},{7,8},{4,6},{2,4},{0,0}};
static const glyph_stroke_t stroke_50_1[7] = {{13,21},{15,20},{16,18},{16,16},{15,14},{13,12},{7,8}};
static const glyph_stroke_t stroke_50_2[7] = {{1,2},{2,3},{4,3},{9,1},{12,1},{14,2},{15,4}};
static const glyph_stroke_t stroke_50_3[5] = {{4,3},{9,0},{12,0},{14,1},{15,4}};
static const glyph_stroke_t *strokes_50[4] = {stroke_50_0, stroke_50_1, stroke_50_2, stroke_50_3};
static const uint8_t ncoords_50[4] = {19, 7, 7, 5};
static const glyph_stroke_t stroke_51_0[15] = {{5,17},{6,16},{5,15},{4,16},{4,17},{5,19},{6,20},{9,21},{12,21},{15,20},{16,18},{16,16},{15,14},{12,12},{9,11}};
static const glyph_stroke_t stroke_51_1[6] = {{12,21},{14,20},{15,18},{15,16},{14,14},{12,12}};
static const glyph_stroke_t stroke_51_2[17] = {{7,11},{9,11},{12,10},{13,9},{14,7},{14,4},{13,2},{12,1},{9,0},{5,0},{2,1},{1,2},{0,4},{0,5},{1,6},{2,5},{1,4}};
static const glyph_stroke_t stroke_51_3[8] = {{9,11},{11,10},{12,9},{13,7},{13,4},{12,2},{11,1},{9,0}};
static const glyph_stroke_t *strokes_51[4] = {stroke_51_0, stroke_51_1, stroke_51_2, stroke_51_3};
static const uint8_t ncoords_51[4] = {15, 6, 17, 8};
static const glyph_stroke_t stroke_52_0[2] = {{14,20},{8,0}};
static const glyph_stroke_t stroke_52_1[2] = {{15,21},{9,0}};
static const glyph_stroke_t stroke_52_2[3] = {{15,21},{0,6},{16,6}};
static const glyph_stroke_t *strokes_52[3] = {stroke_52_0, stroke_52_1, stroke_52_2};
static const uint8_t ncoords_52[3] = {2, 2, 3};
static const glyph_stroke_t stroke_53_0[2] = {{7,21},{2,11}};
static const glyph_stroke_t stroke_53_1[2] = {{7,21},{17,21}};
static const glyph_stroke_t stroke_53_2[3] = {{7,20},{12,20},{17,21}};
static const glyph_stroke_t stroke_53_3[19] = {{2,11},{3,12},{6,13},{9,13},{12,12},{13,11},{14,9},{14,6},{13,3},{11,1},{8,0},{5,0},{2,1},{1,2},{0,4},{0,5},{1,6},{2,5},{1,4}};
static const glyph_stroke_t stroke_53_4[8] = {{9,13},{11,12},{12,11},{13,9},{13,6},{12,3},{10,1},{8,0}};
static const glyph_stroke_t *strokes_53[5] = {stroke_53_0, stroke_53_1, stroke_53_2, stroke_53_3, stroke_53_4};
static const uint8_t ncoords_53[5] = {2, 2, 3, 19, 8};
static const glyph_stroke_t stroke_54_0[29] = {{14,18},{13,17},{14,16},{15,17},{15,18},{14,20},{12,21},{9,21},{6,20},{4,18},{2,15},{1,12},{0,8},{0,4},{1,2},{2,1},{4,0},{7,0},{10,1},{12,3},{13,5},{13,8},{12,10},{11,11},{9,12},{6,12},{4,11},{2,9},{1,7}};
static const glyph_stroke_t stroke_54_1[8] = {{9,21},{7,20},{5,18},{3,15},{2,12},{1,8},{1,3},{2,1}};
static const glyph_stroke_t stroke_54_2[6] = {{7,0},{9,1},{11,3},{12,5},{12,9},{11,11}};
static const glyph_stroke_t *strokes_54[3] = {stroke_54_0, stroke_54_1, stroke_54_2};
static const uint8_t ncoords_54[3] = {29, 8, 6};
static const glyph_stroke_t stroke_55_0[2] = {{2,21},{0,15}};
static const glyph_stroke_t stroke_55_1[7] = {{15,21},{14,18},{12,15},{7,9},{5,6},{4,4},{3,0}};
static const glyph_stroke_t stroke_55_2[5] = {{12,15},{6,9},{4,6},{3,4},{2,0}};
static const glyph_stroke_t stroke_55_3[4] = {{1,18},{4,21},{6,21},{11,18}};
static const glyph_stroke_t stroke_55_4[7] = {{2,19},{4,20},{6,20},{11,18},{13,18},{14,19},{15,21}};
static const glyph_stroke_t *strokes_55[5] = {stroke_55_0, stroke_55_1, stroke_55_2, stroke_55_3, stroke_55_4};
static const uint8_t ncoords_55[5] = {2, 7, 5, 4, 7};
static const glyph_stroke_t stroke_56_0[15] = {{9,21},{6,20},{5,19},{4,17},{4,14},{5,12},{7,11},{10,11},{14,12},{15,13},{16,15},{16,18},{15,20},{12,21},{9,21}};
static const glyph_stroke_t stroke_56_1[7] = {{9,21},{7,20},{6,19},{5,17},{5,14},{6,12},{7,11}};
static const glyph_stroke_t stroke_56_2[7] = {{10,11},{13,12},{14,13},{15,15},{15,18},{14,20},{12,21}};
static const glyph_stroke_t stroke_56_3[15] = {{7,11},{3,10},{1,8},{0,6},{0,3},{1,1},{4,0},{8,0},{12,1},{13,2},{14,4},{14,7},{13,9},{12,10},{10,11}};
static const glyph_stroke_t stroke_56_4[7] = {{7,11},{4,10},{2,8},{1,6},{1,3},{2,1},{4,0}};
static const glyph_stroke_t stroke_56_5[6] = {{8,0},{11,1},{12,2},{13,4},{13,8},{12,10}};
static const glyph_stroke_t *strokes_56[6] = {stroke_56_0, stroke_56_1, stroke_56_2, stroke_56_3, stroke_56_4, stroke_56_5};
static const uint8_t ncoords_56[6] = {15, 7, 7, 15, 7, 6};
static const glyph_stroke_t stroke_57_0[29] = {{14,14},{13,12},{11,10},{9,9},{6,9},{4,10},{3,11},{2,13},{2,16},{3,18},{5,20},{8,21},{11,21},{13,20},{14,19},{15,17},{15,13},{14,9},{13,6},{11,3},{9,1},{6,0},{3,0},{1,1},{0,3},{0,4},{1,5},{2,4},{1,3}};
static const glyph_stroke_t stroke_57_1[6] = {{4,10},{3,12},{3,16},{4,18},{6,20},{8,21}};
static const glyph_stroke_t stroke_57_2[8] = {{13,20},{14,18},{14,13},{13,9},{12,6},{10,3},{8,1},{6,0}};
static const glyph_stroke_t *strokes_57[3] = {stroke_57_0, stroke_57_1, stroke_57_2};
static const uint8_t ncoords_57[3] = {29, 6, 8};
static const glyph_stroke_t stroke_58_0[5] = {{4,14},{3,13},{4,12},{5,13},{4,14}};
static const glyph_stroke_t stroke_58_1[4] = {{1,2},{0,1},{1,0},{2,1}};
static const glyph_stroke_t *strokes_58[2] = {stroke_58_0, stroke_58_1};
static const uint8_t ncoords_58[2] = {5, 4};
static const glyph_stroke_t stroke_59_0[5] = {{5,14},{4,13},{5,12},{6,13},{5,14}};
static const glyph_stroke_t stroke_59_1[7] = {{2,0},{1,1},{2,2},{3,1},{3,0},{2,-2},{0,-4}};
static const glyph_stroke_t *strokes_59[2] = {stroke_59_0, stroke_59_1};
static const uint8_t ncoords_59[2] = {5, 7};
static const glyph_stroke_t stroke_60_0[3] = {{16,18},{0,9},{16,0}};
static const glyph_stroke_t *strokes_60[1] = {stroke_60_0};
static const uint8_t ncoords_60[1] = {3};
static const glyph_stroke_t stroke_61_0[2] = {{0,12},{18,12}};
static const glyph_stroke_t stroke_61_1[2] = {{0,6},{18,6}};
static const glyph_stroke_t *strokes_61[2] = {stroke_61_0, stroke_61_1};
static const uint8_t ncoords_61[2] = {2, 2};
static const glyph_stroke_t stroke_62_0[3] = {{0,18},{16,9},{0,0}};
static const glyph_stroke_t *strokes_62[1] = {stroke_62_0};
static const uint8_t ncoords_62[1] = {3};
static const glyph_stroke_t stroke_63_0[19] = {{1,17},{2,16},{1,15},{0,16},{0,17},{1,19},{2,20},{5,21},{9,21},{12,20},{13,18},{13,16},{12,14},{11,13},{5,11},{3,10},{3,8},{4,7},{6,7}};
static const glyph_stroke_t stroke_63_1[7] = {{9,21},{11,20},{12,18},{12,16},{11,14},{10,13},{8,12}};
static const glyph_stroke_t stroke_63_2[5] = {{2,2},{1,1},{2,0},{3,1},{2,2}};
static const glyph_stroke_t *strokes_63[3] = {stroke_63_0, stroke_63_1, stroke_63_2};
static const uint8_t ncoords_63[3] = {19, 7, 5};
static const glyph_stroke_t stroke_64_0[13] = {{15,13},{14,15},{12,16},{9,16},{7,15},{6,14},{5,11},{5,8},{6,6},{8,5},{11,5},{13,6},{14,8}};
static const glyph_stroke_t stroke_64_1[6] = {{9,16},{7,14},{6,11},{6,8},{7,6},{8,5}};
static const glyph_stroke_t stroke_64_2[29] = {{15,16},{14,8},{14,6},{16,5},{18,5},{20,7},{21,10},{21,12},{20,15},{19,17},{17,19},{15,20},{12,21},{9,21},{6,20},{4,19},{2,17},{1,15},{0,12},{0,9},{1,6},{2,4},{4,2},{6,1},{9,0},{12,0},{15,1},{17,2},{18,3}};
static const glyph_stroke_t stroke_64_3[4] = {{16,16},{15,8},{15,6},{16,5}};
static const glyph_stroke_t *strokes_64[4] = {stroke_64_0, stroke_64_1, stroke_64_2, stroke_64_3};
static const uint8_t ncoords_64[4] = {13, 6, 29, 4};
static const glyph_stroke_t stroke_65_0[19] = {{0,0},{2,1},{5,4},{8,8},{12,15},{15,21},{15,0},{14,3},{12,6},{10,8},{7,10},{5,10},{4,9},{4,7},{5,5},{7,3},{10,1},{13,0},{18,0}};
static const glyph_stroke_t *strokes_65[1] = {stroke_65_0};
static const uint8_t ncoords_65[1] = {19};
static const glyph_stroke_t stroke_66_0[27] = {{10,19},{11,18},{11,15},{10,11},{9,8},{8,6},{6,3},{4,1},{2,0},{1,0},{0,1},{0,4},{1,9},{2,12},{3,14},{5,17},{7,19},{9,20},{12,21},{15,21},{17,20},{18,18},{18,16},{17,14},{16,13},{14,12},{11,11}};
static const glyph_stroke_t stroke_66_1[12] = {{10,11},{11,11},{14,10},{15,9},{16,7},{16,4},{15,2},{14,1},{12,0},{9,0},{7,1},{6,3}};
static const glyph_stroke_t *strokes_66[2] = {stroke_66_0, stroke_66_1};
static const uint8_t ncoords_66[2] = {27, 12};
static const glyph_stroke_t stroke_67_0[23] = {{9,15},{9,14},{10,13},{12,13},{14,14},{15,16},{15,18},{14,20},{12,21},{9,21},{6,20},{4,18},{2,15},{1,13},{0,9},{0,5},{1,2},{2,1},{4,0},{6,0},{9,1},{11,3},{12,5}};
static const glyph_stroke_t *strokes_67[1] = {stroke_67_0};
static const uint8_t ncoords_67[1] = {23};
static const glyph_stroke_t stroke_68_0[34] = {{14,21},{12,20},{11,18},{10,14},{9,8},{8,5},{7,3},{5,1},{3,0},{1,0},{0,1},{0,3},{1,4},{3,4},{5,3},{7,1},{10,0},{13,0},{16,1},{18,3},{20,7},{21,12},{21,16},{20,19},{19,20},{17,21},{14,21},{12,19},{12,17},{13,14},{15,11},{17,9},{20,7},{22,6}};
static const glyph_stroke_t *strokes_68[1] = {stroke_68_0};
static const uint8_t ncoords_68[1] = {34};
static const glyph_stroke_t stroke_69_0[27] = {{11,17},{11,16},{12,15},{14,15},{15,16},{15,18},{14,20},{11,21},{7,21},{4,20},{3,18},{3,15},{4,13},{5,12},{8,11},{5,11},{2,10},{1,9},{0,7},{0,4},{1,2},{2,1},{5,0},{8,0},{11,1},{13,3},{14,5}};
static const glyph_stroke_t *strokes_69[1] = {stroke_69_0};
static const uint8_t ncoords_69[1] = {27};
static const glyph_stroke_t stroke_70_0[10] = {{9,15},{7,15},{5,16},{4,18},{5,20},{8,21},{11,21},{15,20},{18,20},{20,21}};
static const glyph_stroke_t stroke_70_1[13] = {{15,20},{13,13},{11,7},{9,3},{7,1},{5,0},{3,0},{1,1},{0,3},{0,5},{1,6},{3,6},{5,5}};
static const glyph_stroke_t stroke_70_2[2] = {{8,11},{17,11}};
static const glyph_stroke_t *strokes_70[3] = {stroke_70_0, stroke_70_1, stroke_70_2};
static const uint8_t ncoords_70[3] = {10, 13, 2};
static const glyph_stroke_t stroke_71_0[28] = {{0,0},{2,1},{6,5},{9,10},{10,13},{11,17},{11,20},{10,21},{9,21},{8,20},{7,18},{7,15},{8,13},{10,12},{14,12},{17,13},{18,14},{19,16},{19,10},{18,5},{17,3},{15,1},{12,0},{8,0},{5,1},{3,3},{2,5},{2,7}};
static const glyph_stroke_t *strokes_71[1] = {stroke_71_0};
static const uint8_t ncoords_71[1] = {28};
static const glyph_stroke_t stroke_72_0[17] = {{6,14},{4,15},{3,17},{3,18},{4,20},{6,21},{7,21},{9,20},{10,18},{10,16},{9,12},{7,6},{5,2},{3,0},{1,0},{0,1},{0,3}};
static const glyph_stroke_t stroke_72_1[19] = {{6,9},{15,12},{17,13},{20,15},{22,17},{23,19},{23,20},{22,21},{21,21},{19,19},{17,15},{15,9},{14,4},{14,1},{15,0},{16,0},{18,1},{19,2},{21,5}};
static const glyph_stroke_t *strokes_72[2] = {stroke_72_0, stroke_72_1};
static const uint8_t ncoords_72[2] = {17, 19};
static const glyph_stroke_t stroke_73_0[24] = {{13,5},{11,7},{9,10},{8,12},{7,15},{7,18},{8,20},{9,21},{11,21},{12,20},{13,18},{13,15},{12,10},{10,5},{9,3},{7,1},{5,0},{3,0},{1,1},{0,3},{0,5},{1,6},{3,6},{5,5}};
static const glyph_stroke_t *strokes_73[1] = {stroke_73_0};
static const uint8_t ncoords_73[1] = {24};
static const glyph_stroke_t stroke_74_0[24] = {{9,-3},{7,0},{5,5},{4,11},{4,17},{5,20},{7,21},{9,21},{10,20},{11,17},{11,14},{10,9},{7,0},{5,-6},{4,-9},{3,-11},{1,-12},{0,-11},{0,-9},{1,-6},{3,-3},{5,-1},{8,1},{12,3}};
static const glyph_stroke_t *strokes_74[1] = {stroke_74_0};
static const uint8_t ncoords_74[1] = {24};
static const glyph_stroke_t stroke_75_0[17] = {{6,14},{4,15},{3,17},{3,18},{4,20},{6,21},{7,21},{9,20},{10,18},{10,16},{9,12},{7,6},{5,2},{3,0},{1,0},{0,1},{0,3}};
static const glyph_stroke_t stroke_75_1[10] = {{23,18},{23,20},{22,21},{21,21},{19,20},{17,18},{15,15},{13,13},{11,12},{9,12}};
static const glyph_stroke_t stroke_75_2[9] = {{11,12},{12,10},{12,3},{13,1},{14,0},{15,0},{17,1},{18,2},{20,5}};
static const glyph_stroke_t *strokes_75[3] = {stroke_75_0, stroke_75_1, stroke_75_2};
static const uint8_t ncoords_75[3] = {17, 10, 9};
static const glyph_stroke_t stroke_76_0[28] = {{4,9},{6,9},{10,10},{13,12},{15,14},{16,16},{16,19},{15,21},{13,21},{12,20},{11,18},{10,13},{9,8},{8,5},{7,3},{5,1},{3,0},{1,0},{0,1},{0,3},{1,4},{3,4},{5,3},{8,1},{11,0},{13,0},{16,1},{18,3}};
static const glyph_stroke_t *strokes_76[1] = {stroke_76_0};
static const uint8_t ncoords_76[1] = {28};
static const glyph_stroke_t stroke_77_0[13] = {{3,14},{1,15},{0,17},{0,18},{1,20},{3,21},{4,21},{6,20},{7,18},{7,16},{6,11},{5,7},{3,0}};
static const glyph_stroke_t stroke_77_1[12] = {{5,7},{8,15},{10,19},{11,20},{13,21},{14,21},{16,20},{17,18},{17,16},{16,11},{15,7},{13,0}};
static const glyph_stroke_t stroke_77_2[17] = {{15,7},{18,15},{20,19},{21,20},{23,21},{24,21},{26,20},{27,18},{27,16},{26,11},{24,4},{24,1},{25,0},{26,0},{28,1},{29,2},{31,5}};
static const glyph_stroke_t *strokes_77[3] = {stroke_77_0, stroke_77_1, stroke_77_2};
static const uint8_t ncoords_77[3] = {13, 12, 17};
static const glyph_stroke_t stroke_78_0[13] = {{3,14},{1,15},{0,17},{0,18},{1,20},{3,21},{4,21},{6,20},{7,18},{7,16},{6,11},{5,7},{3,0}};
static const glyph_stroke_t stroke_78_1[17] = {{5,7},{8,15},{10,19},{11,20},{13,21},{15,21},{17,20},{18,18},{18,16},{17,11},{15,4},{15,1},{16,0},{17,0},{19,1},{20,2},{22,5}};
static const glyph_stroke_t *strokes_78[2] = {stroke_78_0, stroke_78_1};
static const uint8_t ncoords_78[2] = {13, 17};
static const glyph_stroke_t stroke_79_0[28] = {{9,21},{6,20},{4,18},{2,15},{1,13},{0,9},{0,5},{1,2},{2,1},{4,0},{6,0},{9,1},{11,3},{13,6},{14,8},{15,12},{15,16},{14,19},{13,20},{11,21},{9,21},{7,19},{7,16},{8,13},{10,10},{12,8},{15,6},{17,5}};
static const glyph_stroke_t *strokes_79[1] = {stroke_79_0};
static const uint8_t ncoords_79[1] = {28};
static const glyph_stroke_t stroke_80_0[30] = {{10,19},{11,18},{11,15},{10,11},{9,8},{8,6},{6,3},{4,1},{2,0},{1,0},{0,1},{0,4},{1,9},{2,12},{3,14},{5,17},{7,19},{9,20},{12,21},{17,21},{19,20},{20,19},{21,17},{21,14},{20,12},{19,11},{17,10},{14,10},{12,11},{11,12}};
static const glyph_stroke_t *strokes_80[1] = {stroke_80_0};
static const uint8_t ncoords_80[1] = {30};
static const glyph_stroke_t stroke_81_0[31] = {{13,15},{12,13},{11,12},{9,11},{7,11},{6,13},{6,15},{7,18},{9,20},{12,21},{15,21},{17,20},{18,18},{18,14},{17,11},{15,8},{11,4},{8,2},{6,1},{3,0},{1,0},{0,1},{0,3},{1,4},{3,4},{5,3},{8,1},{11,0},{14,0},{17,1},{19,3}};
static const glyph_stroke_t *strokes_81[1] = {stroke_81_0};
static const uint8_t ncoords_81[1] = {31};
static const glyph_stroke_t stroke_82_0[37] = {{10,19},{11,18},{11,15},{10,11},{9,8},{8,6},{6,3},{4,1},{2,0},{1,0},{0,1},{0,4},{1,9},{2,12},{3,14},{5,17},{7,19},{9,20},{12,21},{16,21},{18,20},{19,19},{20,17},{20,14},{19,12},{18,11},{16,10},{13,10},{10,11},{11,10},{12,8},{12,3},{13,1},{15,0},{17,1},{18,2},{20,5}};
static const glyph_stroke_t *strokes_82[1] = {stroke_82_0};
static const uint8_t ncoords_82[1] = {37};
static const glyph_stroke_t stroke_83_0[27] = {{0,0},{2,1},{4,3},{7,7},{9,10},{11,14},{12,17},{12,20},{11,21},{10,21},{9,20},{8,18},{8,16},{9,14},{11,12},{14,10},{16,8},{17,6},{17,4},{16,2},{15,1},{12,0},{8,0},{5,1},{3,3},{2,5},{2,7}};
static const glyph_stroke_t *strokes_83[1] = {stroke_83_0};
static const uint8_t ncoords_83[1] = {27};
static const glyph_stroke_t stroke_84_0[10] = {{9,15},{7,15},{5,16},{4,18},{5,20},{8,21},{11,21},{15,20},{18,20},{20,21}};
static const glyph_stroke_t stroke_84_1[13] = {{15,20},{13,13},{11,7},{9,3},{7,1},{5,0},{3,0},{1,1},{0,3},{0,5},{1,6},{3,6},{5,5}};
static const glyph_stroke_t *strokes_84[2] = {stroke_84_0, stroke_84_1};
static const uint8_t ncoords_84[2] = {10, 13};
static const glyph_stroke_t stroke_85_0[22] = {{3,14},{1,15},{0,17},{0,18},{1,20},{3,21},{4,21},{6,20},{7,18},{7,16},{6,12},{5,9},{4,5},{4,3},{5,1},{7,0},{9,0},{11,1},{12,2},{14,6},{17,14},{19,21}};
static const glyph_stroke_t stroke_85_1[9] = {{17,14},{16,10},{15,4},{15,1},{16,0},{17,0},{19,1},{20,2},{22,5}};
static const glyph_stroke_t *strokes_85[2] = {stroke_85_0, stroke_85_1};
static const uint8_t ncoords_85[2] = {22, 9};
static const glyph_stroke_t stroke_86_0[31] = {{3,14},{1,15},{0,17},{0,18},{1,20},{3,21},{4,21},{6,20},{7,18},{7,16},{6,12},{5,9},{4,5},{4,2},{5,0},{7,0},{9,1},{12,4},{14,7},{16,11},{17,14},{18,18},{18,20},{17,21},{16,21},{15,20},{14,18},{14,16},{15,13},{17,11},{19,10}};
static const glyph_stroke_t *strokes_86[1] = {stroke_86_0};
static const uint8_t ncoords_86[1] = {31};
static const glyph_stroke_t stroke_87_0[11] = {{3,14},{1,15},{0,17},{0,18},{1,20},{3,21},{4,21},{6,20},{7,18},{7,15},{6,0}};
static const glyph_stroke_t stroke_87_1[2] = {{16,21},{6,0}};
static const glyph_stroke_t stroke_87_2[2] = {{16,21},{14,0}};
static const glyph_stroke_t stroke_87_3[6] = {{28,21},{26,20},{23,17},{20,13},{17,7},{14,0}};
static const glyph_stroke_t *strokes_87[4] = {stroke_87_0, stroke_87_1, stroke_87_2, stroke_87_3};
static const uint8_t ncoords_87[4] = {11, 2, 2, 6};
static const glyph_stroke_t stroke_88_0[20] = {{7,15},{5,15},{4,16},{4,18},{5,20},{7,21},{9,21},{11,20},{12,18},{12,15},{10,6},{10,3},{11,1},{13,0},{15,0},{17,1},{18,3},{18,5},{17,6},{15,6}};
static const glyph_stroke_t stroke_88_1[14] = {{22,18},{22,20},{21,21},{19,21},{17,20},{15,18},{13,15},{9,6},{7,3},{5,1},{3,0},{1,0},{0,1},{0,3}};
static const glyph_stroke_t *strokes_88[2] = {stroke_88_0, stroke_88_1};
static const uint8_t ncoords_88[2] = {20, 14};
static const glyph_stroke_t stroke_89_0[22] = {{3,14},{1,15},{0,17},{0,18},{1,20},{3,21},{4,21},{6,20},{7,18},{7,16},{6,12},{5,9},{4,5},{4,3},{5,1},{6,0},{8,0},{10,1},{12,3},{14,6},{15,8},{17,14}};
static const glyph_stroke_t stroke_89_1[14] = {{19,21},{17,14},{14,4},{12,-2},{10,-7},{8,-11},{6,-12},{5,-11},{5,-9},{6,-6},{8,-3},{11,0},{14,2},{19,5}};
static const glyph_stroke_t *strokes_89[2] = {stroke_89_0, stroke_89_1};
static const uint8_t ncoords_89[2] = {22, 14};
static const glyph_stroke_t stroke_90_0[39] = {{11,15},{10,13},{9,12},{7,11},{5,11},{4,13},{4,15},{5,18},{7,20},{10,21},{13,21},{15,20},{16,18},{16,14},{15,11},{13,7},{10,4},{6,1},{4,0},{1,0},{0,1},{0,3},{1,4},{4,4},{6,3},{7,2},{8,0},{8,-3},{7,-6},{6,-8},{4,-11},{2,-12},{1,-11},{1,-9},{2,-6},{4,-3},{7,0},{10,2},{16,5}};
static const glyph_stroke_t *strokes_90[1] = {stroke_90_0};
static const uint8_t ncoords_90[1] = {39};
static const glyph_stroke_t stroke_91_0[2] = {{0,25},{0,-7}};
static const glyph_stroke_t stroke_91_1[2] = {{1,25},{1,-7}};
static const glyph_stroke_t stroke_91_2[2] = {{0,25},{7,25}};
static const glyph_stroke_t stroke_91_3[2] = {{0,-7},{7,-7}};
static const glyph_stroke_t *strokes_91[4] = {stroke_91_0, stroke_91_1, stroke_91_2, stroke_91_3};
static const uint8_t ncoords_91[4] = {2, 2, 2, 2};
static const glyph_stroke_t stroke_92_0[2] = {{0,21},{14,-3}};
static const glyph_stroke_t *strokes_92[1] = {stroke_92_0};
static const uint8_t ncoords_92[1] = {2};
static const glyph_stroke_t stroke_93_0[2] = {{6,25},{6,-7}};
static const glyph_stroke_t stroke_93_1[2] = {{7,25},{7,-7}};
static const glyph_stroke_t stroke_93_2[2] = {{0,25},{7,25}};
static const glyph_stroke_t stroke_93_3[2] = {{0,-7},{7,-7}};
static const glyph_stroke_t *strokes_93[4] = {stroke_93_0, stroke_93_1, stroke_93_2, stroke_93_3};
static const uint8_t ncoords_93[4] = {2, 2, 2, 2};
static const glyph_stroke_t stroke_94_0[3] = {{3,15},{5,18},{7,15}};
static const glyph_stroke_t stroke_94_1[3] = {{0,12},{5,17},{10,12}};
static const glyph_stroke_t stroke_94_2[2] = {{5,17},{5,0}};
static const glyph_stroke_t *strokes_94[3] = {stroke_94_0, stroke_94_1, stroke_94_2};
static const uint8_t ncoords_94[3] = {3, 3, 2};
static const glyph_stroke_t stroke_95_0[2] = {{0,-2},{16,-2}};
static const glyph_stroke_t *strokes_95[1] = {stroke_95_0};
static const uint8_t ncoords_95[1] = {2};
static const glyph_stroke_t stroke_96_0[7] = {{3,21},{1,19},{0,17},{0,16},{1,15},{2,16},{1,17}};
static const glyph_stroke_t *strokes_96[1] = {stroke_96_0};
static const uint8_t ncoords_96[1] = {7};
static const glyph_stroke_t stroke_97_0[21] = {{9,6},{8,8},{6,9},{4,9},{2,8},{1,7},{0,5},{0,3},{1,1},{3,0},{5,0},{7,1},{8,3},{10,9},{9,4},{9,1},{10,0},{11,0},{13,1},{14,2},{16,5}};
static const glyph_stroke_t *strokes_97[1] = {stroke_97_0};
static const uint8_t ncoords_97[1] = {21};
static const glyph_stroke_t stroke_98_0[22] = {{0,5},{2,8},{5,13},{6,15},{7,18},{7,20},{6,21},{4,20},{3,18},{2,14},{1,7},{1,1},{2,0},{3,0},{5,1},{7,3},{8,6},{8,9},{9,5},{10,4},{12,4},{14,5}};
static const glyph_stroke_t *strokes_98[1] = {stroke_98_0};
static const uint8_t ncoords_98[1] = {22};
static const glyph_stroke_t stroke_99_0[13] = {{7,7},{7,8},{6,9},{4,9},{2,8},{1,7},{0,5},{0,3},{1,1},{3,0},{6,0},{9,2},{11,5}};
static const glyph_stroke_t *strokes_99[1] = {stroke_99_0};
static const uint8_t ncoords_99[1] = {13};
static const glyph_stroke_t stroke_100_0[14] = {{9,6},{8,8},{6,9},{4,9},{2,8},{1,7},{0,5},{0,3},{1,1},{3,0},{5,0},{7,1},{8,3},{14,21}};
static const glyph_stroke_t stroke_100_1[8] = {{10,9},{9,4},{9,1},{10,0},{11,0},{13,1},{14,2},{16,5}};
static const glyph_stroke_t *strokes_100[2] = {stroke_100_0, stroke_100_1};
static const uint8_t ncoords_100[2] = {14, 8};
static const glyph_stroke_t stroke_101_0[16] = {{1,2},{3,3},{4,4},{5,6},{5,8},{4,9},{3,9},{1,8},{0,6},{0,3},{1,1},{3,0},{5,0},{7,1},{8,2},{10,5}};
static const glyph_stroke_t *strokes_101[1] = {stroke_101_0};
static const uint8_t ncoords_101[1] = {16};
static const glyph_stroke_t stroke_102_0[23] = {{5,5},{9,10},{11,13},{12,15},{13,18},{13,20},{12,21},{10,20},{9,18},{7,10},{4,1},{1,-6},{0,-9},{0,-11},{1,-12},{3,-11},{4,-8},{5,1},{6,0},{8,0},{10,1},{11,2},{13,5}};
static const glyph_stroke_t *strokes_102[1] = {stroke_102_0};
static const uint8_t ncoords_102[1] = {23};
static const glyph_stroke_t stroke_103_0[13] = {{9,6},{8,8},{6,9},{4,9},{2,8},{1,7},{0,5},{0,3},{1,1},{3,0},{5,0},{7,1},{8,2}};
static const glyph_stroke_t stroke_103_1[13] = {{10,9},{8,2},{4,-9},{3,-11},{1,-12},{0,-11},{0,-9},{1,-6},{4,-3},{7,-1},{9,0},{12,2},{15,5}};
static const glyph_stroke_t *strokes_103[2] = {stroke_103_0, stroke_103_1};
static const uint8_t ncoords_103[2] = {13, 13};
static const glyph_stroke_t stroke_104_0[12] = {{0,5},{2,8},{5,13},{6,15},{7,18},{7,20},{6,21},{4,20},{3,18},{2,14},{1,8},{0,0}};
static const glyph_stroke_t stroke_104_1[15] = {{0,0},{1,3},{2,5},{4,8},{6,9},{8,9},{9,8},{9,6},{8,3},{8,1},{9,0},{10,0},{12,1},{13,2},{15,5}};
static const glyph_stroke_t *strokes_104[2] = {stroke_104_0, stroke_104_1};
static const uint8_t ncoords_104[2] = {12, 15};
static const glyph_stroke_t stroke_105_0[5] = {{3,14},{3,13},{4,13},{4,14},{3,14}};
static const glyph_stroke_t stroke_105_1[9] = {{0,5},{2,9},{0,3},{0,1},{1,0},{2,0},{4,1},{5,2},{7,5}};
static const glyph_stroke_t *strokes_105[2] = {stroke_105_0, stroke_105_1};
static const uint8_t ncoords_105[2] = {5, 9};
static const glyph_stroke_t stroke_106_0[5] = {{11,14},{11,13},{12,13},{12,14},{11,14}};
static const glyph_stroke_t stroke_106_1[13] = {{8,5},{10,9},{4,-9},{3,-11},{1,-12},{0,-11},{0,-9},{1,-6},{4,-3},{7,-1},{9,0},{12,2},{15,5}};
static const glyph_stroke_t *strokes_106[2] = {stroke_106_0, stroke_106_1};
static const uint8_t ncoords_106[2] = {5, 13};
static const glyph_stroke_t stroke_107_0[12] = {{0,5},{2,8},{5,13},{6,15},{7,18},{7,20},{6,21},{4,20},{3,18},{2,14},{1,8},{0,0}};
static const glyph_stroke_t stroke_107_1[10] = {{0,0},{1,3},{2,5},{4,8},{6,9},{8,9},{9,8},{9,6},{7,5},{4,5}};
static const glyph_stroke_t stroke_107_2[8] = {{4,5},{6,4},{7,1},{8,0},{9,0},{11,1},{12,2},{14,5}};
static const glyph_stroke_t *strokes_107[3] = {stroke_107_0, stroke_107_1, stroke_107_2};
static const uint8_t ncoords_107[3] = {12, 10, 8};
static const glyph_stroke_t stroke_108_0[17] = {{0,5},{2,8},{5,13},{6,15},{7,18},{7,20},{6,21},{4,20},{3,18},{2,14},{1,7},{1,1},{2,0},{3,0},{5,1},{6,2},{8,5}};
static const glyph_stroke_t *strokes_108[1] = {stroke_108_0};
static const uint8_t ncoords_108[1] = {17};
static const glyph_stroke_t stroke_109_0[7] = {{0,5},{2,8},{4,9},{5,8},{5,7},{4,3},{3,0}};
static const glyph_stroke_t stroke_109_1[9] = {{4,3},{5,5},{7,8},{9,9},{11,9},{12,8},{12,7},{11,3},{10,0}};
static const glyph_stroke_t stroke_109_2[14] = {{11,3},{12,5},{14,8},{16,9},{18,9},{19,8},{19,6},{18,3},{18,1},{19,0},{20,0},{22,1},{23,2},{25,5}};
static const glyph_stroke_t *strokes_109[3] = {stroke_109_0, stroke_109_1, stroke_109_2};
static const uint8_t ncoords_109[3] = {7, 9, 14};
static const glyph_stroke_t stroke_110_0[7] = {{0,5},{2,8},{4,9},{5,8},{5,7},{4,3},{3,0}};
static const glyph_stroke_t stroke_110_1[14] = {{4,3},{5,5},{7,8},{9,9},{11,9},{12,8},{12,6},{11,3},{11,1},{12,0},{13,0},{15,1},{16,2},{18,5}};
static const glyph_stroke_t *strokes_110[2] = {stroke_110_0, stroke_110_1};
static const uint8_t ncoords_110[2] = {7, 14};
static const glyph_stroke_t stroke_111_0[22] = {{6,9},{4,9},{2,8},{1,7},{0,5},{0,3},{1,1},{3,0},{5,0},{7,1},{8,2},{9,4},{9,6},{8,8},{6,9},{5,8},{5,6},{6,4},{8,3},{11,3},{13,4},{14,5}};
static const glyph_stroke_t *strokes_111[1] = {stroke_111_0};
static const uint8_t ncoords_111[1] = {22};
static const glyph_stroke_t stroke_112_0[5] = {{4,5},{6,8},{7,10},{6,6},{0,-12}};
static const glyph_stroke_t stroke_112_1[10] = {{6,6},{7,8},{9,9},{11,9},{13,8},{14,6},{14,4},{13,2},{12,1},{10,0}};
static const glyph_stroke_t stroke_112_2[6] = {{6,1},{8,0},{11,0},{14,1},{16,2},{19,5}};
static const glyph_stroke_t *strokes_112[3] = {stroke_112_0, stroke_112_1, stroke_112_2};
static const uint8_t ncoords_112[3] = {5, 10, 6};
static const glyph_stroke_t stroke_113_0[12] = {{9,6},{8,8},{6,9},{4,9},{2,8},{1,7},{0,5},{0,3},{1,1},{3,0},{5,0},{7,1}};
static const glyph_stroke_t stroke_113_1[13] = {{10,9},{9,6},{7,1},{4,-6},{3,-9},{3,-11},{4,-12},{6,-11},{7,-8},{7,-1},{9,0},{12,2},{15,5}};
static const glyph_stroke_t *strokes_113[2] = {stroke_113_0, stroke_113_1};
static const uint8_t ncoords_113[2] = {12, 13};
static const glyph_stroke_t stroke_114_0[14] = {{0,5},{2,8},{3,10},{3,8},{6,8},{7,7},{7,5},{6,2},{6,1},{7,0},{8,0},{10,1},{11,2},{13,5}};
static const glyph_stroke_t *strokes_114[1] = {stroke_114_0};
static const uint8_t ncoords_114[1] = {14};
static const glyph_stroke_t stroke_115_0[8] = {{0,5},{2,8},{3,10},{3,8},{5,5},{6,3},{6,1},{4,0}};
static const glyph_stroke_t stroke_115_1[6] = {{0,1},{2,0},{6,0},{8,1},{9,2},{11,5}};
static const glyph_stroke_t *strokes_115[2] = {stroke_115_0, stroke_115_1};
static const uint8_t ncoords_115[2] = {8, 6};
static const glyph_stroke_t stroke_116_0[3] = {{0,5},{2,8},{4,12}};
static const glyph_stroke_t stroke_116_1[8] = {{7,21},{1,3},{1,1},{2,0},{4,0},{6,1},{7,2},{9,5}};
static const glyph_stroke_t stroke_116_2[2] = {{1,13},{8,13}};
static const glyph_stroke_t *strokes_116[3] = {stroke_116_0, stroke_116_1, stroke_116_2};
static const uint8_t ncoords_116[3] = {3, 8, 2};
static const glyph_stroke_t stroke_117_0[9] = {{0,5},{2,9},{0,3},{0,1},{1,0},{3,0},{5,1},{7,3},{9,6}};
static const glyph_stroke_t stroke_117_1[8] = {{10,9},{8,3},{8,1},{9,0},{10,0},{12,1},{13,2},{15,5}};
static const glyph_stroke_t *strokes_117[2] = {stroke_117_0, stroke_117_1};
static const uint8_t ncoords_117[2] = {9, 8};
static const glyph_stroke_t stroke_118_0[10] = {{0,5},{2,9},{1,4},{1,1},{2,0},{3,0},{6,1},{8,3},{9,6},{9,9}};
static const glyph_stroke_t stroke_118_1[5] = {{9,9},{10,5},{11,4},{13,4},{15,5}};
static const glyph_stroke_t *strokes_118[2] = {stroke_118_0, stroke_118_1};
static const uint8_t ncoords_118[2] = {10, 5};
static const glyph_stroke_t stroke_119_0[8] = {{3,9},{1,7},{0,4},{0,2},{1,0},{3,0},{5,1},{7,3}};
static const glyph_stroke_t stroke_119_1[9] = {{9,9},{7,3},{7,1},{8,0},{10,0},{12,1},{14,3},{15,6},{15,9}};
static const glyph_stroke_t stroke_119_2[5] = {{15,9},{16,5},{17,4},{19,4},{21,5}};
static const glyph_stroke_t *strokes_119[3] = {stroke_119_0, stroke_119_1, stroke_119_2};
static const uint8_t ncoords_119[3] = {8, 9, 5};
static const glyph_stroke_t stroke_120_0[10] = {{0,5},{2,8},{4,9},{6,9},{7,8},{7,1},{8,0},{11,0},{14,2},{16,5}};
static const glyph_stroke_t stroke_120_1[8] = {{13,8},{12,9},{10,9},{9,8},{5,1},{4,0},{2,0},{1,1}};
static const glyph_stroke_t *strokes_120[2] = {stroke_120_0, stroke_120_1};
static const uint8_t ncoords_120[2] = {10, 8};
static const glyph_stroke_t stroke_121_0[9] = {{0,5},{2,9},{0,3},{0,1},{1,0},{3,0},{5,1},{7,3},{9,6}};
static const glyph_stroke_t stroke_121_1[12] = {{10,9},{4,-9},{3,-11},{1,-12},{0,-11},{0,-9},{1,-6},{4,-3},{7,-1},{9,0},{12,2},{15,5}};
static const glyph_stroke_t *strokes_121[2] = {stroke_121_0, stroke_121_1};
static const uint8_t ncoords_121[2] = {9, 12};
static const glyph_stroke_t stroke_122_0[22] = {{0,5},{2,8},{4,9},{6,9},{8,7},{8,5},{7,3},{5,1},{2,0},{4,-1},{5,-3},{5,-6},{4,-9},{3,-11},{1,-12},{0,-11},{0,-9},{1,-6},{4,-3},{7,-1},{11,2},{14,5}};
static const glyph_stroke_t *strokes_122[1] = {stroke_122_0};
static const uint8_t ncoords_122[1] = {22};
static const glyph_stroke_t stroke_123_0[10] = {{5,25},{3,24},{2,23},{1,21},{1,19},{2,17},{3,16},{4,14},{4,12},{2,10}};
static const glyph_stroke_t stroke_123_1[17] = {{3,24},{2,22},{2,20},{3,18},{4,17},{5,15},{5,13},{4,11},{0,9},{4,7},{5,5},{5,3},{4,1},{3,0},{2,-2},{2,-4},{3,-6}};
static const glyph_stroke_t stroke_123_2[10] = {{2,8},{4,6},{4,4},{3,2},{2,1},{1,-1},{1,-3},{2,-5},{3,-6},{5,-7}};
static const glyph_stroke_t *strokes_123[3] = {stroke_123_0, stroke_123_1, stroke_123_2};
static const uint8_t ncoords_123[3] = {10, 17, 10};
static const glyph_stroke_t stroke_124_0[2] = {{0,25},{0,-7}};
static const glyph_stroke_t *strokes_124[1] = {stroke_124_0};
static const uint8_t ncoords_124[1] = {2};
static const glyph_stroke_t stroke_125_0[10] = {{0,25},{2,24},{3,23},{4,21},{4,19},{3,17},{2,16},{1,14},{1,12},{3,10}};
static const glyph_stroke_t stroke_125_1[17] = {{2,24},{3,22},{3,20},{2,18},{1,17},{0,15},{0,13},{1,11},{5,9},{1,7},{0,5},{0,3},{1,1},{2,0},{3,-2},{3,-4},{2,-6}};
static const glyph_stroke_t stroke_125_2[10] = {{3,8},{1,6},{1,4},{2,2},{3,1},{4,-1},{4,-3},{3,-5},{2,-6},{0,-7}};
static const glyph_stroke_t *strokes_125[3] = {stroke_125_0, stroke_125_1, stroke_125_2};
static const uint8_t ncoords_125[3] = {10, 17, 10};
static const glyph_stroke_t stroke_126_0[11] = {{0,6},{0,8},{1,11},{3,12},{5,12},{7,11},{11,8},{13,7},{15,7},{17,8},{18,10}};
static const glyph_stroke_t stroke_126_1[11] = {{0,8},{1,10},{3,11},{5,11},{7,10},{11,7},{13,6},{15,6},{17,7},{18,10},{18,12}};
static const glyph_stroke_t *strokes_126[2] = {stroke_126_0, stroke_126_1};
static const uint8_t ncoords_126[2] = {11, 11};
static const glyph_stroke_t stroke_127_0[13] = {{3,21},{1,20},{0,18},{0,16},{1,14},{3,13},{5,13},{7,14},{8,16},{8,18},{7,20},{5,21},{3,21}};
static const glyph_stroke_t *strokes_127[1] = {stroke_127_0};
static const uint8_t ncoords_127[1] = {13};
static const glyph_data_t glyph_data[96] = {
	{ 0x00000020, 0, 0, 0, 0, -6, 6, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x00000021, 0, 0, 7, 21, -2, 9, 0, 4, strokes_33, ncoords_33 },
	{ 0x00000022, 0, 14, 12, 21, -5, 13, 0, 4, strokes_34, ncoords_34 },
	{ 0x00000023, 0, -7, 15, 25, -3, 18, 0, 4, strokes_35, ncoords_35 },
	{ 0x00000024, 0, -4, 17, 25, -2, 19, 0, 4, strokes_36, ncoords_36 },
	{ 0x00000025, 0, 0, 18, 21, -3, 21, 0, 3, strokes_37, ncoords_37 },
	{ 0x00000026, 0, 0, 22, 21, -2, 24, 0, 3, strokes_38, ncoords_38 },
	{ 0x00000027, 0, 15, 3, 21, -6, 5, 0, 1, strokes_39, ncoords_39 },
	{ 0x00000028, 0, -7, 12, 25, -3, 12, 0, 2, strokes_40, ncoords_40 },
	{ 0x00000029, 0, -7, 12, 25, 0, 15, 0, 2, strokes_41, ncoords_41 },
	{ 0x0000002a, 0, 9, 10, 21, -5, 12, 0, 3, strokes_42, ncoords_42 },
	{ 0x0000002b, 0, 0, 18, 18, -4, 22, 0, 2, strokes_43, ncoords_43 },
	{ 0x0000002c, 0, -4, 3, 2, -1, 10, 0, 1, strokes_44, ncoords_44 },
	{ 0x0000002d, 0, 9, 18, 9, -4, 22, 0, 1, strokes_45, ncoords_45 },
	{ 0x0000002e, 0, 0, 2, 2, -4, 6, 0, 1, strokes_46, ncoords_46 },
	{ 0x0000002f, 0, -7, 26, 25, 2, 24, 0, 1, strokes_47, ncoords_47 },
	{ 0x00000030, 0, 0, 15, 21, -3, 18, 0, 3, strokes_48, ncoords_48 },
	{ 0x00000031, 0, 0, 8, 21, -6, 15, 0, 4, strokes_49, ncoords_49 },
	{ 0x00000032, 0, 0, 17, 21, -1, 20, 0, 4, strokes_50, ncoords_50 },
	{ 0x00000033, 0, 0, 16, 21, -2, 19, 0, 4, strokes_51, ncoords_51 },
	{ 0x00000034, 0, 0, 16, 21, -2, 19, 0, 3, strokes_52, ncoords_52 },
	{ 0x00000035, 0, 0, 17, 21, -2, 19, 0, 5, strokes_53, ncoords_53 },
	{ 0x00000036, 0, 0, 15, 21, -3, 18, 0, 3, strokes_54, ncoords_54 },
	{ 0x00000037, 0, 0, 15, 21, -4, 17, 0, 5, strokes_55, ncoords_55 },
	{ 0x00000038, 0, 0, 16, 21, -2, 19, 0, 6, strokes_56, ncoords_56 },
	{ 0x00000039, 0, 0, 15, 21, -3, 18, 0, 3, strokes_57, ncoords_57 },
	{ 0x0000003a, 0, 0, 5, 14, -2, 9, 0, 2, strokes_58, ncoords_58 },
	{ 0x0000003b, 0, -4, 6, 14, -1, 10, 0, 2, strokes_59, ncoords_59 },
	{ 0x0000003c, 0, 0, 16, 18, -4, 20, 0, 1, strokes_60, ncoords_60 },
	{ 0x0000003d, 0, 6, 18, 12, -4, 22, 0, 2, strokes_61, ncoords_61 },
	{ 0x0000003e, 0, 0, 16, 18, -4, 20, 0, 1, strokes_62, ncoords_62 },
	{ 0x0000003f, 0, 0, 13, 21, -6, 15, 0, 3, strokes_63, ncoords_63 },
	{ 0x00000040, 0, 0, 21, 21, -3, 24, 0, 4, strokes_64, ncoords_64 },
	{ 0x00000041, 0, 0, 18, 21, 0, 20, 0, 1, strokes_65, ncoords_65 },
	{ 0x00000042, 0, 0, 18, 21, -3, 20, 0, 2, strokes_66, ncoords_66 },
	{ 0x00000043, 0, 0, 15, 21, -3, 17, 0, 1, strokes_67, ncoords_67 },
	{ 0x00000044, 0, 0, 22, 21, 1, 24, 0, 1, strokes_68, ncoords_68 },
	{ 0x00000045, 0, 0, 15, 21, -3, 17, 0, 1, strokes_69, ncoords_69 },
	{ 0x00000046, 0, 0, 20, 21, -1, 19, 0, 3, strokes_70, ncoords_70 },
	{ 0x00000047, 0, 0, 19, 21, 0, 23, 0, 1, strokes_71, ncoords_71 },
	{ 0x00000048, 0, 0, 23, 21, -1, 23, 0, 2, strokes_72, ncoords_72 },
	{ 0x00000049, 0, 0, 13, 21, -1, 16, 0, 1, strokes_73, ncoords_73 },
	{ 0x0000004a, 0, -12, 12, 21, -1, 14, 0, 1, strokes_74, ncoords_74 },
	{ 0x0000004b, 0, 0, 23, 21, -1, 23, 0, 3, strokes_75, ncoords_75 },
	{ 0x0000004c, 0, 0, 18, 21, 0, 19, 0, 1, strokes_76, ncoords_76 },
	{ 0x0000004d, 0, 0, 31, 21, -2, 31, 0, 3, strokes_77, ncoords_77 },
	{ 0x0000004e, 0, 0, 22, 21, -2, 22, 0, 2, strokes_78, ncoords_78 },
	{ 0x0000004f, 0, 0, 17, 21, -3, 18, 0, 1, strokes_79, ncoords_79 },
	{ 0x00000050, 0, 0, 21, 21, -3, 22, 0, 1, strokes_80, ncoords_80 },
	{ 0x00000051, 0, 0, 19, 21, 0, 22, 0, 1, strokes_81, ncoords_81 },
	{ 0x00000052, 0, 0, 20, 21, -3, 22, 0, 1, strokes_82, ncoords_82 },
	{ 0x00000053, 0, 0, 17, 21, 0, 20, 0, 1, strokes_83, ncoords_83 },
	{ 0x00000054, 0, 0, 20, 21, -1, 18, 0, 2, strokes_84, ncoords_84 },
	{ 0x00000055, 0, 0, 22, 21, -2, 22, 0, 2, strokes_85, ncoords_85 },
	{ 0x00000056, 0, 0, 19, 21, -2, 21, 0, 1, strokes_86, ncoords_86 },
	{ 0x00000057, 0, 0, 28, 21, -2, 26, 0, 4, strokes_87, ncoords_87 },
	{ 0x00000058, 0, 0, 22, 21, -1, 23, 0, 2, strokes_88, ncoords_88 },
	{ 0x00000059, 0, -12, 19, 21, -2, 21, 0, 2, strokes_89, ncoords_89 },
	{ 0x0000005a, 0, -12, 16, 21, -2, 19, 0, 1, strokes_90, ncoords_90 },
	{ 0x0000005b, 0, -7, 7, 25, -4, 10, 0, 4, strokes_91, ncoords_91 },
	{ 0x0000005c, 0, -3, 14, 21, 0, 14, 0, 1, strokes_92, ncoords_92 },
	{ 0x0000005d, 0, -7, 7, 25, -3, 11, 0, 4, strokes_93, ncoords_93 },
	{ 0x0000005e, 0, 0, 10, 18, -3, 13, 0, 3, strokes_94, ncoords_94 },
	{ 0x0000005f, 0, -2, 16, -2, 0, 16, 0, 1, strokes_95, ncoords_95 },
	{ 0x00000060, 0, 15, 3, 21, -6, 5, 0, 1, strokes_96, ncoords_96 },
	{ 0x00000061, 0, 0, 16, 9, 0, 16, 0, 1, strokes_97, ncoords_97 },
	{ 0x00000062, 0, 0, 14, 21, 0, 14, 0, 1, strokes_98, ncoords_98 },
	{ 0x00000063, 0, 0, 11, 9, 0, 11, 0, 1, strokes_99, ncoords_99 },
	{ 0x00000064, 0, 0, 16, 21, 0, 16, 0, 2, strokes_100, ncoords_100 },
	{ 0x00000065, 0, 0, 10, 9, 0, 10, 0, 1, strokes_101, ncoords_101 },
	{ 0x00000066, 0, -12, 13, 21, 5, 13, 0, 1, strokes_102, ncoords_102 },
	{ 0x00000067, 0, -12, 15, 9, 0, 15, 0, 2, strokes_103, ncoords_103 },
	{ 0x00000068, 0, 0, 15, 21, 0, 15, 0, 2, strokes_104, ncoords_104 },
	{ 0x00000069, 0, 0, 7, 14, 0, 7, 0, 2, strokes_105, ncoords_105 },
	{ 0x0000006a, 0, -12, 15, 14, 8, 15, 0, 2, strokes_106, ncoords_106 },
	{ 0x0000006b, 0, 0, 14, 21, 0, 14, 0, 3, strokes_107, ncoords_107 },
	{ 0x0000006c, 0, 0, 8, 21, 0, 8, 0, 1, strokes_108, ncoords_108 },
	{ 0x0000006d, 0, 0, 25, 9, 0, 25, 0, 3, strokes_109, ncoords_109 },
	{ 0x0000006e, 0, 0, 18, 9, 0, 18, 0, 2, strokes_110, ncoords_110 },
	{ 0x0000006f, 0, 0, 14, 9, 0, 14, 0, 1, strokes_111, ncoords_111 },
	{ 0x00000070, 0, -12, 19, 10, 4, 19, 0, 3, strokes_112, ncoords_112 },
	{ 0x00000071, 0, -12, 15, 9, 0, 15, 0, 2, strokes_113, ncoords_113 },
	{ 0x00000072, 0, 0, 13, 10, 0, 13, 0, 1, strokes_114, ncoords_114 },
	{ 0x00000073, 0, 0, 11, 10, 0, 11, 0, 2, strokes_115, ncoords_115 },
	{ 0x00000074, 0, 0, 9, 21, 0, 9, 0, 3, strokes_116, ncoords_116 },
	{ 0x00000075, 0, 0, 15, 9, 0, 15, 0, 2, strokes_117, ncoords_117 },
	{ 0x00000076, 0, 0, 15, 9, 0, 15, 0, 2, strokes_118, ncoords_118 },
	{ 0x00000077, 0, 0, 21, 9, 0, 21, 0, 3, strokes_119, ncoords_119 },
	{ 0x00000078, 0, 0, 16, 9, 0, 16, 0, 2, strokes_120, ncoords_120 },
	{ 0x00000079, 0, -12, 15, 9, 0, 15, 0, 2, strokes_121, ncoords_121 },
	{ 0x0000007a, 0, -12, 14, 9, 0, 14, 0, 1, strokes_122, ncoords_122 },
	{ 0x0000007b, 0, -7, 5, 25, -4, 10, 0, 3, strokes_123, ncoords_123 },
	{ 0x0000007c, 0, -7, 0, 25, -4, 4, 0, 1, strokes_124, ncoords_124 },
	{ 0x0000007d, 0, -7, 5, 25, -5, 9, 0, 3, strokes_125, ncoords_125 },
	{ 0x0000007e, 0, 6, 18, 12, -3, 21, 0, 2, strokes_126, ncoords_126 },
	{ 0x0000007f, 0, 13, 8, 21, -3, 11, 0, 1, strokes_127, ncoords_127 }
};
const font_data_t font_hscript_1 = {
	"Hershey Script - single stroke",
	21,
	96,
	glyph_data
};
