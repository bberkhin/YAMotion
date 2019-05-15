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

static const glyph_stroke_t stroke_33_0[5] = {{1,2},{0,1},{1,0},{2,1},{1,2}};
static const glyph_stroke_t stroke_33_1[2] = {{1,7},{1,21}};
static const glyph_stroke_t *strokes_33[2] = {stroke_33_0, stroke_33_1};
static const uint8_t ncoords_33[2] = {5, 2};
static const glyph_stroke_t stroke_34_0[2] = {{0,14},{0,21}};
static const glyph_stroke_t stroke_34_1[2] = {{8,21},{8,14}};
static const glyph_stroke_t *strokes_34[2] = {stroke_34_0, stroke_34_1};
static const uint8_t ncoords_34[2] = {2, 2};
static const glyph_stroke_t stroke_35_0[2] = {{1,-7},{8,25}};
static const glyph_stroke_t stroke_35_1[2] = {{14,25},{7,-7}};
static const glyph_stroke_t stroke_35_2[2] = {{15,12},{1,12}};
static const glyph_stroke_t stroke_35_3[2] = {{0,6},{14,6}};
static const glyph_stroke_t *strokes_35[4] = {stroke_35_0, stroke_35_1, stroke_35_2, stroke_35_3};
static const uint8_t ncoords_35[4] = {2, 2, 2, 2};
static const glyph_stroke_t stroke_36_0[20] = {{0,3},{2,1},{5,0},{9,0},{12,1},{14,3},{14,6},{13,8},{12,9},{10,10},{4,12},{2,13},{1,14},{0,16},{0,18},{2,20},{5,21},{9,21},{12,20},{14,18}};
static const glyph_stroke_t stroke_36_1[2] = {{9,25},{9,-4}};
static const glyph_stroke_t stroke_36_2[2] = {{5,-4},{5,25}};
static const glyph_stroke_t *strokes_36[3] = {stroke_36_0, stroke_36_1, stroke_36_2};
static const uint8_t ncoords_36[3] = {20, 2, 2};
static const glyph_stroke_t stroke_37_0[17] = {{0,0},{18,21},{16,20},{13,19},{10,19},{7,20},{5,21},{3,21},{1,20},{0,18},{0,16},{2,14},{4,14},{6,15},{7,17},{7,19},{5,21}};
static const glyph_stroke_t stroke_37_1[11] = {{14,7},{12,6},{11,4},{11,2},{13,0},{15,0},{17,1},{18,3},{18,5},{16,7},{14,7}};
static const glyph_stroke_t *strokes_37[2] = {stroke_37_0, stroke_37_1};
static const uint8_t ncoords_37[2] = {17, 11};
static const glyph_stroke_t stroke_38_0[34] = {{20,12},{20,13},{19,14},{18,14},{17,13},{16,11},{14,6},{12,3},{10,1},{8,0},{4,0},{2,1},{1,2},{0,4},{0,6},{1,8},{2,9},{9,13},{10,14},{11,16},{11,18},{10,20},{8,21},{6,20},{5,18},{5,16},{6,13},{8,10},{13,3},{15,1},{17,0},{19,0},{20,1},{20,2}};
static const glyph_stroke_t *strokes_38[1] = {stroke_38_0};
static const uint8_t ncoords_38[1] = {34};
static const glyph_stroke_t stroke_39_0[7] = {{1,19},{0,20},{1,21},{2,20},{2,18},{1,16},{0,15}};
static const glyph_stroke_t *strokes_39[1] = {stroke_39_0};
static const uint8_t ncoords_39[1] = {7};
static const glyph_stroke_t stroke_40_0[10] = {{7,25},{5,23},{3,20},{1,16},{0,11},{0,7},{1,2},{3,-2},{5,-5},{7,-7}};
static const glyph_stroke_t *strokes_40[1] = {stroke_40_0};
static const uint8_t ncoords_40[1] = {10};
static const glyph_stroke_t stroke_41_0[10] = {{0,25},{2,23},{4,20},{6,16},{7,11},{7,7},{6,2},{4,-2},{2,-5},{0,-7}};
static const glyph_stroke_t *strokes_41[1] = {stroke_41_0};
static const uint8_t ncoords_41[1] = {10};
static const glyph_stroke_t stroke_42_0[2] = {{0,6},{10,12}};
static const glyph_stroke_t stroke_42_1[2] = {{10,6},{0,12}};
static const glyph_stroke_t stroke_42_2[2] = {{5,15},{5,3}};
static const glyph_stroke_t *strokes_42[3] = {stroke_42_0, stroke_42_1, stroke_42_2};
static const uint8_t ncoords_42[3] = {2, 2, 2};
static const glyph_stroke_t stroke_43_0[2] = {{0,9},{18,9}};
static const glyph_stroke_t stroke_43_1[2] = {{9,18},{9,0}};
static const glyph_stroke_t *strokes_43[2] = {stroke_43_0, stroke_43_1};
static const uint8_t ncoords_43[2] = {2, 2};
static const glyph_stroke_t stroke_44_0[7] = {{2,1},{1,0},{0,1},{1,2},{2,1},{2,-1},{0,-3}};
static const glyph_stroke_t *strokes_44[1] = {stroke_44_0};
static const uint8_t ncoords_44[1] = {7};
static const glyph_stroke_t stroke_45_0[2] = {{0,9},{10,9}};
static const glyph_stroke_t *strokes_45[1] = {stroke_45_0};
static const uint8_t ncoords_45[1] = {2};
static const glyph_stroke_t stroke_46_0[5] = {{1,2},{0,1},{1,0},{2,1},{1,2}};
static const glyph_stroke_t *strokes_46[1] = {stroke_46_0};
static const uint8_t ncoords_46[1] = {5};
static const glyph_stroke_t stroke_47_0[2] = {{0,-7},{18,25}};
static const glyph_stroke_t *strokes_47[1] = {stroke_47_0};
static const uint8_t ncoords_47[1] = {2};
static const glyph_stroke_t stroke_48_0[17] = {{1,4},{3,1},{6,0},{8,0},{11,1},{13,4},{14,9},{14,12},{13,17},{11,20},{8,21},{6,21},{3,20},{1,17},{0,12},{0,9},{1,4}};
static const glyph_stroke_t *strokes_48[1] = {stroke_48_0};
static const uint8_t ncoords_48[1] = {17};
static const glyph_stroke_t stroke_49_0[4] = {{0,17},{2,18},{5,21},{5,0}};
static const glyph_stroke_t *strokes_49[1] = {stroke_49_0};
static const uint8_t ncoords_49[1] = {4};
static const glyph_stroke_t stroke_50_0[14] = {{1,16},{1,17},{2,19},{3,20},{5,21},{9,21},{11,20},{12,19},{13,17},{13,15},{12,13},{10,10},{0,0},{14,0}};
static const glyph_stroke_t *strokes_50[1] = {stroke_50_0};
static const uint8_t ncoords_50[1] = {14};
static const glyph_stroke_t stroke_51_0[15] = {{0,4},{1,2},{2,1},{5,0},{8,0},{11,1},{13,3},{14,6},{14,8},{13,11},{12,12},{10,13},{7,13},{13,21},{2,21}};
static const glyph_stroke_t *strokes_51[1] = {stroke_51_0};
static const uint8_t ncoords_51[1] = {15};
static const glyph_stroke_t stroke_52_0[4] = {{10,0},{10,21},{0,7},{15,7}};
static const glyph_stroke_t *strokes_52[1] = {stroke_52_0};
static const uint8_t ncoords_52[1] = {4};
static const glyph_stroke_t stroke_53_0[17] = {{0,4},{1,2},{2,1},{5,0},{8,0},{11,1},{13,3},{14,6},{14,8},{13,11},{11,13},{8,14},{5,14},{2,13},{1,12},{2,21},{12,21}};
static const glyph_stroke_t *strokes_53[1] = {stroke_53_0};
static const uint8_t ncoords_53[1] = {17};
static const glyph_stroke_t stroke_54_0[23] = {{0,7},{1,10},{3,12},{6,13},{7,13},{10,12},{12,10},{13,7},{13,6},{12,3},{10,1},{7,0},{6,0},{3,1},{1,3},{0,7},{0,12},{1,17},{3,20},{6,21},{8,21},{11,20},{12,18}};
static const glyph_stroke_t *strokes_54[1] = {stroke_54_0};
static const uint8_t ncoords_54[1] = {23};
static const glyph_stroke_t stroke_55_0[3] = {{0,21},{14,21},{4,0}};
static const glyph_stroke_t *strokes_55[1] = {stroke_55_0};
static const uint8_t ncoords_55[1] = {3};
static const glyph_stroke_t stroke_56_0[29] = {{1,2},{0,4},{0,7},{1,9},{3,11},{6,12},{10,13},{12,14},{13,16},{13,18},{12,20},{9,21},{5,21},{2,20},{1,18},{1,16},{2,14},{4,13},{8,12},{11,11},{13,9},{14,7},{14,4},{13,2},{12,1},{9,0},{5,0},{2,1},{1,2}};
static const glyph_stroke_t *strokes_56[1] = {stroke_56_0};
static const uint8_t ncoords_56[1] = {29};
static const glyph_stroke_t stroke_57_0[23] = {{1,3},{2,1},{5,0},{7,0},{10,1},{12,4},{13,9},{13,14},{12,18},{10,20},{7,21},{6,21},{3,20},{1,18},{0,15},{0,14},{1,11},{3,9},{6,8},{7,8},{10,9},{12,11},{13,14}};
static const glyph_stroke_t *strokes_57[1] = {stroke_57_0};
static const uint8_t ncoords_57[1] = {23};
static const glyph_stroke_t stroke_58_0[5] = {{1,9},{0,8},{1,7},{2,8},{1,9}};
static const glyph_stroke_t stroke_58_1[5] = {{1,2},{0,1},{1,0},{2,1},{1,2}};
static const glyph_stroke_t *strokes_58[2] = {stroke_58_0, stroke_58_1};
static const uint8_t ncoords_58[2] = {5, 5};
static const glyph_stroke_t stroke_59_0[5] = {{1,9},{0,8},{1,7},{2,8},{1,9}};
static const glyph_stroke_t stroke_59_1[7] = {{2,1},{1,0},{0,1},{1,2},{2,1},{2,-1},{0,-3}};
static const glyph_stroke_t *strokes_59[2] = {stroke_59_0, stroke_59_1};
static const uint8_t ncoords_59[2] = {5, 7};
static const glyph_stroke_t stroke_60_0[3] = {{16,18},{0,9},{16,0}};
static const glyph_stroke_t *strokes_60[1] = {stroke_60_0};
static const uint8_t ncoords_60[1] = {3};
static const glyph_stroke_t stroke_61_0[2] = {{0,12},{18,12}};
static const glyph_stroke_t stroke_61_1[2] = {{18,6},{0,6}};
static const glyph_stroke_t *strokes_61[2] = {stroke_61_0, stroke_61_1};
static const uint8_t ncoords_61[2] = {2, 2};
static const glyph_stroke_t stroke_62_0[3] = {{0,18},{16,9},{0,0}};
static const glyph_stroke_t *strokes_62[1] = {stroke_62_0};
static const uint8_t ncoords_62[1] = {3};
static const glyph_stroke_t stroke_63_0[14] = {{0,16},{0,17},{1,19},{2,20},{4,21},{8,21},{10,20},{11,19},{12,17},{12,15},{11,13},{10,12},{6,10},{6,7}};
static const glyph_stroke_t stroke_63_1[5] = {{6,2},{5,1},{6,0},{7,1},{6,2}};
static const glyph_stroke_t *strokes_63[2] = {stroke_63_0, stroke_63_1};
static const uint8_t ncoords_63[2] = {14, 5};
static const glyph_stroke_t stroke_64_0[6] = {{9,16},{7,14},{6,11},{6,8},{7,6},{8,5}};
static const glyph_stroke_t stroke_64_1[4] = {{16,5},{15,6},{15,8},{16,16}};
static const glyph_stroke_t stroke_64_2[13] = {{15,13},{14,15},{12,16},{9,16},{7,15},{6,14},{5,11},{5,8},{6,6},{8,5},{11,5},{13,6},{14,8}};
static const glyph_stroke_t stroke_64_3[29] = {{15,16},{14,8},{14,6},{16,5},{18,5},{20,7},{21,10},{21,12},{20,15},{19,17},{17,19},{15,20},{12,21},{9,21},{6,20},{4,19},{2,17},{1,15},{0,12},{0,9},{1,6},{2,4},{4,2},{6,1},{9,0},{12,0},{15,1},{17,2},{18,3}};
static const glyph_stroke_t *strokes_64[4] = {stroke_64_0, stroke_64_1, stroke_64_2, stroke_64_3};
static const uint8_t ncoords_64[4] = {6, 4, 13, 29};
static const glyph_stroke_t stroke_65_0[3] = {{0,0},{8,21},{16,0}};
static const glyph_stroke_t stroke_65_1[2] = {{3,7},{13,7}};
static const glyph_stroke_t *strokes_65[2] = {stroke_65_0, stroke_65_1};
static const uint8_t ncoords_65[2] = {3, 2};
static const glyph_stroke_t stroke_66_0[10] = {{0,0},{0,21},{9,21},{12,20},{13,19},{14,17},{14,15},{13,13},{12,12},{9,11}};
static const glyph_stroke_t stroke_66_1[10] = {{0,11},{9,11},{12,10},{13,9},{14,7},{14,4},{13,2},{12,1},{9,0},{0,0}};
static const glyph_stroke_t *strokes_66[2] = {stroke_66_0, stroke_66_1};
static const uint8_t ncoords_66[2] = {10, 10};
static const glyph_stroke_t stroke_67_0[18] = {{15,16},{14,18},{12,20},{10,21},{6,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3},{4,1},{6,0},{10,0},{12,1},{14,3},{15,5}};
static const glyph_stroke_t *strokes_67[1] = {stroke_67_0};
static const uint8_t ncoords_67[1] = {18};
static const glyph_stroke_t stroke_68_0[13] = {{0,0},{0,21},{7,21},{10,20},{12,18},{13,16},{14,13},{14,8},{13,5},{12,3},{10,1},{7,0},{0,0}};
static const glyph_stroke_t *strokes_68[1] = {stroke_68_0};
static const uint8_t ncoords_68[1] = {13};
static const glyph_stroke_t stroke_69_0[4] = {{13,0},{0,0},{0,21},{13,21}};
static const glyph_stroke_t stroke_69_1[2] = {{8,11},{0,11}};
static const glyph_stroke_t *strokes_69[2] = {stroke_69_0, stroke_69_1};
static const uint8_t ncoords_69[2] = {4, 2};
static const glyph_stroke_t stroke_70_0[3] = {{0,0},{0,21},{13,21}};
static const glyph_stroke_t stroke_70_1[2] = {{8,11},{0,11}};
static const glyph_stroke_t *strokes_70[2] = {stroke_70_0, stroke_70_1};
static const uint8_t ncoords_70[2] = {3, 2};
static const glyph_stroke_t stroke_71_0[20] = {{15,16},{14,18},{12,20},{10,21},{6,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3},{4,1},{6,0},{10,0},{12,1},{14,3},{15,5},{15,8},{10,8}};
static const glyph_stroke_t *strokes_71[1] = {stroke_71_0};
static const uint8_t ncoords_71[1] = {20};
static const glyph_stroke_t stroke_72_0[2] = {{0,0},{0,21}};
static const glyph_stroke_t stroke_72_1[2] = {{14,21},{14,0}};
static const glyph_stroke_t stroke_72_2[2] = {{0,11},{14,11}};
static const glyph_stroke_t *strokes_72[3] = {stroke_72_0, stroke_72_1, stroke_72_2};
static const uint8_t ncoords_72[3] = {2, 2, 2};
static const glyph_stroke_t stroke_73_0[2] = {{0,21},{0,0}};
static const glyph_stroke_t *strokes_73[1] = {stroke_73_0};
static const uint8_t ncoords_73[1] = {2};
static const glyph_stroke_t stroke_74_0[10] = {{0,7},{0,5},{1,2},{2,1},{4,0},{6,0},{8,1},{9,2},{10,5},{10,21}};
static const glyph_stroke_t *strokes_74[1] = {stroke_74_0};
static const uint8_t ncoords_74[1] = {10};
static const glyph_stroke_t stroke_75_0[2] = {{0,0},{0,21}};
static const glyph_stroke_t stroke_75_1[2] = {{14,21},{0,7}};
static const glyph_stroke_t stroke_75_2[2] = {{5,12},{14,0}};
static const glyph_stroke_t *strokes_75[3] = {stroke_75_0, stroke_75_1, stroke_75_2};
static const uint8_t ncoords_75[3] = {2, 2, 2};
static const glyph_stroke_t stroke_76_0[3] = {{0,21},{0,0},{12,0}};
static const glyph_stroke_t *strokes_76[1] = {stroke_76_0};
static const uint8_t ncoords_76[1] = {3};
static const glyph_stroke_t stroke_77_0[5] = {{0,0},{0,21},{8,0},{16,21},{16,0}};
static const glyph_stroke_t *strokes_77[1] = {stroke_77_0};
static const uint8_t ncoords_77[1] = {5};
static const glyph_stroke_t stroke_78_0[4] = {{0,0},{0,21},{14,0},{14,21}};
static const glyph_stroke_t *strokes_78[1] = {stroke_78_0};
static const uint8_t ncoords_78[1] = {4};
static const glyph_stroke_t stroke_79_0[21] = {{2,3},{4,1},{6,0},{10,0},{12,1},{14,3},{15,5},{16,8},{16,13},{15,16},{14,18},{12,20},{10,21},{6,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3}};
static const glyph_stroke_t *strokes_79[1] = {stroke_79_0};
static const uint8_t ncoords_79[1] = {21};
static const glyph_stroke_t stroke_80_0[11] = {{0,0},{0,21},{9,21},{12,20},{13,19},{14,17},{14,14},{13,12},{12,11},{9,10},{0,10}};
static const glyph_stroke_t *strokes_80[1] = {stroke_80_0};
static const uint8_t ncoords_80[1] = {11};
static const glyph_stroke_t stroke_81_0[21] = {{2,3},{4,1},{6,0},{10,0},{12,1},{14,3},{15,5},{16,8},{16,13},{15,16},{14,18},{12,20},{10,21},{6,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3}};
static const glyph_stroke_t stroke_81_1[2] = {{9,4},{15,-2}};
static const glyph_stroke_t *strokes_81[2] = {stroke_81_0, stroke_81_1};
static const uint8_t ncoords_81[2] = {21, 2};
static const glyph_stroke_t stroke_82_0[11] = {{0,0},{0,21},{9,21},{12,20},{13,19},{14,17},{14,15},{13,13},{12,12},{9,11},{0,11}};
static const glyph_stroke_t stroke_82_1[2] = {{7,11},{14,0}};
static const glyph_stroke_t *strokes_82[2] = {stroke_82_0, stroke_82_1};
static const uint8_t ncoords_82[2] = {11, 2};
static const glyph_stroke_t stroke_83_0[20] = {{0,3},{2,1},{5,0},{9,0},{12,1},{14,3},{14,6},{13,8},{12,9},{10,10},{4,12},{2,13},{1,14},{0,16},{0,18},{2,20},{5,21},{9,21},{12,20},{14,18}};
static const glyph_stroke_t *strokes_83[1] = {stroke_83_0};
static const uint8_t ncoords_83[1] = {20};
static const glyph_stroke_t stroke_84_0[2] = {{7,0},{7,21}};
static const glyph_stroke_t stroke_84_1[2] = {{0,21},{14,21}};
static const glyph_stroke_t *strokes_84[2] = {stroke_84_0, stroke_84_1};
static const uint8_t ncoords_84[2] = {2, 2};
static const glyph_stroke_t stroke_85_0[10] = {{0,21},{0,6},{1,3},{3,1},{6,0},{8,0},{11,1},{13,3},{14,6},{14,21}};
static const glyph_stroke_t *strokes_85[1] = {stroke_85_0};
static const uint8_t ncoords_85[1] = {10};
static const glyph_stroke_t stroke_86_0[3] = {{0,21},{8,0},{16,21}};
static const glyph_stroke_t *strokes_86[1] = {stroke_86_0};
static const uint8_t ncoords_86[1] = {3};
static const glyph_stroke_t stroke_87_0[5] = {{0,21},{5,0},{10,21},{15,0},{20,21}};
static const glyph_stroke_t *strokes_87[1] = {stroke_87_0};
static const uint8_t ncoords_87[1] = {5};
static const glyph_stroke_t stroke_88_0[2] = {{0,0},{14,21}};
static const glyph_stroke_t stroke_88_1[2] = {{0,21},{14,0}};
static const glyph_stroke_t *strokes_88[2] = {stroke_88_0, stroke_88_1};
static const uint8_t ncoords_88[2] = {2, 2};
static const glyph_stroke_t stroke_89_0[3] = {{0,21},{8,11},{16,21}};
static const glyph_stroke_t stroke_89_1[2] = {{8,11},{8,0}};
static const glyph_stroke_t *strokes_89[2] = {stroke_89_0, stroke_89_1};
static const uint8_t ncoords_89[2] = {3, 2};
static const glyph_stroke_t stroke_90_0[4] = {{0,21},{14,21},{0,0},{14,0}};
static const glyph_stroke_t *strokes_90[1] = {stroke_90_0};
static const uint8_t ncoords_90[1] = {4};
static const glyph_stroke_t stroke_91_0[4] = {{7,25},{0,25},{0,-7},{7,-7}};
static const glyph_stroke_t *strokes_91[1] = {stroke_91_0};
static const uint8_t ncoords_91[1] = {4};
static const glyph_stroke_t stroke_92_0[2] = {{0,21},{14,-3}};
static const glyph_stroke_t *strokes_92[1] = {stroke_92_0};
static const uint8_t ncoords_92[1] = {2};
static const glyph_stroke_t stroke_93_0[4] = {{0,25},{7,25},{7,-7},{0,-7}};
static const glyph_stroke_t *strokes_93[1] = {stroke_93_0};
static const uint8_t ncoords_93[1] = {4};
static const glyph_stroke_t stroke_94_0[3] = {{0,9},{8,23},{16,9}};
static const glyph_stroke_t *strokes_94[1] = {stroke_94_0};
static const uint8_t ncoords_94[1] = {3};
static const glyph_stroke_t stroke_95_0[2] = {{0,-7},{18,-7}};
static const glyph_stroke_t *strokes_95[1] = {stroke_95_0};
static const uint8_t ncoords_95[1] = {2};
static const glyph_stroke_t stroke_96_0[7] = {{0,12},{1,13},{2,12},{1,11},{0,12},{0,14},{2,16}};
static const glyph_stroke_t *strokes_96[1] = {stroke_96_0};
static const uint8_t ncoords_96[1] = {7};
static const glyph_stroke_t stroke_97_0[2] = {{12,0},{12,14}};
static const glyph_stroke_t stroke_97_1[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t *strokes_97[2] = {stroke_97_0, stroke_97_1};
static const uint8_t ncoords_97[2] = {2, 14};
static const glyph_stroke_t stroke_98_0[2] = {{0,0},{0,21}};
static const glyph_stroke_t stroke_98_1[14] = {{0,11},{2,13},{4,14},{7,14},{9,13},{11,11},{12,8},{12,6},{11,3},{9,1},{7,0},{4,0},{2,1},{0,3}};
static const glyph_stroke_t *strokes_98[2] = {stroke_98_0, stroke_98_1};
static const uint8_t ncoords_98[2] = {2, 14};
static const glyph_stroke_t stroke_99_0[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t *strokes_99[1] = {stroke_99_0};
static const uint8_t ncoords_99[1] = {14};
static const glyph_stroke_t stroke_100_0[2] = {{12,0},{12,21}};
static const glyph_stroke_t stroke_100_1[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t *strokes_100[2] = {stroke_100_0, stroke_100_1};
static const uint8_t ncoords_100[2] = {2, 14};
static const glyph_stroke_t stroke_101_0[17] = {{0,8},{12,8},{12,10},{11,12},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t *strokes_101[1] = {stroke_101_0};
static const uint8_t ncoords_101[1] = {17};
static const glyph_stroke_t stroke_102_0[5] = {{3,0},{3,17},{4,20},{6,21},{8,21}};
static const glyph_stroke_t stroke_102_1[2] = {{0,14},{7,14}};
static const glyph_stroke_t *strokes_102[2] = {stroke_102_0, stroke_102_1};
static const uint8_t ncoords_102[2] = {5, 2};
static const glyph_stroke_t stroke_103_0[7] = {{3,-6},{5,-7},{8,-7},{10,-6},{11,-5},{12,-2},{12,14}};
static const glyph_stroke_t stroke_103_1[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t *strokes_103[2] = {stroke_103_0, stroke_103_1};
static const uint8_t ncoords_103[2] = {7, 14};
static const glyph_stroke_t stroke_104_0[2] = {{0,0},{0,21}};
static const glyph_stroke_t stroke_104_1[7] = {{0,10},{3,13},{5,14},{8,14},{10,13},{11,10},{11,0}};
static const glyph_stroke_t *strokes_104[2] = {stroke_104_0, stroke_104_1};
static const uint8_t ncoords_104[2] = {2, 7};
static const glyph_stroke_t stroke_105_0[2] = {{1,0},{1,14}};
static const glyph_stroke_t stroke_105_1[5] = {{0,21},{1,20},{2,21},{1,22},{0,21}};
static const glyph_stroke_t *strokes_105[2] = {stroke_105_0, stroke_105_1};
static const uint8_t ncoords_105[2] = {2, 5};
static const glyph_stroke_t stroke_106_0[5] = {{0,-7},{2,-7},{4,-6},{5,-3},{5,14}};
static const glyph_stroke_t stroke_106_1[5] = {{4,21},{5,20},{6,21},{5,22},{4,21}};
static const glyph_stroke_t *strokes_106[2] = {stroke_106_0, stroke_106_1};
static const uint8_t ncoords_106[2] = {5, 5};
static const glyph_stroke_t stroke_107_0[2] = {{0,0},{0,21}};
static const glyph_stroke_t stroke_107_1[2] = {{10,14},{0,4}};
static const glyph_stroke_t stroke_107_2[2] = {{4,8},{11,0}};
static const glyph_stroke_t *strokes_107[3] = {stroke_107_0, stroke_107_1, stroke_107_2};
static const uint8_t ncoords_107[3] = {2, 2, 2};
static const glyph_stroke_t stroke_108_0[2] = {{0,0},{0,21}};
static const glyph_stroke_t *strokes_108[1] = {stroke_108_0};
static const uint8_t ncoords_108[1] = {2};
static const glyph_stroke_t stroke_109_0[2] = {{0,0},{0,14}};
static const glyph_stroke_t stroke_109_1[7] = {{0,10},{3,13},{5,14},{8,14},{10,13},{11,10},{11,0}};
static const glyph_stroke_t stroke_109_2[7] = {{11,10},{14,13},{16,14},{19,14},{21,13},{22,10},{22,0}};
static const glyph_stroke_t *strokes_109[3] = {stroke_109_0, stroke_109_1, stroke_109_2};
static const uint8_t ncoords_109[3] = {2, 7, 7};
static const glyph_stroke_t stroke_110_0[2] = {{0,0},{0,14}};
static const glyph_stroke_t stroke_110_1[7] = {{0,10},{3,13},{5,14},{8,14},{10,13},{11,10},{11,0}};
static const glyph_stroke_t *strokes_110[2] = {stroke_110_0, stroke_110_1};
static const uint8_t ncoords_110[2] = {2, 7};
static const glyph_stroke_t stroke_111_0[17] = {{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3},{13,6},{13,8},{12,11},{10,13},{8,14},{5,14}};
static const glyph_stroke_t *strokes_111[1] = {stroke_111_0};
static const uint8_t ncoords_111[1] = {17};
static const glyph_stroke_t stroke_112_0[2] = {{0,-7},{0,14}};
static const glyph_stroke_t stroke_112_1[14] = {{0,11},{2,13},{4,14},{7,14},{9,13},{11,11},{12,8},{12,6},{11,3},{9,1},{7,0},{4,0},{2,1},{0,3}};
static const glyph_stroke_t *strokes_112[2] = {stroke_112_0, stroke_112_1};
static const uint8_t ncoords_112[2] = {2, 14};
static const glyph_stroke_t stroke_113_0[2] = {{12,-7},{12,14}};
static const glyph_stroke_t stroke_113_1[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t *strokes_113[2] = {stroke_113_0, stroke_113_1};
static const uint8_t ncoords_113[2] = {2, 14};
static const glyph_stroke_t stroke_114_0[2] = {{0,0},{0,14}};
static const glyph_stroke_t stroke_114_1[5] = {{0,8},{1,11},{3,13},{5,14},{8,14}};
static const glyph_stroke_t *strokes_114[2] = {stroke_114_0, stroke_114_1};
static const uint8_t ncoords_114[2] = {2, 5};
static const glyph_stroke_t stroke_115_0[17] = {{0,3},{1,1},{4,0},{7,0},{10,1},{11,3},{11,4},{10,6},{8,7},{3,8},{1,9},{0,11},{1,13},{4,14},{7,14},{10,13},{11,11}};
static const glyph_stroke_t *strokes_115[1] = {stroke_115_0};
static const uint8_t ncoords_115[1] = {17};
static const glyph_stroke_t stroke_116_0[5] = {{8,0},{6,0},{4,1},{3,4},{3,21}};
static const glyph_stroke_t stroke_116_1[2] = {{0,14},{7,14}};
static const glyph_stroke_t *strokes_116[2] = {stroke_116_0, stroke_116_1};
static const uint8_t ncoords_116[2] = {5, 2};
static const glyph_stroke_t stroke_117_0[7] = {{0,14},{0,4},{1,1},{3,0},{6,0},{8,1},{11,4}};
static const glyph_stroke_t stroke_117_1[2] = {{11,14},{11,0}};
static const glyph_stroke_t *strokes_117[2] = {stroke_117_0, stroke_117_1};
static const uint8_t ncoords_117[2] = {7, 2};
static const glyph_stroke_t stroke_118_0[3] = {{0,14},{6,0},{12,14}};
static const glyph_stroke_t *strokes_118[1] = {stroke_118_0};
static const uint8_t ncoords_118[1] = {3};
static const glyph_stroke_t stroke_119_0[5] = {{0,14},{4,0},{8,14},{12,0},{16,14}};
static const glyph_stroke_t *strokes_119[1] = {stroke_119_0};
static const uint8_t ncoords_119[1] = {5};
static const glyph_stroke_t stroke_120_0[2] = {{0,0},{11,14}};
static const glyph_stroke_t stroke_120_1[2] = {{0,14},{11,0}};
static const glyph_stroke_t *strokes_120[2] = {stroke_120_0, stroke_120_1};
static const uint8_t ncoords_120[2] = {2, 2};
static const glyph_stroke_t stroke_121_0[6] = {{0,-7},{1,-7},{3,-6},{5,-4},{7,0},{13,14}};
static const glyph_stroke_t stroke_121_1[2] = {{1,14},{7,0}};
static const glyph_stroke_t *strokes_121[2] = {stroke_121_0, stroke_121_1};
static const uint8_t ncoords_121[2] = {6, 2};
static const glyph_stroke_t stroke_122_0[4] = {{0,14},{11,14},{0,0},{11,0}};
static const glyph_stroke_t *strokes_122[1] = {stroke_122_0};
static const uint8_t ncoords_122[1] = {4};
static const glyph_stroke_t stroke_123_0[19] = {{5,-7},{3,-6},{2,-4},{2,-2},{3,0},{4,1},{5,3},{5,5},{4,7},{0,9},{4,11},{5,13},{5,15},{4,17},{3,18},{2,20},{2,22},{3,24},{5,25}};
static const glyph_stroke_t *strokes_123[1] = {stroke_123_0};
static const uint8_t ncoords_123[1] = {19};
static const glyph_stroke_t stroke_124_0[2] = {{0,-7},{0,25}};
static const glyph_stroke_t *strokes_124[1] = {stroke_124_0};
static const uint8_t ncoords_124[1] = {2};
static const glyph_stroke_t stroke_125_0[19] = {{0,-7},{2,-6},{3,-4},{3,-2},{2,0},{1,1},{0,3},{0,5},{1,7},{5,9},{1,11},{0,13},{0,15},{1,17},{2,18},{3,20},{3,22},{2,24},{0,25}};
static const glyph_stroke_t *strokes_125[1] = {stroke_125_0};
static const uint8_t ncoords_125[1] = {19};
static const glyph_stroke_t stroke_126_0[12] = {{0,7},{0,9},{1,11},{3,12},{5,12},{7,11},{11,8},{13,7},{15,7},{17,8},{18,10},{18,12}};
static const glyph_stroke_t *strokes_126[1] = {stroke_126_0};
static const uint8_t ncoords_126[1] = {12};
static const glyph_stroke_t stroke_127_0[34] = {{0,21},{0,0},{1,0},{1,21},{2,21},{2,0},{3,0},{3,21},{4,21},{4,0},{5,0},{5,21},{6,21},{6,0},{7,0},{7,21},{8,21},{8,0},{9,0},{9,21},{10,21},{10,0},{11,0},{11,21},{12,21},{12,0},{13,0},{13,21},{14,21},{14,0},{15,0},{15,21},{16,21},{16,0}};
static const glyph_stroke_t *strokes_127[1] = {stroke_127_0};
static const uint8_t ncoords_127[1] = {34};
static const glyph_stroke_t stroke_161_0[2] = {{1,0},{1,14}};
static const glyph_stroke_t stroke_161_1[5] = {{1,19},{0,20},{1,21},{2,20},{1,19}};
static const glyph_stroke_t *strokes_161[2] = {stroke_161_0, stroke_161_1};
static const uint8_t ncoords_161[2] = {2, 5};
static const glyph_stroke_t stroke_57515_0[3] = {{2,6},{0,8},{2,10}};
static const glyph_stroke_t stroke_57515_1[3] = {{4,10},{2,8},{4,6}};
static const glyph_stroke_t *strokes_57515[2] = {stroke_57515_0, stroke_57515_1};
static const uint8_t ncoords_57515[2] = {3, 3};
static const glyph_stroke_t stroke_57520_0[9] = {{3,15},{5,16},{6,18},{5,20},{3,21},{1,20},{0,18},{1,16},{3,15}};
static const glyph_stroke_t *strokes_57520[1] = {stroke_57520_0};
static const uint8_t ncoords_57520[1] = {9};
static const glyph_stroke_t stroke_177_0[2] = {{0,0},{16,0}};
static const glyph_stroke_t stroke_177_1[2] = {{16,9},{0,9}};
static const glyph_stroke_t stroke_177_2[2] = {{8,17},{8,0}};
static const glyph_stroke_t *strokes_177[3] = {stroke_177_0, stroke_177_1, stroke_177_2};
static const uint8_t ncoords_177[3] = {2, 2, 2};
static const glyph_stroke_t stroke_183_0[5] = {{0,10},{0,9},{1,9},{1,10},{0,10}};
static const glyph_stroke_t *strokes_183[1] = {stroke_183_0};
static const uint8_t ncoords_183[1] = {5};
static const glyph_stroke_t stroke_57531_0[3] = {{0,6},{2,8},{0,10}};
static const glyph_stroke_t stroke_57531_1[3] = {{2,10},{4,8},{2,6}};
static const glyph_stroke_t *strokes_57531[2] = {stroke_57531_0, stroke_57531_1};
static const uint8_t ncoords_57531[2] = {3, 3};
static const glyph_stroke_t stroke_191_0[14] = {{0,5},{0,4},{1,2},{2,1},{4,0},{8,0},{10,1},{11,2},{12,4},{12,7},{11,8},{10,9},{6,11},{6,14}};
static const glyph_stroke_t stroke_191_1[5] = {{6,19},{5,20},{6,21},{7,20},{6,19}};
static const glyph_stroke_t *strokes_191[2] = {stroke_191_0, stroke_191_1};
static const uint8_t ncoords_191[2] = {14, 5};
static const glyph_stroke_t stroke_192_0[3] = {{0,0},{8,21},{16,0}};
static const glyph_stroke_t stroke_192_1[2] = {{13,7},{3,7}};
static const glyph_stroke_t stroke_192_2[4] = {{4,29},{3,28},{9,24},{4,29}};
static const glyph_stroke_t *strokes_192[3] = {stroke_192_0, stroke_192_1, stroke_192_2};
static const uint8_t ncoords_192[3] = {3, 2, 4};
static const glyph_stroke_t stroke_193_0[3] = {{0,0},{8,21},{16,0}};
static const glyph_stroke_t stroke_193_1[2] = {{13,7},{3,7}};
static const glyph_stroke_t stroke_193_2[4] = {{12,29},{13,28},{7,24},{12,29}};
static const glyph_stroke_t *strokes_193[3] = {stroke_193_0, stroke_193_1, stroke_193_2};
static const uint8_t ncoords_193[3] = {3, 2, 4};
static const glyph_stroke_t stroke_194_0[3] = {{0,0},{8,21},{16,0}};
static const glyph_stroke_t stroke_194_1[2] = {{13,7},{3,7}};
static const glyph_stroke_t stroke_194_2[3] = {{4,23},{8,27},{12,23}};
static const glyph_stroke_t *strokes_194[3] = {stroke_194_0, stroke_194_1, stroke_194_2};
static const uint8_t ncoords_194[3] = {3, 2, 3};
static const glyph_stroke_t stroke_195_0[3] = {{0,0},{8,21},{16,0}};
static const glyph_stroke_t stroke_195_1[2] = {{13,7},{3,7}};
static const glyph_stroke_t stroke_195_2[6] = {{5,24},{6,25},{7,25},{9,24},{10,24},{11,25}};
static const glyph_stroke_t *strokes_195[3] = {stroke_195_0, stroke_195_1, stroke_195_2};
static const uint8_t ncoords_195[3] = {3, 2, 6};
static const glyph_stroke_t stroke_196_0[3] = {{0,0},{8,21},{16,0}};
static const glyph_stroke_t stroke_196_1[2] = {{13,7},{3,7}};
static const glyph_stroke_t stroke_196_2[5] = {{5,25},{4,24},{5,23},{6,24},{5,25}};
static const glyph_stroke_t stroke_196_3[5] = {{11,25},{12,24},{11,23},{10,24},{11,25}};
static const glyph_stroke_t *strokes_196[4] = {stroke_196_0, stroke_196_1, stroke_196_2, stroke_196_3};
static const uint8_t ncoords_196[4] = {3, 2, 5, 5};
static const glyph_stroke_t stroke_197_0[11] = {{0,0},{8,21},{10,22},{11,24},{10,26},{8,27},{6,26},{5,24},{6,22},{8,21},{16,0}};
static const glyph_stroke_t stroke_197_1[2] = {{3,7},{13,7}};
static const glyph_stroke_t *strokes_197[2] = {stroke_197_0, stroke_197_1};
static const uint8_t ncoords_197[2] = {11, 2};
static const glyph_stroke_t stroke_198_0[3] = {{0,0},{8,21},{20,21}};
static const glyph_stroke_t stroke_198_1[3] = {{8,21},{8,0},{20,0}};
static const glyph_stroke_t stroke_198_2[2] = {{15,11},{8,11}};
static const glyph_stroke_t stroke_198_3[2] = {{3,7},{8,7}};
static const glyph_stroke_t *strokes_198[4] = {stroke_198_0, stroke_198_1, stroke_198_2, stroke_198_3};
static const uint8_t ncoords_198[4] = {3, 3, 2, 2};
static const glyph_stroke_t stroke_57543_0[5] = {{8,-3},{9,-3},{9,-2},{8,-1},{8,0}};
static const glyph_stroke_t stroke_57543_1[18] = {{15,5},{14,3},{12,1},{10,0},{6,0},{4,1},{2,3},{1,5},{0,8},{0,13},{1,16},{2,18},{4,20},{6,21},{10,21},{12,20},{14,18},{15,16}};
static const glyph_stroke_t *strokes_57543[2] = {stroke_57543_0, stroke_57543_1};
static const uint8_t ncoords_57543[2] = {5, 18};
static const glyph_stroke_t stroke_200_0[4] = {{13,0},{0,0},{0,21},{13,21}};
static const glyph_stroke_t stroke_200_1[4] = {{2,29},{1,28},{7,24},{2,29}};
static const glyph_stroke_t stroke_200_2[2] = {{0,11},{8,11}};
static const glyph_stroke_t *strokes_200[3] = {stroke_200_0, stroke_200_1, stroke_200_2};
static const uint8_t ncoords_200[3] = {4, 4, 2};
static const glyph_stroke_t stroke_201_0[4] = {{13,0},{0,0},{0,21},{13,21}};
static const glyph_stroke_t stroke_201_1[4] = {{10,29},{11,28},{5,24},{10,29}};
static const glyph_stroke_t stroke_201_2[2] = {{0,11},{8,11}};
static const glyph_stroke_t *strokes_201[3] = {stroke_201_0, stroke_201_1, stroke_201_2};
static const uint8_t ncoords_201[3] = {4, 4, 2};
static const glyph_stroke_t stroke_202_0[4] = {{13,0},{0,0},{0,21},{13,21}};
static const glyph_stroke_t stroke_202_1[3] = {{10,23},{6,27},{2,23}};
static const glyph_stroke_t stroke_202_2[2] = {{0,11},{8,11}};
static const glyph_stroke_t *strokes_202[3] = {stroke_202_0, stroke_202_1, stroke_202_2};
static const uint8_t ncoords_202[3] = {4, 3, 2};
static const glyph_stroke_t stroke_203_0[4] = {{13,0},{0,0},{0,21},{13,21}};
static const glyph_stroke_t stroke_203_1[5] = {{9,25},{10,24},{9,23},{8,24},{9,25}};
static const glyph_stroke_t stroke_203_2[5] = {{3,25},{2,24},{3,23},{4,24},{3,25}};
static const glyph_stroke_t stroke_203_3[2] = {{0,11},{8,11}};
static const glyph_stroke_t *strokes_203[4] = {stroke_203_0, stroke_203_1, stroke_203_2, stroke_203_3};
static const uint8_t ncoords_203[4] = {4, 5, 5, 2};
static const glyph_stroke_t stroke_204_0[2] = {{5,0},{5,21}};
static const glyph_stroke_t stroke_204_1[4] = {{1,29},{0,28},{6,24},{1,29}};
static const glyph_stroke_t *strokes_204[2] = {stroke_204_0, stroke_204_1};
static const uint8_t ncoords_204[2] = {2, 4};
static const glyph_stroke_t stroke_205_0[2] = {{1,0},{1,21}};
static const glyph_stroke_t stroke_205_1[4] = {{5,29},{6,28},{0,24},{5,29}};
static const glyph_stroke_t *strokes_205[2] = {stroke_205_0, stroke_205_1};
static const uint8_t ncoords_205[2] = {2, 4};
static const glyph_stroke_t stroke_206_0[2] = {{4,0},{4,21}};
static const glyph_stroke_t stroke_206_1[3] = {{0,23},{4,27},{8,23}};
static const glyph_stroke_t *strokes_206[2] = {stroke_206_0, stroke_206_1};
static const uint8_t ncoords_206[2] = {2, 3};
static const glyph_stroke_t stroke_207_0[2] = {{4,0},{4,21}};
static const glyph_stroke_t stroke_207_1[5] = {{1,25},{0,24},{1,23},{2,24},{1,25}};
static const glyph_stroke_t stroke_207_2[5] = {{7,25},{8,24},{7,23},{6,24},{7,25}};
static const glyph_stroke_t *strokes_207[3] = {stroke_207_0, stroke_207_1, stroke_207_2};
static const uint8_t ncoords_207[3] = {2, 5, 5};
static const glyph_stroke_t stroke_57552_0[13] = {{0,0},{0,21},{7,21},{10,20},{12,18},{13,16},{14,13},{14,8},{13,5},{12,3},{10,1},{7,0},{0,0}};
static const glyph_stroke_t stroke_57552_1[2] = {{-2,11},{4,11}};
static const glyph_stroke_t *strokes_57552[2] = {stroke_57552_0, stroke_57552_1};
static const uint8_t ncoords_57552[2] = {13, 2};
static const glyph_stroke_t stroke_209_0[4] = {{0,0},{0,21},{14,0},{14,21}};
static const glyph_stroke_t stroke_209_1[6] = {{10,25},{9,24},{8,24},{6,25},{5,25},{4,24}};
static const glyph_stroke_t *strokes_209[2] = {stroke_209_0, stroke_209_1};
static const uint8_t ncoords_209[2] = {4, 6};
static const glyph_stroke_t stroke_210_0[21] = {{6,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3},{4,1},{6,0},{10,0},{12,1},{14,3},{15,5},{16,8},{16,13},{15,16},{14,18},{12,20},{10,21},{6,21}};
static const glyph_stroke_t stroke_210_1[4] = {{4,29},{3,28},{9,24},{4,29}};
static const glyph_stroke_t *strokes_210[2] = {stroke_210_0, stroke_210_1};
static const uint8_t ncoords_210[2] = {21, 4};
static const glyph_stroke_t stroke_211_0[21] = {{6,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3},{4,1},{6,0},{10,0},{12,1},{14,3},{15,5},{16,8},{16,13},{15,16},{14,18},{12,20},{10,21},{6,21}};
static const glyph_stroke_t stroke_211_1[4] = {{12,29},{13,28},{7,24},{12,29}};
static const glyph_stroke_t *strokes_211[2] = {stroke_211_0, stroke_211_1};
static const uint8_t ncoords_211[2] = {21, 4};
static const glyph_stroke_t stroke_212_0[21] = {{6,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3},{4,1},{6,0},{10,0},{12,1},{14,3},{15,5},{16,8},{16,13},{15,16},{14,18},{12,20},{10,21},{6,21}};
static const glyph_stroke_t stroke_212_1[3] = {{4,23},{8,27},{12,23}};
static const glyph_stroke_t *strokes_212[2] = {stroke_212_0, stroke_212_1};
static const uint8_t ncoords_212[2] = {21, 3};
static const glyph_stroke_t stroke_213_0[21] = {{6,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3},{4,1},{6,0},{10,0},{12,1},{14,3},{15,5},{16,8},{16,13},{15,16},{14,18},{12,20},{10,21},{6,21}};
static const glyph_stroke_t stroke_213_1[6] = {{5,24},{6,25},{7,25},{9,24},{10,24},{11,25}};
static const glyph_stroke_t *strokes_213[2] = {stroke_213_0, stroke_213_1};
static const uint8_t ncoords_213[2] = {21, 6};
static const glyph_stroke_t stroke_214_0[21] = {{6,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3},{4,1},{6,0},{10,0},{12,1},{14,3},{15,5},{16,8},{16,13},{15,16},{14,18},{12,20},{10,21},{6,21}};
static const glyph_stroke_t stroke_214_1[5] = {{5,25},{4,24},{5,23},{6,24},{5,25}};
static const glyph_stroke_t stroke_214_2[5] = {{11,25},{12,24},{11,23},{10,24},{11,25}};
static const glyph_stroke_t *strokes_214[3] = {stroke_214_0, stroke_214_1, stroke_214_2};
static const uint8_t ncoords_214[3] = {21, 5, 5};
static const glyph_stroke_t stroke_215_0[2] = {{0,2},{14,16}};
static const glyph_stroke_t stroke_215_1[2] = {{0,16},{14,2}};
static const glyph_stroke_t *strokes_215[2] = {stroke_215_0, stroke_215_1};
static const uint8_t ncoords_215[2] = {2, 2};
static const glyph_stroke_t stroke_216_0[2] = {{0,0},{16,21}};
static const glyph_stroke_t stroke_216_1[21] = {{10,21},{6,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3},{4,1},{6,0},{10,0},{12,1},{14,3},{15,5},{16,8},{16,13},{15,16},{14,18},{12,20},{10,21}};
static const glyph_stroke_t *strokes_216[2] = {stroke_216_0, stroke_216_1};
static const uint8_t ncoords_216[2] = {2, 21};
static const glyph_stroke_t stroke_217_0[10] = {{0,21},{0,6},{1,3},{3,1},{6,0},{8,0},{11,1},{13,3},{14,6},{14,21}};
static const glyph_stroke_t stroke_217_1[4] = {{3,29},{2,28},{8,24},{3,29}};
static const glyph_stroke_t *strokes_217[2] = {stroke_217_0, stroke_217_1};
static const uint8_t ncoords_217[2] = {10, 4};
static const glyph_stroke_t stroke_218_0[10] = {{0,21},{0,6},{1,3},{3,1},{6,0},{8,0},{11,1},{13,3},{14,6},{14,21}};
static const glyph_stroke_t stroke_218_1[4] = {{11,29},{12,28},{6,24},{11,29}};
static const glyph_stroke_t *strokes_218[2] = {stroke_218_0, stroke_218_1};
static const uint8_t ncoords_218[2] = {10, 4};
static const glyph_stroke_t stroke_219_0[10] = {{0,21},{0,6},{1,3},{3,1},{6,0},{8,0},{11,1},{13,3},{14,6},{14,21}};
static const glyph_stroke_t stroke_219_1[3] = {{11,23},{7,27},{3,23}};
static const glyph_stroke_t *strokes_219[2] = {stroke_219_0, stroke_219_1};
static const uint8_t ncoords_219[2] = {10, 3};
static const glyph_stroke_t stroke_220_0[10] = {{0,21},{0,6},{1,3},{3,1},{6,0},{8,0},{11,1},{13,3},{14,6},{14,21}};
static const glyph_stroke_t stroke_220_1[5] = {{10,25},{11,24},{10,23},{9,24},{10,25}};
static const glyph_stroke_t stroke_220_2[5] = {{4,25},{3,24},{4,23},{5,24},{4,25}};
static const glyph_stroke_t *strokes_220[3] = {stroke_220_0, stroke_220_1, stroke_220_2};
static const uint8_t ncoords_220[3] = {10, 5, 5};
static const glyph_stroke_t stroke_221_0[3] = {{0,21},{8,11},{16,21}};
static const glyph_stroke_t stroke_221_1[4] = {{12,29},{13,28},{7,24},{12,29}};
static const glyph_stroke_t stroke_221_2[2] = {{8,11},{8,0}};
static const glyph_stroke_t *strokes_221[3] = {stroke_221_0, stroke_221_1, stroke_221_2};
static const uint8_t ncoords_221[3] = {3, 4, 2};
static const glyph_stroke_t stroke_57566_0[2] = {{0,0},{0,21}};
static const glyph_stroke_t stroke_57566_1[11] = {{0,17},{7,17},{10,16},{12,14},{13,12},{13,10},{13,9},{12,7},{10,5},{7,4},{0,4}};
static const glyph_stroke_t *strokes_57566[2] = {stroke_57566_0, stroke_57566_1};
static const uint8_t ncoords_57566[2] = {2, 11};
static const glyph_stroke_t stroke_224_0[2] = {{12,0},{12,14}};
static const glyph_stroke_t stroke_224_1[4] = {{2,23},{1,22},{7,18},{2,23}};
static const glyph_stroke_t stroke_224_2[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t *strokes_224[3] = {stroke_224_0, stroke_224_1, stroke_224_2};
static const uint8_t ncoords_224[3] = {2, 4, 14};
static const glyph_stroke_t stroke_225_0[2] = {{12,0},{12,14}};
static const glyph_stroke_t stroke_225_1[4] = {{10,23},{11,22},{5,18},{10,23}};
static const glyph_stroke_t stroke_225_2[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t *strokes_225[3] = {stroke_225_0, stroke_225_1, stroke_225_2};
static const uint8_t ncoords_225[3] = {2, 4, 14};
static const glyph_stroke_t stroke_226_0[2] = {{12,0},{12,14}};
static const glyph_stroke_t stroke_226_1[3] = {{10,18},{6,22},{2,18}};
static const glyph_stroke_t stroke_226_2[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t *strokes_226[3] = {stroke_226_0, stroke_226_1, stroke_226_2};
static const uint8_t ncoords_226[3] = {2, 3, 14};
static const glyph_stroke_t stroke_227_0[2] = {{12,0},{12,14}};
static const glyph_stroke_t stroke_227_1[6] = {{9,20},{8,19},{7,19},{5,20},{4,20},{3,19}};
static const glyph_stroke_t stroke_227_2[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t *strokes_227[3] = {stroke_227_0, stroke_227_1, stroke_227_2};
static const uint8_t ncoords_227[3] = {2, 6, 14};
static const glyph_stroke_t stroke_228_0[2] = {{12,0},{12,14}};
static const glyph_stroke_t stroke_228_1[5] = {{9,20},{10,19},{9,18},{8,19},{9,20}};
static const glyph_stroke_t stroke_228_2[5] = {{3,20},{2,19},{3,18},{4,19},{3,20}};
static const glyph_stroke_t stroke_228_3[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t *strokes_228[4] = {stroke_228_0, stroke_228_1, stroke_228_2, stroke_228_3};
static const uint8_t ncoords_228[4] = {2, 5, 5, 14};
static const glyph_stroke_t stroke_229_0[2] = {{12,0},{12,14}};
static const glyph_stroke_t stroke_229_1[9] = {{6,16},{8,17},{9,19},{8,21},{6,22},{4,21},{3,19},{4,17},{6,16}};
static const glyph_stroke_t stroke_229_2[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t *strokes_229[3] = {stroke_229_0, stroke_229_1, stroke_229_2};
static const uint8_t ncoords_229[3] = {2, 9, 14};
static const glyph_stroke_t stroke_230_0[2] = {{12,0},{12,14}};
static const glyph_stroke_t stroke_230_1[14] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_230_2[17] = {{12,8},{24,8},{24,10},{23,12},{22,13},{20,14},{17,14},{15,13},{13,11},{12,8},{12,6},{13,3},{15,1},{17,0},{20,0},{22,1},{24,3}};
static const glyph_stroke_t *strokes_230[3] = {stroke_230_0, stroke_230_1, stroke_230_2};
static const uint8_t ncoords_230[3] = {2, 14, 17};
static const glyph_stroke_t stroke_57575_0[5] = {{7,-3},{8,-3},{8,-2},{7,-1},{7,0}};
static const glyph_stroke_t stroke_57575_1[14] = {{12,3},{10,1},{8,0},{5,0},{3,1},{1,3},{0,6},{0,8},{1,11},{3,13},{5,14},{8,14},{10,13},{12,11}};
static const glyph_stroke_t *strokes_57575[2] = {stroke_57575_0, stroke_57575_1};
static const uint8_t ncoords_57575[2] = {5, 14};
static const glyph_stroke_t stroke_232_0[17] = {{0,8},{12,8},{12,10},{11,12},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_232_1[4] = {{2,23},{1,22},{7,18},{2,23}};
static const glyph_stroke_t *strokes_232[2] = {stroke_232_0, stroke_232_1};
static const uint8_t ncoords_232[2] = {17, 4};
static const glyph_stroke_t stroke_233_0[17] = {{0,8},{12,8},{12,10},{11,12},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_233_1[4] = {{10,23},{11,22},{5,18},{10,23}};
static const glyph_stroke_t *strokes_233[2] = {stroke_233_0, stroke_233_1};
static const uint8_t ncoords_233[2] = {17, 4};
static const glyph_stroke_t stroke_234_0[17] = {{0,8},{12,8},{12,10},{11,12},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_234_1[3] = {{10,18},{6,22},{2,18}};
static const glyph_stroke_t *strokes_234[2] = {stroke_234_0, stroke_234_1};
static const uint8_t ncoords_234[2] = {17, 3};
static const glyph_stroke_t stroke_235_0[17] = {{0,8},{12,8},{12,10},{11,12},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3}};
static const glyph_stroke_t stroke_235_1[5] = {{9,20},{10,19},{9,18},{8,19},{9,20}};
static const glyph_stroke_t stroke_235_2[5] = {{3,20},{2,19},{3,18},{4,19},{3,20}};
static const glyph_stroke_t *strokes_235[3] = {stroke_235_0, stroke_235_1, stroke_235_2};
static const uint8_t ncoords_235[3] = {17, 5, 5};
static const glyph_stroke_t stroke_236_0[2] = {{5,0},{5,14}};
static const glyph_stroke_t stroke_236_1[4] = {{1,23},{0,22},{6,18},{1,23}};
static const glyph_stroke_t *strokes_236[2] = {stroke_236_0, stroke_236_1};
static const uint8_t ncoords_236[2] = {2, 4};
static const glyph_stroke_t stroke_237_0[2] = {{1,0},{1,14}};
static const glyph_stroke_t stroke_237_1[4] = {{5,23},{6,22},{0,18},{5,23}};
static const glyph_stroke_t *strokes_237[2] = {stroke_237_0, stroke_237_1};
static const uint8_t ncoords_237[2] = {2, 4};
static const glyph_stroke_t stroke_238_0[2] = {{4,0},{4,14}};
static const glyph_stroke_t stroke_238_1[3] = {{0,18},{4,22},{8,18}};
static const glyph_stroke_t *strokes_238[2] = {stroke_238_0, stroke_238_1};
static const uint8_t ncoords_238[2] = {2, 3};
static const glyph_stroke_t stroke_239_0[2] = {{4,0},{4,14}};
static const glyph_stroke_t stroke_239_1[5] = {{1,20},{0,19},{1,18},{2,19},{1,20}};
static const glyph_stroke_t stroke_239_2[5] = {{7,20},{8,19},{7,18},{6,19},{7,20}};
static const glyph_stroke_t *strokes_239[3] = {stroke_239_0, stroke_239_1, stroke_239_2};
static const uint8_t ncoords_239[3] = {2, 5, 5};
static const glyph_stroke_t stroke_57584_0[18] = {{12,11},{10,13},{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3},{13,6},{13,8},{12,11},{3,20}};
static const glyph_stroke_t stroke_57584_1[2] = {{3,17},{8,18}};
static const glyph_stroke_t *strokes_57584[2] = {stroke_57584_0, stroke_57584_1};
static const uint8_t ncoords_57584[2] = {18, 2};
static const glyph_stroke_t stroke_241_0[2] = {{0,0},{0,14}};
static const glyph_stroke_t stroke_241_1[6] = {{2,19},{3,20},{4,20},{6,19},{7,19},{8,20}};
static const glyph_stroke_t stroke_241_2[7] = {{0,10},{3,13},{5,14},{8,14},{10,13},{11,10},{11,0}};
static const glyph_stroke_t *strokes_241[3] = {stroke_241_0, stroke_241_1, stroke_241_2};
static const uint8_t ncoords_241[3] = {2, 6, 7};
static const glyph_stroke_t stroke_242_0[17] = {{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3},{13,6},{13,8},{12,11},{10,13},{8,14},{5,14}};
static const glyph_stroke_t stroke_242_1[4] = {{2,23},{1,22},{7,18},{2,23}};
static const glyph_stroke_t *strokes_242[2] = {stroke_242_0, stroke_242_1};
static const uint8_t ncoords_242[2] = {17, 4};
static const glyph_stroke_t stroke_243_0[17] = {{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3},{13,6},{13,8},{12,11},{10,13},{8,14},{5,14}};
static const glyph_stroke_t stroke_243_1[4] = {{10,23},{11,22},{5,18},{10,23}};
static const glyph_stroke_t *strokes_243[2] = {stroke_243_0, stroke_243_1};
static const uint8_t ncoords_243[2] = {17, 4};
static const glyph_stroke_t stroke_244_0[17] = {{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3},{13,6},{13,8},{12,11},{10,13},{8,14},{5,14}};
static const glyph_stroke_t stroke_244_1[3] = {{2,18},{6,22},{10,18}};
static const glyph_stroke_t *strokes_244[2] = {stroke_244_0, stroke_244_1};
static const uint8_t ncoords_244[2] = {17, 3};
static const glyph_stroke_t stroke_245_0[17] = {{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3},{13,6},{13,8},{12,11},{10,13},{8,14},{5,14}};
static const glyph_stroke_t stroke_245_1[6] = {{3,19},{4,20},{5,20},{7,19},{8,19},{9,20}};
static const glyph_stroke_t *strokes_245[2] = {stroke_245_0, stroke_245_1};
static const uint8_t ncoords_245[2] = {17, 6};
static const glyph_stroke_t stroke_246_0[17] = {{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3},{13,6},{13,8},{12,11},{10,13},{8,14},{5,14}};
static const glyph_stroke_t stroke_246_1[5] = {{3,20},{2,19},{3,18},{4,19},{3,20}};
static const glyph_stroke_t stroke_246_2[5] = {{9,20},{10,19},{9,18},{8,19},{9,20}};
static const glyph_stroke_t *strokes_246[3] = {stroke_246_0, stroke_246_1, stroke_246_2};
static const uint8_t ncoords_246[3] = {17, 5, 5};
static const glyph_stroke_t stroke_247_0[2] = {{0,9},{18,9}};
static const glyph_stroke_t stroke_247_1[5] = {{9,18},{8,17},{9,16},{10,17},{9,18}};
static const glyph_stroke_t stroke_247_2[5] = {{9,2},{8,1},{9,0},{10,1},{9,2}};
static const glyph_stroke_t *strokes_247[3] = {stroke_247_0, stroke_247_1, stroke_247_2};
static const uint8_t ncoords_247[3] = {2, 5, 5};
static const glyph_stroke_t stroke_248_0[2] = {{0,0},{13,14}};
static const glyph_stroke_t stroke_248_1[17] = {{8,14},{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3},{13,6},{13,8},{12,11},{10,13},{8,14}};
static const glyph_stroke_t *strokes_248[2] = {stroke_248_0, stroke_248_1};
static const uint8_t ncoords_248[2] = {2, 17};
static const glyph_stroke_t stroke_249_0[7] = {{0,14},{0,4},{1,1},{3,0},{6,0},{8,1},{11,4}};
static const glyph_stroke_t stroke_249_1[2] = {{11,0},{11,14}};
static const glyph_stroke_t stroke_249_2[4] = {{1,23},{0,22},{6,18},{1,23}};
static const glyph_stroke_t *strokes_249[3] = {stroke_249_0, stroke_249_1, stroke_249_2};
static const uint8_t ncoords_249[3] = {7, 2, 4};
static const glyph_stroke_t stroke_250_0[7] = {{0,14},{0,4},{1,1},{3,0},{6,0},{8,1},{11,4}};
static const glyph_stroke_t stroke_250_1[2] = {{11,0},{11,14}};
static const glyph_stroke_t stroke_250_2[4] = {{9,23},{10,22},{4,18},{9,23}};
static const glyph_stroke_t *strokes_250[3] = {stroke_250_0, stroke_250_1, stroke_250_2};
static const uint8_t ncoords_250[3] = {7, 2, 4};
static const glyph_stroke_t stroke_251_0[7] = {{0,14},{0,4},{1,1},{3,0},{6,0},{8,1},{11,4}};
static const glyph_stroke_t stroke_251_1[2] = {{11,0},{11,14}};
static const glyph_stroke_t stroke_251_2[3] = {{9,18},{5,22},{1,18}};
static const glyph_stroke_t *strokes_251[3] = {stroke_251_0, stroke_251_1, stroke_251_2};
static const uint8_t ncoords_251[3] = {7, 2, 3};
static const glyph_stroke_t stroke_252_0[7] = {{0,14},{0,4},{1,1},{3,0},{6,0},{8,1},{11,4}};
static const glyph_stroke_t stroke_252_1[2] = {{11,0},{11,14}};
static const glyph_stroke_t stroke_252_2[5] = {{8,20},{9,19},{8,18},{7,19},{8,20}};
static const glyph_stroke_t stroke_252_3[5] = {{2,20},{1,19},{2,18},{3,19},{2,20}};
static const glyph_stroke_t *strokes_252[4] = {stroke_252_0, stroke_252_1, stroke_252_2, stroke_252_3};
static const uint8_t ncoords_252[4] = {7, 2, 5, 5};
static const glyph_stroke_t stroke_253_0[6] = {{0,-7},{1,-7},{3,-6},{5,-4},{7,0},{13,14}};
static const glyph_stroke_t stroke_253_1[4] = {{11,23},{12,22},{6,18},{11,23}};
static const glyph_stroke_t stroke_253_2[2] = {{1,14},{7,0}};
static const glyph_stroke_t *strokes_253[3] = {stroke_253_0, stroke_253_1, stroke_253_2};
static const uint8_t ncoords_253[3] = {6, 4, 2};
static const glyph_stroke_t stroke_57598_0[2] = {{0,-7},{0,21}};
static const glyph_stroke_t stroke_57598_1[17] = {{5,14},{3,13},{1,11},{0,8},{0,6},{1,3},{3,1},{5,0},{8,0},{10,1},{12,3},{13,6},{13,8},{12,11},{10,13},{8,14},{5,14}};
static const glyph_stroke_t *strokes_57598[2] = {stroke_57598_0, stroke_57598_1};
static const uint8_t ncoords_57598[2] = {2, 17};
static const glyph_stroke_t stroke_255_0[6] = {{0,-7},{1,-7},{3,-6},{5,-4},{7,0},{13,14}};
static const glyph_stroke_t stroke_255_1[5] = {{10,20},{11,19},{10,18},{9,19},{10,20}};
static const glyph_stroke_t stroke_255_2[5] = {{4,20},{3,19},{4,18},{5,19},{4,20}};
static const glyph_stroke_t stroke_255_3[2] = {{1,14},{7,0}};
static const glyph_stroke_t *strokes_255[4] = {stroke_255_0, stroke_255_1, stroke_255_2, stroke_255_3};
static const uint8_t ncoords_255[4] = {6, 5, 5, 2};
static const glyph_stroke_t stroke_913_0[3] = {{0,0},{8,21},{16,0}};
static const glyph_stroke_t stroke_913_1[2] = {{3,7},{13,7}};
static const glyph_stroke_t *strokes_913[2] = {stroke_913_0, stroke_913_1};
static const uint8_t ncoords_913[2] = {3, 2};
static const glyph_stroke_t stroke_914_0[10] = {{0,0},{0,21},{9,21},{12,20},{13,19},{14,17},{14,15},{13,13},{12,12},{9,11}};
static const glyph_stroke_t stroke_914_1[10] = {{0,11},{9,11},{12,10},{13,9},{14,7},{14,4},{13,2},{12,1},{9,0},{0,0}};
static const glyph_stroke_t *strokes_914[2] = {stroke_914_0, stroke_914_1};
static const uint8_t ncoords_914[2] = {10, 10};
static const glyph_stroke_t stroke_915_0[3] = {{0,0},{0,21},{12,21}};
static const glyph_stroke_t *strokes_915[1] = {stroke_915_0};
static const uint8_t ncoords_915[1] = {3};
static const glyph_stroke_t stroke_916_0[4] = {{0,0},{8,21},{16,0},{0,0}};
static const glyph_stroke_t *strokes_916[1] = {stroke_916_0};
static const uint8_t ncoords_916[1] = {4};
static const glyph_stroke_t stroke_917_0[4] = {{13,0},{0,0},{0,21},{13,21}};
static const glyph_stroke_t stroke_917_1[2] = {{8,11},{0,11}};
static const glyph_stroke_t *strokes_917[2] = {stroke_917_0, stroke_917_1};
static const uint8_t ncoords_917[2] = {4, 2};
static const glyph_stroke_t stroke_918_0[4] = {{0,21},{14,21},{0,0},{14,0}};
static const glyph_stroke_t *strokes_918[1] = {stroke_918_0};
static const uint8_t ncoords_918[1] = {4};
static const glyph_stroke_t stroke_919_0[2] = {{0,0},{0,21}};
static const glyph_stroke_t stroke_919_1[2] = {{14,21},{14,0}};
static const glyph_stroke_t stroke_919_2[2] = {{0,11},{14,11}};
static const glyph_stroke_t *strokes_919[3] = {stroke_919_0, stroke_919_1, stroke_919_2};
static const uint8_t ncoords_919[3] = {2, 2, 2};
static const glyph_stroke_t stroke_920_0[21] = {{0,8},{1,5},{2,3},{4,1},{6,0},{10,0},{12,1},{14,3},{15,5},{16,8},{16,13},{15,16},{14,18},{12,20},{10,21},{6,21},{4,20},{2,18},{1,16},{0,13},{0,8}};
static const glyph_stroke_t stroke_920_1[2] = {{5,11},{11,11}};
static const glyph_stroke_t *strokes_920[2] = {stroke_920_0, stroke_920_1};
static const uint8_t ncoords_920[2] = {21, 2};
static const glyph_stroke_t stroke_921_0[2] = {{0,0},{0,21}};
static const glyph_stroke_t *strokes_921[1] = {stroke_921_0};
static const uint8_t ncoords_921[1] = {2};
static const glyph_stroke_t stroke_922_0[2] = {{0,0},{0,21}};
static const glyph_stroke_t stroke_922_1[2] = {{14,21},{0,7}};
static const glyph_stroke_t stroke_922_2[2] = {{5,12},{14,0}};
static const glyph_stroke_t *strokes_922[3] = {stroke_922_0, stroke_922_1, stroke_922_2};
static const uint8_t ncoords_922[3] = {2, 2, 2};
static const glyph_stroke_t stroke_923_0[3] = {{0,0},{8,21},{16,0}};
static const glyph_stroke_t *strokes_923[1] = {stroke_923_0};
static const uint8_t ncoords_923[1] = {3};
static const glyph_stroke_t stroke_924_0[5] = {{0,0},{0,21},{8,0},{16,21},{16,0}};
static const glyph_stroke_t *strokes_924[1] = {stroke_924_0};
static const uint8_t ncoords_924[1] = {5};
static const glyph_stroke_t stroke_925_0[4] = {{0,0},{0,21},{14,0},{14,21}};
static const glyph_stroke_t *strokes_925[1] = {stroke_925_0};
static const uint8_t ncoords_925[1] = {4};
static const glyph_stroke_t stroke_926_0[2] = {{0,0},{14,0}};
static const glyph_stroke_t stroke_926_1[2] = {{10,11},{4,11}};
static const glyph_stroke_t stroke_926_2[2] = {{0,21},{14,21}};
static const glyph_stroke_t *strokes_926[3] = {stroke_926_0, stroke_926_1, stroke_926_2};
static const uint8_t ncoords_926[3] = {2, 2, 2};
static const glyph_stroke_t stroke_927_0[21] = {{2,3},{4,1},{6,0},{10,0},{12,1},{14,3},{15,5},{16,8},{16,13},{15,16},{14,18},{12,20},{10,21},{6,21},{4,20},{2,18},{1,16},{0,13},{0,8},{1,5},{2,3}};
static const glyph_stroke_t *strokes_927[1] = {stroke_927_0};
static const uint8_t ncoords_927[1] = {21};
static const glyph_stroke_t stroke_928_0[4] = {{0,0},{0,21},{14,21},{14,0}};
static const glyph_stroke_t *strokes_928[1] = {stroke_928_0};
static const uint8_t ncoords_928[1] = {4};
static const glyph_stroke_t stroke_929_0[11] = {{0,0},{0,21},{9,21},{12,20},{13,19},{14,17},{14,14},{13,12},{12,11},{9,10},{0,10}};
static const glyph_stroke_t *strokes_929[1] = {stroke_929_0};
static const uint8_t ncoords_929[1] = {11};
static const glyph_stroke_t stroke_931_0[5] = {{14,0},{0,0},{7,11},{0,21},{14,21}};
static const glyph_stroke_t *strokes_931[1] = {stroke_931_0};
static const uint8_t ncoords_931[1] = {5};
static const glyph_stroke_t stroke_932_0[2] = {{7,0},{7,21}};
static const glyph_stroke_t stroke_932_1[2] = {{0,21},{14,21}};
static const glyph_stroke_t *strokes_932[2] = {stroke_932_0, stroke_932_1};
static const uint8_t ncoords_932[2] = {2, 2};
static const glyph_stroke_t stroke_933_0[9] = {{7,0},{7,14},{6,18},{5,20},{4,21},{2,21},{1,20},{0,18},{0,16}};
static const glyph_stroke_t stroke_933_1[8] = {{14,16},{14,18},{13,20},{12,21},{10,21},{9,20},{8,18},{7,14}};
static const glyph_stroke_t *strokes_933[2] = {stroke_933_0, stroke_933_1};
static const uint8_t ncoords_933[2] = {9, 8};
static const glyph_stroke_t stroke_934_0[2] = {{7,0},{7,21}};
static const glyph_stroke_t stroke_934_1[17] = {{5,16},{2,15},{1,14},{0,12},{0,9},{1,7},{2,6},{5,5},{9,5},{12,6},{13,7},{14,9},{14,12},{13,14},{12,15},{9,16},{5,16}};
static const glyph_stroke_t *strokes_934[2] = {stroke_934_0, stroke_934_1};
static const uint8_t ncoords_934[2] = {2, 17};
static const glyph_stroke_t stroke_935_0[2] = {{0,0},{14,21}};
static const glyph_stroke_t stroke_935_1[2] = {{0,21},{14,0}};
static const glyph_stroke_t *strokes_935[2] = {stroke_935_0, stroke_935_1};
static const uint8_t ncoords_935[2] = {2, 2};
static const glyph_stroke_t stroke_936_0[2] = {{9,0},{9,21}};
static const glyph_stroke_t stroke_936_1[14] = {{0,15},{1,15},{2,14},{3,10},{4,8},{5,7},{8,6},{10,6},{13,7},{14,8},{15,10},{16,14},{17,15},{18,15}};
static const glyph_stroke_t *strokes_936[2] = {stroke_936_0, stroke_936_1};
static const uint8_t ncoords_936[2] = {2, 14};
static const glyph_stroke_t stroke_937_0[16] = {{0,0},{4,0},{1,7},{0,11},{0,15},{1,18},{3,20},{6,21},{8,21},{11,20},{13,18},{14,15},{14,11},{13,7},{10,0},{14,0}};
static const glyph_stroke_t *strokes_937[1] = {stroke_937_0};
static const uint8_t ncoords_937[1] = {16};
static const glyph_stroke_t stroke_938_0[2] = {{4,0},{4,21}};
static const glyph_stroke_t stroke_938_1[5] = {{1,24},{0,23},{1,22},{2,23},{1,24}};
static const glyph_stroke_t stroke_938_2[5] = {{7,24},{8,23},{7,22},{6,23},{7,24}};
static const glyph_stroke_t *strokes_938[3] = {stroke_938_0, stroke_938_1, stroke_938_2};
static const uint8_t ncoords_938[3] = {2, 5, 5};
static const glyph_stroke_t stroke_939_0[9] = {{7,0},{7,14},{6,18},{5,20},{4,21},{2,21},{1,20},{0,18},{0,16}};
static const glyph_stroke_t stroke_939_1[5] = {{4,24},{3,23},{4,22},{5,23},{4,24}};
static const glyph_stroke_t stroke_939_2[5] = {{10,24},{11,23},{10,22},{9,23},{10,24}};
static const glyph_stroke_t stroke_939_3[8] = {{14,16},{14,18},{13,20},{12,21},{10,21},{9,20},{8,18},{7,14}};
static const glyph_stroke_t *strokes_939[4] = {stroke_939_0, stroke_939_1, stroke_939_2, stroke_939_3};
static const uint8_t ncoords_939[4] = {9, 5, 5, 8};
static const glyph_stroke_t stroke_940_0[4] = {{12,22},{13,21},{7,17},{12,22}};
static const glyph_stroke_t stroke_940_1[21] = {{15,14},{14,11},{12,7},{10,4},{7,1},{5,0},{3,0},{1,1},{0,3},{0,6},{1,9},{2,11},{4,13},{6,14},{8,14},{9,13},{10,11},{12,3},{13,1},{14,0},{15,0}};
static const glyph_stroke_t *strokes_940[2] = {stroke_940_0, stroke_940_1};
static const uint8_t ncoords_940[2] = {4, 21};
static const glyph_stroke_t stroke_941_0[4] = {{10,22},{11,21},{5,17},{10,22}};
static const glyph_stroke_t stroke_941_1[16] = {{10,12},{9,13},{7,14},{4,14},{2,13},{2,11},{3,9},{6,8},{2,7},{0,5},{0,3},{1,1},{3,0},{6,0},{8,1},{10,3}};
static const glyph_stroke_t *strokes_941[2] = {stroke_941_0, stroke_941_1};
static const uint8_t ncoords_941[2] = {4, 16};
static const glyph_stroke_t stroke_942_0[8] = {{3,0},{5,7},{6,11},{6,13},{5,14},{3,14},{1,12},{0,10}};
static const glyph_stroke_t stroke_942_1[4] = {{14,22},{15,21},{9,17},{14,22}};
static const glyph_stroke_t stroke_942_2[9] = {{5,7},{7,11},{9,13},{11,14},{13,14},{15,12},{15,9},{14,4},{11,-7}};
static const glyph_stroke_t *strokes_942[3] = {stroke_942_0, stroke_942_1, stroke_942_2};
static const uint8_t ncoords_942[3] = {8, 4, 9};
static const glyph_stroke_t stroke_943_0[8] = {{6,4},{5,2},{3,0},{1,0},{0,1},{0,3},{1,7},{3,14}};
static const glyph_stroke_t stroke_943_1[4] = {{8,22},{9,21},{3,17},{8,22}};
static const glyph_stroke_t *strokes_943[2] = {stroke_943_0, stroke_943_1};
static const uint8_t ncoords_943[2] = {8, 4};
static const glyph_stroke_t stroke_945_0[21] = {{15,14},{14,11},{12,7},{10,4},{7,1},{5,0},{3,0},{1,1},{0,3},{0,6},{1,9},{2,11},{4,13},{6,14},{8,14},{9,13},{10,11},{12,3},{13,1},{14,0},{15,0}};
static const glyph_stroke_t *strokes_945[1] = {stroke_945_0};
static const uint8_t ncoords_945[1] = {21};
static const glyph_stroke_t stroke_946_0[26] = {{0,-7},{1,1},{2,7},{3,11},{4,14},{6,18},{8,20},{10,21},{12,21},{14,19},{14,16},{13,14},{12,13},{10,12},{7,12},{9,11},{11,9},{12,7},{12,4},{11,2},{10,1},{8,0},{6,0},{4,1},{3,2},{2,5}};
static const glyph_stroke_t *strokes_946[1] = {stroke_946_0};
static const uint8_t ncoords_946[1] = {26};
static const glyph_stroke_t stroke_947_0[9] = {{0,11},{2,13},{4,14},{5,14},{7,13},{8,12},{9,9},{9,5},{8,0}};
static const glyph_stroke_t stroke_947_1[6] = {{5,-7},{6,-4},{8,0},{14,9},{15,11},{16,14}};
static const glyph_stroke_t *strokes_947[2] = {stroke_947_0, stroke_947_1};
static const uint8_t ncoords_947[2] = {9, 6};
static const glyph_stroke_t stroke_948_0[23] = {{8,14},{5,14},{3,13},{1,11},{0,8},{0,5},{1,2},{2,1},{4,0},{6,0},{8,1},{10,3},{11,6},{11,9},{10,12},{8,14},{6,16},{5,18},{5,20},{6,21},{8,21},{10,20},{12,18}};
static const glyph_stroke_t *strokes_948[1] = {stroke_948_0};
static const uint8_t ncoords_948[1] = {23};
static const glyph_stroke_t stroke_949_0[16] = {{10,12},{9,13},{7,14},{4,14},{2,13},{2,11},{3,9},{6,8},{2,7},{0,5},{0,3},{1,1},{3,0},{6,0},{8,1},{10,3}};
static const glyph_stroke_t *strokes_949[1] = {stroke_949_0};
static const uint8_t ncoords_949[1] = {16};
static const glyph_stroke_t stroke_950_0[20] = {{7,21},{5,20},{4,19},{4,18},{5,17},{8,16},{11,16},{7,14},{4,12},{1,9},{0,6},{0,4},{1,2},{3,0},{6,-2},{7,-4},{7,-6},{6,-7},{4,-7},{3,-5}};
static const glyph_stroke_t *strokes_950[1] = {stroke_950_0};
static const uint8_t ncoords_950[1] = {20};
static const glyph_stroke_t stroke_951_0[8] = {{3,0},{5,7},{6,11},{6,13},{5,14},{3,14},{1,12},{0,10}};
static const glyph_stroke_t stroke_951_1[9] = {{5,7},{7,11},{9,13},{11,14},{13,14},{15,12},{15,9},{14,4},{11,-7}};
static const glyph_stroke_t *strokes_951[2] = {stroke_951_0, stroke_951_1};
static const uint8_t ncoords_951[2] = {8, 9};
static const glyph_stroke_t stroke_952_0[26] = {{0,10},{1,12},{3,14},{5,14},{6,13},{6,11},{5,6},{5,3},{6,1},{7,0},{9,0},{11,1},{13,4},{14,6},{15,9},{16,14},{16,17},{15,20},{13,21},{11,21},{10,19},{10,17},{11,14},{13,11},{15,9},{18,7}};
static const glyph_stroke_t *strokes_952[1] = {stroke_952_0};
static const uint8_t ncoords_952[1] = {26};
static const glyph_stroke_t stroke_953_0[8] = {{3,14},{1,7},{0,3},{0,1},{1,0},{3,0},{5,2},{6,4}};
static const glyph_stroke_t *strokes_953[1] = {stroke_953_0};
static const uint8_t ncoords_953[1] = {8};
static const glyph_stroke_t stroke_954_0[2] = {{0,0},{4,14}};
static const glyph_stroke_t stroke_954_1[13] = {{14,13},{13,14},{12,14},{10,13},{6,9},{4,8},{3,8},{5,7},{6,6},{8,1},{9,0},{10,0},{11,1}};
static const glyph_stroke_t *strokes_954[2] = {stroke_954_0, stroke_954_1};
static const uint8_t ncoords_954[2] = {2, 13};
static const glyph_stroke_t stroke_955_0[2] = {{1,0},{7,14}};
static const glyph_stroke_t stroke_955_1[5] = {{0,21},{2,21},{4,20},{5,19},{13,0}};
static const glyph_stroke_t *strokes_955[2] = {stroke_955_0, stroke_955_1};
static const uint8_t ncoords_955[2] = {2, 5};
static const glyph_stroke_t stroke_956_0[2] = {{0,-7},{6,14}};
static const glyph_stroke_t stroke_956_1[8] = {{5,10},{4,5},{4,2},{6,0},{8,0},{10,1},{12,3},{14,7}};
static const glyph_stroke_t stroke_956_2[8] = {{16,14},{14,7},{13,3},{13,1},{14,0},{16,0},{18,2},{19,4}};
static const glyph_stroke_t *strokes_956[3] = {stroke_956_0, stroke_956_1, stroke_956_2};
static const uint8_t ncoords_956[3] = {2, 8, 8};
static const glyph_stroke_t stroke_957_0[11] = {{0,14},{3,14},{2,8},{1,3},{0,0},{3,1},{6,3},{9,6},{11,9},{12,11},{13,14}};
static const glyph_stroke_t *strokes_957[1] = {stroke_957_0};
static const uint8_t ncoords_957[1] = {11};
static const glyph_stroke_t stroke_958_0[7] = {{7,21},{5,20},{4,19},{4,18},{5,17},{8,16},{11,16}};
static const glyph_stroke_t stroke_958_1[8] = {{8,16},{5,15},{3,14},{2,12},{2,10},{4,8},{7,7},{9,7}};
static const glyph_stroke_t stroke_958_2[11] = {{7,7},{3,6},{1,5},{0,3},{0,1},{2,-1},{6,-3},{7,-4},{7,-6},{5,-7},{3,-7}};
static const glyph_stroke_t *strokes_958[3] = {stroke_958_0, stroke_958_1, stroke_958_2};
static const uint8_t ncoords_958[3] = {7, 8, 11};
static const glyph_stroke_t stroke_959_0[17] = {{1,2},{2,1},{4,0},{6,0},{8,1},{10,3},{11,6},{11,9},{10,12},{9,13},{7,14},{5,14},{3,13},{1,11},{0,8},{0,5},{1,2}};
static const glyph_stroke_t *strokes_959[1] = {stroke_959_0};
static const uint8_t ncoords_959[1] = {17};
static const glyph_stroke_t stroke_960_0[2] = {{3,0},{7,14}};
static const glyph_stroke_t stroke_960_1[4] = {{0,11},{2,13},{5,14},{18,14}};
static const glyph_stroke_t stroke_960_2[4] = {{12,14},{13,8},{14,3},{15,0}};
static const glyph_stroke_t *strokes_960[3] = {stroke_960_0, stroke_960_1, stroke_960_2};
static const uint8_t ncoords_960[3] = {2, 4, 4};
static const glyph_stroke_t stroke_961_0[18] = {{4,8},{4,5},{5,2},{6,1},{8,0},{10,0},{12,1},{14,3},{15,6},{15,9},{14,12},{13,13},{11,14},{9,14},{7,13},{5,11},{4,8},{0,-7}};
static const glyph_stroke_t *strokes_961[1] = {stroke_961_0};
static const uint8_t ncoords_961[1] = {18};
static const glyph_stroke_t stroke_963_0[17] = {{7,14},{9,13},{10,12},{11,9},{11,6},{10,3},{8,1},{6,0},{4,0},{2,1},{1,2},{0,5},{0,8},{1,11},{3,13},{5,14},{15,14}};
static const glyph_stroke_t *strokes_963[1] = {stroke_963_0};
static const uint8_t ncoords_963[1] = {17};
static const glyph_stroke_t stroke_964_0[2] = {{6,0},{9,14}};
static const glyph_stroke_t stroke_964_1[4] = {{0,11},{2,13},{5,14},{16,14}};
static const glyph_stroke_t *strokes_964[2] = {stroke_964_0, stroke_964_1};
static const uint8_t ncoords_964[2] = {2, 4};
static const glyph_stroke_t stroke_965_0[15] = {{0,10},{1,12},{3,14},{5,14},{6,13},{6,11},{4,5},{4,2},{6,0},{8,0},{11,1},{13,3},{15,7},{16,11},{16,14}};
static const glyph_stroke_t *strokes_965[1] = {stroke_965_0};
static const uint8_t ncoords_965[1] = {15};
static const glyph_stroke_t stroke_966_0[20] = {{5,13},{3,12},{1,10},{0,7},{0,4},{1,2},{2,1},{4,0},{7,0},{10,1},{13,3},{15,6},{16,9},{16,12},{14,14},{12,14},{10,12},{8,8},{6,3},{3,-7}};
static const glyph_stroke_t *strokes_966[1] = {stroke_966_0};
static const uint8_t ncoords_966[1] = {20};
static const glyph_stroke_t stroke_967_0[6] = {{0,-7},{1,-5},{3,-2},{13,9},{15,12},{16,14}};
static const glyph_stroke_t stroke_967_1[6] = {{1,14},{3,14},{5,12},{11,-5},{13,-7},{15,-7}};
static const glyph_stroke_t *strokes_967[2] = {stroke_967_0, stroke_967_1};
static const uint8_t ncoords_967[2] = {6, 6};
static const glyph_stroke_t stroke_968_0[2] = {{7,-7},{15,21}};
static const glyph_stroke_t stroke_968_1[16] = {{0,10},{1,12},{3,14},{5,14},{6,13},{6,11},{5,6},{5,3},{6,1},{8,0},{10,0},{13,1},{15,3},{17,6},{19,11},{20,14}};
static const glyph_stroke_t *strokes_968[2] = {stroke_968_0, stroke_968_1};
static const uint8_t ncoords_968[2] = {2, 16};
static const glyph_stroke_t stroke_969_0[10] = {{5,14},{3,13},{1,10},{0,7},{0,4},{1,1},{2,0},{4,0},{6,1},{8,4}};
static const glyph_stroke_t stroke_969_1[11] = {{9,8},{8,4},{9,1},{10,0},{12,0},{14,1},{16,4},{17,7},{17,10},{16,13},{15,14}};
static const glyph_stroke_t *strokes_969[2] = {stroke_969_0, stroke_969_1};
static const uint8_t ncoords_969[2] = {10, 11};
static const glyph_stroke_t stroke_970_0[8] = {{7,4},{6,2},{4,0},{2,0},{1,1},{1,3},{2,7},{4,14}};
static const glyph_stroke_t stroke_970_1[5] = {{1,19},{0,18},{1,17},{2,18},{1,19}};
static const glyph_stroke_t stroke_970_2[5] = {{7,19},{8,18},{7,17},{6,18},{7,19}};
static const glyph_stroke_t *strokes_970[3] = {stroke_970_0, stroke_970_1, stroke_970_2};
static const uint8_t ncoords_970[3] = {8, 5, 5};
static const glyph_stroke_t stroke_971_0[15] = {{0,10},{1,12},{3,14},{5,14},{6,13},{6,11},{4,5},{4,2},{6,0},{8,0},{11,1},{13,3},{15,7},{16,11},{16,14}};
static const glyph_stroke_t stroke_971_1[5] = {{12,19},{13,18},{12,17},{11,18},{12,19}};
static const glyph_stroke_t stroke_971_2[5] = {{6,19},{5,18},{6,17},{7,18},{6,19}};
static const glyph_stroke_t *strokes_971[3] = {stroke_971_0, stroke_971_1, stroke_971_2};
static const uint8_t ncoords_971[3] = {15, 5, 5};
static const glyph_stroke_t stroke_972_0[17] = {{5,14},{3,13},{1,11},{0,8},{0,5},{1,2},{2,1},{4,0},{6,0},{8,1},{10,3},{11,6},{11,9},{10,12},{9,13},{7,14},{5,14}};
static const glyph_stroke_t stroke_972_1[4] = {{10,22},{11,21},{5,17},{10,22}};
static const glyph_stroke_t *strokes_972[2] = {stroke_972_0, stroke_972_1};
static const uint8_t ncoords_972[2] = {17, 4};
static const glyph_stroke_t stroke_973_0[15] = {{0,10},{1,12},{3,14},{5,14},{6,13},{6,11},{4,5},{4,2},{6,0},{8,0},{11,1},{13,3},{15,7},{16,11},{16,14}};
static const glyph_stroke_t stroke_973_1[4] = {{14,22},{15,21},{9,17},{14,22}};
static const glyph_stroke_t *strokes_973[2] = {stroke_973_0, stroke_973_1};
static const uint8_t ncoords_973[2] = {15, 4};
static const glyph_stroke_t stroke_974_0[10] = {{5,14},{3,13},{1,10},{0,7},{0,4},{1,1},{2,0},{4,0},{6,1},{8,4}};
static const glyph_stroke_t stroke_974_1[11] = {{9,8},{8,4},{9,1},{10,0},{12,0},{14,1},{16,4},{17,7},{17,10},{16,13},{15,14}};
static const glyph_stroke_t stroke_974_2[4] = {{14,22},{15,21},{9,17},{14,22}};
static const glyph_stroke_t *strokes_974[3] = {stroke_974_0, stroke_974_1, stroke_974_2};
static const uint8_t ncoords_974[3] = {10, 11, 4};
static const glyph_stroke_t stroke_8592_0[3] = {{3,11},{0,9},{3,7}};
static const glyph_stroke_t stroke_8592_1[3] = {{6,14},{1,9},{6,4}};
static const glyph_stroke_t stroke_8592_2[2] = {{0,9},{18,9}};
static const glyph_stroke_t *strokes_8592[3] = {stroke_8592_0, stroke_8592_1, stroke_8592_2};
static const uint8_t ncoords_8592[3] = {3, 3, 2};
static const glyph_stroke_t stroke_8593_0[3] = {{3,15},{5,18},{7,15}};
static const glyph_stroke_t stroke_8593_1[3] = {{0,12},{5,17},{10,12}};
static const glyph_stroke_t stroke_8593_2[2] = {{5,18},{5,0}};
static const glyph_stroke_t *strokes_8593[3] = {stroke_8593_0, stroke_8593_1, stroke_8593_2};
static const uint8_t ncoords_8593[3] = {3, 3, 2};
static const glyph_stroke_t stroke_8594_0[3] = {{15,11},{18,9},{15,7}};
static const glyph_stroke_t stroke_8594_1[3] = {{12,14},{17,9},{12,4}};
static const glyph_stroke_t stroke_8594_2[2] = {{0,9},{18,9}};
static const glyph_stroke_t *strokes_8594[3] = {stroke_8594_0, stroke_8594_1, stroke_8594_2};
static const uint8_t ncoords_8594[3] = {3, 3, 2};
static const glyph_stroke_t stroke_8595_0[3] = {{3,3},{5,0},{7,3}};
static const glyph_stroke_t stroke_8595_1[3] = {{0,6},{5,1},{10,6}};
static const glyph_stroke_t stroke_8595_2[2] = {{5,18},{5,0}};
static const glyph_stroke_t *strokes_8595[3] = {stroke_8595_0, stroke_8595_1, stroke_8595_2};
static const uint8_t ncoords_8595[3] = {3, 3, 2};
static const glyph_stroke_t stroke_8596_0[3] = {{15,11},{18,9},{15,7}};
static const glyph_stroke_t stroke_8596_1[3] = {{12,14},{17,9},{12,4}};
static const glyph_stroke_t stroke_8596_2[3] = {{3,11},{0,9},{3,7}};
static const glyph_stroke_t stroke_8596_3[3] = {{6,14},{1,9},{6,4}};
static const glyph_stroke_t stroke_8596_4[2] = {{0,9},{18,9}};
static const glyph_stroke_t *strokes_8596[5] = {stroke_8596_0, stroke_8596_1, stroke_8596_2, stroke_8596_3, stroke_8596_4};
static const uint8_t ncoords_8596[5] = {3, 3, 3, 3, 2};
static const glyph_stroke_t stroke_8597_0[3] = {{3,3},{5,0},{7,3}};
static const glyph_stroke_t stroke_8597_1[3] = {{0,6},{5,1},{10,6}};
static const glyph_stroke_t stroke_8597_2[3] = {{3,15},{5,18},{7,15}};
static const glyph_stroke_t stroke_8597_3[3] = {{0,12},{5,17},{10,12}};
static const glyph_stroke_t stroke_8597_4[2] = {{5,18},{5,0}};
static const glyph_stroke_t *strokes_8597[5] = {stroke_8597_0, stroke_8597_1, stroke_8597_2, stroke_8597_3, stroke_8597_4};
static const uint8_t ncoords_8597[5] = {3, 3, 3, 3, 2};
static const glyph_stroke_t stroke_8656_0[3] = {{3,11},{0,9},{3,7}};
static const glyph_stroke_t stroke_8656_1[3] = {{6,14},{1,9},{6,4}};
static const glyph_stroke_t stroke_8656_2[2] = {{18,10},{2,10}};
static const glyph_stroke_t stroke_8656_3[2] = {{2,8},{18,8}};
static const glyph_stroke_t *strokes_8656[4] = {stroke_8656_0, stroke_8656_1, stroke_8656_2, stroke_8656_3};
static const uint8_t ncoords_8656[4] = {3, 3, 2, 2};
static const glyph_stroke_t stroke_8657_0[3] = {{3,15},{5,18},{7,15}};
static const glyph_stroke_t stroke_8657_1[3] = {{0,12},{5,17},{10,12}};
static const glyph_stroke_t stroke_8657_2[2] = {{4,0},{4,16}};
static const glyph_stroke_t stroke_8657_3[2] = {{6,16},{6,0}};
static const glyph_stroke_t *strokes_8657[4] = {stroke_8657_0, stroke_8657_1, stroke_8657_2, stroke_8657_3};
static const uint8_t ncoords_8657[4] = {3, 3, 2, 2};
static const glyph_stroke_t stroke_8658_0[3] = {{15,11},{18,9},{15,7}};
static const glyph_stroke_t stroke_8658_1[3] = {{12,14},{17,9},{12,4}};
static const glyph_stroke_t stroke_8658_2[2] = {{16,10},{0,10}};
static const glyph_stroke_t stroke_8658_3[2] = {{0,8},{16,8}};
static const glyph_stroke_t *strokes_8658[4] = {stroke_8658_0, stroke_8658_1, stroke_8658_2, stroke_8658_3};
static const uint8_t ncoords_8658[4] = {3, 3, 2, 2};
static const glyph_stroke_t stroke_8659_0[3] = {{3,3},{5,0},{7,3}};
static const glyph_stroke_t stroke_8659_1[3] = {{0,6},{5,1},{10,6}};
static const glyph_stroke_t stroke_8659_2[2] = {{4,2},{4,18}};
static const glyph_stroke_t stroke_8659_3[2] = {{6,18},{6,2}};
static const glyph_stroke_t *strokes_8659[4] = {stroke_8659_0, stroke_8659_1, stroke_8659_2, stroke_8659_3};
static const uint8_t ncoords_8659[4] = {3, 3, 2, 2};
static const glyph_stroke_t stroke_8660_0[3] = {{3,11},{0,9},{3,7}};
static const glyph_stroke_t stroke_8660_1[3] = {{6,14},{1,9},{6,4}};
static const glyph_stroke_t stroke_8660_2[2] = {{16,10},{2,10}};
static const glyph_stroke_t stroke_8660_3[2] = {{2,8},{16,8}};
static const glyph_stroke_t stroke_8660_4[3] = {{15,11},{18,9},{15,7}};
static const glyph_stroke_t stroke_8660_5[3] = {{12,14},{17,9},{12,4}};
static const glyph_stroke_t *strokes_8660[6] = {stroke_8660_0, stroke_8660_1, stroke_8660_2, stroke_8660_3, stroke_8660_4, stroke_8660_5};
static const uint8_t ncoords_8660[6] = {3, 3, 2, 2, 3, 3};
static const glyph_stroke_t stroke_8661_0[3] = {{3,3},{5,0},{7,3}};
static const glyph_stroke_t stroke_8661_1[3] = {{0,6},{5,1},{10,6}};
static const glyph_stroke_t stroke_8661_2[2] = {{4,2},{4,16}};
static const glyph_stroke_t stroke_8661_3[2] = {{6,16},{6,2}};
static const glyph_stroke_t stroke_8661_4[3] = {{3,15},{5,18},{7,15}};
static const glyph_stroke_t stroke_8661_5[3] = {{0,12},{5,17},{10,12}};
static const glyph_stroke_t *strokes_8661[6] = {stroke_8661_0, stroke_8661_1, stroke_8661_2, stroke_8661_3, stroke_8661_4, stroke_8661_5};
static const uint8_t ncoords_8661[6] = {3, 3, 2, 2, 3, 3};
static const glyph_stroke_t stroke_8706_0[25] = {{3,18},{3,19},{4,20},{6,21},{9,21},{11,20},{12,19},{13,16},{13,11},{12,6},{11,3},{9,1},{6,0},{4,0},{2,1},{1,2},{0,4},{0,7},{1,10},{3,13},{6,14},{8,14},{10,13},{11,12},{12,9}};
static const glyph_stroke_t *strokes_8706[1] = {stroke_8706_0};
static const uint8_t ncoords_8706[1] = {25};
static const glyph_stroke_t stroke_8707_0[4] = {{0,0},{13,0},{13,21},{0,21}};
static const glyph_stroke_t stroke_8707_1[2] = {{5,11},{13,11}};
static const glyph_stroke_t *strokes_8707[2] = {stroke_8707_0, stroke_8707_1};
static const uint8_t ncoords_8707[2] = {4, 2};
static const glyph_stroke_t stroke_8710_0[4] = {{0,0},{8,21},{16,0},{0,0}};
static const glyph_stroke_t *strokes_8710[1] = {stroke_8710_0};
static const uint8_t ncoords_8710[1] = {4};
static const glyph_stroke_t stroke_8711_0[4] = {{8,0},{0,21},{16,21},{8,0}};
static const glyph_stroke_t *strokes_8711[1] = {stroke_8711_0};
static const uint8_t ncoords_8711[1] = {4};
static const glyph_stroke_t stroke_8714_0[2] = {{0,9},{12,9}};
static const glyph_stroke_t stroke_8714_1[12] = {{16,17},{9,17},{5,16},{3,15},{1,13},{0,10},{0,8},{1,5},{3,3},{5,2},{9,1},{16,1}};
static const glyph_stroke_t *strokes_8714[2] = {stroke_8714_0, stroke_8714_1};
static const uint8_t ncoords_8714[2] = {2, 12};
static const glyph_stroke_t stroke_8723_0[2] = {{8,0},{8,17}};
static const glyph_stroke_t stroke_8723_1[2] = {{16,17},{0,17}};
static const glyph_stroke_t stroke_8723_2[2] = {{0,9},{16,9}};
static const glyph_stroke_t *strokes_8723[3] = {stroke_8723_0, stroke_8723_1, stroke_8723_2};
static const uint8_t ncoords_8723[3] = {2, 2, 2};
static const glyph_stroke_t stroke_8728_0[13] = {{1,14},{3,13},{5,13},{7,14},{8,16},{8,18},{7,20},{5,21},{3,21},{1,20},{0,18},{0,16},{1,14}};
static const glyph_stroke_t *strokes_8728[1] = {stroke_8728_0};
static const uint8_t ncoords_8728[1] = {13};
static const glyph_stroke_t stroke_8730_0[3] = {{0,14},{4,14},{10,2}};
static const glyph_stroke_t stroke_8730_1[2] = {{3,14},{10,0}};
static const glyph_stroke_t stroke_8730_2[2] = {{19,25},{10,0}};
static const glyph_stroke_t *strokes_8730[3] = {stroke_8730_0, stroke_8730_1, stroke_8730_2};
static const uint8_t ncoords_8730[3] = {3, 2, 2};
static const glyph_stroke_t stroke_8733_0[20] = {{17,4},{15,4},{13,5},{11,7},{8,11},{7,12},{5,13},{3,13},{1,12},{0,10},{0,8},{1,6},{3,5},{5,5},{7,6},{8,7},{11,11},{13,13},{15,14},{17,14}};
static const glyph_stroke_t *strokes_8733[1] = {stroke_8733_0};
static const uint8_t ncoords_8733[1] = {20};
static const glyph_stroke_t stroke_8734_0[25] = {{1,6},{3,5},{5,5},{7,6},{8,7},{11,11},{12,12},{14,13},{16,13},{18,12},{19,10},{19,8},{18,6},{16,5},{14,5},{12,6},{11,7},{8,11},{7,12},{5,13},{3,13},{1,12},{0,10},{0,8},{1,6}};
static const glyph_stroke_t *strokes_8734[1] = {stroke_8734_0};
static const uint8_t ncoords_8734[1] = {25};
static const glyph_stroke_t stroke_8736_0[3] = {{18,25},{0,0},{18,0}};
static const glyph_stroke_t *strokes_8736[1] = {stroke_8736_0};
static const uint8_t ncoords_8736[1] = {3};
static const glyph_stroke_t stroke_8741_0[2] = {{0,-7},{0,25}};
static const glyph_stroke_t stroke_8741_1[2] = {{6,25},{6,-7}};
static const glyph_stroke_t *strokes_8741[2] = {stroke_8741_0, stroke_8741_1};
static const uint8_t ncoords_8741[2] = {2, 2};
static const glyph_stroke_t stroke_8743_0[3] = {{0,1},{8,17},{16,1}};
static const glyph_stroke_t *strokes_8743[1] = {stroke_8743_0};
static const uint8_t ncoords_8743[1] = {3};
static const glyph_stroke_t stroke_8744_0[3] = {{0,17},{8,1},{16,17}};
static const glyph_stroke_t *strokes_8744[1] = {stroke_8744_0};
static const uint8_t ncoords_8744[1] = {3};
static const glyph_stroke_t stroke_8745_0[12] = {{0,1},{0,8},{1,12},{2,14},{4,16},{7,17},{9,17},{12,16},{14,14},{15,12},{16,8},{16,1}};
static const glyph_stroke_t *strokes_8745[1] = {stroke_8745_0};
static const uint8_t ncoords_8745[1] = {12};
static const glyph_stroke_t stroke_8746_0[12] = {{0,17},{0,10},{1,6},{2,4},{4,2},{7,1},{9,1},{12,2},{14,4},{15,6},{16,10},{16,17}};
static const glyph_stroke_t *strokes_8746[1] = {stroke_8746_0};
static const uint8_t ncoords_8746[1] = {12};
static const glyph_stroke_t stroke_8747_0[17] = {{0,-5},{0,-6},{1,-7},{3,-7},{5,-6},{6,-5},{7,-3},{8,1},{10,13},{11,17},{12,20},{13,22},{15,24},{17,25},{19,25},{20,24},{20,23}};
static const glyph_stroke_t *strokes_8747[1] = {stroke_8747_0};
static const uint8_t ncoords_8747[1] = {17};
static const glyph_stroke_t stroke_8756_0[5] = {{1,2},{0,1},{1,0},{2,1},{1,2}};
static const glyph_stroke_t stroke_8756_1[5] = {{10,18},{9,17},{10,16},{11,17},{10,18}};
static const glyph_stroke_t stroke_8756_2[5] = {{19,2},{18,1},{19,0},{20,1},{19,2}};
static const glyph_stroke_t *strokes_8756[3] = {stroke_8756_0, stroke_8756_1, stroke_8756_2};
static const uint8_t ncoords_8756[3] = {5, 5, 5};
static const glyph_stroke_t stroke_8757_0[5] = {{10,0},{9,1},{10,2},{11,1},{10,0}};
static const glyph_stroke_t stroke_8757_1[5] = {{1,16},{0,17},{1,18},{2,17},{1,16}};
static const glyph_stroke_t stroke_8757_2[5] = {{19,16},{18,17},{19,18},{20,17},{19,16}};
static const glyph_stroke_t *strokes_8757[3] = {stroke_8757_0, stroke_8757_1, stroke_8757_2};
static const uint8_t ncoords_8757[3] = {5, 5, 5};
static const glyph_stroke_t stroke_62007_0[5] = {{1,2},{0,1},{1,0},{2,1},{1,2}};
static const glyph_stroke_t stroke_62007_1[5] = {{1,16},{0,17},{1,18},{2,17},{1,16}};
static const glyph_stroke_t stroke_62007_2[5] = {{17,16},{16,17},{17,18},{18,17},{17,16}};
static const glyph_stroke_t stroke_62007_3[5] = {{17,2},{16,1},{17,0},{18,1},{17,2}};
static const glyph_stroke_t *strokes_62007[4] = {stroke_62007_0, stroke_62007_1, stroke_62007_2, stroke_62007_3};
static const uint8_t ncoords_62007[4] = {5, 5, 5, 5};
static const glyph_stroke_t stroke_8764_0[10] = {{0,9},{1,11},{3,12},{5,12},{7,11},{11,8},{13,7},{15,7},{17,8},{18,10}};
static const glyph_stroke_t *strokes_8764[1] = {stroke_8764_0};
static const uint8_t ncoords_8764[1] = {10};
static const glyph_stroke_t stroke_8765_0[10] = {{0,10},{1,8},{3,7},{5,7},{7,8},{11,11},{13,12},{15,12},{17,11},{18,9}};
static const glyph_stroke_t *strokes_8765[1] = {stroke_8765_0};
static const uint8_t ncoords_8765[1] = {10};
static const glyph_stroke_t stroke_8770_0[10] = {{0,6},{1,8},{3,9},{5,9},{7,8},{11,5},{13,4},{15,4},{17,5},{18,7}};
static const glyph_stroke_t stroke_8770_1[2] = {{18,12},{0,12}};
static const glyph_stroke_t *strokes_8770[2] = {stroke_8770_0, stroke_8770_1};
static const uint8_t ncoords_8770[2] = {10, 2};
static const glyph_stroke_t stroke_8771_0[2] = {{0,6},{18,6}};
static const glyph_stroke_t stroke_8771_1[10] = {{18,13},{17,11},{15,10},{13,10},{11,11},{7,14},{5,15},{3,15},{1,14},{0,12}};
static const glyph_stroke_t *strokes_8771[2] = {stroke_8771_0, stroke_8771_1};
static const uint8_t ncoords_8771[2] = {2, 10};
static const glyph_stroke_t stroke_8773_0[2] = {{0,6},{18,6}};
static const glyph_stroke_t stroke_8773_1[2] = {{18,12},{0,12}};
static const glyph_stroke_t stroke_8773_2[10] = {{0,15},{1,17},{3,18},{5,18},{7,17},{10,15},{13,14},{15,14},{17,15},{18,17}};
static const glyph_stroke_t *strokes_8773[3] = {stroke_8773_0, stroke_8773_1, stroke_8773_2};
static const uint8_t ncoords_8773[3] = {2, 2, 10};
static const glyph_stroke_t stroke_8776_0[10] = {{0,6},{1,8},{3,9},{5,9},{7,8},{11,5},{13,4},{15,4},{17,5},{18,7}};
static const glyph_stroke_t stroke_8776_1[10] = {{18,13},{17,11},{15,10},{13,10},{11,11},{7,14},{5,15},{3,15},{1,14},{0,12}};
static const glyph_stroke_t *strokes_8776[2] = {stroke_8776_0, stroke_8776_1};
static const uint8_t ncoords_8776[2] = {10, 10};
static const glyph_stroke_t stroke_8779_0[10] = {{0,3},{1,5},{3,6},{5,6},{7,5},{11,2},{13,1},{15,1},{17,2},{18,4}};
static const glyph_stroke_t stroke_8779_1[10] = {{18,10},{17,8},{15,7},{13,7},{11,8},{7,11},{5,12},{3,12},{1,11},{0,9}};
static const glyph_stroke_t stroke_8779_2[10] = {{0,15},{1,17},{3,18},{5,18},{7,17},{11,14},{13,13},{15,13},{17,14},{18,16}};
static const glyph_stroke_t *strokes_8779[3] = {stroke_8779_0, stroke_8779_1, stroke_8779_2};
static const uint8_t ncoords_8779[3] = {10, 10, 10};
static const glyph_stroke_t stroke_8800_0[2] = {{0,12},{18,12}};
static const glyph_stroke_t stroke_8800_1[2] = {{16,18},{2,0}};
static const glyph_stroke_t stroke_8800_2[2] = {{0,6},{18,6}};
static const glyph_stroke_t *strokes_8800[3] = {stroke_8800_0, stroke_8800_1, stroke_8800_2};
static const uint8_t ncoords_8800[3] = {2, 2, 2};
static const glyph_stroke_t stroke_8801_0[2] = {{0,4},{18,4}};
static const glyph_stroke_t stroke_8801_1[2] = {{18,9},{0,9}};
static const glyph_stroke_t stroke_8801_2[2] = {{0,14},{18,14}};
static const glyph_stroke_t *strokes_8801[3] = {stroke_8801_0, stroke_8801_1, stroke_8801_2};
static const uint8_t ncoords_8801[3] = {2, 2, 2};
static const glyph_stroke_t stroke_8804_0[2] = {{0,5},{16,5}};
static const glyph_stroke_t stroke_8804_1[3] = {{16,21},{0,14},{16,7}};
static const glyph_stroke_t *strokes_8804[2] = {stroke_8804_0, stroke_8804_1};
static const uint8_t ncoords_8804[2] = {2, 3};
static const glyph_stroke_t stroke_8805_0[3] = {{0,21},{16,14},{0,7}};
static const glyph_stroke_t stroke_8805_1[2] = {{0,5},{16,5}};
static const glyph_stroke_t *strokes_8805[2] = {stroke_8805_0, stroke_8805_1};
static const uint8_t ncoords_8805[2] = {3, 2};
static const glyph_stroke_t stroke_8806_0[2] = {{0,0},{16,0}};
static const glyph_stroke_t stroke_8806_1[2] = {{16,5},{0,5}};
static const glyph_stroke_t stroke_8806_2[3] = {{16,7},{0,14},{16,21}};
static const glyph_stroke_t *strokes_8806[3] = {stroke_8806_0, stroke_8806_1, stroke_8806_2};
static const uint8_t ncoords_8806[3] = {2, 2, 3};
static const glyph_stroke_t stroke_8807_0[2] = {{0,0},{16,0}};
static const glyph_stroke_t stroke_8807_1[2] = {{16,5},{0,5}};
static const glyph_stroke_t stroke_8807_2[3] = {{0,7},{16,14},{0,21}};
static const glyph_stroke_t *strokes_8807[3] = {stroke_8807_0, stroke_8807_1, stroke_8807_2};
static const uint8_t ncoords_8807[3] = {2, 2, 3};
static const glyph_stroke_t stroke_8834_0[12] = {{16,1},{9,1},{5,2},{3,3},{1,5},{0,8},{0,10},{1,13},{3,15},{5,16},{9,17},{16,17}};
static const glyph_stroke_t *strokes_8834[1] = {stroke_8834_0};
static const uint8_t ncoords_8834[1] = {12};
static const glyph_stroke_t stroke_8835_0[12] = {{0,1},{7,1},{11,2},{13,3},{15,5},{16,8},{16,10},{15,13},{13,15},{11,16},{7,17},{0,17}};
static const glyph_stroke_t *strokes_8835[1] = {stroke_8835_0};
static const uint8_t ncoords_8835[1] = {12};
static const glyph_stroke_t stroke_8869_0[2] = {{0,0},{18,0}};
static const glyph_stroke_t stroke_8869_1[2] = {{9,25},{9,0}};
static const glyph_stroke_t *strokes_8869[2] = {stroke_8869_0, stroke_8869_1};
static const uint8_t ncoords_8869[2] = {2, 2};
static const glyph_stroke_t stroke_9001_0[3] = {{7,25},{0,9},{7,-7}};
static const glyph_stroke_t *strokes_9001[1] = {stroke_9001_0};
static const uint8_t ncoords_9001[1] = {3};
static const glyph_stroke_t stroke_9002_0[3] = {{0,25},{7,9},{0,-7}};
static const glyph_stroke_t *strokes_9002[1] = {stroke_9002_0};
static const uint8_t ncoords_9002[1] = {3};
static const glyph_data_t glyph_data[432] = {
	{ 0x00000020, 0, 0, 0, 0, -6, 6, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x00000021, 0, 0, 2, 21, -4, 6, 0, 2, strokes_33, ncoords_33 },
	{ 0x00000022, 0, 14, 8, 21, -4, 12, 0, 2, strokes_34, ncoords_34 },
	{ 0x00000023, 0, -7, 15, 25, -3, 18, 0, 4, strokes_35, ncoords_35 },
	{ 0x00000024, 0, -4, 14, 25, -3, 17, 0, 3, strokes_36, ncoords_36 },
	{ 0x00000025, 0, 0, 18, 21, -3, 21, 0, 2, strokes_37, ncoords_37 },
	{ 0x00000026, 0, 0, 20, 21, -3, 23, 0, 1, strokes_38, ncoords_38 },
	{ 0x00000027, 0, 15, 2, 21, -4, 6, 0, 1, strokes_39, ncoords_39 },
	{ 0x00000028, 0, -7, 7, 25, -4, 10, 0, 1, strokes_40, ncoords_40 },
	{ 0x00000029, 0, -7, 7, 25, -3, 11, 0, 1, strokes_41, ncoords_41 },
	{ 0x0000002a, 0, 3, 10, 15, -3, 13, 0, 3, strokes_42, ncoords_42 },
	{ 0x0000002b, 0, 0, 18, 18, -4, 22, 0, 2, strokes_43, ncoords_43 },
	{ 0x0000002c, 0, -3, 2, 2, -3, 5, 0, 1, strokes_44, ncoords_44 },
	{ 0x0000002d, 0, 9, 10, 9, -3, 13, 0, 1, strokes_45, ncoords_45 },
	{ 0x0000002e, 0, 0, 2, 2, -3, 5, 0, 1, strokes_46, ncoords_46 },
	{ 0x0000002f, 0, -7, 18, 25, -2, 20, 0, 1, strokes_47, ncoords_47 },
	{ 0x00000030, 0, 0, 14, 21, -3, 17, 0, 1, strokes_48, ncoords_48 },
	{ 0x00000031, 0, 0, 5, 21, -6, 14, 0, 1, strokes_49, ncoords_49 },
	{ 0x00000032, 0, 0, 14, 21, -3, 17, 0, 1, strokes_50, ncoords_50 },
	{ 0x00000033, 0, 0, 14, 21, -3, 17, 0, 1, strokes_51, ncoords_51 },
	{ 0x00000034, 0, 0, 15, 21, -3, 17, 0, 1, strokes_52, ncoords_52 },
	{ 0x00000035, 0, 0, 14, 21, -3, 17, 0, 1, strokes_53, ncoords_53 },
	{ 0x00000036, 0, 0, 13, 21, -4, 16, 0, 1, strokes_54, ncoords_54 },
	{ 0x00000037, 0, 0, 14, 21, -3, 17, 0, 1, strokes_55, ncoords_55 },
	{ 0x00000038, 0, 0, 14, 21, -3, 17, 0, 1, strokes_56, ncoords_56 },
	{ 0x00000039, 0, 0, 13, 21, -3, 17, 0, 1, strokes_57, ncoords_57 },
	{ 0x0000003a, 0, 0, 2, 9, -3, 5, 0, 2, strokes_58, ncoords_58 },
	{ 0x0000003b, 0, -3, 2, 9, -3, 5, 0, 2, strokes_59, ncoords_59 },
	{ 0x0000003c, 0, 0, 16, 18, -4, 20, 0, 1, strokes_60, ncoords_60 },
	{ 0x0000003d, 0, 6, 18, 12, -4, 22, 0, 2, strokes_61, ncoords_61 },
	{ 0x0000003e, 0, 0, 16, 18, -4, 20, 0, 1, strokes_62, ncoords_62 },
	{ 0x0000003f, 0, 0, 12, 21, -3, 15, 0, 2, strokes_63, ncoords_63 },
	{ 0x00000040, 0, 0, 21, 21, -3, 24, 0, 4, strokes_64, ncoords_64 },
	{ 0x00000041, 0, 0, 16, 21, -1, 17, 0, 2, strokes_65, ncoords_65 },
	{ 0x00000042, 0, 0, 14, 21, -4, 17, 0, 2, strokes_66, ncoords_66 },
	{ 0x00000043, 0, 0, 15, 21, -3, 18, 0, 1, strokes_67, ncoords_67 },
	{ 0x00000044, 0, 0, 14, 21, -4, 17, 0, 1, strokes_68, ncoords_68 },
	{ 0x00000045, 0, 0, 13, 21, -4, 15, 0, 2, strokes_69, ncoords_69 },
	{ 0x00000046, 0, 0, 13, 21, -4, 14, 0, 2, strokes_70, ncoords_70 },
	{ 0x00000047, 0, 0, 15, 21, -3, 18, 0, 1, strokes_71, ncoords_71 },
	{ 0x00000048, 0, 0, 14, 21, -4, 18, 0, 3, strokes_72, ncoords_72 },
	{ 0x00000049, 0, 0, 0, 21, -4, 4, 0, 1, strokes_73, ncoords_73 },
	{ 0x0000004a, 0, 0, 10, 21, -2, 14, 0, 1, strokes_74, ncoords_74 },
	{ 0x0000004b, 0, 0, 14, 21, -4, 17, 0, 3, strokes_75, ncoords_75 },
	{ 0x0000004c, 0, 0, 12, 21, -4, 13, 0, 1, strokes_76, ncoords_76 },
	{ 0x0000004d, 0, 0, 16, 21, -4, 20, 0, 1, strokes_77, ncoords_77 },
	{ 0x0000004e, 0, 0, 14, 21, -4, 18, 0, 1, strokes_78, ncoords_78 },
	{ 0x0000004f, 0, 0, 16, 21, -3, 19, 0, 1, strokes_79, ncoords_79 },
	{ 0x00000050, 0, 0, 14, 21, -4, 17, 0, 1, strokes_80, ncoords_80 },
	{ 0x00000051, 0, -2, 16, 21, -3, 19, 0, 2, strokes_81, ncoords_81 },
	{ 0x00000052, 0, 0, 14, 21, -4, 17, 0, 2, strokes_82, ncoords_82 },
	{ 0x00000053, 0, 0, 14, 21, -3, 17, 0, 1, strokes_83, ncoords_83 },
	{ 0x00000054, 0, 0, 14, 21, -1, 15, 0, 2, strokes_84, ncoords_84 },
	{ 0x00000055, 0, 0, 14, 21, -4, 18, 0, 1, strokes_85, ncoords_85 },
	{ 0x00000056, 0, 0, 16, 21, -1, 17, 0, 1, strokes_86, ncoords_86 },
	{ 0x00000057, 0, 0, 20, 21, -2, 22, 0, 1, strokes_87, ncoords_87 },
	{ 0x00000058, 0, 0, 14, 21, -3, 17, 0, 2, strokes_88, ncoords_88 },
	{ 0x00000059, 0, 0, 16, 21, -1, 17, 0, 2, strokes_89, ncoords_89 },
	{ 0x0000005a, 0, 0, 14, 21, -3, 17, 0, 1, strokes_90, ncoords_90 },
	{ 0x0000005b, 0, -7, 7, 25, -4, 10, 0, 1, strokes_91, ncoords_91 },
	{ 0x0000005c, 0, -3, 14, 21, 0, 14, 0, 1, strokes_92, ncoords_92 },
	{ 0x0000005d, 0, -7, 7, 25, -3, 11, 0, 1, strokes_93, ncoords_93 },
	{ 0x0000005e, 0, 9, 16, 23, 0, 16, 0, 1, strokes_94, ncoords_94 },
	{ 0x0000005f, 0, -7, 18, -7, 0, 18, 0, 1, strokes_95, ncoords_95 },
	{ 0x00000060, 0, 11, 2, 16, -3, 5, 0, 1, strokes_96, ncoords_96 },
	{ 0x00000061, 0, 0, 12, 14, -3, 16, 0, 2, strokes_97, ncoords_97 },
	{ 0x00000062, 0, 0, 12, 21, -4, 15, 0, 2, strokes_98, ncoords_98 },
	{ 0x00000063, 0, 0, 12, 14, -3, 15, 0, 1, strokes_99, ncoords_99 },
	{ 0x00000064, 0, 0, 12, 21, -3, 16, 0, 2, strokes_100, ncoords_100 },
	{ 0x00000065, 0, 0, 12, 14, -3, 15, 0, 1, strokes_101, ncoords_101 },
	{ 0x00000066, 0, 0, 8, 21, -2, 10, 0, 2, strokes_102, ncoords_102 },
	{ 0x00000067, 0, -7, 12, 14, -3, 16, 0, 2, strokes_103, ncoords_103 },
	{ 0x00000068, 0, 0, 11, 21, -4, 15, 0, 2, strokes_104, ncoords_104 },
	{ 0x00000069, 0, 0, 2, 22, -3, 5, 0, 2, strokes_105, ncoords_105 },
	{ 0x0000006a, 0, -7, 6, 22, -1, 9, 0, 2, strokes_106, ncoords_106 },
	{ 0x0000006b, 0, 0, 11, 21, -4, 13, 0, 3, strokes_107, ncoords_107 },
	{ 0x0000006c, 0, 0, 0, 21, -4, 4, 0, 1, strokes_108, ncoords_108 },
	{ 0x0000006d, 0, 0, 22, 14, -4, 26, 0, 3, strokes_109, ncoords_109 },
	{ 0x0000006e, 0, 0, 11, 14, -4, 15, 0, 2, strokes_110, ncoords_110 },
	{ 0x0000006f, 0, 0, 13, 14, -3, 16, 0, 1, strokes_111, ncoords_111 },
	{ 0x00000070, 0, -7, 12, 14, -4, 15, 0, 2, strokes_112, ncoords_112 },
	{ 0x00000071, 0, -7, 12, 14, -3, 16, 0, 2, strokes_113, ncoords_113 },
	{ 0x00000072, 0, 0, 8, 14, -3, 10, 0, 2, strokes_114, ncoords_114 },
	{ 0x00000073, 0, 0, 11, 14, -3, 14, 0, 1, strokes_115, ncoords_115 },
	{ 0x00000074, 0, 0, 8, 21, -2, 10, 0, 2, strokes_116, ncoords_116 },
	{ 0x00000075, 0, 0, 11, 14, -4, 15, 0, 2, strokes_117, ncoords_117 },
	{ 0x00000076, 0, 0, 12, 14, -2, 14, 0, 1, strokes_118, ncoords_118 },
	{ 0x00000077, 0, 0, 16, 14, -3, 19, 0, 1, strokes_119, ncoords_119 },
	{ 0x00000078, 0, 0, 11, 14, -3, 14, 0, 2, strokes_120, ncoords_120 },
	{ 0x00000079, 0, -7, 13, 14, -1, 15, 0, 2, strokes_121, ncoords_121 },
	{ 0x0000007a, 0, 0, 11, 14, -3, 14, 0, 1, strokes_122, ncoords_122 },
	{ 0x0000007b, 0, -7, 5, 25, -4, 10, 0, 1, strokes_123, ncoords_123 },
	{ 0x0000007c, 0, -7, 0, 25, -4, 4, 0, 1, strokes_124, ncoords_124 },
	{ 0x0000007d, 0, -7, 5, 25, -5, 9, 0, 1, strokes_125, ncoords_125 },
	{ 0x0000007e, 0, 7, 18, 12, -3, 21, 0, 1, strokes_126, ncoords_126 },
	{ 0x0000007f, 0, 0, 16, 21, 0, 16, 0, 1, strokes_127, ncoords_127 },
	{ 0x000000a1, 0, 0, 2, 21, -4, 6, 0, 2, strokes_161, ncoords_161 },
	{ 0x000000b1, 0, 0, 16, 17, -4, 20, 0, 3, strokes_177, ncoords_177 },
	{ 0x000000b7, 0, 9, 1, 10, -2, 3, 0, 1, strokes_183, ncoords_183 },
	{ 0x000000bf, 0, 0, 12, 21, -3, 15, 0, 2, strokes_191, ncoords_191 },
	{ 0x000000c0, 0, 0, 16, 29, -1, 17, 0, 3, strokes_192, ncoords_192 },
	{ 0x000000c1, 0, 0, 16, 29, -1, 17, 0, 3, strokes_193, ncoords_193 },
	{ 0x000000c2, 0, 0, 16, 27, -1, 17, 0, 3, strokes_194, ncoords_194 },
	{ 0x000000c3, 0, 0, 16, 25, -1, 17, 0, 3, strokes_195, ncoords_195 },
	{ 0x000000c4, 0, 0, 16, 25, -1, 17, 0, 4, strokes_196, ncoords_196 },
	{ 0x000000c5, 0, 0, 16, 27, -1, 17, 0, 2, strokes_197, ncoords_197 },
	{ 0x000000c6, 0, 0, 20, 21, -1, 22, 0, 4, strokes_198, ncoords_198 },
	{ 0x000000c8, 0, 0, 13, 29, -4, 15, 0, 3, strokes_200, ncoords_200 },
	{ 0x000000c9, 0, 0, 13, 29, -4, 15, 0, 3, strokes_201, ncoords_201 },
	{ 0x000000ca, 0, 0, 13, 27, -4, 15, 0, 3, strokes_202, ncoords_202 },
	{ 0x000000cb, 0, 0, 13, 25, -4, 15, 0, 4, strokes_203, ncoords_203 },
	{ 0x000000cc, 0, 0, 6, 29, 1, 9, 0, 2, strokes_204, ncoords_204 },
	{ 0x000000cd, 0, 0, 6, 29, -3, 5, 0, 2, strokes_205, ncoords_205 },
	{ 0x000000ce, 0, 0, 8, 27, 0, 8, 0, 2, strokes_206, ncoords_206 },
	{ 0x000000cf, 0, 0, 8, 25, 0, 8, 0, 3, strokes_207, ncoords_207 },
	{ 0x000000d1, 0, 0, 14, 25, -4, 18, 0, 2, strokes_209, ncoords_209 },
	{ 0x000000d2, 0, 0, 16, 29, -3, 19, 0, 2, strokes_210, ncoords_210 },
	{ 0x000000d3, 0, 0, 16, 29, -3, 19, 0, 2, strokes_211, ncoords_211 },
	{ 0x000000d4, 0, 0, 16, 27, -3, 19, 0, 2, strokes_212, ncoords_212 },
	{ 0x000000d5, 0, 0, 16, 25, -3, 19, 0, 2, strokes_213, ncoords_213 },
	{ 0x000000d6, 0, 0, 16, 25, -3, 19, 0, 3, strokes_214, ncoords_214 },
	{ 0x000000d7, 0, 2, 14, 16, -4, 18, 0, 2, strokes_215, ncoords_215 },
	{ 0x000000d8, 0, 0, 16, 21, -3, 19, 0, 2, strokes_216, ncoords_216 },
	{ 0x000000d9, 0, 0, 14, 29, -4, 18, 0, 2, strokes_217, ncoords_217 },
	{ 0x000000da, 0, 0, 14, 29, -4, 18, 0, 2, strokes_218, ncoords_218 },
	{ 0x000000db, 0, 0, 14, 27, -4, 18, 0, 2, strokes_219, ncoords_219 },
	{ 0x000000dc, 0, 0, 14, 25, -4, 18, 0, 3, strokes_220, ncoords_220 },
	{ 0x000000dd, 0, 0, 16, 29, -1, 17, 0, 3, strokes_221, ncoords_221 },
	{ 0x000000e0, 0, 0, 12, 23, -3, 16, 0, 3, strokes_224, ncoords_224 },
	{ 0x000000e1, 0, 0, 12, 23, -3, 16, 0, 3, strokes_225, ncoords_225 },
	{ 0x000000e2, 0, 0, 12, 22, -3, 16, 0, 3, strokes_226, ncoords_226 },
	{ 0x000000e3, 0, 0, 12, 20, -3, 16, 0, 3, strokes_227, ncoords_227 },
	{ 0x000000e4, 0, 0, 12, 20, -3, 16, 0, 4, strokes_228, ncoords_228 },
	{ 0x000000e5, 0, 0, 12, 22, -3, 16, 0, 3, strokes_229, ncoords_229 },
	{ 0x000000e6, 0, 0, 24, 14, -3, 27, 0, 3, strokes_230, ncoords_230 },
	{ 0x000000e8, 0, 0, 12, 23, -3, 15, 0, 2, strokes_232, ncoords_232 },
	{ 0x000000e9, 0, 0, 12, 23, -3, 15, 0, 2, strokes_233, ncoords_233 },
	{ 0x000000ea, 0, 0, 12, 22, -3, 15, 0, 2, strokes_234, ncoords_234 },
	{ 0x000000eb, 0, 0, 12, 20, -3, 15, 0, 3, strokes_235, ncoords_235 },
	{ 0x000000ec, 0, 0, 6, 23, 1, 9, 0, 2, strokes_236, ncoords_236 },
	{ 0x000000ed, 0, 0, 6, 23, -3, 5, 0, 2, strokes_237, ncoords_237 },
	{ 0x000000ee, 0, 0, 8, 22, 0, 8, 0, 2, strokes_238, ncoords_238 },
	{ 0x000000ef, 0, 0, 8, 20, 0, 8, 0, 3, strokes_239, ncoords_239 },
	{ 0x000000f1, 0, 0, 11, 20, -4, 15, 0, 3, strokes_241, ncoords_241 },
	{ 0x000000f2, 0, 0, 13, 23, -3, 16, 0, 2, strokes_242, ncoords_242 },
	{ 0x000000f3, 0, 0, 13, 23, -3, 16, 0, 2, strokes_243, ncoords_243 },
	{ 0x000000f4, 0, 0, 13, 22, -3, 16, 0, 2, strokes_244, ncoords_244 },
	{ 0x000000f5, 0, 0, 13, 20, -3, 16, 0, 2, strokes_245, ncoords_245 },
	{ 0x000000f6, 0, 0, 13, 20, -3, 16, 0, 3, strokes_246, ncoords_246 },
	{ 0x000000f7, 0, 0, 18, 18, -4, 22, 0, 3, strokes_247, ncoords_247 },
	{ 0x000000f8, 0, 0, 13, 14, -3, 16, 0, 2, strokes_248, ncoords_248 },
	{ 0x000000f9, 0, 0, 11, 23, -4, 15, 0, 3, strokes_249, ncoords_249 },
	{ 0x000000fa, 0, 0, 11, 23, -4, 15, 0, 3, strokes_250, ncoords_250 },
	{ 0x000000fb, 0, 0, 11, 22, -4, 15, 0, 3, strokes_251, ncoords_251 },
	{ 0x000000fc, 0, 0, 11, 20, -4, 15, 0, 4, strokes_252, ncoords_252 },
	{ 0x000000fd, 0, -7, 13, 23, -1, 15, 0, 3, strokes_253, ncoords_253 },
	{ 0x000000ff, 0, -7, 13, 20, -1, 15, 0, 4, strokes_255, ncoords_255 },
	{ 0x00000391, 0, 0, 16, 21, -1, 17, 0, 2, strokes_913, ncoords_913 },
	{ 0x00000392, 0, 0, 14, 21, -4, 17, 0, 2, strokes_914, ncoords_914 },
	{ 0x00000393, 0, 0, 12, 21, -4, 13, 0, 1, strokes_915, ncoords_915 },
	{ 0x00000394, 0, 0, 16, 21, -1, 17, 0, 1, strokes_916, ncoords_916 },
	{ 0x00000395, 0, 0, 13, 21, -4, 15, 0, 2, strokes_917, ncoords_917 },
	{ 0x00000396, 0, 0, 14, 21, -3, 17, 0, 1, strokes_918, ncoords_918 },
	{ 0x00000397, 0, 0, 14, 21, -4, 18, 0, 3, strokes_919, ncoords_919 },
	{ 0x00000398, 0, 0, 16, 21, -3, 19, 0, 2, strokes_920, ncoords_920 },
	{ 0x00000399, 0, 0, 0, 21, -4, 4, 0, 1, strokes_921, ncoords_921 },
	{ 0x0000039a, 0, 0, 14, 21, -4, 17, 0, 3, strokes_922, ncoords_922 },
	{ 0x0000039b, 0, 0, 16, 21, -1, 17, 0, 1, strokes_923, ncoords_923 },
	{ 0x0000039c, 0, 0, 16, 21, -4, 20, 0, 1, strokes_924, ncoords_924 },
	{ 0x0000039d, 0, 0, 14, 21, -4, 18, 0, 1, strokes_925, ncoords_925 },
	{ 0x0000039e, 0, 0, 14, 21, -2, 16, 0, 3, strokes_926, ncoords_926 },
	{ 0x0000039f, 0, 0, 16, 21, -3, 19, 0, 1, strokes_927, ncoords_927 },
	{ 0x000003a0, 0, 0, 14, 21, -4, 18, 0, 1, strokes_928, ncoords_928 },
	{ 0x000003a1, 0, 0, 14, 21, -4, 17, 0, 1, strokes_929, ncoords_929 },
	{ 0x000003a3, 0, 0, 14, 21, -2, 16, 0, 1, strokes_931, ncoords_931 },
	{ 0x000003a4, 0, 0, 14, 21, -1, 15, 0, 2, strokes_932, ncoords_932 },
	{ 0x000003a5, 0, 0, 14, 21, -2, 16, 0, 2, strokes_933, ncoords_933 },
	{ 0x000003a6, 0, 0, 14, 21, -3, 17, 0, 2, strokes_934, ncoords_934 },
	{ 0x000003a7, 0, 0, 14, 21, -3, 17, 0, 2, strokes_935, ncoords_935 },
	{ 0x000003a8, 0, 0, 18, 21, -2, 20, 0, 2, strokes_936, ncoords_936 },
	{ 0x000003a9, 0, 0, 14, 21, -3, 17, 0, 1, strokes_937, ncoords_937 },
	{ 0x000003aa, 0, 0, 8, 24, -4, 12, 0, 3, strokes_938, ncoords_938 },
	{ 0x000003ab, 0, 0, 14, 24, -1, 15, 0, 4, strokes_939, ncoords_939 },
	{ 0x000003ac, 0, 0, 15, 22, -3, 18, 0, 2, strokes_940, ncoords_940 },
	{ 0x000003ad, 0, 0, 11, 22, -3, 13, 0, 2, strokes_941, ncoords_941 },
	{ 0x000003ae, 0, -7, 15, 22, -1, 19, 0, 3, strokes_942, ncoords_942 },
	{ 0x000003af, 0, 0, 9, 22, -3, 10, 0, 2, strokes_943, ncoords_943 },
	{ 0x000003b1, 0, 0, 15, 14, -3, 18, 0, 1, strokes_945, ncoords_945 },
	{ 0x000003b2, 0, -7, 14, 21, -2, 17, 0, 1, strokes_946, ncoords_946 },
	{ 0x000003b3, 0, -7, 16, 14, -1, 18, 0, 2, strokes_947, ncoords_947 },
	{ 0x000003b4, 0, 0, 12, 21, -3, 15, 0, 1, strokes_948, ncoords_948 },
	{ 0x000003b5, 0, 0, 10, 14, -3, 13, 0, 1, strokes_949, ncoords_949 },
	{ 0x000003b6, 0, -7, 11, 21, -3, 12, 0, 1, strokes_950, ncoords_950 },
	{ 0x000003b7, 0, -7, 15, 14, -1, 19, 0, 2, strokes_951, ncoords_951 },
	{ 0x000003b8, 0, 0, 18, 21, -1, 20, 0, 1, strokes_952, ncoords_952 },
	{ 0x000003b9, 0, 0, 6, 14, -3, 8, 0, 1, strokes_953, ncoords_953 },
	{ 0x000003ba, 0, 0, 14, 14, -2, 16, 0, 2, strokes_954, ncoords_954 },
	{ 0x000003bb, 0, 0, 13, 21, -1, 15, 0, 2, strokes_955, ncoords_955 },
	{ 0x000003bc, 0, -7, 19, 14, -1, 20, 0, 3, strokes_956, ncoords_956 },
	{ 0x000003bd, 0, 0, 13, 14, -3, 15, 0, 1, strokes_957, ncoords_957 },
	{ 0x000003be, 0, -7, 11, 21, -3, 13, 0, 3, strokes_958, ncoords_958 },
	{ 0x000003bf, 0, 0, 11, 14, -3, 14, 0, 1, strokes_959, ncoords_959 },
	{ 0x000003c0, 0, 0, 18, 14, -2, 20, 0, 3, strokes_960, ncoords_960 },
	{ 0x000003c1, 0, -7, 15, 14, 0, 18, 0, 1, strokes_961, ncoords_961 },
	{ 0x000003c3, 0, 0, 15, 14, -3, 17, 0, 1, strokes_963, ncoords_963 },
	{ 0x000003c4, 0, 0, 16, 14, -2, 18, 0, 2, strokes_964, ncoords_964 },
	{ 0x000003c5, 0, 0, 16, 14, -1, 19, 0, 1, strokes_965, ncoords_965 },
	{ 0x000003c6, 0, -7, 16, 14, -3, 19, 0, 1, strokes_966, ncoords_966 },
	{ 0x000003c7, 0, -7, 16, 14, -1, 17, 0, 2, strokes_967, ncoords_967 },
	{ 0x000003c8, 0, -7, 20, 21, -1, 22, 0, 2, strokes_968, ncoords_968 },
	{ 0x000003c9, 0, 0, 17, 14, -3, 20, 0, 2, strokes_969, ncoords_969 },
	{ 0x000003ca, 0, 0, 8, 19, -4, 12, 0, 3, strokes_970, ncoords_970 },
	{ 0x000003cb, 0, 0, 16, 19, 1, 17, 0, 3, strokes_971, ncoords_971 },
	{ 0x000003cc, 0, 0, 11, 22, -3, 13, 0, 2, strokes_972, ncoords_972 },
	{ 0x000003cd, 0, 0, 16, 22, 1, 17, 0, 2, strokes_973, ncoords_973 },
	{ 0x000003ce, 0, 0, 17, 22, 1, 17, 0, 3, strokes_974, ncoords_974 },
	{ 0x00002190, 0, 4, 18, 14, -4, 22, 0, 3, strokes_8592, ncoords_8592 },
	{ 0x00002191, 0, 0, 10, 18, -3, 13, 0, 3, strokes_8593, ncoords_8593 },
	{ 0x00002192, 0, 4, 18, 14, -4, 22, 0, 3, strokes_8594, ncoords_8594 },
	{ 0x00002193, 0, 0, 10, 18, -3, 13, 0, 3, strokes_8595, ncoords_8595 },
	{ 0x00002194, 0, 4, 18, 14, -4, 22, 0, 5, strokes_8596, ncoords_8596 },
	{ 0x00002195, 0, 0, 10, 18, -3, 13, 0, 5, strokes_8597, ncoords_8597 },
	{ 0x000021d0, 0, 4, 18, 14, -4, 22, 0, 4, strokes_8656, ncoords_8656 },
	{ 0x000021d1, 0, 0, 10, 18, -3, 13, 0, 4, strokes_8657, ncoords_8657 },
	{ 0x000021d2, 0, 4, 18, 14, -4, 22, 0, 4, strokes_8658, ncoords_8658 },
	{ 0x000021d3, 0, 0, 10, 18, -3, 13, 0, 4, strokes_8659, ncoords_8659 },
	{ 0x000021d4, 0, 4, 18, 14, -4, 22, 0, 6, strokes_8660, ncoords_8660 },
	{ 0x000021d5, 0, 0, 10, 18, -3, 13, 0, 6, strokes_8661, ncoords_8661 },
	{ 0x00002202, 0, 0, 13, 21, -3, 16, 0, 1, strokes_8706, ncoords_8706 },
	{ 0x00002203, 0, 0, 13, 21, -2, 17, 0, 2, strokes_8707, ncoords_8707 },
	{ 0x00002206, 0, 0, 16, 21, -2, 18, 0, 1, strokes_8710, ncoords_8710 },
	{ 0x00002207, 0, 0, 16, 21, -2, 18, 0, 1, strokes_8711, ncoords_8711 },
	{ 0x0000220a, 0, 1, 16, 17, -4, 20, 0, 2, strokes_8714, ncoords_8714 },
	{ 0x00002213, 0, 0, 16, 17, -4, 20, 0, 3, strokes_8723, ncoords_8723 },
	{ 0x00002218, 0, 13, 8, 21, -3, 11, 0, 1, strokes_8728, ncoords_8728 },
	{ 0x0000221a, 0, 0, 19, 25, -3, 19, 0, 3, strokes_8730, ncoords_8730 },
	{ 0x0000221d, 0, 4, 17, 14, -4, 21, 0, 1, strokes_8733, ncoords_8733 },
	{ 0x0000221e, 0, 5, 19, 13, -3, 22, 0, 1, strokes_8734, ncoords_8734 },
	{ 0x00002220, 0, 0, 18, 25, -3, 21, 0, 1, strokes_8736, ncoords_8736 },
	{ 0x00002225, 0, -7, 6, 25, -4, 10, 0, 2, strokes_8741, ncoords_8741 },
	{ 0x00002227, 0, 1, 16, 17, -4, 20, 0, 1, strokes_8743, ncoords_8743 },
	{ 0x00002228, 0, 1, 16, 17, -4, 20, 0, 1, strokes_8744, ncoords_8744 },
	{ 0x00002229, 0, 1, 16, 17, -4, 20, 0, 1, strokes_8745, ncoords_8745 },
	{ 0x0000222a, 0, 1, 16, 17, -4, 20, 0, 1, strokes_8746, ncoords_8746 },
	{ 0x0000222b, 0, -7, 20, 25, -2, 22, 0, 1, strokes_8747, ncoords_8747 },
	{ 0x00002234, 0, 0, 20, 18, -3, 23, 0, 3, strokes_8756, ncoords_8756 },
	{ 0x00002235, 0, 0, 20, 18, -3, 23, 0, 3, strokes_8757, ncoords_8757 },
	{ 0x0000223c, 0, 7, 18, 12, -2, 20, 0, 1, strokes_8764, ncoords_8764 },
	{ 0x0000223d, 0, 7, 18, 12, -2, 20, 0, 1, strokes_8765, ncoords_8765 },
	{ 0x00002242, 0, 4, 18, 12, -4, 22, 0, 2, strokes_8770, ncoords_8770 },
	{ 0x00002243, 0, 6, 18, 15, -4, 22, 0, 2, strokes_8771, ncoords_8771 },
	{ 0x00002245, 0, 6, 18, 18, -4, 22, 0, 3, strokes_8773, ncoords_8773 },
	{ 0x00002248, 0, 4, 18, 15, -4, 22, 0, 2, strokes_8776, ncoords_8776 },
	{ 0x0000224b, 0, 1, 18, 18, -4, 22, 0, 3, strokes_8779, ncoords_8779 },
	{ 0x00002260, 0, 0, 18, 18, -4, 22, 0, 3, strokes_8800, ncoords_8800 },
	{ 0x00002261, 0, 4, 18, 14, -4, 22, 0, 3, strokes_8801, ncoords_8801 },
	{ 0x00002264, 0, 5, 16, 21, -4, 20, 0, 2, strokes_8804, ncoords_8804 },
	{ 0x00002265, 0, 5, 16, 21, -4, 20, 0, 2, strokes_8805, ncoords_8805 },
	{ 0x00002266, 0, 0, 16, 21, -4, 20, 0, 3, strokes_8806, ncoords_8806 },
	{ 0x00002267, 0, 0, 16, 21, -4, 20, 0, 3, strokes_8807, ncoords_8807 },
	{ 0x00002282, 0, 1, 16, 17, -4, 20, 0, 1, strokes_8834, ncoords_8834 },
	{ 0x00002283, 0, 1, 16, 17, -4, 20, 0, 1, strokes_8835, ncoords_8835 },
	{ 0x000022a5, 0, 0, 18, 25, -3, 21, 0, 2, strokes_8869, ncoords_8869 },
	{ 0x00002329, 0, -7, 7, 25, -3, 11, 0, 1, strokes_9001, ncoords_9001 },
	{ 0x0000232a, 0, -7, 7, 25, -4, 10, 0, 1, strokes_9002, ncoords_9002 },
	{ 0x0000e0a0, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0a2, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0a3, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0a4, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0a5, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0a6, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0a7, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0a8, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0a9, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0aa, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0ab, 0, 6, 4, 10, -2, 6, 0, 2, strokes_57515, ncoords_57515 },
	{ 0x0000e0ac, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0ad, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0ae, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0af, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0b0, 0, 15, 6, 21, -2, 8, 0, 1, strokes_57520, ncoords_57520 },
	{ 0x0000e0b2, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0b3, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0b4, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0b5, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0b6, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0b8, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0b9, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0ba, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0bb, 0, 6, 4, 10, -2, 6, 0, 2, strokes_57531, ncoords_57531 },
	{ 0x0000e0bc, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0bd, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0be, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0c7, 0, -3, 15, 21, -3, 18, 0, 2, strokes_57543, ncoords_57543 },
	{ 0x0000e0d0, -2, 0, 14, 21, -4, 17, 0, 2, strokes_57552, ncoords_57552 },
	{ 0x0000e0de, 0, 0, 13, 21, -4, 16, 0, 2, strokes_57566, ncoords_57566 },
	{ 0x0000e0df, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e0e7, 0, -3, 12, 14, -3, 15, 0, 2, strokes_57575, ncoords_57575 },
	{ 0x0000e0f0, 0, 0, 13, 20, -3, 16, 0, 2, strokes_57584, ncoords_57584 },
	{ 0x0000e0fe, 0, -7, 13, 21, -3, 16, 0, 2, strokes_57598, ncoords_57598 },
	{ 0x0000e390, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e3a2, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e3b0, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e3c2, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000e3cf, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f196, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f197, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f198, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f199, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f19a, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f19b, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f19c, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f19d, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f19e, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f19f, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f1d6, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f1d7, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f1d8, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f1d9, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f1da, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f1db, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f1dc, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f1dd, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f1de, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f1df, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f200, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f201, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f204, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f205, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f208, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f209, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f20b, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f20c, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f20d, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f20e, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f20f, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f210, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f211, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f212, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f214, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f215, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f216, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f217, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f219, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f21b, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f21c, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f21f, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f221, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f222, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f223, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f224, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f226, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f22c, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f22d, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f22e, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f22f, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f230, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f231, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f232, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f233, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f236, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f237, 0, 0, 18, 18, -3, 21, 0, 4, strokes_62007, ncoords_62007 },
	{ 0x0000f238, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f239, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f23a, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f23b, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f23e, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f23f, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f240, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f241, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f244, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f246, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f247, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f249, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f24a, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f24c, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f24d, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f24e, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f24f, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f262, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f263, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f268, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f269, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f26a, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f26b, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f26c, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f26d, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f26e, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f26f, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f280, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f281, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f284, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f284, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f286, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f287, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f288, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f289, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f28a, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f28b, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f28c, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f28d, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f28e, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f28f, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f2a0, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f2a1, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f2a2, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f2a3, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f2a4, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f2a6, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f2a7, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f2a8, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f2a9, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f2aa, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f2ab, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f2ac, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f2ad, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f2ae, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
	{ 0x0000f2af, 0, 0, 0, 0, -8, 8, 0, 0, (const glyph_stroke_t **)0, (const uint8_t *)0 },
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
const font_data_t font_hsans_1_rs = {
	"Hershey Sans regular - single stroke - reduced strokelength",
	21,
	432,
	glyph_data
};
