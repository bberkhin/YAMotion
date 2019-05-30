#include "wx/wx.h"
#include "LexGCode.h"// Preferences
//#include "defsext.h"     // Additional definitions
#include "prefs.h"
#include "wx/stc/stc.h"  // styled text control
#include "..\..\src\stc\scintilla\include\SciLexer.h"


//============================================================================
// declarations
//============================================================================



//----------------------------------------------------------------------------
// keywordlists
// C++

// GCode 
const char* GCoddeWordlist = "abs acos asin atan cos exp fix fup ln round sin sqrt tan exists";
const char* GcmcWordlist1 = "abs acos asin atan atan_xy atan_xz atan_yz ceil comment cos count delete error exp fixpos_restore fixpos_set fixpos_store floor head "
"insert isangle isconst isdefined isdeg isdistance isdxf isfloat isgcode isinch isint ismm ismodemm isnone israd isrelative isscalar isstring issvg "
"isundef isvector isvectorlist layer layerstack length literal log10 log2 loge message normalize pause pi plane position pow relocate reverse rootate_xy rootate_xz rootate_yz "
"round scale sign sin sqrt svg_closepath tail tan to_chr to_deg to_distance to_float to_in to_inch to_int to_mm to_native to_none to_rad to_string to_val typeset undef warning "
"arc_ccw arc_ccw_r arc_cw arc_cw_r circle_ccw circle_ccw_r circle_cw circle_cw_r coolant drill dwell feedmode feedrate fixpos_restore fixpos_store goto goto_r move move_r pathmode "
"pause plane spindle spindlespeed toolchange";
const char* GcmcWordlist2 = "for if while do else return function foreach include";

/*
//----------------------------------------------------------------------------
//! languages
const LanguageInfo g_LanguagePrefs[] = {
	  // G Code
	{"G Code",
	FILETYPE_NC,
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
	  {SCE_GCODE_WORD, GCoddeWordlist },
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
   FILETYPE_GCMC,
   "*.gcmc",
  SCLEX_GCMC,   
	{{SCE_GCMC_DEFAULT, NULL},
	{SCE_GCODE_COMMENT, NULL},
	{SCE_GCODE_COMMENT_ML, NULL},
	{SCE_GCODE_G, NULL},
	{SCE_GCODE_M, NULL},
	{SCE_GCODE_PARAM, NULL},
	{SCE_GCODE_VAR, NULL},
	{SCE_GCODE_NUMBER, NULL},
	{SCE_GCODE_COORDINATE, NULL},
	{SCE_GCMC_WORD1, GcmcWordlist1 },
	{SCE_GCMC_WORD2, GcmcWordlist2 },
	{SCE_GCMC_WORD2, GcmcWordlist2 },
	{SCE_GCODE_OPERATORS,NULL},
	{SCE_GCODE_IDENTIFIER, NULL},
	{SCE_GCMC_STRING,NULL},	
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
{wxTRANSLATE("<default>"), FILETYPE_UNKNOW,
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
{"SCE_GCODE_DEFAULT","GRAY", "WHITE", "", 10, 0, 0},
{"SCE_GCODE_COMMENT", "FOREST GREEN", "WHITE", "", 10, 0, 0},
{"SCE_GCODE_COMMENT_ML","FOREST GREEN", "WHITE","", 10, 0, 0},
{"3SCE_GCODE_G","BLUE", "WHITE","", 10, mySTC_STYLE_BOLD, 0},
{"SCE_GCODE_M","RED", "WHITE","", 10, mySTC_STYLE_BOLD, 0},
{"SCE_GCODE_PARAM","BROWN", "WHITE","", 10, mySTC_STYLE_BOLD, 0},
{"SCE_GCODE_VAR","SIENNA", "WHITE","", 10, mySTC_STYLE_BOLD, 0},
{"SCE_GCODE_NUMBER","BLACK", "WHITE","", 10, mySTC_STYLE_BOLD, 0},
{"SCE_GCODE_COORDINATE","MAGENTA", "WHITE","", 10, mySTC_STYLE_BOLD, 0},
{"SCE_GCODE_WORD","RED", "WHITE","", 10, mySTC_STYLE_BOLD, 0},
{"SCE_GCODE_OPERATORS","VIOLET RED", "WHITE", "", 10, mySTC_STYLE_BOLD, 0},
{"SCE_GCODE_IDENTIFIER","BLACK", "WHITE","", 10, 0, 0},
{"SCE_GCMC_DEFAULT","BLACK", "WHITE","", 10, mySTC_STYLE_BOLD, 0},
{"SCE_GCMC_WORD1","RED", "WHITE","", 10, mySTC_STYLE_BOLD, 0},
{"SCE_GCMC_WORD2","BLUE", "WHITE","", 10, mySTC_STYLE_BOLD, 0},
{"SCE_GCMC_STRING","GREEN", "WHITE","", 10, mySTC_STYLE_BOLD, 0}
 };

const int g_StylePrefsSize = WXSIZEOF(g_StylePrefs);

*/
#include "wx/jsonreader.h"
#include "standartpaths.h"
#include <wx/wfstream.h>

Preferences global_pprefs;


Preferences::Preferences()
{	
	m_common = {
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
		4,//tabWidth
		"", // gcmc_sybatx;
		"", //nc_syntax
		"" //them_color
	};

	m_languages.push_back( LanguageInfo() );
	m_languages.push_back(LanguageInfo(FILETYPE_NC, SCLEX_GCODE));
	m_languages.push_back(LanguageInfo(FILETYPE_GCMC, SCLEX_GCMC));
	m_languages.push_back(LanguageInfo(FILETYPE_JSON, SCLEX_JSON));

};

