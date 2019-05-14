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
static const glyph_stroke_t stroke_35_0[2] = {{8,21},{1,-7}};
static const glyph_stroke_t stroke_35_1[2] = {{14,21},{7,-7}};
static const glyph_stroke_t stroke_35_2[2] = {{1,10},{15,10}};
static const glyph_stroke_t stroke_35_3[2] = {{0,4},{14,4}};
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
static const glyph_stroke_t stroke_65_0[14] = {{20,21},{18,19},{16,16},{13,11},{11,8},{8,4},{5,1},{3,0},{1,0},{0,1},{0,3},{1,4},{2,3},{1,2}};
static const glyph_stroke_t stroke_65_1[4] = {{20,21},{19,17},{17,7},{16,0}};
static const glyph_stroke_t stroke_65_2[2] = {{20,21},{17,0}};
static const glyph_stroke_t stroke_65_3[14] = {{16,0},{16,2},{15,5},{14,7},{12,9},{10,10},{8,10},{7,9},{7,7},{8,4},{11,1},{14,0},{18,0},{20,1}};
static const glyph_stroke_t *strokes_65[4] = {stroke_65_0, stroke_65_1, stroke_65_2, stroke_65_3};
static const uint8_t ncoords_65[4] = {14, 4, 2, 14};
static const glyph_stroke_t stroke_66_0[8] = {{14,20},{13,19},{12,17},{10,12},{8,6},{7,4},{5,1},{3,0}};
static const glyph_stroke_t stroke_66_1[13] = {{13,19},{12,16},{10,8},{9,5},{8,3},{6,1},{3,0},{1,0},{0,1},{0,3},{1,4},{2,3},{1,2}};
static const glyph_stroke_t stroke_66_2[18] = {{8,15},{7,13},{6,12},{4,12},{3,13},{3,15},{4,17},{6,19},{8,20},{11,21},{17,21},{19,20},{20,18},{20,16},{19,14},{17,13},{13,12},{11,12}};
static const glyph_stroke_t stroke_66_3[6] = {{17,21},{18,20},{19,18},{19,16},{18,14},{17,13}};
static const glyph_stroke_t stroke_66_4[12] = {{13,12},{16,11},{17,10},{18,8},{18,5},{17,2},{16,1},{14,0},{12,0},{11,1},{11,3},{12,6}};
static const glyph_stroke_t stroke_66_5[7] = {{13,12},{15,11},{16,10},{17,8},{17,5},{16,2},{14,0}};
static const glyph_stroke_t *strokes_66[6] = {stroke_66_0, stroke_66_1, stroke_66_2, stroke_66_3, stroke_66_4, stroke_66_5};
static const uint8_t ncoords_66[6] = {8, 13, 18, 6, 12, 7};
static const glyph_stroke_t stroke_67_0[30] = {{1,19},{0,17},{0,15},{1,13},{4,12},{7,12},{11,13},{13,14},{15,16},{16,18},{16,20},{15,21},{13,21},{10,20},{7,17},{5,14},{3,10},{2,6},{2,3},{3,1},{6,0},{8,0},{11,1},{13,3},{14,5},{14,7},{13,9},{11,9},{9,8},{8,6}};
static const glyph_stroke_t stroke_67_1[9] = {{13,21},{11,20},{8,17},{6,14},{4,10},{3,6},{3,3},{4,1},{6,0}};
static const glyph_stroke_t *strokes_67[2] = {stroke_67_0, stroke_67_1};
static const uint8_t ncoords_67[2] = {30, 9};
static const glyph_stroke_t stroke_68_0[8] = {{14,20},{13,19},{12,17},{10,12},{8,6},{7,4},{5,1},{3,0}};
static const glyph_stroke_t stroke_68_1[33] = {{13,19},{12,16},{10,8},{9,5},{8,3},{6,1},{3,0},{1,0},{0,1},{0,3},{1,4},{3,4},{5,3},{7,1},{9,0},{12,0},{14,1},{16,3},{18,7},{19,12},{19,15},{18,18},{16,20},{14,21},{9,21},{6,20},{4,18},{3,16},{3,14},{4,13},{6,13},{7,14},{8,16}};
static const glyph_stroke_t *strokes_68[2] = {stroke_68_0, stroke_68_1};
static const uint8_t ncoords_68[2] = {8, 33};
static const glyph_stroke_t stroke_69_0[16] = {{12,18},{11,17},{11,15},{12,14},{14,14},{15,16},{15,18},{14,20},{12,21},{9,21},{7,20},{6,19},{5,17},{5,15},{6,13},{8,12}};
static const glyph_stroke_t stroke_69_1[5] = {{9,21},{7,19},{6,17},{6,14},{8,12}};
static const glyph_stroke_t stroke_69_2[18] = {{8,12},{6,12},{3,11},{1,9},{0,7},{0,4},{1,2},{2,1},{4,0},{7,0},{10,1},{12,3},{13,5},{13,7},{12,9},{10,9},{8,8},{7,6}};
static const glyph_stroke_t stroke_69_3[6] = {{6,12},{4,11},{2,9},{1,7},{1,3},{2,1}};
static const glyph_stroke_t *strokes_69[4] = {stroke_69_0, stroke_69_1, stroke_69_2, stroke_69_3};
static const uint8_t ncoords_69[4] = {16, 5, 18, 6};
static const glyph_stroke_t stroke_70_0[7] = {{15,19},{14,17},{12,12},{10,6},{9,4},{7,1},{5,0}};
static const glyph_stroke_t stroke_70_1[25] = {{9,15},{8,13},{6,12},{4,12},{3,14},{3,16},{4,18},{6,20},{9,21},{19,21},{16,20},{15,19},{14,16},{12,8},{11,5},{10,3},{8,1},{5,0},{3,0},{1,1},{0,2},{0,3},{1,4},{2,3},{1,2}};
static const glyph_stroke_t stroke_70_2[3] = {{11,21},{15,20},{16,20}};
static const glyph_stroke_t stroke_70_3[7] = {{7,8},{8,9},{10,10},{14,10},{16,11},{18,14},{16,7}};
static const glyph_stroke_t *strokes_70[4] = {stroke_70_0, stroke_70_1, stroke_70_2, stroke_70_3};
static const uint8_t ncoords_70[4] = {7, 25, 3, 7};
static const glyph_stroke_t stroke_71_0[24] = {{1,18},{0,16},{0,14},{1,12},{3,11},{6,11},{9,12},{11,13},{14,16},{15,19},{15,20},{14,21},{13,21},{11,20},{9,18},{8,16},{7,13},{7,10},{8,8},{10,7},{12,7},{14,8},{16,10},{17,12}};
static const glyph_stroke_t stroke_71_1[7] = {{14,21},{12,20},{10,18},{9,16},{8,13},{8,9},{10,7}};
static const glyph_stroke_t stroke_71_2[13] = {{17,12},{16,8},{14,4},{12,2},{10,1},{6,0},{3,0},{1,1},{0,3},{0,4},{1,5},{2,4},{1,3}};
static const glyph_stroke_t stroke_71_3[5] = {{16,8},{14,5},{12,3},{9,1},{6,0}};
static const glyph_stroke_t *strokes_71[4] = {stroke_71_0, stroke_71_1, stroke_71_2, stroke_71_3};
static const uint8_t ncoords_71[4] = {24, 7, 13, 5};
static const glyph_stroke_t stroke_72_0[17] = {{6,15},{5,16},{5,18},{6,20},{9,21},{12,21},{9,10},{7,4},{6,2},{5,1},{3,0},{1,0},{0,1},{0,3},{1,4},{2,3},{1,2}};
static const glyph_stroke_t stroke_72_1[6] = {{12,21},{9,12},{8,9},{6,4},{5,2},{3,0}};
static const glyph_stroke_t stroke_72_2[21] = {{4,7},{5,8},{7,9},{16,12},{18,13},{21,15},{23,17},{24,19},{24,20},{23,21},{22,21},{20,20},{18,17},{17,15},{15,9},{14,5},{14,2},{16,0},{17,0},{19,1},{21,3}};
static const glyph_stroke_t stroke_72_3[7] = {{22,21},{20,19},{18,15},{16,9},{15,5},{15,2},{16,0}};
static const glyph_stroke_t *strokes_72[4] = {stroke_72_0, stroke_72_1, stroke_72_2, stroke_72_3};
static const uint8_t ncoords_72[4] = {17, 6, 21, 7};
static const glyph_stroke_t stroke_73_0[7] = {{14,19},{12,16},{10,11},{8,6},{7,4},{5,1},{3,0}};
static const glyph_stroke_t stroke_73_1[24] = {{16,15},{14,13},{11,12},{8,12},{6,13},{5,15},{5,17},{6,19},{8,20},{12,21},{16,21},{14,19},{13,17},{11,11},{9,5},{8,3},{6,1},{3,0},{1,0},{0,1},{0,3},{1,4},{2,3},{1,2}};
static const glyph_stroke_t *strokes_73[2] = {stroke_73_0, stroke_73_1};
static const uint8_t ncoords_73[2] = {7, 24};
static const glyph_stroke_t stroke_74_0[6] = {{15,21},{13,19},{11,16},{9,11},{6,2},{4,-2}};
static const glyph_stroke_t stroke_74_1[26] = {{15,14},{13,12},{10,11},{7,11},{5,12},{4,14},{4,16},{5,18},{7,20},{11,21},{15,21},{13,18},{12,16},{9,7},{7,3},{6,1},{4,-2},{3,-3},{1,-4},{0,-3},{0,-1},{1,1},{3,3},{5,4},{8,5},{12,6}};
static const glyph_stroke_t *strokes_74[2] = {stroke_74_0, stroke_74_1};
static const uint8_t ncoords_74[2] = {6, 26};
static const glyph_stroke_t stroke_75_0[17] = {{6,15},{5,16},{5,18},{7,20},{10,21},{12,21},{9,10},{7,4},{6,2},{5,1},{3,0},{1,0},{0,1},{0,3},{1,4},{2,3},{1,2}};
static const glyph_stroke_t stroke_75_1[6] = {{12,21},{9,12},{8,9},{6,4},{5,2},{3,0}};
static const glyph_stroke_t stroke_75_2[5] = {{20,20},{17,16},{15,14},{13,13},{10,12}};
static const glyph_stroke_t stroke_75_3[12] = {{23,20},{22,19},{23,18},{24,19},{24,20},{23,21},{22,21},{20,20},{17,15},{16,14},{14,13},{10,12}};
static const glyph_stroke_t stroke_75_4[5] = {{10,12},{13,11},{14,9},{15,2},{16,0}};
static const glyph_stroke_t stroke_75_5[8] = {{10,12},{12,11},{13,9},{14,2},{16,0},{17,0},{19,1},{21,3}};
static const glyph_stroke_t *strokes_75[6] = {stroke_75_0, stroke_75_1, stroke_75_2, stroke_75_3, stroke_75_4, stroke_75_5};
static const uint8_t ncoords_75[6] = {17, 6, 5, 12, 5, 8};
static const glyph_stroke_t stroke_76_0[20] = {{5,18},{4,16},{4,14},{5,12},{7,11},{10,11},{13,12},{15,13},{18,16},{19,19},{19,20},{18,21},{17,21},{15,20},{14,19},{12,16},{8,6},{7,4},{5,1},{3,0}};
static const glyph_stroke_t stroke_76_1[18] = {{14,19},{12,15},{10,8},{9,5},{8,3},{6,1},{3,0},{1,0},{0,1},{0,3},{1,4},{3,4},{5,3},{8,1},{10,0},{13,0},{15,1},{17,3}};
static const glyph_stroke_t *strokes_76[2] = {stroke_76_0, stroke_76_1};
static const uint8_t ncoords_76[2] = {20, 18};
static const glyph_stroke_t stroke_77_0[12] = {{16,21},{12,12},{9,6},{7,3},{5,1},{3,0},{1,0},{0,1},{0,3},{1,4},{2,3},{1,2}};
static const glyph_stroke_t stroke_77_1[6] = {{16,21},{14,14},{13,10},{12,5},{12,1},{14,0}};
static const glyph_stroke_t stroke_77_2[6] = {{16,21},{15,17},{14,12},{13,5},{13,1},{14,0}};
static const glyph_stroke_t stroke_77_3[4] = {{25,21},{21,12},{16,3},{14,0}};
static const glyph_stroke_t stroke_77_4[9] = {{25,21},{23,14},{22,10},{21,5},{21,1},{23,0},{24,0},{26,1},{28,3}};
static const glyph_stroke_t stroke_77_5[6] = {{25,21},{24,17},{23,12},{22,5},{22,1},{23,0}};
static const glyph_stroke_t *strokes_77[6] = {stroke_77_0, stroke_77_1, stroke_77_2, stroke_77_3, stroke_77_4, stroke_77_5};
static const uint8_t ncoords_77[6] = {12, 6, 6, 4, 9, 6};
static const glyph_stroke_t stroke_78_0[13] = {{13,21},{12,17},{10,11},{8,6},{7,4},{5,1},{3,0},{1,0},{0,1},{0,3},{1,4},{2,3},{1,2}};
static const glyph_stroke_t stroke_78_1[4] = {{13,21},{13,16},{14,5},{15,0}};
static const glyph_stroke_t stroke_78_2[4] = {{13,21},{14,16},{15,5},{15,0}};
static const glyph_stroke_t stroke_78_3[13] = {{27,20},{26,19},{27,18},{28,19},{28,20},{27,21},{25,21},{23,20},{21,17},{20,15},{18,10},{16,4},{15,0}};
static const glyph_stroke_t *strokes_78[4] = {stroke_78_0, stroke_78_1, stroke_78_2, stroke_78_3};
static const uint8_t ncoords_78[4] = {13, 4, 4, 13};
static const glyph_stroke_t stroke_79_0[25] = {{8,21},{6,20},{4,18},{2,15},{1,13},{0,9},{0,5},{1,2},{2,1},{4,0},{6,0},{9,1},{11,3},{13,6},{14,8},{15,12},{15,16},{14,19},{13,20},{12,20},{10,19},{8,17},{6,13},{5,8},{5,5}};
static const glyph_stroke_t stroke_79_1[7] = {{6,20},{4,17},{2,13},{1,9},{1,5},{2,2},{4,0}};
static const glyph_stroke_t *strokes_79[2] = {stroke_79_0, stroke_79_1};
static const uint8_t ncoords_79[2] = {25, 7};
static const glyph_stroke_t stroke_80_0[8] = {{14,20},{13,19},{12,17},{10,12},{8,6},{7,4},{5,1},{3,0}};
static const glyph_stroke_t stroke_80_1[13] = {{13,19},{12,16},{10,8},{9,5},{8,3},{6,1},{3,0},{1,0},{0,1},{0,3},{1,4},{2,3},{1,2}};
static const glyph_stroke_t stroke_80_2[20] = {{8,15},{7,13},{6,12},{4,12},{3,13},{3,15},{4,17},{6,19},{8,20},{11,21},{15,21},{18,20},{19,19},{20,17},{20,14},{19,12},{18,11},{15,10},{13,10},{11,11}};
static const glyph_stroke_t stroke_80_3[8] = {{15,21},{17,20},{18,19},{19,17},{19,14},{18,12},{17,11},{15,10}};
static const glyph_stroke_t *strokes_80[4] = {stroke_80_0, stroke_80_1, stroke_80_2, stroke_80_3};
static const uint8_t ncoords_80[4] = {8, 13, 20, 8};
static const glyph_stroke_t stroke_81_0[32] = {{13,17},{13,15},{12,13},{11,12},{9,11},{7,11},{6,13},{6,15},{7,18},{9,20},{12,21},{15,21},{17,20},{18,18},{18,14},{17,11},{15,8},{11,4},{8,2},{6,1},{3,0},{1,0},{0,1},{0,3},{1,4},{3,4},{5,3},{8,1},{11,0},{14,0},{16,1},{18,3}};
static const glyph_stroke_t stroke_81_1[9] = {{15,21},{16,20},{17,18},{17,14},{16,11},{14,8},{11,5},{7,2},{3,0}};
static const glyph_stroke_t *strokes_81[2] = {stroke_81_0, stroke_81_1};
static const uint8_t ncoords_81[2] = {32, 9};
static const glyph_stroke_t stroke_82_0[8] = {{14,20},{13,19},{12,17},{10,12},{8,6},{7,4},{5,1},{3,0}};
static const glyph_stroke_t stroke_82_1[13] = {{13,19},{12,16},{10,8},{9,5},{8,3},{6,1},{3,0},{1,0},{0,1},{0,3},{1,4},{2,3},{1,2}};
static const glyph_stroke_t stroke_82_2[18] = {{8,15},{7,13},{6,12},{4,12},{3,13},{3,15},{4,17},{6,19},{8,20},{11,21},{16,21},{19,20},{20,18},{20,16},{19,14},{18,13},{15,12},{11,12}};
static const glyph_stroke_t stroke_82_3[7] = {{16,21},{18,20},{19,18},{19,16},{18,14},{17,13},{15,12}};
static const glyph_stroke_t stroke_82_4[5] = {{11,12},{14,11},{15,9},{16,2},{17,0}};
static const glyph_stroke_t stroke_82_5[8] = {{11,12},{13,11},{14,9},{15,2},{17,0},{18,0},{20,1},{22,3}};
static const glyph_stroke_t *strokes_82[6] = {stroke_82_0, stroke_82_1, stroke_82_2, stroke_82_3, stroke_82_4, stroke_82_5};
static const uint8_t ncoords_82[6] = {8, 13, 18, 7, 5, 8};
static const glyph_stroke_t stroke_83_0[21] = {{6,18},{5,16},{5,14},{6,12},{8,11},{11,11},{14,12},{16,13},{19,16},{20,19},{20,20},{19,21},{18,21},{16,20},{15,19},{14,17},{13,14},{11,7},{10,4},{8,1},{6,0}};
static const glyph_stroke_t stroke_83_1[13] = {{14,17},{13,13},{12,6},{11,3},{9,1},{6,0},{3,0},{1,1},{0,3},{0,4},{1,5},{2,4},{1,3}};
static const glyph_stroke_t *strokes_83[2] = {stroke_83_0, stroke_83_1};
static const uint8_t ncoords_83[2] = {21, 13};
static const glyph_stroke_t stroke_84_0[7] = {{15,19},{14,17},{12,12},{10,6},{9,4},{7,1},{5,0}};
static const glyph_stroke_t stroke_84_1[25] = {{9,15},{8,13},{6,12},{4,12},{3,14},{3,16},{4,18},{6,20},{9,21},{18,21},{16,20},{15,19},{14,16},{12,8},{11,5},{10,3},{8,1},{5,0},{3,0},{1,1},{0,2},{0,3},{1,4},{2,3},{1,2}};
static const glyph_stroke_t stroke_84_2[3] = {{11,21},{15,20},{16,20}};
static const glyph_stroke_t *strokes_84[3] = {stroke_84_0, stroke_84_1, stroke_84_2};
static const uint8_t ncoords_84[3] = {7, 25, 3};
static const glyph_stroke_t stroke_85_0[10] = {{0,17},{2,20},{4,21},{5,21},{7,19},{7,16},{6,13},{3,5},{3,2},{4,0}};
static const glyph_stroke_t stroke_85_1[12] = {{5,21},{6,19},{6,16},{3,8},{2,5},{2,2},{4,0},{6,0},{8,1},{11,4},{13,7},{14,9}};
static const glyph_stroke_t stroke_85_2[8] = {{18,21},{14,9},{13,5},{13,2},{15,0},{16,0},{18,1},{20,3}};
static const glyph_stroke_t stroke_85_3[5] = {{19,21},{15,9},{14,5},{14,2},{15,0}};
static const glyph_stroke_t *strokes_85[4] = {stroke_85_0, stroke_85_1, stroke_85_2, stroke_85_3};
static const uint8_t ncoords_85[4] = {10, 12, 8, 5};
static const glyph_stroke_t stroke_86_0[10] = {{0,17},{2,20},{4,21},{5,21},{7,19},{7,16},{6,12},{4,5},{4,2},{5,0}};
static const glyph_stroke_t stroke_86_1[24] = {{5,21},{6,19},{6,16},{4,9},{3,5},{3,2},{5,0},{6,0},{9,1},{12,4},{14,7},{16,11},{17,14},{18,18},{18,20},{17,21},{16,21},{15,20},{14,18},{14,15},{15,13},{17,11},{19,10},{21,10}};
static const glyph_stroke_t *strokes_86[2] = {stroke_86_0, stroke_86_1};
static const uint8_t ncoords_86[2] = {10, 24};
static const glyph_stroke_t stroke_87_0[11] = {{2,15},{1,15},{0,16},{0,18},{1,20},{3,21},{7,21},{6,19},{5,15},{4,6},{3,0}};
static const glyph_stroke_t stroke_87_1[3] = {{5,15},{5,6},{4,0}};
static const glyph_stroke_t stroke_87_2[6] = {{15,21},{13,19},{11,15},{8,6},{6,2},{4,0}};
static const glyph_stroke_t stroke_87_3[5] = {{15,21},{14,19},{13,15},{12,6},{11,0}};
static const glyph_stroke_t stroke_87_4[3] = {{13,15},{13,6},{12,0}};
static const glyph_stroke_t stroke_87_5[7] = {{25,21},{23,20},{21,18},{19,15},{16,6},{14,2},{12,0}};
static const glyph_stroke_t *strokes_87[6] = {stroke_87_0, stroke_87_1, stroke_87_2, stroke_87_3, stroke_87_4, stroke_87_5};
static const uint8_t ncoords_87[6] = {11, 3, 6, 5, 3, 7};
static const glyph_stroke_t stroke_88_0[22] = {{9,16},{8,15},{6,15},{5,16},{5,18},{6,20},{8,21},{10,21},{12,20},{13,18},{13,15},{12,11},{10,6},{8,3},{6,1},{3,0},{1,0},{0,1},{0,3},{1,4},{2,3},{1,2}};
static const glyph_stroke_t stroke_88_1[9] = {{10,21},{11,20},{12,18},{12,15},{11,11},{9,6},{7,3},{5,1},{3,0}};
static const glyph_stroke_t stroke_88_2[18] = {{22,20},{21,19},{22,18},{23,19},{23,20},{22,21},{20,21},{18,20},{16,18},{14,15},{12,11},{11,6},{11,3},{12,1},{13,0},{14,0},{16,1},{18,3}};
static const glyph_stroke_t *strokes_88[3] = {stroke_88_0, stroke_88_1, stroke_88_2};
static const uint8_t ncoords_88[3] = {22, 9, 18};
static const glyph_stroke_t stroke_89_0[9] = {{1,17},{3,20},{5,21},{6,21},{8,20},{8,18},{6,12},{6,9},{7,7}};
static const glyph_stroke_t stroke_89_1[11] = {{6,21},{7,20},{7,18},{5,12},{5,9},{7,7},{9,7},{12,8},{14,10},{16,13},{17,15}};
static const glyph_stroke_t stroke_89_2[4] = {{19,21},{17,15},{14,7},{12,3}};
static const glyph_stroke_t stroke_89_3[14] = {{20,21},{18,15},{16,10},{14,6},{12,3},{10,1},{7,0},{3,0},{1,1},{0,3},{0,4},{1,5},{2,4},{1,3}};
static const glyph_stroke_t *strokes_89[4] = {stroke_89_0, stroke_89_1, stroke_89_2, stroke_89_3};
static const uint8_t ncoords_89[4] = {9, 11, 4, 14};
static const glyph_stroke_t stroke_90_0[9] = {{19,19},{18,17},{16,12},{15,9},{14,7},{12,4},{10,2},{8,1},{5,0}};
static const glyph_stroke_t stroke_90_1[29] = {{12,15},{11,13},{9,12},{7,12},{6,14},{6,16},{7,18},{9,20},{12,21},{22,21},{20,20},{19,19},{18,16},{17,12},{15,6},{13,3},{10,1},{5,0},{1,0},{0,1},{0,3},{1,4},{3,4},{5,3},{8,1},{10,0},{13,0},{16,1},{18,3}};
static const glyph_stroke_t stroke_90_2[3] = {{15,21},{19,20},{20,20}};
static const glyph_stroke_t *strokes_90[3] = {stroke_90_0, stroke_90_1, stroke_90_2};
static const uint8_t ncoords_90[3] = {9, 29, 3};
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
static const glyph_stroke_t stroke_97_0[13] = {{9,6},{8,8},{6,9},{4,9},{2,8},{1,7},{0,5},{0,3},{1,1},{3,0},{5,0},{7,1},{8,3}};
static const glyph_stroke_t stroke_97_1[5] = {{4,9},{2,7},{1,5},{1,2},{3,0}};
static const glyph_stroke_t stroke_97_2[7] = {{10,9},{8,3},{8,1},{10,0},{12,1},{13,2},{15,5}};
static const glyph_stroke_t stroke_97_3[4] = {{11,9},{9,3},{9,1},{10,0}};
static const glyph_stroke_t *strokes_97[4] = {stroke_97_0, stroke_97_1, stroke_97_2, stroke_97_3};
static const uint8_t ncoords_97[4] = {13, 5, 7, 4};
static const glyph_stroke_t stroke_98_0[3] = {{0,5},{2,8},{4,12}};
static const glyph_stroke_t stroke_98_1[13] = {{7,21},{1,3},{1,1},{3,0},{4,0},{6,1},{8,3},{9,6},{9,9},{10,5},{11,4},{12,4},{14,5}};
static const glyph_stroke_t stroke_98_2[4] = {{8,21},{2,3},{2,1},{3,0}};
static const glyph_stroke_t *strokes_98[3] = {stroke_98_0, stroke_98_1, stroke_98_2};
static const uint8_t ncoords_98[3] = {3, 13, 4};
static const glyph_stroke_t stroke_99_0[15] = {{7,8},{6,7},{7,7},{7,8},{6,9},{4,9},{2,8},{1,7},{0,5},{0,3},{1,1},{3,0},{6,0},{9,2},{11,5}};
static const glyph_stroke_t stroke_99_1[5] = {{4,9},{2,7},{1,5},{1,2},{3,0}};
static const glyph_stroke_t *strokes_99[2] = {stroke_99_0, stroke_99_1};
static const uint8_t ncoords_99[2] = {15, 5};
static const glyph_stroke_t stroke_100_0[13] = {{9,6},{8,8},{6,9},{4,9},{2,8},{1,7},{0,5},{0,3},{1,1},{3,0},{5,0},{7,1},{8,3}};
static const glyph_stroke_t stroke_100_1[5] = {{4,9},{2,7},{1,5},{1,2},{3,0}};
static const glyph_stroke_t stroke_100_2[7] = {{14,21},{8,3},{8,1},{10,0},{12,1},{13,2},{15,5}};
static const glyph_stroke_t stroke_100_3[4] = {{15,21},{9,3},{9,1},{10,0}};
static const glyph_stroke_t *strokes_100[4] = {stroke_100_0, stroke_100_1, stroke_100_2, stroke_100_3};
static const uint8_t ncoords_100[4] = {13, 5, 7, 4};
static const glyph_stroke_t stroke_101_0[16] = {{2,2},{4,3},{5,4},{6,6},{6,8},{5,9},{4,9},{2,8},{1,7},{0,5},{0,3},{1,1},{3,0},{6,0},{9,2},{11,5}};
static const glyph_stroke_t stroke_101_1[5] = {{4,9},{2,7},{1,5},{1,2},{3,0}};
static const glyph_stroke_t *strokes_101[2] = {stroke_101_0, stroke_101_1};
static const uint8_t ncoords_101[2] = {16, 5};
static const glyph_stroke_t stroke_102_0[19] = {{7,9},{10,12},{12,15},{13,18},{13,20},{12,21},{10,20},{9,18},{0,-9},{0,-11},{1,-12},{3,-11},{4,-8},{5,1},{6,0},{8,0},{10,1},{11,2},{13,5}};
static const glyph_stroke_t stroke_102_1[6] = {{9,18},{8,13},{7,9},{4,0},{2,-5},{0,-9}};
static const glyph_stroke_t *strokes_102[2] = {stroke_102_0, stroke_102_1};
static const uint8_t ncoords_102[2] = {19, 6};
static const glyph_stroke_t stroke_103_0[13] = {{9,6},{8,8},{6,9},{4,9},{2,8},{1,7},{0,5},{0,3},{1,1},{3,0},{5,0},{7,1},{8,3}};
static const glyph_stroke_t stroke_103_1[5] = {{4,9},{2,7},{1,5},{1,2},{3,0}};
static const glyph_stroke_t stroke_103_2[2] = {{10,9},{4,-9}};
static const glyph_stroke_t stroke_103_3[14] = {{11,9},{8,0},{6,-5},{4,-9},{3,-11},{1,-12},{0,-11},{0,-9},{1,-6},{3,-4},{6,-2},{10,0},{13,2},{15,5}};
static const glyph_stroke_t *strokes_103[4] = {stroke_103_0, stroke_103_1, stroke_103_2, stroke_103_3};
static const uint8_t ncoords_103[4] = {13, 5, 2, 14};
static const glyph_stroke_t stroke_104_0[3] = {{0,5},{2,8},{4,12}};
static const glyph_stroke_t stroke_104_1[2] = {{7,21},{0,0}};
static const glyph_stroke_t stroke_104_2[2] = {{8,21},{1,0}};
static const glyph_stroke_t stroke_104_3[9] = {{3,6},{5,8},{7,9},{8,9},{10,8},{10,6},{9,3},{9,1},{10,0}};
static const glyph_stroke_t stroke_104_4[9] = {{8,9},{9,8},{9,6},{8,3},{8,1},{10,0},{12,1},{13,2},{15,5}};
static const glyph_stroke_t *strokes_104[5] = {stroke_104_0, stroke_104_1, stroke_104_2, stroke_104_3, stroke_104_4};
static const uint8_t ncoords_104[5] = {3, 2, 2, 9, 9};
static const glyph_stroke_t stroke_105_0[5] = {{4,15},{3,14},{4,13},{5,14},{4,15}};
static const glyph_stroke_t stroke_105_1[7] = {{2,9},{0,3},{0,1},{2,0},{4,1},{5,2},{7,5}};
static const glyph_stroke_t stroke_105_2[4] = {{3,9},{1,3},{1,1},{2,0}};
static const glyph_stroke_t *strokes_105[3] = {stroke_105_0, stroke_105_1, stroke_105_2};
static const uint8_t ncoords_105[3] = {5, 7, 4};
static const glyph_stroke_t stroke_106_0[5] = {{12,15},{11,14},{12,13},{13,14},{12,15}};
static const glyph_stroke_t stroke_106_1[2] = {{10,9},{4,-9}};
static const glyph_stroke_t stroke_106_2[14] = {{11,9},{8,0},{6,-5},{4,-9},{3,-11},{1,-12},{0,-11},{0,-9},{1,-6},{3,-4},{6,-2},{10,0},{13,2},{15,5}};
static const glyph_stroke_t *strokes_106[3] = {stroke_106_0, stroke_106_1, stroke_106_2};
static const uint8_t ncoords_106[3] = {5, 2, 14};
static const glyph_stroke_t stroke_107_0[3] = {{0,5},{2,8},{4,12}};
static const glyph_stroke_t stroke_107_1[2] = {{7,21},{0,0}};
static const glyph_stroke_t stroke_107_2[2] = {{8,21},{1,0}};
static const glyph_stroke_t stroke_107_3[7] = {{9,9},{9,8},{10,8},{9,9},{8,9},{6,7},{3,6}};
static const glyph_stroke_t stroke_107_4[4] = {{3,6},{6,5},{7,1},{8,0}};
static const glyph_stroke_t stroke_107_5[7] = {{3,6},{5,5},{6,1},{8,0},{9,0},{12,2},{14,5}};
static const glyph_stroke_t *strokes_107[6] = {stroke_107_0, stroke_107_1, stroke_107_2, stroke_107_3, stroke_107_4, stroke_107_5};
static const uint8_t ncoords_107[6] = {3, 2, 2, 7, 4, 7};
static const glyph_stroke_t stroke_108_0[3] = {{0,5},{2,8},{4,12}};
static const glyph_stroke_t stroke_108_1[7] = {{7,21},{1,3},{1,1},{3,0},{5,1},{6,2},{8,5}};
static const glyph_stroke_t stroke_108_2[4] = {{8,21},{2,3},{2,1},{3,0}};
static const glyph_stroke_t *strokes_108[3] = {stroke_108_0, stroke_108_1, stroke_108_2};
static const uint8_t ncoords_108[3] = {3, 7, 4};
static const glyph_stroke_t stroke_109_0[6] = {{0,5},{2,8},{4,9},{6,8},{6,6},{4,0}};
static const glyph_stroke_t stroke_109_1[4] = {{4,9},{5,8},{5,6},{3,0}};
static const glyph_stroke_t stroke_109_2[7] = {{6,6},{8,8},{10,9},{11,9},{13,8},{13,6},{11,0}};
static const glyph_stroke_t stroke_109_3[4] = {{11,9},{12,8},{12,6},{10,0}};
static const glyph_stroke_t stroke_109_4[9] = {{13,6},{15,8},{17,9},{18,9},{20,8},{20,6},{19,3},{19,1},{20,0}};
static const glyph_stroke_t stroke_109_5[9] = {{18,9},{19,8},{19,6},{18,3},{18,1},{20,0},{22,1},{23,2},{25,5}};
static const glyph_stroke_t *strokes_109[6] = {stroke_109_0, stroke_109_1, stroke_109_2, stroke_109_3, stroke_109_4, stroke_109_5};
static const uint8_t ncoords_109[6] = {6, 4, 7, 4, 9, 9};
static const glyph_stroke_t stroke_110_0[6] = {{0,5},{2,8},{4,9},{6,8},{6,6},{4,0}};
static const glyph_stroke_t stroke_110_1[4] = {{4,9},{5,8},{5,6},{3,0}};
static const glyph_stroke_t stroke_110_2[9] = {{6,6},{8,8},{10,9},{11,9},{13,8},{13,6},{12,3},{12,1},{13,0}};
static const glyph_stroke_t stroke_110_3[9] = {{11,9},{12,8},{12,6},{11,3},{11,1},{13,0},{15,1},{16,2},{18,5}};
static const glyph_stroke_t *strokes_110[4] = {stroke_110_0, stroke_110_1, stroke_110_2, stroke_110_3};
static const uint8_t ncoords_110[4] = {6, 4, 9, 9};
static const glyph_stroke_t stroke_111_0[22] = {{6,9},{4,9},{2,8},{1,7},{0,5},{0,3},{1,1},{3,0},{5,0},{7,1},{8,2},{9,4},{9,6},{8,8},{6,9},{5,8},{5,6},{6,4},{8,3},{10,3},{12,4},{13,5}};
static const glyph_stroke_t stroke_111_1[5] = {{4,9},{2,7},{1,5},{1,2},{3,0}};
static const glyph_stroke_t *strokes_111[2] = {stroke_111_0, stroke_111_1};
static const uint8_t ncoords_111[2] = {22, 5};
static const glyph_stroke_t stroke_112_0[3] = {{4,5},{6,8},{8,12}};
static const glyph_stroke_t stroke_112_1[2] = {{9,15},{0,-12}};
static const glyph_stroke_t stroke_112_2[2] = {{10,15},{1,-12}};
static const glyph_stroke_t stroke_112_3[9] = {{7,6},{9,8},{11,9},{12,9},{14,8},{14,6},{13,3},{13,1},{14,0}};
static const glyph_stroke_t stroke_112_4[9] = {{12,9},{13,8},{13,6},{12,3},{12,1},{14,0},{16,1},{17,2},{19,5}};
static const glyph_stroke_t *strokes_112[5] = {stroke_112_0, stroke_112_1, stroke_112_2, stroke_112_3, stroke_112_4};
static const uint8_t ncoords_112[5] = {3, 2, 2, 9, 9};
static const glyph_stroke_t stroke_113_0[12] = {{9,6},{8,8},{6,9},{4,9},{2,8},{1,7},{0,5},{0,3},{1,1},{3,0},{5,0},{7,1}};
static const glyph_stroke_t stroke_113_1[5] = {{4,9},{2,7},{1,5},{1,2},{3,0}};
static const glyph_stroke_t stroke_113_2[10] = {{10,9},{4,-9},{4,-11},{5,-12},{7,-11},{8,-8},{8,0},{10,0},{13,2},{15,5}};
static const glyph_stroke_t stroke_113_3[4] = {{11,9},{8,0},{6,-5},{4,-9}};
static const glyph_stroke_t *strokes_113[4] = {stroke_113_0, stroke_113_1, stroke_113_2, stroke_113_3};
static const uint8_t ncoords_113[4] = {12, 5, 10, 4};
static const glyph_stroke_t stroke_114_0[6] = {{0,5},{2,8},{4,9},{6,8},{6,6},{4,0}};
static const glyph_stroke_t stroke_114_1[4] = {{4,9},{5,8},{5,6},{3,0}};
static const glyph_stroke_t stroke_114_2[5] = {{6,6},{8,8},{10,9},{11,9},{10,6}};
static const glyph_stroke_t stroke_114_3[5] = {{10,9},{10,6},{11,4},{12,4},{14,5}};
static const glyph_stroke_t *strokes_114[4] = {stroke_114_0, stroke_114_1, stroke_114_2, stroke_114_3};
static const uint8_t ncoords_114[4] = {6, 4, 5, 5};
static const glyph_stroke_t stroke_115_0[9] = {{0,5},{2,8},{3,10},{3,8},{6,6},{7,4},{7,2},{6,1},{4,0}};
static const glyph_stroke_t stroke_115_1[5] = {{3,8},{5,6},{6,4},{6,2},{4,0}};
static const glyph_stroke_t stroke_115_2[5] = {{0,1},{2,0},{7,0},{10,2},{12,5}};
static const glyph_stroke_t *strokes_115[3] = {stroke_115_0, stroke_115_1, stroke_115_2};
static const uint8_t ncoords_115[3] = {9, 5, 5};
static const glyph_stroke_t stroke_116_0[3] = {{0,5},{2,8},{4,12}};
static const glyph_stroke_t stroke_116_1[7] = {{7,21},{1,3},{1,1},{3,0},{5,1},{6,2},{8,5}};
static const glyph_stroke_t stroke_116_2[4] = {{8,21},{2,3},{2,1},{3,0}};
static const glyph_stroke_t stroke_116_3[2] = {{2,13},{8,13}};
static const glyph_stroke_t *strokes_116[4] = {stroke_116_0, stroke_116_1, stroke_116_2, stroke_116_3};
static const uint8_t ncoords_116[4] = {3, 7, 4, 2};
static const glyph_stroke_t stroke_117_0[8] = {{2,9},{0,3},{0,1},{2,0},{3,0},{5,1},{7,3},{9,6}};
static const glyph_stroke_t stroke_117_1[4] = {{3,9},{1,3},{1,1},{2,0}};
static const glyph_stroke_t stroke_117_2[7] = {{10,9},{8,3},{8,1},{10,0},{12,1},{13,2},{15,5}};
static const glyph_stroke_t stroke_117_3[4] = {{11,9},{9,3},{9,1},{10,0}};
static const glyph_stroke_t *strokes_117[4] = {stroke_117_0, stroke_117_1, stroke_117_2, stroke_117_3};
static const uint8_t ncoords_117[4] = {8, 4, 7, 4};
static const glyph_stroke_t stroke_118_0[10] = {{2,9},{1,7},{0,4},{0,1},{2,0},{3,0},{6,1},{8,3},{9,6},{9,9}};
static const glyph_stroke_t stroke_118_1[5] = {{3,9},{2,7},{1,4},{1,1},{2,0}};
static const glyph_stroke_t stroke_118_2[5] = {{9,9},{10,5},{11,4},{12,4},{14,5}};
static const glyph_stroke_t *strokes_118[3] = {stroke_118_0, stroke_118_1, stroke_118_2};
static const uint8_t ncoords_118[3] = {10, 5, 5};
static const glyph_stroke_t stroke_119_0[8] = {{3,9},{1,7},{0,4},{0,1},{2,0},{3,0},{5,1},{7,3}};
static const glyph_stroke_t stroke_119_1[5] = {{4,9},{2,7},{1,4},{1,1},{2,0}};
static const glyph_stroke_t stroke_119_2[9] = {{9,9},{7,3},{7,1},{9,0},{10,0},{12,1},{14,3},{15,6},{15,9}};
static const glyph_stroke_t stroke_119_3[4] = {{10,9},{8,3},{8,1},{9,0}};
static const glyph_stroke_t stroke_119_4[5] = {{15,9},{16,5},{17,4},{18,4},{20,5}};
static const glyph_stroke_t *strokes_119[5] = {stroke_119_0, stroke_119_1, stroke_119_2, stroke_119_3, stroke_119_4};
static const uint8_t ncoords_119[5] = {8, 5, 9, 4, 5};
static const glyph_stroke_t stroke_120_0[14] = {{0,5},{2,8},{4,9},{6,9},{7,8},{7,6},{6,3},{5,1},{3,0},{2,0},{1,1},{1,2},{2,2},{1,1}};
static const glyph_stroke_t stroke_120_1[14] = {{13,8},{12,7},{13,7},{13,8},{12,9},{11,9},{9,8},{8,6},{7,3},{7,1},{8,0},{11,0},{14,2},{16,5}};
static const glyph_stroke_t stroke_120_2[2] = {{7,8},{8,6}};
static const glyph_stroke_t stroke_120_3[2] = {{9,8},{7,6}};
static const glyph_stroke_t stroke_120_4[2] = {{6,3},{7,1}};
static const glyph_stroke_t stroke_120_5[2] = {{7,3},{5,1}};
static const glyph_stroke_t *strokes_120[6] = {stroke_120_0, stroke_120_1, stroke_120_2, stroke_120_3, stroke_120_4, stroke_120_5};
static const uint8_t ncoords_120[6] = {14, 14, 2, 2, 2, 2};
static const glyph_stroke_t stroke_121_0[8] = {{2,9},{0,3},{0,1},{2,0},{3,0},{5,1},{7,3},{9,6}};
static const glyph_stroke_t stroke_121_1[4] = {{3,9},{1,3},{1,1},{2,0}};
static const glyph_stroke_t stroke_121_2[2] = {{10,9},{4,-9}};
static const glyph_stroke_t stroke_121_3[14] = {{11,9},{8,0},{6,-5},{4,-9},{3,-11},{1,-12},{0,-11},{0,-9},{1,-6},{3,-4},{6,-2},{10,0},{13,2},{15,5}};
static const glyph_stroke_t *strokes_121[4] = {stroke_121_0, stroke_121_1, stroke_121_2, stroke_121_3};
static const uint8_t ncoords_121[4] = {8, 4, 2, 14};
static const glyph_stroke_t stroke_122_0[9] = {{1,5},{3,8},{5,9},{7,9},{9,8},{9,5},{8,3},{5,1},{3,0}};
static const glyph_stroke_t stroke_122_1[5] = {{7,9},{8,8},{8,5},{7,3},{5,1}};
static const glyph_stroke_t stroke_122_2[14] = {{3,0},{5,-1},{6,-3},{6,-6},{5,-9},{3,-11},{1,-12},{0,-11},{0,-9},{1,-6},{4,-3},{7,-1},{11,2},{14,5}};
static const glyph_stroke_t stroke_122_3[6] = {{3,0},{4,-1},{5,-3},{5,-6},{4,-9},{3,-11}};
static const glyph_stroke_t *strokes_122[4] = {stroke_122_0, stroke_122_1, stroke_122_2, stroke_122_3};
static const uint8_t ncoords_122[4] = {9, 5, 14, 6};
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
	{ 0x00000023, 0, -7, 15, 21, -3, 18, 0, 4, strokes_35, ncoords_35 },
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
	{ 0x0000002e, 0, 0, 2, 2, -2, 9, 0, 1, strokes_46, ncoords_46 },
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
	{ 0x00000041, 0, 0, 20, 21, 1, 24, 0, 4, strokes_65, ncoords_65 },
	{ 0x00000042, 0, 0, 20, 21, -1, 23, 0, 6, strokes_66, ncoords_66 },
	{ 0x00000043, 0, 0, 16, 21, -2, 19, 0, 2, strokes_67, ncoords_67 },
	{ 0x00000044, 0, 0, 19, 21, -1, 22, 0, 2, strokes_68, ncoords_68 },
	{ 0x00000045, 0, 0, 15, 21, -2, 17, 0, 4, strokes_69, ncoords_69 },
	{ 0x00000046, 0, 0, 19, 21, -1, 20, 0, 4, strokes_70, ncoords_70 },
	{ 0x00000047, 0, 0, 17, 21, -2, 20, 0, 4, strokes_71, ncoords_71 },
	{ 0x00000048, 0, 0, 24, 21, 0, 24, 0, 4, strokes_72, ncoords_72 },
	{ 0x00000049, 0, 0, 16, 21, 0, 16, 0, 2, strokes_73, ncoords_73 },
	{ 0x0000004a, 0, -4, 15, 21, -1, 16, 0, 2, strokes_74, ncoords_74 },
	{ 0x0000004b, 0, 0, 24, 21, 0, 24, 0, 6, strokes_75, ncoords_75 },
	{ 0x0000004c, 0, 0, 19, 21, 1, 19, 0, 2, strokes_76, ncoords_76 },
	{ 0x0000004d, 0, 0, 28, 21, 2, 30, 0, 6, strokes_77, ncoords_77 },
	{ 0x0000004e, 0, 0, 28, 21, 2, 25, 0, 4, strokes_78, ncoords_78 },
	{ 0x0000004f, 0, 0, 15, 21, -3, 18, 0, 2, strokes_79, ncoords_79 },
	{ 0x00000050, 0, 0, 20, 21, -1, 22, 0, 4, strokes_80, ncoords_80 },
	{ 0x00000051, 0, 0, 18, 21, 0, 21, 0, 2, strokes_81, ncoords_81 },
	{ 0x00000052, 0, 0, 22, 21, -1, 23, 0, 6, strokes_82, ncoords_82 },
	{ 0x00000053, 0, 0, 20, 21, 0, 20, 0, 2, strokes_83, ncoords_83 },
	{ 0x00000054, 0, 0, 18, 21, -1, 17, 0, 3, strokes_84, ncoords_84 },
	{ 0x00000055, 0, 0, 20, 21, -1, 21, 0, 4, strokes_85, ncoords_85 },
	{ 0x00000056, 0, 0, 21, 21, -1, 20, 0, 2, strokes_86, ncoords_86 },
	{ 0x00000057, 0, 0, 25, 21, -1, 22, 0, 6, strokes_87, ncoords_87 },
	{ 0x00000058, 0, 0, 23, 21, 1, 21, 0, 3, strokes_88, ncoords_88 },
	{ 0x00000059, 0, 0, 20, 21, -2, 20, 0, 4, strokes_89, ncoords_89 },
	{ 0x0000005a, 0, 0, 22, 21, 0, 21, 0, 3, strokes_90, ncoords_90 },
	{ 0x0000005b, 0, -7, 7, 25, -4, 10, 0, 4, strokes_91, ncoords_91 },
	{ 0x0000005c, 0, -3, 14, 21, 0, 14, 0, 1, strokes_92, ncoords_92 },
	{ 0x0000005d, 0, -7, 7, 25, -3, 11, 0, 4, strokes_93, ncoords_93 },
	{ 0x0000005e, 0, 0, 10, 18, -3, 13, 0, 3, strokes_94, ncoords_94 },
	{ 0x0000005f, 0, -2, 16, -2, 0, 16, 0, 1, strokes_95, ncoords_95 },
	{ 0x00000060, 0, 15, 3, 21, -6, 5, 0, 1, strokes_96, ncoords_96 },
	{ 0x00000061, 0, 0, 15, 9, -1, 15, 0, 4, strokes_97, ncoords_97 },
	{ 0x00000062, 0, 0, 14, 21, 0, 14, 0, 3, strokes_98, ncoords_98 },
	{ 0x00000063, 0, 0, 11, 9, -1, 11, 0, 2, strokes_99, ncoords_99 },
	{ 0x00000064, 0, 0, 15, 21, -1, 15, 0, 4, strokes_100, ncoords_100 },
	{ 0x00000065, 0, 0, 11, 9, -1, 11, 0, 2, strokes_101, ncoords_101 },
	{ 0x00000066, 0, -12, 13, 21, 4, 13, 0, 2, strokes_102, ncoords_102 },
	{ 0x00000067, 0, -12, 15, 9, -1, 15, 0, 4, strokes_103, ncoords_103 },
	{ 0x00000068, 0, 0, 15, 21, 0, 15, 0, 5, strokes_104, ncoords_104 },
	{ 0x00000069, 0, 0, 7, 15, -1, 7, 0, 3, strokes_105, ncoords_105 },
	{ 0x0000006a, 0, -12, 15, 15, 7, 15, 0, 3, strokes_106, ncoords_106 },
	{ 0x0000006b, 0, 0, 14, 21, 0, 14, 0, 6, strokes_107, ncoords_107 },
	{ 0x0000006c, 0, 0, 8, 21, 0, 8, 0, 3, strokes_108, ncoords_108 },
	{ 0x0000006d, 0, 0, 25, 9, 0, 25, 0, 6, strokes_109, ncoords_109 },
	{ 0x0000006e, 0, 0, 18, 9, 0, 18, 0, 4, strokes_110, ncoords_110 },
	{ 0x0000006f, 0, 0, 13, 9, -1, 13, 0, 2, strokes_111, ncoords_111 },
	{ 0x00000070, 0, -12, 19, 15, 4, 19, 0, 5, strokes_112, ncoords_112 },
	{ 0x00000071, 0, -12, 15, 9, -1, 15, 0, 4, strokes_113, ncoords_113 },
	{ 0x00000072, 0, 0, 14, 9, 0, 14, 0, 4, strokes_114, ncoords_114 },
	{ 0x00000073, 0, 0, 12, 10, 0, 12, 0, 3, strokes_115, ncoords_115 },
	{ 0x00000074, 0, 0, 8, 21, 0, 8, 0, 4, strokes_116, ncoords_116 },
	{ 0x00000075, 0, 0, 15, 9, -1, 15, 0, 4, strokes_117, ncoords_117 },
	{ 0x00000076, 0, 0, 14, 9, -1, 14, 0, 3, strokes_118, ncoords_118 },
	{ 0x00000077, 0, 0, 20, 9, -1, 20, 0, 5, strokes_119, ncoords_119 },
	{ 0x00000078, 0, 0, 16, 9, 0, 16, 0, 6, strokes_120, ncoords_120 },
	{ 0x00000079, 0, -12, 15, 9, -1, 15, 0, 4, strokes_121, ncoords_121 },
	{ 0x0000007a, 0, -12, 14, 9, 1, 14, 0, 4, strokes_122, ncoords_122 },
	{ 0x0000007b, 0, -7, 5, 25, -4, 10, 0, 3, strokes_123, ncoords_123 },
	{ 0x0000007c, 0, -7, 0, 25, -4, 4, 0, 1, strokes_124, ncoords_124 },
	{ 0x0000007d, 0, -7, 5, 25, -5, 9, 0, 3, strokes_125, ncoords_125 },
	{ 0x0000007e, 0, 6, 18, 12, -3, 21, 0, 2, strokes_126, ncoords_126 },
	{ 0x0000007f, 0, 13, 8, 21, -5, 10, 0, 1, strokes_127, ncoords_127 }
};
const font_data_t font_hscript_2 = {
	"Hershey Script - double stroke",
	21,
	96,
	glyph_data
};
