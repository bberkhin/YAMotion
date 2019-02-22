#include "wx/wx.h"

//#include "defsext.h"     // Additional definitions
#include "prefs.h"     
#include "LexGCode.h"// Preferences


//============================================================================
// declarations
//============================================================================

//----------------------------------------------------------------------------
//! language types
const CommonInfo g_CommonPrefs = {
    // editor functionality prefs
    true,  // syntaxEnable
    true,  // foldEnable
    true,  // indentEnable
    // display defaults prefs
    false, // overTypeInitial
    false, // readOnlyInitial
    false,  // wrapModeInitial
    false, // displayEOLEnable
    false, // IndentGuideEnable
    true,  // lineNumberEnable
    false, // longLineOnEnable
    false, // whiteSpaceEnable
};

//----------------------------------------------------------------------------
// keywordlists
// C++

// GCode 
const char* GCoddeWordlist = "abs acos asin atan cos exp fix fup ln round sin sqrt tan exists";
const char* GcmcWordlist = "abs acos asin atan atan_xy atan_xz atan_yz ceil comment cos count delete error exp fixpos_restore fixpos_set fixpos_store floor head "
	"insert isangle isconst isdefined isdeg isdistance isdxf isfloat isgcode isinch isint ismm ismodemm isnone israd isrelative isscalar isstring issvg"
	"isundef isvector isvectorlist layer layerstack length literal log10 log2 loge message normalize pause pi plane position pow relocate reverse rotate_xy rotate_xz rotate_yz"
	"round scale sign sin sqrt svg_closepath tail tan to_chr to_deg to_distance to_float to_in to_inch to_int to_mm to_native to_none to_rad to_string to_val typeset undef warning";



//----------------------------------------------------------------------------
//! languages
const LanguageInfo g_LanguagePrefs[] = {
	  // G Code
	{"G Code",
	 "*.ngc;*.nc;*.cnc",
	SCLEX_GCODE,
	 {{SCE_GCODE_DEFAULT, NULL},
	  {SCE_GCODE_COMMENT, NULL},
	  {SCE_GCODE_COMMENT_ML, NULL},
	  {SCE_GCODE_G, NULL},
	  {SCE_GCODE_M, NULL},
	  {SCE_GCODE_PARAM, NULL},
	  {SCE_GCODE_VAR, NULL},
	  {SCE_GCODE_NUMBER, NULL},
	  {SCE_GCODE_COORDINATE, NULL},
	  {SCE_GCODE_WORD1, GCoddeWordlist },
	  {SCE_GCODE_OPERATORS,NULL},
	  {SCE_GCODE_IDENTIFIER, NULL},
	  {-1, NULL},
	  {-1, NULL},
	  {-1, NULL},
	  {-1, NULL},
	  {-1, NULL},
	  {-1, NULL},
	  {-1, NULL},
	  {-1, NULL},
	  {-1, NULL},
	  {-1, NULL},
	  {-1, NULL},
	  {-1, NULL},
	  {-1, NULL},
	  {-1, NULL},
	  {-1, NULL},
	  {-1, NULL},
	  {-1, NULL},
	  {-1, NULL},
	  {-1, NULL},
	  {-1, NULL}},
	 mySTC_FOLD_COMMENT | mySTC_FOLD_COMPACT | mySTC_FOLD_PREPROC},
	// GCMC
  {"GCMC",
   "*.gcmc",
  SCLEX_GCMC,
   {{SCE_GCODE_DEFAULT, NULL},
	{SCE_GCODE_COMMENT, NULL},
	{SCE_GCODE_COMMENT_ML, NULL},
	{SCE_GCODE_G, NULL},
	{SCE_GCODE_M, NULL},
	{SCE_GCODE_PARAM, NULL},
	{SCE_GCODE_VAR, NULL},
	{SCE_GCODE_NUMBER, NULL},
	{SCE_GCODE_COORDINATE, NULL},
	{SCE_GCODE_WORD1, GcmcWordlist },
	{SCE_GCODE_OPERATORS,NULL},
	{SCE_GCODE_IDENTIFIER, NULL},
	{-1, NULL},
	{-1, NULL},
	{-1, NULL},
	{-1, NULL},
	{-1, NULL},
	{-1, NULL},
	{-1, NULL},
	{-1, NULL},
	{-1, NULL},
	{-1, NULL},
	{-1, NULL},
	{-1, NULL},
	{-1, NULL},
	{-1, NULL},
	{-1, NULL},
	{-1, NULL},
	{-1, NULL},
	{-1, NULL},
	{-1, NULL},
	{-1, NULL}},
   mySTC_FOLD_COMMENT | mySTC_FOLD_COMPACT | mySTC_FOLD_PREPROC},

	// * (any)
{wxTRANSLATE("<default>"),
    "*.*",
    wxSTC_LEX_PROPERTIES,
    {{mySTC_TYPE_DEFAULT, NULL},
    {mySTC_TYPE_DEFAULT, NULL},
    {mySTC_TYPE_DEFAULT, NULL},
    {mySTC_TYPE_DEFAULT, NULL},
    {mySTC_TYPE_DEFAULT, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL}},
    0},
    };

const int g_LanguagePrefsSize = WXSIZEOF(g_LanguagePrefs);

//----------------------------------------------------------------------------
//! style types

const StyleInfo g_StylePrefs [] = {
    // SCE_GCODE_DEFAULT
    {"Default",
     "GREY", "WHITE",
     "", 10, 0, 0},

	// SCE_GCODE_COMMENT
  {"Comment",
   "FOREST GREEN", "WHITE",
   "", 10, 0, 0},

   // SCE_GCODE_COMMENT_ML
   {"Comment (Doc)",
	"FOREST GREEN", "WHITE",
	"", 10, 0, 0},
	
    // SCE_GCODE_G
    {"Keyword1",
     "BLUE", "WHITE",
     "", 10, mySTC_STYLE_BOLD, 0},

    // SCE_GCODE_M
    {"Keyword2",
     "RED", "WHITE",
	 "", 10, mySTC_STYLE_BOLD, 0},
	
	 // SCE_GCODE_PARAM
    {"Keyword4",
     "BROWN", "WHITE",
	 "", 10, mySTC_STYLE_BOLD, 0},

    // SCE_GCODE_VAR
    {"Keyword5",
     "SIENNA", "WHITE",
	 "", 10, mySTC_STYLE_BOLD, 0},

	 // SCE_GCODE_NUMBER
    {"Number",
     "BLACK", "WHITE",
	 "", 10, mySTC_STYLE_BOLD, 0},

    // SCE_GCODE_COORDINATE
    {"Parameter",
     "MAGENTA", "WHITE",
	 "", 10, mySTC_STYLE_BOLD, 0},
   
    // #define SCE_GCODE_WORD1 9 
    {"Keywords",
     "ORANGE", "WHITE",
     "", 10, 0, 0},
	 //SCE_GCODE_OPERATORS
	  {"Keyword2",
	 "BLACK", "WHITE",
	 "", 10, mySTC_STYLE_BOLD, 0},
	//SCE_GCODE_IDENTIFIER
	{"Default",
	 "GREY", "WHITE",
	 "", 10, 0, 0},


    };

const int g_StylePrefsSize = WXSIZEOF(g_StylePrefs);