const LanguageInfo  *Preferences::FindByType(int type)
{

	if (type >= static_cast<int>(m_languages.size()))
		type = 0;
	m_languages[type].Init();
	return &(m_languages[type]);
}

const  LanguageInfo *Preferences::FindByFileName(const wxString &name)
{
	wxString filename = name.Lower();


	auto it = std::find_if(m_languages.begin(), m_languages.end(), [filename](LanguageInfo &p)
	{  return p.Match(filename); });

	LanguageInfo &ln = (it == m_languages.end()) ? m_languages[0] : (*it);
	ln.Init();
	return  &ln;

}
Preferences::~Preferences()
{

}

bool Preferences::Read()
{
	std::filesystem::path dirpath = StandartPaths::Get()->GetPreferencesPath(L"main.json");
	wxFFileInputStream  file_stream(dirpath.c_str());
	if (!file_stream.IsOk())
	{
		wxString msg = wxString::Format(_("Can not open file %s"), dirpath.c_str());
		wxMessageBox(msg, _("Error opening file"));
		return false;
	}
	wxJSONReader reader;
	wxJSONValue root;
	// now read the JSON text and store it in the 'root' structure
  // check for errors before retreiving values...
	int numErrors = reader.Parse(file_stream, &root);
	if (numErrors > 0)
	{
		const wxArrayString& errors = reader.GetErrors();
		wxString msg = wxString::Format(_("Error parsing file %s\n"), dirpath.c_str());
		for (auto p = errors.begin(); p != errors.end(); ++p)
		{
			msg += *p;
			msg += L"\n";
		}
		wxMessageBox(msg, _("Error parsing file"));
		return false;
	}

	root["syntax"].AsBool(g_CommonPrefs.syntaxEnable);
	root["fold"].AsBool(g_CommonPrefs.foldEnable);
	root["indent"].AsBool(g_CommonPrefs.indentEnable);
	// display defaults prefs
	root["wrapMode"].AsBool(g_CommonPrefs.wrapModeInitial);
	root["displayEOL"].AsBool(g_CommonPrefs.displayEOLEnable);
	root["indentGuide"].AsBool(g_CommonPrefs.indentGuideEnable);
	root["lineNumber"].AsBool(g_CommonPrefs.lineNumberEnable);
	root["longLineOn"].AsBool(g_CommonPrefs.longLineOnEnable);
	root["whiteSpace"].AsBool(g_CommonPrefs.whiteSpaceEnable);
	root["tabWidth"].AsInt(g_CommonPrefs.tabWidth);
	g_CommonPrefs.theme_color = root["theme_syntax"].AsString();

	wxJSONValue &files = root["files"];
	m_languages.clear();
	m_languages.push_back(LanguageInfo());
	
	for( unsigned int i = 0; i < files.Size();++i)
	{
		wxJSONValue &val = files.Item(i);
		wxString name = val["name"].AsString();
		wxString filename = val["syntax"].AsString();

		m_languages.push_back(LanguageInfo(i+1, SCLEX_GCODE));
		m_languages.push_back(LanguageInfo(FILETYPE_GCMC, SCLEX_GCMC));
		m_languages.push_back(LanguageInfo(FILETYPE_JSON, SCLEX_JSON));


		FindByType(i+1)

		SetFileName()

	}
	return true;
}


LanguageInfo::LanguageInfo(int file_type, int lexer )
	:  m_inited(false), m_file_type(file_type), m_lexer(lexer), m_fold(0)
{

}

LanguageInfo::LanguageInfo()
	:  m_inited(false), m_file_type(FILETYPE_UNKNOW), m_lexer(0), m_fold(0)
{

}

void LanguageInfo::Init()
{
	if (m_inited)
		return;
	
	if ( !m_filename.empty() )
		Read();

	m_inited = true;
	return;
}

bool LanguageInfo::Read()
{
	std::filesystem::path dirpath = StandartPaths::Get()->GetPreferencesPath(m_filename);
	wxFFileInputStream  file_stream(dirpath.c_str());
	if (!file_stream.IsOk())
	{
		wxString msg = wxString::Format(_("Can not open file %s"), dirpath.c_str());
		wxMessageBox(msg, _("Error opening file"));
		return false;
	}
	wxJSONReader reader;
	wxJSONValue root;
	// now read the JSON text and store it in the 'root' structure
  // check for errors before retreiving values...
	int numErrors = reader.Parse(file_stream, &root);
	if (numErrors > 0)
	{
		const wxArrayString& errors = reader.GetErrors();
		wxString msg = wxString::Format(_("Error parsing file %s\n"), dirpath.c_str());
		for (auto p = errors.begin(); p != errors.end(); ++p)
		{
			msg += *p;
			msg += L"\n";
		}
		wxMessageBox(msg, _("Error parsing file"));
		return false;
	}
	/*
	g_CommonPrefs.theme_color = root["theme_syntax"].AsString();	
	root["syntax"].AsBool(g_CommonPrefs.syntaxEnable);
	g_CommonPrefs.theme_color = root["theme_syntax"].AsString();
	"name"       : "GCMC",

	  "id"         : 2,
	  "extensions" : "*.ngc;*.nc;*.cnc",
	  "fontsize"   : 10,
	  "fontname"   : "system",
	  "fclr"       : "BLACK",
	  "bclr"       : "WHITE",
	  "italic"     : false,
	  "styles"     :
  */
	return false;
}


bool  LanguageInfo::Match(const wxString &fname)
{
	wxString filepattern = m_filepattern;
	while (!filepattern.empty())
	{
		wxString cur = filepattern.BeforeFirst(';');
		if ((cur == fname) ||
			(cur == (fname.BeforeLast('.') + ".*")) ||
			(cur == ("*." + fname.AfterLast('.')))) {
			return true;
		}
		filepattern = filepattern.AfterFirst(';');
	}
	return false;
}
