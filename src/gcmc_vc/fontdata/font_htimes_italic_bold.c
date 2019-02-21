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

static const glyph_stroke_t stroke_33_0[4] = {{7,21},{6,21},{5,20},{3,7}};
static const glyph_stroke_t stroke_33_1[3] = {{7,20},{6,20},{3,7}};
static const glyph_stroke_t stroke_33_2[3] = {{7,20},{7,19},{3,7}};
static const glyph_stroke_t stroke_33_3[4] = {{7,21},{8,20},{8,19},{3,7}};
static const glyph_stroke_t stroke_33_4[9] = {{1,3},{0,2},{0,1},{1,0},{2,0},{3,1},{3,2},{2,3},{1,3}};
static const glyph_stroke_t stroke_33_5[5] = {{1,2},{1,1},{2,1},{2,2},{1,2}};
static const glyph_stroke_t *strokes_33[6] = {stroke_33_0, stroke_33_1, stroke_33_2, stroke_33_3, stroke_33_4, stroke_33_5};
static const uint8_t ncoords_33[6] = {4, 3, 3, 4, 9, 5};
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
static const glyph_stroke_t stroke_36_2[19] = {{16,16},{16,17},{15,17},{15,15},{17,15},{17,17},{16,19},{15,20},{12,21},{8,21},{5,20},{3,18},{3,15},{4,13},{6,11},{12,8},{13,6},{13,3},{12,1}};
static const glyph_stroke_t stroke_36_3[4] = {{4,15},{5,13},{12,9},{13,7}};
static const glyph_stroke_t stroke_36_4[20] = {{5,20},{4,18},{4,16},{5,14},{11,11},{13,9},{14,7},{14,4},{13,2},{12,1},{9,0},{5,0},{2,1},{1,2},{0,4},{0,6},{2,6},{2,4},{1,4},{1,5}};
static const glyph_stroke_t *strokes_36[5] = {stroke_36_0, stroke_36_1, stroke_36_2, stroke_36_3, stroke_36_4};
static const uint8_t ncoords_36[5] = {2, 2, 19, 4, 20};
static const glyph_stroke_t stroke_37_0[2] = {{18,21},{0,0}};
static const glyph_stroke_t stroke_37_1[16] = {{5,21},{7,19},{7,17},{6,15},{4,14},{2,14},{0,16},{0,18},{1,20},{3,21},{5,21},{7,20},{10,19},{13,19},{16,20},{18,21}};
static const glyph_stroke_t stroke_37_2[11] = {{14,7},{12,6},{11,4},{11,2},{13,0},{15,0},{17,1},{18,3},{18,5},{16,7},{14,7}};
static const glyph_stroke_t *strokes_37[3] = {stroke_37_0, stroke_37_1, stroke_37_2};
static const uint8_t ncoords_37[3] = {2, 16, 11};
static const glyph_stroke_t stroke_38_0[38] = {{21,12},{21,13},{20,13},{20,11},{22,11},{22,13},{21,14},{20,14},{18,13},{16,11},{11,3},{9,1},{7,0},{4,0},{1,1},{0,3},{0,5},{1,7},{2,8},{4,9},{9,11},{11,12},{13,14},{14,16},{14,18},{13,20},{11,21},{9,20},{8,18},{8,15},{9,9},{10,6},{11,4},{13,1},{15,0},{17,0},{18,2},{18,3}};
static const glyph_stroke_t stroke_38_1[2] = {{5,0},{1,1}};
static const glyph_stroke_t stroke_38_2[6] = {{2,1},{1,3},{1,5},{2,7},{3,8},{5,9}};
static const glyph_stroke_t stroke_38_3[4] = {{9,11},{10,8},{13,2},{15,1}};
static const glyph_stroke_t stroke_38_4[8] = {{4,0},{3,1},{2,3},{2,5},{3,7},{4,8},{6,9},{11,12}};
static const glyph_stroke_t stroke_38_5[8] = {{8,15},{9,12},{10,9},{12,5},{14,2},{16,1},{17,1},{18,2}};
static const glyph_stroke_t *strokes_38[6] = {stroke_38_0, stroke_38_1, stroke_38_2, stroke_38_3, stroke_38_4, stroke_38_5};
static const uint8_t ncoords_38[6] = {38, 2, 6, 4, 8, 8};
static const glyph_stroke_t stroke_39_0[2] = {{2,21},{0,14}};
static const glyph_stroke_t stroke_39_1[2] = {{3,21},{0,14}};
static const glyph_stroke_t *strokes_39[2] = {stroke_39_0, stroke_39_1};
static const uint8_t ncoords_39[2] = {2, 2};
static const glyph_stroke_t stroke_40_0[11] = {{13,25},{11,24},{8,22},{5,19},{3,16},{1,12},{0,8},{0,3},{1,-1},{2,-4},{4,-7}};
static const glyph_stroke_t stroke_40_1[5] = {{6,19},{4,16},{2,12},{1,7},{1,-1}};
static const glyph_stroke_t stroke_40_2[8] = {{13,25},{10,23},{7,20},{5,17},{4,15},{3,12},{2,8},{1,-1}};
static const glyph_stroke_t stroke_40_3[4] = {{1,7},{2,-2},{3,-5},{4,-7}};
static const glyph_stroke_t *strokes_40[4] = {stroke_40_0, stroke_40_1, stroke_40_2, stroke_40_3};
static const uint8_t ncoords_40[4] = {11, 5, 8, 4};
static const glyph_stroke_t stroke_41_0[11] = {{9,25},{11,22},{12,19},{13,15},{13,10},{12,6},{10,2},{8,-1},{5,-4},{2,-6},{0,-7}};
static const glyph_stroke_t stroke_41_1[5] = {{12,19},{12,11},{11,6},{9,2},{7,-1}};
static const glyph_stroke_t stroke_41_2[4] = {{9,25},{10,23},{11,20},{12,11}};
static const glyph_stroke_t stroke_41_3[8] = {{12,19},{11,10},{10,6},{9,3},{8,1},{6,-2},{3,-5},{0,-7}};
static const glyph_stroke_t *strokes_41[4] = {stroke_41_0, stroke_41_1, stroke_41_2, stroke_41_3};
static const uint8_t ncoords_41[4] = {11, 5, 4, 8};
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
static const glyph_stroke_t stroke_44_0[11] = {{3,0},{2,0},{1,1},{1,2},{2,3},{3,3},{4,2},{4,0},{3,-2},{2,-3},{0,-4}};
static const glyph_stroke_t stroke_44_1[5] = {{2,2},{2,1},{3,1},{3,2},{2,2}};
static const glyph_stroke_t stroke_44_2[3] = {{3,0},{3,-1},{2,-3}};
static const glyph_stroke_t *strokes_44[3] = {stroke_44_0, stroke_44_1, stroke_44_2};
static const uint8_t ncoords_44[3] = {11, 5, 3};
static const glyph_stroke_t stroke_45_0[2] = {{0,9},{18,9}};
static const glyph_stroke_t *strokes_45[1] = {stroke_45_0};
static const uint8_t ncoords_45[1] = {2};
static const glyph_stroke_t stroke_46_0[9] = {{1,3},{0,2},{0,1},{1,0},{2,0},{3,1},{3,2},{2,3},{1,3}};
static const glyph_stroke_t stroke_46_1[5] = {{1,2},{1,1},{2,1},{2,2},{1,2}};
static const glyph_stroke_t *strokes_46[2] = {stroke_46_0, stroke_46_1};
static const uint8_t ncoords_46[2] = {9, 5};
static const glyph_stroke_t stroke_47_0[3] = {{18,25},{0,-7},{1,-7}};
static const glyph_stroke_t stroke_47_1[3] = {{18,25},{19,25},{1,-7}};
static const glyph_stroke_t *strokes_47[2] = {stroke_47_0, stroke_47_1};
static const uint8_t ncoords_47[2] = {3, 3};
static const glyph_stroke_t stroke_48_0[21] = {{9,21},{6,20},{4,18},{2,15},{1,12},{0,8},{0,5},{1,2},{2,1},{4,0},{6,0},{9,1},{11,3},{13,6},{14,9},{15,13},{15,16},{14,19},{13,20},{11,21},{9,21}};
static const glyph_stroke_t stroke_48_1[7] = {{6,19},{4,17},{3,15},{2,12},{1,8},{1,4},{2,2}};
static const glyph_stroke_t stroke_48_2[7] = {{9,2},{11,4},{12,6},{13,9},{14,13},{14,17},{13,19}};
static const glyph_stroke_t stroke_48_3[9] = {{9,21},{7,20},{5,17},{4,15},{3,12},{2,8},{2,3},{3,1},{4,0}};
static const glyph_stroke_t stroke_48_4[9] = {{6,0},{8,1},{10,4},{11,6},{12,9},{13,13},{13,18},{12,20},{11,21}};
static const glyph_stroke_t *strokes_48[5] = {stroke_48_0, stroke_48_1, stroke_48_2, stroke_48_3, stroke_48_4};
static const uint8_t ncoords_48[5] = {21, 7, 7, 9, 9};
static const glyph_stroke_t stroke_49_0[3] = {{5,17},{0,0},{2,0}};
static const glyph_stroke_t stroke_49_1[3] = {{8,21},{6,17},{1,0}};
static const glyph_stroke_t stroke_49_2[2] = {{8,21},{2,0}};
static const glyph_stroke_t stroke_49_3[4] = {{8,21},{5,18},{2,16},{0,15}};
static const glyph_stroke_t stroke_49_4[3] = {{5,17},{3,16},{0,15}};
static const glyph_stroke_t *strokes_49[5] = {stroke_49_0, stroke_49_1, stroke_49_2, stroke_49_3, stroke_49_4};
static const uint8_t ncoords_49[5] = {3, 3, 2, 4, 3};
static const glyph_stroke_t stroke_50_0[18] = {{6,16},{6,17},{7,17},{7,15},{5,15},{5,17},{6,19},{7,20},{10,21},{13,21},{16,20},{17,18},{17,16},{16,14},{14,12},{4,6},{2,4},{0,0}};
static const glyph_stroke_t stroke_50_1[6] = {{15,20},{16,18},{16,16},{15,14},{13,12},{10,10}};
static const glyph_stroke_t stroke_50_2[7] = {{13,21},{14,20},{15,18},{15,16},{14,14},{12,12},{4,6}};
static const glyph_stroke_t stroke_50_3[6] = {{1,2},{2,3},{4,3},{9,2},{14,2},{15,3}};
static const glyph_stroke_t stroke_50_4[3] = {{4,3},{9,1},{14,1}};
static const glyph_stroke_t stroke_50_5[6] = {{4,3},{9,0},{12,0},{14,1},{15,3},{15,4}};
static const glyph_stroke_t *strokes_50[6] = {stroke_50_0, stroke_50_1, stroke_50_2, stroke_50_3, stroke_50_4, stroke_50_5};
static const uint8_t ncoords_50[6] = {18, 6, 7, 6, 3, 6};
static const glyph_stroke_t stroke_51_0[17] = {{5,16},{5,17},{6,17},{6,15},{4,15},{4,17},{5,19},{6,20},{9,21},{12,21},{15,20},{16,18},{16,16},{15,14},{14,13},{12,12},{9,11}};
static const glyph_stroke_t stroke_51_1[5] = {{14,20},{15,18},{15,16},{14,14},{13,13}};
static const glyph_stroke_t stroke_51_2[7] = {{12,21},{13,20},{14,18},{14,16},{13,14},{11,12},{9,11}};
static const glyph_stroke_t stroke_51_3[18] = {{7,11},{9,11},{12,10},{13,9},{14,7},{14,4},{13,2},{11,1},{8,0},{5,0},{2,1},{1,2},{0,4},{0,6},{2,6},{2,4},{1,4},{1,5}};
static const glyph_stroke_t stroke_51_4[4] = {{12,9},{13,7},{13,4},{12,2}};
static const glyph_stroke_t stroke_51_5[7] = {{9,11},{11,10},{12,8},{12,4},{11,2},{10,1},{8,0}};
static const glyph_stroke_t *strokes_51[6] = {stroke_51_0, stroke_51_1, stroke_51_2, stroke_51_3, stroke_51_4, stroke_51_5};
static const uint8_t ncoords_51[6] = {17, 5, 7, 18, 4, 7};
static const glyph_stroke_t stroke_52_0[3] = {{13,17},{8,0},{10,0}};
static const glyph_stroke_t stroke_52_1[3] = {{16,21},{14,17},{9,0}};
static const glyph_stroke_t stroke_52_2[2] = {{16,21},{10,0}};
static const glyph_stroke_t stroke_52_3[3] = {{16,21},{0,6},{16,6}};
static const glyph_stroke_t *strokes_52[4] = {stroke_52_0, stroke_52_1, stroke_52_2, stroke_52_3};
static const uint8_t ncoords_52[4] = {3, 3, 2, 3};
static const glyph_stroke_t stroke_53_0[2] = {{7,21},{2,11}};
static const glyph_stroke_t stroke_53_1[2] = {{7,21},{17,21}};
static const glyph_stroke_t stroke_53_2[2] = {{7,20},{15,20}};
static const glyph_stroke_t stroke_53_3[4] = {{6,19},{11,19},{15,20},{17,21}};
static const glyph_stroke_t stroke_53_4[20] = {{2,11},{3,12},{6,13},{9,13},{12,12},{13,11},{14,9},{14,6},{13,3},{11,1},{7,0},{4,0},{2,1},{1,2},{0,4},{0,6},{2,6},{2,4},{1,4},{1,5}};
static const glyph_stroke_t stroke_53_5[5] = {{12,11},{13,9},{13,6},{12,3},{10,1}};
static const glyph_stroke_t stroke_53_6[7] = {{9,13},{11,12},{12,10},{12,6},{11,3},{9,1},{7,0}};
static const glyph_stroke_t *strokes_53[7] = {stroke_53_0, stroke_53_1, stroke_53_2, stroke_53_3, stroke_53_4, stroke_53_5, stroke_53_6};
static const uint8_t ncoords_53[7] = {2, 2, 2, 4, 20, 5, 7};
static const glyph_stroke_t stroke_54_0[30] = {{14,17},{14,18},{13,18},{13,16},{15,16},{15,18},{14,20},{12,21},{9,21},{6,20},{4,18},{2,15},{1,12},{0,8},{0,5},{1,2},{2,1},{4,0},{7,0},{10,1},{12,3},{13,5},{13,8},{12,10},{11,11},{9,12},{6,12},{4,11},{3,10},{2,8}};
static const glyph_stroke_t stroke_54_1[6] = {{5,18},{3,15},{2,12},{1,8},{1,4},{2,2}};
static const glyph_stroke_t stroke_54_2[4] = {{11,3},{12,5},{12,8},{11,10}};
static const glyph_stroke_t stroke_54_3[9] = {{9,21},{7,20},{5,17},{4,15},{3,12},{2,8},{2,3},{3,1},{4,0}};
static const glyph_stroke_t stroke_54_4[7] = {{7,0},{9,1},{10,2},{11,5},{11,9},{10,11},{9,12}};
static const glyph_stroke_t *strokes_54[5] = {stroke_54_0, stroke_54_1, stroke_54_2, stroke_54_3, stroke_54_4};
static const uint8_t ncoords_54[5] = {30, 6, 4, 9, 7};
static const glyph_stroke_t stroke_55_0[2] = {{2,21},{0,15}};
static const glyph_stroke_t stroke_55_1[7] = {{15,21},{14,18},{12,15},{8,10},{6,7},{5,4},{4,0}};
static const glyph_stroke_t stroke_55_2[3] = {{6,8},{4,4},{3,0}};
static const glyph_stroke_t stroke_55_3[6] = {{12,15},{6,9},{4,6},{3,4},{2,0},{4,0}};
static const glyph_stroke_t stroke_55_4[4] = {{1,18},{4,21},{6,21},{11,18}};
static const glyph_stroke_t stroke_55_5[3] = {{3,20},{6,20},{11,18}};
static const glyph_stroke_t stroke_55_6[7] = {{1,18},{3,19},{6,19},{11,18},{13,18},{14,19},{15,21}};
static const glyph_stroke_t *strokes_55[7] = {stroke_55_0, stroke_55_1, stroke_55_2, stroke_55_3, stroke_55_4, stroke_55_5, stroke_55_6};
static const uint8_t ncoords_55[7] = {2, 7, 3, 6, 4, 3, 7};
static const glyph_stroke_t stroke_56_0[15] = {{9,21},{6,20},{5,19},{4,17},{4,14},{5,12},{7,11},{10,11},{13,12},{15,13},{16,15},{16,18},{15,20},{13,21},{9,21}};
static const glyph_stroke_t stroke_56_1[2] = {{11,21},{6,20}};
static const glyph_stroke_t stroke_56_2[4] = {{6,19},{5,17},{5,13},{6,12}};
static const glyph_stroke_t stroke_56_3[2] = {{5,12},{8,11}};
static const glyph_stroke_t stroke_56_4[2] = {{9,11},{13,12}};
static const glyph_stroke_t stroke_56_5[4] = {{14,13},{15,15},{15,18},{14,20}};
static const glyph_stroke_t stroke_56_6[2] = {{15,20},{11,21}};
static const glyph_stroke_t stroke_56_7[5] = {{9,21},{7,19},{6,17},{6,13},{7,11}};
static const glyph_stroke_t stroke_56_8[6] = {{10,11},{12,12},{13,13},{14,15},{14,19},{13,21}};
static const glyph_stroke_t stroke_56_9[15] = {{7,11},{3,10},{1,8},{0,6},{0,3},{1,1},{4,0},{8,0},{12,1},{13,2},{14,4},{14,7},{13,9},{12,10},{10,11}};
static const glyph_stroke_t stroke_56_10[2] = {{8,11},{3,10}};
static const glyph_stroke_t stroke_56_11[5] = {{4,10},{2,8},{1,6},{1,3},{2,1}};
static const glyph_stroke_t stroke_56_12[3] = {{1,1},{6,0},{12,1}};
static const glyph_stroke_t stroke_56_13[4] = {{12,2},{13,4},{13,7},{12,9}};
static const glyph_stroke_t stroke_56_14[2] = {{12,10},{9,11}};
static const glyph_stroke_t stroke_56_15[7] = {{7,11},{5,10},{3,8},{2,6},{2,3},{3,1},{4,0}};
static const glyph_stroke_t stroke_56_16[7] = {{8,0},{10,1},{11,2},{12,4},{12,8},{11,10},{10,11}};
static const glyph_stroke_t *strokes_56[17] = {stroke_56_0, stroke_56_1, stroke_56_2, stroke_56_3, stroke_56_4, stroke_56_5, stroke_56_6, stroke_56_7, stroke_56_8, stroke_56_9, stroke_56_10, stroke_56_11, stroke_56_12, stroke_56_13, stroke_56_14, stroke_56_15, stroke_56_16};
static const uint8_t ncoords_56[17] = {15, 2, 4, 2, 2, 4, 2, 5, 6, 15, 2, 5, 3, 4, 2, 7, 7};
static const glyph_stroke_t stroke_57_0[30] = {{13,13},{12,11},{11,10},{9,9},{6,9},{4,10},{3,11},{2,13},{2,16},{3,18},{5,20},{8,21},{11,21},{13,20},{14,19},{15,16},{15,13},{14,9},{13,6},{11,3},{9,1},{6,0},{3,0},{1,1},{0,3},{0,5},{2,5},{2,3},{1,3},{1,4}};
static const glyph_stroke_t stroke_57_1[4] = {{4,11},{3,13},{3,16},{4,18}};
static const glyph_stroke_t stroke_57_2[6] = {{13,19},{14,17},{14,13},{13,9},{12,6},{10,3}};
static const glyph_stroke_t stroke_57_3[7] = {{6,9},{5,10},{4,12},{4,16},{5,19},{6,20},{8,21}};
static const glyph_stroke_t stroke_57_4[9] = {{11,21},{12,20},{13,18},{13,13},{12,9},{11,6},{10,4},{8,1},{6,0}};
static const glyph_stroke_t *strokes_57[5] = {stroke_57_0, stroke_57_1, stroke_57_2, stroke_57_3, stroke_57_4};
static const uint8_t ncoords_57[5] = {30, 4, 6, 7, 9};
static const glyph_stroke_t stroke_58_0[9] = {{4,14},{3,13},{3,12},{4,11},{5,11},{6,12},{6,13},{5,14},{4,14}};
static const glyph_stroke_t stroke_58_1[5] = {{4,13},{4,12},{5,12},{5,13},{4,13}};
static const glyph_stroke_t stroke_58_2[9] = {{1,3},{0,2},{0,1},{1,0},{2,0},{3,1},{3,2},{2,3},{1,3}};
static const glyph_stroke_t stroke_58_3[5] = {{1,2},{1,1},{2,1},{2,2},{1,2}};
static const glyph_stroke_t *strokes_58[4] = {stroke_58_0, stroke_58_1, stroke_58_2, stroke_58_3};
static const uint8_t ncoords_58[4] = {9, 5, 9, 5};
static const glyph_stroke_t stroke_59_0[9] = {{5,14},{4,13},{4,12},{5,11},{6,11},{7,12},{7,13},{6,14},{5,14}};
static const glyph_stroke_t stroke_59_1[5] = {{5,13},{5,12},{6,12},{6,13},{5,13}};
static const glyph_stroke_t stroke_59_2[11] = {{3,0},{2,0},{1,1},{1,2},{2,3},{3,3},{4,2},{4,0},{3,-2},{2,-3},{0,-4}};
static const glyph_stroke_t stroke_59_3[5] = {{2,2},{2,1},{3,1},{3,2},{2,2}};
static const glyph_stroke_t stroke_59_4[3] = {{3,0},{3,-1},{2,-3}};
static const glyph_stroke_t *strokes_59[5] = {stroke_59_0, stroke_59_1, stroke_59_2, stroke_59_3, stroke_59_4};
static const uint8_t ncoords_59[5] = {9, 5, 11, 5, 3};
static const glyph_stroke_t stroke_60_0[3] = {{16,18},{0,9},{16,0}};
static const glyph_stroke_t *strokes_60[1] = {stroke_60_0};
static const uint8_t ncoords_60[1] = {3};
static const glyph_stroke_t stroke_61_0[3] = {{0,14},{17,14},{17,13}};
static const glyph_stroke_t stroke_61_1[3] = {{0,14},{0,13},{17,13}};
static const glyph_stroke_t stroke_61_2[3] = {{0,6},{17,6},{17,5}};
static const glyph_stroke_t stroke_61_3[3] = {{0,6},{0,5},{17,5}};
static const glyph_stroke_t *strokes_61[4] = {stroke_61_0, stroke_61_1, stroke_61_2, stroke_61_3};
static const uint8_t ncoords_61[4] = {3, 3, 3, 3};
static const glyph_stroke_t stroke_62_0[3] = {{0,18},{16,9},{0,0}};
static const glyph_stroke_t *strokes_62[1] = {stroke_62_0};
static const uint8_t ncoords_62[1] = {3};
static const glyph_stroke_t stroke_63_0[21] = {{1,16},{1,17},{2,17},{2,15},{0,15},{0,17},{1,19},{2,20},{5,21},{9,21},{12,20},{13,18},{13,16},{12,14},{11,13},{9,12},{5,11},{3,10},{3,8},{5,7},{6,7}};
static const glyph_stroke_t stroke_63_1[2] = {{7,21},{12,20}};
static const glyph_stroke_t stroke_63_2[6] = {{11,20},{12,18},{12,16},{11,14},{10,13},{8,12}};
static const glyph_stroke_t stroke_63_3[10] = {{9,21},{10,20},{11,18},{11,16},{10,14},{9,13},{5,11},{4,10},{4,8},{5,7}};
static const glyph_stroke_t stroke_63_4[9] = {{2,3},{1,2},{1,1},{2,0},{3,0},{4,1},{4,2},{3,3},{2,3}};
static const glyph_stroke_t stroke_63_5[5] = {{2,2},{2,1},{3,1},{3,2},{2,2}};
static const glyph_stroke_t *strokes_63[6] = {stroke_63_0, stroke_63_1, stroke_63_2, stroke_63_3, stroke_63_4, stroke_63_5};
static const uint8_t ncoords_63[6] = {21, 2, 6, 10, 9, 5};
static const glyph_stroke_t stroke_64_0[13] = {{15,13},{14,15},{12,16},{9,16},{7,15},{6,14},{5,11},{5,8},{6,6},{8,5},{11,5},{13,6},{14,8}};
static const glyph_stroke_t stroke_64_1[6] = {{9,16},{7,14},{6,11},{6,8},{7,6},{8,5}};
static const glyph_stroke_t stroke_64_2[29] = {{15,16},{14,8},{14,6},{16,5},{18,5},{20,7},{21,10},{21,12},{20,15},{19,17},{17,19},{15,20},{12,21},{9,21},{6,20},{4,19},{2,17},{1,15},{0,12},{0,9},{1,6},{2,4},{4,2},{6,1},{9,0},{12,0},{15,1},{17,2},{18,3}};
static const glyph_stroke_t stroke_64_3[4] = {{16,16},{15,8},{15,6},{16,5}};
static const glyph_stroke_t *strokes_64[4] = {stroke_64_0, stroke_64_1, stroke_64_2, stroke_64_3};
static const uint8_t ncoords_64[4] = {13, 6, 29, 4};
static const glyph_stroke_t stroke_65_0[2] = {{15,21},{3,1}};
static const glyph_stroke_t stroke_65_1[2] = {{13,17},{14,0}};
static const glyph_stroke_t stroke_65_2[2] = {{14,19},{15,1}};
static const glyph_stroke_t stroke_65_3[4] = {{15,21},{15,19},{16,2},{16,0}};
static const glyph_stroke_t stroke_65_4[2] = {{6,6},{14,6}};
static const glyph_stroke_t stroke_65_5[2] = {{0,0},{6,0}};
static const glyph_stroke_t stroke_65_6[2] = {{11,0},{18,0}};
static const glyph_stroke_t stroke_65_7[2] = {{3,1},{1,0}};
static const glyph_stroke_t stroke_65_8[2] = {{3,1},{5,0}};
static const glyph_stroke_t stroke_65_9[2] = {{14,1},{12,0}};
static const glyph_stroke_t stroke_65_10[2] = {{14,2},{13,0}};
static const glyph_stroke_t stroke_65_11[2] = {{16,2},{17,0}};
static const glyph_stroke_t *strokes_65[12] = {stroke_65_0, stroke_65_1, stroke_65_2, stroke_65_3, stroke_65_4, stroke_65_5, stroke_65_6, stroke_65_7, stroke_65_8, stroke_65_9, stroke_65_10, stroke_65_11};
static const uint8_t ncoords_65[12] = {2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_66_0[2] = {{9,21},{3,0}};
static const glyph_stroke_t stroke_66_1[2] = {{10,21},{4,0}};
static const glyph_stroke_t stroke_66_2[2] = {{11,21},{5,0}};
static const glyph_stroke_t stroke_66_3[8] = {{6,21},{17,21},{20,20},{21,18},{21,16},{20,13},{19,12},{16,11}};
static const glyph_stroke_t stroke_66_4[5] = {{19,20},{20,18},{20,16},{19,13},{18,12}};
static const glyph_stroke_t stroke_66_5[6] = {{17,21},{18,20},{19,18},{19,16},{18,13},{16,11}};
static const glyph_stroke_t stroke_66_6[9] = {{8,11},{16,11},{18,10},{19,8},{19,6},{18,3},{16,1},{12,0},{0,0}};
static const glyph_stroke_t stroke_66_7[5] = {{17,10},{18,8},{18,6},{17,3},{15,1}};
static const glyph_stroke_t stroke_66_8[6] = {{16,11},{17,9},{17,6},{16,3},{14,1},{12,0}};
static const glyph_stroke_t stroke_66_9[2] = {{7,21},{10,20}};
static const glyph_stroke_t stroke_66_10[2] = {{8,21},{9,19}};
static const glyph_stroke_t stroke_66_11[2] = {{12,21},{10,19}};
static const glyph_stroke_t stroke_66_12[2] = {{13,21},{10,20}};
static const glyph_stroke_t stroke_66_13[2] = {{4,1},{1,0}};
static const glyph_stroke_t stroke_66_14[2] = {{4,2},{2,0}};
static const glyph_stroke_t stroke_66_15[2] = {{5,2},{6,0}};
static const glyph_stroke_t stroke_66_16[2] = {{4,1},{7,0}};
static const glyph_stroke_t *strokes_66[17] = {stroke_66_0, stroke_66_1, stroke_66_2, stroke_66_3, stroke_66_4, stroke_66_5, stroke_66_6, stroke_66_7, stroke_66_8, stroke_66_9, stroke_66_10, stroke_66_11, stroke_66_12, stroke_66_13, stroke_66_14, stroke_66_15, stroke_66_16};
static const uint8_t ncoords_66[17] = {2, 2, 2, 8, 5, 6, 9, 5, 6, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_67_0[22] = {{15,19},{16,19},{17,21},{16,15},{16,17},{15,19},{14,20},{12,21},{9,21},{6,20},{4,18},{2,15},{1,12},{0,8},{0,5},{1,2},{2,1},{5,0},{8,0},{10,1},{12,3},{13,5}};
static const glyph_stroke_t stroke_67_1[7] = {{6,19},{4,17},{3,15},{2,12},{1,8},{1,4},{2,2}};
static const glyph_stroke_t stroke_67_2[9] = {{9,21},{7,20},{5,17},{4,15},{3,12},{2,8},{2,3},{3,1},{5,0}};
static const glyph_stroke_t *strokes_67[3] = {stroke_67_0, stroke_67_1, stroke_67_2};
static const uint8_t ncoords_67[3] = {22, 7, 9};
static const glyph_stroke_t stroke_68_0[2] = {{9,21},{3,0}};
static const glyph_stroke_t stroke_68_1[2] = {{10,21},{4,0}};
static const glyph_stroke_t stroke_68_2[2] = {{11,21},{5,0}};
static const glyph_stroke_t stroke_68_3[12] = {{6,21},{15,21},{18,20},{19,19},{20,16},{20,12},{19,8},{17,4},{15,2},{13,1},{9,0},{0,0}};
static const glyph_stroke_t stroke_68_4[7] = {{17,20},{18,19},{19,16},{19,12},{18,8},{16,4},{14,2}};
static const glyph_stroke_t stroke_68_5[8] = {{15,21},{17,19},{18,16},{18,12},{17,8},{15,4},{12,1},{9,0}};
static const glyph_stroke_t stroke_68_6[2] = {{7,21},{10,20}};
static const glyph_stroke_t stroke_68_7[2] = {{8,21},{9,19}};
static const glyph_stroke_t stroke_68_8[2] = {{12,21},{10,19}};
static const glyph_stroke_t stroke_68_9[2] = {{13,21},{10,20}};
static const glyph_stroke_t stroke_68_10[2] = {{4,1},{1,0}};
static const glyph_stroke_t stroke_68_11[2] = {{4,2},{2,0}};
static const glyph_stroke_t stroke_68_12[2] = {{5,2},{6,0}};
static const glyph_stroke_t stroke_68_13[2] = {{4,1},{7,0}};
static const glyph_stroke_t *strokes_68[14] = {stroke_68_0, stroke_68_1, stroke_68_2, stroke_68_3, stroke_68_4, stroke_68_5, stroke_68_6, stroke_68_7, stroke_68_8, stroke_68_9, stroke_68_10, stroke_68_11, stroke_68_12, stroke_68_13};
static const uint8_t ncoords_68[14] = {2, 2, 2, 12, 7, 8, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_69_0[2] = {{9,21},{3,0}};
static const glyph_stroke_t stroke_69_1[2] = {{10,21},{4,0}};
static const glyph_stroke_t stroke_69_2[2] = {{11,21},{5,0}};
static const glyph_stroke_t stroke_69_3[2] = {{15,15},{13,7}};
static const glyph_stroke_t stroke_69_4[3] = {{6,21},{21,21},{20,15}};
static const glyph_stroke_t stroke_69_5[2] = {{8,11},{14,11}};
static const glyph_stroke_t stroke_69_6[3] = {{0,0},{15,0},{17,5}};
static const glyph_stroke_t stroke_69_7[2] = {{7,21},{10,20}};
static const glyph_stroke_t stroke_69_8[2] = {{8,21},{9,19}};
static const glyph_stroke_t stroke_69_9[2] = {{12,21},{10,19}};
static const glyph_stroke_t stroke_69_10[2] = {{13,21},{10,20}};
static const glyph_stroke_t stroke_69_11[2] = {{17,21},{20,20}};
static const glyph_stroke_t stroke_69_12[2] = {{18,21},{20,19}};
static const glyph_stroke_t stroke_69_13[2] = {{19,21},{20,18}};
static const glyph_stroke_t stroke_69_14[2] = {{20,21},{20,15}};
static const glyph_stroke_t stroke_69_15[3] = {{15,15},{13,11},{13,7}};
static const glyph_stroke_t stroke_69_16[3] = {{14,13},{12,11},{13,9}};
static const glyph_stroke_t stroke_69_17[3] = {{14,12},{11,11},{13,10}};
static const glyph_stroke_t stroke_69_18[2] = {{4,1},{1,0}};
static const glyph_stroke_t stroke_69_19[2] = {{4,2},{2,0}};
static const glyph_stroke_t stroke_69_20[2] = {{5,2},{6,0}};
static const glyph_stroke_t stroke_69_21[2] = {{4,1},{7,0}};
static const glyph_stroke_t stroke_69_22[2] = {{10,0},{15,1}};
static const glyph_stroke_t stroke_69_23[2] = {{12,0},{15,2}};
static const glyph_stroke_t stroke_69_24[2] = {{15,2},{17,5}};
static const glyph_stroke_t *strokes_69[25] = {stroke_69_0, stroke_69_1, stroke_69_2, stroke_69_3, stroke_69_4, stroke_69_5, stroke_69_6, stroke_69_7, stroke_69_8, stroke_69_9, stroke_69_10, stroke_69_11, stroke_69_12, stroke_69_13, stroke_69_14, stroke_69_15, stroke_69_16, stroke_69_17, stroke_69_18, stroke_69_19, stroke_69_20, stroke_69_21, stroke_69_22, stroke_69_23, stroke_69_24};
static const uint8_t ncoords_69[25] = {2, 2, 2, 2, 3, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_70_0[2] = {{9,21},{3,0}};
static const glyph_stroke_t stroke_70_1[2] = {{10,21},{4,0}};
static const glyph_stroke_t stroke_70_2[2] = {{11,21},{5,0}};
static const glyph_stroke_t stroke_70_3[2] = {{15,15},{13,7}};
static const glyph_stroke_t stroke_70_4[3] = {{6,21},{21,21},{20,15}};
static const glyph_stroke_t stroke_70_5[2] = {{8,11},{14,11}};
static const glyph_stroke_t stroke_70_6[2] = {{0,0},{8,0}};
static const glyph_stroke_t stroke_70_7[2] = {{7,21},{10,20}};
static const glyph_stroke_t stroke_70_8[2] = {{8,21},{9,19}};
static const glyph_stroke_t stroke_70_9[2] = {{12,21},{10,19}};
static const glyph_stroke_t stroke_70_10[2] = {{13,21},{10,20}};
static const glyph_stroke_t stroke_70_11[2] = {{17,21},{20,20}};
static const glyph_stroke_t stroke_70_12[2] = {{18,21},{20,19}};
static const glyph_stroke_t stroke_70_13[2] = {{19,21},{20,18}};
static const glyph_stroke_t stroke_70_14[2] = {{20,21},{20,15}};
static const glyph_stroke_t stroke_70_15[3] = {{15,15},{13,11},{13,7}};
static const glyph_stroke_t stroke_70_16[3] = {{14,13},{12,11},{13,9}};
static const glyph_stroke_t stroke_70_17[3] = {{14,12},{11,11},{13,10}};
static const glyph_stroke_t stroke_70_18[2] = {{4,1},{1,0}};
static const glyph_stroke_t stroke_70_19[2] = {{4,2},{2,0}};
static const glyph_stroke_t stroke_70_20[2] = {{5,2},{6,0}};
static const glyph_stroke_t stroke_70_21[2] = {{4,1},{7,0}};
static const glyph_stroke_t *strokes_70[22] = {stroke_70_0, stroke_70_1, stroke_70_2, stroke_70_3, stroke_70_4, stroke_70_5, stroke_70_6, stroke_70_7, stroke_70_8, stroke_70_9, stroke_70_10, stroke_70_11, stroke_70_12, stroke_70_13, stroke_70_14, stroke_70_15, stroke_70_16, stroke_70_17, stroke_70_18, stroke_70_19, stroke_70_20, stroke_70_21};
static const uint8_t ncoords_70[22] = {2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 2, 2, 2, 2};
static const glyph_stroke_t stroke_71_0[22] = {{15,19},{16,19},{17,21},{16,15},{16,17},{15,19},{14,20},{12,21},{9,21},{6,20},{4,18},{2,15},{1,12},{0,8},{0,5},{1,2},{2,1},{5,0},{7,0},{10,1},{12,3},{14,7}};
static const glyph_stroke_t stroke_71_1[7] = {{6,19},{4,17},{3,15},{2,12},{1,8},{1,4},{2,2}};
static const glyph_stroke_t stroke_71_2[3] = {{11,3},{12,4},{13,7}};
static const glyph_stroke_t stroke_71_3[9] = {{9,21},{7,20},{5,17},{4,15},{3,12},{2,8},{2,3},{3,1},{5,0}};
static const glyph_stroke_t stroke_71_4[4] = {{7,0},{9,1},{11,4},{12,7}};
static const glyph_stroke_t stroke_71_5[2] = {{9,7},{17,7}};
static const glyph_stroke_t stroke_71_6[2] = {{10,7},{12,6}};
static const glyph_stroke_t stroke_71_7[2] = {{11,7},{12,4}};
static const glyph_stroke_t stroke_71_8[2] = {{15,7},{13,5}};
static const glyph_stroke_t stroke_71_9[2] = {{16,7},{13,6}};
static const glyph_stroke_t *strokes_71[10] = {stroke_71_0, stroke_71_1, stroke_71_2, stroke_71_3, stroke_71_4, stroke_71_5, stroke_71_6, stroke_71_7, stroke_71_8, stroke_71_9};
static const uint8_t ncoords_71[10] = {22, 7, 3, 9, 4, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_72_0[2] = {{9,21},{3,0}};
static const glyph_stroke_t stroke_72_1[2] = {{10,21},{4,0}};
static const glyph_stroke_t stroke_72_2[2] = {{11,21},{5,0}};
static const glyph_stroke_t stroke_72_3[2] = {{21,21},{15,0}};
static const glyph_stroke_t stroke_72_4[2] = {{22,21},{16,0}};
static const glyph_stroke_t stroke_72_5[2] = {{23,21},{17,0}};
static const glyph_stroke_t stroke_72_6[2] = {{6,21},{14,21}};
static const glyph_stroke_t stroke_72_7[2] = {{18,21},{26,21}};
static const glyph_stroke_t stroke_72_8[2] = {{7,11},{19,11}};
static const glyph_stroke_t stroke_72_9[2] = {{0,0},{8,0}};
static const glyph_stroke_t stroke_72_10[2] = {{12,0},{20,0}};
static const glyph_stroke_t stroke_72_11[2] = {{7,21},{10,20}};
static const glyph_stroke_t stroke_72_12[2] = {{8,21},{9,19}};
static const glyph_stroke_t stroke_72_13[2] = {{12,21},{10,19}};
static const glyph_stroke_t stroke_72_14[2] = {{13,21},{10,20}};
static const glyph_stroke_t stroke_72_15[2] = {{19,21},{22,20}};
static const glyph_stroke_t stroke_72_16[2] = {{20,21},{21,19}};
static const glyph_stroke_t stroke_72_17[2] = {{24,21},{22,19}};
static const glyph_stroke_t stroke_72_18[2] = {{25,21},{22,20}};
static const glyph_stroke_t stroke_72_19[2] = {{4,1},{1,0}};
static const glyph_stroke_t stroke_72_20[2] = {{4,2},{2,0}};
static const glyph_stroke_t stroke_72_21[2] = {{5,2},{6,0}};
static const glyph_stroke_t stroke_72_22[2] = {{4,1},{7,0}};
static const glyph_stroke_t stroke_72_23[2] = {{16,1},{13,0}};
static const glyph_stroke_t stroke_72_24[2] = {{16,2},{14,0}};
static const glyph_stroke_t stroke_72_25[2] = {{17,2},{18,0}};
static const glyph_stroke_t stroke_72_26[2] = {{16,1},{19,0}};
static const glyph_stroke_t *strokes_72[27] = {stroke_72_0, stroke_72_1, stroke_72_2, stroke_72_3, stroke_72_4, stroke_72_5, stroke_72_6, stroke_72_7, stroke_72_8, stroke_72_9, stroke_72_10, stroke_72_11, stroke_72_12, stroke_72_13, stroke_72_14, stroke_72_15, stroke_72_16, stroke_72_17, stroke_72_18, stroke_72_19, stroke_72_20, stroke_72_21, stroke_72_22, stroke_72_23, stroke_72_24, stroke_72_25, stroke_72_26};
static const uint8_t ncoords_72[27] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_73_0[2] = {{9,21},{3,0}};
static const glyph_stroke_t stroke_73_1[2] = {{10,21},{4,0}};
static const glyph_stroke_t stroke_73_2[2] = {{11,21},{5,0}};
static const glyph_stroke_t stroke_73_3[2] = {{6,21},{14,21}};
static const glyph_stroke_t stroke_73_4[2] = {{0,0},{8,0}};
static const glyph_stroke_t stroke_73_5[2] = {{7,21},{10,20}};
static const glyph_stroke_t stroke_73_6[2] = {{8,21},{9,19}};
static const glyph_stroke_t stroke_73_7[2] = {{12,21},{10,19}};
static const glyph_stroke_t stroke_73_8[2] = {{13,21},{10,20}};
static const glyph_stroke_t stroke_73_9[2] = {{4,1},{1,0}};
static const glyph_stroke_t stroke_73_10[2] = {{4,2},{2,0}};
static const glyph_stroke_t stroke_73_11[2] = {{5,2},{6,0}};
static const glyph_stroke_t stroke_73_12[2] = {{4,1},{7,0}};
static const glyph_stroke_t *strokes_73[13] = {stroke_73_0, stroke_73_1, stroke_73_2, stroke_73_3, stroke_73_4, stroke_73_5, stroke_73_6, stroke_73_7, stroke_73_8, stroke_73_9, stroke_73_10, stroke_73_11, stroke_73_12};
static const uint8_t ncoords_73[13] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_74_0[4] = {{13,21},{8,4},{7,2},{5,0}};
static const glyph_stroke_t stroke_74_1[4] = {{14,21},{10,8},{9,5},{8,3}};
static const glyph_stroke_t stroke_74_2[15] = {{15,21},{11,8},{9,3},{7,1},{5,0},{3,0},{1,1},{0,3},{0,5},{1,6},{2,6},{3,5},{3,4},{2,3},{1,3}};
static const glyph_stroke_t stroke_74_3[5] = {{1,5},{1,4},{2,4},{2,5},{1,5}};
static const glyph_stroke_t stroke_74_4[2] = {{10,21},{18,21}};
static const glyph_stroke_t stroke_74_5[2] = {{11,21},{14,20}};
static const glyph_stroke_t stroke_74_6[2] = {{12,21},{13,19}};
static const glyph_stroke_t stroke_74_7[2] = {{16,21},{14,19}};
static const glyph_stroke_t stroke_74_8[2] = {{17,21},{14,20}};
static const glyph_stroke_t *strokes_74[9] = {stroke_74_0, stroke_74_1, stroke_74_2, stroke_74_3, stroke_74_4, stroke_74_5, stroke_74_6, stroke_74_7, stroke_74_8};
static const uint8_t ncoords_74[9] = {4, 4, 15, 5, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_75_0[2] = {{9,21},{3,0}};
static const glyph_stroke_t stroke_75_1[2] = {{10,21},{4,0}};
static const glyph_stroke_t stroke_75_2[2] = {{11,21},{5,0}};
static const glyph_stroke_t stroke_75_3[2] = {{22,20},{7,9}};
static const glyph_stroke_t stroke_75_4[2] = {{11,12},{15,0}};
static const glyph_stroke_t stroke_75_5[2] = {{12,12},{16,0}};
static const glyph_stroke_t stroke_75_6[2] = {{13,13},{17,1}};
static const glyph_stroke_t stroke_75_7[2] = {{6,21},{14,21}};
static const glyph_stroke_t stroke_75_8[2] = {{19,21},{25,21}};
static const glyph_stroke_t stroke_75_9[2] = {{0,0},{8,0}};
static const glyph_stroke_t stroke_75_10[2] = {{12,0},{19,0}};
static const glyph_stroke_t stroke_75_11[2] = {{7,21},{10,20}};
static const glyph_stroke_t stroke_75_12[2] = {{8,21},{9,19}};
static const glyph_stroke_t stroke_75_13[2] = {{12,21},{10,19}};
static const glyph_stroke_t stroke_75_14[2] = {{13,21},{10,20}};
static const glyph_stroke_t stroke_75_15[2] = {{20,21},{22,20}};
static const glyph_stroke_t stroke_75_16[2] = {{24,21},{22,20}};
static const glyph_stroke_t stroke_75_17[2] = {{4,1},{1,0}};
static const glyph_stroke_t stroke_75_18[2] = {{4,2},{2,0}};
static const glyph_stroke_t stroke_75_19[2] = {{5,2},{6,0}};
static const glyph_stroke_t stroke_75_20[2] = {{4,1},{7,0}};
static const glyph_stroke_t stroke_75_21[2] = {{15,1},{13,0}};
static const glyph_stroke_t stroke_75_22[2] = {{15,2},{14,0}};
static const glyph_stroke_t stroke_75_23[2] = {{16,2},{18,0}};
static const glyph_stroke_t *strokes_75[24] = {stroke_75_0, stroke_75_1, stroke_75_2, stroke_75_3, stroke_75_4, stroke_75_5, stroke_75_6, stroke_75_7, stroke_75_8, stroke_75_9, stroke_75_10, stroke_75_11, stroke_75_12, stroke_75_13, stroke_75_14, stroke_75_15, stroke_75_16, stroke_75_17, stroke_75_18, stroke_75_19, stroke_75_20, stroke_75_21, stroke_75_22, stroke_75_23};
static const uint8_t ncoords_75[24] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_76_0[2] = {{9,21},{3,0}};
static const glyph_stroke_t stroke_76_1[2] = {{10,21},{4,0}};
static const glyph_stroke_t stroke_76_2[2] = {{11,21},{5,0}};
static const glyph_stroke_t stroke_76_3[2] = {{6,21},{14,21}};
static const glyph_stroke_t stroke_76_4[3] = {{0,0},{15,0},{17,6}};
static const glyph_stroke_t stroke_76_5[2] = {{7,21},{10,20}};
static const glyph_stroke_t stroke_76_6[2] = {{8,21},{9,19}};
static const glyph_stroke_t stroke_76_7[2] = {{12,21},{10,19}};
static const glyph_stroke_t stroke_76_8[2] = {{13,21},{10,20}};
static const glyph_stroke_t stroke_76_9[2] = {{4,1},{1,0}};
static const glyph_stroke_t stroke_76_10[2] = {{4,2},{2,0}};
static const glyph_stroke_t stroke_76_11[2] = {{5,2},{6,0}};
static const glyph_stroke_t stroke_76_12[2] = {{4,1},{7,0}};
static const glyph_stroke_t stroke_76_13[2] = {{10,0},{15,1}};
static const glyph_stroke_t stroke_76_14[2] = {{12,0},{16,3}};
static const glyph_stroke_t stroke_76_15[2] = {{14,0},{17,6}};
static const glyph_stroke_t *strokes_76[16] = {stroke_76_0, stroke_76_1, stroke_76_2, stroke_76_3, stroke_76_4, stroke_76_5, stroke_76_6, stroke_76_7, stroke_76_8, stroke_76_9, stroke_76_10, stroke_76_11, stroke_76_12, stroke_76_13, stroke_76_14, stroke_76_15};
static const uint8_t ncoords_76[16] = {2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_77_0[2] = {{9,21},{3,1}};
static const glyph_stroke_t stroke_77_1[3] = {{9,20},{10,2},{10,0}};
static const glyph_stroke_t stroke_77_2[2] = {{10,21},{11,2}};
static const glyph_stroke_t stroke_77_3[2] = {{11,21},{12,3}};
static const glyph_stroke_t stroke_77_4[3] = {{23,21},{12,3},{10,0}};
static const glyph_stroke_t stroke_77_5[2] = {{23,21},{17,0}};
static const glyph_stroke_t stroke_77_6[2] = {{24,21},{18,0}};
static const glyph_stroke_t stroke_77_7[2] = {{25,21},{19,0}};
static const glyph_stroke_t stroke_77_8[2] = {{6,21},{11,21}};
static const glyph_stroke_t stroke_77_9[2] = {{23,21},{28,21}};
static const glyph_stroke_t stroke_77_10[2] = {{0,0},{6,0}};
static const glyph_stroke_t stroke_77_11[2] = {{14,0},{22,0}};
static const glyph_stroke_t stroke_77_12[2] = {{7,21},{9,20}};
static const glyph_stroke_t stroke_77_13[2] = {{8,21},{9,19}};
static const glyph_stroke_t stroke_77_14[2] = {{26,21},{24,19}};
static const glyph_stroke_t stroke_77_15[2] = {{27,21},{24,20}};
static const glyph_stroke_t stroke_77_16[2] = {{3,1},{1,0}};
static const glyph_stroke_t stroke_77_17[2] = {{3,1},{5,0}};
static const glyph_stroke_t stroke_77_18[2] = {{18,1},{15,0}};
static const glyph_stroke_t stroke_77_19[2] = {{18,2},{16,0}};
static const glyph_stroke_t stroke_77_20[2] = {{19,2},{20,0}};
static const glyph_stroke_t stroke_77_21[2] = {{18,1},{21,0}};
static const glyph_stroke_t *strokes_77[22] = {stroke_77_0, stroke_77_1, stroke_77_2, stroke_77_3, stroke_77_4, stroke_77_5, stroke_77_6, stroke_77_7, stroke_77_8, stroke_77_9, stroke_77_10, stroke_77_11, stroke_77_12, stroke_77_13, stroke_77_14, stroke_77_15, stroke_77_16, stroke_77_17, stroke_77_18, stroke_77_19, stroke_77_20, stroke_77_21};
static const uint8_t ncoords_77[22] = {2, 3, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_78_0[2] = {{9,21},{3,1}};
static const glyph_stroke_t stroke_78_1[2] = {{9,21},{16,0}};
static const glyph_stroke_t stroke_78_2[2] = {{10,21},{16,3}};
static const glyph_stroke_t stroke_78_3[2] = {{11,21},{17,3}};
static const glyph_stroke_t stroke_78_4[3] = {{22,20},{17,3},{16,0}};
static const glyph_stroke_t stroke_78_5[2] = {{6,21},{11,21}};
static const glyph_stroke_t stroke_78_6[2] = {{19,21},{25,21}};
static const glyph_stroke_t stroke_78_7[2] = {{0,0},{6,0}};
static const glyph_stroke_t stroke_78_8[2] = {{7,21},{10,20}};
static const glyph_stroke_t stroke_78_9[2] = {{8,21},{10,19}};
static const glyph_stroke_t stroke_78_10[2] = {{20,21},{22,20}};
static const glyph_stroke_t stroke_78_11[2] = {{24,21},{22,20}};
static const glyph_stroke_t stroke_78_12[2] = {{3,1},{1,0}};
static const glyph_stroke_t stroke_78_13[2] = {{3,1},{5,0}};
static const glyph_stroke_t *strokes_78[14] = {stroke_78_0, stroke_78_1, stroke_78_2, stroke_78_3, stroke_78_4, stroke_78_5, stroke_78_6, stroke_78_7, stroke_78_8, stroke_78_9, stroke_78_10, stroke_78_11, stroke_78_12, stroke_78_13};
static const uint8_t ncoords_78[14] = {2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_79_0[21] = {{9,21},{6,20},{4,18},{2,15},{1,12},{0,8},{0,5},{1,2},{2,1},{4,0},{7,0},{10,1},{12,3},{14,6},{15,9},{16,13},{16,16},{15,19},{14,20},{12,21},{9,21}};
static const glyph_stroke_t stroke_79_1[6] = {{5,18},{3,15},{2,12},{1,8},{1,4},{2,2}};
static const glyph_stroke_t stroke_79_2[6] = {{11,3},{13,6},{14,9},{15,13},{15,17},{14,19}};
static const glyph_stroke_t stroke_79_3[9] = {{9,21},{7,20},{5,17},{4,15},{3,12},{2,8},{2,3},{3,1},{4,0}};
static const glyph_stroke_t stroke_79_4[9] = {{7,0},{9,1},{11,4},{12,6},{13,9},{14,13},{14,18},{13,20},{12,21}};
static const glyph_stroke_t *strokes_79[5] = {stroke_79_0, stroke_79_1, stroke_79_2, stroke_79_3, stroke_79_4};
static const uint8_t ncoords_79[5] = {21, 6, 6, 9, 9};
static const glyph_stroke_t stroke_80_0[2] = {{9,21},{3,0}};
static const glyph_stroke_t stroke_80_1[2] = {{10,21},{4,0}};
static const glyph_stroke_t stroke_80_2[2] = {{11,21},{5,0}};
static const glyph_stroke_t stroke_80_3[9] = {{6,21},{18,21},{21,20},{22,18},{22,16},{21,13},{19,11},{15,10},{7,10}};
static const glyph_stroke_t stroke_80_4[5] = {{20,20},{21,18},{21,16},{20,13},{18,11}};
static const glyph_stroke_t stroke_80_5[7] = {{18,21},{19,20},{20,18},{20,16},{19,13},{17,11},{15,10}};
static const glyph_stroke_t stroke_80_6[2] = {{0,0},{8,0}};
static const glyph_stroke_t stroke_80_7[2] = {{7,21},{10,20}};
static const glyph_stroke_t stroke_80_8[2] = {{8,21},{9,19}};
static const glyph_stroke_t stroke_80_9[2] = {{12,21},{10,19}};
static const glyph_stroke_t stroke_80_10[2] = {{13,21},{10,20}};
static const glyph_stroke_t stroke_80_11[2] = {{4,1},{1,0}};
static const glyph_stroke_t stroke_80_12[2] = {{4,2},{2,0}};
static const glyph_stroke_t stroke_80_13[2] = {{5,2},{6,0}};
static const glyph_stroke_t stroke_80_14[2] = {{4,1},{7,0}};
static const glyph_stroke_t *strokes_80[15] = {stroke_80_0, stroke_80_1, stroke_80_2, stroke_80_3, stroke_80_4, stroke_80_5, stroke_80_6, stroke_80_7, stroke_80_8, stroke_80_9, stroke_80_10, stroke_80_11, stroke_80_12, stroke_80_13, stroke_80_14};
static const uint8_t ncoords_80[15] = {2, 2, 2, 9, 5, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_81_0[21] = {{9,21},{6,20},{4,18},{2,15},{1,12},{0,8},{0,5},{1,2},{2,1},{4,0},{7,0},{10,1},{12,3},{14,6},{15,9},{16,13},{16,16},{15,19},{14,20},{12,21},{9,21}};
static const glyph_stroke_t stroke_81_1[6] = {{5,18},{3,15},{2,12},{1,8},{1,4},{2,2}};
static const glyph_stroke_t stroke_81_2[6] = {{11,3},{13,6},{14,9},{15,13},{15,17},{14,19}};
static const glyph_stroke_t stroke_81_3[9] = {{9,21},{7,20},{5,17},{4,15},{3,12},{2,8},{2,3},{3,1},{4,0}};
static const glyph_stroke_t stroke_81_4[9] = {{7,0},{9,1},{11,4},{12,6},{13,9},{14,13},{14,18},{13,20},{12,21}};
static const glyph_stroke_t stroke_81_5[10] = {{2,3},{3,5},{5,6},{6,6},{8,5},{9,3},{10,-2},{11,-3},{12,-3},{13,-2}};
static const glyph_stroke_t stroke_81_6[3] = {{10,-3},{11,-4},{12,-4}};
static const glyph_stroke_t stroke_81_7[6] = {{9,3},{9,-4},{10,-5},{12,-5},{13,-2},{13,-1}};
static const glyph_stroke_t *strokes_81[8] = {stroke_81_0, stroke_81_1, stroke_81_2, stroke_81_3, stroke_81_4, stroke_81_5, stroke_81_6, stroke_81_7};
static const uint8_t ncoords_81[8] = {21, 6, 6, 9, 9, 10, 3, 6};
static const glyph_stroke_t stroke_82_0[2] = {{9,21},{3,0}};
static const glyph_stroke_t stroke_82_1[2] = {{10,21},{4,0}};
static const glyph_stroke_t stroke_82_2[2] = {{11,21},{5,0}};
static const glyph_stroke_t stroke_82_3[9] = {{6,21},{17,21},{20,20},{21,18},{21,16},{20,13},{19,12},{16,11},{8,11}};
static const glyph_stroke_t stroke_82_4[5] = {{19,20},{20,18},{20,16},{19,13},{18,12}};
static const glyph_stroke_t stroke_82_5[6] = {{17,21},{18,20},{19,18},{19,16},{18,13},{16,11}};
static const glyph_stroke_t stroke_82_6[7] = {{12,11},{14,10},{15,9},{17,3},{18,2},{19,2},{20,3}};
static const glyph_stroke_t stroke_82_7[3] = {{17,2},{18,1},{19,1}};
static const glyph_stroke_t stroke_82_8[6] = {{15,9},{16,1},{17,0},{19,0},{20,3},{20,4}};
static const glyph_stroke_t stroke_82_9[2] = {{0,0},{8,0}};
static const glyph_stroke_t stroke_82_10[2] = {{7,21},{10,20}};
static const glyph_stroke_t stroke_82_11[2] = {{8,21},{9,19}};
static const glyph_stroke_t stroke_82_12[2] = {{12,21},{10,19}};
static const glyph_stroke_t stroke_82_13[2] = {{13,21},{10,20}};
static const glyph_stroke_t stroke_82_14[2] = {{4,1},{1,0}};
static const glyph_stroke_t stroke_82_15[2] = {{4,2},{2,0}};
static const glyph_stroke_t stroke_82_16[2] = {{5,2},{6,0}};
static const glyph_stroke_t stroke_82_17[2] = {{4,1},{7,0}};
static const glyph_stroke_t *strokes_82[18] = {stroke_82_0, stroke_82_1, stroke_82_2, stroke_82_3, stroke_82_4, stroke_82_5, stroke_82_6, stroke_82_7, stroke_82_8, stroke_82_9, stroke_82_10, stroke_82_11, stroke_82_12, stroke_82_13, stroke_82_14, stroke_82_15, stroke_82_16, stroke_82_17};
static const uint8_t ncoords_82[18] = {2, 2, 2, 9, 5, 6, 7, 3, 6, 2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_83_0[18] = {{17,19},{18,19},{19,21},{18,15},{18,17},{17,19},{16,20},{13,21},{9,21},{6,20},{4,18},{4,15},{5,13},{7,11},{13,8},{14,6},{14,3},{13,1}};
static const glyph_stroke_t stroke_83_1[4] = {{5,15},{6,13},{13,9},{14,7}};
static const glyph_stroke_t stroke_83_2[19] = {{6,20},{5,18},{5,16},{6,14},{12,11},{14,9},{15,7},{15,4},{14,2},{13,1},{10,0},{6,0},{3,1},{2,2},{1,4},{1,6},{0,0},{1,2},{2,2}};
static const glyph_stroke_t *strokes_83[3] = {stroke_83_0, stroke_83_1, stroke_83_2};
static const uint8_t ncoords_83[3] = {18, 4, 19};
static const glyph_stroke_t stroke_84_0[2] = {{9,21},{3,0}};
static const glyph_stroke_t stroke_84_1[2] = {{10,21},{4,0}};
static const glyph_stroke_t stroke_84_2[2] = {{11,21},{5,0}};
static const glyph_stroke_t stroke_84_3[2] = {{2,21},{0,15}};
static const glyph_stroke_t stroke_84_4[2] = {{18,21},{17,15}};
static const glyph_stroke_t stroke_84_5[2] = {{2,21},{18,21}};
static const glyph_stroke_t stroke_84_6[2] = {{0,0},{8,0}};
static const glyph_stroke_t stroke_84_7[2] = {{3,21},{0,15}};
static const glyph_stroke_t stroke_84_8[2] = {{5,21},{1,18}};
static const glyph_stroke_t stroke_84_9[2] = {{7,21},{2,20}};
static const glyph_stroke_t stroke_84_10[2] = {{14,21},{17,20}};
static const glyph_stroke_t stroke_84_11[2] = {{15,21},{17,19}};
static const glyph_stroke_t stroke_84_12[2] = {{16,21},{17,18}};
static const glyph_stroke_t stroke_84_13[2] = {{17,21},{17,15}};
static const glyph_stroke_t stroke_84_14[2] = {{4,1},{1,0}};
static const glyph_stroke_t stroke_84_15[2] = {{4,2},{2,0}};
static const glyph_stroke_t stroke_84_16[2] = {{5,2},{6,0}};
static const glyph_stroke_t stroke_84_17[2] = {{4,1},{7,0}};
static const glyph_stroke_t *strokes_84[18] = {stroke_84_0, stroke_84_1, stroke_84_2, stroke_84_3, stroke_84_4, stroke_84_5, stroke_84_6, stroke_84_7, stroke_84_8, stroke_84_9, stroke_84_10, stroke_84_11, stroke_84_12, stroke_84_13, stroke_84_14, stroke_84_15, stroke_84_16, stroke_84_17};
static const uint8_t ncoords_84[18] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_85_0[11] = {{4,21},{1,10},{0,6},{0,3},{1,1},{4,0},{8,0},{11,1},{13,3},{14,6},{18,20}};
static const glyph_stroke_t stroke_85_1[5] = {{5,21},{2,10},{1,6},{1,2},{2,1}};
static const glyph_stroke_t stroke_85_2[5] = {{6,21},{3,10},{2,6},{2,2},{4,0}};
static const glyph_stroke_t stroke_85_3[2] = {{1,21},{9,21}};
static const glyph_stroke_t stroke_85_4[2] = {{15,21},{21,21}};
static const glyph_stroke_t stroke_85_5[2] = {{2,21},{5,20}};
static const glyph_stroke_t stroke_85_6[2] = {{3,21},{4,19}};
static const glyph_stroke_t stroke_85_7[2] = {{7,21},{5,19}};
static const glyph_stroke_t stroke_85_8[2] = {{8,21},{5,20}};
static const glyph_stroke_t stroke_85_9[2] = {{16,21},{18,20}};
static const glyph_stroke_t stroke_85_10[2] = {{20,21},{18,20}};
static const glyph_stroke_t *strokes_85[11] = {stroke_85_0, stroke_85_1, stroke_85_2, stroke_85_3, stroke_85_4, stroke_85_5, stroke_85_6, stroke_85_7, stroke_85_8, stroke_85_9, stroke_85_10};
static const uint8_t ncoords_85[11] = {11, 5, 5, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_86_0[4] = {{2,21},{2,19},{3,2},{3,0}};
static const glyph_stroke_t stroke_86_1[2] = {{3,20},{4,3}};
static const glyph_stroke_t stroke_86_2[2] = {{4,21},{5,4}};
static const glyph_stroke_t stroke_86_3[2] = {{15,20},{3,0}};
static const glyph_stroke_t stroke_86_4[2] = {{0,21},{7,21}};
static const glyph_stroke_t stroke_86_5[2] = {{12,21},{18,21}};
static const glyph_stroke_t stroke_86_6[2] = {{1,21},{2,19}};
static const glyph_stroke_t stroke_86_7[2] = {{5,21},{4,19}};
static const glyph_stroke_t stroke_86_8[2] = {{6,21},{3,20}};
static const glyph_stroke_t stroke_86_9[2] = {{13,21},{15,20}};
static const glyph_stroke_t stroke_86_10[2] = {{17,21},{15,20}};
static const glyph_stroke_t *strokes_86[11] = {stroke_86_0, stroke_86_1, stroke_86_2, stroke_86_3, stroke_86_4, stroke_86_5, stroke_86_6, stroke_86_7, stroke_86_8, stroke_86_9, stroke_86_10};
static const uint8_t ncoords_86[11] = {4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_87_0[4] = {{3,21},{3,19},{1,2},{1,0}};
static const glyph_stroke_t stroke_87_1[2] = {{4,20},{2,3}};
static const glyph_stroke_t stroke_87_2[2] = {{5,21},{3,4}};
static const glyph_stroke_t stroke_87_3[3] = {{11,21},{3,4},{1,0}};
static const glyph_stroke_t stroke_87_4[4] = {{11,21},{11,19},{9,2},{9,0}};
static const glyph_stroke_t stroke_87_5[2] = {{12,20},{10,3}};
static const glyph_stroke_t stroke_87_6[2] = {{13,21},{11,4}};
static const glyph_stroke_t stroke_87_7[3] = {{19,20},{11,4},{9,0}};
static const glyph_stroke_t stroke_87_8[2] = {{0,21},{8,21}};
static const glyph_stroke_t stroke_87_9[2] = {{11,21},{13,21}};
static const glyph_stroke_t stroke_87_10[2] = {{16,21},{22,21}};
static const glyph_stroke_t stroke_87_11[2] = {{1,21},{4,20}};
static const glyph_stroke_t stroke_87_12[2] = {{2,21},{3,19}};
static const glyph_stroke_t stroke_87_13[2] = {{6,21},{4,18}};
static const glyph_stroke_t stroke_87_14[2] = {{7,21},{4,20}};
static const glyph_stroke_t stroke_87_15[2] = {{17,21},{19,20}};
static const glyph_stroke_t stroke_87_16[2] = {{21,21},{19,20}};
static const glyph_stroke_t *strokes_87[17] = {stroke_87_0, stroke_87_1, stroke_87_2, stroke_87_3, stroke_87_4, stroke_87_5, stroke_87_6, stroke_87_7, stroke_87_8, stroke_87_9, stroke_87_10, stroke_87_11, stroke_87_12, stroke_87_13, stroke_87_14, stroke_87_15, stroke_87_16};
static const uint8_t ncoords_87[17] = {4, 2, 2, 3, 4, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_88_0[2] = {{8,21},{14,0}};
static const glyph_stroke_t stroke_88_1[2] = {{9,21},{15,0}};
static const glyph_stroke_t stroke_88_2[2] = {{10,21},{16,0}};
static const glyph_stroke_t stroke_88_3[2] = {{21,20},{3,1}};
static const glyph_stroke_t stroke_88_4[2] = {{6,21},{13,21}};
static const glyph_stroke_t stroke_88_5[2] = {{18,21},{24,21}};
static const glyph_stroke_t stroke_88_6[2] = {{0,0},{6,0}};
static const glyph_stroke_t stroke_88_7[2] = {{11,0},{18,0}};
static const glyph_stroke_t stroke_88_8[2] = {{7,21},{9,19}};
static const glyph_stroke_t stroke_88_9[2] = {{11,21},{10,19}};
static const glyph_stroke_t stroke_88_10[2] = {{12,21},{10,20}};
static const glyph_stroke_t stroke_88_11[2] = {{19,21},{21,20}};
static const glyph_stroke_t stroke_88_12[2] = {{23,21},{21,20}};
static const glyph_stroke_t stroke_88_13[2] = {{3,1},{1,0}};
static const glyph_stroke_t stroke_88_14[2] = {{3,1},{5,0}};
static const glyph_stroke_t stroke_88_15[2] = {{14,1},{12,0}};
static const glyph_stroke_t stroke_88_16[2] = {{14,2},{13,0}};
static const glyph_stroke_t stroke_88_17[2] = {{15,2},{17,0}};
static const glyph_stroke_t *strokes_88[18] = {stroke_88_0, stroke_88_1, stroke_88_2, stroke_88_3, stroke_88_4, stroke_88_5, stroke_88_6, stroke_88_7, stroke_88_8, stroke_88_9, stroke_88_10, stroke_88_11, stroke_88_12, stroke_88_13, stroke_88_14, stroke_88_15, stroke_88_16, stroke_88_17};
static const uint8_t ncoords_88[18] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_89_0[3] = {{2,21},{6,11},{3,0}};
static const glyph_stroke_t stroke_89_1[3] = {{3,21},{7,11},{4,0}};
static const glyph_stroke_t stroke_89_2[3] = {{4,21},{8,11},{5,0}};
static const glyph_stroke_t stroke_89_3[2] = {{17,20},{8,11}};
static const glyph_stroke_t stroke_89_4[2] = {{0,21},{7,21}};
static const glyph_stroke_t stroke_89_5[2] = {{14,21},{20,21}};
static const glyph_stroke_t stroke_89_6[2] = {{0,0},{8,0}};
static const glyph_stroke_t stroke_89_7[2] = {{1,21},{3,20}};
static const glyph_stroke_t stroke_89_8[2] = {{5,21},{4,19}};
static const glyph_stroke_t stroke_89_9[2] = {{6,21},{3,20}};
static const glyph_stroke_t stroke_89_10[2] = {{15,21},{17,20}};
static const glyph_stroke_t stroke_89_11[2] = {{19,21},{17,20}};
static const glyph_stroke_t stroke_89_12[2] = {{4,1},{1,0}};
static const glyph_stroke_t stroke_89_13[2] = {{4,2},{2,0}};
static const glyph_stroke_t stroke_89_14[2] = {{5,2},{6,0}};
static const glyph_stroke_t stroke_89_15[2] = {{4,1},{7,0}};
static const glyph_stroke_t *strokes_89[16] = {stroke_89_0, stroke_89_1, stroke_89_2, stroke_89_3, stroke_89_4, stroke_89_5, stroke_89_6, stroke_89_7, stroke_89_8, stroke_89_9, stroke_89_10, stroke_89_11, stroke_89_12, stroke_89_13, stroke_89_14, stroke_89_15};
static const uint8_t ncoords_89[16] = {3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_90_0[2] = {{18,21},{0,0}};
static const glyph_stroke_t stroke_90_1[2] = {{19,21},{1,0}};
static const glyph_stroke_t stroke_90_2[2] = {{20,21},{2,0}};
static const glyph_stroke_t stroke_90_3[3] = {{20,21},{6,21},{4,15}};
static const glyph_stroke_t stroke_90_4[3] = {{0,0},{14,0},{16,6}};
static const glyph_stroke_t stroke_90_5[2] = {{7,21},{4,15}};
static const glyph_stroke_t stroke_90_6[2] = {{8,21},{5,18}};
static const glyph_stroke_t stroke_90_7[2] = {{10,21},{6,20}};
static const glyph_stroke_t stroke_90_8[2] = {{10,0},{14,1}};
static const glyph_stroke_t stroke_90_9[2] = {{12,0},{15,3}};
static const glyph_stroke_t stroke_90_10[2] = {{13,0},{16,6}};
static const glyph_stroke_t *strokes_90[11] = {stroke_90_0, stroke_90_1, stroke_90_2, stroke_90_3, stroke_90_4, stroke_90_5, stroke_90_6, stroke_90_7, stroke_90_8, stroke_90_9, stroke_90_10};
static const uint8_t ncoords_90[11] = {2, 2, 2, 3, 3, 2, 2, 2, 2, 2, 2};
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
static const glyph_stroke_t stroke_94_0[3] = {{0,7},{8,12},{16,7}};
static const glyph_stroke_t stroke_94_1[3] = {{0,7},{8,11},{16,7}};
static const glyph_stroke_t *strokes_94[2] = {stroke_94_0, stroke_94_1};
static const uint8_t ncoords_94[2] = {3, 3};
static const glyph_stroke_t stroke_95_0[2] = {{0,-7},{20,-7}};
static const glyph_stroke_t *strokes_95[1] = {stroke_95_0};
static const uint8_t ncoords_95[1] = {2};
static const glyph_stroke_t stroke_96_0[2] = {{1,21},{6,15}};
static const glyph_stroke_t stroke_96_1[3] = {{1,21},{0,20},{6,15}};
static const glyph_stroke_t *strokes_96[2] = {stroke_96_0, stroke_96_1};
static const uint8_t ncoords_96[2] = {2, 3};
static const glyph_stroke_t stroke_97_0[8] = {{13,14},{11,7},{11,3},{12,1},{13,0},{15,0},{17,2},{18,4}};
static const glyph_stroke_t stroke_97_1[3] = {{14,14},{12,7},{12,1}};
static const glyph_stroke_t stroke_97_2[4] = {{13,14},{15,14},{13,7},{12,3}};
static const glyph_stroke_t stroke_97_3[17] = {{11,7},{11,10},{10,13},{8,14},{6,14},{3,13},{1,10},{0,7},{0,5},{1,2},{2,1},{4,0},{6,0},{8,1},{9,2},{10,4},{11,7}};
static const glyph_stroke_t stroke_97_4[5] = {{4,13},{2,10},{1,7},{1,4},{2,2}};
static const glyph_stroke_t stroke_97_5[7] = {{6,14},{4,12},{3,10},{2,7},{2,4},{3,1},{4,0}};
static const glyph_stroke_t *strokes_97[6] = {stroke_97_0, stroke_97_1, stroke_97_2, stroke_97_3, stroke_97_4, stroke_97_5};
static const uint8_t ncoords_97[6] = {8, 3, 4, 17, 5, 7};
static const glyph_stroke_t stroke_98_0[20] = {{3,21},{1,14},{0,8},{0,4},{1,2},{2,1},{4,0},{6,0},{9,1},{11,4},{12,7},{12,9},{11,12},{10,13},{8,14},{6,14},{4,13},{3,12},{2,10},{1,7}};
static const glyph_stroke_t stroke_98_1[5] = {{4,21},{2,14},{1,10},{1,4},{2,1}};
static const glyph_stroke_t stroke_98_2[5] = {{9,2},{10,4},{11,7},{11,10},{10,12}};
static const glyph_stroke_t stroke_98_3[4] = {{0,21},{5,21},{3,14},{1,7}};
static const glyph_stroke_t stroke_98_4[7] = {{6,0},{8,2},{9,4},{10,7},{10,10},{9,13},{8,14}};
static const glyph_stroke_t stroke_98_5[2] = {{1,21},{4,20}};
static const glyph_stroke_t stroke_98_6[2] = {{2,21},{3,19}};
static const glyph_stroke_t *strokes_98[7] = {stroke_98_0, stroke_98_1, stroke_98_2, stroke_98_3, stroke_98_4, stroke_98_5, stroke_98_6};
static const uint8_t ncoords_98[7] = {20, 5, 5, 4, 7, 2, 2};
static const glyph_stroke_t stroke_99_0[19] = {{11,10},{11,11},{10,11},{10,9},{12,9},{12,11},{11,13},{9,14},{6,14},{3,13},{1,10},{0,7},{0,5},{1,2},{2,1},{4,0},{6,0},{9,1},{11,4}};
static const glyph_stroke_t stroke_99_1[5] = {{3,12},{2,10},{1,7},{1,4},{2,2}};
static const glyph_stroke_t stroke_99_2[7] = {{6,14},{4,12},{3,10},{2,7},{2,4},{3,1},{4,0}};
static const glyph_stroke_t *strokes_99[3] = {stroke_99_0, stroke_99_1, stroke_99_2};
static const uint8_t ncoords_99[3] = {19, 5, 7};
static const glyph_stroke_t stroke_100_0[9] = {{15,21},{12,10},{11,6},{11,3},{12,1},{13,0},{15,0},{17,2},{18,4}};
static const glyph_stroke_t stroke_100_1[4] = {{16,21},{13,10},{12,6},{12,1}};
static const glyph_stroke_t stroke_100_2[4] = {{12,21},{17,21},{13,7},{12,3}};
static const glyph_stroke_t stroke_100_3[17] = {{11,7},{11,10},{10,13},{8,14},{6,14},{3,13},{1,10},{0,7},{0,5},{1,2},{2,1},{4,0},{6,0},{8,1},{9,2},{10,4},{11,7}};
static const glyph_stroke_t stroke_100_4[5] = {{3,12},{2,10},{1,7},{1,4},{2,2}};
static const glyph_stroke_t stroke_100_5[7] = {{6,14},{4,12},{3,10},{2,7},{2,4},{3,1},{4,0}};
static const glyph_stroke_t stroke_100_6[2] = {{13,21},{16,20}};
static const glyph_stroke_t stroke_100_7[2] = {{14,21},{15,19}};
static const glyph_stroke_t *strokes_100[8] = {stroke_100_0, stroke_100_1, stroke_100_2, stroke_100_3, stroke_100_4, stroke_100_5, stroke_100_6, stroke_100_7};
static const uint8_t ncoords_100[8] = {9, 4, 4, 17, 5, 7, 2, 2};
static const glyph_stroke_t stroke_101_0[18] = {{1,5},{5,6},{8,7},{11,9},{12,11},{11,13},{9,14},{6,14},{3,13},{1,10},{0,7},{0,5},{1,2},{2,1},{4,0},{6,0},{9,1},{11,3}};
static const glyph_stroke_t stroke_101_1[5] = {{3,12},{2,10},{1,7},{1,4},{2,2}};
static const glyph_stroke_t stroke_101_2[7] = {{6,14},{4,12},{3,10},{2,7},{2,4},{3,1},{4,0}};
static const glyph_stroke_t *strokes_101[3] = {stroke_101_0, stroke_101_1, stroke_101_2};
static const uint8_t ncoords_101[3] = {18, 5, 7};
static const glyph_stroke_t stroke_102_0[17] = {{18,19},{18,20},{17,20},{17,18},{19,18},{19,20},{18,21},{16,21},{14,20},{12,18},{11,16},{10,13},{9,9},{7,0},{6,-3},{5,-5},{3,-7}};
static const glyph_stroke_t stroke_102_1[5] = {{12,17},{11,14},{10,9},{8,0},{7,-3}};
static const glyph_stroke_t stroke_102_2[17] = {{16,21},{14,19},{13,17},{12,14},{11,9},{9,1},{8,-2},{7,-4},{5,-6},{3,-7},{1,-7},{0,-6},{0,-4},{2,-4},{2,-6},{1,-6},{1,-5}};
static const glyph_stroke_t stroke_102_3[2] = {{6,14},{17,14}};
static const glyph_stroke_t *strokes_102[4] = {stroke_102_0, stroke_102_1, stroke_102_2, stroke_102_3};
static const uint8_t ncoords_102[4] = {17, 5, 17, 2};
static const glyph_stroke_t stroke_103_0[5] = {{15,14},{11,0},{10,-3},{8,-6},{6,-7}};
static const glyph_stroke_t stroke_103_1[3] = {{16,14},{12,0},{10,-4}};
static const glyph_stroke_t stroke_103_2[14] = {{15,14},{17,14},{13,0},{11,-4},{9,-6},{6,-7},{3,-7},{1,-6},{0,-5},{0,-3},{2,-3},{2,-5},{1,-5},{1,-4}};
static const glyph_stroke_t stroke_103_3[17] = {{13,7},{13,10},{12,13},{10,14},{8,14},{5,13},{3,10},{2,7},{2,5},{3,2},{4,1},{6,0},{8,0},{10,1},{11,2},{12,4},{13,7}};
static const glyph_stroke_t stroke_103_4[5] = {{5,12},{4,10},{3,7},{3,4},{4,2}};
static const glyph_stroke_t stroke_103_5[7] = {{8,14},{6,12},{5,10},{4,7},{4,4},{5,1},{6,0}};
static const glyph_stroke_t *strokes_103[6] = {stroke_103_0, stroke_103_1, stroke_103_2, stroke_103_3, stroke_103_4, stroke_103_5};
static const uint8_t ncoords_103[6] = {5, 3, 14, 17, 5, 7};
static const glyph_stroke_t stroke_104_0[3] = {{6,21},{0,0},{2,0}};
static const glyph_stroke_t stroke_104_1[2] = {{7,21},{1,0}};
static const glyph_stroke_t stroke_104_2[3] = {{3,21},{8,21},{2,0}};
static const glyph_stroke_t stroke_104_3[9] = {{4,7},{6,11},{8,13},{10,14},{12,14},{14,13},{15,11},{15,8},{13,3}};
static const glyph_stroke_t stroke_104_4[4] = {{14,13},{14,9},{13,5},{13,1}};
static const glyph_stroke_t stroke_104_5[8] = {{14,11},{12,6},{12,3},{13,1},{14,0},{16,0},{18,2},{19,4}};
static const glyph_stroke_t stroke_104_6[2] = {{4,21},{7,20}};
static const glyph_stroke_t stroke_104_7[2] = {{5,21},{6,19}};
static const glyph_stroke_t *strokes_104[8] = {stroke_104_0, stroke_104_1, stroke_104_2, stroke_104_3, stroke_104_4, stroke_104_5, stroke_104_6, stroke_104_7};
static const uint8_t ncoords_104[8] = {3, 2, 3, 9, 4, 8, 2, 2};
static const glyph_stroke_t stroke_105_0[5] = {{7,21},{7,19},{9,19},{9,21},{7,21}};
static const glyph_stroke_t stroke_105_1[2] = {{8,21},{8,19}};
static const glyph_stroke_t stroke_105_2[2] = {{7,20},{9,20}};
static const glyph_stroke_t stroke_105_3[8] = {{0,10},{1,12},{3,14},{5,14},{6,13},{7,11},{7,8},{5,3}};
static const glyph_stroke_t stroke_105_4[4] = {{6,13},{6,9},{5,5},{5,1}};
static const glyph_stroke_t stroke_105_5[8] = {{6,11},{4,6},{4,3},{5,1},{6,0},{8,0},{10,2},{11,4}};
static const glyph_stroke_t *strokes_105[6] = {stroke_105_0, stroke_105_1, stroke_105_2, stroke_105_3, stroke_105_4, stroke_105_5};
static const uint8_t ncoords_105[6] = {5, 2, 2, 8, 4, 8};
static const glyph_stroke_t stroke_106_0[5] = {{12,21},{12,19},{14,19},{14,21},{12,21}};
static const glyph_stroke_t stroke_106_1[2] = {{13,21},{13,19}};
static const glyph_stroke_t stroke_106_2[2] = {{12,20},{14,20}};
static const glyph_stroke_t stroke_106_3[19] = {{4,10},{5,12},{7,14},{9,14},{10,13},{11,11},{11,8},{9,1},{8,-2},{7,-4},{5,-6},{3,-7},{1,-7},{0,-6},{0,-4},{2,-4},{2,-6},{1,-6},{1,-5}};
static const glyph_stroke_t stroke_106_4[5] = {{10,13},{10,8},{8,1},{7,-2},{6,-4}};
static const glyph_stroke_t stroke_106_5[6] = {{10,11},{9,7},{7,0},{6,-3},{5,-5},{3,-7}};
static const glyph_stroke_t *strokes_106[6] = {stroke_106_0, stroke_106_1, stroke_106_2, stroke_106_3, stroke_106_4, stroke_106_5};
static const uint8_t ncoords_106[6] = {5, 2, 2, 19, 5, 6};
static const glyph_stroke_t stroke_107_0[3] = {{6,21},{0,0},{2,0}};
static const glyph_stroke_t stroke_107_1[2] = {{7,21},{1,0}};
static const glyph_stroke_t stroke_107_2[3] = {{3,21},{8,21},{2,0}};
static const glyph_stroke_t stroke_107_3[11] = {{16,12},{16,13},{15,13},{15,11},{17,11},{17,13},{16,14},{14,14},{12,13},{8,9},{6,8}};
static const glyph_stroke_t stroke_107_4[7] = {{4,8},{6,8},{8,7},{9,6},{11,2},{12,1},{14,1}};
static const glyph_stroke_t stroke_107_5[3] = {{8,6},{10,2},{11,1}};
static const glyph_stroke_t stroke_107_6[7] = {{6,8},{7,7},{9,1},{10,0},{12,0},{14,1},{16,4}};
static const glyph_stroke_t stroke_107_7[2] = {{4,21},{7,20}};
static const glyph_stroke_t stroke_107_8[2] = {{5,21},{6,19}};
static const glyph_stroke_t *strokes_107[9] = {stroke_107_0, stroke_107_1, stroke_107_2, stroke_107_3, stroke_107_4, stroke_107_5, stroke_107_6, stroke_107_7, stroke_107_8};
static const uint8_t ncoords_107[9] = {3, 2, 3, 11, 7, 3, 7, 2, 2};
static const glyph_stroke_t stroke_108_0[9] = {{4,21},{1,10},{0,6},{0,3},{1,1},{2,0},{4,0},{6,2},{7,4}};
static const glyph_stroke_t stroke_108_1[4] = {{5,21},{2,10},{1,6},{1,1}};
static const glyph_stroke_t stroke_108_2[4] = {{1,21},{6,21},{2,7},{1,3}};
static const glyph_stroke_t stroke_108_3[2] = {{2,21},{5,20}};
static const glyph_stroke_t stroke_108_4[2] = {{3,21},{4,19}};
static const glyph_stroke_t *strokes_108[5] = {stroke_108_0, stroke_108_1, stroke_108_2, stroke_108_3, stroke_108_4};
static const uint8_t ncoords_108[5] = {9, 4, 4, 2, 2};
static const glyph_stroke_t stroke_109_0[8] = {{0,10},{1,12},{3,14},{5,14},{6,13},{7,11},{7,8},{5,0}};
static const glyph_stroke_t stroke_109_1[3] = {{6,13},{6,8},{4,0}};
static const glyph_stroke_t stroke_109_2[4] = {{6,11},{5,7},{3,0},{5,0}};
static const glyph_stroke_t stroke_109_3[9] = {{7,8},{9,11},{11,13},{13,14},{15,14},{17,13},{18,11},{18,8},{16,0}};
static const glyph_stroke_t stroke_109_4[3] = {{17,13},{17,8},{15,0}};
static const glyph_stroke_t stroke_109_5[4] = {{17,11},{16,7},{14,0},{16,0}};
static const glyph_stroke_t stroke_109_6[9] = {{18,8},{20,11},{22,13},{24,14},{26,14},{28,13},{29,11},{29,8},{27,3}};
static const glyph_stroke_t stroke_109_7[4] = {{28,13},{28,9},{27,5},{27,1}};
static const glyph_stroke_t stroke_109_8[8] = {{28,11},{26,6},{26,3},{27,1},{28,0},{30,0},{32,2},{33,4}};
static const glyph_stroke_t *strokes_109[9] = {stroke_109_0, stroke_109_1, stroke_109_2, stroke_109_3, stroke_109_4, stroke_109_5, stroke_109_6, stroke_109_7, stroke_109_8};
static const uint8_t ncoords_109[9] = {8, 3, 4, 9, 3, 4, 9, 4, 8};
static const glyph_stroke_t stroke_110_0[8] = {{0,10},{1,12},{3,14},{5,14},{6,13},{7,11},{7,8},{5,0}};
static const glyph_stroke_t stroke_110_1[3] = {{6,13},{6,8},{4,0}};
static const glyph_stroke_t stroke_110_2[4] = {{6,11},{5,7},{3,0},{5,0}};
static const glyph_stroke_t stroke_110_3[9] = {{7,8},{9,11},{11,13},{13,14},{15,14},{17,13},{18,11},{18,8},{16,3}};
static const glyph_stroke_t stroke_110_4[4] = {{17,13},{17,9},{16,5},{16,1}};
static const glyph_stroke_t stroke_110_5[8] = {{17,11},{15,6},{15,3},{16,1},{17,0},{19,0},{21,2},{22,4}};
static const glyph_stroke_t *strokes_110[6] = {stroke_110_0, stroke_110_1, stroke_110_2, stroke_110_3, stroke_110_4, stroke_110_5};
static const uint8_t ncoords_110[6] = {8, 3, 4, 9, 4, 8};
static const glyph_stroke_t stroke_111_0[17] = {{6,14},{3,13},{1,10},{0,7},{0,5},{1,2},{2,1},{5,0},{8,0},{11,1},{13,4},{14,7},{14,9},{13,12},{12,13},{9,14},{6,14}};
static const glyph_stroke_t stroke_111_1[5] = {{3,12},{2,10},{1,7},{1,4},{2,2}};
static const glyph_stroke_t stroke_111_2[5] = {{11,2},{12,4},{13,7},{13,10},{12,12}};
static const glyph_stroke_t stroke_111_3[7] = {{6,14},{4,12},{3,10},{2,7},{2,4},{3,1},{5,0}};
static const glyph_stroke_t stroke_111_4[7] = {{8,0},{10,2},{11,4},{12,7},{12,10},{11,13},{9,14}};
static const glyph_stroke_t *strokes_111[5] = {stroke_111_0, stroke_111_1, stroke_111_2, stroke_111_3, stroke_111_4};
static const uint8_t ncoords_111[5] = {17, 5, 5, 7, 7};
static const glyph_stroke_t stroke_112_0[9] = {{2,10},{3,12},{5,14},{7,14},{8,13},{9,11},{9,8},{8,4},{5,-7}};
static const glyph_stroke_t stroke_112_1[4] = {{8,13},{8,8},{7,4},{4,-7}};
static const glyph_stroke_t stroke_112_2[3] = {{8,11},{7,7},{3,-7}};
static const glyph_stroke_t stroke_112_3[17] = {{9,7},{10,10},{11,12},{12,13},{14,14},{16,14},{18,13},{19,12},{20,9},{20,7},{19,4},{17,1},{14,0},{12,0},{10,1},{9,4},{9,7}};
static const glyph_stroke_t stroke_112_4[5] = {{18,12},{19,10},{19,7},{18,4},{17,2}};
static const glyph_stroke_t stroke_112_5[7] = {{16,14},{17,13},{18,10},{18,7},{17,4},{16,2},{14,0}};
static const glyph_stroke_t stroke_112_6[2] = {{0,-7},{8,-7}};
static const glyph_stroke_t stroke_112_7[2] = {{4,-6},{1,-7}};
static const glyph_stroke_t stroke_112_8[2] = {{4,-5},{2,-7}};
static const glyph_stroke_t stroke_112_9[2] = {{5,-5},{6,-7}};
static const glyph_stroke_t stroke_112_10[2] = {{4,-6},{7,-7}};
static const glyph_stroke_t *strokes_112[11] = {stroke_112_0, stroke_112_1, stroke_112_2, stroke_112_3, stroke_112_4, stroke_112_5, stroke_112_6, stroke_112_7, stroke_112_8, stroke_112_9, stroke_112_10};
static const uint8_t ncoords_112[11] = {9, 4, 3, 17, 5, 7, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_113_0[2] = {{13,14},{7,-7}};
static const glyph_stroke_t stroke_113_1[2] = {{14,14},{8,-7}};
static const glyph_stroke_t stroke_113_2[3] = {{13,14},{15,14},{9,-7}};
static const glyph_stroke_t stroke_113_3[17] = {{11,7},{11,10},{10,13},{8,14},{6,14},{3,13},{1,10},{0,7},{0,5},{1,2},{2,1},{4,0},{6,0},{8,1},{9,2},{10,4},{11,7}};
static const glyph_stroke_t stroke_113_4[5] = {{3,12},{2,10},{1,7},{1,4},{2,2}};
static const glyph_stroke_t stroke_113_5[7] = {{6,14},{4,12},{3,10},{2,7},{2,4},{3,1},{4,0}};
static const glyph_stroke_t stroke_113_6[2] = {{4,-7},{12,-7}};
static const glyph_stroke_t stroke_113_7[2] = {{8,-6},{5,-7}};
static const glyph_stroke_t stroke_113_8[2] = {{8,-5},{6,-7}};
static const glyph_stroke_t stroke_113_9[2] = {{9,-5},{10,-7}};
static const glyph_stroke_t stroke_113_10[2] = {{8,-6},{11,-7}};
static const glyph_stroke_t *strokes_113[11] = {stroke_113_0, stroke_113_1, stroke_113_2, stroke_113_3, stroke_113_4, stroke_113_5, stroke_113_6, stroke_113_7, stroke_113_8, stroke_113_9, stroke_113_10};
static const uint8_t ncoords_113[11] = {2, 2, 3, 17, 5, 7, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_114_0[8] = {{0,10},{1,12},{3,14},{5,14},{6,13},{7,11},{7,7},{5,0}};
static const glyph_stroke_t stroke_114_1[3] = {{6,13},{6,7},{4,0}};
static const glyph_stroke_t stroke_114_2[4] = {{6,11},{5,7},{3,0},{5,0}};
static const glyph_stroke_t stroke_114_3[11] = {{15,12},{15,13},{14,13},{14,11},{16,11},{16,13},{15,14},{13,14},{11,13},{9,11},{7,7}};
static const glyph_stroke_t *strokes_114[4] = {stroke_114_0, stroke_114_1, stroke_114_2, stroke_114_3};
static const uint8_t ncoords_114[4] = {8, 3, 4, 11};
static const glyph_stroke_t stroke_115_0[17] = {{12,11},{12,12},{11,12},{11,10},{13,10},{13,12},{12,13},{9,14},{6,14},{3,13},{2,12},{2,10},{3,8},{5,7},{8,6},{10,5},{11,3}};
static const glyph_stroke_t stroke_115_1[2] = {{3,13},{2,10}};
static const glyph_stroke_t stroke_115_2[4] = {{3,9},{5,8},{8,7},{10,6}};
static const glyph_stroke_t stroke_115_3[2] = {{11,5},{10,1}};
static const glyph_stroke_t stroke_115_4[17] = {{2,12},{3,10},{5,9},{8,8},{10,7},{11,5},{11,3},{10,1},{7,0},{4,0},{1,1},{0,2},{0,4},{2,4},{2,2},{1,2},{1,3}};
static const glyph_stroke_t *strokes_115[5] = {stroke_115_0, stroke_115_1, stroke_115_2, stroke_115_3, stroke_115_4};
static const uint8_t ncoords_115[5] = {17, 2, 4, 2, 17};
static const glyph_stroke_t stroke_116_0[9] = {{6,21},{3,10},{2,6},{2,3},{3,1},{4,0},{6,0},{8,2},{9,4}};
static const glyph_stroke_t stroke_116_1[4] = {{7,21},{4,10},{3,6},{3,1}};
static const glyph_stroke_t stroke_116_2[4] = {{6,21},{8,21},{4,7},{3,3}};
static const glyph_stroke_t stroke_116_3[2] = {{0,14},{10,14}};
static const glyph_stroke_t *strokes_116[4] = {stroke_116_0, stroke_116_1, stroke_116_2, stroke_116_3};
static const uint8_t ncoords_116[4] = {9, 4, 4, 2};
static const glyph_stroke_t stroke_117_0[8] = {{0,10},{1,12},{3,14},{5,14},{6,13},{7,11},{7,8},{5,3}};
static const glyph_stroke_t stroke_117_1[4] = {{6,13},{6,9},{5,5},{5,1}};
static const glyph_stroke_t stroke_117_2[9] = {{6,11},{4,6},{4,3},{5,1},{7,0},{9,0},{11,1},{13,3},{15,6}};
static const glyph_stroke_t stroke_117_3[8] = {{17,14},{15,6},{15,3},{16,1},{17,0},{19,0},{21,2},{22,4}};
static const glyph_stroke_t stroke_117_4[3] = {{18,14},{16,6},{16,1}};
static const glyph_stroke_t stroke_117_5[4] = {{17,14},{19,14},{17,7},{16,3}};
static const glyph_stroke_t *strokes_117[6] = {stroke_117_0, stroke_117_1, stroke_117_2, stroke_117_3, stroke_117_4, stroke_117_5};
static const uint8_t ncoords_117[6] = {8, 4, 9, 8, 3, 4};
static const glyph_stroke_t stroke_118_0[8] = {{0,10},{1,12},{3,14},{5,14},{6,13},{7,11},{7,8},{5,3}};
static const glyph_stroke_t stroke_118_1[4] = {{6,13},{6,9},{5,5},{5,1}};
static const glyph_stroke_t stroke_118_2[14] = {{6,11},{4,6},{4,3},{5,1},{7,0},{9,0},{11,1},{13,3},{15,6},{16,10},{16,14},{15,14},{15,13},{16,11}};
static const glyph_stroke_t *strokes_118[3] = {stroke_118_0, stroke_118_1, stroke_118_2};
static const uint8_t ncoords_118[3] = {8, 4, 14};
static const glyph_stroke_t stroke_119_0[8] = {{0,10},{1,12},{3,14},{5,14},{6,13},{7,11},{7,8},{5,3}};
static const glyph_stroke_t stroke_119_1[4] = {{6,13},{6,9},{5,5},{5,1}};
static const glyph_stroke_t stroke_119_2[9] = {{6,11},{4,6},{4,3},{5,1},{7,0},{9,0},{11,1},{13,3},{14,6}};
static const glyph_stroke_t stroke_119_3[14] = {{16,14},{14,6},{14,3},{15,1},{17,0},{19,0},{21,1},{23,3},{25,6},{26,10},{26,14},{25,14},{25,13},{26,11}};
static const glyph_stroke_t stroke_119_4[3] = {{17,14},{15,6},{15,1}};
static const glyph_stroke_t stroke_119_5[4] = {{16,14},{18,14},{16,7},{15,3}};
static const glyph_stroke_t *strokes_119[6] = {stroke_119_0, stroke_119_1, stroke_119_2, stroke_119_3, stroke_119_4, stroke_119_5};
static const uint8_t ncoords_119[6] = {8, 4, 9, 14, 3, 4};
static const glyph_stroke_t stroke_120_0[7] = {{2,10},{4,13},{6,14},{8,14},{10,13},{11,11},{11,9}};
static const glyph_stroke_t stroke_120_1[14] = {{8,14},{9,13},{9,9},{8,5},{7,3},{5,1},{3,0},{1,0},{0,1},{0,3},{2,3},{2,1},{1,1},{1,2}};
static const glyph_stroke_t stroke_120_2[4] = {{10,12},{10,9},{9,5},{9,2}};
static const glyph_stroke_t stroke_120_3[14] = {{18,12},{18,13},{17,13},{17,11},{19,11},{19,13},{18,14},{16,14},{14,13},{12,11},{11,9},{10,5},{10,1},{11,0}};
static const glyph_stroke_t stroke_120_4[7] = {{8,5},{8,3},{9,1},{11,0},{13,0},{15,1},{17,4}};
static const glyph_stroke_t *strokes_120[5] = {stroke_120_0, stroke_120_1, stroke_120_2, stroke_120_3, stroke_120_4};
static const uint8_t ncoords_120[5] = {7, 14, 4, 14, 7};
static const glyph_stroke_t stroke_121_0[8] = {{0,10},{1,12},{3,14},{5,14},{6,13},{7,11},{7,8},{5,3}};
static const glyph_stroke_t stroke_121_1[4] = {{6,13},{6,9},{5,5},{5,1}};
static const glyph_stroke_t stroke_121_2[9] = {{6,11},{4,6},{4,3},{5,1},{7,0},{9,0},{11,1},{13,3},{15,7}};
static const glyph_stroke_t stroke_121_3[5] = {{17,14},{13,0},{12,-3},{10,-6},{8,-7}};
static const glyph_stroke_t stroke_121_4[3] = {{18,14},{14,0},{12,-4}};
static const glyph_stroke_t stroke_121_5[14] = {{17,14},{19,14},{15,0},{13,-4},{11,-6},{8,-7},{5,-7},{3,-6},{2,-5},{2,-3},{4,-3},{4,-5},{3,-5},{3,-4}};
static const glyph_stroke_t *strokes_121[6] = {stroke_121_0, stroke_121_1, stroke_121_2, stroke_121_3, stroke_121_4, stroke_121_5};
static const uint8_t ncoords_121[6] = {8, 4, 9, 5, 3, 14};
static const glyph_stroke_t stroke_122_0[6] = {{14,14},{13,12},{11,10},{3,4},{1,2},{0,0}};
static const glyph_stroke_t stroke_122_1[4] = {{13,12},{4,12},{2,11},{1,9}};
static const glyph_stroke_t stroke_122_2[4] = {{11,12},{7,13},{4,13},{3,12}};
static const glyph_stroke_t stroke_122_3[5] = {{11,12},{7,14},{4,14},{2,12},{1,9}};
static const glyph_stroke_t stroke_122_4[4] = {{1,2},{10,2},{12,3},{13,5}};
static const glyph_stroke_t stroke_122_5[4] = {{3,2},{7,1},{10,1},{11,2}};
static const glyph_stroke_t stroke_122_6[5] = {{3,2},{7,0},{10,0},{12,2},{13,5}};
static const glyph_stroke_t *strokes_122[7] = {stroke_122_0, stroke_122_1, stroke_122_2, stroke_122_3, stroke_122_4, stroke_122_5, stroke_122_6};
static const uint8_t ncoords_122[7] = {6, 4, 4, 5, 4, 4, 5};
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
static const glyph_stroke_t stroke_127_0[34] = {{0,21},{0,0},{1,0},{1,21},{2,21},{2,0},{3,0},{3,21},{4,21},{4,0},{5,0},{5,21},{6,21},{6,0},{7,0},{7,21},{8,21},{8,0},{9,0},{9,21},{10,21},{10,0},{11,0},{11,21},{12,21},{12,0},{13,0},{13,21},{14,21},{14,0},{15,0},{15,21},{16,21},{16,0}};
static const glyph_stroke_t *strokes_127[1] = {stroke_127_0};
static const uint8_t ncoords_127[1] = {34};
static const glyph_stroke_t stroke_9811_0[8] = {{1,19},{5,17},{7,15},{8,12},{8,9},{7,6},{5,4},{1,2}};
static const glyph_stroke_t stroke_9811_1[5] = {{1,19},{4,18},{6,17},{8,15},{9,12}};
static const glyph_stroke_t stroke_9811_2[5] = {{9,9},{8,6},{6,4},{4,3},{1,2}};
static const glyph_stroke_t stroke_9811_3[5] = {{17,19},{14,18},{12,17},{10,15},{9,12}};
static const glyph_stroke_t stroke_9811_4[5] = {{9,9},{10,6},{12,4},{14,3},{17,2}};
static const glyph_stroke_t stroke_9811_5[8] = {{17,19},{13,17},{11,15},{10,12},{10,9},{11,6},{13,4},{17,2}};
static const glyph_stroke_t stroke_9811_6[2] = {{0,11},{18,11}};
static const glyph_stroke_t stroke_9811_7[2] = {{0,10},{18,10}};
static const glyph_stroke_t *strokes_9811[8] = {stroke_9811_0, stroke_9811_1, stroke_9811_2, stroke_9811_3, stroke_9811_4, stroke_9811_5, stroke_9811_6, stroke_9811_7};
static const uint8_t ncoords_9811[8] = {8, 5, 5, 5, 5, 8, 2, 2};
static const glyph_stroke_t stroke_9737_0[21] = {{9,21},{6,20},{3,18},{1,15},{0,12},{0,9},{1,6},{3,3},{6,1},{9,0},{12,0},{15,1},{18,3},{20,6},{21,9},{21,12},{20,15},{18,18},{15,20},{12,21},{9,21}};
static const glyph_stroke_t stroke_9737_1[9] = {{10,12},{9,11},{9,10},{10,9},{11,9},{12,10},{12,11},{11,12},{10,12}};
static const glyph_stroke_t stroke_9737_2[5] = {{10,11},{10,10},{11,10},{11,11},{10,11}};
static const glyph_stroke_t *strokes_9737[3] = {stroke_9737_0, stroke_9737_1, stroke_9737_2};
static const uint8_t ncoords_9737[3] = {21, 9, 5};
static const glyph_stroke_t stroke_9791_0[4] = {{3,21},{1,20},{2,18},{4,17}};
static const glyph_stroke_t stroke_9791_1[3] = {{3,21},{2,20},{2,18}};
static const glyph_stroke_t stroke_9791_2[4] = {{8,21},{10,20},{9,18},{7,17}};
static const glyph_stroke_t stroke_9791_3[3] = {{8,21},{9,20},{9,18}};
static const glyph_stroke_t stroke_9791_4[17] = {{4,17},{2,16},{1,15},{0,13},{0,10},{1,8},{2,7},{4,6},{7,6},{9,7},{10,8},{11,10},{11,13},{10,15},{9,16},{7,17},{4,17}};
static const glyph_stroke_t stroke_9791_5[2] = {{5,6},{5,0}};
static const glyph_stroke_t stroke_9791_6[2] = {{6,6},{6,0}};
static const glyph_stroke_t stroke_9791_7[2] = {{1,3},{10,3}};
static const glyph_stroke_t *strokes_9791[8] = {stroke_9791_0, stroke_9791_1, stroke_9791_2, stroke_9791_3, stroke_9791_4, stroke_9791_5, stroke_9791_6, stroke_9791_7};
static const uint8_t ncoords_9791[8] = {4, 3, 4, 3, 17, 2, 2, 2};
static const glyph_stroke_t stroke_9792_0[17] = {{6,21},{3,20},{1,18},{0,15},{0,14},{1,11},{3,9},{6,8},{7,8},{10,9},{12,11},{13,14},{13,15},{12,18},{10,20},{7,21},{6,21}};
static const glyph_stroke_t stroke_9792_1[2] = {{6,8},{6,0}};
static const glyph_stroke_t stroke_9792_2[2] = {{7,8},{7,0}};
static const glyph_stroke_t stroke_9792_3[2] = {{2,4},{11,4}};
static const glyph_stroke_t *strokes_9792[4] = {stroke_9792_0, stroke_9792_1, stroke_9792_2, stroke_9792_3};
static const uint8_t ncoords_9792[4] = {17, 2, 2, 2};
static const glyph_stroke_t stroke_10753_0[21] = {{9,21},{6,20},{3,18},{1,15},{0,12},{0,8},{1,5},{3,2},{6,0},{9,-1},{13,-1},{16,0},{19,2},{21,5},{22,8},{22,12},{21,15},{19,18},{16,20},{13,21},{9,21}};
static const glyph_stroke_t stroke_10753_1[2] = {{11,21},{11,-1}};
static const glyph_stroke_t stroke_10753_2[2] = {{0,10},{22,10}};
static const glyph_stroke_t *strokes_10753[3] = {stroke_10753_0, stroke_10753_1, stroke_10753_2};
static const uint8_t ncoords_10753[3] = {21, 2, 2};
static const glyph_stroke_t stroke_9794_0[17] = {{6,14},{3,13},{1,11},{0,8},{0,7},{1,4},{3,2},{6,1},{7,1},{10,2},{12,4},{13,7},{13,8},{12,11},{10,13},{7,14},{6,14}};
static const glyph_stroke_t stroke_9794_1[4] = {{19,20},{13,20},{17,19},{11,13}};
static const glyph_stroke_t stroke_9794_2[4] = {{19,20},{19,14},{18,18},{12,12}};
static const glyph_stroke_t stroke_9794_3[2] = {{18,19},{12,13}};
static const glyph_stroke_t *strokes_9794[4] = {stroke_9794_0, stroke_9794_1, stroke_9794_2, stroke_9794_3};
static const uint8_t ncoords_9794[4] = {17, 4, 4, 2};
static const glyph_stroke_t stroke_9795_0[11] = {{0,18},{1,20},{3,21},{6,21},{8,20},{9,18},{9,15},{8,12},{7,10},{5,8},{2,6}};
static const glyph_stroke_t stroke_9795_1[6] = {{6,21},{7,20},{8,18},{8,14},{7,11},{5,8}};
static const glyph_stroke_t stroke_9795_2[2] = {{13,21},{11,0}};
static const glyph_stroke_t stroke_9795_3[2] = {{14,21},{10,0}};
static const glyph_stroke_t stroke_9795_4[2] = {{2,6},{16,6}};
static const glyph_stroke_t *strokes_9795[5] = {stroke_9795_0, stroke_9795_1, stroke_9795_2, stroke_9795_3, stroke_9795_4};
static const uint8_t ncoords_9795[5] = {11, 6, 2, 2, 2};
static const glyph_stroke_t stroke_9796_0[2] = {{2,21},{2,6}};
static const glyph_stroke_t stroke_9796_1[2] = {{3,21},{2,10}};
static const glyph_stroke_t stroke_9796_2[10] = {{2,10},{3,12},{4,13},{6,14},{9,14},{12,13},{13,11},{13,9},{12,7},{10,5}};
static const glyph_stroke_t stroke_9796_3[9] = {{9,14},{11,13},{12,11},{12,9},{9,3},{9,1},{10,0},{12,0},{14,2}};
static const glyph_stroke_t stroke_9796_4[2] = {{0,21},{3,21}};
static const glyph_stroke_t *strokes_9796[5] = {stroke_9796_0, stroke_9796_1, stroke_9796_2, stroke_9796_3, stroke_9796_4};
static const uint8_t ncoords_9796[5] = {2, 2, 10, 9, 2};
static const glyph_stroke_t stroke_9896_0[17] = {{6,13},{3,12},{1,10},{0,7},{0,6},{1,3},{3,1},{6,0},{7,0},{10,1},{12,3},{13,6},{13,7},{12,10},{10,12},{7,13},{6,13}};
static const glyph_stroke_t stroke_9896_1[4] = {{6,19},{2,17},{6,21},{6,13}};
static const glyph_stroke_t stroke_9896_2[4] = {{7,19},{11,17},{7,21},{7,13}};
static const glyph_stroke_t stroke_9896_3[9] = {{6,8},{5,7},{5,6},{6,5},{7,5},{8,6},{8,7},{7,8},{6,8}};
static const glyph_stroke_t stroke_9896_4[5] = {{6,7},{6,6},{7,6},{7,7},{6,7}};
static const glyph_stroke_t *strokes_9896[5] = {stroke_9896_0, stroke_9896_1, stroke_9896_2, stroke_9896_3, stroke_9896_4};
static const uint8_t ncoords_9896[5] = {17, 4, 4, 9, 5};
static const glyph_stroke_t stroke_9798_0[3] = {{7,19},{8,21},{8,0}};
static const glyph_stroke_t stroke_9798_1[3] = {{10,19},{9,21},{9,0}};
static const glyph_stroke_t stroke_9798_2[7] = {{0,19},{1,21},{1,14},{2,11},{4,9},{7,8},{8,8}};
static const glyph_stroke_t stroke_9798_3[4] = {{3,19},{2,21},{2,13},{3,10}};
static const glyph_stroke_t stroke_9798_4[7] = {{17,19},{16,21},{16,14},{15,11},{13,9},{10,8},{9,8}};
static const glyph_stroke_t stroke_9798_5[4] = {{14,19},{15,21},{15,13},{14,10}};
static const glyph_stroke_t stroke_9798_6[2] = {{4,4},{13,4}};
static const glyph_stroke_t *strokes_9798[7] = {stroke_9798_0, stroke_9798_1, stroke_9798_2, stroke_9798_3, stroke_9798_4, stroke_9798_5, stroke_9798_6};
static const uint8_t ncoords_9798[7] = {3, 3, 7, 4, 7, 4, 2};
static const glyph_stroke_t stroke_9799_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_9799_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_9799_2[10] = {{0,21},{12,21},{15,20},{16,19},{17,17},{17,14},{16,12},{15,11},{12,10},{4,10}};
static const glyph_stroke_t stroke_9799_3[8] = {{12,21},{14,20},{15,19},{16,17},{16,14},{15,12},{14,11},{12,10}};
static const glyph_stroke_t stroke_9799_4[4] = {{0,0},{16,0},{16,5},{15,0}};
static const glyph_stroke_t *strokes_9799[5] = {stroke_9799_0, stroke_9799_1, stroke_9799_2, stroke_9799_3, stroke_9799_4};
static const uint8_t ncoords_9799[5] = {2, 2, 10, 8, 4};
static const glyph_stroke_t stroke_9790_0[12] = {{14,20},{10,20},{6,19},{3,17},{1,14},{0,11},{0,8},{1,5},{3,2},{6,0},{10,-1},{14,-1}};
static const glyph_stroke_t stroke_9790_1[10] = {{14,20},{11,19},{8,17},{6,14},{5,11},{5,8},{6,5},{8,2},{11,0},{14,-1}};
static const glyph_stroke_t *strokes_9790[2] = {stroke_9790_0, stroke_9790_1};
static const uint8_t ncoords_9790[2] = {12, 10};
static const glyph_stroke_t stroke_9732_0[17] = {{6,10},{4,10},{2,9},{1,8},{0,6},{0,4},{1,2},{2,1},{4,0},{6,0},{8,1},{9,2},{10,4},{10,6},{9,8},{8,9},{6,10}};
static const glyph_stroke_t stroke_9732_1[2] = {{10,19},{7,10}};
static const glyph_stroke_t stroke_9732_2[2] = {{17,17},{9,9}};
static const glyph_stroke_t stroke_9732_3[2] = {{19,10},{10,7}};
static const glyph_stroke_t *strokes_9732[4] = {stroke_9732_0, stroke_9732_1, stroke_9732_2, stroke_9732_3};
static const uint8_t ncoords_9732[4] = {17, 2, 2, 2};
static const glyph_stroke_t stroke_10035_0[2] = {{4,16},{10,2}};
static const glyph_stroke_t stroke_10035_1[2] = {{10,16},{4,2}};
static const glyph_stroke_t stroke_10035_2[2] = {{0,12},{14,6}};
static const glyph_stroke_t stroke_10035_3[2] = {{14,12},{0,6}};
static const glyph_stroke_t *strokes_10035[4] = {stroke_10035_0, stroke_10035_1, stroke_10035_2, stroke_10035_3};
static const uint8_t ncoords_10035[4] = {2, 2, 2, 2};
static const glyph_stroke_t stroke_9738_0[38] = {{6,5},{4,6},{3,6},{1,5},{0,3},{0,2},{1,0},{3,-1},{4,-1},{6,0},{7,2},{7,3},{6,5},{3,9},{2,12},{2,14},{3,17},{5,19},{8,20},{12,20},{15,19},{17,17},{18,14},{18,12},{17,9},{14,5},{13,3},{13,2},{14,0},{16,-1},{17,-1},{19,0},{20,2},{20,3},{19,5},{17,6},{16,6},{14,5}};
static const glyph_stroke_t stroke_9738_1[8] = {{2,14},{3,16},{5,18},{8,19},{12,19},{15,18},{17,16},{18,14}};
static const glyph_stroke_t *strokes_9738[2] = {stroke_9738_0, stroke_9738_1};
static const uint8_t ncoords_9738[2] = {38, 8};
static const glyph_stroke_t stroke_9739_0[38] = {{6,14},{4,13},{3,13},{1,14},{0,16},{0,17},{1,19},{3,20},{4,20},{6,19},{7,17},{7,16},{6,14},{3,10},{2,7},{2,5},{3,2},{5,0},{8,-1},{12,-1},{15,0},{17,2},{18,5},{18,7},{17,10},{14,14},{13,16},{13,17},{14,19},{16,20},{17,20},{19,19},{20,17},{20,16},{19,14},{17,13},{16,13},{14,14}};
static const glyph_stroke_t stroke_9739_1[8] = {{2,5},{3,3},{5,1},{8,0},{12,0},{15,1},{17,3},{18,5}};
static const glyph_stroke_t *strokes_9739[2] = {stroke_9739_0, stroke_9739_1};
static const uint8_t ncoords_9739[2] = {38, 8};
static const glyph_stroke_t stroke_9800_0[10] = {{1,14},{0,15},{0,17},{1,19},{3,20},{5,20},{7,19},{8,18},{9,16},{10,11}};
static const glyph_stroke_t stroke_9800_1[8] = {{0,17},{2,19},{4,19},{6,18},{7,17},{8,15},{9,11},{9,0}};
static const glyph_stroke_t stroke_9800_2[10] = {{18,14},{19,15},{19,17},{18,19},{16,20},{14,20},{12,19},{11,18},{10,16},{9,11}};
static const glyph_stroke_t stroke_9800_3[8] = {{19,17},{17,19},{15,19},{13,18},{12,17},{11,15},{10,11},{10,0}};
static const glyph_stroke_t *strokes_9800[4] = {stroke_9800_0, stroke_9800_1, stroke_9800_2, stroke_9800_3};
static const uint8_t ncoords_9800[4] = {10, 8, 10, 8};
static const glyph_stroke_t stroke_9801_0[10] = {{0,20},{1,16},{2,14},{4,12},{7,11},{11,11},{14,12},{16,14},{17,16},{18,20}};
static const glyph_stroke_t stroke_9801_1[10] = {{0,20},{1,17},{2,15},{4,13},{7,12},{11,12},{14,13},{16,15},{17,17},{18,20}};
static const glyph_stroke_t stroke_9801_2[16] = {{7,12},{5,11},{4,10},{3,8},{3,5},{4,3},{6,1},{8,0},{10,0},{12,1},{14,3},{15,5},{15,8},{14,10},{13,11},{11,12}};
static const glyph_stroke_t stroke_9801_3[5] = {{7,11},{5,10},{4,8},{4,5},{5,2}};
static const glyph_stroke_t stroke_9801_4[5] = {{13,2},{14,5},{14,8},{13,10},{11,11}};
static const glyph_stroke_t *strokes_9801[5] = {stroke_9801_0, stroke_9801_1, stroke_9801_2, stroke_9801_3, stroke_9801_4};
static const uint8_t ncoords_9801[5] = {10, 10, 16, 5, 5};
static const glyph_stroke_t stroke_9802_0[2] = {{4,17},{4,5}};
static const glyph_stroke_t stroke_9802_1[2] = {{5,16},{5,6}};
static const glyph_stroke_t stroke_9802_2[2] = {{13,16},{13,6}};
static const glyph_stroke_t stroke_9802_3[2] = {{14,17},{14,5}};
static const glyph_stroke_t stroke_9802_4[8] = {{0,20},{2,18},{4,17},{7,16},{11,16},{14,17},{16,18},{18,20}};
static const glyph_stroke_t stroke_9802_5[8] = {{0,2},{2,4},{4,5},{7,6},{11,6},{14,5},{16,4},{18,2}};
static const glyph_stroke_t *strokes_9802[6] = {stroke_9802_0, stroke_9802_1, stroke_9802_2, stroke_9802_3, stroke_9802_4, stroke_9802_5};
static const uint8_t ncoords_9802[6] = {2, 2, 2, 2, 8, 8};
static const glyph_stroke_t stroke_9803_0[13] = {{18,18},{3,18},{1,17},{0,15},{0,13},{1,11},{3,10},{5,10},{7,11},{8,13},{8,15},{7,17},{18,17}};
static const glyph_stroke_t stroke_9803_1[4] = {{0,14},{1,12},{2,11},{4,10}};
static const glyph_stroke_t stroke_9803_2[4] = {{8,14},{7,16},{6,17},{4,18}};
static const glyph_stroke_t stroke_9803_3[13] = {{0,3},{15,3},{17,4},{18,6},{18,8},{17,10},{15,11},{13,11},{11,10},{10,8},{10,6},{11,4},{0,4}};
static const glyph_stroke_t stroke_9803_4[4] = {{18,7},{17,9},{16,10},{14,11}};
static const glyph_stroke_t stroke_9803_5[4] = {{10,7},{11,5},{12,4},{14,3}};
static const glyph_stroke_t *strokes_9803[6] = {stroke_9803_0, stroke_9803_1, stroke_9803_2, stroke_9803_3, stroke_9803_4, stroke_9803_5};
static const uint8_t ncoords_9803[6] = {13, 4, 4, 13, 4, 4};
static const glyph_stroke_t stroke_9804_0[32] = {{6,6},{4,7},{3,7},{1,6},{0,4},{0,3},{1,1},{3,0},{4,0},{6,1},{7,3},{7,4},{6,6},{1,11},{0,13},{0,16},{1,18},{3,19},{6,20},{10,20},{14,19},{16,17},{17,15},{17,12},{16,9},{13,6},{12,4},{12,2},{13,0},{15,0},{16,1},{17,3}};
static const glyph_stroke_t stroke_9804_1[6] = {{4,8},{2,11},{1,13},{1,16},{2,18},{3,19}};
static const glyph_stroke_t stroke_9804_2[7] = {{10,20},{13,19},{15,17},{16,15},{16,12},{15,9},{13,6}};
static const glyph_stroke_t *strokes_9804[3] = {stroke_9804_0, stroke_9804_1, stroke_9804_2};
static const uint8_t ncoords_9804[3] = {32, 6, 7};
static const glyph_stroke_t stroke_9805_0[4] = {{0,16},{3,19},{5,16},{5,5}};
static const glyph_stroke_t stroke_9805_1[3] = {{2,18},{4,15},{4,5}};
static const glyph_stroke_t stroke_9805_2[4] = {{5,16},{8,19},{10,16},{10,6}};
static const glyph_stroke_t stroke_9805_3[3] = {{7,18},{9,15},{9,6}};
static const glyph_stroke_t stroke_9805_4[4] = {{10,16},{13,19},{15,16},{15,0}};
static const glyph_stroke_t stroke_9805_5[3] = {{12,18},{14,15},{14,0}};
static const glyph_stroke_t stroke_9805_6[10] = {{15,16},{18,19},{19,17},{20,14},{20,11},{19,8},{18,6},{16,4},{13,2},{8,0}};
static const glyph_stroke_t stroke_9805_7[9] = {{17,18},{18,17},{19,14},{19,11},{18,8},{17,6},{15,4},{12,2},{8,0}};
static const glyph_stroke_t *strokes_9805[8] = {stroke_9805_0, stroke_9805_1, stroke_9805_2, stroke_9805_3, stroke_9805_4, stroke_9805_5, stroke_9805_6, stroke_9805_7};
static const uint8_t ncoords_9805[8] = {4, 3, 4, 3, 4, 3, 10, 9};
static const glyph_stroke_t stroke_9807_0[4] = {{0,15},{3,18},{6,15},{6,3}};
static const glyph_stroke_t stroke_9807_1[3] = {{2,17},{5,14},{5,3}};
static const glyph_stroke_t stroke_9807_2[4] = {{6,15},{9,18},{12,15},{12,3}};
static const glyph_stroke_t stroke_9807_3[3] = {{8,17},{11,14},{11,3}};
static const glyph_stroke_t stroke_9807_4[5] = {{12,15},{15,18},{18,15},{18,4},{20,2}};
static const glyph_stroke_t stroke_9807_5[5] = {{14,17},{17,14},{17,3},{19,1},{22,4}};
static const glyph_stroke_t *strokes_9807[6] = {stroke_9807_0, stroke_9807_1, stroke_9807_2, stroke_9807_3, stroke_9807_4, stroke_9807_5};
static const uint8_t ncoords_9807[6] = {4, 3, 4, 3, 5, 5};
static const glyph_stroke_t stroke_9808_0[2] = {{16,18},{0,2}};
static const glyph_stroke_t stroke_9808_1[3] = {{16,18},{13,17},{7,17}};
static const glyph_stroke_t stroke_9808_2[3] = {{14,16},{11,16},{7,17}};
static const glyph_stroke_t stroke_9808_3[3] = {{16,18},{15,15},{15,9}};
static const glyph_stroke_t stroke_9808_4[3] = {{14,16},{14,13},{15,9}};
static const glyph_stroke_t stroke_9808_5[2] = {{7,9},{0,9}};
static const glyph_stroke_t stroke_9808_6[3] = {{6,8},{3,8},{0,9}};
static const glyph_stroke_t stroke_9808_7[2] = {{7,9},{7,2}};
static const glyph_stroke_t stroke_9808_8[3] = {{6,8},{6,5},{7,2}};
static const glyph_stroke_t *strokes_9808[9] = {stroke_9808_0, stroke_9808_1, stroke_9808_2, stroke_9808_3, stroke_9808_4, stroke_9808_5, stroke_9808_6, stroke_9808_7, stroke_9808_8};
static const uint8_t ncoords_9808[9] = {2, 3, 3, 3, 3, 2, 3, 2, 3};
static const glyph_stroke_t stroke_9809_0[3] = {{0,12},{2,16},{7,6}};
static const glyph_stroke_t stroke_9809_1[18] = {{2,14},{7,4},{10,11},{15,11},{18,12},{19,14},{19,16},{18,18},{16,19},{15,19},{13,18},{12,16},{12,14},{13,11},{14,9},{15,6},{15,3},{13,1}};
static const glyph_stroke_t stroke_9809_2[9] = {{15,19},{14,18},{13,16},{13,14},{15,10},{16,7},{16,4},{15,2},{13,1}};
static const glyph_stroke_t *strokes_9809[3] = {stroke_9809_0, stroke_9809_1, stroke_9809_2};
static const uint8_t ncoords_9809[3] = {3, 18, 9};
static const glyph_stroke_t stroke_9810_0[3] = {{0,12},{3,15},{7,13}};
static const glyph_stroke_t stroke_9810_1[4] = {{2,14},{6,12},{9,15},{12,13}};
static const glyph_stroke_t stroke_9810_2[4] = {{8,14},{11,12},{14,15},{16,13}};
static const glyph_stroke_t stroke_9810_3[3] = {{13,14},{15,12},{18,15}};
static const glyph_stroke_t stroke_9810_4[3] = {{0,6},{3,9},{7,7}};
static const glyph_stroke_t stroke_9810_5[4] = {{2,8},{6,6},{9,9},{12,7}};
static const glyph_stroke_t stroke_9810_6[4] = {{8,8},{11,6},{14,9},{16,7}};
static const glyph_stroke_t stroke_9810_7[3] = {{13,8},{15,6},{18,9}};
static const glyph_stroke_t *strokes_9810[8] = {stroke_9810_0, stroke_9810_1, stroke_9810_2, stroke_9810_3, stroke_9810_4, stroke_9810_5, stroke_9810_6, stroke_9810_7};
static const uint8_t ncoords_9810[8] = {3, 4, 4, 3, 3, 4, 4, 3};
static const glyph_data_t glyph_data[128] = {
	{ 0x00000020, 0, 0, 0, 0, -6, 6, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x00000021, 0, 0, 8, 21, -2, 9, 0, 6, strokes_33, ncoords_33 },
	{ 0x00000022, 0, 14, 12, 21, -5, 13, 0, 4, strokes_34, ncoords_34 },
	{ 0x00000023, 0, -7, 15, 25, -3, 18, 0, 4, strokes_35, ncoords_35 },
	{ 0x00000024, 0, -4, 17, 25, -2, 19, 0, 5, strokes_36, ncoords_36 },
	{ 0x00000025, 0, 0, 18, 21, -3, 21, 0, 3, strokes_37, ncoords_37 },
	{ 0x00000026, 0, 0, 22, 21, -2, 24, 0, 6, strokes_38, ncoords_38 },
	{ 0x00000027, 0, 14, 3, 21, -5, 4, 0, 2, strokes_39, ncoords_39 },
	{ 0x00000028, 0, -7, 13, 25, -3, 13, 0, 4, strokes_40, ncoords_40 },
	{ 0x00000029, 0, -7, 13, 25, 0, 16, 0, 4, strokes_41, ncoords_41 },
	{ 0x0000002a, 0, 9, 10, 21, -5, 12, 0, 9, strokes_42, ncoords_42 },
	{ 0x0000002b, 0, 1, 17, 18, -4, 21, 0, 4, strokes_43, ncoords_43 },
	{ 0x0000002c, 0, -4, 4, 3, -1, 10, 0, 3, strokes_44, ncoords_44 },
	{ 0x0000002d, 0, 9, 18, 9, -4, 22, 0, 1, strokes_45, ncoords_45 },
	{ 0x0000002e, 0, 0, 3, 3, -2, 9, 0, 2, strokes_46, ncoords_46 },
	{ 0x0000002f, 0, -7, 19, 25, -2, 21, 0, 2, strokes_47, ncoords_47 },
	{ 0x00000030, 0, 0, 15, 21, -3, 18, 0, 5, strokes_48, ncoords_48 },
	{ 0x00000031, 0, 0, 8, 21, -7, 14, 0, 5, strokes_49, ncoords_49 },
	{ 0x00000032, 0, 0, 17, 21, -1, 20, 0, 6, strokes_50, ncoords_50 },
	{ 0x00000033, 0, 0, 16, 21, -2, 19, 0, 6, strokes_51, ncoords_51 },
	{ 0x00000034, 0, 0, 16, 21, -2, 19, 0, 4, strokes_52, ncoords_52 },
	{ 0x00000035, 0, 0, 17, 21, -2, 19, 0, 7, strokes_53, ncoords_53 },
	{ 0x00000036, 0, 0, 15, 21, -3, 18, 0, 5, strokes_54, ncoords_54 },
	{ 0x00000037, 0, 0, 15, 21, -4, 17, 0, 7, strokes_55, ncoords_55 },
	{ 0x00000038, 0, 0, 16, 21, -2, 19, 0, 17, strokes_56, ncoords_56 },
	{ 0x00000039, 0, 0, 15, 21, -3, 18, 0, 5, strokes_57, ncoords_57 },
	{ 0x0000003a, 0, 0, 6, 14, -2, 9, 0, 4, strokes_58, ncoords_58 },
	{ 0x0000003b, 0, -4, 7, 14, -1, 10, 0, 5, strokes_59, ncoords_59 },
	{ 0x0000003c, 0, 0, 16, 18, -4, 20, 0, 1, strokes_60, ncoords_60 },
	{ 0x0000003d, 0, 5, 17, 14, -4, 21, 0, 4, strokes_61, ncoords_61 },
	{ 0x0000003e, 0, 0, 16, 18, -4, 20, 0, 1, strokes_62, ncoords_62 },
	{ 0x0000003f, 0, 0, 13, 21, -6, 15, 0, 6, strokes_63, ncoords_63 },
	{ 0x00000040, 0, 0, 21, 21, -3, 24, 0, 4, strokes_64, ncoords_64 },
	{ 0x00000041, 0, 0, 18, 21, 2, 22, 0, 12, strokes_65, ncoords_65 },
	{ 0x00000042, 0, 0, 21, 21, 0, 24, 0, 17, strokes_66, ncoords_66 },
	{ 0x00000043, 0, 0, 17, 21, -3, 18, 0, 3, strokes_67, ncoords_67 },
	{ 0x00000044, 0, 0, 20, 21, 0, 23, 0, 14, strokes_68, ncoords_68 },
	{ 0x00000045, 0, 0, 21, 21, 0, 23, 0, 25, strokes_69, ncoords_69 },
	{ 0x00000046, 0, 0, 21, 21, 0, 22, 0, 22, strokes_70, ncoords_70 },
	{ 0x00000047, 0, 0, 17, 21, -3, 19, 0, 10, strokes_71, ncoords_71 },
	{ 0x00000048, 0, 0, 26, 21, 0, 26, 0, 27, strokes_72, ncoords_72 },
	{ 0x00000049, 0, 0, 14, 21, 0, 14, 0, 13, strokes_73, ncoords_73 },
	{ 0x0000004a, 0, 0, 18, 21, -1, 18, 0, 9, strokes_74, ncoords_74 },
	{ 0x0000004b, 0, 0, 25, 21, 0, 23, 0, 24, strokes_75, ncoords_75 },
	{ 0x0000004c, 0, 0, 17, 21, 0, 20, 0, 16, strokes_76, ncoords_76 },
	{ 0x0000004d, 0, 0, 28, 21, 0, 28, 0, 22, strokes_77, ncoords_77 },
	{ 0x0000004e, 0, 0, 25, 21, 0, 25, 0, 14, strokes_78, ncoords_78 },
	{ 0x0000004f, 0, 0, 16, 21, -3, 19, 0, 5, strokes_79, ncoords_79 },
	{ 0x00000050, 0, 0, 22, 21, 0, 23, 0, 15, strokes_80, ncoords_80 },
	{ 0x00000051, 0, -5, 16, 21, -3, 19, 0, 8, strokes_81, ncoords_81 },
	{ 0x00000052, 0, 0, 21, 21, 0, 24, 0, 18, strokes_82, ncoords_82 },
	{ 0x00000053, 0, 0, 19, 21, -2, 21, 0, 3, strokes_83, ncoords_83 },
	{ 0x00000054, 0, 0, 18, 21, -4, 18, 0, 18, strokes_84, ncoords_84 },
	{ 0x00000055, 0, 0, 21, 21, -4, 21, 0, 11, strokes_85, ncoords_85 },
	{ 0x00000056, 0, 0, 18, 21, -4, 16, 0, 11, strokes_86, ncoords_86 },
	{ 0x00000057, 0, 0, 22, 21, -5, 21, 0, 17, strokes_87, ncoords_87 },
	{ 0x00000058, 0, 0, 24, 21, 1, 23, 0, 18, strokes_88, ncoords_88 },
	{ 0x00000059, 0, 0, 20, 21, -4, 18, 0, 16, strokes_89, ncoords_89 },
	{ 0x0000005a, 0, 0, 20, 21, -1, 21, 0, 11, strokes_90, ncoords_90 },
	{ 0x0000005b, 0, -7, 7, 25, -4, 10, 0, 4, strokes_91, ncoords_91 },
	{ 0x0000005c, 0, -3, 14, 21, 0, 14, 0, 1, strokes_92, ncoords_92 },
	{ 0x0000005d, 0, -7, 7, 25, -3, 11, 0, 4, strokes_93, ncoords_93 },
	{ 0x0000005e, 0, 7, 16, 12, -3, 19, 0, 2, strokes_94, ncoords_94 },
	{ 0x0000005f, 0, -7, 20, -7, 0, 20, 0, 1, strokes_95, ncoords_95 },
	{ 0x00000060, 0, 15, 6, 21, -3, 9, 0, 2, strokes_96, ncoords_96 },
	{ 0x00000061, 0, 0, 18, 14, -3, 19, 0, 6, strokes_97, ncoords_97 },
	{ 0x00000062, 0, 0, 12, 21, -4, 15, 0, 7, strokes_98, ncoords_98 },
	{ 0x00000063, 0, 0, 12, 14, -3, 15, 0, 3, strokes_99, ncoords_99 },
	{ 0x00000064, 0, 0, 18, 21, -3, 19, 0, 8, strokes_100, ncoords_100 },
	{ 0x00000065, 0, 0, 12, 14, -3, 15, 0, 3, strokes_101, ncoords_101 },
	{ 0x00000066, 0, -7, 19, 21, 2, 18, 0, 4, strokes_102, ncoords_102 },
	{ 0x00000067, 0, -7, 17, 14, -1, 20, 0, 6, strokes_103, ncoords_103 },
	{ 0x00000068, 0, 0, 19, 21, -2, 20, 0, 8, strokes_104, ncoords_104 },
	{ 0x00000069, 0, 0, 11, 21, -1, 12, 0, 6, strokes_105, ncoords_105 },
	{ 0x0000006a, 0, -7, 14, 21, 2, 15, 0, 6, strokes_106, ncoords_106 },
	{ 0x0000006b, 0, 0, 17, 21, -2, 20, 0, 9, strokes_107, ncoords_107 },
	{ 0x0000006c, 0, 0, 7, 21, -4, 8, 0, 5, strokes_108, ncoords_108 },
	{ 0x0000006d, 0, 0, 33, 14, -1, 34, 0, 9, strokes_109, ncoords_109 },
	{ 0x0000006e, 0, 0, 22, 14, -1, 23, 0, 6, strokes_110, ncoords_110 },
	{ 0x0000006f, 0, 0, 14, 14, -3, 17, 0, 5, strokes_111, ncoords_111 },
	{ 0x00000070, 0, -7, 20, 14, 1, 23, 0, 11, strokes_112, ncoords_112 },
	{ 0x00000071, 0, -7, 15, 14, -3, 18, 0, 11, strokes_113, ncoords_113 },
	{ 0x00000072, 0, 0, 16, 14, -1, 17, 0, 4, strokes_114, ncoords_114 },
	{ 0x00000073, 0, 0, 13, 14, -2, 15, 0, 5, strokes_115, ncoords_115 },
	{ 0x00000074, 0, 0, 10, 21, -3, 11, 0, 4, strokes_116, ncoords_116 },
	{ 0x00000075, 0, 0, 22, 14, -1, 23, 0, 6, strokes_117, ncoords_117 },
	{ 0x00000076, 0, 0, 16, 14, -1, 19, 0, 3, strokes_118, ncoords_118 },
	{ 0x00000077, 0, 0, 26, 14, -1, 29, 0, 6, strokes_119, ncoords_119 },
	{ 0x00000078, 0, 0, 19, 14, -1, 21, 0, 5, strokes_120, ncoords_120 },
	{ 0x00000079, 0, -7, 19, 14, -1, 21, 0, 6, strokes_121, ncoords_121 },
	{ 0x0000007a, 0, 0, 14, 14, -3, 17, 0, 7, strokes_122, ncoords_122 },
	{ 0x0000007b, 0, -7, 5, 25, -4, 10, 0, 3, strokes_123, ncoords_123 },
	{ 0x0000007c, 0, -7, 0, 25, -4, 4, 0, 1, strokes_124, ncoords_124 },
	{ 0x0000007d, 0, -7, 5, 25, -5, 9, 0, 3, strokes_125, ncoords_125 },
	{ 0x0000007e, 0, 6, 18, 12, -3, 21, 0, 2, strokes_126, ncoords_126 },
	{ 0x0000007f, 0, 0, 16, 21, 0, 16, 0, 1, strokes_127, ncoords_127 },
	{ 0x00002604, 0, 0, 19, 19, -3, 22, 0, 4, strokes_9732, ncoords_9732 },
	{ 0x00002609, 0, 0, 21, 21, -3, 24, 0, 3, strokes_9737, ncoords_9737 },
	{ 0x0000260a, 0, -1, 20, 20, -2, 22, 0, 2, strokes_9738, ncoords_9738 },
	{ 0x0000260b, 0, -1, 20, 20, -2, 22, 0, 2, strokes_9739, ncoords_9739 },
	{ 0x0000263e, 0, -1, 14, 20, -3, 16, 0, 2, strokes_9790, ncoords_9790 },
	{ 0x0000263f, 0, 0, 11, 21, -3, 14, 0, 8, strokes_9791, ncoords_9791 },
	{ 0x00002640, 0, 0, 13, 21, -3, 16, 0, 4, strokes_9792, ncoords_9792 },
	{ 0x00002642, 0, 1, 19, 20, -3, 22, 0, 4, strokes_9794, ncoords_9794 },
	{ 0x00002643, 0, 0, 16, 21, -3, 19, 0, 5, strokes_9795, ncoords_9795 },
	{ 0x00002644, 0, 0, 14, 21, -2, 17, 0, 5, strokes_9796, ncoords_9796 },
	{ 0x00002646, 0, 0, 17, 21, -3, 20, 0, 7, strokes_9798, ncoords_9798 },
	{ 0x00002647, 0, 0, 17, 21, -2, 20, 0, 5, strokes_9799, ncoords_9799 },
	{ 0x00002648, 0, 0, 19, 20, -3, 22, 0, 4, strokes_9800, ncoords_9800 },
	{ 0x00002649, 0, 0, 18, 20, -3, 21, 0, 5, strokes_9801, ncoords_9801 },
	{ 0x0000264a, 0, 2, 18, 20, -3, 21, 0, 6, strokes_9802, ncoords_9802 },
	{ 0x0000264b, 0, 3, 18, 18, -3, 21, 0, 6, strokes_9803, ncoords_9803 },
	{ 0x0000264c, 0, 0, 17, 20, -3, 20, 0, 3, strokes_9804, ncoords_9804 },
	{ 0x0000264d, 0, 0, 20, 19, -1, 23, 0, 8, strokes_9805, ncoords_9805 },
	{ 0x0000264f, 0, 1, 22, 18, -1, 24, 0, 6, strokes_9807, ncoords_9807 },
	{ 0x00002650, 0, 2, 16, 18, -3, 19, 0, 9, strokes_9808, ncoords_9808 },
	{ 0x00002651, 0, 1, 19, 19, -2, 22, 0, 3, strokes_9809, ncoords_9809 },
	{ 0x00002652, 0, 6, 18, 15, -3, 21, 0, 8, strokes_9810, ncoords_9810 },
	{ 0x00002653, 0, 2, 18, 19, -3, 21, 0, 8, strokes_9811, ncoords_9811 },
	{ 0x000026a8, 0, 0, 13, 21, -3, 16, 0, 5, strokes_9896, ncoords_9896 },
	{ 0x00002733, 0, 2, 14, 16, -3, 17, 0, 4, strokes_10035, ncoords_10035 },
	{ 0x00002a01, 0, -1, 22, 21, -3, 25, 0, 3, strokes_10753, ncoords_10753 },
	{ 0x0000e000, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e001, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e002, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e003, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e004, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e005, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 }
};
const font_data_t font_htimes_italic_bold = {
	"Hershey Times italic bold",
	21,
	128,
	glyph_data
};
