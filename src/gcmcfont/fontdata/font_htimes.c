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

static const glyph_stroke_t stroke_33_0[5] = {{1,21},{0,19},{1,7},{2,19},{1,21}};
static const glyph_stroke_t stroke_33_1[2] = {{1,19},{1,13}};
static const glyph_stroke_t stroke_33_2[5] = {{1,2},{0,1},{1,0},{2,1},{1,2}};
static const glyph_stroke_t *strokes_33[3] = {stroke_33_0, stroke_33_1, stroke_33_2};
static const uint8_t ncoords_33[3] = {5, 2, 5};
static const glyph_stroke_t stroke_34_0[3] = {{1,21},{0,20},{0,14}};
static const glyph_stroke_t stroke_34_1[2] = {{1,20},{0,14}};
static const glyph_stroke_t stroke_34_2[3] = {{1,21},{2,20},{0,14}};
static const glyph_stroke_t stroke_34_3[3] = {{10,21},{9,20},{9,14}};
static const glyph_stroke_t stroke_34_4[2] = {{10,20},{9,14}};
static const glyph_stroke_t stroke_34_5[3] = {{10,21},{11,20},{9,14}};
static const glyph_stroke_t *strokes_34[6] = {stroke_34_0, stroke_34_1, stroke_34_2, stroke_34_3, stroke_34_4, stroke_34_5};
static const uint8_t ncoords_34[6] = {3, 2, 3, 3, 2, 3};
static const glyph_stroke_t stroke_35_0[2] = {{8,25},{1,-7}};
static const glyph_stroke_t stroke_35_1[2] = {{14,25},{7,-7}};
static const glyph_stroke_t stroke_35_2[2] = {{1,12},{15,12}};
static const glyph_stroke_t stroke_35_3[2] = {{0,6},{14,6}};
static const glyph_stroke_t *strokes_35[4] = {stroke_35_0, stroke_35_1, stroke_35_2, stroke_35_3};
static const uint8_t ncoords_35[4] = {2, 2, 2, 2};
static const glyph_stroke_t stroke_36_0[2] = {{5,25},{5,-4}};
static const glyph_stroke_t stroke_36_1[2] = {{9,25},{9,-4}};
static const glyph_stroke_t stroke_36_2[17] = {{13,18},{12,17},{13,16},{14,17},{14,18},{12,20},{9,21},{5,21},{2,20},{0,18},{0,16},{1,14},{2,13},{4,12},{10,10},{12,9},{14,7}};
static const glyph_stroke_t stroke_36_3[17] = {{0,16},{2,14},{4,13},{10,11},{12,10},{13,9},{14,7},{14,3},{12,1},{9,0},{5,0},{2,1},{0,3},{0,4},{1,5},{2,4},{1,3}};
static const glyph_stroke_t *strokes_36[4] = {stroke_36_0, stroke_36_1, stroke_36_2, stroke_36_3};
static const uint8_t ncoords_36[4] = {2, 2, 17, 17};
static const glyph_stroke_t stroke_37_0[2] = {{18,21},{0,0}};
static const glyph_stroke_t stroke_37_1[16] = {{5,21},{7,19},{7,17},{6,15},{4,14},{2,14},{0,16},{0,18},{1,20},{3,21},{5,21},{7,20},{10,19},{13,19},{16,20},{18,21}};
static const glyph_stroke_t stroke_37_2[11] = {{14,7},{12,6},{11,4},{11,2},{13,0},{15,0},{17,1},{18,3},{18,5},{16,7},{14,7}};
static const glyph_stroke_t *strokes_37[3] = {stroke_37_0, stroke_37_1, stroke_37_2};
static const uint8_t ncoords_37[3] = {2, 16, 11};
static const glyph_stroke_t stroke_38_0[35] = {{18,13},{17,12},{18,11},{19,12},{19,13},{18,14},{17,14},{16,13},{15,11},{13,6},{11,3},{9,1},{7,0},{4,0},{1,1},{0,3},{0,6},{1,8},{7,12},{9,14},{10,16},{10,18},{9,20},{7,21},{5,20},{4,18},{4,16},{5,13},{7,10},{12,3},{14,1},{17,0},{18,0},{19,1},{19,2}};
static const glyph_stroke_t stroke_38_1[6] = {{4,0},{2,1},{1,3},{1,6},{2,8},{4,10}};
static const glyph_stroke_t stroke_38_2[5] = {{4,16},{5,14},{13,3},{15,1},{17,0}};
static const glyph_stroke_t *strokes_38[3] = {stroke_38_0, stroke_38_1, stroke_38_2};
static const uint8_t ncoords_38[3] = {35, 6, 5};
static const glyph_stroke_t stroke_39_0[2] = {{1,21},{0,14}};
static const glyph_stroke_t stroke_39_1[2] = {{2,21},{0,14}};
static const glyph_stroke_t *strokes_39[2] = {stroke_39_0, stroke_39_1};
static const uint8_t ncoords_39[2] = {2, 2};
static const glyph_stroke_t stroke_40_0[10] = {{7,25},{5,23},{3,20},{1,16},{0,11},{0,7},{1,2},{3,-2},{5,-5},{7,-7}};
static const glyph_stroke_t stroke_40_1[8] = {{5,23},{3,19},{2,16},{1,11},{1,7},{2,2},{3,-1},{5,-5}};
static const glyph_stroke_t *strokes_40[2] = {stroke_40_0, stroke_40_1};
static const uint8_t ncoords_40[2] = {10, 8};
static const glyph_stroke_t stroke_41_0[10] = {{0,25},{2,23},{4,20},{6,16},{7,11},{7,7},{6,2},{4,-2},{2,-5},{0,-7}};
static const glyph_stroke_t stroke_41_1[8] = {{2,23},{4,19},{5,16},{6,11},{6,7},{5,2},{4,-1},{2,-5}};
static const glyph_stroke_t *strokes_41[2] = {stroke_41_0, stroke_41_1};
static const uint8_t ncoords_41[2] = {10, 8};
static const glyph_stroke_t stroke_42_0[2] = {{5,15},{5,3}};
static const glyph_stroke_t stroke_42_1[2] = {{0,12},{10,6}};
static const glyph_stroke_t stroke_42_2[2] = {{10,12},{0,6}};
static const glyph_stroke_t *strokes_42[3] = {stroke_42_0, stroke_42_1, stroke_42_2};
static const uint8_t ncoords_42[3] = {2, 2, 2};
static const glyph_stroke_t stroke_43_0[2] = {{9,18},{9,0}};
static const glyph_stroke_t stroke_43_1[2] = {{0,9},{18,9}};
static const glyph_stroke_t *strokes_43[2] = {stroke_43_0, stroke_43_1};
static const uint8_t ncoords_43[2] = {2, 2};
static const glyph_stroke_t stroke_44_0[7] = {{2,1},{1,0},{0,1},{1,2},{2,1},{2,-1},{0,-3}};
static const glyph_stroke_t *strokes_44[1] = {stroke_44_0};
static const uint8_t ncoords_44[1] = {7};
static const glyph_stroke_t stroke_45_0[2] = {{0,9},{12,9}};
static const glyph_stroke_t *strokes_45[1] = {stroke_45_0};
static const uint8_t ncoords_45[1] = {2};
static const glyph_stroke_t stroke_46_0[5] = {{1,2},{0,1},{1,0},{2,1},{1,2}};
static const glyph_stroke_t *strokes_46[1] = {stroke_46_0};
static const uint8_t ncoords_46[1] = {5};
static const glyph_stroke_t stroke_47_0[2] = {{18,25},{0,-7}};
static const glyph_stroke_t *strokes_47[1] = {stroke_47_0};
static const uint8_t ncoords_47[1] = {2};
static const glyph_stroke_t stroke_48_0[17] = {{6,21},{3,20},{1,17},{0,12},{0,9},{1,4},{3,1},{6,0},{8,0},{11,1},{13,4},{14,9},{14,12},{13,17},{11,20},{8,21},{6,21}};
static const glyph_stroke_t stroke_48_1[10] = {{6,21},{4,20},{3,19},{2,17},{1,12},{1,9},{2,4},{3,2},{4,1},{6,0}};
static const glyph_stroke_t stroke_48_2[10] = {{8,0},{10,1},{11,2},{12,4},{13,9},{13,12},{12,17},{11,19},{10,20},{8,21}};
static const glyph_stroke_t *strokes_48[3] = {stroke_48_0, stroke_48_1, stroke_48_2};
static const uint8_t ncoords_48[3] = {17, 10, 10};
static const glyph_stroke_t stroke_49_0[4] = {{0,17},{2,18},{5,21},{5,0}};
static const glyph_stroke_t stroke_49_1[2] = {{4,20},{4,0}};
static const glyph_stroke_t stroke_49_2[2] = {{0,0},{9,0}};
static const glyph_stroke_t *strokes_49[3] = {stroke_49_0, stroke_49_1, stroke_49_2};
static const uint8_t ncoords_49[3] = {4, 2, 2};
static const glyph_stroke_t stroke_50_0[20] = {{1,17},{2,16},{1,15},{0,16},{0,17},{1,19},{2,20},{5,21},{9,21},{12,20},{13,19},{14,17},{14,15},{13,13},{10,11},{5,9},{3,8},{1,6},{0,3},{0,0}};
static const glyph_stroke_t stroke_50_1[8] = {{9,21},{11,20},{12,19},{13,17},{13,15},{12,13},{9,11},{5,9}};
static const glyph_stroke_t stroke_50_2[7] = {{0,2},{1,3},{3,3},{8,1},{11,1},{13,2},{14,3}};
static const glyph_stroke_t stroke_50_3[6] = {{3,3},{8,0},{12,0},{13,1},{14,3},{14,5}};
static const glyph_stroke_t *strokes_50[4] = {stroke_50_0, stroke_50_1, stroke_50_2, stroke_50_3};
static const uint8_t ncoords_50[4] = {20, 8, 7, 6};
static const glyph_stroke_t stroke_51_0[15] = {{1,17},{2,16},{1,15},{0,16},{0,17},{1,19},{2,20},{5,21},{9,21},{12,20},{13,18},{13,15},{12,13},{9,12},{6,12}};
static const glyph_stroke_t stroke_51_1[6] = {{9,21},{11,20},{12,18},{12,15},{11,13},{9,12}};
static const glyph_stroke_t stroke_51_2[16] = {{9,12},{11,11},{13,9},{14,7},{14,4},{13,2},{12,1},{9,0},{5,0},{2,1},{1,2},{0,4},{0,5},{1,6},{2,5},{1,4}};
static const glyph_stroke_t stroke_51_3[6] = {{12,10},{13,7},{13,4},{12,2},{11,1},{9,0}};
static const glyph_stroke_t *strokes_51[4] = {stroke_51_0, stroke_51_1, stroke_51_2, stroke_51_3};
static const uint8_t ncoords_51[4] = {15, 6, 16, 6};
static const glyph_stroke_t stroke_52_0[2] = {{10,19},{10,0}};
static const glyph_stroke_t stroke_52_1[2] = {{11,21},{11,0}};
static const glyph_stroke_t stroke_52_2[3] = {{11,21},{0,6},{16,6}};
static const glyph_stroke_t stroke_52_3[2] = {{7,0},{14,0}};
static const glyph_stroke_t *strokes_52[4] = {stroke_52_0, stroke_52_1, stroke_52_2, stroke_52_3};
static const uint8_t ncoords_52[4] = {2, 2, 3, 2};
static const glyph_stroke_t stroke_53_0[2] = {{2,21},{0,11}};
static const glyph_stroke_t stroke_53_1[19] = {{0,11},{2,13},{5,14},{8,14},{11,13},{13,11},{14,8},{14,6},{13,3},{11,1},{8,0},{5,0},{2,1},{1,2},{0,4},{0,5},{1,6},{2,5},{1,4}};
static const glyph_stroke_t stroke_53_2[8] = {{8,14},{10,13},{12,11},{13,8},{13,6},{12,3},{10,1},{8,0}};
static const glyph_stroke_t stroke_53_3[2] = {{2,21},{12,21}};
static const glyph_stroke_t stroke_53_4[3] = {{2,20},{7,20},{12,21}};
static const glyph_stroke_t *strokes_53[5] = {stroke_53_0, stroke_53_1, stroke_53_2, stroke_53_3, stroke_53_4};
static const uint8_t ncoords_53[5] = {2, 19, 8, 2, 3};
static const glyph_stroke_t stroke_54_0[28] = {{12,18},{11,17},{12,16},{13,17},{13,18},{12,20},{10,21},{7,21},{4,20},{2,18},{1,16},{0,12},{0,6},{1,3},{3,1},{6,0},{8,0},{11,1},{13,3},{14,6},{14,7},{13,10},{11,12},{8,13},{7,13},{4,12},{2,10},{1,7}};
static const glyph_stroke_t stroke_54_1[9] = {{7,21},{5,20},{3,18},{2,16},{1,12},{1,6},{2,3},{4,1},{6,0}};
static const glyph_stroke_t stroke_54_2[8] = {{8,0},{10,1},{12,3},{13,6},{13,7},{12,10},{10,12},{8,13}};
static const glyph_stroke_t *strokes_54[3] = {stroke_54_0, stroke_54_1, stroke_54_2};
static const uint8_t ncoords_54[3] = {28, 9, 8};
static const glyph_stroke_t stroke_55_0[2] = {{0,21},{0,15}};
static const glyph_stroke_t stroke_55_1[8] = {{0,17},{1,19},{3,21},{5,21},{10,18},{12,18},{13,19},{14,21}};
static const glyph_stroke_t stroke_55_2[4] = {{1,19},{3,20},{5,20},{10,18}};
static const glyph_stroke_t stroke_55_3[7] = {{14,21},{14,18},{13,15},{9,10},{8,8},{7,5},{7,0}};
static const glyph_stroke_t stroke_55_4[5] = {{13,15},{8,10},{7,8},{6,5},{6,0}};
static const glyph_stroke_t *strokes_55[5] = {stroke_55_0, stroke_55_1, stroke_55_2, stroke_55_3, stroke_55_4};
static const uint8_t ncoords_55[5] = {2, 8, 4, 7, 5};
static const glyph_stroke_t stroke_56_0[13] = {{5,21},{2,20},{1,18},{1,15},{2,13},{5,12},{9,12},{12,13},{13,15},{13,18},{12,20},{9,21},{5,21}};
static const glyph_stroke_t stroke_56_1[6] = {{5,21},{3,20},{2,18},{2,15},{3,13},{5,12}};
static const glyph_stroke_t stroke_56_2[6] = {{9,12},{11,13},{12,15},{12,18},{11,20},{9,21}};
static const glyph_stroke_t stroke_56_3[16] = {{5,12},{2,11},{1,10},{0,8},{0,4},{1,2},{2,1},{5,0},{9,0},{12,1},{13,2},{14,4},{14,8},{13,10},{12,11},{9,12}};
static const glyph_stroke_t stroke_56_4[8] = {{5,12},{3,11},{2,10},{1,8},{1,4},{2,2},{3,1},{5,0}};
static const glyph_stroke_t stroke_56_5[8] = {{9,0},{11,1},{12,2},{13,4},{13,8},{12,10},{11,11},{9,12}};
static const glyph_stroke_t *strokes_56[6] = {stroke_56_0, stroke_56_1, stroke_56_2, stroke_56_3, stroke_56_4, stroke_56_5};
static const uint8_t ncoords_56[6] = {13, 6, 6, 16, 8, 8};
static const glyph_stroke_t stroke_57_0[28] = {{13,14},{12,11},{10,9},{7,8},{6,8},{3,9},{1,11},{0,14},{0,15},{1,18},{3,20},{6,21},{8,21},{11,20},{13,18},{14,15},{14,9},{13,5},{12,3},{10,1},{7,0},{4,0},{2,1},{1,3},{1,4},{2,5},{3,4},{2,3}};
static const glyph_stroke_t stroke_57_1[8] = {{6,8},{4,9},{2,11},{1,14},{1,15},{2,18},{4,20},{6,21}};
static const glyph_stroke_t stroke_57_2[9] = {{8,21},{10,20},{12,18},{13,15},{13,9},{12,5},{11,3},{9,1},{7,0}};
static const glyph_stroke_t *strokes_57[3] = {stroke_57_0, stroke_57_1, stroke_57_2};
static const uint8_t ncoords_57[3] = {28, 8, 9};
static const glyph_stroke_t stroke_58_0[5] = {{1,9},{0,8},{1,7},{2,8},{1,9}};
static const glyph_stroke_t stroke_58_1[5] = {{1,2},{0,1},{1,0},{2,1},{1,2}};
static const glyph_stroke_t *strokes_58[2] = {stroke_58_0, stroke_58_1};
static const uint8_t ncoords_58[2] = {5, 5};
static const glyph_stroke_t stroke_59_0[5] = {{1,12},{0,11},{1,10},{2,11},{1,12}};
static const glyph_stroke_t stroke_59_1[7] = {{2,4},{1,3},{0,4},{1,5},{2,4},{2,2},{0,0}};
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
static const glyph_stroke_t stroke_63_0[17] = {{1,17},{2,16},{1,15},{0,16},{0,17},{1,19},{2,20},{4,21},{7,21},{10,20},{11,19},{12,17},{12,15},{11,13},{10,12},{6,10},{6,7}};
static const glyph_stroke_t stroke_63_1[7] = {{7,21},{9,20},{10,19},{11,17},{11,15},{10,13},{8,11}};
static const glyph_stroke_t stroke_63_2[5] = {{6,2},{5,1},{6,0},{7,1},{6,2}};
static const glyph_stroke_t *strokes_63[3] = {stroke_63_0, stroke_63_1, stroke_63_2};
static const uint8_t ncoords_63[3] = {17, 7, 5};
static const glyph_stroke_t stroke_64_0[13] = {{15,13},{14,15},{12,16},{9,16},{7,15},{6,14},{5,11},{5,8},{6,6},{8,5},{11,5},{13,6},{14,8}};
static const glyph_stroke_t stroke_64_1[6] = {{9,16},{7,14},{6,11},{6,8},{7,6},{8,5}};
static const glyph_stroke_t stroke_64_2[29] = {{15,16},{14,8},{14,6},{16,5},{18,5},{20,7},{21,10},{21,12},{20,15},{19,17},{17,19},{15,20},{12,21},{9,21},{6,20},{4,19},{2,17},{1,15},{0,12},{0,9},{1,6},{2,4},{4,2},{6,1},{9,0},{12,0},{15,1},{17,2},{18,3}};
static const glyph_stroke_t stroke_64_3[4] = {{16,16},{15,8},{15,6},{16,5}};
static const glyph_stroke_t *strokes_64[4] = {stroke_64_0, stroke_64_1, stroke_64_2, stroke_64_3};
static const uint8_t ncoords_64[4] = {13, 6, 29, 4};
static const glyph_stroke_t stroke_65_0[2] = {{9,21},{2,0}};
static const glyph_stroke_t stroke_65_1[2] = {{9,21},{16,0}};
static const glyph_stroke_t stroke_65_2[2] = {{9,18},{15,0}};
static const glyph_stroke_t stroke_65_3[2] = {{4,6},{13,6}};
static const glyph_stroke_t stroke_65_4[2] = {{0,0},{6,0}};
static const glyph_stroke_t stroke_65_5[2] = {{12,0},{18,0}};
static const glyph_stroke_t *strokes_65[6] = {stroke_65_0, stroke_65_1, stroke_65_2, stroke_65_3, stroke_65_4, stroke_65_5};
static const uint8_t ncoords_65[6] = {2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_66_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_66_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_66_2[9] = {{0,21},{12,21},{15,20},{16,19},{17,17},{17,15},{16,13},{15,12},{12,11}};
static const glyph_stroke_t stroke_66_3[8] = {{12,21},{14,20},{15,19},{16,17},{16,15},{15,13},{14,12},{12,11}};
static const glyph_stroke_t stroke_66_4[10] = {{4,11},{12,11},{15,10},{16,9},{17,7},{17,4},{16,2},{15,1},{12,0},{0,0}};
static const glyph_stroke_t stroke_66_5[8] = {{12,11},{14,10},{15,9},{16,7},{16,4},{15,2},{14,1},{12,0}};
static const glyph_stroke_t *strokes_66[6] = {stroke_66_0, stroke_66_1, stroke_66_2, stroke_66_3, stroke_66_4, stroke_66_5};
static const uint8_t ncoords_66[6] = {2, 2, 9, 8, 10, 8};
static const glyph_stroke_t stroke_67_0[20] = {{14,18},{15,15},{15,21},{14,18},{12,20},{9,21},{7,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3},{4,1},{7,0},{9,0},{12,1},{14,3},{15,5}};
static const glyph_stroke_t stroke_67_1[10] = {{7,21},{5,20},{3,18},{2,16},{1,13},{1,8},{2,5},{3,3},{5,1},{7,0}};
static const glyph_stroke_t *strokes_67[2] = {stroke_67_0, stroke_67_1};
static const uint8_t ncoords_67[2] = {20, 10};
static const glyph_stroke_t stroke_68_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_68_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_68_2[12] = {{0,21},{10,21},{13,20},{15,18},{16,16},{17,13},{17,8},{16,5},{15,3},{13,1},{10,0},{0,0}};
static const glyph_stroke_t stroke_68_3[10] = {{10,21},{12,20},{14,18},{15,16},{16,13},{16,8},{15,5},{14,3},{12,1},{10,0}};
static const glyph_stroke_t *strokes_68[4] = {stroke_68_0, stroke_68_1, stroke_68_2, stroke_68_3};
static const uint8_t ncoords_68[4] = {2, 2, 12, 10};
static const glyph_stroke_t stroke_69_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_69_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_69_2[2] = {{10,15},{10,7}};
static const glyph_stroke_t stroke_69_3[4] = {{0,21},{16,21},{16,15},{15,21}};
static const glyph_stroke_t stroke_69_4[2] = {{4,11},{10,11}};
static const glyph_stroke_t stroke_69_5[4] = {{0,0},{16,0},{16,6},{15,0}};
static const glyph_stroke_t *strokes_69[6] = {stroke_69_0, stroke_69_1, stroke_69_2, stroke_69_3, stroke_69_4, stroke_69_5};
static const uint8_t ncoords_69[6] = {2, 2, 2, 4, 2, 4};
static const glyph_stroke_t stroke_70_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_70_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_70_2[2] = {{10,15},{10,7}};
static const glyph_stroke_t stroke_70_3[4] = {{0,21},{16,21},{16,15},{15,21}};
static const glyph_stroke_t stroke_70_4[2] = {{4,11},{10,11}};
static const glyph_stroke_t stroke_70_5[2] = {{0,0},{7,0}};
static const glyph_stroke_t *strokes_70[6] = {stroke_70_0, stroke_70_1, stroke_70_2, stroke_70_3, stroke_70_4, stroke_70_5};
static const uint8_t ncoords_70[6] = {2, 2, 2, 4, 2, 2};
static const glyph_stroke_t stroke_71_0[19] = {{14,18},{15,15},{15,21},{14,18},{12,20},{9,21},{7,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3},{4,1},{7,0},{9,0},{12,1},{14,3}};
static const glyph_stroke_t stroke_71_1[10] = {{7,21},{5,20},{3,18},{2,16},{1,13},{1,8},{2,5},{3,3},{5,1},{7,0}};
static const glyph_stroke_t stroke_71_2[2] = {{14,8},{14,0}};
static const glyph_stroke_t stroke_71_3[2] = {{15,8},{15,0}};
static const glyph_stroke_t stroke_71_4[2] = {{11,8},{18,8}};
static const glyph_stroke_t *strokes_71[5] = {stroke_71_0, stroke_71_1, stroke_71_2, stroke_71_3, stroke_71_4};
static const uint8_t ncoords_71[5] = {19, 10, 2, 2, 2};
static const glyph_stroke_t stroke_72_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_72_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_72_2[2] = {{16,21},{16,0}};
static const glyph_stroke_t stroke_72_3[2] = {{17,21},{17,0}};
static const glyph_stroke_t stroke_72_4[2] = {{0,21},{7,21}};
static const glyph_stroke_t stroke_72_5[2] = {{13,21},{20,21}};
static const glyph_stroke_t stroke_72_6[2] = {{4,11},{16,11}};
static const glyph_stroke_t stroke_72_7[2] = {{0,0},{7,0}};
static const glyph_stroke_t stroke_72_8[2] = {{13,0},{20,0}};
static const glyph_stroke_t *strokes_72[9] = {stroke_72_0, stroke_72_1, stroke_72_2, stroke_72_3, stroke_72_4, stroke_72_5, stroke_72_6, stroke_72_7, stroke_72_8};
static const uint8_t ncoords_72[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_73_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_73_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_73_2[2] = {{0,21},{7,21}};
static const glyph_stroke_t stroke_73_3[2] = {{0,0},{7,0}};
static const glyph_stroke_t *strokes_73[4] = {stroke_73_0, stroke_73_1, stroke_73_2, stroke_73_3};
static const uint8_t ncoords_73[4] = {2, 2, 2, 2};
static const glyph_stroke_t stroke_74_0[11] = {{8,21},{8,4},{7,1},{5,0},{3,0},{1,1},{0,3},{0,5},{1,6},{2,5},{1,4}};
static const glyph_stroke_t stroke_74_1[4] = {{7,21},{7,4},{6,1},{5,0}};
static const glyph_stroke_t stroke_74_2[2] = {{4,21},{11,21}};
static const glyph_stroke_t *strokes_74[3] = {stroke_74_0, stroke_74_1, stroke_74_2};
static const uint8_t ncoords_74[3] = {11, 4, 2};
static const glyph_stroke_t stroke_75_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_75_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_75_2[2] = {{17,21},{4,8}};
static const glyph_stroke_t stroke_75_3[2] = {{9,12},{17,0}};
static const glyph_stroke_t stroke_75_4[2] = {{8,12},{16,0}};
static const glyph_stroke_t stroke_75_5[2] = {{0,21},{7,21}};
static const glyph_stroke_t stroke_75_6[2] = {{13,21},{19,21}};
static const glyph_stroke_t stroke_75_7[2] = {{0,0},{7,0}};
static const glyph_stroke_t stroke_75_8[2] = {{13,0},{19,0}};
static const glyph_stroke_t *strokes_75[9] = {stroke_75_0, stroke_75_1, stroke_75_2, stroke_75_3, stroke_75_4, stroke_75_5, stroke_75_6, stroke_75_7, stroke_75_8};
static const uint8_t ncoords_75[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_76_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_76_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_76_2[2] = {{0,21},{7,21}};
static const glyph_stroke_t stroke_76_3[4] = {{0,0},{15,0},{15,6},{14,0}};
static const glyph_stroke_t *strokes_76[4] = {stroke_76_0, stroke_76_1, stroke_76_2, stroke_76_3};
static const uint8_t ncoords_76[4] = {2, 2, 2, 4};
static const glyph_stroke_t stroke_77_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_77_1[2] = {{4,21},{10,3}};
static const glyph_stroke_t stroke_77_2[2] = {{3,21},{10,0}};
static const glyph_stroke_t stroke_77_3[2] = {{17,21},{10,0}};
static const glyph_stroke_t stroke_77_4[2] = {{17,21},{17,0}};
static const glyph_stroke_t stroke_77_5[2] = {{18,21},{18,0}};
static const glyph_stroke_t stroke_77_6[2] = {{0,21},{4,21}};
static const glyph_stroke_t stroke_77_7[2] = {{17,21},{21,21}};
static const glyph_stroke_t stroke_77_8[2] = {{0,0},{6,0}};
static const glyph_stroke_t stroke_77_9[2] = {{14,0},{21,0}};
static const glyph_stroke_t *strokes_77[10] = {stroke_77_0, stroke_77_1, stroke_77_2, stroke_77_3, stroke_77_4, stroke_77_5, stroke_77_6, stroke_77_7, stroke_77_8, stroke_77_9};
static const uint8_t ncoords_77[10] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_78_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_78_1[2] = {{4,21},{16,2}};
static const glyph_stroke_t stroke_78_2[2] = {{4,19},{16,0}};
static const glyph_stroke_t stroke_78_3[2] = {{16,21},{16,0}};
static const glyph_stroke_t stroke_78_4[2] = {{0,21},{4,21}};
static const glyph_stroke_t stroke_78_5[2] = {{13,21},{19,21}};
static const glyph_stroke_t stroke_78_6[2] = {{0,0},{6,0}};
static const glyph_stroke_t *strokes_78[7] = {stroke_78_0, stroke_78_1, stroke_78_2, stroke_78_3, stroke_78_4, stroke_78_5, stroke_78_6};
static const uint8_t ncoords_78[7] = {2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_79_0[21] = {{7,21},{4,20},{2,18},{1,16},{0,12},{0,9},{1,5},{2,3},{4,1},{7,0},{9,0},{12,1},{14,3},{15,5},{16,9},{16,12},{15,16},{14,18},{12,20},{9,21},{7,21}};
static const glyph_stroke_t stroke_79_1[10] = {{7,21},{5,20},{3,18},{2,16},{1,12},{1,9},{2,5},{3,3},{5,1},{7,0}};
static const glyph_stroke_t stroke_79_2[10] = {{9,0},{11,1},{13,3},{14,5},{15,9},{15,12},{14,16},{13,18},{11,20},{9,21}};
static const glyph_stroke_t *strokes_79[3] = {stroke_79_0, stroke_79_1, stroke_79_2};
static const uint8_t ncoords_79[3] = {21, 10, 10};
static const glyph_stroke_t stroke_80_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_80_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_80_2[10] = {{0,21},{12,21},{15,20},{16,19},{17,17},{17,14},{16,12},{15,11},{12,10},{4,10}};
static const glyph_stroke_t stroke_80_3[8] = {{12,21},{14,20},{15,19},{16,17},{16,14},{15,12},{14,11},{12,10}};
static const glyph_stroke_t stroke_80_4[2] = {{0,0},{7,0}};
static const glyph_stroke_t *strokes_80[5] = {stroke_80_0, stroke_80_1, stroke_80_2, stroke_80_3, stroke_80_4};
static const uint8_t ncoords_80[5] = {2, 2, 10, 8, 2};
static const glyph_stroke_t stroke_81_0[21] = {{7,21},{4,20},{2,18},{1,16},{0,12},{0,9},{1,5},{2,3},{4,1},{7,0},{9,0},{12,1},{14,3},{15,5},{16,9},{16,12},{15,16},{14,18},{12,20},{9,21},{7,21}};
static const glyph_stroke_t stroke_81_1[10] = {{7,21},{5,20},{3,18},{2,16},{1,12},{1,9},{2,5},{3,3},{5,1},{7,0}};
static const glyph_stroke_t stroke_81_2[10] = {{9,0},{11,1},{13,3},{14,5},{15,9},{15,12},{14,16},{13,18},{11,20},{9,21}};
static const glyph_stroke_t stroke_81_3[12] = {{4,2},{4,3},{5,5},{7,6},{8,6},{10,5},{11,3},{12,-4},{13,-5},{15,-5},{16,-3},{16,-2}};
static const glyph_stroke_t stroke_81_4[6] = {{11,3},{12,-1},{13,-3},{14,-4},{15,-4},{16,-3}};
static const glyph_stroke_t *strokes_81[5] = {stroke_81_0, stroke_81_1, stroke_81_2, stroke_81_3, stroke_81_4};
static const uint8_t ncoords_81[5] = {21, 10, 10, 12, 6};
static const glyph_stroke_t stroke_82_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_82_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_82_2[10] = {{0,21},{12,21},{15,20},{16,19},{17,17},{17,15},{16,13},{15,12},{12,11},{4,11}};
static const glyph_stroke_t stroke_82_3[8] = {{12,21},{14,20},{15,19},{16,17},{16,15},{15,13},{14,12},{12,11}};
static const glyph_stroke_t stroke_82_4[2] = {{0,0},{7,0}};
static const glyph_stroke_t stroke_82_5[7] = {{9,11},{11,10},{12,9},{15,2},{16,1},{17,1},{18,2}};
static const glyph_stroke_t stroke_82_6[7] = {{11,10},{12,8},{14,1},{15,0},{17,0},{18,2},{18,3}};
static const glyph_stroke_t *strokes_82[7] = {stroke_82_0, stroke_82_1, stroke_82_2, stroke_82_3, stroke_82_4, stroke_82_5, stroke_82_6};
static const uint8_t ncoords_82[7] = {2, 2, 10, 8, 2, 7, 7};
static const glyph_stroke_t stroke_83_0[16] = {{13,18},{14,21},{14,15},{13,18},{11,20},{8,21},{5,21},{2,20},{0,18},{0,16},{1,14},{2,13},{4,12},{10,10},{12,9},{14,7}};
static const glyph_stroke_t stroke_83_1[16] = {{0,16},{2,14},{4,13},{10,11},{12,10},{13,9},{14,7},{14,3},{12,1},{9,0},{6,0},{3,1},{1,3},{0,6},{0,0},{1,3}};
static const glyph_stroke_t *strokes_83[2] = {stroke_83_0, stroke_83_1};
static const uint8_t ncoords_83[2] = {16, 16};
static const glyph_stroke_t stroke_84_0[2] = {{7,21},{7,0}};
static const glyph_stroke_t stroke_84_1[2] = {{8,21},{8,0}};
static const glyph_stroke_t stroke_84_2[6] = {{1,21},{0,15},{0,21},{15,21},{15,15},{14,21}};
static const glyph_stroke_t stroke_84_3[2] = {{4,0},{11,0}};
static const glyph_stroke_t *strokes_84[4] = {stroke_84_0, stroke_84_1, stroke_84_2, stroke_84_3};
static const uint8_t ncoords_84[4] = {2, 2, 6, 2};
static const glyph_stroke_t stroke_85_0[10] = {{3,21},{3,6},{4,3},{6,1},{9,0},{11,0},{14,1},{16,3},{17,6},{17,21}};
static const glyph_stroke_t stroke_85_1[5] = {{4,21},{4,6},{5,3},{7,1},{9,0}};
static const glyph_stroke_t stroke_85_2[2] = {{0,21},{7,21}};
static const glyph_stroke_t stroke_85_3[2] = {{14,21},{20,21}};
static const glyph_stroke_t *strokes_85[4] = {stroke_85_0, stroke_85_1, stroke_85_2, stroke_85_3};
static const uint8_t ncoords_85[4] = {10, 5, 2, 2};
static const glyph_stroke_t stroke_86_0[2] = {{2,21},{9,0}};
static const glyph_stroke_t stroke_86_1[2] = {{3,21},{9,3}};
static const glyph_stroke_t stroke_86_2[2] = {{16,21},{9,0}};
static const glyph_stroke_t stroke_86_3[2] = {{0,21},{6,21}};
static const glyph_stroke_t stroke_86_4[2] = {{12,21},{18,21}};
static const glyph_stroke_t *strokes_86[5] = {stroke_86_0, stroke_86_1, stroke_86_2, stroke_86_3, stroke_86_4};
static const uint8_t ncoords_86[5] = {2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_87_0[2] = {{3,21},{7,0}};
static const glyph_stroke_t stroke_87_1[2] = {{4,21},{7,5}};
static const glyph_stroke_t stroke_87_2[2] = {{11,21},{7,0}};
static const glyph_stroke_t stroke_87_3[2] = {{11,21},{15,0}};
static const glyph_stroke_t stroke_87_4[2] = {{12,21},{15,5}};
static const glyph_stroke_t stroke_87_5[2] = {{19,21},{15,0}};
static const glyph_stroke_t stroke_87_6[2] = {{0,21},{7,21}};
static const glyph_stroke_t stroke_87_7[2] = {{16,21},{22,21}};
static const glyph_stroke_t *strokes_87[8] = {stroke_87_0, stroke_87_1, stroke_87_2, stroke_87_3, stroke_87_4, stroke_87_5, stroke_87_6, stroke_87_7};
static const uint8_t ncoords_87[8] = {2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_88_0[2] = {{2,21},{15,0}};
static const glyph_stroke_t stroke_88_1[2] = {{3,21},{16,0}};
static const glyph_stroke_t stroke_88_2[2] = {{16,21},{2,0}};
static const glyph_stroke_t stroke_88_3[2] = {{0,21},{6,21}};
static const glyph_stroke_t stroke_88_4[2] = {{12,21},{18,21}};
static const glyph_stroke_t stroke_88_5[2] = {{0,0},{6,0}};
static const glyph_stroke_t stroke_88_6[2] = {{12,0},{18,0}};
static const glyph_stroke_t *strokes_88[7] = {stroke_88_0, stroke_88_1, stroke_88_2, stroke_88_3, stroke_88_4, stroke_88_5, stroke_88_6};
static const uint8_t ncoords_88[7] = {2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_89_0[3] = {{2,21},{9,10},{9,0}};
static const glyph_stroke_t stroke_89_1[3] = {{3,21},{10,10},{10,0}};
static const glyph_stroke_t stroke_89_2[2] = {{17,21},{10,10}};
static const glyph_stroke_t stroke_89_3[2] = {{0,21},{6,21}};
static const glyph_stroke_t stroke_89_4[2] = {{13,21},{19,21}};
static const glyph_stroke_t stroke_89_5[2] = {{6,0},{13,0}};
static const glyph_stroke_t *strokes_89[6] = {stroke_89_0, stroke_89_1, stroke_89_2, stroke_89_3, stroke_89_4, stroke_89_5};
static const uint8_t ncoords_89[6] = {3, 3, 2, 2, 2, 2};
static const glyph_stroke_t stroke_90_0[2] = {{13,21},{0,0}};
static const glyph_stroke_t stroke_90_1[2] = {{14,21},{1,0}};
static const glyph_stroke_t stroke_90_2[4] = {{1,21},{0,15},{0,21},{14,21}};
static const glyph_stroke_t stroke_90_3[4] = {{0,0},{14,0},{14,6},{13,0}};
static const glyph_stroke_t *strokes_90[4] = {stroke_90_0, stroke_90_1, stroke_90_2, stroke_90_3};
static const uint8_t ncoords_90[4] = {2, 2, 4, 4};
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
static const glyph_stroke_t stroke_97_0[13] = {{2,12},{2,11},{1,11},{1,12},{2,13},{4,14},{8,14},{10,13},{11,12},{12,10},{12,3},{13,1},{14,0}};
static const glyph_stroke_t stroke_97_1[5] = {{11,12},{11,3},{12,1},{14,0},{15,0}};
static const glyph_stroke_t stroke_97_2[11] = {{11,10},{10,9},{4,8},{1,7},{0,5},{0,3},{1,1},{4,0},{7,0},{9,1},{11,3}};
static const glyph_stroke_t stroke_97_3[6] = {{4,8},{2,7},{1,5},{1,3},{2,1},{4,0}};
static const glyph_stroke_t *strokes_97[4] = {stroke_97_0, stroke_97_1, stroke_97_2, stroke_97_3};
static const uint8_t ncoords_97[4] = {13, 5, 11, 6};
static const glyph_stroke_t stroke_98_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_98_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_98_2[14] = {{4,11},{6,13},{8,14},{10,14},{13,13},{15,11},{16,8},{16,6},{15,3},{13,1},{10,0},{8,0},{6,1},{4,3}};
static const glyph_stroke_t stroke_98_3[8] = {{10,14},{12,13},{14,11},{15,8},{15,6},{14,3},{12,1},{10,0}};
static const glyph_stroke_t stroke_98_4[2] = {{0,21},{4,21}};
static const glyph_stroke_t *strokes_98[5] = {stroke_98_0, stroke_98_1, stroke_98_2, stroke_98_3, stroke_98_4};
static const uint8_t ncoords_98[5] = {2, 2, 14, 8, 2};
static const glyph_stroke_t stroke_99_0[18] = {{12,11},{11,10},{12,9},{13,10},{13,11},{11,13},{9,14},{6,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{6,0},{8,0},{11,1},{13,3}};
static const glyph_stroke_t stroke_99_1[8] = {{6,14},{4,13},{2,11},{1,8},{1,6},{2,3},{4,1},{6,0}};
static const glyph_stroke_t *strokes_99[2] = {stroke_99_0, stroke_99_1};
static const uint8_t ncoords_99[2] = {18, 8};
static const glyph_stroke_t stroke_100_0[2] = {{12,21},{12,0}};
static const glyph_stroke_t stroke_100_1[2] = {{13,21},{13,0}};
static const glyph_stroke_t stroke_100_2[14] = {{12,11},{10,13},{8,14},{6,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{6,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_100_3[8] = {{6,14},{4,13},{2,11},{1,8},{1,6},{2,3},{4,1},{6,0}};
static const glyph_stroke_t stroke_100_4[2] = {{9,21},{13,21}};
static const glyph_stroke_t stroke_100_5[2] = {{12,0},{16,0}};
static const glyph_stroke_t *strokes_100[6] = {stroke_100_0, stroke_100_1, stroke_100_2, stroke_100_3, stroke_100_4, stroke_100_5};
static const uint8_t ncoords_100[6] = {2, 2, 14, 8, 2, 2};
static const glyph_stroke_t stroke_101_0[17] = {{1,8},{13,8},{13,10},{12,12},{11,13},{9,14},{6,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{6,0},{8,0},{11,1},{13,3}};
static const glyph_stroke_t stroke_101_1[3] = {{12,8},{12,11},{11,13}};
static const glyph_stroke_t stroke_101_2[8] = {{6,14},{4,13},{2,11},{1,8},{1,6},{2,3},{4,1},{6,0}};
static const glyph_stroke_t *strokes_101[3] = {stroke_101_0, stroke_101_1, stroke_101_2};
static const uint8_t ncoords_101[3] = {17, 3, 8};
static const glyph_stroke_t stroke_102_0[10] = {{8,20},{7,19},{8,18},{9,19},{9,20},{8,21},{6,21},{4,20},{3,18},{3,0}};
static const glyph_stroke_t stroke_102_1[4] = {{6,21},{5,20},{4,18},{4,0}};
static const glyph_stroke_t stroke_102_2[2] = {{0,14},{8,14}};
static const glyph_stroke_t stroke_102_3[2] = {{0,0},{7,0}};
static const glyph_stroke_t *strokes_102[4] = {stroke_102_0, stroke_102_1, stroke_102_2, stroke_102_3};
static const uint8_t ncoords_102[4] = {10, 4, 2, 2};
static const glyph_stroke_t stroke_103_0[17] = {{6,14},{4,13},{3,12},{2,10},{2,8},{3,6},{4,5},{6,4},{8,4},{10,5},{11,6},{12,8},{12,10},{11,12},{10,13},{8,14},{6,14}};
static const glyph_stroke_t stroke_103_1[4] = {{4,13},{3,11},{3,7},{4,5}};
static const glyph_stroke_t stroke_103_2[4] = {{10,5},{11,7},{11,11},{10,13}};
static const glyph_stroke_t stroke_103_3[5] = {{11,12},{12,13},{14,14},{14,13},{12,13}};
static const glyph_stroke_t stroke_103_4[9] = {{3,6},{2,5},{1,3},{1,2},{2,0},{5,-1},{10,-1},{13,-2},{14,-3}};
static const glyph_stroke_t stroke_103_5[15] = {{1,2},{2,1},{5,0},{10,0},{13,-1},{14,-3},{14,-4},{13,-6},{10,-7},{4,-7},{1,-6},{0,-4},{0,-3},{1,-1},{4,0}};
static const glyph_stroke_t *strokes_103[6] = {stroke_103_0, stroke_103_1, stroke_103_2, stroke_103_3, stroke_103_4, stroke_103_5};
static const uint8_t ncoords_103[6] = {17, 4, 4, 5, 9, 15};
static const glyph_stroke_t stroke_104_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_104_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_104_2[7] = {{4,11},{6,13},{9,14},{11,14},{14,13},{15,11},{15,0}};
static const glyph_stroke_t stroke_104_3[4] = {{11,14},{13,13},{14,11},{14,0}};
static const glyph_stroke_t stroke_104_4[2] = {{0,21},{4,21}};
static const glyph_stroke_t stroke_104_5[2] = {{0,0},{7,0}};
static const glyph_stroke_t stroke_104_6[2] = {{11,0},{18,0}};
static const glyph_stroke_t *strokes_104[7] = {stroke_104_0, stroke_104_1, stroke_104_2, stroke_104_3, stroke_104_4, stroke_104_5, stroke_104_6};
static const uint8_t ncoords_104[7] = {2, 2, 7, 4, 2, 2, 2};
static const glyph_stroke_t stroke_105_0[5] = {{3,21},{2,20},{3,19},{4,20},{3,21}};
static const glyph_stroke_t stroke_105_1[2] = {{3,14},{3,0}};
static const glyph_stroke_t stroke_105_2[2] = {{4,14},{4,0}};
static const glyph_stroke_t stroke_105_3[2] = {{0,14},{4,14}};
static const glyph_stroke_t stroke_105_4[2] = {{0,0},{7,0}};
static const glyph_stroke_t *strokes_105[5] = {stroke_105_0, stroke_105_1, stroke_105_2, stroke_105_3, stroke_105_4};
static const uint8_t ncoords_105[5] = {5, 2, 2, 2, 2};
static const glyph_stroke_t stroke_106_0[5] = {{5,21},{4,20},{5,19},{6,20},{5,21}};
static const glyph_stroke_t stroke_106_1[10] = {{6,14},{6,-4},{5,-6},{3,-7},{1,-7},{0,-6},{0,-5},{1,-4},{2,-5},{1,-6}};
static const glyph_stroke_t stroke_106_2[4] = {{5,14},{5,-4},{4,-6},{3,-7}};
static const glyph_stroke_t stroke_106_3[2] = {{2,14},{6,14}};
static const glyph_stroke_t *strokes_106[4] = {stroke_106_0, stroke_106_1, stroke_106_2, stroke_106_3};
static const uint8_t ncoords_106[4] = {5, 10, 4, 2};
static const glyph_stroke_t stroke_107_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_107_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_107_2[2] = {{14,14},{4,4}};
static const glyph_stroke_t stroke_107_3[2] = {{9,8},{15,0}};
static const glyph_stroke_t stroke_107_4[2] = {{8,8},{14,0}};
static const glyph_stroke_t stroke_107_5[2] = {{0,21},{4,21}};
static const glyph_stroke_t stroke_107_6[2] = {{11,14},{17,14}};
static const glyph_stroke_t stroke_107_7[2] = {{0,0},{7,0}};
static const glyph_stroke_t stroke_107_8[2] = {{11,0},{17,0}};
static const glyph_stroke_t *strokes_107[9] = {stroke_107_0, stroke_107_1, stroke_107_2, stroke_107_3, stroke_107_4, stroke_107_5, stroke_107_6, stroke_107_7, stroke_107_8};
static const uint8_t ncoords_107[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_108_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_108_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_108_2[2] = {{0,21},{4,21}};
static const glyph_stroke_t stroke_108_3[2] = {{0,0},{7,0}};
static const glyph_stroke_t *strokes_108[4] = {stroke_108_0, stroke_108_1, stroke_108_2, stroke_108_3};
static const uint8_t ncoords_108[4] = {2, 2, 2, 2};
static const glyph_stroke_t stroke_109_0[2] = {{3,14},{3,0}};
static const glyph_stroke_t stroke_109_1[2] = {{4,14},{4,0}};
static const glyph_stroke_t stroke_109_2[7] = {{4,11},{6,13},{9,14},{11,14},{14,13},{15,11},{15,0}};
static const glyph_stroke_t stroke_109_3[4] = {{11,14},{13,13},{14,11},{14,0}};
static const glyph_stroke_t stroke_109_4[7] = {{15,11},{17,13},{20,14},{22,14},{25,13},{26,11},{26,0}};
static const glyph_stroke_t stroke_109_5[4] = {{22,14},{24,13},{25,11},{25,0}};
static const glyph_stroke_t stroke_109_6[2] = {{0,14},{4,14}};
static const glyph_stroke_t stroke_109_7[2] = {{0,0},{7,0}};
static const glyph_stroke_t stroke_109_8[2] = {{11,0},{18,0}};
static const glyph_stroke_t stroke_109_9[2] = {{22,0},{29,0}};
static const glyph_stroke_t *strokes_109[10] = {stroke_109_0, stroke_109_1, stroke_109_2, stroke_109_3, stroke_109_4, stroke_109_5, stroke_109_6, stroke_109_7, stroke_109_8, stroke_109_9};
static const uint8_t ncoords_109[10] = {2, 2, 7, 4, 7, 4, 2, 2, 2, 2};
static const glyph_stroke_t stroke_110_0[2] = {{3,14},{3,0}};
static const glyph_stroke_t stroke_110_1[2] = {{4,14},{4,0}};
static const glyph_stroke_t stroke_110_2[7] = {{4,11},{6,13},{9,14},{11,14},{14,13},{15,11},{15,0}};
static const glyph_stroke_t stroke_110_3[4] = {{11,14},{13,13},{14,11},{14,0}};
static const glyph_stroke_t stroke_110_4[2] = {{0,14},{4,14}};
static const glyph_stroke_t stroke_110_5[2] = {{0,0},{7,0}};
static const glyph_stroke_t stroke_110_6[2] = {{11,0},{18,0}};
static const glyph_stroke_t *strokes_110[7] = {stroke_110_0, stroke_110_1, stroke_110_2, stroke_110_3, stroke_110_4, stroke_110_5, stroke_110_6};
static const uint8_t ncoords_110[7] = {2, 2, 7, 4, 2, 2, 2};
static const glyph_stroke_t stroke_111_0[17] = {{6,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{6,0},{8,0},{11,1},{13,3},{14,6},{14,8},{13,11},{11,13},{8,14},{6,14}};
static const glyph_stroke_t stroke_111_1[8] = {{6,14},{4,13},{2,11},{1,8},{1,6},{2,3},{4,1},{6,0}};
static const glyph_stroke_t stroke_111_2[8] = {{8,0},{10,1},{12,3},{13,6},{13,8},{12,11},{10,13},{8,14}};
static const glyph_stroke_t *strokes_111[3] = {stroke_111_0, stroke_111_1, stroke_111_2};
static const uint8_t ncoords_111[3] = {17, 8, 8};
static const glyph_stroke_t stroke_112_0[2] = {{3,14},{3,-7}};
static const glyph_stroke_t stroke_112_1[2] = {{4,14},{4,-7}};
static const glyph_stroke_t stroke_112_2[14] = {{4,11},{6,13},{8,14},{10,14},{13,13},{15,11},{16,8},{16,6},{15,3},{13,1},{10,0},{8,0},{6,1},{4,3}};
static const glyph_stroke_t stroke_112_3[8] = {{10,14},{12,13},{14,11},{15,8},{15,6},{14,3},{12,1},{10,0}};
static const glyph_stroke_t stroke_112_4[2] = {{0,14},{4,14}};
static const glyph_stroke_t stroke_112_5[2] = {{0,-7},{7,-7}};
static const glyph_stroke_t *strokes_112[6] = {stroke_112_0, stroke_112_1, stroke_112_2, stroke_112_3, stroke_112_4, stroke_112_5};
static const uint8_t ncoords_112[6] = {2, 2, 14, 8, 2, 2};
static const glyph_stroke_t stroke_113_0[2] = {{12,14},{12,-7}};
static const glyph_stroke_t stroke_113_1[2] = {{13,14},{13,-7}};
static const glyph_stroke_t stroke_113_2[14] = {{12,11},{10,13},{8,14},{6,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{6,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_113_3[8] = {{6,14},{4,13},{2,11},{1,8},{1,6},{2,3},{4,1},{6,0}};
static const glyph_stroke_t stroke_113_4[2] = {{9,-7},{16,-7}};
static const glyph_stroke_t *strokes_113[5] = {stroke_113_0, stroke_113_1, stroke_113_2, stroke_113_3, stroke_113_4};
static const uint8_t ncoords_113[5] = {2, 2, 14, 8, 2};
static const glyph_stroke_t stroke_114_0[2] = {{3,14},{3,0}};
static const glyph_stroke_t stroke_114_1[2] = {{4,14},{4,0}};
static const glyph_stroke_t stroke_114_2[10] = {{4,8},{5,11},{7,13},{9,14},{12,14},{13,13},{13,12},{12,11},{11,12},{12,13}};
static const glyph_stroke_t stroke_114_3[2] = {{0,14},{4,14}};
static const glyph_stroke_t stroke_114_4[2] = {{0,0},{7,0}};
static const glyph_stroke_t *strokes_114[5] = {stroke_114_0, stroke_114_1, stroke_114_2, stroke_114_3, stroke_114_4};
static const uint8_t ncoords_114[5] = {2, 2, 10, 2, 2};
static const glyph_stroke_t stroke_115_0[15] = {{10,12},{11,14},{11,10},{10,12},{9,13},{7,14},{3,14},{1,13},{0,12},{0,10},{1,9},{3,8},{8,6},{10,5},{11,4}};
static const glyph_stroke_t stroke_115_1[15] = {{0,11},{1,10},{3,9},{8,7},{10,6},{11,5},{11,2},{10,1},{8,0},{4,0},{2,1},{1,2},{0,4},{0,0},{1,2}};
static const glyph_stroke_t *strokes_115[2] = {stroke_115_0, stroke_115_1};
static const uint8_t ncoords_115[2] = {15, 15};
static const glyph_stroke_t stroke_116_0[7] = {{3,21},{3,4},{4,1},{6,0},{8,0},{10,1},{11,3}};
static const glyph_stroke_t stroke_116_1[4] = {{4,21},{4,4},{5,1},{6,0}};
static const glyph_stroke_t stroke_116_2[2] = {{0,14},{8,14}};
static const glyph_stroke_t *strokes_116[3] = {stroke_116_0, stroke_116_1, stroke_116_2};
static const uint8_t ncoords_116[3] = {7, 4, 2};
static const glyph_stroke_t stroke_117_0[7] = {{3,14},{3,3},{4,1},{7,0},{9,0},{12,1},{14,3}};
static const glyph_stroke_t stroke_117_1[4] = {{4,14},{4,3},{5,1},{7,0}};
static const glyph_stroke_t stroke_117_2[2] = {{14,14},{14,0}};
static const glyph_stroke_t stroke_117_3[2] = {{15,14},{15,0}};
static const glyph_stroke_t stroke_117_4[2] = {{0,14},{4,14}};
static const glyph_stroke_t stroke_117_5[2] = {{11,14},{15,14}};
static const glyph_stroke_t stroke_117_6[2] = {{14,0},{18,0}};
static const glyph_stroke_t *strokes_117[7] = {stroke_117_0, stroke_117_1, stroke_117_2, stroke_117_3, stroke_117_4, stroke_117_5, stroke_117_6};
static const uint8_t ncoords_117[7] = {7, 4, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_118_0[2] = {{2,14},{8,0}};
static const glyph_stroke_t stroke_118_1[2] = {{3,14},{8,2}};
static const glyph_stroke_t stroke_118_2[2] = {{14,14},{8,0}};
static const glyph_stroke_t stroke_118_3[2] = {{0,14},{6,14}};
static const glyph_stroke_t stroke_118_4[2] = {{10,14},{16,14}};
static const glyph_stroke_t *strokes_118[5] = {stroke_118_0, stroke_118_1, stroke_118_2, stroke_118_3, stroke_118_4};
static const uint8_t ncoords_118[5] = {2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_119_0[2] = {{3,14},{7,0}};
static const glyph_stroke_t stroke_119_1[2] = {{4,14},{7,3}};
static const glyph_stroke_t stroke_119_2[2] = {{11,14},{7,0}};
static const glyph_stroke_t stroke_119_3[2] = {{11,14},{15,0}};
static const glyph_stroke_t stroke_119_4[2] = {{12,14},{15,3}};
static const glyph_stroke_t stroke_119_5[2] = {{19,14},{15,0}};
static const glyph_stroke_t stroke_119_6[2] = {{0,14},{7,14}};
static const glyph_stroke_t stroke_119_7[2] = {{16,14},{22,14}};
static const glyph_stroke_t *strokes_119[8] = {stroke_119_0, stroke_119_1, stroke_119_2, stroke_119_3, stroke_119_4, stroke_119_5, stroke_119_6, stroke_119_7};
static const uint8_t ncoords_119[8] = {2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_120_0[2] = {{2,14},{13,0}};
static const glyph_stroke_t stroke_120_1[2] = {{3,14},{14,0}};
static const glyph_stroke_t stroke_120_2[2] = {{14,14},{2,0}};
static const glyph_stroke_t stroke_120_3[2] = {{0,14},{6,14}};
static const glyph_stroke_t stroke_120_4[2] = {{10,14},{16,14}};
static const glyph_stroke_t stroke_120_5[2] = {{0,0},{6,0}};
static const glyph_stroke_t stroke_120_6[2] = {{10,0},{16,0}};
static const glyph_stroke_t *strokes_120[7] = {stroke_120_0, stroke_120_1, stroke_120_2, stroke_120_3, stroke_120_4, stroke_120_5, stroke_120_6};
static const uint8_t ncoords_120[7] = {2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_121_0[2] = {{2,14},{8,0}};
static const glyph_stroke_t stroke_121_1[2] = {{3,14},{8,2}};
static const glyph_stroke_t stroke_121_2[9] = {{14,14},{8,0},{6,-4},{4,-6},{2,-7},{1,-7},{0,-6},{1,-5},{2,-6}};
static const glyph_stroke_t stroke_121_3[2] = {{0,14},{6,14}};
static const glyph_stroke_t stroke_121_4[2] = {{10,14},{16,14}};
static const glyph_stroke_t *strokes_121[5] = {stroke_121_0, stroke_121_1, stroke_121_2, stroke_121_3, stroke_121_4};
static const uint8_t ncoords_121[5] = {2, 2, 9, 2, 2};
static const glyph_stroke_t stroke_122_0[2] = {{11,14},{0,0}};
static const glyph_stroke_t stroke_122_1[2] = {{12,14},{1,0}};
static const glyph_stroke_t stroke_122_2[4] = {{1,14},{0,10},{0,14},{12,14}};
static const glyph_stroke_t stroke_122_3[4] = {{0,0},{12,0},{12,4},{11,0}};
static const glyph_stroke_t *strokes_122[4] = {stroke_122_0, stroke_122_1, stroke_122_2, stroke_122_3};
static const uint8_t ncoords_122[4] = {2, 2, 4, 4};
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
static const glyph_stroke_t stroke_913_0[2] = {{9,21},{2,0}};
static const glyph_stroke_t stroke_913_1[2] = {{9,21},{16,0}};
static const glyph_stroke_t stroke_913_2[2] = {{9,18},{15,0}};
static const glyph_stroke_t stroke_913_3[2] = {{4,6},{13,6}};
static const glyph_stroke_t stroke_913_4[2] = {{0,0},{6,0}};
static const glyph_stroke_t stroke_913_5[2] = {{12,0},{18,0}};
static const glyph_stroke_t *strokes_913[6] = {stroke_913_0, stroke_913_1, stroke_913_2, stroke_913_3, stroke_913_4, stroke_913_5};
static const uint8_t ncoords_913[6] = {2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_914_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_914_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_914_2[9] = {{0,21},{12,21},{15,20},{16,19},{17,17},{17,15},{16,13},{15,12},{12,11}};
static const glyph_stroke_t stroke_914_3[8] = {{12,21},{14,20},{15,19},{16,17},{16,15},{15,13},{14,12},{12,11}};
static const glyph_stroke_t stroke_914_4[10] = {{4,11},{12,11},{15,10},{16,9},{17,7},{17,4},{16,2},{15,1},{12,0},{0,0}};
static const glyph_stroke_t stroke_914_5[8] = {{12,11},{14,10},{15,9},{16,7},{16,4},{15,2},{14,1},{12,0}};
static const glyph_stroke_t *strokes_914[6] = {stroke_914_0, stroke_914_1, stroke_914_2, stroke_914_3, stroke_914_4, stroke_914_5};
static const uint8_t ncoords_914[6] = {2, 2, 9, 8, 10, 8};
static const glyph_stroke_t stroke_915_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_915_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_915_2[4] = {{0,21},{15,21},{15,15},{14,21}};
static const glyph_stroke_t stroke_915_3[2] = {{0,0},{7,0}};
static const glyph_stroke_t *strokes_915[4] = {stroke_915_0, stroke_915_1, stroke_915_2, stroke_915_3};
static const uint8_t ncoords_915[4] = {2, 2, 4, 2};
static const glyph_stroke_t stroke_916_0[2] = {{8,21},{0,0}};
static const glyph_stroke_t stroke_916_1[2] = {{8,21},{16,0}};
static const glyph_stroke_t stroke_916_2[2] = {{8,18},{15,0}};
static const glyph_stroke_t stroke_916_3[2] = {{1,1},{15,1}};
static const glyph_stroke_t stroke_916_4[2] = {{0,0},{16,0}};
static const glyph_stroke_t *strokes_916[5] = {stroke_916_0, stroke_916_1, stroke_916_2, stroke_916_3, stroke_916_4};
static const uint8_t ncoords_916[5] = {2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_917_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_917_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_917_2[2] = {{10,15},{10,7}};
static const glyph_stroke_t stroke_917_3[4] = {{0,21},{16,21},{16,15},{15,21}};
static const glyph_stroke_t stroke_917_4[2] = {{4,11},{10,11}};
static const glyph_stroke_t stroke_917_5[4] = {{0,0},{16,0},{16,6},{15,0}};
static const glyph_stroke_t *strokes_917[6] = {stroke_917_0, stroke_917_1, stroke_917_2, stroke_917_3, stroke_917_4, stroke_917_5};
static const uint8_t ncoords_917[6] = {2, 2, 2, 4, 2, 4};
static const glyph_stroke_t stroke_918_0[2] = {{13,21},{0,0}};
static const glyph_stroke_t stroke_918_1[2] = {{14,21},{1,0}};
static const glyph_stroke_t stroke_918_2[4] = {{1,21},{0,15},{0,21},{14,21}};
static const glyph_stroke_t stroke_918_3[4] = {{0,0},{14,0},{14,6},{13,0}};
static const glyph_stroke_t *strokes_918[4] = {stroke_918_0, stroke_918_1, stroke_918_2, stroke_918_3};
static const uint8_t ncoords_918[4] = {2, 2, 4, 4};
static const glyph_stroke_t stroke_919_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_919_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_919_2[2] = {{16,21},{16,0}};
static const glyph_stroke_t stroke_919_3[2] = {{17,21},{17,0}};
static const glyph_stroke_t stroke_919_4[2] = {{0,21},{7,21}};
static const glyph_stroke_t stroke_919_5[2] = {{13,21},{20,21}};
static const glyph_stroke_t stroke_919_6[2] = {{4,11},{16,11}};
static const glyph_stroke_t stroke_919_7[2] = {{0,0},{7,0}};
static const glyph_stroke_t stroke_919_8[2] = {{13,0},{20,0}};
static const glyph_stroke_t *strokes_919[9] = {stroke_919_0, stroke_919_1, stroke_919_2, stroke_919_3, stroke_919_4, stroke_919_5, stroke_919_6, stroke_919_7, stroke_919_8};
static const uint8_t ncoords_919[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_920_0[21] = {{7,21},{4,20},{2,18},{1,16},{0,12},{0,9},{1,5},{2,3},{4,1},{7,0},{9,0},{12,1},{14,3},{15,5},{16,9},{16,12},{15,16},{14,18},{12,20},{9,21},{7,21}};
static const glyph_stroke_t stroke_920_1[10] = {{7,21},{5,20},{3,18},{2,16},{1,12},{1,9},{2,5},{3,3},{5,1},{7,0}};
static const glyph_stroke_t stroke_920_2[10] = {{9,0},{11,1},{13,3},{14,5},{15,9},{15,12},{14,16},{13,18},{11,20},{9,21}};
static const glyph_stroke_t stroke_920_3[2] = {{5,14},{5,7}};
static const glyph_stroke_t stroke_920_4[2] = {{11,14},{11,7}};
static const glyph_stroke_t stroke_920_5[2] = {{5,11},{11,11}};
static const glyph_stroke_t stroke_920_6[2] = {{5,10},{11,10}};
static const glyph_stroke_t *strokes_920[7] = {stroke_920_0, stroke_920_1, stroke_920_2, stroke_920_3, stroke_920_4, stroke_920_5, stroke_920_6};
static const uint8_t ncoords_920[7] = {21, 10, 10, 2, 2, 2, 2};
static const glyph_stroke_t stroke_921_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_921_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_921_2[2] = {{0,21},{7,21}};
static const glyph_stroke_t stroke_921_3[2] = {{0,0},{7,0}};
static const glyph_stroke_t *strokes_921[4] = {stroke_921_0, stroke_921_1, stroke_921_2, stroke_921_3};
static const uint8_t ncoords_921[4] = {2, 2, 2, 2};
static const glyph_stroke_t stroke_922_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_922_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_922_2[2] = {{17,21},{4,8}};
static const glyph_stroke_t stroke_922_3[2] = {{9,12},{17,0}};
static const glyph_stroke_t stroke_922_4[2] = {{8,12},{16,0}};
static const glyph_stroke_t stroke_922_5[2] = {{0,21},{7,21}};
static const glyph_stroke_t stroke_922_6[2] = {{13,21},{19,21}};
static const glyph_stroke_t stroke_922_7[2] = {{0,0},{7,0}};
static const glyph_stroke_t stroke_922_8[2] = {{13,0},{19,0}};
static const glyph_stroke_t *strokes_922[9] = {stroke_922_0, stroke_922_1, stroke_922_2, stroke_922_3, stroke_922_4, stroke_922_5, stroke_922_6, stroke_922_7, stroke_922_8};
static const uint8_t ncoords_922[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_923_0[2] = {{9,21},{2,0}};
static const glyph_stroke_t stroke_923_1[2] = {{9,21},{16,0}};
static const glyph_stroke_t stroke_923_2[2] = {{9,18},{15,0}};
static const glyph_stroke_t stroke_923_3[2] = {{0,0},{6,0}};
static const glyph_stroke_t stroke_923_4[2] = {{12,0},{18,0}};
static const glyph_stroke_t *strokes_923[5] = {stroke_923_0, stroke_923_1, stroke_923_2, stroke_923_3, stroke_923_4};
static const uint8_t ncoords_923[5] = {2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_924_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_924_1[2] = {{4,21},{10,3}};
static const glyph_stroke_t stroke_924_2[2] = {{3,21},{10,0}};
static const glyph_stroke_t stroke_924_3[2] = {{17,21},{10,0}};
static const glyph_stroke_t stroke_924_4[2] = {{17,21},{17,0}};
static const glyph_stroke_t stroke_924_5[2] = {{18,21},{18,0}};
static const glyph_stroke_t stroke_924_6[2] = {{0,21},{4,21}};
static const glyph_stroke_t stroke_924_7[2] = {{17,21},{21,21}};
static const glyph_stroke_t stroke_924_8[2] = {{0,0},{6,0}};
static const glyph_stroke_t stroke_924_9[2] = {{14,0},{21,0}};
static const glyph_stroke_t *strokes_924[10] = {stroke_924_0, stroke_924_1, stroke_924_2, stroke_924_3, stroke_924_4, stroke_924_5, stroke_924_6, stroke_924_7, stroke_924_8, stroke_924_9};
static const uint8_t ncoords_924[10] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_925_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_925_1[2] = {{4,21},{16,2}};
static const glyph_stroke_t stroke_925_2[2] = {{4,19},{16,0}};
static const glyph_stroke_t stroke_925_3[2] = {{16,21},{16,0}};
static const glyph_stroke_t stroke_925_4[2] = {{0,21},{4,21}};
static const glyph_stroke_t stroke_925_5[2] = {{13,21},{19,21}};
static const glyph_stroke_t stroke_925_6[2] = {{0,0},{6,0}};
static const glyph_stroke_t *strokes_925[7] = {stroke_925_0, stroke_925_1, stroke_925_2, stroke_925_3, stroke_925_4, stroke_925_5, stroke_925_6};
static const uint8_t ncoords_925[7] = {2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_926_0[2] = {{1,22},{0,17}};
static const glyph_stroke_t stroke_926_1[2] = {{16,22},{15,17}};
static const glyph_stroke_t stroke_926_2[2] = {{5,13},{4,8}};
static const glyph_stroke_t stroke_926_3[2] = {{12,13},{11,8}};
static const glyph_stroke_t stroke_926_4[2] = {{1,4},{0,-1}};
static const glyph_stroke_t stroke_926_5[2] = {{16,4},{15,-1}};
static const glyph_stroke_t stroke_926_6[2] = {{1,20},{15,20}};
static const glyph_stroke_t stroke_926_7[2] = {{1,19},{15,19}};
static const glyph_stroke_t stroke_926_8[2] = {{5,11},{11,11}};
static const glyph_stroke_t stroke_926_9[2] = {{5,10},{11,10}};
static const glyph_stroke_t stroke_926_10[2] = {{1,2},{15,2}};
static const glyph_stroke_t stroke_926_11[2] = {{1,1},{15,1}};
static const glyph_stroke_t *strokes_926[12] = {stroke_926_0, stroke_926_1, stroke_926_2, stroke_926_3, stroke_926_4, stroke_926_5, stroke_926_6, stroke_926_7, stroke_926_8, stroke_926_9, stroke_926_10, stroke_926_11};
static const uint8_t ncoords_926[12] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_927_0[21] = {{7,21},{4,20},{2,18},{1,16},{0,12},{0,9},{1,5},{2,3},{4,1},{7,0},{9,0},{12,1},{14,3},{15,5},{16,9},{16,12},{15,16},{14,18},{12,20},{9,21},{7,21}};
static const glyph_stroke_t stroke_927_1[10] = {{7,21},{5,20},{3,18},{2,16},{1,12},{1,9},{2,5},{3,3},{5,1},{7,0}};
static const glyph_stroke_t stroke_927_2[10] = {{9,0},{11,1},{13,3},{14,5},{15,9},{15,12},{14,16},{13,18},{11,20},{9,21}};
static const glyph_stroke_t *strokes_927[3] = {stroke_927_0, stroke_927_1, stroke_927_2};
static const uint8_t ncoords_927[3] = {21, 10, 10};
static const glyph_stroke_t stroke_928_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_928_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_928_2[2] = {{16,21},{16,0}};
static const glyph_stroke_t stroke_928_3[2] = {{17,21},{17,0}};
static const glyph_stroke_t stroke_928_4[2] = {{0,21},{20,21}};
static const glyph_stroke_t stroke_928_5[2] = {{0,0},{7,0}};
static const glyph_stroke_t stroke_928_6[2] = {{13,0},{20,0}};
static const glyph_stroke_t *strokes_928[7] = {stroke_928_0, stroke_928_1, stroke_928_2, stroke_928_3, stroke_928_4, stroke_928_5, stroke_928_6};
static const uint8_t ncoords_928[7] = {2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_929_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_929_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_929_2[10] = {{0,21},{12,21},{15,20},{16,19},{17,17},{17,14},{16,12},{15,11},{12,10},{4,10}};
static const glyph_stroke_t stroke_929_3[8] = {{12,21},{14,20},{15,19},{16,17},{16,14},{15,12},{14,11},{12,10}};
static const glyph_stroke_t stroke_929_4[2] = {{0,0},{7,0}};
static const glyph_stroke_t *strokes_929[5] = {stroke_929_0, stroke_929_1, stroke_929_2, stroke_929_3, stroke_929_4};
static const uint8_t ncoords_929[5] = {2, 2, 10, 8, 2};
static const glyph_stroke_t stroke_931_0[3] = {{1,21},{8,11},{0,0}};
static const glyph_stroke_t stroke_931_1[2] = {{0,21},{7,11}};
static const glyph_stroke_t stroke_931_2[4] = {{0,21},{15,21},{16,15},{14,21}};
static const glyph_stroke_t stroke_931_3[2] = {{1,1},{14,1}};
static const glyph_stroke_t stroke_931_4[4] = {{0,0},{15,0},{16,6},{14,0}};
static const glyph_stroke_t *strokes_931[5] = {stroke_931_0, stroke_931_1, stroke_931_2, stroke_931_3, stroke_931_4};
static const uint8_t ncoords_931[5] = {3, 2, 4, 2, 4};
static const glyph_stroke_t stroke_932_0[2] = {{7,21},{7,0}};
static const glyph_stroke_t stroke_932_1[2] = {{8,21},{8,0}};
static const glyph_stroke_t stroke_932_2[6] = {{1,21},{0,15},{0,21},{15,21},{15,15},{14,21}};
static const glyph_stroke_t stroke_932_3[2] = {{4,0},{11,0}};
static const glyph_stroke_t *strokes_932[4] = {stroke_932_0, stroke_932_1, stroke_932_2, stroke_932_3};
static const uint8_t ncoords_932[4] = {2, 2, 6, 2};
static const glyph_stroke_t stroke_933_0[9] = {{0,16},{0,18},{1,20},{2,21},{4,21},{5,20},{6,18},{7,14},{7,0}};
static const glyph_stroke_t stroke_933_1[4] = {{0,18},{2,20},{4,20},{6,18}};
static const glyph_stroke_t stroke_933_2[9] = {{15,16},{15,18},{14,20},{13,21},{11,21},{10,20},{9,18},{8,14},{8,0}};
static const glyph_stroke_t stroke_933_3[4] = {{15,18},{13,20},{11,20},{9,18}};
static const glyph_stroke_t stroke_933_4[2] = {{4,0},{11,0}};
static const glyph_stroke_t *strokes_933[5] = {stroke_933_0, stroke_933_1, stroke_933_2, stroke_933_3, stroke_933_4};
static const uint8_t ncoords_933[5] = {9, 4, 9, 4, 2};
static const glyph_stroke_t stroke_934_0[2] = {{7,21},{7,0}};
static const glyph_stroke_t stroke_934_1[2] = {{8,21},{8,0}};
static const glyph_stroke_t stroke_934_2[17] = {{5,16},{2,15},{1,14},{0,12},{0,9},{1,7},{2,6},{5,5},{10,5},{13,6},{14,7},{15,9},{15,12},{14,14},{13,15},{10,16},{5,16}};
static const glyph_stroke_t stroke_934_3[8] = {{5,16},{3,15},{2,14},{1,12},{1,9},{2,7},{3,6},{5,5}};
static const glyph_stroke_t stroke_934_4[8] = {{10,5},{12,6},{13,7},{14,9},{14,12},{13,14},{12,15},{10,16}};
static const glyph_stroke_t stroke_934_5[2] = {{4,21},{11,21}};
static const glyph_stroke_t stroke_934_6[2] = {{4,0},{11,0}};
static const glyph_stroke_t *strokes_934[7] = {stroke_934_0, stroke_934_1, stroke_934_2, stroke_934_3, stroke_934_4, stroke_934_5, stroke_934_6};
static const uint8_t ncoords_934[7] = {2, 2, 17, 8, 8, 2, 2};
static const glyph_stroke_t stroke_935_0[2] = {{2,21},{15,0}};
static const glyph_stroke_t stroke_935_1[2] = {{3,21},{16,0}};
static const glyph_stroke_t stroke_935_2[2] = {{16,21},{2,0}};
static const glyph_stroke_t stroke_935_3[2] = {{0,21},{6,21}};
static const glyph_stroke_t stroke_935_4[2] = {{12,21},{18,21}};
static const glyph_stroke_t stroke_935_5[2] = {{0,0},{6,0}};
static const glyph_stroke_t stroke_935_6[2] = {{12,0},{18,0}};
static const glyph_stroke_t *strokes_935[7] = {stroke_935_0, stroke_935_1, stroke_935_2, stroke_935_3, stroke_935_4, stroke_935_5, stroke_935_6};
static const uint8_t ncoords_935[7] = {2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_936_0[2] = {{9,21},{9,0}};
static const glyph_stroke_t stroke_936_1[2] = {{10,21},{10,0}};
static const glyph_stroke_t stroke_936_2[7] = {{0,14},{1,15},{3,14},{4,10},{5,8},{6,7},{8,6}};
static const glyph_stroke_t stroke_936_3[12] = {{1,15},{2,14},{3,10},{4,8},{5,7},{8,6},{11,6},{14,7},{15,8},{16,10},{17,14},{18,15}};
static const glyph_stroke_t stroke_936_4[7] = {{11,6},{13,7},{14,8},{15,10},{16,14},{18,15},{19,14}};
static const glyph_stroke_t stroke_936_5[2] = {{6,21},{13,21}};
static const glyph_stroke_t stroke_936_6[2] = {{6,0},{13,0}};
static const glyph_stroke_t *strokes_936[7] = {stroke_936_0, stroke_936_1, stroke_936_2, stroke_936_3, stroke_936_4, stroke_936_5, stroke_936_6};
static const uint8_t ncoords_936[7] = {2, 2, 7, 12, 7, 2, 2};
static const glyph_stroke_t stroke_937_0[20] = {{0,3},{1,0},{5,0},{3,4},{1,8},{0,11},{0,15},{1,18},{3,20},{6,21},{10,21},{13,20},{15,18},{16,15},{16,11},{15,8},{13,4},{11,0},{15,0},{16,3}};
static const glyph_stroke_t stroke_937_1[7] = {{3,4},{2,7},{1,11},{1,15},{2,18},{4,20},{6,21}};
static const glyph_stroke_t stroke_937_2[7] = {{10,21},{12,20},{14,18},{15,15},{15,11},{14,7},{13,4}};
static const glyph_stroke_t stroke_937_3[2] = {{1,1},{4,1}};
static const glyph_stroke_t stroke_937_4[2] = {{12,1},{15,1}};
static const glyph_stroke_t *strokes_937[5] = {stroke_937_0, stroke_937_1, stroke_937_2, stroke_937_3, stroke_937_4};
static const uint8_t ncoords_937[5] = {20, 7, 7, 2, 2};
static const glyph_stroke_t stroke_945_0[14] = {{7,14},{4,13},{2,11},{1,9},{0,6},{0,3},{1,1},{4,0},{6,0},{8,1},{11,4},{13,7},{15,11},{16,14}};
static const glyph_stroke_t stroke_945_1[8] = {{7,14},{5,13},{3,11},{2,9},{1,6},{1,3},{2,1},{4,0}};
static const glyph_stroke_t stroke_945_2[7] = {{7,14},{9,14},{11,13},{12,11},{14,3},{15,1},{16,0}};
static const glyph_stroke_t stroke_945_3[7] = {{9,14},{10,13},{11,11},{13,3},{14,1},{16,0},{17,0}};
static const glyph_stroke_t *strokes_945[4] = {stroke_945_0, stroke_945_1, stroke_945_2, stroke_945_3};
static const uint8_t ncoords_945[4] = {14, 8, 7, 7};
static const glyph_stroke_t stroke_946_0[8] = {{11,21},{8,20},{6,18},{4,14},{3,11},{2,7},{1,1},{0,-7}};
static const glyph_stroke_t stroke_946_1[8] = {{11,21},{9,20},{7,18},{5,14},{4,11},{3,7},{2,1},{1,-7}};
static const glyph_stroke_t stroke_946_2[9] = {{11,21},{13,21},{15,20},{16,19},{16,16},{15,14},{14,13},{11,12},{7,12}};
static const glyph_stroke_t stroke_946_3[6] = {{13,21},{15,19},{15,16},{14,14},{13,13},{11,12}};
static const glyph_stroke_t stroke_946_4[12] = {{7,12},{11,11},{13,9},{14,7},{14,4},{13,2},{12,1},{9,0},{7,0},{5,1},{4,2},{3,5}};
static const glyph_stroke_t stroke_946_5[8] = {{7,12},{10,11},{12,9},{13,7},{13,4},{12,2},{11,1},{9,0}};
static const glyph_stroke_t *strokes_946[6] = {stroke_946_0, stroke_946_1, stroke_946_2, stroke_946_3, stroke_946_4, stroke_946_5};
static const uint8_t ncoords_946[6] = {8, 8, 9, 6, 12, 8};
static const glyph_stroke_t stroke_947_0[10] = {{0,11},{2,13},{4,14},{6,14},{8,13},{9,12},{10,9},{10,5},{9,1},{6,-7}};
static const glyph_stroke_t stroke_947_1[4] = {{1,12},{3,13},{7,13},{9,12}};
static const glyph_stroke_t stroke_947_2[6] = {{17,14},{16,11},{15,9},{10,2},{7,-3},{5,-7}};
static const glyph_stroke_t stroke_947_3[4] = {{16,14},{15,11},{14,9},{10,2}};
static const glyph_stroke_t *strokes_947[4] = {stroke_947_0, stroke_947_1, stroke_947_2, stroke_947_3};
static const uint8_t ncoords_947[4] = {10, 4, 6, 4};
static const glyph_stroke_t stroke_948_0[23] = {{10,13},{8,14},{6,14},{3,13},{1,10},{0,7},{0,4},{1,2},{2,1},{4,0},{6,0},{9,1},{11,4},{12,7},{12,10},{11,12},{7,17},{6,19},{6,21},{7,22},{9,22},{11,21},{13,19}};
static const glyph_stroke_t stroke_948_1[6] = {{6,14},{4,13},{2,10},{1,7},{1,3},{2,1}};
static const glyph_stroke_t stroke_948_2[12] = {{6,0},{8,1},{10,4},{11,7},{11,11},{10,13},{8,16},{7,18},{7,20},{8,21},{10,21},{13,19}};
static const glyph_stroke_t *strokes_948[3] = {stroke_948_0, stroke_948_1, stroke_948_2};
static const uint8_t ncoords_948[3] = {23, 6, 12};
static const glyph_stroke_t stroke_949_0[8] = {{12,11},{10,13},{8,14},{4,14},{2,13},{2,11},{4,9},{7,8}};
static const glyph_stroke_t stroke_949_1[5] = {{4,14},{3,13},{3,11},{5,9},{7,8}};
static const glyph_stroke_t stroke_949_2[9] = {{7,8},{2,7},{0,5},{0,3},{1,1},{4,0},{7,0},{9,1},{11,3}};
static const glyph_stroke_t stroke_949_3[6] = {{7,8},{3,7},{1,5},{1,3},{2,1},{4,0}};
static const glyph_stroke_t *strokes_949[4] = {stroke_949_0, stroke_949_1, stroke_949_2, stroke_949_3};
static const uint8_t ncoords_949[4] = {8, 5, 9, 6};
static const glyph_stroke_t stroke_950_0[22] = {{8,21},{6,20},{5,19},{5,18},{6,17},{9,16},{14,16},{14,17},{11,16},{7,14},{4,12},{1,9},{0,6},{0,4},{1,2},{4,0},{7,-2},{8,-4},{8,-6},{7,-7},{5,-7},{4,-6}};
static const glyph_stroke_t stroke_950_1[7] = {{9,15},{5,12},{2,9},{1,6},{1,4},{2,2},{4,0}};
static const glyph_stroke_t *strokes_950[2] = {stroke_950_0, stroke_950_1};
static const uint8_t ncoords_950[2] = {22, 7};
static const glyph_stroke_t stroke_951_0[8] = {{0,10},{1,12},{3,14},{6,14},{7,13},{7,11},{6,7},{4,0}};
static const glyph_stroke_t stroke_951_1[5] = {{5,14},{6,13},{6,11},{5,7},{3,0}};
static const glyph_stroke_t stroke_951_2[10] = {{6,7},{8,11},{10,13},{12,14},{14,14},{16,13},{17,12},{17,9},{16,4},{13,-7}};
static const glyph_stroke_t stroke_951_3[5] = {{14,14},{16,12},{16,9},{15,4},{12,-7}};
static const glyph_stroke_t *strokes_951[4] = {stroke_951_0, stroke_951_1, stroke_951_2, stroke_951_3};
static const uint8_t ncoords_951[4] = {8, 5, 10, 5};
static const glyph_stroke_t stroke_952_0[10] = {{0,10},{1,12},{3,14},{6,14},{7,13},{7,11},{6,6},{6,3},{7,1},{8,0}};
static const glyph_stroke_t stroke_952_1[23] = {{5,14},{6,13},{6,11},{5,6},{5,3},{6,1},{8,0},{10,0},{12,1},{14,3},{16,6},{17,9},{18,14},{18,18},{17,20},{15,21},{13,21},{11,19},{11,17},{12,14},{14,11},{16,9},{19,7}};
static const glyph_stroke_t stroke_952_2[8] = {{12,1},{14,4},{15,6},{16,9},{17,14},{17,18},{16,20},{15,21}};
static const glyph_stroke_t *strokes_952[3] = {stroke_952_0, stroke_952_1, stroke_952_2};
static const uint8_t ncoords_952[3] = {10, 23, 8};
static const glyph_stroke_t stroke_953_0[8] = {{3,14},{1,7},{0,3},{0,1},{1,0},{4,0},{6,2},{7,4}};
static const glyph_stroke_t stroke_953_1[5] = {{4,14},{2,7},{1,3},{1,1},{2,0}};
static const glyph_stroke_t *strokes_953[2] = {stroke_953_0, stroke_953_1};
static const uint8_t ncoords_953[2] = {8, 5};
static const glyph_stroke_t stroke_954_0[2] = {{4,14},{0,0}};
static const glyph_stroke_t stroke_954_1[2] = {{5,14},{1,0}};
static const glyph_stroke_t stroke_954_2[9] = {{14,14},{15,13},{16,13},{15,14},{13,14},{11,13},{7,9},{5,8},{3,8}};
static const glyph_stroke_t stroke_954_3[4] = {{5,8},{7,7},{9,1},{10,0}};
static const glyph_stroke_t stroke_954_4[7] = {{5,8},{6,7},{8,1},{9,0},{11,0},{13,1},{15,4}};
static const glyph_stroke_t *strokes_954[5] = {stroke_954_0, stroke_954_1, stroke_954_2, stroke_954_3, stroke_954_4};
static const uint8_t ncoords_954[5] = {2, 2, 9, 4, 7};
static const glyph_stroke_t stroke_955_0[8] = {{1,21},{3,21},{5,20},{6,19},{7,17},{13,3},{14,1},{15,0}};
static const glyph_stroke_t stroke_955_1[7] = {{3,21},{5,19},{6,17},{12,3},{13,1},{15,0},{16,0}};
static const glyph_stroke_t stroke_955_2[2] = {{8,14},{0,0}};
static const glyph_stroke_t stroke_955_3[2] = {{8,14},{1,0}};
static const glyph_stroke_t *strokes_955[4] = {stroke_955_0, stroke_955_1, stroke_955_2, stroke_955_3};
static const uint8_t ncoords_955[4] = {8, 7, 2, 2};
static const glyph_stroke_t stroke_956_0[2] = {{6,14},{0,-7}};
static const glyph_stroke_t stroke_956_1[2] = {{7,14},{1,-7}};
static const glyph_stroke_t stroke_956_2[8] = {{6,11},{5,5},{5,2},{7,0},{9,0},{11,1},{13,3},{15,6}};
static const glyph_stroke_t stroke_956_3[7] = {{17,14},{14,3},{14,1},{15,0},{18,0},{20,2},{21,4}};
static const glyph_stroke_t stroke_956_4[4] = {{18,14},{15,3},{15,1},{16,0}};
static const glyph_stroke_t *strokes_956[5] = {stroke_956_0, stroke_956_1, stroke_956_2, stroke_956_3, stroke_956_4};
static const uint8_t ncoords_956[5] = {2, 2, 8, 7, 4};
static const glyph_stroke_t stroke_957_0[2] = {{3,14},{1,0}};
static const glyph_stroke_t stroke_957_1[4] = {{4,14},{3,8},{2,3},{1,0}};
static const glyph_stroke_t stroke_957_2[3] = {{14,14},{13,10},{11,6}};
static const glyph_stroke_t stroke_957_3[8] = {{15,14},{14,11},{13,9},{11,6},{9,4},{6,2},{4,1},{1,0}};
static const glyph_stroke_t stroke_957_4[2] = {{0,14},{4,14}};
static const glyph_stroke_t *strokes_957[5] = {stroke_957_0, stroke_957_1, stroke_957_2, stroke_957_3, stroke_957_4};
static const uint8_t ncoords_957[5] = {2, 4, 3, 8, 2};
static const glyph_stroke_t stroke_958_0[7] = {{8,21},{6,20},{5,19},{5,18},{6,17},{9,16},{12,16}};
static const glyph_stroke_t stroke_958_1[8] = {{9,16},{5,15},{3,14},{2,12},{2,10},{4,8},{7,7},{10,7}};
static const glyph_stroke_t stroke_958_2[7] = {{9,16},{6,15},{4,14},{3,12},{3,10},{5,8},{7,7}};
static const glyph_stroke_t stroke_958_3[11] = {{7,7},{3,6},{1,5},{0,3},{0,1},{2,-1},{7,-3},{8,-4},{8,-6},{6,-7},{4,-7}};
static const glyph_stroke_t stroke_958_4[7] = {{7,7},{4,6},{2,5},{1,3},{1,1},{3,-1},{7,-3}};
static const glyph_stroke_t *strokes_958[5] = {stroke_958_0, stroke_958_1, stroke_958_2, stroke_958_3, stroke_958_4};
static const uint8_t ncoords_958[5] = {7, 8, 7, 11, 7};
static const glyph_stroke_t stroke_959_0[17] = {{6,14},{3,13},{1,10},{0,7},{0,4},{1,2},{2,1},{4,0},{6,0},{9,1},{11,4},{12,7},{12,10},{11,12},{10,13},{8,14},{6,14}};
static const glyph_stroke_t stroke_959_1[6] = {{6,14},{4,13},{2,10},{1,7},{1,3},{2,1}};
static const glyph_stroke_t stroke_959_2[6] = {{6,0},{8,1},{10,4},{11,7},{11,11},{10,13}};
static const glyph_stroke_t *strokes_959[3] = {stroke_959_0, stroke_959_1, stroke_959_2};
static const uint8_t ncoords_959[3] = {17, 6, 6};
static const glyph_stroke_t stroke_960_0[2] = {{7,13},{3,0}};
static const glyph_stroke_t stroke_960_1[2] = {{7,13},{4,0}};
static const glyph_stroke_t stroke_960_2[2] = {{13,13},{13,0}};
static const glyph_stroke_t stroke_960_3[2] = {{13,13},{14,0}};
static const glyph_stroke_t stroke_960_4[4] = {{0,11},{2,13},{5,14},{18,14}};
static const glyph_stroke_t stroke_960_5[4] = {{0,11},{2,12},{5,13},{18,13}};
static const glyph_stroke_t *strokes_960[6] = {stroke_960_0, stroke_960_1, stroke_960_2, stroke_960_3, stroke_960_4, stroke_960_5};
static const uint8_t ncoords_960[6] = {2, 2, 2, 2, 4, 4};
static const glyph_stroke_t stroke_961_0[17] = {{4,5},{5,2},{6,1},{8,0},{10,0},{13,1},{15,4},{16,7},{16,10},{15,12},{14,13},{12,14},{10,14},{7,13},{5,10},{4,7},{0,-7}};
static const glyph_stroke_t stroke_961_1[6] = {{10,0},{12,1},{14,4},{15,7},{15,11},{14,13}};
static const glyph_stroke_t stroke_961_2[5] = {{10,14},{8,13},{6,10},{5,7},{1,-7}};
static const glyph_stroke_t *strokes_961[3] = {stroke_961_0, stroke_961_1, stroke_961_2};
static const uint8_t ncoords_961[3] = {17, 6, 5};
static const glyph_stroke_t stroke_963_0[17] = {{16,14},{6,14},{3,13},{1,10},{0,7},{0,4},{1,2},{2,1},{4,0},{6,0},{9,1},{11,4},{12,7},{12,10},{11,12},{10,13},{8,14}};
static const glyph_stroke_t stroke_963_1[6] = {{6,14},{4,13},{2,10},{1,7},{1,3},{2,1}};
static const glyph_stroke_t stroke_963_2[6] = {{6,0},{8,1},{10,4},{11,7},{11,11},{10,13}};
static const glyph_stroke_t stroke_963_3[2] = {{10,13},{16,13}};
static const glyph_stroke_t *strokes_963[4] = {stroke_963_0, stroke_963_1, stroke_963_2, stroke_963_3};
static const uint8_t ncoords_963[4] = {17, 6, 6, 2};
static const glyph_stroke_t stroke_964_0[2] = {{9,13},{6,0}};
static const glyph_stroke_t stroke_964_1[2] = {{9,13},{7,0}};
static const glyph_stroke_t stroke_964_2[4] = {{0,11},{2,13},{5,14},{16,14}};
static const glyph_stroke_t stroke_964_3[4] = {{0,11},{2,12},{5,13},{16,13}};
static const glyph_stroke_t *strokes_964[4] = {stroke_964_0, stroke_964_1, stroke_964_2, stroke_964_3};
static const uint8_t ncoords_964[4] = {2, 2, 4, 4};
static const glyph_stroke_t stroke_197_0[9] = {{0,10},{1,12},{3,14},{6,14},{7,13},{7,11},{5,5},{5,2},{7,0}};
static const glyph_stroke_t stroke_197_1[17] = {{5,14},{6,13},{6,11},{4,5},{4,2},{5,1},{7,0},{8,0},{11,1},{13,3},{15,6},{16,9},{16,12},{15,14},{14,13},{15,12},{16,9}};
static const glyph_stroke_t stroke_197_2[2] = {{15,6},{16,12}};
static const glyph_stroke_t *strokes_197[3] = {stroke_197_0, stroke_197_1, stroke_197_2};
static const uint8_t ncoords_197[3] = {9, 17, 2};
static const glyph_stroke_t stroke_966_0[20] = {{5,13},{3,12},{1,10},{0,7},{0,4},{1,2},{2,1},{4,0},{7,0},{10,1},{13,3},{15,6},{16,9},{16,12},{14,14},{12,14},{10,12},{8,8},{6,3},{3,-7}};
static const glyph_stroke_t stroke_966_1[7] = {{0,4},{2,2},{4,1},{7,1},{10,2},{13,4},{15,6}};
static const glyph_stroke_t stroke_966_2[7] = {{16,12},{14,13},{12,13},{10,11},{8,8},{6,2},{4,-7}};
static const glyph_stroke_t *strokes_966[3] = {stroke_966_0, stroke_966_1, stroke_966_2};
static const uint8_t ncoords_966[3] = {20, 7, 7};
static const glyph_stroke_t stroke_967_0[7] = {{1,14},{3,14},{5,13},{6,11},{11,-4},{12,-6},{13,-7}};
static const glyph_stroke_t stroke_967_1[7] = {{3,14},{4,13},{5,11},{10,-4},{11,-6},{13,-7},{15,-7}};
static const glyph_stroke_t stroke_967_2[6] = {{16,14},{15,12},{13,9},{3,-2},{1,-5},{0,-7}};
static const glyph_stroke_t *strokes_967[3] = {stroke_967_0, stroke_967_1, stroke_967_2};
static const uint8_t ncoords_967[3] = {7, 7, 6};
static const glyph_stroke_t stroke_968_0[2] = {{14,21},{8,-7}};
static const glyph_stroke_t stroke_968_1[2] = {{15,21},{7,-7}};
static const glyph_stroke_t stroke_968_2[13] = {{0,10},{1,12},{3,14},{6,14},{7,13},{7,11},{6,6},{6,3},{8,1},{11,1},{13,2},{16,5},{18,8}};
static const glyph_stroke_t stroke_968_3[13] = {{5,14},{6,13},{6,11},{5,6},{5,3},{6,1},{8,0},{11,0},{13,1},{15,3},{17,6},{18,8},{20,14}};
static const glyph_stroke_t *strokes_968[4] = {stroke_968_0, stroke_968_1, stroke_968_2, stroke_968_3};
static const uint8_t ncoords_968[4] = {2, 2, 13, 13};
static const glyph_stroke_t stroke_969_0[14] = {{1,10},{3,12},{6,13},{5,14},{3,13},{1,10},{0,7},{0,4},{1,1},{2,0},{4,0},{6,1},{8,4},{9,7}};
static const glyph_stroke_t stroke_969_1[6] = {{0,4},{1,2},{2,1},{4,1},{6,2},{8,4}};
static const glyph_stroke_t stroke_969_2[14] = {{8,7},{8,4},{9,1},{10,0},{12,0},{14,1},{16,4},{17,7},{17,10},{16,13},{15,14},{14,13},{16,12},{17,10}};
static const glyph_stroke_t stroke_969_3[6] = {{8,4},{9,2},{10,1},{12,1},{14,2},{16,4}};
static const glyph_stroke_t *strokes_969[4] = {stroke_969_0, stroke_969_1, stroke_969_2, stroke_969_3};
static const uint8_t ncoords_969[4] = {14, 6, 14, 6};
static const glyph_stroke_t stroke_1040_0[2] = {{9,21},{2,0}};
static const glyph_stroke_t stroke_1040_1[2] = {{9,21},{16,0}};
static const glyph_stroke_t stroke_1040_2[2] = {{9,18},{15,0}};
static const glyph_stroke_t stroke_1040_3[2] = {{4,6},{13,6}};
static const glyph_stroke_t stroke_1040_4[2] = {{0,0},{6,0}};
static const glyph_stroke_t stroke_1040_5[2] = {{12,0},{18,0}};
static const glyph_stroke_t *strokes_1040[6] = {stroke_1040_0, stroke_1040_1, stroke_1040_2, stroke_1040_3, stroke_1040_4, stroke_1040_5};
static const uint8_t ncoords_1040[6] = {2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_1041_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_1041_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_1041_2[4] = {{0,21},{16,21},{16,15},{15,21}};
static const glyph_stroke_t stroke_1041_3[10] = {{4,11},{12,11},{15,10},{16,9},{17,7},{17,4},{16,2},{15,1},{12,0},{0,0}};
static const glyph_stroke_t stroke_1041_4[8] = {{12,11},{14,10},{15,9},{16,7},{16,4},{15,2},{14,1},{12,0}};
static const glyph_stroke_t *strokes_1041[5] = {stroke_1041_0, stroke_1041_1, stroke_1041_2, stroke_1041_3, stroke_1041_4};
static const uint8_t ncoords_1041[5] = {2, 2, 4, 10, 8};
static const glyph_stroke_t stroke_1042_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_1042_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_1042_2[9] = {{0,21},{12,21},{15,20},{16,19},{17,17},{17,15},{16,13},{15,12},{12,11}};
static const glyph_stroke_t stroke_1042_3[8] = {{12,21},{14,20},{15,19},{16,17},{16,15},{15,13},{14,12},{12,11}};
static const glyph_stroke_t stroke_1042_4[10] = {{4,11},{12,11},{15,10},{16,9},{17,7},{17,4},{16,2},{15,1},{12,0},{0,0}};
static const glyph_stroke_t stroke_1042_5[8] = {{12,11},{14,10},{15,9},{16,7},{16,4},{15,2},{14,1},{12,0}};
static const glyph_stroke_t *strokes_1042[6] = {stroke_1042_0, stroke_1042_1, stroke_1042_2, stroke_1042_3, stroke_1042_4, stroke_1042_5};
static const uint8_t ncoords_1042[6] = {2, 2, 9, 8, 10, 8};
static const glyph_stroke_t stroke_1043_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_1043_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_1043_2[4] = {{0,21},{15,21},{15,15},{14,21}};
static const glyph_stroke_t stroke_1043_3[2] = {{0,0},{7,0}};
static const glyph_stroke_t *strokes_1043[4] = {stroke_1043_0, stroke_1043_1, stroke_1043_2, stroke_1043_3};
static const uint8_t ncoords_1043[4] = {2, 2, 4, 2};
static const glyph_stroke_t stroke_1044_0[6] = {{7,21},{7,15},{6,7},{5,3},{4,1},{3,0}};
static const glyph_stroke_t stroke_1044_1[2] = {{17,21},{17,0}};
static const glyph_stroke_t stroke_1044_2[2] = {{18,21},{18,0}};
static const glyph_stroke_t stroke_1044_3[2] = {{4,21},{21,21}};
static const glyph_stroke_t stroke_1044_4[2] = {{0,0},{21,0}};
static const glyph_stroke_t stroke_1044_5[2] = {{0,0},{0,-7}};
static const glyph_stroke_t stroke_1044_6[2] = {{1,0},{0,-7}};
static const glyph_stroke_t stroke_1044_7[2] = {{20,0},{21,-7}};
static const glyph_stroke_t stroke_1044_8[2] = {{21,0},{21,-7}};
static const glyph_stroke_t *strokes_1044[9] = {stroke_1044_0, stroke_1044_1, stroke_1044_2, stroke_1044_3, stroke_1044_4, stroke_1044_5, stroke_1044_6, stroke_1044_7, stroke_1044_8};
static const uint8_t ncoords_1044[9] = {6, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_1045_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_1045_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_1045_2[2] = {{10,15},{10,7}};
static const glyph_stroke_t stroke_1045_3[4] = {{0,21},{16,21},{16,15},{15,21}};
static const glyph_stroke_t stroke_1045_4[2] = {{4,11},{10,11}};
static const glyph_stroke_t stroke_1045_5[4] = {{0,0},{16,0},{16,6},{15,0}};
static const glyph_stroke_t *strokes_1045[6] = {stroke_1045_0, stroke_1045_1, stroke_1045_2, stroke_1045_3, stroke_1045_4, stroke_1045_5};
static const uint8_t ncoords_1045[6] = {2, 2, 2, 4, 2, 4};
static const glyph_stroke_t stroke_1046_0[2] = {{13,21},{13,0}};
static const glyph_stroke_t stroke_1046_1[2] = {{14,21},{14,0}};
static const glyph_stroke_t stroke_1046_2[2] = {{10,21},{17,21}};
static const glyph_stroke_t stroke_1046_3[24] = {{2,20},{3,19},{2,18},{1,19},{1,20},{2,21},{3,21},{4,20},{5,18},{6,14},{7,12},{9,11},{18,11},{20,12},{21,14},{22,18},{23,20},{24,21},{25,21},{26,20},{26,19},{25,18},{24,19},{25,20}};
static const glyph_stroke_t stroke_1046_4[6] = {{9,11},{7,10},{6,8},{5,3},{4,1},{3,0}};
static const glyph_stroke_t stroke_1046_5[9] = {{9,11},{8,10},{7,8},{6,3},{5,1},{4,0},{2,0},{1,1},{0,3}};
static const glyph_stroke_t stroke_1046_6[6] = {{18,11},{20,10},{21,8},{22,3},{23,1},{24,0}};
static const glyph_stroke_t stroke_1046_7[9] = {{18,11},{19,10},{20,8},{21,3},{22,1},{23,0},{25,0},{26,1},{27,3}};
static const glyph_stroke_t stroke_1046_8[2] = {{10,0},{17,0}};
static const glyph_stroke_t *strokes_1046[9] = {stroke_1046_0, stroke_1046_1, stroke_1046_2, stroke_1046_3, stroke_1046_4, stroke_1046_5, stroke_1046_6, stroke_1046_7, stroke_1046_8};
static const uint8_t ncoords_1046[9] = {2, 2, 2, 24, 6, 9, 6, 9, 2};
static const glyph_stroke_t stroke_1047_0[13] = {{1,18},{0,21},{0,15},{1,18},{3,20},{5,21},{9,21},{12,20},{13,18},{13,15},{12,13},{9,12},{6,12}};
static const glyph_stroke_t stroke_1047_1[6] = {{9,21},{11,20},{12,18},{12,15},{11,13},{9,12}};
static const glyph_stroke_t stroke_1047_2[16] = {{9,12},{11,11},{13,9},{14,7},{14,4},{13,2},{12,1},{9,0},{4,0},{2,1},{1,2},{0,4},{0,5},{1,6},{2,5},{1,4}};
static const glyph_stroke_t stroke_1047_3[6] = {{12,10},{13,7},{13,4},{12,2},{11,1},{9,0}};
static const glyph_stroke_t *strokes_1047[4] = {stroke_1047_0, stroke_1047_1, stroke_1047_2, stroke_1047_3};
static const uint8_t ncoords_1047[4] = {13, 6, 16, 6};
static const glyph_stroke_t stroke_1048_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_1048_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_1048_2[2] = {{16,21},{16,0}};
static const glyph_stroke_t stroke_1048_3[2] = {{17,21},{17,0}};
static const glyph_stroke_t stroke_1048_4[2] = {{0,21},{7,21}};
static const glyph_stroke_t stroke_1048_5[2] = {{13,21},{20,21}};
static const glyph_stroke_t stroke_1048_6[2] = {{16,19},{4,2}};
static const glyph_stroke_t stroke_1048_7[2] = {{0,0},{7,0}};
static const glyph_stroke_t stroke_1048_8[2] = {{13,0},{20,0}};
static const glyph_stroke_t *strokes_1048[9] = {stroke_1048_0, stroke_1048_1, stroke_1048_2, stroke_1048_3, stroke_1048_4, stroke_1048_5, stroke_1048_6, stroke_1048_7, stroke_1048_8};
static const uint8_t ncoords_1048[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_1049_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_1049_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_1049_2[2] = {{16,21},{16,0}};
static const glyph_stroke_t stroke_1049_3[2] = {{17,21},{17,0}};
static const glyph_stroke_t stroke_1049_4[2] = {{0,21},{7,21}};
static const glyph_stroke_t stroke_1049_5[2] = {{13,21},{20,21}};
static const glyph_stroke_t stroke_1049_6[2] = {{16,19},{4,2}};
static const glyph_stroke_t stroke_1049_7[2] = {{0,0},{7,0}};
static const glyph_stroke_t stroke_1049_8[2] = {{13,0},{20,0}};
static const glyph_stroke_t stroke_1049_9[9] = {{7,26},{7,27},{6,27},{6,26},{7,24},{9,23},{11,23},{13,24},{14,26}};
static const glyph_stroke_t *strokes_1049[10] = {stroke_1049_0, stroke_1049_1, stroke_1049_2, stroke_1049_3, stroke_1049_4, stroke_1049_5, stroke_1049_6, stroke_1049_7, stroke_1049_8, stroke_1049_9};
static const uint8_t ncoords_1049[10] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 9};
static const glyph_stroke_t stroke_1050_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_1050_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_1050_2[2] = {{0,21},{7,21}};
static const glyph_stroke_t stroke_1050_3[13] = {{4,11},{11,11},{13,12},{14,14},{15,18},{16,20},{17,21},{18,21},{19,20},{19,19},{18,18},{17,19},{18,20}};
static const glyph_stroke_t stroke_1050_4[6] = {{11,11},{13,10},{14,8},{15,3},{16,1},{17,0}};
static const glyph_stroke_t stroke_1050_5[9] = {{11,11},{12,10},{13,8},{14,3},{15,1},{16,0},{18,0},{19,1},{20,3}};
static const glyph_stroke_t stroke_1050_6[2] = {{0,0},{7,0}};
static const glyph_stroke_t *strokes_1050[7] = {stroke_1050_0, stroke_1050_1, stroke_1050_2, stroke_1050_3, stroke_1050_4, stroke_1050_5, stroke_1050_6};
static const uint8_t ncoords_1050[7] = {2, 2, 2, 13, 6, 9, 2};
static const glyph_stroke_t stroke_1051_0[12] = {{6,21},{6,15},{5,7},{4,3},{3,1},{2,0},{1,0},{0,1},{0,2},{1,3},{2,2},{1,1}};
static const glyph_stroke_t stroke_1051_1[2] = {{17,21},{17,0}};
static const glyph_stroke_t stroke_1051_2[2] = {{18,21},{18,0}};
static const glyph_stroke_t stroke_1051_3[2] = {{3,21},{21,21}};
static const glyph_stroke_t stroke_1051_4[2] = {{14,0},{21,0}};
static const glyph_stroke_t *strokes_1051[5] = {stroke_1051_0, stroke_1051_1, stroke_1051_2, stroke_1051_3, stroke_1051_4};
static const uint8_t ncoords_1051[5] = {12, 2, 2, 2, 2};
static const glyph_stroke_t stroke_1052_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_1052_1[2] = {{4,21},{10,3}};
static const glyph_stroke_t stroke_1052_2[2] = {{3,21},{10,0}};
static const glyph_stroke_t stroke_1052_3[2] = {{17,21},{10,0}};
static const glyph_stroke_t stroke_1052_4[2] = {{17,21},{17,0}};
static const glyph_stroke_t stroke_1052_5[2] = {{18,21},{18,0}};
static const glyph_stroke_t stroke_1052_6[2] = {{0,21},{4,21}};
static const glyph_stroke_t stroke_1052_7[2] = {{17,21},{21,21}};
static const glyph_stroke_t stroke_1052_8[2] = {{0,0},{6,0}};
static const glyph_stroke_t stroke_1052_9[2] = {{14,0},{21,0}};
static const glyph_stroke_t *strokes_1052[10] = {stroke_1052_0, stroke_1052_1, stroke_1052_2, stroke_1052_3, stroke_1052_4, stroke_1052_5, stroke_1052_6, stroke_1052_7, stroke_1052_8, stroke_1052_9};
static const uint8_t ncoords_1052[10] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_1053_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_1053_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_1053_2[2] = {{16,21},{16,0}};
static const glyph_stroke_t stroke_1053_3[2] = {{17,21},{17,0}};
static const glyph_stroke_t stroke_1053_4[2] = {{0,21},{7,21}};
static const glyph_stroke_t stroke_1053_5[2] = {{13,21},{20,21}};
static const glyph_stroke_t stroke_1053_6[2] = {{4,11},{16,11}};
static const glyph_stroke_t stroke_1053_7[2] = {{0,0},{7,0}};
static const glyph_stroke_t stroke_1053_8[2] = {{13,0},{20,0}};
static const glyph_stroke_t *strokes_1053[9] = {stroke_1053_0, stroke_1053_1, stroke_1053_2, stroke_1053_3, stroke_1053_4, stroke_1053_5, stroke_1053_6, stroke_1053_7, stroke_1053_8};
static const uint8_t ncoords_1053[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_1054_0[21] = {{7,21},{4,20},{2,18},{1,16},{0,12},{0,9},{1,5},{2,3},{4,1},{7,0},{9,0},{12,1},{14,3},{15,5},{16,9},{16,12},{15,16},{14,18},{12,20},{9,21},{7,21}};
static const glyph_stroke_t stroke_1054_1[10] = {{7,21},{5,20},{3,18},{2,16},{1,12},{1,9},{2,5},{3,3},{5,1},{7,0}};
static const glyph_stroke_t stroke_1054_2[10] = {{9,0},{11,1},{13,3},{14,5},{15,9},{15,12},{14,16},{13,18},{11,20},{9,21}};
static const glyph_stroke_t *strokes_1054[3] = {stroke_1054_0, stroke_1054_1, stroke_1054_2};
static const uint8_t ncoords_1054[3] = {21, 10, 10};
static const glyph_stroke_t stroke_1055_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_1055_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_1055_2[2] = {{16,21},{16,0}};
static const glyph_stroke_t stroke_1055_3[2] = {{17,21},{17,0}};
static const glyph_stroke_t stroke_1055_4[2] = {{0,21},{20,21}};
static const glyph_stroke_t stroke_1055_5[2] = {{0,0},{7,0}};
static const glyph_stroke_t stroke_1055_6[2] = {{13,0},{20,0}};
static const glyph_stroke_t *strokes_1055[7] = {stroke_1055_0, stroke_1055_1, stroke_1055_2, stroke_1055_3, stroke_1055_4, stroke_1055_5, stroke_1055_6};
static const uint8_t ncoords_1055[7] = {2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_1056_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_1056_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_1056_2[10] = {{0,21},{12,21},{15,20},{16,19},{17,17},{17,14},{16,12},{15,11},{12,10},{4,10}};
static const glyph_stroke_t stroke_1056_3[8] = {{12,21},{14,20},{15,19},{16,17},{16,14},{15,12},{14,11},{12,10}};
static const glyph_stroke_t stroke_1056_4[2] = {{0,0},{7,0}};
static const glyph_stroke_t *strokes_1056[5] = {stroke_1056_0, stroke_1056_1, stroke_1056_2, stroke_1056_3, stroke_1056_4};
static const uint8_t ncoords_1056[5] = {2, 2, 10, 8, 2};
static const glyph_stroke_t stroke_1057_0[20] = {{14,18},{15,15},{15,21},{14,18},{12,20},{9,21},{7,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3},{4,1},{7,0},{9,0},{12,1},{14,3},{15,5}};
static const glyph_stroke_t stroke_1057_1[10] = {{7,21},{5,20},{3,18},{2,16},{1,13},{1,8},{2,5},{3,3},{5,1},{7,0}};
static const glyph_stroke_t *strokes_1057[2] = {stroke_1057_0, stroke_1057_1};
static const uint8_t ncoords_1057[2] = {20, 10};
static const glyph_stroke_t stroke_1058_0[2] = {{7,21},{7,0}};
static const glyph_stroke_t stroke_1058_1[2] = {{8,21},{8,0}};
static const glyph_stroke_t stroke_1058_2[6] = {{1,21},{0,15},{0,21},{15,21},{15,15},{14,21}};
static const glyph_stroke_t stroke_1058_3[2] = {{4,0},{11,0}};
static const glyph_stroke_t *strokes_1058[4] = {stroke_1058_0, stroke_1058_1, stroke_1058_2, stroke_1058_3};
static const uint8_t ncoords_1058[4] = {2, 2, 6, 2};
static const glyph_stroke_t stroke_1059_0[2] = {{2,21},{9,5}};
static const glyph_stroke_t stroke_1059_1[2] = {{3,21},{10,5}};
static const glyph_stroke_t stroke_1059_2[11] = {{17,21},{10,5},{8,2},{7,1},{5,0},{4,0},{3,1},{3,2},{4,3},{5,2},{4,1}};
static const glyph_stroke_t stroke_1059_3[2] = {{0,21},{6,21}};
static const glyph_stroke_t stroke_1059_4[2] = {{13,21},{19,21}};
static const glyph_stroke_t *strokes_1059[5] = {stroke_1059_0, stroke_1059_1, stroke_1059_2, stroke_1059_3, stroke_1059_4};
static const uint8_t ncoords_1059[5] = {2, 2, 11, 2, 2};
static const glyph_stroke_t stroke_1060_0[2] = {{9,21},{9,0}};
static const glyph_stroke_t stroke_1060_1[2] = {{10,21},{10,0}};
static const glyph_stroke_t stroke_1060_2[2] = {{6,21},{13,21}};
static const glyph_stroke_t stroke_1060_3[17] = {{7,18},{3,17},{1,15},{0,12},{0,9},{1,6},{3,4},{7,3},{12,3},{16,4},{18,6},{19,9},{19,12},{18,15},{16,17},{12,18},{7,18}};
static const glyph_stroke_t stroke_1060_4[8] = {{7,18},{4,17},{2,15},{1,12},{1,9},{2,6},{4,4},{7,3}};
static const glyph_stroke_t stroke_1060_5[8] = {{12,3},{15,4},{17,6},{18,9},{18,12},{17,15},{15,17},{12,18}};
static const glyph_stroke_t stroke_1060_6[2] = {{6,0},{13,0}};
static const glyph_stroke_t *strokes_1060[7] = {stroke_1060_0, stroke_1060_1, stroke_1060_2, stroke_1060_3, stroke_1060_4, stroke_1060_5, stroke_1060_6};
static const uint8_t ncoords_1060[7] = {2, 2, 2, 17, 8, 8, 2};
static const glyph_stroke_t stroke_1061_0[2] = {{2,21},{15,0}};
static const glyph_stroke_t stroke_1061_1[2] = {{3,21},{16,0}};
static const glyph_stroke_t stroke_1061_2[2] = {{16,21},{2,0}};
static const glyph_stroke_t stroke_1061_3[2] = {{0,21},{6,21}};
static const glyph_stroke_t stroke_1061_4[2] = {{12,21},{18,21}};
static const glyph_stroke_t stroke_1061_5[2] = {{0,0},{6,0}};
static const glyph_stroke_t stroke_1061_6[2] = {{12,0},{18,0}};
static const glyph_stroke_t *strokes_1061[7] = {stroke_1061_0, stroke_1061_1, stroke_1061_2, stroke_1061_3, stroke_1061_4, stroke_1061_5, stroke_1061_6};
static const uint8_t ncoords_1061[7] = {2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_1062_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_1062_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_1062_2[2] = {{16,21},{16,0}};
static const glyph_stroke_t stroke_1062_3[2] = {{17,21},{17,0}};
static const glyph_stroke_t stroke_1062_4[2] = {{0,21},{7,21}};
static const glyph_stroke_t stroke_1062_5[2] = {{13,21},{20,21}};
static const glyph_stroke_t stroke_1062_6[2] = {{0,0},{20,0}};
static const glyph_stroke_t stroke_1062_7[2] = {{19,0},{20,-7}};
static const glyph_stroke_t stroke_1062_8[2] = {{20,0},{20,-7}};
static const glyph_stroke_t *strokes_1062[9] = {stroke_1062_0, stroke_1062_1, stroke_1062_2, stroke_1062_3, stroke_1062_4, stroke_1062_5, stroke_1062_6, stroke_1062_7, stroke_1062_8};
static const uint8_t ncoords_1062[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_1063_0[7] = {{3,21},{3,10},{4,8},{7,7},{10,7},{13,8},{15,10}};
static const glyph_stroke_t stroke_1063_1[4] = {{4,21},{4,10},{5,8},{7,7}};
static const glyph_stroke_t stroke_1063_2[2] = {{15,21},{15,0}};
static const glyph_stroke_t stroke_1063_3[2] = {{16,21},{16,0}};
static const glyph_stroke_t stroke_1063_4[2] = {{0,21},{7,21}};
static const glyph_stroke_t stroke_1063_5[2] = {{12,21},{19,21}};
static const glyph_stroke_t stroke_1063_6[2] = {{12,0},{19,0}};
static const glyph_stroke_t *strokes_1063[7] = {stroke_1063_0, stroke_1063_1, stroke_1063_2, stroke_1063_3, stroke_1063_4, stroke_1063_5, stroke_1063_6};
static const uint8_t ncoords_1063[7] = {7, 4, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_1064_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_1064_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_1064_2[2] = {{14,21},{14,0}};
static const glyph_stroke_t stroke_1064_3[2] = {{15,21},{15,0}};
static const glyph_stroke_t stroke_1064_4[2] = {{25,21},{25,0}};
static const glyph_stroke_t stroke_1064_5[2] = {{26,21},{26,0}};
static const glyph_stroke_t stroke_1064_6[2] = {{0,21},{7,21}};
static const glyph_stroke_t stroke_1064_7[2] = {{11,21},{18,21}};
static const glyph_stroke_t stroke_1064_8[2] = {{22,21},{29,21}};
static const glyph_stroke_t stroke_1064_9[2] = {{0,0},{29,0}};
static const glyph_stroke_t *strokes_1064[10] = {stroke_1064_0, stroke_1064_1, stroke_1064_2, stroke_1064_3, stroke_1064_4, stroke_1064_5, stroke_1064_6, stroke_1064_7, stroke_1064_8, stroke_1064_9};
static const uint8_t ncoords_1064[10] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_1065_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_1065_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_1065_2[2] = {{14,21},{14,0}};
static const glyph_stroke_t stroke_1065_3[2] = {{15,21},{15,0}};
static const glyph_stroke_t stroke_1065_4[2] = {{25,21},{25,0}};
static const glyph_stroke_t stroke_1065_5[2] = {{26,21},{26,0}};
static const glyph_stroke_t stroke_1065_6[2] = {{0,21},{7,21}};
static const glyph_stroke_t stroke_1065_7[2] = {{11,21},{18,21}};
static const glyph_stroke_t stroke_1065_8[2] = {{22,21},{29,21}};
static const glyph_stroke_t stroke_1065_9[2] = {{0,0},{29,0}};
static const glyph_stroke_t stroke_1065_10[2] = {{28,0},{29,-7}};
static const glyph_stroke_t stroke_1065_11[2] = {{29,0},{29,-7}};
static const glyph_stroke_t *strokes_1065[12] = {stroke_1065_0, stroke_1065_1, stroke_1065_2, stroke_1065_3, stroke_1065_4, stroke_1065_5, stroke_1065_6, stroke_1065_7, stroke_1065_8, stroke_1065_9, stroke_1065_10, stroke_1065_11};
static const uint8_t ncoords_1065[12] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_1066_0[2] = {{8,21},{8,0}};
static const glyph_stroke_t stroke_1066_1[2] = {{9,21},{9,0}};
static const glyph_stroke_t stroke_1066_2[4] = {{1,21},{0,15},{0,21},{12,21}};
static const glyph_stroke_t stroke_1066_3[10] = {{9,11},{16,11},{19,10},{20,9},{21,7},{21,4},{20,2},{19,1},{16,0},{5,0}};
static const glyph_stroke_t stroke_1066_4[8] = {{16,11},{18,10},{19,9},{20,7},{20,4},{19,2},{18,1},{16,0}};
static const glyph_stroke_t *strokes_1066[5] = {stroke_1066_0, stroke_1066_1, stroke_1066_2, stroke_1066_3, stroke_1066_4};
static const uint8_t ncoords_1066[5] = {2, 2, 4, 10, 8};
static const glyph_stroke_t stroke_1067_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_1067_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_1067_2[2] = {{0,21},{7,21}};
static const glyph_stroke_t stroke_1067_3[10] = {{4,11},{11,11},{14,10},{15,9},{16,7},{16,4},{15,2},{14,1},{11,0},{0,0}};
static const glyph_stroke_t stroke_1067_4[8] = {{11,11},{13,10},{14,9},{15,7},{15,4},{14,2},{13,1},{11,0}};
static const glyph_stroke_t stroke_1067_5[2] = {{22,21},{22,0}};
static const glyph_stroke_t stroke_1067_6[2] = {{23,21},{23,0}};
static const glyph_stroke_t stroke_1067_7[2] = {{19,21},{26,21}};
static const glyph_stroke_t stroke_1067_8[2] = {{19,0},{26,0}};
static const glyph_stroke_t *strokes_1067[9] = {stroke_1067_0, stroke_1067_1, stroke_1067_2, stroke_1067_3, stroke_1067_4, stroke_1067_5, stroke_1067_6, stroke_1067_7, stroke_1067_8};
static const uint8_t ncoords_1067[9] = {2, 2, 2, 10, 8, 2, 2, 2, 2};
static const glyph_stroke_t stroke_1068_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_1068_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_1068_2[2] = {{0,21},{7,21}};
static const glyph_stroke_t stroke_1068_3[10] = {{4,11},{11,11},{14,10},{15,9},{16,7},{16,4},{15,2},{14,1},{11,0},{0,0}};
static const glyph_stroke_t stroke_1068_4[8] = {{11,11},{13,10},{14,9},{15,7},{15,4},{14,2},{13,1},{11,0}};
static const glyph_stroke_t *strokes_1068[5] = {stroke_1068_0, stroke_1068_1, stroke_1068_2, stroke_1068_3, stroke_1068_4};
static const uint8_t ncoords_1068[5] = {2, 2, 2, 10, 8};
static const glyph_stroke_t stroke_1069_0[24] = {{1,18},{0,21},{0,15},{1,18},{3,20},{6,21},{8,21},{11,20},{13,18},{14,16},{15,13},{15,8},{14,5},{13,3},{11,1},{8,0},{5,0},{2,1},{1,2},{0,4},{0,5},{1,6},{2,5},{1,4}};
static const glyph_stroke_t stroke_1069_1[10] = {{8,21},{10,20},{12,18},{13,16},{14,13},{14,8},{13,5},{12,3},{10,1},{8,0}};
static const glyph_stroke_t stroke_1069_2[2] = {{5,11},{14,11}};
static const glyph_stroke_t *strokes_1069[3] = {stroke_1069_0, stroke_1069_1, stroke_1069_2};
static const uint8_t ncoords_1069[3] = {24, 10, 2};
static const glyph_stroke_t stroke_1070_0[2] = {{3,21},{3,0}};
static const glyph_stroke_t stroke_1070_1[2] = {{4,21},{4,0}};
static const glyph_stroke_t stroke_1070_2[2] = {{0,21},{7,21}};
static const glyph_stroke_t stroke_1070_3[2] = {{0,0},{7,0}};
static const glyph_stroke_t stroke_1070_4[21] = {{17,21},{14,20},{12,18},{11,16},{10,12},{10,9},{11,5},{12,3},{14,1},{17,0},{19,0},{22,1},{24,3},{25,5},{26,9},{26,12},{25,16},{24,18},{22,20},{19,21},{17,21}};
static const glyph_stroke_t stroke_1070_5[10] = {{17,21},{15,20},{13,18},{12,16},{11,12},{11,9},{12,5},{13,3},{15,1},{17,0}};
static const glyph_stroke_t stroke_1070_6[10] = {{19,0},{21,1},{23,3},{24,5},{25,9},{25,12},{24,16},{23,18},{21,20},{19,21}};
static const glyph_stroke_t stroke_1070_7[2] = {{4,11},{10,11}};
static const glyph_stroke_t *strokes_1070[8] = {stroke_1070_0, stroke_1070_1, stroke_1070_2, stroke_1070_3, stroke_1070_4, stroke_1070_5, stroke_1070_6, stroke_1070_7};
static const uint8_t ncoords_1070[8] = {2, 2, 2, 2, 21, 10, 10, 2};
static const glyph_stroke_t stroke_1071_0[2] = {{14,21},{14,0}};
static const glyph_stroke_t stroke_1071_1[2] = {{15,21},{15,0}};
static const glyph_stroke_t stroke_1071_2[10] = {{18,21},{6,21},{3,20},{2,19},{1,17},{1,15},{2,13},{3,12},{6,11},{14,11}};
static const glyph_stroke_t stroke_1071_3[8] = {{6,21},{4,20},{3,19},{2,17},{2,15},{3,13},{4,12},{6,11}};
static const glyph_stroke_t stroke_1071_4[7] = {{9,11},{7,10},{6,9},{3,2},{2,1},{1,1},{0,2}};
static const glyph_stroke_t stroke_1071_5[7] = {{7,10},{6,8},{4,1},{3,0},{1,0},{0,2},{0,3}};
static const glyph_stroke_t stroke_1071_6[2] = {{11,0},{18,0}};
static const glyph_stroke_t *strokes_1071[7] = {stroke_1071_0, stroke_1071_1, stroke_1071_2, stroke_1071_3, stroke_1071_4, stroke_1071_5, stroke_1071_6};
static const uint8_t ncoords_1071[7] = {2, 2, 10, 8, 7, 7, 2};
static const glyph_stroke_t stroke_1072_0[13] = {{2,12},{2,11},{1,11},{1,12},{2,13},{4,14},{8,14},{10,13},{11,12},{12,10},{12,3},{13,1},{14,0}};
static const glyph_stroke_t stroke_1072_1[5] = {{11,12},{11,3},{12,1},{14,0},{15,0}};
static const glyph_stroke_t stroke_1072_2[11] = {{11,10},{10,9},{4,8},{1,7},{0,5},{0,3},{1,1},{4,0},{7,0},{9,1},{11,3}};
static const glyph_stroke_t stroke_1072_3[6] = {{4,8},{2,7},{1,5},{1,3},{2,1},{4,0}};
static const glyph_stroke_t *strokes_1072[4] = {stroke_1072_0, stroke_1072_1, stroke_1072_2, stroke_1072_3};
static const uint8_t ncoords_1072[4] = {13, 5, 11, 6};
static const glyph_stroke_t stroke_1073_0[22] = {{13,21},{12,20},{6,18},{3,16},{1,13},{0,10},{0,6},{1,3},{3,1},{6,0},{8,0},{11,1},{13,3},{14,6},{14,8},{13,11},{11,13},{8,14},{6,14},{3,13},{1,11},{0,8}};
static const glyph_stroke_t stroke_1073_1[6] = {{13,21},{12,19},{10,18},{6,17},{3,15},{1,13}};
static const glyph_stroke_t stroke_1073_2[8] = {{6,14},{4,13},{2,11},{1,8},{1,6},{2,3},{4,1},{6,0}};
static const glyph_stroke_t stroke_1073_3[8] = {{8,0},{10,1},{12,3},{13,6},{13,8},{12,11},{10,13},{8,14}};
static const glyph_stroke_t *strokes_1073[4] = {stroke_1073_0, stroke_1073_1, stroke_1073_2, stroke_1073_3};
static const uint8_t ncoords_1073[4] = {22, 6, 8, 8};
static const glyph_stroke_t stroke_1074_0[2] = {{3,14},{3,0}};
static const glyph_stroke_t stroke_1074_1[2] = {{4,14},{4,0}};
static const glyph_stroke_t stroke_1074_2[7] = {{0,14},{11,14},{14,13},{15,11},{15,10},{14,8},{11,7}};
static const glyph_stroke_t stroke_1074_3[6] = {{11,14},{13,13},{14,11},{14,10},{13,8},{11,7}};
static const glyph_stroke_t stroke_1074_4[8] = {{4,7},{11,7},{14,6},{15,4},{15,3},{14,1},{11,0},{0,0}};
static const glyph_stroke_t stroke_1074_5[6] = {{11,7},{13,6},{14,4},{14,3},{13,1},{11,0}};
static const glyph_stroke_t *strokes_1074[6] = {stroke_1074_0, stroke_1074_1, stroke_1074_2, stroke_1074_3, stroke_1074_4, stroke_1074_5};
static const uint8_t ncoords_1074[6] = {2, 2, 7, 6, 8, 6};
static const glyph_stroke_t stroke_1075_0[2] = {{3,14},{3,0}};
static const glyph_stroke_t stroke_1075_1[2] = {{4,14},{4,0}};
static const glyph_stroke_t stroke_1075_2[4] = {{0,14},{14,14},{14,9},{13,14}};
static const glyph_stroke_t stroke_1075_3[2] = {{0,0},{7,0}};
static const glyph_stroke_t *strokes_1075[4] = {stroke_1075_0, stroke_1075_1, stroke_1075_2, stroke_1075_3};
static const uint8_t ncoords_1075[4] = {2, 2, 4, 2};
static const glyph_stroke_t stroke_1076_0[5] = {{6,14},{6,10},{5,4},{4,1},{3,0}};
static const glyph_stroke_t stroke_1076_1[2] = {{15,14},{15,0}};
static const glyph_stroke_t stroke_1076_2[2] = {{16,14},{16,0}};
static const glyph_stroke_t stroke_1076_3[2] = {{3,14},{19,14}};
static const glyph_stroke_t stroke_1076_4[6] = {{1,0},{0,-5},{0,0},{19,0},{19,-5},{18,0}};
static const glyph_stroke_t *strokes_1076[5] = {stroke_1076_0, stroke_1076_1, stroke_1076_2, stroke_1076_3, stroke_1076_4};
static const uint8_t ncoords_1076[5] = {5, 2, 2, 2, 6};
static const glyph_stroke_t stroke_1077_0[17] = {{1,8},{13,8},{13,10},{12,12},{11,13},{9,14},{6,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{6,0},{8,0},{11,1},{13,3}};
static const glyph_stroke_t stroke_1077_1[3] = {{12,8},{12,11},{11,13}};
static const glyph_stroke_t stroke_1077_2[8] = {{6,14},{4,13},{2,11},{1,8},{1,6},{2,3},{4,1},{6,0}};
static const glyph_stroke_t *strokes_1077[3] = {stroke_1077_0, stroke_1077_1, stroke_1077_2};
static const uint8_t ncoords_1077[3] = {17, 3, 8};
static const glyph_stroke_t stroke_1078_0[2] = {{11,14},{11,0}};
static const glyph_stroke_t stroke_1078_1[2] = {{12,14},{12,0}};
static const glyph_stroke_t stroke_1078_2[2] = {{8,14},{15,14}};
static const glyph_stroke_t stroke_1078_3[18] = {{3,13},{2,12},{1,13},{2,14},{3,14},{4,13},{6,9},{7,8},{9,7},{14,7},{16,8},{17,9},{19,13},{20,14},{21,14},{22,13},{21,12},{20,13}};
static const glyph_stroke_t stroke_1078_4[5] = {{9,7},{7,6},{6,5},{4,1},{3,0}};
static const glyph_stroke_t stroke_1078_5[7] = {{9,7},{7,5},{5,1},{4,0},{2,0},{1,1},{0,3}};
static const glyph_stroke_t stroke_1078_6[5] = {{14,7},{16,6},{17,5},{19,1},{20,0}};
static const glyph_stroke_t stroke_1078_7[7] = {{14,7},{16,5},{18,1},{19,0},{21,0},{22,1},{23,3}};
static const glyph_stroke_t stroke_1078_8[2] = {{8,0},{15,0}};
static const glyph_stroke_t *strokes_1078[9] = {stroke_1078_0, stroke_1078_1, stroke_1078_2, stroke_1078_3, stroke_1078_4, stroke_1078_5, stroke_1078_6, stroke_1078_7, stroke_1078_8};
static const uint8_t ncoords_1078[9] = {2, 2, 2, 18, 5, 7, 5, 7, 2};
static const glyph_stroke_t stroke_1079_0[12] = {{1,12},{0,14},{0,10},{1,12},{2,13},{4,14},{8,14},{11,13},{12,11},{12,10},{11,8},{8,7}};
static const glyph_stroke_t stroke_1079_1[6] = {{8,14},{10,13},{11,11},{11,10},{10,8},{8,7}};
static const glyph_stroke_t stroke_1079_2[14] = {{5,7},{8,7},{11,6},{12,4},{12,3},{11,1},{8,0},{4,0},{1,1},{0,3},{0,4},{1,5},{2,4},{1,3}};
static const glyph_stroke_t stroke_1079_3[6] = {{8,7},{10,6},{11,4},{11,3},{10,1},{8,0}};
static const glyph_stroke_t *strokes_1079[4] = {stroke_1079_0, stroke_1079_1, stroke_1079_2, stroke_1079_3};
static const uint8_t ncoords_1079[4] = {12, 6, 14, 6};
static const glyph_stroke_t stroke_1080_0[2] = {{3,14},{3,0}};
static const glyph_stroke_t stroke_1080_1[2] = {{4,14},{4,0}};
static const glyph_stroke_t stroke_1080_2[2] = {{14,14},{14,0}};
static const glyph_stroke_t stroke_1080_3[2] = {{15,14},{15,0}};
static const glyph_stroke_t stroke_1080_4[2] = {{0,14},{7,14}};
static const glyph_stroke_t stroke_1080_5[2] = {{11,14},{18,14}};
static const glyph_stroke_t stroke_1080_6[2] = {{0,0},{7,0}};
static const glyph_stroke_t stroke_1080_7[2] = {{11,0},{18,0}};
static const glyph_stroke_t stroke_1080_8[2] = {{14,13},{4,1}};
static const glyph_stroke_t *strokes_1080[9] = {stroke_1080_0, stroke_1080_1, stroke_1080_2, stroke_1080_3, stroke_1080_4, stroke_1080_5, stroke_1080_6, stroke_1080_7, stroke_1080_8};
static const uint8_t ncoords_1080[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_1081_0[2] = {{3,14},{3,0}};
static const glyph_stroke_t stroke_1081_1[2] = {{4,14},{4,0}};
static const glyph_stroke_t stroke_1081_2[2] = {{14,14},{14,0}};
static const glyph_stroke_t stroke_1081_3[2] = {{15,14},{15,0}};
static const glyph_stroke_t stroke_1081_4[2] = {{0,14},{7,14}};
static const glyph_stroke_t stroke_1081_5[2] = {{11,14},{18,14}};
static const glyph_stroke_t stroke_1081_6[2] = {{0,0},{7,0}};
static const glyph_stroke_t stroke_1081_7[2] = {{11,0},{18,0}};
static const glyph_stroke_t stroke_1081_8[2] = {{14,13},{4,1}};
static const glyph_stroke_t stroke_1081_9[9] = {{6,20},{6,21},{5,21},{5,20},{6,18},{8,17},{10,17},{12,18},{13,20}};
static const glyph_stroke_t *strokes_1081[10] = {stroke_1081_0, stroke_1081_1, stroke_1081_2, stroke_1081_3, stroke_1081_4, stroke_1081_5, stroke_1081_6, stroke_1081_7, stroke_1081_8, stroke_1081_9};
static const uint8_t ncoords_1081[10] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 9};
static const glyph_stroke_t stroke_1082_0[2] = {{3,14},{3,0}};
static const glyph_stroke_t stroke_1082_1[2] = {{4,14},{4,0}};
static const glyph_stroke_t stroke_1082_2[2] = {{0,14},{7,14}};
static const glyph_stroke_t stroke_1082_3[10] = {{4,7},{6,7},{9,8},{10,9},{12,13},{13,14},{14,14},{15,13},{14,12},{13,13}};
static const glyph_stroke_t stroke_1082_4[5] = {{6,7},{9,6},{10,5},{12,1},{13,0}};
static const glyph_stroke_t stroke_1082_5[8] = {{6,7},{8,6},{9,5},{11,1},{12,0},{14,0},{15,1},{16,3}};
static const glyph_stroke_t stroke_1082_6[2] = {{0,0},{7,0}};
static const glyph_stroke_t *strokes_1082[7] = {stroke_1082_0, stroke_1082_1, stroke_1082_2, stroke_1082_3, stroke_1082_4, stroke_1082_5, stroke_1082_6};
static const uint8_t ncoords_1082[7] = {2, 2, 2, 10, 5, 8, 2};
static const glyph_stroke_t stroke_1083_0[9] = {{5,14},{5,10},{4,4},{3,1},{2,0},{1,0},{0,1},{1,2},{2,1}};
static const glyph_stroke_t stroke_1083_1[2] = {{14,14},{14,0}};
static const glyph_stroke_t stroke_1083_2[2] = {{15,14},{15,0}};
static const glyph_stroke_t stroke_1083_3[2] = {{2,14},{18,14}};
static const glyph_stroke_t stroke_1083_4[2] = {{11,0},{18,0}};
static const glyph_stroke_t *strokes_1083[5] = {stroke_1083_0, stroke_1083_1, stroke_1083_2, stroke_1083_3, stroke_1083_4};
static const uint8_t ncoords_1083[5] = {9, 2, 2, 2, 2};
static const glyph_stroke_t stroke_1084_0[2] = {{3,14},{3,0}};
static const glyph_stroke_t stroke_1084_1[2] = {{3,14},{9,0}};
static const glyph_stroke_t stroke_1084_2[2] = {{4,14},{9,2}};
static const glyph_stroke_t stroke_1084_3[2] = {{15,14},{9,0}};
static const glyph_stroke_t stroke_1084_4[2] = {{15,14},{15,0}};
static const glyph_stroke_t stroke_1084_5[2] = {{16,14},{16,0}};
static const glyph_stroke_t stroke_1084_6[2] = {{0,14},{4,14}};
static const glyph_stroke_t stroke_1084_7[2] = {{15,14},{19,14}};
static const glyph_stroke_t stroke_1084_8[2] = {{0,0},{6,0}};
static const glyph_stroke_t stroke_1084_9[2] = {{12,0},{19,0}};
static const glyph_stroke_t *strokes_1084[10] = {stroke_1084_0, stroke_1084_1, stroke_1084_2, stroke_1084_3, stroke_1084_4, stroke_1084_5, stroke_1084_6, stroke_1084_7, stroke_1084_8, stroke_1084_9};
static const uint8_t ncoords_1084[10] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_1085_0[2] = {{3,14},{3,0}};
static const glyph_stroke_t stroke_1085_1[2] = {{4,14},{4,0}};
static const glyph_stroke_t stroke_1085_2[2] = {{14,14},{14,0}};
static const glyph_stroke_t stroke_1085_3[2] = {{15,14},{15,0}};
static const glyph_stroke_t stroke_1085_4[2] = {{0,14},{7,14}};
static const glyph_stroke_t stroke_1085_5[2] = {{11,14},{18,14}};
static const glyph_stroke_t stroke_1085_6[2] = {{4,7},{14,7}};
static const glyph_stroke_t stroke_1085_7[2] = {{0,0},{7,0}};
static const glyph_stroke_t stroke_1085_8[2] = {{11,0},{18,0}};
static const glyph_stroke_t *strokes_1085[9] = {stroke_1085_0, stroke_1085_1, stroke_1085_2, stroke_1085_3, stroke_1085_4, stroke_1085_5, stroke_1085_6, stroke_1085_7, stroke_1085_8};
static const uint8_t ncoords_1085[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_1086_0[17] = {{6,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{6,0},{8,0},{11,1},{13,3},{14,6},{14,8},{13,11},{11,13},{8,14},{6,14}};
static const glyph_stroke_t stroke_1086_1[8] = {{6,14},{4,13},{2,11},{1,8},{1,6},{2,3},{4,1},{6,0}};
static const glyph_stroke_t stroke_1086_2[8] = {{8,0},{10,1},{12,3},{13,6},{13,8},{12,11},{10,13},{8,14}};
static const glyph_stroke_t *strokes_1086[3] = {stroke_1086_0, stroke_1086_1, stroke_1086_2};
static const uint8_t ncoords_1086[3] = {17, 8, 8};
static const glyph_stroke_t stroke_1087_0[2] = {{3,14},{3,0}};
static const glyph_stroke_t stroke_1087_1[2] = {{4,14},{4,0}};
static const glyph_stroke_t stroke_1087_2[2] = {{14,14},{14,0}};
static const glyph_stroke_t stroke_1087_3[2] = {{15,14},{15,0}};
static const glyph_stroke_t stroke_1087_4[2] = {{0,14},{18,14}};
static const glyph_stroke_t stroke_1087_5[2] = {{0,0},{7,0}};
static const glyph_stroke_t stroke_1087_6[2] = {{11,0},{18,0}};
static const glyph_stroke_t *strokes_1087[7] = {stroke_1087_0, stroke_1087_1, stroke_1087_2, stroke_1087_3, stroke_1087_4, stroke_1087_5, stroke_1087_6};
static const uint8_t ncoords_1087[7] = {2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_1088_0[2] = {{3,14},{3,-7}};
static const glyph_stroke_t stroke_1088_1[2] = {{4,14},{4,-7}};
static const glyph_stroke_t stroke_1088_2[14] = {{4,11},{6,13},{8,14},{10,14},{13,13},{15,11},{16,8},{16,6},{15,3},{13,1},{10,0},{8,0},{6,1},{4,3}};
static const glyph_stroke_t stroke_1088_3[8] = {{10,14},{12,13},{14,11},{15,8},{15,6},{14,3},{12,1},{10,0}};
static const glyph_stroke_t stroke_1088_4[2] = {{0,14},{4,14}};
static const glyph_stroke_t stroke_1088_5[2] = {{0,-7},{7,-7}};
static const glyph_stroke_t *strokes_1088[6] = {stroke_1088_0, stroke_1088_1, stroke_1088_2, stroke_1088_3, stroke_1088_4, stroke_1088_5};
static const uint8_t ncoords_1088[6] = {2, 2, 14, 8, 2, 2};
static const glyph_stroke_t stroke_1089_0[18] = {{12,11},{11,10},{12,9},{13,10},{13,11},{11,13},{9,14},{6,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{6,0},{8,0},{11,1},{13,3}};
static const glyph_stroke_t stroke_1089_1[8] = {{6,14},{4,13},{2,11},{1,8},{1,6},{2,3},{4,1},{6,0}};
static const glyph_stroke_t *strokes_1089[2] = {stroke_1089_0, stroke_1089_1};
static const uint8_t ncoords_1089[2] = {18, 8};
static const glyph_stroke_t stroke_1090_0[2] = {{6,14},{6,0}};
static const glyph_stroke_t stroke_1090_1[2] = {{7,14},{7,0}};
static const glyph_stroke_t stroke_1090_2[6] = {{1,14},{0,9},{0,14},{13,14},{13,9},{12,14}};
static const glyph_stroke_t stroke_1090_3[2] = {{3,0},{10,0}};
static const glyph_stroke_t *strokes_1090[4] = {stroke_1090_0, stroke_1090_1, stroke_1090_2, stroke_1090_3};
static const uint8_t ncoords_1090[4] = {2, 2, 6, 2};
static const glyph_stroke_t stroke_1091_0[2] = {{2,14},{8,0}};
static const glyph_stroke_t stroke_1091_1[2] = {{3,14},{8,2}};
static const glyph_stroke_t stroke_1091_2[9] = {{14,14},{8,0},{6,-4},{4,-6},{2,-7},{1,-7},{0,-6},{1,-5},{2,-6}};
static const glyph_stroke_t stroke_1091_3[2] = {{0,14},{6,14}};
static const glyph_stroke_t stroke_1091_4[2] = {{10,14},{16,14}};
static const glyph_stroke_t *strokes_1091[5] = {stroke_1091_0, stroke_1091_1, stroke_1091_2, stroke_1091_3, stroke_1091_4};
static const uint8_t ncoords_1091[5] = {2, 2, 9, 2, 2};
static const glyph_stroke_t stroke_1092_0[2] = {{7,21},{7,-7}};
static const glyph_stroke_t stroke_1092_1[2] = {{8,21},{8,-7}};
static const glyph_stroke_t stroke_1092_2[2] = {{4,21},{8,21}};
static const glyph_stroke_t stroke_1092_3[12] = {{7,11},{6,13},{5,14},{3,14},{1,13},{0,10},{0,4},{1,1},{3,0},{5,0},{6,1},{7,3}};
static const glyph_stroke_t stroke_1092_4[6] = {{3,14},{2,13},{1,10},{1,4},{2,1},{3,0}};
static const glyph_stroke_t stroke_1092_5[6] = {{12,14},{13,13},{14,10},{14,4},{13,1},{12,0}};
static const glyph_stroke_t stroke_1092_6[12] = {{8,11},{9,13},{10,14},{12,14},{14,13},{15,10},{15,4},{14,1},{12,0},{10,0},{9,1},{8,3}};
static const glyph_stroke_t stroke_1092_7[2] = {{4,-7},{11,-7}};
static const glyph_stroke_t *strokes_1092[8] = {stroke_1092_0, stroke_1092_1, stroke_1092_2, stroke_1092_3, stroke_1092_4, stroke_1092_5, stroke_1092_6, stroke_1092_7};
static const uint8_t ncoords_1092[8] = {2, 2, 2, 12, 6, 6, 12, 2};
static const glyph_stroke_t stroke_1093_0[2] = {{2,14},{13,0}};
static const glyph_stroke_t stroke_1093_1[2] = {{3,14},{14,0}};
static const glyph_stroke_t stroke_1093_2[2] = {{14,14},{2,0}};
static const glyph_stroke_t stroke_1093_3[2] = {{0,14},{6,14}};
static const glyph_stroke_t stroke_1093_4[2] = {{10,14},{16,14}};
static const glyph_stroke_t stroke_1093_5[2] = {{0,0},{6,0}};
static const glyph_stroke_t stroke_1093_6[2] = {{10,0},{16,0}};
static const glyph_stroke_t *strokes_1093[7] = {stroke_1093_0, stroke_1093_1, stroke_1093_2, stroke_1093_3, stroke_1093_4, stroke_1093_5, stroke_1093_6};
static const uint8_t ncoords_1093[7] = {2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_1094_0[2] = {{3,14},{3,0}};
static const glyph_stroke_t stroke_1094_1[2] = {{4,14},{4,0}};
static const glyph_stroke_t stroke_1094_2[2] = {{14,14},{14,0}};
static const glyph_stroke_t stroke_1094_3[2] = {{15,14},{15,0}};
static const glyph_stroke_t stroke_1094_4[2] = {{0,14},{7,14}};
static const glyph_stroke_t stroke_1094_5[2] = {{11,14},{18,14}};
static const glyph_stroke_t stroke_1094_6[4] = {{0,0},{18,0},{18,-5},{17,0}};
static const glyph_stroke_t *strokes_1094[7] = {stroke_1094_0, stroke_1094_1, stroke_1094_2, stroke_1094_3, stroke_1094_4, stroke_1094_5, stroke_1094_6};
static const uint8_t ncoords_1094[7] = {2, 2, 2, 2, 2, 2, 4};
static const glyph_stroke_t stroke_1095_0[7] = {{3,14},{3,7},{4,5},{7,4},{9,4},{12,5},{14,7}};
static const glyph_stroke_t stroke_1095_1[4] = {{4,14},{4,7},{5,5},{7,4}};
static const glyph_stroke_t stroke_1095_2[2] = {{14,14},{14,0}};
static const glyph_stroke_t stroke_1095_3[2] = {{15,14},{15,0}};
static const glyph_stroke_t stroke_1095_4[2] = {{0,14},{7,14}};
static const glyph_stroke_t stroke_1095_5[2] = {{11,14},{18,14}};
static const glyph_stroke_t stroke_1095_6[2] = {{11,0},{18,0}};
static const glyph_stroke_t *strokes_1095[7] = {stroke_1095_0, stroke_1095_1, stroke_1095_2, stroke_1095_3, stroke_1095_4, stroke_1095_5, stroke_1095_6};
static const uint8_t ncoords_1095[7] = {7, 4, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_1096_0[2] = {{3,14},{3,0}};
static const glyph_stroke_t stroke_1096_1[2] = {{4,14},{4,0}};
static const glyph_stroke_t stroke_1096_2[2] = {{13,14},{13,0}};
static const glyph_stroke_t stroke_1096_3[2] = {{14,14},{14,0}};
static const glyph_stroke_t stroke_1096_4[2] = {{23,14},{23,0}};
static const glyph_stroke_t stroke_1096_5[2] = {{24,14},{24,0}};
static const glyph_stroke_t stroke_1096_6[2] = {{0,14},{7,14}};
static const glyph_stroke_t stroke_1096_7[2] = {{10,14},{17,14}};
static const glyph_stroke_t stroke_1096_8[2] = {{20,14},{27,14}};
static const glyph_stroke_t stroke_1096_9[2] = {{0,0},{27,0}};
static const glyph_stroke_t *strokes_1096[10] = {stroke_1096_0, stroke_1096_1, stroke_1096_2, stroke_1096_3, stroke_1096_4, stroke_1096_5, stroke_1096_6, stroke_1096_7, stroke_1096_8, stroke_1096_9};
static const uint8_t ncoords_1096[10] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
static const glyph_stroke_t stroke_1097_0[2] = {{3,14},{3,0}};
static const glyph_stroke_t stroke_1097_1[2] = {{4,14},{4,0}};
static const glyph_stroke_t stroke_1097_2[2] = {{13,14},{13,0}};
static const glyph_stroke_t stroke_1097_3[2] = {{14,14},{14,0}};
static const glyph_stroke_t stroke_1097_4[2] = {{23,14},{23,0}};
static const glyph_stroke_t stroke_1097_5[2] = {{24,14},{24,0}};
static const glyph_stroke_t stroke_1097_6[2] = {{0,14},{7,14}};
static const glyph_stroke_t stroke_1097_7[2] = {{10,14},{17,14}};
static const glyph_stroke_t stroke_1097_8[2] = {{20,14},{27,14}};
static const glyph_stroke_t stroke_1097_9[4] = {{0,0},{27,0},{27,-5},{26,0}};
static const glyph_stroke_t *strokes_1097[10] = {stroke_1097_0, stroke_1097_1, stroke_1097_2, stroke_1097_3, stroke_1097_4, stroke_1097_5, stroke_1097_6, stroke_1097_7, stroke_1097_8, stroke_1097_9};
static const uint8_t ncoords_1097[10] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 4};
static const glyph_stroke_t stroke_1098_0[2] = {{6,14},{6,0}};
static const glyph_stroke_t stroke_1098_1[2] = {{7,14},{7,0}};
static const glyph_stroke_t stroke_1098_2[4] = {{1,14},{0,9},{0,14},{10,14}};
static const glyph_stroke_t stroke_1098_3[8] = {{7,7},{11,7},{14,6},{15,4},{15,3},{14,1},{11,0},{3,0}};
static const glyph_stroke_t stroke_1098_4[6] = {{11,7},{13,6},{14,4},{14,3},{13,1},{11,0}};
static const glyph_stroke_t *strokes_1098[5] = {stroke_1098_0, stroke_1098_1, stroke_1098_2, stroke_1098_3, stroke_1098_4};
static const uint8_t ncoords_1098[5] = {2, 2, 4, 8, 6};
static const glyph_stroke_t stroke_1099_0[2] = {{3,14},{3,0}};
static const glyph_stroke_t stroke_1099_1[2] = {{4,14},{4,0}};
static const glyph_stroke_t stroke_1099_2[2] = {{0,14},{7,14}};
static const glyph_stroke_t stroke_1099_3[8] = {{4,7},{8,7},{11,6},{12,4},{12,3},{11,1},{8,0},{0,0}};
static const glyph_stroke_t stroke_1099_4[6] = {{8,7},{10,6},{11,4},{11,3},{10,1},{8,0}};
static const glyph_stroke_t stroke_1099_5[2] = {{18,14},{18,0}};
static const glyph_stroke_t stroke_1099_6[2] = {{19,14},{19,0}};
static const glyph_stroke_t stroke_1099_7[2] = {{15,14},{22,14}};
static const glyph_stroke_t stroke_1099_8[2] = {{15,0},{22,0}};
static const glyph_stroke_t *strokes_1099[9] = {stroke_1099_0, stroke_1099_1, stroke_1099_2, stroke_1099_3, stroke_1099_4, stroke_1099_5, stroke_1099_6, stroke_1099_7, stroke_1099_8};
static const uint8_t ncoords_1099[9] = {2, 2, 2, 8, 6, 2, 2, 2, 2};
static const glyph_stroke_t stroke_1100_0[2] = {{3,14},{3,0}};
static const glyph_stroke_t stroke_1100_1[2] = {{4,14},{4,0}};
static const glyph_stroke_t stroke_1100_2[2] = {{0,14},{7,14}};
static const glyph_stroke_t stroke_1100_3[8] = {{4,7},{8,7},{11,6},{12,4},{12,3},{11,1},{8,0},{0,0}};
static const glyph_stroke_t stroke_1100_4[6] = {{8,7},{10,6},{11,4},{11,3},{10,1},{8,0}};
static const glyph_stroke_t *strokes_1100[5] = {stroke_1100_0, stroke_1100_1, stroke_1100_2, stroke_1100_3, stroke_1100_4};
static const uint8_t ncoords_1100[5] = {2, 2, 2, 8, 6};
static const glyph_stroke_t stroke_1101_0[24] = {{1,18},{0,21},{0,15},{1,18},{3,20},{6,21},{8,21},{11,20},{13,18},{14,16},{15,13},{15,8},{14,5},{13,3},{11,1},{8,0},{5,0},{2,1},{1,2},{0,4},{0,5},{1,6},{2,5},{1,4}};
static const glyph_stroke_t stroke_1101_1[10] = {{8,21},{10,20},{12,18},{13,16},{14,13},{14,8},{13,5},{12,3},{10,1},{8,0}};
static const glyph_stroke_t stroke_1101_2[2] = {{5,11},{14,11}};
static const glyph_stroke_t *strokes_1101[3] = {stroke_1101_0, stroke_1101_1, stroke_1101_2};
static const uint8_t ncoords_1101[3] = {24, 10, 2};
static const glyph_stroke_t stroke_1102_0[2] = {{3,14},{3,0}};
static const glyph_stroke_t stroke_1102_1[2] = {{4,14},{4,0}};
static const glyph_stroke_t stroke_1102_2[2] = {{0,14},{7,14}};
static const glyph_stroke_t stroke_1102_3[2] = {{0,0},{7,0}};
static const glyph_stroke_t stroke_1102_4[17] = {{16,14},{13,13},{11,11},{10,8},{10,6},{11,3},{13,1},{16,0},{18,0},{21,1},{23,3},{24,6},{24,8},{23,11},{21,13},{18,14},{16,14}};
static const glyph_stroke_t stroke_1102_5[8] = {{16,14},{14,13},{12,11},{11,8},{11,6},{12,3},{14,1},{16,0}};
static const glyph_stroke_t stroke_1102_6[8] = {{18,0},{20,1},{22,3},{23,6},{23,8},{22,11},{20,13},{18,14}};
static const glyph_stroke_t stroke_1102_7[2] = {{4,7},{10,7}};
static const glyph_stroke_t *strokes_1102[8] = {stroke_1102_0, stroke_1102_1, stroke_1102_2, stroke_1102_3, stroke_1102_4, stroke_1102_5, stroke_1102_6, stroke_1102_7};
static const uint8_t ncoords_1102[8] = {2, 2, 2, 2, 17, 8, 8, 2};
static const glyph_stroke_t stroke_1103_0[2] = {{12,14},{12,0}};
static const glyph_stroke_t stroke_1103_1[2] = {{13,14},{13,0}};
static const glyph_stroke_t stroke_1103_2[8] = {{16,14},{5,14},{2,13},{1,11},{1,10},{2,8},{5,7},{12,7}};
static const glyph_stroke_t stroke_1103_3[6] = {{5,14},{3,13},{2,11},{2,10},{3,8},{5,7}};
static const glyph_stroke_t stroke_1103_4[5] = {{10,7},{7,6},{6,5},{4,1},{3,0}};
static const glyph_stroke_t stroke_1103_5[8] = {{10,7},{8,6},{7,5},{5,1},{4,0},{2,0},{1,1},{0,3}};
static const glyph_stroke_t stroke_1103_6[2] = {{9,0},{16,0}};
static const glyph_stroke_t *strokes_1103[7] = {stroke_1103_0, stroke_1103_1, stroke_1103_2, stroke_1103_3, stroke_1103_4, stroke_1103_5, stroke_1103_6};
static const uint8_t ncoords_1103[7] = {2, 2, 8, 6, 5, 8, 2};
static const glyph_data_t glyph_data[224] = {
	{ 0x00000020, 0, 0, 0, 0, -6, 6, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x00000021, 0, 0, 2, 21, -4, 6, 0, 3, strokes_33, ncoords_33 },
	{ 0x00000022, 0, 14, 11, 21, -4, 14, 0, 6, strokes_34, ncoords_34 },
	{ 0x00000023, 0, -7, 15, 25, -3, 18, 0, 4, strokes_35, ncoords_35 },
	{ 0x00000024, 0, -4, 14, 25, -3, 17, 0, 4, strokes_36, ncoords_36 },
	{ 0x00000025, 0, 0, 18, 21, -3, 21, 0, 3, strokes_37, ncoords_37 },
	{ 0x00000026, 0, 0, 19, 21, -3, 22, 0, 3, strokes_38, ncoords_38 },
	{ 0x00000027, 0, 14, 2, 21, -3, 5, 0, 2, strokes_39, ncoords_39 },
	{ 0x00000028, 0, -7, 7, 25, -4, 10, 0, 2, strokes_40, ncoords_40 },
	{ 0x00000029, 0, -7, 7, 25, -3, 11, 0, 2, strokes_41, ncoords_41 },
	{ 0x0000002a, 0, 3, 10, 15, -3, 13, 0, 3, strokes_42, ncoords_42 },
	{ 0x0000002b, 0, 0, 18, 18, -4, 22, 0, 2, strokes_43, ncoords_43 },
	{ 0x0000002c, 0, -3, 2, 2, -3, 5, 0, 1, strokes_44, ncoords_44 },
	{ 0x0000002d, 0, 9, 12, 9, -3, 15, 0, 1, strokes_45, ncoords_45 },
	{ 0x0000002e, 0, 0, 2, 2, -3, 5, 0, 1, strokes_46, ncoords_46 },
	{ 0x0000002f, 0, -7, 18, 25, -2, 20, 0, 1, strokes_47, ncoords_47 },
	{ 0x00000030, 0, 0, 14, 21, -3, 17, 0, 3, strokes_48, ncoords_48 },
	{ 0x00000031, 0, 0, 9, 21, -6, 14, 0, 3, strokes_49, ncoords_49 },
	{ 0x00000032, 0, 0, 14, 21, -3, 17, 0, 4, strokes_50, ncoords_50 },
	{ 0x00000033, 0, 0, 14, 21, -3, 17, 0, 4, strokes_51, ncoords_51 },
	{ 0x00000034, 0, 0, 16, 21, -2, 18, 0, 4, strokes_52, ncoords_52 },
	{ 0x00000035, 0, 0, 14, 21, -3, 17, 0, 5, strokes_53, ncoords_53 },
	{ 0x00000036, 0, 0, 14, 21, -3, 17, 0, 3, strokes_54, ncoords_54 },
	{ 0x00000037, 0, 0, 14, 21, -3, 17, 0, 5, strokes_55, ncoords_55 },
	{ 0x00000038, 0, 0, 14, 21, -3, 17, 0, 6, strokes_56, ncoords_56 },
	{ 0x00000039, 0, 0, 14, 21, -3, 17, 0, 3, strokes_57, ncoords_57 },
	{ 0x0000003a, 0, 0, 2, 9, -3, 5, 0, 2, strokes_58, ncoords_58 },
	{ 0x0000003b, 0, 0, 2, 12, -3, 5, 0, 2, strokes_59, ncoords_59 },
	{ 0x0000003c, 0, 0, 16, 18, -4, 20, 0, 1, strokes_60, ncoords_60 },
	{ 0x0000003d, 0, 6, 18, 12, -4, 22, 0, 2, strokes_61, ncoords_61 },
	{ 0x0000003e, 0, 0, 16, 18, -4, 20, 0, 1, strokes_62, ncoords_62 },
	{ 0x0000003f, 0, 0, 12, 21, -3, 15, 0, 3, strokes_63, ncoords_63 },
	{ 0x00000040, 0, 0, 21, 21, -3, 24, 0, 4, strokes_64, ncoords_64 },
	{ 0x00000041, 0, 0, 18, 21, -1, 19, 0, 6, strokes_65, ncoords_65 },
	{ 0x00000042, 0, 0, 17, 21, -2, 20, 0, 6, strokes_66, ncoords_66 },
	{ 0x00000043, 0, 0, 15, 21, -3, 18, 0, 2, strokes_67, ncoords_67 },
	{ 0x00000044, 0, 0, 17, 21, -2, 20, 0, 4, strokes_68, ncoords_68 },
	{ 0x00000045, 0, 0, 16, 21, -2, 19, 0, 6, strokes_69, ncoords_69 },
	{ 0x00000046, 0, 0, 16, 21, -2, 18, 0, 6, strokes_70, ncoords_70 },
	{ 0x00000047, 0, 0, 18, 21, -3, 20, 0, 5, strokes_71, ncoords_71 },
	{ 0x00000048, 0, 0, 20, 21, -2, 22, 0, 9, strokes_72, ncoords_72 },
	{ 0x00000049, 0, 0, 7, 21, -2, 9, 0, 4, strokes_73, ncoords_73 },
	{ 0x0000004a, 0, 0, 11, 21, -2, 13, 0, 3, strokes_74, ncoords_74 },
	{ 0x0000004b, 0, 0, 19, 21, -2, 20, 0, 9, strokes_75, ncoords_75 },
	{ 0x0000004c, 0, 0, 15, 21, -2, 16, 0, 4, strokes_76, ncoords_76 },
	{ 0x0000004d, 0, 0, 21, 21, -2, 23, 0, 10, strokes_77, ncoords_77 },
	{ 0x0000004e, 0, 0, 19, 21, -2, 21, 0, 7, strokes_78, ncoords_78 },
	{ 0x0000004f, 0, 0, 16, 21, -3, 19, 0, 3, strokes_79, ncoords_79 },
	{ 0x00000050, 0, 0, 17, 21, -2, 20, 0, 5, strokes_80, ncoords_80 },
	{ 0x00000051, 0, -5, 16, 21, -3, 19, 0, 5, strokes_81, ncoords_81 },
	{ 0x00000052, 0, 0, 18, 21, -2, 20, 0, 7, strokes_82, ncoords_82 },
	{ 0x00000053, 0, 0, 14, 21, -3, 17, 0, 2, strokes_83, ncoords_83 },
	{ 0x00000054, 0, 0, 15, 21, -2, 17, 0, 4, strokes_84, ncoords_84 },
	{ 0x00000055, 0, 0, 20, 21, -2, 22, 0, 4, strokes_85, ncoords_85 },
	{ 0x00000056, 0, 0, 18, 21, -1, 19, 0, 5, strokes_86, ncoords_86 },
	{ 0x00000057, 0, 0, 22, 21, -1, 23, 0, 8, strokes_87, ncoords_87 },
	{ 0x00000058, 0, 0, 18, 21, -1, 19, 0, 7, strokes_88, ncoords_88 },
	{ 0x00000059, 0, 0, 19, 21, -1, 20, 0, 6, strokes_89, ncoords_89 },
	{ 0x0000005a, 0, 0, 14, 21, -3, 17, 0, 4, strokes_90, ncoords_90 },
	{ 0x0000005b, 0, -7, 7, 25, -4, 10, 0, 4, strokes_91, ncoords_91 },
	{ 0x0000005c, 0, -3, 14, 21, 0, 14, 0, 1, strokes_92, ncoords_92 },
	{ 0x0000005d, 0, -7, 7, 25, -3, 11, 0, 4, strokes_93, ncoords_93 },
	{ 0x0000005e, 0, 7, 16, 12, -3, 19, 0, 2, strokes_94, ncoords_94 },
	{ 0x0000005f, 0, -7, 20, -7, 0, 20, 0, 1, strokes_95, ncoords_95 },
	{ 0x00000060, 0, 15, 6, 21, -3, 9, 0, 2, strokes_96, ncoords_96 },
	{ 0x00000061, 0, 0, 15, 14, -3, 17, 0, 4, strokes_97, ncoords_97 },
	{ 0x00000062, 0, 0, 16, 21, -2, 19, 0, 5, strokes_98, ncoords_98 },
	{ 0x00000063, 0, 0, 13, 14, -3, 16, 0, 2, strokes_99, ncoords_99 },
	{ 0x00000064, 0, 0, 16, 21, -3, 18, 0, 6, strokes_100, ncoords_100 },
	{ 0x00000065, 0, 0, 13, 14, -3, 16, 0, 3, strokes_101, ncoords_101 },
	{ 0x00000066, 0, 0, 9, 21, -2, 11, 0, 4, strokes_102, ncoords_102 },
	{ 0x00000067, 0, -7, 14, 14, -2, 17, 0, 6, strokes_103, ncoords_103 },
	{ 0x00000068, 0, 0, 18, 21, -2, 20, 0, 7, strokes_104, ncoords_104 },
	{ 0x00000069, 0, 0, 7, 21, -2, 9, 0, 5, strokes_105, ncoords_105 },
	{ 0x0000006a, 0, -7, 6, 21, -1, 10, 0, 4, strokes_106, ncoords_106 },
	{ 0x0000006b, 0, 0, 17, 21, -2, 19, 0, 9, strokes_107, ncoords_107 },
	{ 0x0000006c, 0, 0, 7, 21, -2, 9, 0, 4, strokes_108, ncoords_108 },
	{ 0x0000006d, 0, 0, 29, 14, -2, 31, 0, 10, strokes_109, ncoords_109 },
	{ 0x0000006e, 0, 0, 18, 14, -2, 20, 0, 7, strokes_110, ncoords_110 },
	{ 0x0000006f, 0, 0, 14, 14, -3, 17, 0, 3, strokes_111, ncoords_111 },
	{ 0x00000070, 0, -7, 16, 14, -2, 19, 0, 6, strokes_112, ncoords_112 },
	{ 0x00000071, 0, -7, 16, 14, -3, 17, 0, 5, strokes_113, ncoords_113 },
	{ 0x00000072, 0, 0, 13, 14, -2, 15, 0, 5, strokes_114, ncoords_114 },
	{ 0x00000073, 0, 0, 11, 14, -3, 14, 0, 2, strokes_115, ncoords_115 },
	{ 0x00000074, 0, 0, 11, 21, -2, 13, 0, 3, strokes_116, ncoords_116 },
	{ 0x00000075, 0, 0, 18, 14, -2, 20, 0, 7, strokes_117, ncoords_117 },
	{ 0x00000076, 0, 0, 16, 14, -1, 17, 0, 5, strokes_118, ncoords_118 },
	{ 0x00000077, 0, 0, 22, 14, -1, 23, 0, 8, strokes_119, ncoords_119 },
	{ 0x00000078, 0, 0, 16, 14, -2, 18, 0, 7, strokes_120, ncoords_120 },
	{ 0x00000079, 0, -7, 16, 14, -2, 17, 0, 5, strokes_121, ncoords_121 },
	{ 0x0000007a, 0, 0, 12, 14, -3, 15, 0, 4, strokes_122, ncoords_122 },
	{ 0x0000007b, 0, -7, 5, 25, -4, 10, 0, 3, strokes_123, ncoords_123 },
	{ 0x0000007c, 0, -7, 0, 25, -4, 4, 0, 1, strokes_124, ncoords_124 },
	{ 0x0000007d, 0, -7, 5, 25, -5, 9, 0, 3, strokes_125, ncoords_125 },
	{ 0x0000007e, 0, 6, 18, 12, -3, 21, 0, 2, strokes_126, ncoords_126 },
	{ 0x0000007f, 0, 0, 16, 21, 0, 16, 0, 1, strokes_127, ncoords_127 },
	{ 0x000000c5, 0, 0, 16, 14, -1, 19, 0, 3, strokes_197, ncoords_197 },
	{ 0x00000391, 0, 0, 18, 21, -1, 19, 0, 6, strokes_913, ncoords_913 },
	{ 0x00000392, 0, 0, 17, 21, -2, 20, 0, 6, strokes_914, ncoords_914 },
	{ 0x00000393, 0, 0, 15, 21, -2, 16, 0, 4, strokes_915, ncoords_915 },
	{ 0x00000394, 0, 0, 16, 21, -2, 18, 0, 5, strokes_916, ncoords_916 },
	{ 0x00000395, 0, 0, 16, 21, -2, 19, 0, 6, strokes_917, ncoords_917 },
	{ 0x00000396, 0, 0, 14, 21, -3, 17, 0, 4, strokes_918, ncoords_918 },
	{ 0x00000397, 0, 0, 20, 21, -2, 22, 0, 9, strokes_919, ncoords_919 },
	{ 0x00000398, 0, 0, 16, 21, -3, 19, 0, 7, strokes_920, ncoords_920 },
	{ 0x00000399, 0, 0, 7, 21, -2, 9, 0, 4, strokes_921, ncoords_921 },
	{ 0x0000039a, 0, 0, 19, 21, -2, 20, 0, 9, strokes_922, ncoords_922 },
	{ 0x0000039b, 0, 0, 18, 21, -1, 19, 0, 5, strokes_923, ncoords_923 },
	{ 0x0000039c, 0, 0, 21, 21, -2, 23, 0, 10, strokes_924, ncoords_924 },
	{ 0x0000039d, 0, 0, 19, 21, -2, 21, 0, 7, strokes_925, ncoords_925 },
	{ 0x0000039e, 0, -1, 16, 22, -3, 19, 0, 12, strokes_926, ncoords_926 },
	{ 0x0000039f, 0, 0, 16, 21, -3, 19, 0, 3, strokes_927, ncoords_927 },
	{ 0x000003a0, 0, 0, 20, 21, -2, 22, 0, 7, strokes_928, ncoords_928 },
	{ 0x000003a1, 0, 0, 17, 21, -2, 20, 0, 5, strokes_929, ncoords_929 },
	{ 0x000003a3, 0, 0, 16, 21, -2, 19, 0, 5, strokes_931, ncoords_931 },
	{ 0x000003a4, 0, 0, 15, 21, -2, 17, 0, 4, strokes_932, ncoords_932 },
	{ 0x000003a5, 0, 0, 15, 21, -2, 17, 0, 5, strokes_933, ncoords_933 },
	{ 0x000003a6, 0, 0, 15, 21, -3, 18, 0, 7, strokes_934, ncoords_934 },
	{ 0x000003a7, 0, 0, 18, 21, -1, 19, 0, 7, strokes_935, ncoords_935 },
	{ 0x000003a8, 0, 0, 19, 21, -2, 21, 0, 7, strokes_936, ncoords_936 },
	{ 0x000003a9, 0, 0, 16, 21, -3, 19, 0, 5, strokes_937, ncoords_937 },
	{ 0x000003b1, 0, 0, 17, 14, -3, 20, 0, 4, strokes_945, ncoords_945 },
	{ 0x000003b2, 0, -7, 16, 21, -2, 19, 0, 6, strokes_946, ncoords_946 },
	{ 0x000003b3, 0, -7, 17, 14, -1, 19, 0, 4, strokes_947, ncoords_947 },
	{ 0x000003b4, 0, 0, 13, 22, -3, 16, 0, 3, strokes_948, ncoords_948 },
	{ 0x000003b5, 0, 0, 12, 14, -3, 15, 0, 4, strokes_949, ncoords_949 },
	{ 0x000003b6, 0, -7, 14, 21, -3, 15, 0, 2, strokes_950, ncoords_950 },
	{ 0x000003b7, 0, -7, 17, 14, -1, 21, 0, 4, strokes_951, ncoords_951 },
	{ 0x000003b8, 0, 0, 19, 21, -1, 22, 0, 3, strokes_952, ncoords_952 },
	{ 0x000003b9, 0, 0, 7, 14, -3, 9, 0, 2, strokes_953, ncoords_953 },
	{ 0x000003ba, 0, 0, 16, 14, -2, 18, 0, 5, strokes_954, ncoords_954 },
	{ 0x000003bb, 0, 0, 16, 21, -2, 18, 0, 4, strokes_955, ncoords_955 },
	{ 0x000003bc, 0, -7, 21, 14, -1, 22, 0, 5, strokes_956, ncoords_956 },
	{ 0x000003bd, 0, 0, 15, 14, -3, 17, 0, 5, strokes_957, ncoords_957 },
	{ 0x000003be, 0, -7, 12, 21, -3, 14, 0, 5, strokes_958, ncoords_958 },
	{ 0x000003bf, 0, 0, 12, 14, -3, 15, 0, 3, strokes_959, ncoords_959 },
	{ 0x000003c0, 0, 0, 18, 14, -2, 20, 0, 6, strokes_960, ncoords_960 },
	{ 0x000003c1, 0, -7, 16, 14, 0, 19, 0, 3, strokes_961, ncoords_961 },
	{ 0x000003c3, 0, 0, 16, 14, -3, 18, 0, 4, strokes_963, ncoords_963 },
	{ 0x000003c4, 0, 0, 16, 14, -2, 18, 0, 4, strokes_964, ncoords_964 },
	{ 0x000003c6, 0, -7, 16, 14, -3, 19, 0, 3, strokes_966, ncoords_966 },
	{ 0x000003c7, 0, -7, 16, 14, -1, 17, 0, 3, strokes_967, ncoords_967 },
	{ 0x000003c8, 0, -7, 20, 21, -1, 22, 0, 4, strokes_968, ncoords_968 },
	{ 0x000003c9, 0, 0, 17, 14, -3, 20, 0, 4, strokes_969, ncoords_969 },
	{ 0x00000410, 0, 0, 18, 21, -1, 19, 0, 6, strokes_1040, ncoords_1040 },
	{ 0x00000411, 0, 0, 17, 21, -2, 20, 0, 5, strokes_1041, ncoords_1041 },
	{ 0x00000412, 0, 0, 17, 21, -2, 20, 0, 6, strokes_1042, ncoords_1042 },
	{ 0x00000413, 0, 0, 15, 21, -2, 16, 0, 4, strokes_1043, ncoords_1043 },
	{ 0x00000414, 0, -7, 21, 21, -1, 23, 0, 9, strokes_1044, ncoords_1044 },
	{ 0x00000415, 0, 0, 16, 21, -2, 19, 0, 6, strokes_1045, ncoords_1045 },
	{ 0x00000416, 0, 0, 27, 21, -2, 29, 0, 9, strokes_1046, ncoords_1046 },
	{ 0x00000417, 0, 0, 14, 21, -3, 17, 0, 4, strokes_1047, ncoords_1047 },
	{ 0x00000418, 0, 0, 20, 21, -2, 22, 0, 9, strokes_1048, ncoords_1048 },
	{ 0x00000419, 0, 0, 20, 27, -2, 22, 0, 10, strokes_1049, ncoords_1049 },
	{ 0x0000041a, 0, 0, 20, 21, -2, 22, 0, 7, strokes_1050, ncoords_1050 },
	{ 0x0000041b, 0, 0, 21, 21, -2, 23, 0, 5, strokes_1051, ncoords_1051 },
	{ 0x0000041c, 0, 0, 21, 21, -2, 23, 0, 10, strokes_1052, ncoords_1052 },
	{ 0x0000041d, 0, 0, 20, 21, -2, 22, 0, 9, strokes_1053, ncoords_1053 },
	{ 0x0000041e, 0, 0, 16, 21, -3, 19, 0, 3, strokes_1054, ncoords_1054 },
	{ 0x0000041f, 0, 0, 20, 21, -2, 22, 0, 7, strokes_1055, ncoords_1055 },
	{ 0x00000420, 0, 0, 17, 21, -2, 20, 0, 5, strokes_1056, ncoords_1056 },
	{ 0x00000421, 0, 0, 15, 21, -3, 18, 0, 2, strokes_1057, ncoords_1057 },
	{ 0x00000422, 0, 0, 15, 21, -2, 17, 0, 4, strokes_1058, ncoords_1058 },
	{ 0x00000423, 0, 0, 19, 21, -1, 20, 0, 5, strokes_1059, ncoords_1059 },
	{ 0x00000424, 0, 0, 19, 21, -3, 22, 0, 7, strokes_1060, ncoords_1060 },
	{ 0x00000425, 0, 0, 18, 21, -1, 19, 0, 7, strokes_1061, ncoords_1061 },
	{ 0x00000426, 0, -7, 20, 21, -2, 22, 0, 9, strokes_1062, ncoords_1062 },
	{ 0x00000427, 0, 0, 19, 21, -2, 21, 0, 7, strokes_1063, ncoords_1063 },
	{ 0x00000428, 0, 0, 29, 21, -2, 31, 0, 10, strokes_1064, ncoords_1064 },
	{ 0x00000429, 0, -7, 29, 21, -2, 31, 0, 12, strokes_1065, ncoords_1065 },
	{ 0x0000042a, 0, 0, 21, 21, -2, 24, 0, 5, strokes_1066, ncoords_1066 },
	{ 0x0000042b, 0, 0, 26, 21, -2, 28, 0, 9, strokes_1067, ncoords_1067 },
	{ 0x0000042c, 0, 0, 16, 21, -2, 19, 0, 5, strokes_1068, ncoords_1068 },
	{ 0x0000042d, 0, 0, 15, 21, -3, 18, 0, 3, strokes_1069, ncoords_1069 },
	{ 0x0000042e, 0, 0, 26, 21, -2, 29, 0, 8, strokes_1070, ncoords_1070 },
	{ 0x0000042f, 0, 0, 18, 21, -2, 20, 0, 7, strokes_1071, ncoords_1071 },
	{ 0x00000430, 0, 0, 15, 14, -3, 17, 0, 4, strokes_1072, ncoords_1072 },
	{ 0x00000431, 0, 0, 14, 21, -3, 17, 0, 4, strokes_1073, ncoords_1073 },
	{ 0x00000432, 0, 0, 15, 14, -2, 18, 0, 6, strokes_1074, ncoords_1074 },
	{ 0x00000433, 0, 0, 14, 14, -2, 16, 0, 4, strokes_1075, ncoords_1075 },
	{ 0x00000434, 0, -5, 19, 14, -2, 21, 0, 5, strokes_1076, ncoords_1076 },
	{ 0x00000435, 0, 0, 13, 14, -3, 16, 0, 3, strokes_1077, ncoords_1077 },
	{ 0x00000436, 0, 0, 23, 14, -2, 25, 0, 9, strokes_1078, ncoords_1078 },
	{ 0x00000437, 0, 0, 12, 14, -3, 15, 0, 4, strokes_1079, ncoords_1079 },
	{ 0x00000438, 0, 0, 18, 14, -2, 20, 0, 9, strokes_1080, ncoords_1080 },
	{ 0x00000439, 0, 0, 18, 21, -2, 20, 0, 10, strokes_1081, ncoords_1081 },
	{ 0x0000043a, 0, 0, 16, 14, -2, 18, 0, 7, strokes_1082, ncoords_1082 },
	{ 0x0000043b, 0, 0, 18, 14, -2, 20, 0, 5, strokes_1083, ncoords_1083 },
	{ 0x0000043c, 0, 0, 19, 14, -2, 21, 0, 10, strokes_1084, ncoords_1084 },
	{ 0x0000043d, 0, 0, 18, 14, -2, 20, 0, 9, strokes_1085, ncoords_1085 },
	{ 0x0000043e, 0, 0, 14, 14, -3, 17, 0, 3, strokes_1086, ncoords_1086 },
	{ 0x0000043f, 0, 0, 18, 14, -2, 20, 0, 7, strokes_1087, ncoords_1087 },
	{ 0x00000440, 0, -7, 16, 14, -2, 19, 0, 6, strokes_1088, ncoords_1088 },
	{ 0x00000441, 0, 0, 13, 14, -3, 16, 0, 2, strokes_1089, ncoords_1089 },
	{ 0x00000442, 0, 0, 13, 14, -3, 16, 0, 4, strokes_1090, ncoords_1090 },
	{ 0x00000443, 0, -7, 16, 14, -1, 17, 0, 5, strokes_1091, ncoords_1091 },
	{ 0x00000444, 0, -7, 15, 21, -3, 18, 0, 8, strokes_1092, ncoords_1092 },
	{ 0x00000445, 0, 0, 16, 14, -2, 18, 0, 7, strokes_1093, ncoords_1093 },
	{ 0x00000446, 0, -5, 18, 14, -2, 20, 0, 7, strokes_1094, ncoords_1094 },
	{ 0x00000447, 0, 0, 18, 14, -2, 20, 0, 7, strokes_1095, ncoords_1095 },
	{ 0x00000448, 0, 0, 27, 14, -2, 29, 0, 10, strokes_1096, ncoords_1096 },
	{ 0x00000449, 0, -5, 27, 14, -2, 29, 0, 10, strokes_1097, ncoords_1097 },
	{ 0x0000044a, 0, 0, 15, 14, -3, 18, 0, 5, strokes_1098, ncoords_1098 },
	{ 0x0000044b, 0, 0, 22, 14, -2, 24, 0, 9, strokes_1099, ncoords_1099 },
	{ 0x0000044c, 0, 0, 12, 14, -2, 15, 0, 5, strokes_1100, ncoords_1100 },
	{ 0x0000044d, 0, 0, 15, 21, -3, 18, 0, 3, strokes_1101, ncoords_1101 },
	{ 0x0000044e, 0, 0, 24, 14, -2, 27, 0, 8, strokes_1102, ncoords_1102 },
	{ 0x0000044f, 0, 0, 16, 14, -3, 18, 0, 7, strokes_1103, ncoords_1103 },
	{ 0x0000e390, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e3a9, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e3aa, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e3ab, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e3ac, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e3ad, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e3ae, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e3af, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e3b0, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e3ca, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e3cb, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e3cc, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e3cd, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e3ce, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e3cf, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e3d0, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 }
};
const font_data_t font_htimes = {
	"Hershey Times regular",
	21,
	224,
	glyph_data
};
