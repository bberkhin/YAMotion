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

static const glyph_stroke_t stroke_33_0[3] = {{1,21},{1,7},{2,7}};
static const glyph_stroke_t stroke_33_1[3] = {{1,21},{2,21},{2,7}};
static const glyph_stroke_t stroke_33_2[9] = {{1,3},{0,2},{0,1},{1,0},{2,0},{3,1},{3,2},{2,3},{1,3}};
static const glyph_stroke_t stroke_33_3[5] = {{1,2},{1,1},{2,1},{2,2},{1,2}};
static const glyph_stroke_t *strokes_33[4] = {stroke_33_0, stroke_33_1, stroke_33_2, stroke_33_3};
static const uint8_t ncoords_33[4] = {3, 3, 9, 5};
static const glyph_stroke_t stroke_34_0[3] = {{1,21},{0,20},{0,14}};
static const glyph_stroke_t stroke_34_1[2] = {{1,20},{0,14}};
static const glyph_stroke_t stroke_34_2[3] = {{1,21},{2,20},{0,14}};
static const glyph_stroke_t stroke_34_3[3] = {{10,21},{9,20},{9,14}};
static const glyph_stroke_t stroke_34_4[2] = {{10,20},{9,14}};
static const glyph_stroke_t stroke_34_5[3] = {{10,21},{11,20},{9,14}};
static const glyph_stroke_t *strokes_34[6] = {stroke_34_0, stroke_34_1, stroke_34_2, stroke_34_3, stroke_34_4, stroke_34_5};
static const uint8_t ncoords_34[6] = {3, 2, 3, 3, 2, 3};
static const glyph_stroke_t stroke_35_0[5] = {{8,25},{7,25},{0,-7},{1,-7},{8,25}};
static const glyph_stroke_t stroke_35_1[5] = {{14,25},{15,25},{8,-7},{7,-7},{14,25}};
static const glyph_stroke_t stroke_35_2[5] = {{1,12},{1,13},{15,13},{15,12},{1,12}};
static const glyph_stroke_t stroke_35_3[5] = {{0,6},{0,7},{14,7},{14,6},{0,6}};
static const glyph_stroke_t *strokes_35[4] = {stroke_35_0, stroke_35_1, stroke_35_2, stroke_35_3};
static const uint8_t ncoords_35[4] = {5, 5, 5, 5};
static const glyph_stroke_t stroke_36_0[3] = {{6,25},{6,-4},{7,-4}};
static const glyph_stroke_t stroke_36_1[3] = {{6,25},{7,25},{7,-4}};
static const glyph_stroke_t stroke_36_2[19] = {{11,18},{13,18},{11,20},{8,21},{5,21},{2,20},{0,18},{0,16},{1,14},{2,13},{10,9},{11,8},{12,6},{12,4},{11,2},{8,1},{5,1},{3,2},{2,3}};
static const glyph_stroke_t stroke_36_3[19] = {{11,18},{10,19},{8,20},{5,20},{2,19},{1,18},{1,16},{2,14},{10,10},{12,8},{13,6},{13,4},{12,2},{11,1},{8,0},{5,0},{2,1},{0,3},{2,3}};
static const glyph_stroke_t stroke_36_4[2] = {{12,3},{9,1}};
static const glyph_stroke_t *strokes_36[5] = {stroke_36_0, stroke_36_1, stroke_36_2, stroke_36_3, stroke_36_4};
static const uint8_t ncoords_36[5] = {3, 3, 19, 19, 2};
static const glyph_stroke_t stroke_37_0[5] = {{18,21},{19,21},{1,0},{0,0},{18,21}};
static const glyph_stroke_t stroke_37_1[25] = {{5,21},{7,19},{7,17},{6,15},{4,14},{2,14},{0,16},{0,18},{1,20},{3,21},{5,21},{6,19},{6,17},{5,15},{3,14},{1,16},{1,18},{2,20},{4,21},{5,21},{7,20},{10,19},{13,19},{16,20},{18,21}};
static const glyph_stroke_t stroke_37_2[20] = {{15,7},{13,6},{12,4},{12,2},{14,0},{16,0},{18,1},{19,3},{19,5},{17,7},{15,7},{14,6},{13,4},{13,2},{15,0},{17,1},{18,3},{18,5},{16,7},{15,7}};
static const glyph_stroke_t *strokes_37[3] = {stroke_37_0, stroke_37_1, stroke_37_2};
static const uint8_t ncoords_37[3] = {5, 25, 20};
static const glyph_stroke_t stroke_38_0[35] = {{18,13},{17,12},{18,11},{19,12},{19,13},{18,14},{17,14},{16,13},{15,11},{13,6},{11,3},{9,1},{7,0},{4,0},{1,1},{0,3},{0,6},{1,8},{7,12},{9,14},{10,16},{10,18},{9,20},{7,21},{5,20},{4,18},{4,16},{5,13},{7,10},{12,3},{14,1},{17,0},{18,0},{19,1},{19,2}};
static const glyph_stroke_t stroke_38_1[6] = {{4,0},{2,1},{1,3},{1,6},{2,8},{4,10}};
static const glyph_stroke_t stroke_38_2[5] = {{4,16},{5,14},{13,3},{15,1},{17,0}};
static const glyph_stroke_t *strokes_38[3] = {stroke_38_0, stroke_38_1, stroke_38_2};
static const uint8_t ncoords_38[3] = {35, 6, 5};
static const glyph_stroke_t stroke_39_0[3] = {{1,21},{0,20},{0,14}};
static const glyph_stroke_t stroke_39_1[2] = {{1,20},{0,14}};
static const glyph_stroke_t stroke_39_2[3] = {{1,21},{2,20},{0,14}};
static const glyph_stroke_t *strokes_39[3] = {stroke_39_0, stroke_39_1, stroke_39_2};
static const uint8_t ncoords_39[3] = {3, 2, 3};
static const glyph_stroke_t stroke_40_0[10] = {{7,25},{5,23},{3,20},{1,16},{0,11},{0,7},{1,2},{3,-2},{5,-5},{7,-7}};
static const glyph_stroke_t stroke_40_1[8] = {{5,23},{3,19},{2,16},{1,11},{1,7},{2,2},{3,-1},{5,-5}};
static const glyph_stroke_t *strokes_40[2] = {stroke_40_0, stroke_40_1};
static const uint8_t ncoords_40[2] = {10, 8};
static const glyph_stroke_t stroke_41_0[10] = {{0,25},{2,23},{4,20},{6,16},{7,11},{7,7},{6,2},{4,-2},{2,-5},{0,-7}};
static const glyph_stroke_t stroke_41_1[8] = {{2,23},{4,19},{5,16},{6,11},{6,7},{5,2},{4,-1},{2,-5}};
static const glyph_stroke_t *strokes_41[2] = {stroke_41_0, stroke_41_1};
static const uint8_t ncoords_41[2] = {10, 8};
static const glyph_stroke_t stroke_42_0[4] = {{5,21},{4,20},{6,10},{5,9}};
static const glyph_stroke_t stroke_42_1[2] = {{5,21},{5,9}};
static const glyph_stroke_t stroke_42_2[4] = {{5,21},{6,20},{4,10},{5,9}};
static const glyph_stroke_t stroke_42_3[4] = {{0,18},{1,18},{9,12},{10,12}};
static const glyph_stroke_t stroke_42_4[2] = {{0,18},{10,12}};
static const glyph_stroke_t stroke_42_5[4] = {{0,18},{0,17},{10,13},{10,12}};
static const glyph_stroke_t stroke_42_6[4] = {{10,18},{9,18},{1,12},{0,12}};
static const glyph_stroke_t stroke_42_7[2] = {{10,18},{0,12}};
static const glyph_stroke_t stroke_42_8[4] = {{10,18},{10,17},{0,13},{0,12}};
static const glyph_stroke_t *strokes_42[9] = {stroke_42_0, stroke_42_1, stroke_42_2, stroke_42_3, stroke_42_4, stroke_42_5, stroke_42_6, stroke_42_7, stroke_42_8};
static const uint8_t ncoords_42[9] = {4, 2, 4, 4, 2, 4, 4, 2, 4};
static const glyph_stroke_t stroke_43_0[3] = {{8,18},{8,1},{9,1}};
static const glyph_stroke_t stroke_43_1[3] = {{8,18},{9,18},{9,1}};
static const glyph_stroke_t stroke_43_2[3] = {{0,10},{17,10},{17,9}};
static const glyph_stroke_t stroke_43_3[3] = {{0,10},{0,9},{17,9}};
static const glyph_stroke_t *strokes_43[4] = {stroke_43_0, stroke_43_1, stroke_43_2, stroke_43_3};
static const uint8_t ncoords_43[4] = {3, 3, 3, 3};
static const glyph_stroke_t stroke_44_0[11] = {{3,1},{2,0},{1,0},{0,1},{0,2},{1,3},{2,3},{3,2},{3,-1},{2,-3},{0,-4}};
static const glyph_stroke_t stroke_44_1[5] = {{1,2},{1,1},{2,1},{2,2},{1,2}};
static const glyph_stroke_t stroke_44_2[2] = {{2,0},{3,-1}};
static const glyph_stroke_t stroke_44_3[2] = {{3,1},{2,-3}};
static const glyph_stroke_t *strokes_44[4] = {stroke_44_0, stroke_44_1, stroke_44_2, stroke_44_3};
static const uint8_t ncoords_44[4] = {11, 5, 2, 2};
static const glyph_stroke_t stroke_45_0[5] = {{0,9},{0,10},{10,10},{10,9},{0,9}};
static const glyph_stroke_t *strokes_45[1] = {stroke_45_0};
static const uint8_t ncoords_45[1] = {5};
static const glyph_stroke_t stroke_46_0[9] = {{1,3},{0,2},{0,1},{1,0},{2,0},{3,1},{3,2},{2,3},{1,3}};
static const glyph_stroke_t stroke_46_1[5] = {{1,2},{1,1},{2,1},{2,2},{1,2}};
static const glyph_stroke_t *strokes_46[2] = {stroke_46_0, stroke_46_1};
static const uint8_t ncoords_46[2] = {9, 5};
static const glyph_stroke_t stroke_47_0[3] = {{18,25},{0,-7},{1,-7}};
static const glyph_stroke_t stroke_47_1[3] = {{18,25},{19,25},{1,-7}};
static const glyph_stroke_t *strokes_47[2] = {stroke_47_0, stroke_47_1};
static const uint8_t ncoords_47[2] = {3, 3};
static const glyph_stroke_t stroke_48_0[17] = {{6,21},{3,20},{1,17},{0,12},{0,9},{1,4},{3,1},{6,0},{8,0},{11,1},{13,4},{14,9},{14,12},{13,17},{11,20},{8,21},{6,21}};
static const glyph_stroke_t stroke_48_1[6] = {{4,20},{2,17},{1,12},{1,9},{2,4},{4,1}};
static const glyph_stroke_t stroke_48_2[4] = {{3,2},{6,1},{8,1},{11,2}};
static const glyph_stroke_t stroke_48_3[6] = {{10,1},{12,4},{13,9},{13,12},{12,17},{10,20}};
static const glyph_stroke_t stroke_48_4[4] = {{11,19},{8,20},{6,20},{3,19}};
static const glyph_stroke_t *strokes_48[5] = {stroke_48_0, stroke_48_1, stroke_48_2, stroke_48_3, stroke_48_4};
static const uint8_t ncoords_48[5] = {17, 6, 4, 6, 4};
static const glyph_stroke_t stroke_49_0[4] = {{0,17},{2,18},{5,21},{5,0}};
static const glyph_stroke_t stroke_49_1[6] = {{0,17},{0,16},{2,17},{4,19},{4,0},{5,0}};
static const glyph_stroke_t *strokes_49[2] = {stroke_49_0, stroke_49_1};
static const uint8_t ncoords_49[2] = {4, 6};
static const glyph_stroke_t stroke_50_0[13] = {{1,16},{1,17},{2,19},{3,20},{5,21},{9,21},{11,20},{12,19},{13,17},{13,15},{12,13},{10,10},{1,0}};
static const glyph_stroke_t stroke_50_1[12] = {{1,16},{2,16},{2,17},{3,19},{5,20},{9,20},{11,19},{12,17},{12,15},{11,13},{9,10},{0,0}};
static const glyph_stroke_t stroke_50_2[3] = {{1,1},{14,1},{14,0}};
static const glyph_stroke_t stroke_50_3[2] = {{0,0},{14,0}};
static const glyph_stroke_t *strokes_50[4] = {stroke_50_0, stroke_50_1, stroke_50_2, stroke_50_3};
static const uint8_t ncoords_50[4] = {13, 12, 3, 2};
static const glyph_stroke_t stroke_51_0[3] = {{2,21},{13,21},{6,12}};
static const glyph_stroke_t stroke_51_1[3] = {{2,21},{2,20},{12,20}};
static const glyph_stroke_t stroke_51_2[2] = {{12,21},{5,12}};
static const glyph_stroke_t stroke_51_3[14] = {{6,13},{8,13},{11,12},{13,10},{14,7},{14,6},{13,3},{11,1},{8,0},{5,0},{2,1},{1,2},{0,4},{1,4}};
static const glyph_stroke_t stroke_51_4[4] = {{5,12},{8,12},{11,11},{13,8}};
static const glyph_stroke_t stroke_51_5[6] = {{9,12},{12,10},{13,7},{13,6},{12,3},{9,1}};
static const glyph_stroke_t stroke_51_6[6] = {{13,5},{11,2},{8,1},{5,1},{2,2},{1,4}};
static const glyph_stroke_t stroke_51_7[2] = {{4,1},{1,3}};
static const glyph_stroke_t *strokes_51[8] = {stroke_51_0, stroke_51_1, stroke_51_2, stroke_51_3, stroke_51_4, stroke_51_5, stroke_51_6, stroke_51_7};
static const uint8_t ncoords_51[8] = {3, 3, 2, 14, 4, 6, 6, 2};
static const glyph_stroke_t stroke_52_0[3] = {{10,18},{10,0},{11,0}};
static const glyph_stroke_t stroke_52_1[2] = {{11,21},{11,0}};
static const glyph_stroke_t stroke_52_2[3] = {{11,21},{0,5},{15,5}};
static const glyph_stroke_t stroke_52_3[2] = {{10,18},{1,5}};
static const glyph_stroke_t stroke_52_4[3] = {{1,6},{15,6},{15,5}};
static const glyph_stroke_t *strokes_52[5] = {stroke_52_0, stroke_52_1, stroke_52_2, stroke_52_3, stroke_52_4};
static const uint8_t ncoords_52[5] = {3, 2, 3, 2, 3};
static const glyph_stroke_t stroke_53_0[2] = {{2,21},{1,12}};
static const glyph_stroke_t stroke_53_1[2] = {{3,20},{2,13}};
static const glyph_stroke_t stroke_53_2[3] = {{2,21},{12,21},{12,20}};
static const glyph_stroke_t stroke_53_3[2] = {{3,20},{12,20}};
static const glyph_stroke_t stroke_53_4[15] = {{2,13},{5,14},{8,14},{11,13},{13,11},{14,8},{14,6},{13,3},{11,1},{8,0},{5,0},{2,1},{1,2},{0,4},{1,4}};
static const glyph_stroke_t stroke_53_5[6] = {{1,12},{2,12},{4,13},{8,13},{11,12},{13,9}};
static const glyph_stroke_t stroke_53_6[6] = {{9,13},{12,11},{13,8},{13,6},{12,3},{9,1}};
static const glyph_stroke_t stroke_53_7[6] = {{13,5},{11,2},{8,1},{5,1},{2,2},{1,4}};
static const glyph_stroke_t stroke_53_8[2] = {{4,1},{1,3}};
static const glyph_stroke_t *strokes_53[9] = {stroke_53_0, stroke_53_1, stroke_53_2, stroke_53_3, stroke_53_4, stroke_53_5, stroke_53_6, stroke_53_7, stroke_53_8};
static const uint8_t ncoords_53[9] = {2, 2, 3, 2, 15, 6, 6, 6, 2};
static const glyph_stroke_t stroke_54_0[24] = {{10,20},{11,18},{12,18},{11,20},{8,21},{6,21},{3,20},{1,17},{0,12},{0,7},{1,3},{3,1},{6,0},{7,0},{10,1},{12,3},{13,6},{13,7},{12,10},{10,12},{7,13},{6,13},{3,12},{1,10}};
static const glyph_stroke_t stroke_54_1[4] = {{11,19},{8,20},{6,20},{3,19}};
static const glyph_stroke_t stroke_54_2[6] = {{4,20},{2,17},{1,12},{1,7},{2,3},{5,1}};
static const glyph_stroke_t stroke_54_3[6] = {{1,5},{3,2},{6,1},{7,1},{10,2},{12,5}};
static const glyph_stroke_t stroke_54_4[6] = {{8,1},{11,3},{12,6},{12,7},{11,10},{8,12}};
static const glyph_stroke_t stroke_54_5[6] = {{12,8},{10,11},{7,12},{6,12},{3,11},{1,8}};
static const glyph_stroke_t stroke_54_6[3] = {{5,12},{2,10},{1,7}};
static const glyph_stroke_t *strokes_54[7] = {stroke_54_0, stroke_54_1, stroke_54_2, stroke_54_3, stroke_54_4, stroke_54_5, stroke_54_6};
static const uint8_t ncoords_54[7] = {24, 4, 6, 6, 6, 6, 3};
static const glyph_stroke_t stroke_55_0[3] = {{0,21},{14,21},{4,0}};
static const glyph_stroke_t stroke_55_1[3] = {{0,21},{0,20},{13,20}};
static const glyph_stroke_t stroke_55_2[3] = {{13,21},{3,0},{4,0}};
static const glyph_stroke_t *strokes_55[3] = {stroke_55_0, stroke_55_1, stroke_55_2};
static const uint8_t ncoords_55[3] = {3, 3, 3};
static const glyph_stroke_t stroke_56_0[29] = {{5,21},{2,20},{1,18},{1,16},{2,14},{3,13},{5,12},{9,11},{11,10},{12,9},{13,7},{13,4},{12,2},{9,1},{5,1},{2,2},{1,4},{1,7},{2,9},{3,10},{5,11},{9,12},{11,13},{12,14},{13,16},{13,18},{12,20},{9,21},{5,21}};
static const glyph_stroke_t stroke_56_1[26] = {{3,20},{2,18},{2,16},{3,14},{5,13},{9,12},{11,11},{13,9},{14,7},{14,4},{13,2},{12,1},{9,0},{5,0},{2,1},{1,2},{0,4},{0,7},{1,9},{3,11},{5,12},{9,13},{11,14},{12,16},{12,18},{11,20}};
static const glyph_stroke_t stroke_56_2[4] = {{12,19},{9,20},{5,20},{2,19}};
static const glyph_stroke_t stroke_56_3[2] = {{1,3},{4,1}};
static const glyph_stroke_t stroke_56_4[2] = {{10,1},{13,3}};
static const glyph_stroke_t *strokes_56[5] = {stroke_56_0, stroke_56_1, stroke_56_2, stroke_56_3, stroke_56_4};
static const uint8_t ncoords_56[5] = {29, 26, 4, 2, 2};
static const glyph_stroke_t stroke_57_0[24] = {{12,11},{10,9},{7,8},{6,8},{3,9},{1,11},{0,14},{0,15},{1,18},{3,20},{6,21},{7,21},{10,20},{12,18},{13,14},{13,9},{12,4},{10,1},{7,0},{5,0},{2,1},{1,3},{2,3},{3,1}};
static const glyph_stroke_t stroke_57_1[3] = {{12,14},{11,11},{8,9}};
static const glyph_stroke_t stroke_57_2[6] = {{12,13},{10,10},{7,9},{6,9},{3,10},{1,13}};
static const glyph_stroke_t stroke_57_3[6] = {{5,9},{2,11},{1,14},{1,15},{2,18},{5,20}};
static const glyph_stroke_t stroke_57_4[6] = {{1,16},{3,19},{6,20},{7,20},{10,19},{12,16}};
static const glyph_stroke_t stroke_57_5[6] = {{8,20},{11,18},{12,14},{12,9},{11,4},{9,1}};
static const glyph_stroke_t stroke_57_6[4] = {{10,2},{7,1},{5,1},{2,2}};
static const glyph_stroke_t *strokes_57[7] = {stroke_57_0, stroke_57_1, stroke_57_2, stroke_57_3, stroke_57_4, stroke_57_5, stroke_57_6};
static const uint8_t ncoords_57[7] = {24, 3, 6, 6, 6, 6, 4};
static const glyph_stroke_t stroke_58_0[9] = {{1,14},{0,13},{0,12},{1,11},{2,11},{3,12},{3,13},{2,14},{1,14}};
static const glyph_stroke_t stroke_58_1[5] = {{1,13},{1,12},{2,12},{2,13},{1,13}};
static const glyph_stroke_t stroke_58_2[9] = {{1,3},{0,2},{0,1},{1,0},{2,0},{3,1},{3,2},{2,3},{1,3}};
static const glyph_stroke_t stroke_58_3[5] = {{1,2},{1,1},{2,1},{2,2},{1,2}};
static const glyph_stroke_t *strokes_58[4] = {stroke_58_0, stroke_58_1, stroke_58_2, stroke_58_3};
static const uint8_t ncoords_58[4] = {9, 5, 9, 5};
static const glyph_stroke_t stroke_59_0[9] = {{1,14},{0,13},{0,12},{1,11},{2,11},{3,12},{3,13},{2,14},{1,14}};
static const glyph_stroke_t stroke_59_1[5] = {{1,13},{1,12},{2,12},{2,13},{1,13}};
static const glyph_stroke_t stroke_59_2[11] = {{3,1},{2,0},{1,0},{0,1},{0,2},{1,3},{2,3},{3,2},{3,-1},{2,-3},{0,-4}};
static const glyph_stroke_t stroke_59_3[5] = {{1,2},{1,1},{2,1},{2,2},{1,2}};
static const glyph_stroke_t stroke_59_4[2] = {{2,0},{3,-1}};
static const glyph_stroke_t stroke_59_5[2] = {{3,1},{2,-3}};
static const glyph_stroke_t *strokes_59[6] = {stroke_59_0, stroke_59_1, stroke_59_2, stroke_59_3, stroke_59_4, stroke_59_5};
static const uint8_t ncoords_59[6] = {9, 5, 11, 5, 2, 2};
static const glyph_stroke_t stroke_60_0[7] = {{16,18},{0,9},{16,0},{16,1},{2,9},{16,17},{16,18}};
static const glyph_stroke_t *strokes_60[1] = {stroke_60_0};
static const uint8_t ncoords_60[1] = {7};
static const glyph_stroke_t stroke_61_0[3] = {{0,14},{17,14},{17,13}};
static const glyph_stroke_t stroke_61_1[3] = {{0,14},{0,13},{17,13}};
static const glyph_stroke_t stroke_61_2[3] = {{0,6},{17,6},{17,5}};
static const glyph_stroke_t stroke_61_3[3] = {{0,6},{0,5},{17,5}};
static const glyph_stroke_t *strokes_61[4] = {stroke_61_0, stroke_61_1, stroke_61_2, stroke_61_3};
static const uint8_t ncoords_61[4] = {3, 3, 3, 3};
static const glyph_stroke_t stroke_62_0[7] = {{0,18},{16,9},{0,0},{0,1},{14,9},{0,17},{0,18}};
static const glyph_stroke_t *strokes_62[1] = {stroke_62_0};
static const uint8_t ncoords_62[1] = {7};
static const glyph_stroke_t stroke_63_0[14] = {{0,16},{0,17},{1,19},{2,20},{5,21},{8,21},{11,20},{12,19},{13,17},{13,15},{12,13},{11,12},{9,11},{6,10}};
static const glyph_stroke_t stroke_63_1[12] = {{0,16},{1,16},{1,17},{2,19},{5,20},{8,20},{11,19},{12,17},{12,15},{11,13},{9,12},{6,11}};
static const glyph_stroke_t stroke_63_2[2] = {{1,18},{4,20}};
static const glyph_stroke_t stroke_63_3[2] = {{9,20},{12,18}};
static const glyph_stroke_t stroke_63_4[2] = {{12,14},{8,11}};
static const glyph_stroke_t stroke_63_5[4] = {{6,11},{6,7},{7,7},{7,11}};
static const glyph_stroke_t stroke_63_6[9] = {{6,3},{5,2},{5,1},{6,0},{7,0},{8,1},{8,2},{7,3},{6,3}};
static const glyph_stroke_t stroke_63_7[5] = {{6,2},{6,1},{7,1},{7,2},{6,2}};
static const glyph_stroke_t *strokes_63[8] = {stroke_63_0, stroke_63_1, stroke_63_2, stroke_63_3, stroke_63_4, stroke_63_5, stroke_63_6, stroke_63_7};
static const uint8_t ncoords_63[8] = {14, 12, 2, 2, 2, 4, 9, 5};
static const glyph_stroke_t stroke_64_0[13] = {{15,13},{14,15},{12,16},{9,16},{7,15},{6,14},{5,11},{5,8},{6,6},{8,5},{11,5},{13,6},{14,8}};
static const glyph_stroke_t stroke_64_1[6] = {{9,16},{7,14},{6,11},{6,8},{7,6},{8,5}};
static const glyph_stroke_t stroke_64_2[29] = {{15,16},{14,8},{14,6},{16,5},{18,5},{20,7},{21,10},{21,12},{20,15},{19,17},{17,19},{15,20},{12,21},{9,21},{6,20},{4,19},{2,17},{1,15},{0,12},{0,9},{1,6},{2,4},{4,2},{6,1},{9,0},{12,0},{15,1},{17,2},{18,3}};
static const glyph_stroke_t stroke_64_3[4] = {{16,16},{15,8},{15,6},{16,5}};
static const glyph_stroke_t *strokes_64[4] = {stroke_64_0, stroke_64_1, stroke_64_2, stroke_64_3};
static const uint8_t ncoords_64[4] = {13, 6, 29, 4};
static const glyph_stroke_t stroke_65_0[2] = {{8,21},{0,0}};
static const glyph_stroke_t stroke_65_1[3] = {{8,18},{1,0},{0,0}};
static const glyph_stroke_t stroke_65_2[3] = {{8,18},{15,0},{16,0}};
static const glyph_stroke_t stroke_65_3[2] = {{8,21},{16,0}};
static const glyph_stroke_t stroke_65_4[2] = {{3,6},{13,6}};
static const glyph_stroke_t stroke_65_5[2] = {{2,5},{14,5}};
static const glyph_stroke_t *strokes_65[6] = {stroke_65_0, stroke_65_1, stroke_65_2, stroke_65_3, stroke_65_4, stroke_65_5};
static const uint8_t ncoords_65[6] = {2, 3, 3, 2, 2, 2};
static const glyph_stroke_t stroke_66_0[2] = {{0,21},{0,0}};
static const glyph_stroke_t stroke_66_1[2] = {{1,20},{1,1}};
static const glyph_stroke_t stroke_66_2[9] = {{0,21},{8,21},{11,20},{12,19},{13,17},{13,14},{12,12},{11,11},{8,10}};
static const glyph_stroke_t stroke_66_3[7] = {{1,20},{8,20},{11,19},{12,17},{12,14},{11,12},{8,11}};
static const glyph_stroke_t stroke_66_4[10] = {{1,11},{8,11},{11,10},{12,9},{13,7},{13,4},{12,2},{11,1},{8,0},{0,0}};
static const glyph_stroke_t stroke_66_5[8] = {{1,10},{8,10},{11,9},{12,7},{12,4},{11,2},{8,1},{1,1}};
static const glyph_stroke_t *strokes_66[6] = {stroke_66_0, stroke_66_1, stroke_66_2, stroke_66_3, stroke_66_4, stroke_66_5};
static const uint8_t ncoords_66[6] = {2, 2, 9, 7, 10, 8};
static const glyph_stroke_t stroke_67_0[18] = {{15,16},{14,18},{12,20},{10,21},{6,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3},{4,1},{6,0},{10,0},{12,1},{14,3},{15,5}};
static const glyph_stroke_t stroke_67_1[18] = {{15,16},{14,16},{13,18},{12,19},{10,20},{6,20},{4,19},{2,16},{1,13},{1,8},{2,5},{4,2},{6,1},{10,1},{12,2},{13,3},{14,5},{15,5}};
static const glyph_stroke_t *strokes_67[2] = {stroke_67_0, stroke_67_1};
static const uint8_t ncoords_67[2] = {18, 18};
static const glyph_stroke_t stroke_68_0[2] = {{0,21},{0,0}};
static const glyph_stroke_t stroke_68_1[2] = {{1,20},{1,1}};
static const glyph_stroke_t stroke_68_2[12] = {{0,21},{7,21},{10,20},{12,18},{13,16},{14,13},{14,8},{13,5},{12,3},{10,1},{7,0},{0,0}};
static const glyph_stroke_t stroke_68_3[12] = {{1,20},{7,20},{10,19},{11,18},{12,16},{13,13},{13,8},{12,5},{11,3},{10,2},{7,1},{1,1}};
static const glyph_stroke_t *strokes_68[4] = {stroke_68_0, stroke_68_1, stroke_68_2, stroke_68_3};
static const uint8_t ncoords_68[4] = {2, 2, 12, 12};
static const glyph_stroke_t stroke_69_0[2] = {{0,21},{0,0}};
static const glyph_stroke_t stroke_69_1[2] = {{1,20},{1,1}};
static const glyph_stroke_t stroke_69_2[2] = {{0,21},{12,21}};
static const glyph_stroke_t stroke_69_3[3] = {{1,20},{12,20},{12,21}};
static const glyph_stroke_t stroke_69_4[3] = {{1,11},{7,11},{7,10}};
static const glyph_stroke_t stroke_69_5[2] = {{1,10},{7,10}};
static const glyph_stroke_t stroke_69_6[3] = {{1,1},{12,1},{12,0}};
static const glyph_stroke_t stroke_69_7[2] = {{0,0},{12,0}};
static const glyph_stroke_t *strokes_69[8] = {stroke_69_0, stroke_69_1, stroke_69_2, stroke_69_3, stroke_69_4, stroke_69_5, stroke_69_6, stroke_69_7};
static const uint8_t ncoords_69[8] = {2, 2, 2, 3, 3, 2, 3, 2};
static const glyph_stroke_t stroke_70_0[2] = {{0,21},{0,0}};
static const glyph_stroke_t stroke_70_1[3] = {{1,20},{1,0},{0,0}};
static const glyph_stroke_t stroke_70_2[2] = {{0,21},{12,21}};
static const glyph_stroke_t stroke_70_3[3] = {{1,20},{12,20},{12,21}};
static const glyph_stroke_t stroke_70_4[3] = {{1,11},{7,11},{7,10}};
static const glyph_stroke_t stroke_70_5[2] = {{1,10},{7,10}};
static const glyph_stroke_t *strokes_70[6] = {stroke_70_0, stroke_70_1, stroke_70_2, stroke_70_3, stroke_70_4, stroke_70_5};
static const uint8_t ncoords_70[6] = {2, 3, 2, 3, 3, 2};
static const glyph_stroke_t stroke_71_0[20] = {{15,16},{14,18},{12,20},{10,21},{6,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3},{4,1},{6,0},{10,0},{12,1},{14,3},{15,5},{15,9},{10,9}};
static const glyph_stroke_t stroke_71_1[22] = {{15,16},{14,16},{13,18},{12,19},{10,20},{6,20},{4,19},{3,18},{2,16},{1,13},{1,8},{2,5},{3,3},{4,2},{6,1},{10,1},{12,2},{13,3},{14,5},{14,8},{10,8},{10,9}};
static const glyph_stroke_t *strokes_71[2] = {stroke_71_0, stroke_71_1};
static const uint8_t ncoords_71[2] = {20, 22};
static const glyph_stroke_t stroke_72_0[2] = {{0,21},{0,0}};
static const glyph_stroke_t stroke_72_1[4] = {{0,21},{1,21},{1,0},{0,0}};
static const glyph_stroke_t stroke_72_2[4] = {{14,21},{13,21},{13,0},{14,0}};
static const glyph_stroke_t stroke_72_3[2] = {{14,21},{14,0}};
static const glyph_stroke_t stroke_72_4[2] = {{1,11},{13,11}};
static const glyph_stroke_t stroke_72_5[2] = {{1,10},{13,10}};
static const glyph_stroke_t *strokes_72[6] = {stroke_72_0, stroke_72_1, stroke_72_2, stroke_72_3, stroke_72_4, stroke_72_5};
static const uint8_t ncoords_72[6] = {2, 4, 4, 2, 2, 2};
static const glyph_stroke_t stroke_73_0[3] = {{0,21},{0,0},{1,0}};
static const glyph_stroke_t stroke_73_1[3] = {{0,21},{1,21},{1,0}};
static const glyph_stroke_t *strokes_73[2] = {stroke_73_0, stroke_73_1};
static const uint8_t ncoords_73[2] = {3, 3};
static const glyph_stroke_t stroke_74_0[8] = {{9,21},{9,5},{8,2},{6,1},{4,1},{2,2},{1,5},{0,5}};
static const glyph_stroke_t stroke_74_1[10] = {{9,21},{10,21},{10,5},{9,2},{8,1},{6,0},{4,0},{2,1},{1,2},{0,5}};
static const glyph_stroke_t *strokes_74[2] = {stroke_74_0, stroke_74_1};
static const uint8_t ncoords_74[2] = {8, 10};
static const glyph_stroke_t stroke_75_0[3] = {{0,21},{0,0},{1,0}};
static const glyph_stroke_t stroke_75_1[3] = {{0,21},{1,21},{1,0}};
static const glyph_stroke_t stroke_75_2[3] = {{14,21},{13,21},{1,9}};
static const glyph_stroke_t stroke_75_3[2] = {{14,21},{1,8}};
static const glyph_stroke_t stroke_75_4[3] = {{4,12},{13,0},{14,0}};
static const glyph_stroke_t stroke_75_5[2] = {{5,12},{14,0}};
static const glyph_stroke_t *strokes_75[6] = {stroke_75_0, stroke_75_1, stroke_75_2, stroke_75_3, stroke_75_4, stroke_75_5};
static const uint8_t ncoords_75[6] = {3, 3, 3, 2, 3, 2};
static const glyph_stroke_t stroke_76_0[2] = {{0,21},{0,0}};
static const glyph_stroke_t stroke_76_1[3] = {{0,21},{1,21},{1,1}};
static const glyph_stroke_t stroke_76_2[3] = {{1,1},{12,1},{12,0}};
static const glyph_stroke_t stroke_76_3[2] = {{0,0},{12,0}};
static const glyph_stroke_t *strokes_76[4] = {stroke_76_0, stroke_76_1, stroke_76_2, stroke_76_3};
static const uint8_t ncoords_76[4] = {2, 3, 3, 2};
static const glyph_stroke_t stroke_77_0[2] = {{0,21},{0,0}};
static const glyph_stroke_t stroke_77_1[3] = {{1,16},{1,0},{0,0}};
static const glyph_stroke_t stroke_77_2[2] = {{1,16},{8,0}};
static const glyph_stroke_t stroke_77_3[2] = {{0,21},{8,3}};
static const glyph_stroke_t stroke_77_4[2] = {{16,21},{8,3}};
static const glyph_stroke_t stroke_77_5[2] = {{15,16},{8,0}};
static const glyph_stroke_t stroke_77_6[3] = {{15,16},{15,0},{16,0}};
static const glyph_stroke_t stroke_77_7[2] = {{16,21},{16,0}};
static const glyph_stroke_t *strokes_77[8] = {stroke_77_0, stroke_77_1, stroke_77_2, stroke_77_3, stroke_77_4, stroke_77_5, stroke_77_6, stroke_77_7};
static const uint8_t ncoords_77[8] = {2, 3, 2, 2, 2, 2, 3, 2};
static const glyph_stroke_t stroke_78_0[2] = {{0,21},{0,0}};
static const glyph_stroke_t stroke_78_1[3] = {{1,18},{1,0},{0,0}};
static const glyph_stroke_t stroke_78_2[2] = {{1,18},{14,0}};
static const glyph_stroke_t stroke_78_3[2] = {{0,21},{13,3}};
static const glyph_stroke_t stroke_78_4[2] = {{13,21},{13,3}};
static const glyph_stroke_t stroke_78_5[3] = {{13,21},{14,21},{14,0}};
static const glyph_stroke_t *strokes_78[6] = {stroke_78_0, stroke_78_1, stroke_78_2, stroke_78_3, stroke_78_4, stroke_78_5};
static const uint8_t ncoords_78[6] = {2, 3, 2, 2, 2, 3};
static const glyph_stroke_t stroke_79_0[21] = {{6,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3},{4,1},{6,0},{10,0},{12,1},{14,3},{15,5},{16,8},{16,13},{15,16},{14,18},{12,20},{10,21},{6,21}};
static const glyph_stroke_t stroke_79_1[17] = {{7,20},{4,19},{2,16},{1,13},{1,8},{2,5},{4,2},{7,1},{9,1},{12,2},{14,5},{15,8},{15,13},{14,16},{12,19},{9,20},{7,20}};
static const glyph_stroke_t *strokes_79[2] = {stroke_79_0, stroke_79_1};
static const uint8_t ncoords_79[2] = {21, 17};
static const glyph_stroke_t stroke_80_0[2] = {{0,21},{0,0}};
static const glyph_stroke_t stroke_80_1[3] = {{1,20},{1,0},{0,0}};
static const glyph_stroke_t stroke_80_2[10] = {{0,21},{9,21},{11,20},{12,19},{13,17},{13,14},{12,12},{11,11},{9,10},{1,10}};
static const glyph_stroke_t stroke_80_3[8] = {{1,20},{9,20},{11,19},{12,17},{12,14},{11,12},{9,11},{1,11}};
static const glyph_stroke_t *strokes_80[4] = {stroke_80_0, stroke_80_1, stroke_80_2, stroke_80_3};
static const uint8_t ncoords_80[4] = {2, 3, 10, 8};
static const glyph_stroke_t stroke_81_0[21] = {{6,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3},{4,1},{6,0},{10,0},{12,1},{14,3},{15,5},{16,8},{16,13},{15,16},{14,18},{12,20},{10,21},{6,21}};
static const glyph_stroke_t stroke_81_1[17] = {{7,20},{4,19},{2,16},{1,13},{1,8},{2,5},{4,2},{7,1},{9,1},{12,2},{14,5},{15,8},{15,13},{14,16},{12,19},{9,20},{7,20}};
static const glyph_stroke_t stroke_81_2[3] = {{9,3},{14,-2},{15,-2}};
static const glyph_stroke_t stroke_81_3[3] = {{9,3},{10,3},{15,-2}};
static const glyph_stroke_t *strokes_81[4] = {stroke_81_0, stroke_81_1, stroke_81_2, stroke_81_3};
static const uint8_t ncoords_81[4] = {21, 17, 3, 3};
static const glyph_stroke_t stroke_82_0[2] = {{0,21},{0,0}};
static const glyph_stroke_t stroke_82_1[3] = {{1,20},{1,0},{0,0}};
static const glyph_stroke_t stroke_82_2[10] = {{0,21},{8,21},{11,20},{12,19},{13,17},{13,14},{12,12},{11,11},{8,10},{1,10}};
static const glyph_stroke_t stroke_82_3[8] = {{1,20},{8,20},{11,19},{12,17},{12,14},{11,12},{8,11},{1,11}};
static const glyph_stroke_t stroke_82_4[3] = {{6,10},{12,0},{13,0}};
static const glyph_stroke_t stroke_82_5[2] = {{7,10},{13,0}};
static const glyph_stroke_t *strokes_82[6] = {stroke_82_0, stroke_82_1, stroke_82_2, stroke_82_3, stroke_82_4, stroke_82_5};
static const uint8_t ncoords_82[6] = {2, 3, 10, 8, 3, 2};
static const glyph_stroke_t stroke_83_0[21] = {{14,18},{12,20},{9,21},{5,21},{2,20},{0,18},{0,16},{1,14},{2,13},{4,12},{9,10},{11,9},{12,8},{13,6},{13,3},{12,2},{9,1},{5,1},{3,2},{2,3},{0,3}};
static const glyph_stroke_t stroke_83_1[20] = {{14,18},{12,18},{11,19},{9,20},{5,20},{2,19},{1,18},{1,16},{2,14},{4,13},{9,11},{11,10},{13,8},{14,6},{14,3},{12,1},{9,0},{5,0},{2,1},{0,3}};
static const glyph_stroke_t *strokes_83[2] = {stroke_83_0, stroke_83_1};
static const uint8_t ncoords_83[2] = {21, 20};
static const glyph_stroke_t stroke_84_0[2] = {{6,20},{6,0}};
static const glyph_stroke_t stroke_84_1[3] = {{7,20},{7,0},{6,0}};
static const glyph_stroke_t stroke_84_2[3] = {{0,21},{13,21},{13,20}};
static const glyph_stroke_t stroke_84_3[3] = {{0,21},{0,20},{13,20}};
static const glyph_stroke_t *strokes_84[4] = {stroke_84_0, stroke_84_1, stroke_84_2, stroke_84_3};
static const uint8_t ncoords_84[4] = {2, 3, 3, 3};
static const glyph_stroke_t stroke_85_0[10] = {{0,21},{0,6},{1,3},{3,1},{6,0},{8,0},{11,1},{13,3},{14,6},{14,21}};
static const glyph_stroke_t stroke_85_1[12] = {{0,21},{1,21},{1,6},{2,3},{3,2},{6,1},{8,1},{11,2},{12,3},{13,6},{13,21},{14,21}};
static const glyph_stroke_t *strokes_85[2] = {stroke_85_0, stroke_85_1};
static const uint8_t ncoords_85[2] = {10, 12};
static const glyph_stroke_t stroke_86_0[2] = {{0,21},{8,0}};
static const glyph_stroke_t stroke_86_1[3] = {{0,21},{1,21},{8,3}};
static const glyph_stroke_t stroke_86_2[3] = {{16,21},{15,21},{8,3}};
static const glyph_stroke_t stroke_86_3[2] = {{16,21},{8,0}};
static const glyph_stroke_t *strokes_86[4] = {stroke_86_0, stroke_86_1, stroke_86_2, stroke_86_3};
static const uint8_t ncoords_86[4] = {2, 3, 3, 2};
static const glyph_stroke_t stroke_87_0[2] = {{0,21},{6,0}};
static const glyph_stroke_t stroke_87_1[3] = {{0,21},{1,21},{6,3}};
static const glyph_stroke_t stroke_87_2[2] = {{11,21},{6,3}};
static const glyph_stroke_t stroke_87_3[2] = {{11,18},{6,0}};
static const glyph_stroke_t stroke_87_4[2] = {{11,18},{16,0}};
static const glyph_stroke_t stroke_87_5[2] = {{11,21},{16,3}};
static const glyph_stroke_t stroke_87_6[3] = {{22,21},{21,21},{16,3}};
static const glyph_stroke_t stroke_87_7[2] = {{22,21},{16,0}};
static const glyph_stroke_t *strokes_87[8] = {stroke_87_0, stroke_87_1, stroke_87_2, stroke_87_3, stroke_87_4, stroke_87_5, stroke_87_6, stroke_87_7};
static const uint8_t ncoords_87[8] = {2, 3, 2, 2, 2, 2, 3, 2};
static const glyph_stroke_t stroke_88_0[3] = {{0,21},{13,0},{14,0}};
static const glyph_stroke_t stroke_88_1[3] = {{0,21},{1,21},{14,0}};
static const glyph_stroke_t stroke_88_2[3] = {{14,21},{13,21},{0,0}};
static const glyph_stroke_t stroke_88_3[3] = {{14,21},{1,0},{0,0}};
static const glyph_stroke_t *strokes_88[4] = {stroke_88_0, stroke_88_1, stroke_88_2, stroke_88_3};
static const uint8_t ncoords_88[4] = {3, 3, 3, 3};
static const glyph_stroke_t stroke_89_0[4] = {{0,21},{7,11},{7,0},{8,0}};
static const glyph_stroke_t stroke_89_1[3] = {{0,21},{1,21},{8,11}};
static const glyph_stroke_t stroke_89_2[3] = {{15,21},{14,21},{7,11}};
static const glyph_stroke_t stroke_89_3[3] = {{15,21},{8,11},{8,0}};
static const glyph_stroke_t *strokes_89[4] = {stroke_89_0, stroke_89_1, stroke_89_2, stroke_89_3};
static const uint8_t ncoords_89[4] = {4, 3, 3, 3};
static const glyph_stroke_t stroke_90_0[2] = {{13,21},{0,0}};
static const glyph_stroke_t stroke_90_1[2] = {{14,21},{1,0}};
static const glyph_stroke_t stroke_90_2[2] = {{0,21},{14,21}};
static const glyph_stroke_t stroke_90_3[3] = {{0,21},{0,20},{13,20}};
static const glyph_stroke_t stroke_90_4[3] = {{1,1},{14,1},{14,0}};
static const glyph_stroke_t stroke_90_5[2] = {{0,0},{14,0}};
static const glyph_stroke_t *strokes_90[6] = {stroke_90_0, stroke_90_1, stroke_90_2, stroke_90_3, stroke_90_4, stroke_90_5};
static const uint8_t ncoords_90[6] = {2, 2, 2, 3, 3, 2};
static const glyph_stroke_t stroke_91_0[2] = {{0,25},{0,-7}};
static const glyph_stroke_t stroke_91_1[2] = {{1,25},{1,-7}};
static const glyph_stroke_t stroke_91_2[2] = {{0,25},{7,25}};
static const glyph_stroke_t stroke_91_3[2] = {{0,-7},{7,-7}};
static const glyph_stroke_t *strokes_91[4] = {stroke_91_0, stroke_91_1, stroke_91_2, stroke_91_3};
static const uint8_t ncoords_91[4] = {2, 2, 2, 2};
static const glyph_stroke_t stroke_92_0[5] = {{0,21},{1,21},{14,-3},{13,-3},{0,21}};
static const glyph_stroke_t *strokes_92[1] = {stroke_92_0};
static const uint8_t ncoords_92[1] = {5};
static const glyph_stroke_t stroke_93_0[2] = {{6,25},{6,-7}};
static const glyph_stroke_t stroke_93_1[2] = {{7,25},{7,-7}};
static const glyph_stroke_t stroke_93_2[2] = {{0,25},{7,25}};
static const glyph_stroke_t stroke_93_3[2] = {{0,-7},{7,-7}};
static const glyph_stroke_t *strokes_93[4] = {stroke_93_0, stroke_93_1, stroke_93_2, stroke_93_3};
static const uint8_t ncoords_93[4] = {2, 2, 2, 2};
static const glyph_stroke_t stroke_94_0[3] = {{0,16},{8,23},{16,16}};
static const glyph_stroke_t stroke_94_1[3] = {{0,16},{8,22},{16,16}};
static const glyph_stroke_t *strokes_94[2] = {stroke_94_0, stroke_94_1};
static const uint8_t ncoords_94[2] = {3, 3};
static const glyph_stroke_t stroke_95_0[5] = {{0,-7},{0,-6},{20,-6},{20,-7},{0,-7}};
static const glyph_stroke_t *strokes_95[1] = {stroke_95_0};
static const uint8_t ncoords_95[1] = {5};
static const glyph_stroke_t stroke_96_0[2] = {{1,21},{6,15}};
static const glyph_stroke_t stroke_96_1[3] = {{1,21},{0,20},{6,15}};
static const glyph_stroke_t *strokes_96[2] = {stroke_96_0, stroke_96_1};
static const uint8_t ncoords_96[2] = {2, 3};
static const glyph_stroke_t stroke_97_0[3] = {{12,14},{12,0},{13,0}};
static const glyph_stroke_t stroke_97_1[3] = {{12,14},{13,14},{13,0}};
static const glyph_stroke_t stroke_97_2[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_97_3[12] = {{12,11},{8,13},{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{12,3}};
static const glyph_stroke_t *strokes_97[4] = {stroke_97_0, stroke_97_1, stroke_97_2, stroke_97_3};
static const uint8_t ncoords_97[4] = {3, 3, 14, 12};
static const glyph_stroke_t stroke_98_0[3] = {{0,21},{0,0},{1,0}};
static const glyph_stroke_t stroke_98_1[3] = {{0,21},{1,21},{1,0}};
static const glyph_stroke_t stroke_98_2[14] = {{1,11},{3,13},{5,14},{8,14},{10,13},{12,11},{13,8},{13,6},{12,3},{10,1},{8,0},{5,0},{3,1},{1,3}};
static const glyph_stroke_t stroke_98_3[12] = {{1,11},{5,13},{8,13},{10,12},{11,11},{12,8},{12,6},{11,3},{10,2},{8,1},{5,1},{1,3}};
static const glyph_stroke_t *strokes_98[4] = {stroke_98_0, stroke_98_1, stroke_98_2, stroke_98_3};
static const uint8_t ncoords_98[4] = {3, 3, 14, 12};
static const glyph_stroke_t stroke_99_0[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_99_1[16] = {{12,11},{11,10},{10,12},{8,13},{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{10,2},{11,4},{12,3}};
static const glyph_stroke_t *strokes_99[2] = {stroke_99_0, stroke_99_1};
static const uint8_t ncoords_99[2] = {14, 16};
static const glyph_stroke_t stroke_100_0[3] = {{12,21},{12,0},{13,0}};
static const glyph_stroke_t stroke_100_1[3] = {{12,21},{13,21},{13,0}};
static const glyph_stroke_t stroke_100_2[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_100_3[12] = {{12,11},{8,13},{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{12,3}};
static const glyph_stroke_t *strokes_100[4] = {stroke_100_0, stroke_100_1, stroke_100_2, stroke_100_3};
static const uint8_t ncoords_100[4] = {3, 3, 14, 12};
static const glyph_stroke_t stroke_101_0[17] = {{1,7},{12,7},{12,10},{11,12},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_101_1[17] = {{1,8},{11,8},{11,10},{10,12},{8,13},{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{10,2},{11,4},{12,3}};
static const glyph_stroke_t *strokes_101[2] = {stroke_101_0, stroke_101_1};
static const uint8_t ncoords_101[2] = {17, 17};
static const glyph_stroke_t stroke_102_0[6] = {{8,21},{6,21},{4,20},{3,17},{3,0},{4,0}};
static const glyph_stroke_t stroke_102_1[4] = {{8,21},{8,20},{6,20},{4,19}};
static const glyph_stroke_t stroke_102_2[3] = {{5,20},{4,17},{4,0}};
static const glyph_stroke_t stroke_102_3[3] = {{0,14},{7,14},{7,13}};
static const glyph_stroke_t stroke_102_4[3] = {{0,14},{0,13},{7,13}};
static const glyph_stroke_t *strokes_102[5] = {stroke_102_0, stroke_102_1, stroke_102_2, stroke_102_3, stroke_102_4};
static const uint8_t ncoords_102[5] = {6, 4, 3, 3, 3};
static const glyph_stroke_t stroke_103_0[10] = {{13,14},{12,14},{12,-1},{11,-4},{10,-5},{8,-6},{6,-6},{4,-5},{3,-4},{1,-4}};
static const glyph_stroke_t stroke_103_1[8] = {{13,14},{13,-1},{12,-4},{10,-6},{8,-7},{5,-7},{3,-6},{1,-4}};
static const glyph_stroke_t stroke_103_2[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_103_3[12] = {{12,11},{8,13},{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{12,3}};
static const glyph_stroke_t *strokes_103[4] = {stroke_103_0, stroke_103_1, stroke_103_2, stroke_103_3};
static const uint8_t ncoords_103[4] = {10, 8, 14, 12};
static const glyph_stroke_t stroke_104_0[3] = {{0,21},{0,0},{1,0}};
static const glyph_stroke_t stroke_104_1[3] = {{0,21},{1,21},{1,0}};
static const glyph_stroke_t stroke_104_2[7] = {{1,10},{4,13},{6,14},{9,14},{11,13},{12,10},{12,0}};
static const glyph_stroke_t stroke_104_3[8] = {{1,10},{4,12},{6,13},{8,13},{10,12},{11,10},{11,0},{12,0}};
static const glyph_stroke_t *strokes_104[4] = {stroke_104_0, stroke_104_1, stroke_104_2, stroke_104_3};
static const uint8_t ncoords_104[4] = {3, 3, 7, 8};
static const glyph_stroke_t stroke_105_0[9] = {{1,21},{0,20},{0,19},{1,18},{2,18},{3,19},{3,20},{2,21},{1,21}};
static const glyph_stroke_t stroke_105_1[5] = {{1,20},{1,19},{2,19},{2,20},{1,20}};
static const glyph_stroke_t stroke_105_2[3] = {{1,14},{1,0},{2,0}};
static const glyph_stroke_t stroke_105_3[3] = {{1,14},{2,14},{2,0}};
static const glyph_stroke_t *strokes_105[4] = {stroke_105_0, stroke_105_1, stroke_105_2, stroke_105_3};
static const uint8_t ncoords_105[4] = {9, 5, 3, 3};
static const glyph_stroke_t stroke_106_0[9] = {{1,21},{0,20},{0,19},{1,18},{2,18},{3,19},{3,20},{2,21},{1,21}};
static const glyph_stroke_t stroke_106_1[5] = {{1,20},{1,19},{2,19},{2,20},{1,20}};
static const glyph_stroke_t stroke_106_2[3] = {{1,14},{1,-7},{2,-7}};
static const glyph_stroke_t stroke_106_3[3] = {{1,14},{2,14},{2,-7}};
static const glyph_stroke_t *strokes_106[4] = {stroke_106_0, stroke_106_1, stroke_106_2, stroke_106_3};
static const uint8_t ncoords_106[4] = {9, 5, 3, 3};
static const glyph_stroke_t stroke_107_0[3] = {{0,21},{0,0},{1,0}};
static const glyph_stroke_t stroke_107_1[3] = {{0,21},{1,21},{1,0}};
static const glyph_stroke_t stroke_107_2[3] = {{12,14},{11,14},{1,4}};
static const glyph_stroke_t stroke_107_3[2] = {{12,14},{1,3}};
static const glyph_stroke_t stroke_107_4[3] = {{4,7},{10,0},{12,0}};
static const glyph_stroke_t stroke_107_5[2] = {{5,8},{12,0}};
static const glyph_stroke_t *strokes_107[6] = {stroke_107_0, stroke_107_1, stroke_107_2, stroke_107_3, stroke_107_4, stroke_107_5};
static const uint8_t ncoords_107[6] = {3, 3, 3, 2, 3, 2};
static const glyph_stroke_t stroke_108_0[3] = {{0,21},{0,0},{1,0}};
static const glyph_stroke_t stroke_108_1[3] = {{0,21},{1,21},{1,0}};
static const glyph_stroke_t *strokes_108[2] = {stroke_108_0, stroke_108_1};
static const uint8_t ncoords_108[2] = {3, 3};
static const glyph_stroke_t stroke_109_0[3] = {{0,14},{0,0},{1,0}};
static const glyph_stroke_t stroke_109_1[3] = {{0,14},{1,14},{1,0}};
static const glyph_stroke_t stroke_109_2[7] = {{1,10},{4,13},{6,14},{9,14},{11,13},{12,10},{12,0}};
static const glyph_stroke_t stroke_109_3[8] = {{1,10},{4,12},{6,13},{8,13},{10,12},{11,10},{11,0},{12,0}};
static const glyph_stroke_t stroke_109_4[7] = {{12,10},{15,13},{17,14},{20,14},{22,13},{23,10},{23,0}};
static const glyph_stroke_t stroke_109_5[8] = {{12,10},{15,12},{17,13},{19,13},{21,12},{22,10},{22,0},{23,0}};
static const glyph_stroke_t *strokes_109[6] = {stroke_109_0, stroke_109_1, stroke_109_2, stroke_109_3, stroke_109_4, stroke_109_5};
static const uint8_t ncoords_109[6] = {3, 3, 7, 8, 7, 8};
static const glyph_stroke_t stroke_110_0[3] = {{0,14},{0,0},{1,0}};
static const glyph_stroke_t stroke_110_1[3] = {{0,14},{1,14},{1,0}};
static const glyph_stroke_t stroke_110_2[7] = {{1,10},{4,13},{6,14},{9,14},{11,13},{12,10},{12,0}};
static const glyph_stroke_t stroke_110_3[8] = {{1,10},{4,12},{6,13},{8,13},{10,12},{11,10},{11,0},{12,0}};
static const glyph_stroke_t *strokes_110[4] = {stroke_110_0, stroke_110_1, stroke_110_2, stroke_110_3};
static const uint8_t ncoords_110[4] = {3, 3, 7, 8};
static const glyph_stroke_t stroke_111_0[17] = {{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3},{13,6},{13,8},{12,11},{10,13},{8,14},{5,14}};
static const glyph_stroke_t stroke_111_1[17] = {{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{10,2},{11,3},{12,6},{12,8},{11,11},{10,12},{8,13},{5,13}};
static const glyph_stroke_t *strokes_111[2] = {stroke_111_0, stroke_111_1};
static const uint8_t ncoords_111[2] = {17, 17};
static const glyph_stroke_t stroke_112_0[3] = {{0,14},{0,-7},{1,-7}};
static const glyph_stroke_t stroke_112_1[3] = {{0,14},{1,14},{1,-7}};
static const glyph_stroke_t stroke_112_2[14] = {{1,11},{3,13},{5,14},{8,14},{10,13},{12,11},{13,8},{13,6},{12,3},{10,1},{8,0},{5,0},{3,1},{1,3}};
static const glyph_stroke_t stroke_112_3[12] = {{1,11},{5,13},{8,13},{10,12},{11,11},{12,8},{12,6},{11,3},{10,2},{8,1},{5,1},{1,3}};
static const glyph_stroke_t *strokes_112[4] = {stroke_112_0, stroke_112_1, stroke_112_2, stroke_112_3};
static const uint8_t ncoords_112[4] = {3, 3, 14, 12};
static const glyph_stroke_t stroke_113_0[3] = {{12,14},{12,-7},{13,-7}};
static const glyph_stroke_t stroke_113_1[3] = {{12,14},{13,14},{13,-7}};
static const glyph_stroke_t stroke_113_2[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_113_3[12] = {{12,11},{8,13},{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{12,3}};
static const glyph_stroke_t *strokes_113[4] = {stroke_113_0, stroke_113_1, stroke_113_2, stroke_113_3};
static const uint8_t ncoords_113[4] = {3, 3, 14, 12};
static const glyph_stroke_t stroke_114_0[3] = {{0,14},{0,0},{1,0}};
static const glyph_stroke_t stroke_114_1[3] = {{0,14},{1,14},{1,0}};
static const glyph_stroke_t stroke_114_2[5] = {{1,8},{2,11},{4,13},{6,14},{9,14}};
static const glyph_stroke_t stroke_114_3[6] = {{1,8},{2,10},{4,12},{6,13},{9,13},{9,14}};
static const glyph_stroke_t *strokes_114[4] = {stroke_114_0, stroke_114_1, stroke_114_2, stroke_114_3};
static const uint8_t ncoords_114[4] = {3, 3, 5, 6};
static const glyph_stroke_t stroke_115_0[10] = {{11,11},{10,13},{7,14},{4,14},{1,13},{0,11},{1,9},{3,8},{8,6},{10,5}};
static const glyph_stroke_t stroke_115_1[4] = {{9,6},{10,4},{10,3},{9,1}};
static const glyph_stroke_t stroke_115_2[4] = {{10,2},{7,1},{4,1},{1,2}};
static const glyph_stroke_t stroke_115_3[3] = {{2,1},{1,3},{0,3}};
static const glyph_stroke_t stroke_115_4[3] = {{11,11},{10,11},{9,13}};
static const glyph_stroke_t stroke_115_5[4] = {{10,12},{7,13},{4,13},{1,12}};
static const glyph_stroke_t stroke_115_6[3] = {{2,13},{1,11},{2,9}};
static const glyph_stroke_t stroke_115_7[11] = {{1,10},{3,9},{8,7},{10,6},{11,4},{11,3},{10,1},{7,0},{4,0},{1,1},{0,3}};
static const glyph_stroke_t *strokes_115[8] = {stroke_115_0, stroke_115_1, stroke_115_2, stroke_115_3, stroke_115_4, stroke_115_5, stroke_115_6, stroke_115_7};
static const uint8_t ncoords_115[8] = {10, 4, 4, 3, 3, 4, 3, 11};
static const glyph_stroke_t stroke_116_0[3] = {{3,21},{3,0},{4,0}};
static const glyph_stroke_t stroke_116_1[3] = {{3,21},{4,21},{4,0}};
static const glyph_stroke_t stroke_116_2[3] = {{0,14},{7,14},{7,13}};
static const glyph_stroke_t stroke_116_3[3] = {{0,14},{0,13},{7,13}};
static const glyph_stroke_t *strokes_116[4] = {stroke_116_0, stroke_116_1, stroke_116_2, stroke_116_3};
static const uint8_t ncoords_116[4] = {3, 3, 3, 3};
static const glyph_stroke_t stroke_117_0[7] = {{0,14},{0,4},{1,1},{3,0},{6,0},{8,1},{11,4}};
static const glyph_stroke_t stroke_117_1[8] = {{0,14},{1,14},{1,4},{2,2},{4,1},{6,1},{8,2},{11,4}};
static const glyph_stroke_t stroke_117_2[3] = {{11,14},{11,0},{12,0}};
static const glyph_stroke_t stroke_117_3[3] = {{11,14},{12,14},{12,0}};
static const glyph_stroke_t *strokes_117[4] = {stroke_117_0, stroke_117_1, stroke_117_2, stroke_117_3};
static const uint8_t ncoords_117[4] = {7, 8, 3, 3};
static const glyph_stroke_t stroke_118_0[2] = {{0,14},{6,0}};
static const glyph_stroke_t stroke_118_1[3] = {{0,14},{1,14},{6,2}};
static const glyph_stroke_t stroke_118_2[3] = {{12,14},{11,14},{6,2}};
static const glyph_stroke_t stroke_118_3[2] = {{12,14},{6,0}};
static const glyph_stroke_t *strokes_118[4] = {stroke_118_0, stroke_118_1, stroke_118_2, stroke_118_3};
static const uint8_t ncoords_118[4] = {2, 3, 3, 2};
static const glyph_stroke_t stroke_119_0[2] = {{0,14},{5,0}};
static const glyph_stroke_t stroke_119_1[3] = {{0,14},{1,14},{5,3}};
static const glyph_stroke_t stroke_119_2[2] = {{9,14},{5,3}};
static const glyph_stroke_t stroke_119_3[2] = {{9,11},{5,0}};
static const glyph_stroke_t stroke_119_4[2] = {{9,11},{13,0}};
static const glyph_stroke_t stroke_119_5[2] = {{9,14},{13,3}};
static const glyph_stroke_t stroke_119_6[3] = {{18,14},{17,14},{13,3}};
static const glyph_stroke_t stroke_119_7[2] = {{18,14},{13,0}};
static const glyph_stroke_t *strokes_119[8] = {stroke_119_0, stroke_119_1, stroke_119_2, stroke_119_3, stroke_119_4, stroke_119_5, stroke_119_6, stroke_119_7};
static const uint8_t ncoords_119[8] = {2, 3, 2, 2, 2, 2, 3, 2};
static const glyph_stroke_t stroke_120_0[3] = {{0,14},{11,0},{12,0}};
static const glyph_stroke_t stroke_120_1[3] = {{0,14},{1,14},{12,0}};
static const glyph_stroke_t stroke_120_2[3] = {{12,14},{11,14},{0,0}};
static const glyph_stroke_t stroke_120_3[3] = {{12,14},{1,0},{0,0}};
static const glyph_stroke_t *strokes_120[4] = {stroke_120_0, stroke_120_1, stroke_120_2, stroke_120_3};
static const uint8_t ncoords_120[4] = {3, 3, 3, 3};
static const glyph_stroke_t stroke_121_0[2] = {{0,14},{6,0}};
static const glyph_stroke_t stroke_121_1[3] = {{0,14},{1,14},{6,2}};
static const glyph_stroke_t stroke_121_2[4] = {{12,14},{11,14},{6,2},{2,-7}};
static const glyph_stroke_t stroke_121_3[4] = {{12,14},{6,0},{3,-7},{2,-7}};
static const glyph_stroke_t *strokes_121[4] = {stroke_121_0, stroke_121_1, stroke_121_2, stroke_121_3};
static const uint8_t ncoords_121[4] = {2, 3, 4, 4};
static const glyph_stroke_t stroke_122_0[2] = {{10,13},{0,0}};
static const glyph_stroke_t stroke_122_1[2] = {{12,14},{2,1}};
static const glyph_stroke_t stroke_122_2[2] = {{0,14},{12,14}};
static const glyph_stroke_t stroke_122_3[3] = {{0,14},{0,13},{10,13}};
static const glyph_stroke_t stroke_122_4[3] = {{2,1},{12,1},{12,0}};
static const glyph_stroke_t stroke_122_5[2] = {{0,0},{12,0}};
static const glyph_stroke_t *strokes_122[6] = {stroke_122_0, stroke_122_1, stroke_122_2, stroke_122_3, stroke_122_4, stroke_122_5};
static const uint8_t ncoords_122[6] = {2, 2, 2, 3, 3, 2};
static const glyph_stroke_t stroke_123_0[10] = {{5,25},{3,24},{2,23},{1,21},{1,19},{2,17},{3,16},{4,14},{4,12},{2,10}};
static const glyph_stroke_t stroke_123_1[17] = {{3,24},{2,22},{2,20},{3,18},{4,17},{5,15},{5,13},{4,11},{0,9},{4,7},{5,5},{5,3},{4,1},{3,0},{2,-2},{2,-4},{3,-6}};
static const glyph_stroke_t stroke_123_2[10] = {{2,8},{4,6},{4,4},{3,2},{2,1},{1,-1},{1,-3},{2,-5},{3,-6},{5,-7}};
static const glyph_stroke_t *strokes_123[3] = {stroke_123_0, stroke_123_1, stroke_123_2};
static const uint8_t ncoords_123[3] = {10, 17, 10};
static const glyph_stroke_t stroke_124_0[5] = {{0,25},{1,25},{1,-7},{0,-7},{0,25}};
static const glyph_stroke_t *strokes_124[1] = {stroke_124_0};
static const uint8_t ncoords_124[1] = {5};
static const glyph_stroke_t stroke_125_0[10] = {{0,25},{2,24},{3,23},{4,21},{4,19},{3,17},{2,16},{1,14},{1,12},{3,10}};
static const glyph_stroke_t stroke_125_1[17] = {{2,24},{3,22},{3,20},{2,18},{1,17},{0,15},{0,13},{1,11},{5,9},{1,7},{0,5},{0,3},{1,1},{2,0},{3,-2},{3,-4},{2,-6}};
static const glyph_stroke_t stroke_125_2[10] = {{3,8},{1,6},{1,4},{2,2},{3,1},{4,-1},{4,-3},{3,-5},{2,-6},{0,-7}};
static const glyph_stroke_t *strokes_125[3] = {stroke_125_0, stroke_125_1, stroke_125_2};
static const uint8_t ncoords_125[3] = {10, 17, 10};
static const glyph_stroke_t stroke_126_0[11] = {{0,6},{0,8},{1,11},{3,12},{5,12},{7,11},{11,8},{13,7},{15,7},{17,8},{18,10}};
static const glyph_stroke_t stroke_126_1[11] = {{0,8},{1,10},{3,11},{5,11},{7,10},{11,7},{13,6},{15,6},{17,7},{18,10},{18,12}};
static const glyph_stroke_t *strokes_126[2] = {stroke_126_0, stroke_126_1};
static const uint8_t ncoords_126[2] = {11, 11};
static const glyph_stroke_t stroke_127_0[34] = {{0,21},{0,0},{1,0},{1,21},{2,21},{2,0},{3,0},{3,21},{4,21},{4,0},{5,0},{5,21},{6,21},{6,0},{7,0},{7,21},{8,21},{8,0},{9,0},{9,21},{10,21},{10,0},{11,0},{11,21},{12,21},{12,0},{13,0},{13,21},{14,21},{14,0},{15,0},{15,21},{16,21},{16,0}};
static const glyph_stroke_t *strokes_127[1] = {stroke_127_0};
static const uint8_t ncoords_127[1] = {34};
static const glyph_stroke_t stroke_192_0[2] = {{8,21},{0,0}};
static const glyph_stroke_t stroke_192_1[3] = {{8,18},{1,0},{0,0}};
static const glyph_stroke_t stroke_192_2[3] = {{8,18},{15,0},{16,0}};
static const glyph_stroke_t stroke_192_3[2] = {{8,21},{16,0}};
static const glyph_stroke_t stroke_192_4[2] = {{3,6},{13,6}};
static const glyph_stroke_t stroke_192_5[2] = {{2,5},{14,5}};
static const glyph_stroke_t stroke_192_6[4] = {{4,29},{3,28},{9,24},{4,29}};
static const glyph_stroke_t *strokes_192[7] = {stroke_192_0, stroke_192_1, stroke_192_2, stroke_192_3, stroke_192_4, stroke_192_5, stroke_192_6};
static const uint8_t ncoords_192[7] = {2, 3, 3, 2, 2, 2, 4};
static const glyph_stroke_t stroke_193_0[2] = {{8,21},{0,0}};
static const glyph_stroke_t stroke_193_1[3] = {{8,18},{1,0},{0,0}};
static const glyph_stroke_t stroke_193_2[3] = {{8,18},{15,0},{16,0}};
static const glyph_stroke_t stroke_193_3[2] = {{8,21},{16,0}};
static const glyph_stroke_t stroke_193_4[2] = {{3,6},{13,6}};
static const glyph_stroke_t stroke_193_5[2] = {{2,5},{14,5}};
static const glyph_stroke_t stroke_193_6[4] = {{12,29},{13,28},{7,24},{12,29}};
static const glyph_stroke_t *strokes_193[7] = {stroke_193_0, stroke_193_1, stroke_193_2, stroke_193_3, stroke_193_4, stroke_193_5, stroke_193_6};
static const uint8_t ncoords_193[7] = {2, 3, 3, 2, 2, 2, 4};
static const glyph_stroke_t stroke_194_0[2] = {{8,21},{0,0}};
static const glyph_stroke_t stroke_194_1[3] = {{8,18},{1,0},{0,0}};
static const glyph_stroke_t stroke_194_2[3] = {{8,18},{15,0},{16,0}};
static const glyph_stroke_t stroke_194_3[2] = {{8,21},{16,0}};
static const glyph_stroke_t stroke_194_4[2] = {{3,6},{13,6}};
static const glyph_stroke_t stroke_194_5[2] = {{2,5},{14,5}};
static const glyph_stroke_t stroke_194_6[5] = {{4,23},{8,27},{12,23},{8,26},{4,23}};
static const glyph_stroke_t *strokes_194[7] = {stroke_194_0, stroke_194_1, stroke_194_2, stroke_194_3, stroke_194_4, stroke_194_5, stroke_194_6};
static const uint8_t ncoords_194[7] = {2, 3, 3, 2, 2, 2, 5};
static const glyph_stroke_t stroke_195_0[2] = {{8,21},{0,0}};
static const glyph_stroke_t stroke_195_1[3] = {{8,18},{1,0},{0,0}};
static const glyph_stroke_t stroke_195_2[3] = {{8,18},{15,0},{16,0}};
static const glyph_stroke_t stroke_195_3[2] = {{8,21},{16,0}};
static const glyph_stroke_t stroke_195_4[2] = {{3,6},{13,6}};
static const glyph_stroke_t stroke_195_5[2] = {{2,5},{14,5}};
static const glyph_stroke_t stroke_195_6[6] = {{5,24},{6,25},{7,25},{9,24},{10,24},{11,25}};
static const glyph_stroke_t stroke_195_7[6] = {{6,25},{7,26},{8,26},{10,25},{11,25},{12,26}};
static const glyph_stroke_t *strokes_195[8] = {stroke_195_0, stroke_195_1, stroke_195_2, stroke_195_3, stroke_195_4, stroke_195_5, stroke_195_6, stroke_195_7};
static const uint8_t ncoords_195[8] = {2, 3, 3, 2, 2, 2, 6, 6};
static const glyph_stroke_t stroke_196_0[2] = {{8,21},{0,0}};
static const glyph_stroke_t stroke_196_1[3] = {{8,18},{1,0},{0,0}};
static const glyph_stroke_t stroke_196_2[3] = {{8,18},{15,0},{16,0}};
static const glyph_stroke_t stroke_196_3[2] = {{8,21},{16,0}};
static const glyph_stroke_t stroke_196_4[2] = {{3,6},{13,6}};
static const glyph_stroke_t stroke_196_5[2] = {{2,5},{14,5}};
static const glyph_stroke_t stroke_196_6[9] = {{10,26},{9,25},{9,24},{10,23},{11,23},{12,24},{12,25},{11,26},{10,26}};
static const glyph_stroke_t stroke_196_7[5] = {{10,25},{10,24},{11,24},{11,25},{10,25}};
static const glyph_stroke_t stroke_196_8[9] = {{5,26},{4,25},{4,24},{5,23},{6,23},{7,24},{7,25},{6,26},{5,26}};
static const glyph_stroke_t stroke_196_9[5] = {{5,25},{5,24},{6,24},{6,25},{5,25}};
static const glyph_stroke_t *strokes_196[10] = {stroke_196_0, stroke_196_1, stroke_196_2, stroke_196_3, stroke_196_4, stroke_196_5, stroke_196_6, stroke_196_7, stroke_196_8, stroke_196_9};
static const uint8_t ncoords_196[10] = {2, 3, 3, 2, 2, 2, 9, 5, 9, 5};
static const glyph_stroke_t stroke_197_0[2] = {{8,21},{0,0}};
static const glyph_stroke_t stroke_197_1[3] = {{8,18},{1,0},{0,0}};
static const glyph_stroke_t stroke_197_2[3] = {{8,18},{15,0},{16,0}};
static const glyph_stroke_t stroke_197_3[2] = {{8,21},{16,0}};
static const glyph_stroke_t stroke_197_4[2] = {{3,6},{13,6}};
static const glyph_stroke_t stroke_197_5[2] = {{2,5},{14,5}};
static const glyph_stroke_t stroke_197_6[9] = {{8,21},{10,22},{11,24},{10,26},{8,27},{6,26},{5,24},{6,22},{8,21}};
static const glyph_stroke_t stroke_197_7[9] = {{6,25},{6,23},{7,22},{9,22},{10,23},{10,25},{9,26},{7,26},{6,25}};
static const glyph_stroke_t *strokes_197[8] = {stroke_197_0, stroke_197_1, stroke_197_2, stroke_197_3, stroke_197_4, stroke_197_5, stroke_197_6, stroke_197_7};
static const uint8_t ncoords_197[8] = {2, 3, 3, 2, 2, 2, 9, 9};
static const glyph_stroke_t stroke_198_0[2] = {{8,21},{0,0}};
static const glyph_stroke_t stroke_198_1[3] = {{8,18},{1,0},{0,0}};
static const glyph_stroke_t stroke_198_2[2] = {{3,6},{8,6}};
static const glyph_stroke_t stroke_198_3[2] = {{2,5},{8,5}};
static const glyph_stroke_t stroke_198_4[2] = {{8,21},{8,0}};
static const glyph_stroke_t stroke_198_5[2] = {{9,20},{9,1}};
static const glyph_stroke_t stroke_198_6[2] = {{8,21},{18,21}};
static const glyph_stroke_t stroke_198_7[3] = {{9,20},{18,20},{18,21}};
static const glyph_stroke_t stroke_198_8[3] = {{9,11},{14,11},{14,10}};
static const glyph_stroke_t stroke_198_9[2] = {{9,10},{14,10}};
static const glyph_stroke_t stroke_198_10[3] = {{9,1},{18,1},{18,0}};
static const glyph_stroke_t stroke_198_11[2] = {{8,0},{18,0}};
static const glyph_stroke_t *strokes_198[12] = {stroke_198_0, stroke_198_1, stroke_198_2, stroke_198_3, stroke_198_4, stroke_198_5, stroke_198_6, stroke_198_7, stroke_198_8, stroke_198_9, stroke_198_10, stroke_198_11};
static const uint8_t ncoords_198[12] = {2, 3, 2, 2, 2, 2, 2, 3, 3, 2, 3, 2};
static const glyph_stroke_t stroke_57543_0[18] = {{15,16},{14,18},{12,20},{10,21},{6,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3},{4,1},{6,0},{10,0},{12,1},{14,3},{15,5}};
static const glyph_stroke_t stroke_57543_1[18] = {{15,16},{14,16},{13,18},{12,19},{10,20},{6,20},{4,19},{2,16},{1,13},{1,8},{2,5},{4,2},{6,1},{10,1},{12,2},{13,3},{14,5},{15,5}};
static const glyph_stroke_t stroke_57543_2[5] = {{8,0},{8,-1},{9,-2},{9,-3},{7,-3}};
static const glyph_stroke_t stroke_57543_3[7] = {{9,0},{9,-1},{10,-2},{10,-3},{9,-4},{8,-4},{7,-3}};
static const glyph_stroke_t *strokes_57543[4] = {stroke_57543_0, stroke_57543_1, stroke_57543_2, stroke_57543_3};
static const uint8_t ncoords_57543[4] = {18, 18, 5, 7};
static const glyph_stroke_t stroke_200_0[2] = {{0,21},{0,0}};
static const glyph_stroke_t stroke_200_1[2] = {{1,20},{1,1}};
static const glyph_stroke_t stroke_200_2[2] = {{0,21},{12,21}};
static const glyph_stroke_t stroke_200_3[3] = {{1,20},{12,20},{12,21}};
static const glyph_stroke_t stroke_200_4[3] = {{1,11},{7,11},{7,10}};
static const glyph_stroke_t stroke_200_5[2] = {{1,10},{7,10}};
static const glyph_stroke_t stroke_200_6[3] = {{1,1},{12,1},{12,0}};
static const glyph_stroke_t stroke_200_7[2] = {{0,0},{12,0}};
static const glyph_stroke_t stroke_200_8[4] = {{4,29},{3,28},{9,24},{4,29}};
static const glyph_stroke_t *strokes_200[9] = {stroke_200_0, stroke_200_1, stroke_200_2, stroke_200_3, stroke_200_4, stroke_200_5, stroke_200_6, stroke_200_7, stroke_200_8};
static const uint8_t ncoords_200[9] = {2, 2, 2, 3, 3, 2, 3, 2, 4};
static const glyph_stroke_t stroke_201_0[2] = {{0,21},{0,0}};
static const glyph_stroke_t stroke_201_1[2] = {{1,20},{1,1}};
static const glyph_stroke_t stroke_201_2[2] = {{0,21},{12,21}};
static const glyph_stroke_t stroke_201_3[3] = {{1,20},{12,20},{12,21}};
static const glyph_stroke_t stroke_201_4[3] = {{1,11},{7,11},{7,10}};
static const glyph_stroke_t stroke_201_5[2] = {{1,10},{7,10}};
static const glyph_stroke_t stroke_201_6[3] = {{1,1},{12,1},{12,0}};
static const glyph_stroke_t stroke_201_7[2] = {{0,0},{12,0}};
static const glyph_stroke_t stroke_201_8[4] = {{9,29},{10,28},{4,24},{9,29}};
static const glyph_stroke_t *strokes_201[9] = {stroke_201_0, stroke_201_1, stroke_201_2, stroke_201_3, stroke_201_4, stroke_201_5, stroke_201_6, stroke_201_7, stroke_201_8};
static const uint8_t ncoords_201[9] = {2, 2, 2, 3, 3, 2, 3, 2, 4};
static const glyph_stroke_t stroke_202_0[2] = {{0,21},{0,0}};
static const glyph_stroke_t stroke_202_1[2] = {{1,20},{1,1}};
static const glyph_stroke_t stroke_202_2[2] = {{0,21},{12,21}};
static const glyph_stroke_t stroke_202_3[3] = {{1,20},{12,20},{12,21}};
static const glyph_stroke_t stroke_202_4[3] = {{1,11},{7,11},{7,10}};
static const glyph_stroke_t stroke_202_5[2] = {{1,10},{7,10}};
static const glyph_stroke_t stroke_202_6[3] = {{1,1},{12,1},{12,0}};
static const glyph_stroke_t stroke_202_7[2] = {{0,0},{12,0}};
static const glyph_stroke_t stroke_202_8[5] = {{2,23},{6,27},{10,23},{6,26},{2,23}};
static const glyph_stroke_t *strokes_202[9] = {stroke_202_0, stroke_202_1, stroke_202_2, stroke_202_3, stroke_202_4, stroke_202_5, stroke_202_6, stroke_202_7, stroke_202_8};
static const uint8_t ncoords_202[9] = {2, 2, 2, 3, 3, 2, 3, 2, 5};
static const glyph_stroke_t stroke_203_0[2] = {{0,21},{0,0}};
static const glyph_stroke_t stroke_203_1[2] = {{1,20},{1,1}};
static const glyph_stroke_t stroke_203_2[2] = {{0,21},{12,21}};
static const glyph_stroke_t stroke_203_3[3] = {{1,20},{12,20},{12,21}};
static const glyph_stroke_t stroke_203_4[3] = {{1,11},{7,11},{7,10}};
static const glyph_stroke_t stroke_203_5[2] = {{1,10},{7,10}};
static const glyph_stroke_t stroke_203_6[3] = {{1,1},{12,1},{12,0}};
static const glyph_stroke_t stroke_203_7[2] = {{0,0},{12,0}};
static const glyph_stroke_t stroke_203_8[9] = {{8,26},{7,25},{7,24},{8,23},{9,23},{10,24},{10,25},{9,26},{8,26}};
static const glyph_stroke_t stroke_203_9[5] = {{8,25},{8,24},{9,24},{9,25},{8,25}};
static const glyph_stroke_t stroke_203_10[9] = {{3,26},{2,25},{2,24},{3,23},{4,23},{5,24},{5,25},{4,26},{3,26}};
static const glyph_stroke_t stroke_203_11[5] = {{3,25},{3,24},{4,24},{4,25},{3,25}};
static const glyph_stroke_t *strokes_203[12] = {stroke_203_0, stroke_203_1, stroke_203_2, stroke_203_3, stroke_203_4, stroke_203_5, stroke_203_6, stroke_203_7, stroke_203_8, stroke_203_9, stroke_203_10, stroke_203_11};
static const uint8_t ncoords_203[12] = {2, 2, 2, 3, 3, 2, 3, 2, 9, 5, 9, 5};
static const glyph_stroke_t stroke_204_0[3] = {{0,21},{0,0},{1,0}};
static const glyph_stroke_t stroke_204_1[3] = {{0,21},{1,21},{1,0}};
static const glyph_stroke_t stroke_204_2[4] = {{-2,29},{-3,28},{3,24},{-2,29}};
static const glyph_stroke_t *strokes_204[3] = {stroke_204_0, stroke_204_1, stroke_204_2};
static const uint8_t ncoords_204[3] = {3, 3, 4};
static const glyph_stroke_t stroke_205_0[3] = {{0,21},{0,0},{1,0}};
static const glyph_stroke_t stroke_205_1[3] = {{0,21},{1,21},{1,0}};
static const glyph_stroke_t stroke_205_2[4] = {{3,29},{4,28},{-2,24},{3,29}};
static const glyph_stroke_t *strokes_205[3] = {stroke_205_0, stroke_205_1, stroke_205_2};
static const uint8_t ncoords_205[3] = {3, 3, 4};
static const glyph_stroke_t stroke_206_0[3] = {{0,21},{0,0},{1,0}};
static const glyph_stroke_t stroke_206_1[3] = {{0,21},{1,21},{1,0}};
static const glyph_stroke_t stroke_206_2[5] = {{-3,23},{1,27},{5,23},{1,26},{-3,23}};
static const glyph_stroke_t *strokes_206[3] = {stroke_206_0, stroke_206_1, stroke_206_2};
static const uint8_t ncoords_206[3] = {3, 3, 5};
static const glyph_stroke_t stroke_207_0[3] = {{0,21},{0,0},{1,0}};
static const glyph_stroke_t stroke_207_1[3] = {{0,21},{1,21},{1,0}};
static const glyph_stroke_t stroke_207_2[9] = {{3,26},{2,25},{2,24},{3,23},{4,23},{5,24},{5,25},{4,26},{3,26}};
static const glyph_stroke_t stroke_207_3[5] = {{3,25},{3,24},{4,24},{4,25},{3,25}};
static const glyph_stroke_t stroke_207_4[9] = {{-2,26},{-3,25},{-3,24},{-2,23},{-1,23},{0,24},{0,25},{-1,26},{-2,26}};
static const glyph_stroke_t stroke_207_5[5] = {{-2,25},{-2,24},{-1,24},{-1,25},{-2,25}};
static const glyph_stroke_t *strokes_207[6] = {stroke_207_0, stroke_207_1, stroke_207_2, stroke_207_3, stroke_207_4, stroke_207_5};
static const uint8_t ncoords_207[6] = {3, 3, 9, 5, 9, 5};
static const glyph_stroke_t stroke_57552_0[2] = {{0,21},{0,0}};
static const glyph_stroke_t stroke_57552_1[2] = {{1,20},{1,1}};
static const glyph_stroke_t stroke_57552_2[12] = {{0,21},{7,21},{10,20},{12,18},{13,16},{14,13},{14,8},{13,5},{12,3},{10,1},{7,0},{0,0}};
static const glyph_stroke_t stroke_57552_3[12] = {{1,20},{7,20},{10,19},{11,18},{12,16},{13,13},{13,8},{12,5},{11,3},{10,2},{7,1},{1,1}};
static const glyph_stroke_t stroke_57552_4[5] = {{-2,10},{-2,11},{4,11},{4,10},{-2,10}};
static const glyph_stroke_t *strokes_57552[5] = {stroke_57552_0, stroke_57552_1, stroke_57552_2, stroke_57552_3, stroke_57552_4};
static const uint8_t ncoords_57552[5] = {2, 2, 12, 12, 5};
static const glyph_stroke_t stroke_209_0[2] = {{0,21},{0,0}};
static const glyph_stroke_t stroke_209_1[3] = {{1,18},{1,0},{0,0}};
static const glyph_stroke_t stroke_209_2[2] = {{1,18},{14,0}};
static const glyph_stroke_t stroke_209_3[2] = {{0,21},{13,3}};
static const glyph_stroke_t stroke_209_4[2] = {{13,21},{13,3}};
static const glyph_stroke_t stroke_209_5[3] = {{13,21},{14,21},{14,0}};
static const glyph_stroke_t stroke_209_6[6] = {{4,24},{5,25},{6,25},{8,24},{9,24},{10,25}};
static const glyph_stroke_t stroke_209_7[6] = {{5,25},{6,26},{7,26},{9,25},{10,25},{11,26}};
static const glyph_stroke_t *strokes_209[8] = {stroke_209_0, stroke_209_1, stroke_209_2, stroke_209_3, stroke_209_4, stroke_209_5, stroke_209_6, stroke_209_7};
static const uint8_t ncoords_209[8] = {2, 3, 2, 2, 2, 3, 6, 6};
static const glyph_stroke_t stroke_210_0[21] = {{6,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3},{4,1},{6,0},{10,0},{12,1},{14,3},{15,5},{16,8},{16,13},{15,16},{14,18},{12,20},{10,21},{6,21}};
static const glyph_stroke_t stroke_210_1[17] = {{7,20},{4,19},{2,16},{1,13},{1,8},{2,5},{4,2},{7,1},{9,1},{12,2},{14,5},{15,8},{15,13},{14,16},{12,19},{9,20},{7,20}};
static const glyph_stroke_t stroke_210_2[4] = {{4,29},{3,28},{9,24},{4,29}};
static const glyph_stroke_t *strokes_210[3] = {stroke_210_0, stroke_210_1, stroke_210_2};
static const uint8_t ncoords_210[3] = {21, 17, 4};
static const glyph_stroke_t stroke_211_0[21] = {{6,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3},{4,1},{6,0},{10,0},{12,1},{14,3},{15,5},{16,8},{16,13},{15,16},{14,18},{12,20},{10,21},{6,21}};
static const glyph_stroke_t stroke_211_1[17] = {{7,20},{4,19},{2,16},{1,13},{1,8},{2,5},{4,2},{7,1},{9,1},{12,2},{14,5},{15,8},{15,13},{14,16},{12,19},{9,20},{7,20}};
static const glyph_stroke_t stroke_211_2[4] = {{12,29},{13,28},{7,24},{12,29}};
static const glyph_stroke_t *strokes_211[3] = {stroke_211_0, stroke_211_1, stroke_211_2};
static const uint8_t ncoords_211[3] = {21, 17, 4};
static const glyph_stroke_t stroke_212_0[21] = {{6,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3},{4,1},{6,0},{10,0},{12,1},{14,3},{15,5},{16,8},{16,13},{15,16},{14,18},{12,20},{10,21},{6,21}};
static const glyph_stroke_t stroke_212_1[17] = {{7,20},{4,19},{2,16},{1,13},{1,8},{2,5},{4,2},{7,1},{9,1},{12,2},{14,5},{15,8},{15,13},{14,16},{12,19},{9,20},{7,20}};
static const glyph_stroke_t stroke_212_2[5] = {{4,23},{8,27},{12,23},{8,26},{4,23}};
static const glyph_stroke_t *strokes_212[3] = {stroke_212_0, stroke_212_1, stroke_212_2};
static const uint8_t ncoords_212[3] = {21, 17, 5};
static const glyph_stroke_t stroke_213_0[21] = {{6,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3},{4,1},{6,0},{10,0},{12,1},{14,3},{15,5},{16,8},{16,13},{15,16},{14,18},{12,20},{10,21},{6,21}};
static const glyph_stroke_t stroke_213_1[17] = {{7,20},{4,19},{2,16},{1,13},{1,8},{2,5},{4,2},{7,1},{9,1},{12,2},{14,5},{15,8},{15,13},{14,16},{12,19},{9,20},{7,20}};
static const glyph_stroke_t stroke_213_2[6] = {{5,24},{6,25},{7,25},{9,24},{10,24},{11,25}};
static const glyph_stroke_t stroke_213_3[6] = {{6,25},{7,26},{8,26},{10,25},{11,25},{12,26}};
static const glyph_stroke_t *strokes_213[4] = {stroke_213_0, stroke_213_1, stroke_213_2, stroke_213_3};
static const uint8_t ncoords_213[4] = {21, 17, 6, 6};
static const glyph_stroke_t stroke_214_0[21] = {{6,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3},{4,1},{6,0},{10,0},{12,1},{14,3},{15,5},{16,8},{16,13},{15,16},{14,18},{12,20},{10,21},{6,21}};
static const glyph_stroke_t stroke_214_1[17] = {{7,20},{4,19},{2,16},{1,13},{1,8},{2,5},{4,2},{7,1},{9,1},{12,2},{14,5},{15,8},{15,13},{14,16},{12,19},{9,20},{7,20}};
static const glyph_stroke_t stroke_214_2[9] = {{10,26},{9,25},{9,24},{10,23},{11,23},{12,24},{12,25},{11,26},{10,26}};
static const glyph_stroke_t stroke_214_3[5] = {{10,25},{10,24},{11,24},{11,25},{10,25}};
static const glyph_stroke_t stroke_214_4[9] = {{5,26},{4,25},{4,24},{5,23},{6,23},{7,24},{7,25},{6,26},{5,26}};
static const glyph_stroke_t stroke_214_5[5] = {{5,25},{5,24},{6,24},{6,25},{5,25}};
static const glyph_stroke_t *strokes_214[6] = {stroke_214_0, stroke_214_1, stroke_214_2, stroke_214_3, stroke_214_4, stroke_214_5};
static const uint8_t ncoords_214[6] = {21, 17, 9, 5, 9, 5};
static const glyph_stroke_t stroke_216_0[21] = {{6,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3},{4,1},{6,0},{10,0},{12,1},{14,3},{15,5},{16,8},{16,13},{15,16},{14,18},{12,20},{10,21},{6,21}};
static const glyph_stroke_t stroke_216_1[17] = {{7,20},{4,19},{2,16},{1,13},{1,8},{2,5},{4,2},{7,1},{9,1},{12,2},{14,5},{15,8},{15,13},{14,16},{12,19},{9,20},{7,20}};
static const glyph_stroke_t stroke_216_2[5] = {{0,0},{1,0},{16,21},{15,21},{0,0}};
static const glyph_stroke_t *strokes_216[3] = {stroke_216_0, stroke_216_1, stroke_216_2};
static const uint8_t ncoords_216[3] = {21, 17, 5};
static const glyph_stroke_t stroke_217_0[10] = {{0,21},{0,6},{1,3},{3,1},{6,0},{8,0},{11,1},{13,3},{14,6},{14,21}};
static const glyph_stroke_t stroke_217_1[12] = {{0,21},{1,21},{1,6},{2,3},{3,2},{6,1},{8,1},{11,2},{12,3},{13,6},{13,21},{14,21}};
static const glyph_stroke_t stroke_217_2[4] = {{4,29},{3,28},{9,24},{4,29}};
static const glyph_stroke_t *strokes_217[3] = {stroke_217_0, stroke_217_1, stroke_217_2};
static const uint8_t ncoords_217[3] = {10, 12, 4};
static const glyph_stroke_t stroke_218_0[10] = {{0,21},{0,6},{1,3},{3,1},{6,0},{8,0},{11,1},{13,3},{14,6},{14,21}};
static const glyph_stroke_t stroke_218_1[12] = {{0,21},{1,21},{1,6},{2,3},{3,2},{6,1},{8,1},{11,2},{12,3},{13,6},{13,21},{14,21}};
static const glyph_stroke_t stroke_218_2[4] = {{11,29},{12,28},{6,24},{11,29}};
static const glyph_stroke_t *strokes_218[3] = {stroke_218_0, stroke_218_1, stroke_218_2};
static const uint8_t ncoords_218[3] = {10, 12, 4};
static const glyph_stroke_t stroke_219_0[10] = {{0,21},{0,6},{1,3},{3,1},{6,0},{8,0},{11,1},{13,3},{14,6},{14,21}};
static const glyph_stroke_t stroke_219_1[12] = {{0,21},{1,21},{1,6},{2,3},{3,2},{6,1},{8,1},{11,2},{12,3},{13,6},{13,21},{14,21}};
static const glyph_stroke_t stroke_219_2[5] = {{3,23},{7,27},{11,23},{7,26},{3,23}};
static const glyph_stroke_t *strokes_219[3] = {stroke_219_0, stroke_219_1, stroke_219_2};
static const uint8_t ncoords_219[3] = {10, 12, 5};
static const glyph_stroke_t stroke_220_0[10] = {{0,21},{0,6},{1,3},{3,1},{6,0},{8,0},{11,1},{13,3},{14,6},{14,21}};
static const glyph_stroke_t stroke_220_1[12] = {{0,21},{1,21},{1,6},{2,3},{3,2},{6,1},{8,1},{11,2},{12,3},{13,6},{13,21},{14,21}};
static const glyph_stroke_t stroke_220_2[9] = {{9,26},{8,25},{8,24},{9,23},{10,23},{11,24},{11,25},{10,26},{9,26}};
static const glyph_stroke_t stroke_220_3[5] = {{9,25},{9,24},{10,24},{10,25},{9,25}};
static const glyph_stroke_t stroke_220_4[9] = {{4,26},{3,25},{3,24},{4,23},{5,23},{6,24},{6,25},{5,26},{4,26}};
static const glyph_stroke_t stroke_220_5[5] = {{4,25},{4,24},{5,24},{5,25},{4,25}};
static const glyph_stroke_t *strokes_220[6] = {stroke_220_0, stroke_220_1, stroke_220_2, stroke_220_3, stroke_220_4, stroke_220_5};
static const uint8_t ncoords_220[6] = {10, 12, 9, 5, 9, 5};
static const glyph_stroke_t stroke_221_0[4] = {{0,21},{7,11},{7,0},{8,0}};
static const glyph_stroke_t stroke_221_1[3] = {{0,21},{1,21},{8,11}};
static const glyph_stroke_t stroke_221_2[3] = {{15,21},{14,21},{7,11}};
static const glyph_stroke_t stroke_221_3[3] = {{15,21},{8,11},{8,0}};
static const glyph_stroke_t stroke_221_4[4] = {{11,29},{12,28},{6,24},{11,29}};
static const glyph_stroke_t *strokes_221[5] = {stroke_221_0, stroke_221_1, stroke_221_2, stroke_221_3, stroke_221_4};
static const uint8_t ncoords_221[5] = {4, 3, 3, 3, 4};
static const glyph_stroke_t stroke_57566_0[5] = {{0,21},{0,0},{1,0},{1,21},{0,21}};
static const glyph_stroke_t stroke_57566_1[10] = {{1,17},{7,17},{10,16},{12,14},{13,12},{13,9},{12,7},{10,5},{7,4},{1,4}};
static const glyph_stroke_t stroke_57566_2[10] = {{1,16},{7,16},{10,15},{11,14},{12,12},{12,9},{11,7},{10,6},{7,5},{1,5}};
static const glyph_stroke_t *strokes_57566[3] = {stroke_57566_0, stroke_57566_1, stroke_57566_2};
static const uint8_t ncoords_57566[3] = {5, 10, 10};
static const glyph_stroke_t stroke_224_0[3] = {{12,14},{12,0},{13,0}};
static const glyph_stroke_t stroke_224_1[3] = {{12,14},{13,14},{13,0}};
static const glyph_stroke_t stroke_224_2[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_224_3[12] = {{12,11},{8,13},{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{12,3}};
static const glyph_stroke_t stroke_224_4[4] = {{4,23},{3,22},{9,18},{4,23}};
static const glyph_stroke_t *strokes_224[5] = {stroke_224_0, stroke_224_1, stroke_224_2, stroke_224_3, stroke_224_4};
static const uint8_t ncoords_224[5] = {3, 3, 14, 12, 4};
static const glyph_stroke_t stroke_225_0[3] = {{12,14},{12,0},{13,0}};
static const glyph_stroke_t stroke_225_1[3] = {{12,14},{13,14},{13,0}};
static const glyph_stroke_t stroke_225_2[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_225_3[12] = {{12,11},{8,13},{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{12,3}};
static const glyph_stroke_t stroke_225_4[4] = {{10,23},{11,22},{5,18},{10,23}};
static const glyph_stroke_t *strokes_225[5] = {stroke_225_0, stroke_225_1, stroke_225_2, stroke_225_3, stroke_225_4};
static const uint8_t ncoords_225[5] = {3, 3, 14, 12, 4};
static const glyph_stroke_t stroke_226_0[3] = {{12,14},{12,0},{13,0}};
static const glyph_stroke_t stroke_226_1[3] = {{12,14},{13,14},{13,0}};
static const glyph_stroke_t stroke_226_2[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_226_3[12] = {{12,11},{8,13},{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{12,3}};
static const glyph_stroke_t stroke_226_4[5] = {{3,17},{7,21},{11,17},{7,20},{3,17}};
static const glyph_stroke_t *strokes_226[5] = {stroke_226_0, stroke_226_1, stroke_226_2, stroke_226_3, stroke_226_4};
static const uint8_t ncoords_226[5] = {3, 3, 14, 12, 5};
static const glyph_stroke_t stroke_227_0[3] = {{12,14},{12,0},{13,0}};
static const glyph_stroke_t stroke_227_1[3] = {{12,14},{13,14},{13,0}};
static const glyph_stroke_t stroke_227_2[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_227_3[12] = {{12,11},{8,13},{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{12,3}};
static const glyph_stroke_t stroke_227_4[6] = {{3,18},{4,19},{5,19},{7,18},{8,18},{9,19}};
static const glyph_stroke_t stroke_227_5[6] = {{4,19},{5,20},{6,20},{8,19},{9,19},{10,20}};
static const glyph_stroke_t *strokes_227[6] = {stroke_227_0, stroke_227_1, stroke_227_2, stroke_227_3, stroke_227_4, stroke_227_5};
static const uint8_t ncoords_227[6] = {3, 3, 14, 12, 6, 6};
static const glyph_stroke_t stroke_228_0[3] = {{12,14},{12,0},{13,0}};
static const glyph_stroke_t stroke_228_1[3] = {{12,14},{13,14},{13,0}};
static const glyph_stroke_t stroke_228_2[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_228_3[12] = {{12,11},{8,13},{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{12,3}};
static const glyph_stroke_t stroke_228_4[9] = {{9,20},{8,19},{8,18},{9,17},{10,17},{11,18},{11,19},{10,20},{9,20}};
static const glyph_stroke_t stroke_228_5[5] = {{9,19},{9,18},{10,18},{10,19},{9,19}};
static const glyph_stroke_t stroke_228_6[9] = {{4,20},{3,19},{3,18},{4,17},{5,17},{6,18},{6,19},{5,20},{4,20}};
static const glyph_stroke_t stroke_228_7[5] = {{4,19},{4,18},{5,18},{5,19},{4,19}};
static const glyph_stroke_t *strokes_228[8] = {stroke_228_0, stroke_228_1, stroke_228_2, stroke_228_3, stroke_228_4, stroke_228_5, stroke_228_6, stroke_228_7};
static const uint8_t ncoords_228[8] = {3, 3, 14, 12, 9, 5, 9, 5};
static const glyph_stroke_t stroke_229_0[3] = {{12,14},{12,0},{13,0}};
static const glyph_stroke_t stroke_229_1[3] = {{12,14},{13,14},{13,0}};
static const glyph_stroke_t stroke_229_2[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_229_3[12] = {{12,11},{8,13},{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{12,3}};
static const glyph_stroke_t stroke_229_4[9] = {{7,16},{9,17},{10,19},{9,21},{7,22},{5,21},{4,19},{5,17},{7,16}};
static const glyph_stroke_t stroke_229_5[9] = {{5,20},{5,18},{6,17},{8,17},{9,18},{9,20},{8,21},{6,21},{5,20}};
static const glyph_stroke_t *strokes_229[6] = {stroke_229_0, stroke_229_1, stroke_229_2, stroke_229_3, stroke_229_4, stroke_229_5};
static const uint8_t ncoords_229[6] = {3, 3, 14, 12, 9, 9};
static const glyph_stroke_t stroke_230_0[3] = {{12,14},{12,0},{13,0}};
static const glyph_stroke_t stroke_230_1[3] = {{12,14},{13,14},{13,0}};
static const glyph_stroke_t stroke_230_2[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_230_3[12] = {{12,11},{8,13},{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{12,3}};
static const glyph_stroke_t stroke_230_4[17] = {{13,7},{24,7},{24,10},{23,12},{22,13},{20,14},{17,14},{15,13},{13,11},{12,8},{12,6},{13,3},{15,1},{17,0},{20,0},{22,1},{24,3}};
static const glyph_stroke_t stroke_230_5[17] = {{13,8},{23,8},{23,10},{22,12},{20,13},{17,13},{15,12},{14,11},{13,8},{13,6},{14,3},{15,2},{17,1},{20,1},{22,2},{23,4},{24,3}};
static const glyph_stroke_t *strokes_230[6] = {stroke_230_0, stroke_230_1, stroke_230_2, stroke_230_3, stroke_230_4, stroke_230_5};
static const uint8_t ncoords_230[6] = {3, 3, 14, 12, 17, 17};
static const glyph_stroke_t stroke_57575_0[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_57575_1[16] = {{12,11},{11,10},{10,12},{8,13},{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{10,2},{11,4},{12,3}};
static const glyph_stroke_t stroke_57575_2[5] = {{6,0},{6,-1},{7,-2},{7,-3},{5,-3}};
static const glyph_stroke_t stroke_57575_3[7] = {{7,0},{7,-1},{8,-2},{8,-3},{7,-4},{6,-4},{5,-3}};
static const glyph_stroke_t *strokes_57575[4] = {stroke_57575_0, stroke_57575_1, stroke_57575_2, stroke_57575_3};
static const uint8_t ncoords_57575[4] = {14, 16, 5, 7};
static const glyph_stroke_t stroke_232_0[17] = {{1,7},{12,7},{12,10},{11,12},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_232_1[17] = {{1,8},{11,8},{11,10},{10,12},{8,13},{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{10,2},{11,4},{12,3}};
static const glyph_stroke_t stroke_232_2[4] = {{4,23},{3,22},{9,18},{4,23}};
static const glyph_stroke_t *strokes_232[3] = {stroke_232_0, stroke_232_1, stroke_232_2};
static const uint8_t ncoords_232[3] = {17, 17, 4};
static const glyph_stroke_t stroke_233_0[17] = {{1,7},{12,7},{12,10},{11,12},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_233_1[17] = {{1,8},{11,8},{11,10},{10,12},{8,13},{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{10,2},{11,4},{12,3}};
static const glyph_stroke_t stroke_233_2[4] = {{10,23},{11,22},{5,18},{10,23}};
static const glyph_stroke_t *strokes_233[3] = {stroke_233_0, stroke_233_1, stroke_233_2};
static const uint8_t ncoords_233[3] = {17, 17, 4};
static const glyph_stroke_t stroke_234_0[17] = {{1,7},{12,7},{12,10},{11,12},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_234_1[17] = {{1,8},{11,8},{11,10},{10,12},{8,13},{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{10,2},{11,4},{12,3}};
static const glyph_stroke_t stroke_234_2[5] = {{3,17},{7,21},{11,17},{7,20},{3,17}};
static const glyph_stroke_t *strokes_234[3] = {stroke_234_0, stroke_234_1, stroke_234_2};
static const uint8_t ncoords_234[3] = {17, 17, 5};
static const glyph_stroke_t stroke_235_0[17] = {{1,7},{12,7},{12,10},{11,12},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_235_1[17] = {{1,8},{11,8},{11,10},{10,12},{8,13},{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{10,2},{11,4},{12,3}};
static const glyph_stroke_t stroke_235_2[9] = {{9,20},{8,19},{8,18},{9,17},{10,17},{11,18},{11,19},{10,20},{9,20}};
static const glyph_stroke_t stroke_235_3[5] = {{9,19},{9,18},{10,18},{10,19},{9,19}};
static const glyph_stroke_t stroke_235_4[9] = {{4,20},{3,19},{3,18},{4,17},{5,17},{6,18},{6,19},{5,20},{4,20}};
static const glyph_stroke_t stroke_235_5[5] = {{4,19},{4,18},{5,18},{5,19},{4,19}};
static const glyph_stroke_t *strokes_235[6] = {stroke_235_0, stroke_235_1, stroke_235_2, stroke_235_3, stroke_235_4, stroke_235_5};
static const uint8_t ncoords_235[6] = {17, 17, 9, 5, 9, 5};
static const glyph_stroke_t stroke_236_0[5] = {{1,14},{1,0},{2,0},{2,14},{1,14}};
static const glyph_stroke_t stroke_236_1[4] = {{-1,23},{-2,22},{4,18},{-1,23}};
static const glyph_stroke_t *strokes_236[2] = {stroke_236_0, stroke_236_1};
static const uint8_t ncoords_236[2] = {5, 4};
static const glyph_stroke_t stroke_237_0[5] = {{1,14},{1,0},{2,0},{2,14},{1,14}};
static const glyph_stroke_t stroke_237_1[4] = {{4,23},{5,22},{-1,18},{4,23}};
static const glyph_stroke_t *strokes_237[2] = {stroke_237_0, stroke_237_1};
static const uint8_t ncoords_237[2] = {5, 4};
static const glyph_stroke_t stroke_238_0[5] = {{1,14},{1,0},{2,0},{2,14},{1,14}};
static const glyph_stroke_t stroke_238_1[5] = {{-2,17},{2,21},{6,17},{2,20},{-2,17}};
static const glyph_stroke_t *strokes_238[2] = {stroke_238_0, stroke_238_1};
static const uint8_t ncoords_238[2] = {5, 5};
static const glyph_stroke_t stroke_239_0[5] = {{1,14},{1,0},{2,0},{2,14},{1,14}};
static const glyph_stroke_t stroke_239_1[9] = {{4,20},{3,19},{3,18},{4,17},{5,17},{6,18},{6,19},{5,20},{4,20}};
static const glyph_stroke_t stroke_239_2[5] = {{4,19},{4,18},{5,18},{5,19},{4,19}};
static const glyph_stroke_t stroke_239_3[9] = {{-1,20},{-2,19},{-2,18},{-1,17},{0,17},{1,18},{1,19},{0,20},{-1,20}};
static const glyph_stroke_t stroke_239_4[5] = {{-1,19},{-1,18},{0,18},{0,19},{-1,19}};
static const glyph_stroke_t *strokes_239[5] = {stroke_239_0, stroke_239_1, stroke_239_2, stroke_239_3, stroke_239_4};
static const uint8_t ncoords_239[5] = {5, 9, 5, 9, 5};
static const glyph_stroke_t stroke_57584_0[36] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3},{13,6},{13,8},{12,11},{3,20},{3,19},{11,11},{10,12},{8,13},{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{10,2},{11,3},{12,6},{12,8},{11,11}};
static const glyph_stroke_t stroke_57584_1[5] = {{2,17},{9,19},{9,18},{2,16},{2,17}};
static const glyph_stroke_t *strokes_57584[2] = {stroke_57584_0, stroke_57584_1};
static const uint8_t ncoords_57584[2] = {36, 5};
static const glyph_stroke_t stroke_241_0[3] = {{0,14},{0,0},{1,0}};
static const glyph_stroke_t stroke_241_1[3] = {{0,14},{1,14},{1,0}};
static const glyph_stroke_t stroke_241_2[7] = {{1,10},{4,13},{6,14},{9,14},{11,13},{12,10},{12,0}};
static const glyph_stroke_t stroke_241_3[8] = {{1,10},{4,12},{6,13},{8,13},{10,12},{11,10},{11,0},{12,0}};
static const glyph_stroke_t stroke_241_4[6] = {{3,18},{4,19},{5,19},{7,18},{8,18},{9,19}};
static const glyph_stroke_t stroke_241_5[6] = {{4,19},{5,20},{6,20},{8,19},{9,19},{10,20}};
static const glyph_stroke_t *strokes_241[6] = {stroke_241_0, stroke_241_1, stroke_241_2, stroke_241_3, stroke_241_4, stroke_241_5};
static const uint8_t ncoords_241[6] = {3, 3, 7, 8, 6, 6};
static const glyph_stroke_t stroke_242_0[17] = {{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3},{13,6},{13,8},{12,11},{10,13},{8,14},{5,14}};
static const glyph_stroke_t stroke_242_1[17] = {{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{10,2},{11,3},{12,6},{12,8},{11,11},{10,12},{8,13},{5,13}};
static const glyph_stroke_t stroke_242_2[4] = {{4,23},{3,22},{9,18},{4,23}};
static const glyph_stroke_t *strokes_242[3] = {stroke_242_0, stroke_242_1, stroke_242_2};
static const uint8_t ncoords_242[3] = {17, 17, 4};
static const glyph_stroke_t stroke_243_0[17] = {{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3},{13,6},{13,8},{12,11},{10,13},{8,14},{5,14}};
static const glyph_stroke_t stroke_243_1[17] = {{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{10,2},{11,3},{12,6},{12,8},{11,11},{10,12},{8,13},{5,13}};
static const glyph_stroke_t stroke_243_2[4] = {{10,23},{11,22},{5,18},{10,23}};
static const glyph_stroke_t *strokes_243[3] = {stroke_243_0, stroke_243_1, stroke_243_2};
static const uint8_t ncoords_243[3] = {17, 17, 4};
static const glyph_stroke_t stroke_244_0[17] = {{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3},{13,6},{13,8},{12,11},{10,13},{8,14},{5,14}};
static const glyph_stroke_t stroke_244_1[17] = {{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{10,2},{11,3},{12,6},{12,8},{11,11},{10,12},{8,13},{5,13}};
static const glyph_stroke_t stroke_244_2[5] = {{3,17},{7,21},{11,17},{7,20},{3,17}};
static const glyph_stroke_t *strokes_244[3] = {stroke_244_0, stroke_244_1, stroke_244_2};
static const uint8_t ncoords_244[3] = {17, 17, 5};
static const glyph_stroke_t stroke_245_0[17] = {{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3},{13,6},{13,8},{12,11},{10,13},{8,14},{5,14}};
static const glyph_stroke_t stroke_245_1[17] = {{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{10,2},{11,3},{12,6},{12,8},{11,11},{10,12},{8,13},{5,13}};
static const glyph_stroke_t stroke_245_2[6] = {{3,18},{4,19},{5,19},{7,18},{8,18},{9,19}};
static const glyph_stroke_t stroke_245_3[6] = {{4,19},{5,20},{6,20},{8,19},{9,19},{10,20}};
static const glyph_stroke_t *strokes_245[4] = {stroke_245_0, stroke_245_1, stroke_245_2, stroke_245_3};
static const uint8_t ncoords_245[4] = {17, 17, 6, 6};
static const glyph_stroke_t stroke_246_0[17] = {{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3},{13,6},{13,8},{12,11},{10,13},{8,14},{5,14}};
static const glyph_stroke_t stroke_246_1[17] = {{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{10,2},{11,3},{12,6},{12,8},{11,11},{10,12},{8,13},{5,13}};
static const glyph_stroke_t stroke_246_2[9] = {{9,20},{8,19},{8,18},{9,17},{10,17},{11,18},{11,19},{10,20},{9,20}};
static const glyph_stroke_t stroke_246_3[5] = {{9,19},{9,18},{10,18},{10,19},{9,19}};
static const glyph_stroke_t stroke_246_4[9] = {{4,20},{3,19},{3,18},{4,17},{5,17},{6,18},{6,19},{5,20},{4,20}};
static const glyph_stroke_t stroke_246_5[5] = {{4,19},{4,18},{5,18},{5,19},{4,19}};
static const glyph_stroke_t *strokes_246[6] = {stroke_246_0, stroke_246_1, stroke_246_2, stroke_246_3, stroke_246_4, stroke_246_5};
static const uint8_t ncoords_246[6] = {17, 17, 9, 5, 9, 5};
static const glyph_stroke_t stroke_248_0[17] = {{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3},{13,6},{13,8},{12,11},{10,13},{8,14},{5,14}};
static const glyph_stroke_t stroke_248_1[17] = {{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{10,2},{11,3},{12,6},{12,8},{11,11},{10,12},{8,13},{5,13}};
static const glyph_stroke_t stroke_248_2[5] = {{0,0},{1,0},{13,14},{12,14},{0,0}};
static const glyph_stroke_t *strokes_248[3] = {stroke_248_0, stroke_248_1, stroke_248_2};
static const uint8_t ncoords_248[3] = {17, 17, 5};
static const glyph_stroke_t stroke_249_0[7] = {{0,14},{0,4},{1,1},{3,0},{6,0},{8,1},{11,4}};
static const glyph_stroke_t stroke_249_1[8] = {{0,14},{1,14},{1,4},{2,2},{4,1},{6,1},{8,2},{11,4}};
static const glyph_stroke_t stroke_249_2[3] = {{11,14},{11,0},{12,0}};
static const glyph_stroke_t stroke_249_3[3] = {{11,14},{12,14},{12,0}};
static const glyph_stroke_t stroke_249_4[4] = {{4,23},{3,22},{9,18},{4,23}};
static const glyph_stroke_t *strokes_249[5] = {stroke_249_0, stroke_249_1, stroke_249_2, stroke_249_3, stroke_249_4};
static const uint8_t ncoords_249[5] = {7, 8, 3, 3, 4};
static const glyph_stroke_t stroke_250_0[7] = {{0,14},{0,4},{1,1},{3,0},{6,0},{8,1},{11,4}};
static const glyph_stroke_t stroke_250_1[8] = {{0,14},{1,14},{1,4},{2,2},{4,1},{6,1},{8,2},{11,4}};
static const glyph_stroke_t stroke_250_2[3] = {{11,14},{11,0},{12,0}};
static const glyph_stroke_t stroke_250_3[3] = {{11,14},{12,14},{12,0}};
static const glyph_stroke_t stroke_250_4[4] = {{10,23},{11,22},{5,18},{10,23}};
static const glyph_stroke_t *strokes_250[5] = {stroke_250_0, stroke_250_1, stroke_250_2, stroke_250_3, stroke_250_4};
static const uint8_t ncoords_250[5] = {7, 8, 3, 3, 4};
static const glyph_stroke_t stroke_251_0[7] = {{0,14},{0,4},{1,1},{3,0},{6,0},{8,1},{11,4}};
static const glyph_stroke_t stroke_251_1[8] = {{0,14},{1,14},{1,4},{2,2},{4,1},{6,1},{8,2},{11,4}};
static const glyph_stroke_t stroke_251_2[3] = {{11,14},{11,0},{12,0}};
static const glyph_stroke_t stroke_251_3[3] = {{11,14},{12,14},{12,0}};
static const glyph_stroke_t stroke_251_4[5] = {{3,17},{7,21},{11,17},{7,20},{3,17}};
static const glyph_stroke_t *strokes_251[5] = {stroke_251_0, stroke_251_1, stroke_251_2, stroke_251_3, stroke_251_4};
static const uint8_t ncoords_251[5] = {7, 8, 3, 3, 5};
static const glyph_stroke_t stroke_252_0[7] = {{0,14},{0,4},{1,1},{3,0},{6,0},{8,1},{11,4}};
static const glyph_stroke_t stroke_252_1[8] = {{0,14},{1,14},{1,4},{2,2},{4,1},{6,1},{8,2},{11,4}};
static const glyph_stroke_t stroke_252_2[3] = {{11,14},{11,0},{12,0}};
static const glyph_stroke_t stroke_252_3[3] = {{11,14},{12,14},{12,0}};
static const glyph_stroke_t stroke_252_4[9] = {{8,20},{7,19},{7,18},{8,17},{9,17},{10,18},{10,19},{9,20},{8,20}};
static const glyph_stroke_t stroke_252_5[5] = {{8,19},{8,18},{9,18},{9,19},{8,19}};
static const glyph_stroke_t stroke_252_6[9] = {{3,20},{2,19},{2,18},{3,17},{4,17},{5,18},{5,19},{4,20},{3,20}};
static const glyph_stroke_t stroke_252_7[5] = {{3,19},{3,18},{4,18},{4,19},{3,19}};
static const glyph_stroke_t *strokes_252[8] = {stroke_252_0, stroke_252_1, stroke_252_2, stroke_252_3, stroke_252_4, stroke_252_5, stroke_252_6, stroke_252_7};
static const uint8_t ncoords_252[8] = {7, 8, 3, 3, 9, 5, 9, 5};
static const glyph_stroke_t stroke_253_0[2] = {{0,14},{6,0}};
static const glyph_stroke_t stroke_253_1[3] = {{0,14},{1,14},{6,2}};
static const glyph_stroke_t stroke_253_2[4] = {{12,14},{11,14},{6,2},{2,-7}};
static const glyph_stroke_t stroke_253_3[4] = {{12,14},{6,0},{3,-7},{2,-7}};
static const glyph_stroke_t stroke_253_4[4] = {{10,23},{11,22},{5,18},{10,23}};
static const glyph_stroke_t *strokes_253[5] = {stroke_253_0, stroke_253_1, stroke_253_2, stroke_253_3, stroke_253_4};
static const uint8_t ncoords_253[5] = {2, 3, 4, 4, 4};
static const glyph_stroke_t stroke_57598_0[17] = {{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3},{13,6},{13,8},{12,11},{10,13},{8,14},{5,14}};
static const glyph_stroke_t stroke_57598_1[17] = {{5,13},{3,12},{2,11},{1,8},{1,6},{2,3},{3,2},{5,1},{8,1},{10,2},{11,3},{12,6},{12,8},{11,11},{10,12},{8,13},{5,13}};
static const glyph_stroke_t stroke_57598_2[5] = {{0,-7},{1,-7},{1,21},{0,21},{0,-7}};
static const glyph_stroke_t *strokes_57598[3] = {stroke_57598_0, stroke_57598_1, stroke_57598_2};
static const uint8_t ncoords_57598[3] = {17, 17, 5};
static const glyph_stroke_t stroke_255_0[2] = {{0,14},{6,0}};
static const glyph_stroke_t stroke_255_1[3] = {{0,14},{1,14},{6,2}};
static const glyph_stroke_t stroke_255_2[4] = {{12,14},{11,14},{6,2},{2,-7}};
static const glyph_stroke_t stroke_255_3[4] = {{12,14},{6,0},{3,-7},{2,-7}};
static const glyph_stroke_t stroke_255_4[9] = {{8,20},{7,19},{7,18},{8,17},{9,17},{10,18},{10,19},{9,20},{8,20}};
static const glyph_stroke_t stroke_255_5[5] = {{8,19},{8,18},{9,18},{9,19},{8,19}};
static const glyph_stroke_t stroke_255_6[9] = {{3,20},{2,19},{2,18},{3,17},{4,17},{5,18},{5,19},{4,20},{3,20}};
static const glyph_stroke_t stroke_255_7[5] = {{3,19},{3,18},{4,18},{4,19},{3,19}};
static const glyph_stroke_t *strokes_255[8] = {stroke_255_0, stroke_255_1, stroke_255_2, stroke_255_3, stroke_255_4, stroke_255_5, stroke_255_6, stroke_255_7};
static const uint8_t ncoords_255[8] = {2, 3, 4, 4, 9, 5, 9, 5};
static const glyph_stroke_t stroke_9001_0[7] = {{7,25},{0,9},{7,-7},{7,-6},{1,9},{7,24},{7,25}};
static const glyph_stroke_t *strokes_9001[1] = {stroke_9001_0};
static const uint8_t ncoords_9001[1] = {7};
static const glyph_stroke_t stroke_9002_0[7] = {{0,25},{7,9},{0,-7},{0,-6},{6,9},{0,24},{0,25}};
static const glyph_stroke_t *strokes_9002[1] = {stroke_9002_0};
static const uint8_t ncoords_9002[1] = {7};
static const glyph_data_t glyph_data[176] = {
	{ 0x00000020, 0, 0, 0, 0, -6, 6, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x00000021, 0, 0, 3, 21, -4, 7, 0, 4, strokes_33, ncoords_33 },
	{ 0x00000022, 0, 14, 11, 21, -4, 14, 0, 6, strokes_34, ncoords_34 },
	{ 0x00000023, 0, -7, 15, 25, -3, 18, 0, 4, strokes_35, ncoords_35 },
	{ 0x00000024, 0, -4, 13, 25, -3, 16, 0, 5, strokes_36, ncoords_36 },
	{ 0x00000025, 0, 0, 19, 21, -3, 22, 0, 3, strokes_37, ncoords_37 },
	{ 0x00000026, 0, 0, 19, 21, -3, 22, 0, 3, strokes_38, ncoords_38 },
	{ 0x00000027, 0, 14, 2, 21, -4, 5, 0, 3, strokes_39, ncoords_39 },
	{ 0x00000028, 0, -7, 7, 25, -4, 10, 0, 2, strokes_40, ncoords_40 },
	{ 0x00000029, 0, -7, 7, 25, -3, 11, 0, 2, strokes_41, ncoords_41 },
	{ 0x0000002a, 0, 9, 10, 21, -3, 13, 0, 9, strokes_42, ncoords_42 },
	{ 0x0000002b, 0, 1, 17, 18, -4, 21, 0, 4, strokes_43, ncoords_43 },
	{ 0x0000002c, 0, -4, 3, 3, -4, 7, 0, 4, strokes_44, ncoords_44 },
	{ 0x0000002d, 0, 9, 10, 10, -3, 13, 0, 1, strokes_45, ncoords_45 },
	{ 0x0000002e, 0, 0, 3, 3, -4, 7, 0, 2, strokes_46, ncoords_46 },
	{ 0x0000002f, 0, -7, 19, 25, -2, 21, 0, 2, strokes_47, ncoords_47 },
	{ 0x00000030, 0, 0, 14, 21, -3, 17, 0, 5, strokes_48, ncoords_48 },
	{ 0x00000031, 0, 0, 5, 21, -6, 14, 0, 2, strokes_49, ncoords_49 },
	{ 0x00000032, 0, 0, 14, 21, -3, 17, 0, 4, strokes_50, ncoords_50 },
	{ 0x00000033, 0, 0, 14, 21, -3, 17, 0, 8, strokes_51, ncoords_51 },
	{ 0x00000034, 0, 0, 15, 21, -3, 17, 0, 5, strokes_52, ncoords_52 },
	{ 0x00000035, 0, 0, 14, 21, -3, 17, 0, 9, strokes_53, ncoords_53 },
	{ 0x00000036, 0, 0, 13, 21, -4, 16, 0, 7, strokes_54, ncoords_54 },
	{ 0x00000037, 0, 0, 14, 21, -3, 17, 0, 3, strokes_55, ncoords_55 },
	{ 0x00000038, 0, 0, 14, 21, -3, 17, 0, 5, strokes_56, ncoords_56 },
	{ 0x00000039, 0, 0, 13, 21, -3, 17, 0, 7, strokes_57, ncoords_57 },
	{ 0x0000003a, 0, 0, 3, 14, -4, 7, 0, 4, strokes_58, ncoords_58 },
	{ 0x0000003b, 0, -4, 3, 14, -4, 7, 0, 6, strokes_59, ncoords_59 },
	{ 0x0000003c, 0, 0, 16, 18, -4, 20, 0, 1, strokes_60, ncoords_60 },
	{ 0x0000003d, 0, 5, 17, 14, -4, 21, 0, 4, strokes_61, ncoords_61 },
	{ 0x0000003e, 0, 0, 16, 18, -4, 20, 0, 1, strokes_62, ncoords_62 },
	{ 0x0000003f, 0, 0, 13, 21, -3, 16, 0, 8, strokes_63, ncoords_63 },
	{ 0x00000040, 0, 0, 21, 21, -3, 24, 0, 4, strokes_64, ncoords_64 },
	{ 0x00000041, 0, 0, 16, 21, -2, 18, 0, 6, strokes_65, ncoords_65 },
	{ 0x00000042, 0, 0, 13, 21, -4, 16, 0, 6, strokes_66, ncoords_66 },
	{ 0x00000043, 0, 0, 15, 21, -3, 18, 0, 2, strokes_67, ncoords_67 },
	{ 0x00000044, 0, 0, 14, 21, -4, 17, 0, 4, strokes_68, ncoords_68 },
	{ 0x00000045, 0, 0, 12, 21, -4, 15, 0, 8, strokes_69, ncoords_69 },
	{ 0x00000046, 0, 0, 12, 21, -4, 14, 0, 6, strokes_70, ncoords_70 },
	{ 0x00000047, 0, 0, 15, 21, -3, 18, 0, 2, strokes_71, ncoords_71 },
	{ 0x00000048, 0, 0, 14, 21, -4, 18, 0, 6, strokes_72, ncoords_72 },
	{ 0x00000049, 0, 0, 1, 21, -4, 5, 0, 2, strokes_73, ncoords_73 },
	{ 0x0000004a, 0, 0, 10, 21, -3, 14, 0, 2, strokes_74, ncoords_74 },
	{ 0x0000004b, 0, 0, 14, 21, -4, 17, 0, 6, strokes_75, ncoords_75 },
	{ 0x0000004c, 0, 0, 12, 21, -4, 13, 0, 4, strokes_76, ncoords_76 },
	{ 0x0000004d, 0, 0, 16, 21, -4, 20, 0, 8, strokes_77, ncoords_77 },
	{ 0x0000004e, 0, 0, 14, 21, -4, 18, 0, 6, strokes_78, ncoords_78 },
	{ 0x0000004f, 0, 0, 16, 21, -3, 19, 0, 2, strokes_79, ncoords_79 },
	{ 0x00000050, 0, 0, 13, 21, -4, 16, 0, 4, strokes_80, ncoords_80 },
	{ 0x00000051, 0, -2, 16, 21, -3, 19, 0, 4, strokes_81, ncoords_81 },
	{ 0x00000052, 0, 0, 13, 21, -4, 16, 0, 6, strokes_82, ncoords_82 },
	{ 0x00000053, 0, 0, 14, 21, -3, 17, 0, 2, strokes_83, ncoords_83 },
	{ 0x00000054, 0, 0, 13, 21, -2, 15, 0, 4, strokes_84, ncoords_84 },
	{ 0x00000055, 0, 0, 14, 21, -4, 18, 0, 2, strokes_85, ncoords_85 },
	{ 0x00000056, 0, 0, 16, 21, -2, 18, 0, 4, strokes_86, ncoords_86 },
	{ 0x00000057, 0, 0, 22, 21, -2, 24, 0, 8, strokes_87, ncoords_87 },
	{ 0x00000058, 0, 0, 14, 21, -3, 17, 0, 4, strokes_88, ncoords_88 },
	{ 0x00000059, 0, 0, 15, 21, -2, 17, 0, 4, strokes_89, ncoords_89 },
	{ 0x0000005a, 0, 0, 14, 21, -3, 17, 0, 6, strokes_90, ncoords_90 },
	{ 0x0000005b, 0, -7, 7, 25, -4, 10, 0, 4, strokes_91, ncoords_91 },
	{ 0x0000005c, 0, -3, 14, 21, 0, 14, 0, 1, strokes_92, ncoords_92 },
	{ 0x0000005d, 0, -7, 7, 25, -3, 11, 0, 4, strokes_93, ncoords_93 },
	{ 0x0000005e, 0, 16, 16, 23, -3, 19, 0, 2, strokes_94, ncoords_94 },
	{ 0x0000005f, 0, -7, 20, -6, 0, 20, 0, 1, strokes_95, ncoords_95 },
	{ 0x00000060, 0, 15, 6, 21, -3, 9, 0, 2, strokes_96, ncoords_96 },
	{ 0x00000061, 0, 0, 13, 14, -3, 17, 0, 4, strokes_97, ncoords_97 },
	{ 0x00000062, 0, 0, 13, 21, -4, 16, 0, 4, strokes_98, ncoords_98 },
	{ 0x00000063, 0, 0, 12, 14, -3, 15, 0, 2, strokes_99, ncoords_99 },
	{ 0x00000064, 0, 0, 13, 21, -3, 17, 0, 4, strokes_100, ncoords_100 },
	{ 0x00000065, 0, 0, 12, 14, -3, 15, 0, 2, strokes_101, ncoords_101 },
	{ 0x00000066, 0, 0, 8, 21, -3, 11, 0, 5, strokes_102, ncoords_102 },
	{ 0x00000067, 0, -7, 13, 14, -3, 17, 0, 4, strokes_103, ncoords_103 },
	{ 0x00000068, 0, 0, 12, 21, -4, 16, 0, 4, strokes_104, ncoords_104 },
	{ 0x00000069, 0, 0, 3, 21, -3, 6, 0, 4, strokes_105, ncoords_105 },
	{ 0x0000006a, 0, -7, 3, 21, -3, 6, 0, 4, strokes_106, ncoords_106 },
	{ 0x0000006b, 0, 0, 12, 21, -4, 15, 0, 6, strokes_107, ncoords_107 },
	{ 0x0000006c, 0, 0, 1, 21, -4, 5, 0, 2, strokes_108, ncoords_108 },
	{ 0x0000006d, 0, 0, 23, 14, -4, 27, 0, 6, strokes_109, ncoords_109 },
	{ 0x0000006e, 0, 0, 12, 14, -4, 16, 0, 4, strokes_110, ncoords_110 },
	{ 0x0000006f, 0, 0, 13, 14, -3, 16, 0, 2, strokes_111, ncoords_111 },
	{ 0x00000070, 0, -7, 13, 14, -4, 16, 0, 4, strokes_112, ncoords_112 },
	{ 0x00000071, 0, -7, 13, 14, -3, 17, 0, 4, strokes_113, ncoords_113 },
	{ 0x00000072, 0, 0, 9, 14, -4, 10, 0, 4, strokes_114, ncoords_114 },
	{ 0x00000073, 0, 0, 11, 14, -3, 14, 0, 8, strokes_115, ncoords_115 },
	{ 0x00000074, 0, 0, 7, 21, -2, 9, 0, 4, strokes_116, ncoords_116 },
	{ 0x00000075, 0, 0, 12, 14, -4, 16, 0, 4, strokes_117, ncoords_117 },
	{ 0x00000076, 0, 0, 12, 14, -2, 14, 0, 4, strokes_118, ncoords_118 },
	{ 0x00000077, 0, 0, 18, 14, -3, 21, 0, 8, strokes_119, ncoords_119 },
	{ 0x00000078, 0, 0, 12, 14, -3, 15, 0, 4, strokes_120, ncoords_120 },
	{ 0x00000079, 0, -7, 12, 14, -2, 14, 0, 4, strokes_121, ncoords_121 },
	{ 0x0000007a, 0, 0, 12, 14, -3, 15, 0, 6, strokes_122, ncoords_122 },
	{ 0x0000007b, 0, -7, 5, 25, -4, 10, 0, 3, strokes_123, ncoords_123 },
	{ 0x0000007c, 0, -7, 1, 25, -4, 5, 0, 1, strokes_124, ncoords_124 },
	{ 0x0000007d, 0, -7, 5, 25, -5, 9, 0, 3, strokes_125, ncoords_125 },
	{ 0x0000007e, 0, 6, 18, 12, -3, 21, 0, 2, strokes_126, ncoords_126 },
	{ 0x0000007f, 0, 0, 16, 21, 0, 16, 0, 1, strokes_127, ncoords_127 },
	{ 0x000000c0, 0, 0, 16, 29, -2, 18, 0, 7, strokes_192, ncoords_192 },
	{ 0x000000c1, 0, 0, 16, 29, -2, 18, 0, 7, strokes_193, ncoords_193 },
	{ 0x000000c2, 0, 0, 16, 27, -2, 18, 0, 7, strokes_194, ncoords_194 },
	{ 0x000000c3, 0, 0, 16, 26, -2, 18, 0, 8, strokes_195, ncoords_195 },
	{ 0x000000c4, 0, 0, 16, 26, -2, 18, 0, 10, strokes_196, ncoords_196 },
	{ 0x000000c5, 0, 0, 16, 27, -2, 18, 0, 8, strokes_197, ncoords_197 },
	{ 0x000000c6, 0, 0, 18, 21, -2, 20, 0, 12, strokes_198, ncoords_198 },
	{ 0x000000c8, 0, 0, 12, 29, -4, 15, 0, 9, strokes_200, ncoords_200 },
	{ 0x000000c9, 0, 0, 12, 29, -4, 15, 0, 9, strokes_201, ncoords_201 },
	{ 0x000000ca, 0, 0, 12, 27, -4, 15, 0, 9, strokes_202, ncoords_202 },
	{ 0x000000cb, 0, 0, 12, 26, -4, 15, 0, 12, strokes_203, ncoords_203 },
	{ 0x000000cc, -3, 0, 3, 29, -4, 5, 0, 3, strokes_204, ncoords_204 },
	{ 0x000000cd, -2, 0, 4, 29, -4, 5, 0, 3, strokes_205, ncoords_205 },
	{ 0x000000ce, -3, 0, 5, 27, -4, 5, 0, 3, strokes_206, ncoords_206 },
	{ 0x000000cf, -3, 0, 5, 26, -4, 5, 0, 6, strokes_207, ncoords_207 },
	{ 0x000000d1, 0, 0, 14, 26, -4, 18, 0, 8, strokes_209, ncoords_209 },
	{ 0x000000d2, 0, 0, 16, 29, -3, 19, 0, 3, strokes_210, ncoords_210 },
	{ 0x000000d3, 0, 0, 16, 29, -3, 19, 0, 3, strokes_211, ncoords_211 },
	{ 0x000000d4, 0, 0, 16, 27, -3, 19, 0, 3, strokes_212, ncoords_212 },
	{ 0x000000d5, 0, 0, 16, 26, -3, 19, 0, 4, strokes_213, ncoords_213 },
	{ 0x000000d6, 0, 0, 16, 26, -3, 19, 0, 6, strokes_214, ncoords_214 },
	{ 0x000000d8, 0, 0, 16, 21, -3, 19, 0, 3, strokes_216, ncoords_216 },
	{ 0x000000d9, 0, 0, 14, 29, -4, 18, 0, 3, strokes_217, ncoords_217 },
	{ 0x000000da, 0, 0, 14, 29, -4, 18, 0, 3, strokes_218, ncoords_218 },
	{ 0x000000db, 0, 0, 14, 27, -4, 18, 0, 3, strokes_219, ncoords_219 },
	{ 0x000000dc, 0, 0, 14, 26, -4, 18, 0, 6, strokes_220, ncoords_220 },
	{ 0x000000dd, 0, 0, 15, 29, -2, 17, 0, 5, strokes_221, ncoords_221 },
	{ 0x000000e0, 0, 0, 13, 23, -3, 17, 0, 5, strokes_224, ncoords_224 },
	{ 0x000000e1, 0, 0, 13, 23, -3, 17, 0, 5, strokes_225, ncoords_225 },
	{ 0x000000e2, 0, 0, 13, 21, -3, 17, 0, 5, strokes_226, ncoords_226 },
	{ 0x000000e3, 0, 0, 13, 20, -3, 17, 0, 6, strokes_227, ncoords_227 },
	{ 0x000000e4, 0, 0, 13, 20, -3, 17, 0, 8, strokes_228, ncoords_228 },
	{ 0x000000e5, 0, 0, 13, 22, -3, 17, 0, 6, strokes_229, ncoords_229 },
	{ 0x000000e6, 0, 0, 24, 14, -3, 28, 0, 6, strokes_230, ncoords_230 },
	{ 0x000000e8, 0, 0, 12, 23, -3, 15, 0, 3, strokes_232, ncoords_232 },
	{ 0x000000e9, 0, 0, 12, 23, -3, 15, 0, 3, strokes_233, ncoords_233 },
	{ 0x000000ea, 0, 0, 12, 21, -3, 15, 0, 3, strokes_234, ncoords_234 },
	{ 0x000000eb, 0, 0, 12, 20, -3, 15, 0, 6, strokes_235, ncoords_235 },
	{ 0x000000ec, -2, 0, 4, 23, -3, 6, 0, 2, strokes_236, ncoords_236 },
	{ 0x000000ed, -1, 0, 5, 23, -3, 6, 0, 2, strokes_237, ncoords_237 },
	{ 0x000000ee, -2, 0, 6, 21, -3, 6, 0, 2, strokes_238, ncoords_238 },
	{ 0x000000ef, -2, 0, 6, 20, -3, 6, 0, 5, strokes_239, ncoords_239 },
	{ 0x000000f1, 0, 0, 12, 20, -4, 16, 0, 6, strokes_241, ncoords_241 },
	{ 0x000000f2, 0, 0, 13, 23, -3, 16, 0, 3, strokes_242, ncoords_242 },
	{ 0x000000f3, 0, 0, 13, 23, -3, 16, 0, 3, strokes_243, ncoords_243 },
	{ 0x000000f4, 0, 0, 13, 21, -3, 16, 0, 3, strokes_244, ncoords_244 },
	{ 0x000000f5, 0, 0, 13, 20, -3, 16, 0, 4, strokes_245, ncoords_245 },
	{ 0x000000f6, 0, 0, 13, 20, -3, 16, 0, 6, strokes_246, ncoords_246 },
	{ 0x000000f8, 0, 0, 13, 14, -3, 16, 0, 3, strokes_248, ncoords_248 },
	{ 0x000000f9, 0, 0, 12, 23, -4, 16, 0, 5, strokes_249, ncoords_249 },
	{ 0x000000fa, 0, 0, 12, 23, -4, 16, 0, 5, strokes_250, ncoords_250 },
	{ 0x000000fb, 0, 0, 12, 21, -4, 16, 0, 5, strokes_251, ncoords_251 },
	{ 0x000000fc, 0, 0, 12, 20, -4, 16, 0, 8, strokes_252, ncoords_252 },
	{ 0x000000fd, 0, -7, 12, 23, -2, 14, 0, 5, strokes_253, ncoords_253 },
	{ 0x000000ff, 0, -7, 12, 20, -2, 14, 0, 8, strokes_255, ncoords_255 },
	{ 0x00002329, 0, -7, 7, 25, -3, 11, 0, 1, strokes_9001, ncoords_9001 },
	{ 0x0000232a, 0, -7, 7, 25, -4, 10, 0, 1, strokes_9002, ncoords_9002 },
	{ 0x0000e0c7, 0, -4, 15, 21, -3, 18, 0, 4, strokes_57543, ncoords_57543 },
	{ 0x0000e0d0, -2, 0, 14, 21, -4, 17, 0, 5, strokes_57552, ncoords_57552 },
	{ 0x0000e0d7, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0de, 0, 0, 13, 21, -4, 16, 0, 3, strokes_57566, ncoords_57566 },
	{ 0x0000e0df, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0e7, 0, -4, 12, 14, -3, 15, 0, 4, strokes_57575, ncoords_57575 },
	{ 0x0000e0f0, 0, 0, 13, 20, -3, 16, 0, 2, strokes_57584, ncoords_57584 },
	{ 0x0000e0f7, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0fe, 0, -7, 13, 21, -3, 16, 0, 3, strokes_57598, ncoords_57598 },
	{ 0x0000f320, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f321, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f322, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f323, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f324, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f325, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f326, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f327, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f328, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f32b, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f32c, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f32d, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f32e, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f32f, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 }
};
const font_data_t font_hsans_2 = {
	"Hershey Sans regular - double stroke",
	21,
	176,
	glyph_data
};
