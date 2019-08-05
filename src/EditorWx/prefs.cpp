#include "wx/wx.h"
#include "LexGCode.h"// Preferences
#include "prefs.h"
#include "wx/stc/stc.h"  // styled text control
#include "..\..\src\stc\scintilla\include\SciLexer.h"
#include "wx/jsonreader.h"
#include "standartpaths.h"
#include <wx/wfstream.h>




// GCode 
const char* GCoddeWordlist = "abs acos asin atan cos exp fix fup ln round sin sqrt tan exists";
const char* GcmcWordlist1 = "abs acos asin atan atan_xy atan_xz atan_yz ceil comment cos count delete error exp fixpos_restore fixpos_set fixpos_store floor head "
"insert isangle isconst isdefined isdeg isdistance isdxf isfloat isgcode isinch isint ismm ismodemm isnone israd isrelative isscalar isstring issvg "
"isundef isvector isvectorlist layer layerstack length literal log10 log2 loge message normalize pause pi plane position pow relocate reverse rootate_xy rootate_xz rootate_yz "
"round scale sign sin sqrt svg_closepath tail tan to_chr to_deg to_distance to_float to_in to_inch to_int to_mm to_native to_none to_rad to_string to_val typeset undef warning "
"arc_ccw arc_ccw_r arc_cw arc_cw_r circle_ccw circle_ccw_r circle_cw circle_cw_r coolant drill dwell feedmode feedrate fixpos_restore fixpos_store goto goto_r move move_r pathmode "
"pause plane spindle spindlespeed toolchange";

const char* GcmcWordlist2 = "function for foreach do while if elif else break continue return include local repeat const";
const char* GcmcWordlist3 = "mm mil in deg rad";



 
const char* jsonWordlist = "true false title description default examples";

Preferences global_pprefs;


Preferences::Preferences() : m_artprovider(0), m_tabartprovider(0)
{	
	m_common = {
		// editor functionality prefs
		true,  // syntaxEnable
		false,  // foldEnable
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
		false, // visibleHSB
		false, // enableLogExecution
		4,//tabWidth
		"", // gcmc_sybatx;
		"", //nc_syntax
		"", //them_color
		"" //postprocessing_fn
	};

	m_colors = new ColourScheme();
	m_languages.push_back(LanguageInfo("ALL", FILETYPE_UNKNOW, 0, "*.*"));
	m_languages.push_back(LanguageInfo("GCODE",FILETYPE_NC, SCLEX_GCODE, "*.ngc; *.nc; *.cnc" ));
	m_languages.push_back(LanguageInfo("GCMC", FILETYPE_GCMC, SCLEX_GCMC, "*.gcmc"));
	m_languages.push_back(LanguageInfo("JSON", FILETYPE_JSON, SCLEX_JSON, "*.json"));
};

Preferences::~Preferences()
{
	delete m_colors;
}

const LanguageInfo  *Preferences::FindByType(int type, bool init)
{
	auto it = std::find_if(m_languages.begin(), m_languages.end(), [type](LanguageInfo &p)
	{  return p.GetFileType() == type; });

	LanguageInfo *pln = 0;
	if (it == m_languages.end())
		pln = &(m_languages.back());
	else
		pln = &(*it);

	if (init)
		pln->Init();
	
	return  pln;
}

const  LanguageInfo *Preferences::FindByFileName(const wxString &name, bool init)
{
	wxString filename = name.Lower();


	auto it = std::find_if(m_languages.begin(), m_languages.end(), [filename](LanguageInfo &p)
	{  return p.Match(filename); });


	if (it == m_languages.end())
	{
		// def lang is GCODEE
		return FindByType(FILETYPE_NC, init);
	}

	LanguageInfo *ln = &(*it);
	if (init)
		ln->Init();
	return  ln;

}

LanguageInfo  *Preferences::FindByName(const wxString &name, bool init)
{
	wxString filename = name.Lower();


	auto it = std::find_if(m_languages.begin(), m_languages.end(), [name](LanguageInfo &p)
	{  return p.GetName() == name; });

	LanguageInfo &ln = (it == m_languages.end()) ? m_languages[0] : (*it);
	
	if (init)
		ln.Init();
	return  &ln;
}


wxString Preferences::CreateWildCard() const
{
	//Clear
	wxString wldCrd;
	std::for_each(m_languages.begin(), m_languages.end(), [&wldCrd](const LanguageInfo &p)
	{
		if ( !wldCrd.IsEmpty() )
			wldCrd += L'|';
		wldCrd += p.CreateWildCard();
		
	});
	return wldCrd;
}


bool Preferences::Read()
{
	//Clear
	std::for_each(m_languages.begin(), m_languages.end(), [](LanguageInfo &p)
	{  return p.Clear(); });


	// read default Preferences
	std::filesystem::path dirpath = StandartPaths::Get()->GetPreferencesPath(L"Default Preferences.json");
	if (!DoRead(dirpath.c_str(), true))
		return false;
	// Now Read user setting which overrite default
	dirpath = StandartPaths::Get()->GetPreferencesPath(L"User Preferences.json");
	DoRead(dirpath.c_str(), false);
	return true;

}

bool Preferences::DoRead(const wxString& fileName, bool errifnoexist )
{
	wxLogNull logNo;
	wxFFileInputStream  file_stream(fileName );
	if (!file_stream.IsOk())
	{
		if( errifnoexist )
		{
			wxString msg = wxString::Format(_("Can not open file %s"), fileName);
			wxMessageBox(msg, _("Error opening file"));
		}
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
		wxString msg = wxString::Format(_("Error parsing file %s\n"), fileName);
		for (auto p = errors.begin(); p != errors.end(); ++p)
		{
			msg += *p;
			msg += L"\n";
		}
		wxMessageBox(msg, _("Error parsing file"));
		return false;
	}

	root["syntax"].AsBool(m_common.syntaxEnable);
	root["fold"].AsBool(m_common.foldEnable);
	root["indent"].AsBool(m_common.indentEnable);
	// display defaults prefs
	root["wrapMode"].AsBool(m_common.wrapModeInitial);
	root["displayEOL"].AsBool(m_common.displayEOLEnable);
	root["indentGuide"].AsBool(m_common.indentGuideEnable);
	root["lineNumber"].AsBool(m_common.lineNumberEnable);
	root["longLineOn"].AsBool(m_common.longLineOnEnable);
	root["whiteSpace"].AsBool(m_common.whiteSpaceEnable);
	root["visibleHSB"].AsBool(m_common.visibleHSB);
	root["enableLogExecution"].AsBool(m_common.enableLogExecution);

	root["tabWidth"].AsInt(m_common.tabWidth);
	
	root["theme_syntax"].AsString(m_common.theme_color);	
	m_colors->SetFileName(m_common.theme_color);
	root["postpocessing"].AsString(m_common.postprocessing_fn);
	

	wxJSONValue &files = root["files"];
	
	for (unsigned int i = 0; i < static_cast<unsigned int>(files.Size()); ++i)
	{
		wxJSONValue &val = files.Item(i);
		wxString name = val["name"].AsString();
		wxString filename, filepattern;
		val["syntax"].AsString(filename);
		val["extensions"].AsString(filepattern);
		LanguageInfo *lang = FindByName(name,false);
		if (lang && !filename.empty())
			lang->SetFileName(filename );
		if (lang && !filepattern.empty())
			lang->SetFilePattern(filepattern);
			
	}
	return true;
}


wxAuiDockArt *Preferences::GetArtProvider(bool createnew)
{
	if ( !m_artprovider || createnew )
		m_artprovider = new ThemArtProvider();
	return m_artprovider;
}

wxAuiTabArt *Preferences::GetTabArtProvider()
{
	if (!m_tabartprovider)
		m_tabartprovider = new EditorTabArt();
	return m_tabartprovider;
}

ColourScheme *Preferences::GetColorScheme()
{
	return m_colors;
}

const wxColor &Preferences::GetStdColor(ColourScheme::StdColour code)
{
	return m_colors->Get(code);
}


LanguageInfo::LanguageInfo(const char *name, int file_type, int lexer, const char *filepattern)
	: m_name(name), m_inited(false), m_file_type(file_type), m_lexer(lexer), m_fold(0), m_filepattern(filepattern)
{

}

LanguageInfo::LanguageInfo()
	:  m_inited(false), m_file_type(FILETYPE_UNKNOW), m_lexer(0), m_fold(0), m_filepattern("*.*")
{

}

void LanguageInfo::Clear()
{
	m_inited = false;
	m_styles.clear();
}

void LanguageInfo::Init()
{
	if (m_inited)
		return;
	
	InitDef();

	if ( !m_filename.empty() )
		Read();

	m_inited = true;
	return;
}

void LanguageInfo::AddStyle(int id, const char *clr, const char *clrb, const char *fn, int fsize, bool bold, bool italic, const char *words)
{
	m_styles.push_back( StyleInfo() );
	StyleInfo &st = m_styles.back();
	//const wxString name;
	st.style_Id = id;
	st.foreground = clr;
	st.background = clrb;
	st.fontname = fn;
	st.fontsize = fsize;
	st.bold = bold;
	st.italic = italic;
	st.lettercase = 0;
	st.words = words;
}

void LanguageInfo::InitDef()
{
	m_styles.clear();
	switch (m_file_type)
	{
		case FILETYPE_UNKNOW:
			AddStyle(0, "BLACK", "WHITE", "", 10, 0, 0);			
			break;
		case FILETYPE_NC:
			AddStyle(SCE_GCODE_DEFAULT, "GRAY", "", "", 10, 0, 0);
			AddStyle(SCE_GCODE_COMMENT, "FOREST GREEN", "", "", 10, 0, 0);
			AddStyle(SCE_GCODE_COMMENT_ML, "FOREST GREEN", "", "", 10, 0, 0);
			AddStyle(SCE_GCODE_G, "BLUE", "", "", 10, true, 0);
			AddStyle(SCE_GCODE_M, "RED", "", "", 10, true, 0);
			AddStyle(SCE_GCODE_PARAM, "BROWN", "", "", 10, true, 0);
			AddStyle(SCE_GCODE_VAR, "SIENNA", "", "", 10, true, 0);
			AddStyle(SCE_GCODE_NUMBER, "BLACK", "", "", 10, true, 0);
			AddStyle(SCE_GCODE_COORDINATE, "MAGENTA", "", "", 10, true, 0);
			AddStyle(SCE_GCODE_WORD, "RED", "", "", 10, true, 0, GCoddeWordlist);
			AddStyle(SCE_GCODE_OPERATORS, "VIOLET RED", "", "", 10, true, 0);
			AddStyle(SCE_GCODE_IDENTIFIER, "BLACK", "", "", 10, 0, 0);
		break;
		case FILETYPE_GCMC:
			AddStyle(SCE_GCMC_DEFAULT, "GRAY", "", "", 10, true, 0);
			AddStyle(SCE_GCMC_COMMENT, "FOREST GREEN", "", "", 10, 0, 0);
			AddStyle(SCE_GCMC_COMMENT_ML, "FOREST GREEN", "", "", 10, 0, 0);
			AddStyle(SCE_GCMC_VAR, "SIENNA", "", "", 10, true, 0);
			AddStyle(SCE_GCMC_NUMBER, "BLACK", "", "", 10, true, 0);
			AddStyle(SCE_GCMC_OPERATORS, "VIOLET RED", "", "", 10, true, 0);
			AddStyle(SCE_GCMC_IDENTIFIER, "BLACK", "", "", 10, 0, 0);
			AddStyle(SCE_GCMC_WORD1, "RED", "", "", 10, true, 0, GcmcWordlist1);
			AddStyle(SCE_GCMC_WORD2,"BLUE", "","", 10, true, 0, GcmcWordlist2);
			AddStyle(SCE_GCMC_WORD3, "BLACK", "", "", 10, true, 0, GcmcWordlist3);	
			AddStyle(SCE_GCMC_STRING, "GREEN", "", "", 10, true, 0);
		break;
		case FILETYPE_JSON:
			AddStyle(SCE_JSON_DEFAULT, "WHITE", "", "", 10, 0, 0);
			AddStyle(SCE_JSON_NUMBER, "WHITE", "", "", 10, true, 0);
			AddStyle(SCE_JSON_STRING, "GREEN", "", "", 10, true, 0); 
			AddStyle(SCE_JSON_STRINGEOL, "GRAY", "", "", 10, true, 0);
			AddStyle(SCE_JSON_PROPERTYNAME, "BROWN", "", "", 10, true, 0);
			AddStyle(SCE_JSON_ESCAPESEQUENCE, "GRAY", "", "", 10, true, 0);
			AddStyle(SCE_JSON_LINECOMMENT, "FOREST GREEN", "", "", 10, 0, 0);
			AddStyle(SCE_JSON_BLOCKCOMMENT, "FOREST GREEN", "", "", 10, 0, 0);
			AddStyle(SCE_JSON_OPERATOR, "VIOLET RED", "", "", 10, true, 0);
			AddStyle(SCE_JSON_URI, "BLUE", "", "", 10, true, 0);
			AddStyle(SCE_JSON_COMPACTIRI, "SIENNA", "", "", 10, true, 0);
			AddStyle(SCE_JSON_KEYWORD, "RED", "", "", 10, true, 0, jsonWordlist);
			AddStyle(SCE_JSON_LDKEYWORD, "BLUE", "", "", 10, true, 0, jsonWordlist);
			AddStyle(SCE_JSON_ERROR, "WHITE", "RED", "", 10, true, 0);
		break;
		default:
			AddStyle(0, "BLACK", "", "", 10, 0, 0);
			break;
		
	}
}

const StyleInfo *LanguageInfo::GetById(int id) const
{
	auto it = std::find_if(m_styles.begin(), m_styles.end(), [id](const StyleInfo &p)
	{  return p.style_Id == id; });

	if (it == m_styles.end())
		return 0;
	return &(*it);
}

bool LanguageInfo::Read()
{
	
	wxLogNull logNo;
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
	int defSize = 10; 
	wxString deffont = "";
	wxString defClr = "BLACK";
	wxString defBgClr = "";
	bool defitalic = false;
	bool defbold = false;

	root["fontsize"].AsInt(defSize);
	root["fontname"].AsString(deffont);
	root["fclr"].AsString(defClr);
	root["bclr"].AsString(defBgClr);
	root["italic"].AsBool(defitalic);
	root["bold"].AsBool(defbold);

	wxJSONValue &styles = root["styles"];

	for (unsigned int i = 0; i < static_cast<unsigned int>(styles.Size()); ++i)
	{
		wxJSONValue &val = styles.Item(i);
		int id = -1;
		val["nameid"].AsInt(id);
	
		auto it = std::find_if(m_styles.begin(), m_styles.end(), [id](StyleInfo &p)
		{  return p.style_Id == id; });
		if (it == m_styles.end())
			continue;

		StyleInfo *st = &(*it);
		
		if (!val["fontsize"].AsInt(st->fontsize) )
			st->fontsize = defSize;
		if (!val["fontname"].AsString(st->fontname) )
			st->fontname = deffont;
		if (!val["fclr"].AsString(st->foreground) )
			st->foreground = defClr;
		if (!val["bclr"].AsString(st->background))
			st->background = defBgClr;
		if (!val["italic"].AsBool(st->italic) )
			st->italic = defitalic;
		if (!val["bold"].AsBool(st->bold))
			st->bold = defbold;

	}
	return false;
}


bool  LanguageInfo::Match(const wxString &fname)
{
	wxString filepattern = m_filepattern;
	while (!filepattern.empty())
	{
		
		wxString cur = filepattern.BeforeFirst(';');
		cur.Trim(true);
		cur.Trim(false);
		if ((cur == fname) ||
			(cur == (fname.BeforeLast('.') + ".*")) ||
			(cur == ("*." + fname.AfterLast('.')))) 
		{
			return true;
		}
		filepattern = filepattern.AfterFirst(';');
	}
	return false;
}

wxString LanguageInfo::CreateWildCard() const
{
	return wxString::Format(_("%s Files (%s)|%s"), m_name,m_filepattern, m_filepattern);
	/*
	if (pedit->GetFileType() == FILETYPE_GCMC)
		wildCard = _("GCMC Files (*.gcmc)|*.gcmc");
	else
		wildCard = _("GCode Files (*.ngc;*.nc)|*.ngc;*.nc");
	*/
}


const PostProcessing &Preferences::PostPocessing()
{ 
	if (!m_postrocessing.IsInited() && !m_common.postprocessing_fn.IsEmpty())
	{
		m_postrocessing.Read(m_common.postprocessing_fn);
	}
	return m_postrocessing;
}

PostProcessing::PostProcessing()
{
	m_inited = false;
	m_precision = 4;
	m_fext = L"nc";
	m_desc = L"Default preprocessor";
	m_prolog = "G90G80G21G49"; //START
	m_epilog = "M30"; //END
}

PostProcessing::~PostProcessing()
{

}

static wchar_t *do_trim(wchar_t *line, bool *token)
{
	wchar_t *s;
	wchar_t *end;
	bool in_token = false;
	if (token)	*token = false;
	for (s = line; *s != 0 && ::iswblank(*s); s++);

	for (end = s; *end != 0; end++)
	{
		if (*end == L'"')
		{
			if (!in_token)
			{
				*end = 0;
				s = end + 1;
				in_token = true;
				if (token)
					*token = true;
			}
			else // Last "
			{
				*end = 0;
				break;
			}
			continue;
		}
		if (::iswblank(*end) && !in_token)
		{
			*end = 0;
			break;
		}
		if (*end == '\r' || *end == '\n')
		{
			*end = 0;
			break;
		}
	}
	return s;
}

bool PostProcessing::Read(const wxString& fileName)
{
	std::filesystem::path name = StandartPaths::Get()->GetPreferencesPath(fileName);
	FILE *file = _wfopen(name.c_str(), L"r,ccs=UTF-8");
	if (file == NULL)
	{
		wxString msg = wxString::Format(_("Can not open file %s"), fileName);
		wxMessageBox(msg, _("Error opening file"));
		return false;
	}

	double d = 0;
	int index = 0;
	wchar_t *c = 0;
	wchar_t line[512];
	wchar_t *arg, *val;
	bool token;
	bool first_start = true;
	bool first_end = true;
	while (true)
	{
		if (fgetws(line, 512, file) == NULL)
			break;
		line[511] = 0;
		if (line[0] == L';')
			continue;
		c = wcschr(line, L'=');
		if (c == NULL)
			continue;
		*c = 0;
			
		arg = do_trim(line,0);
		val = do_trim(c+1, &token);
		if (wcscmp(arg, L"DESCRIPTION") == 0)
			m_desc = val;
		else if (wcscmp(arg, L"FILE_EXTENSION") == 0)
			m_fext = val;
		else if (wcscmp(arg, L"PRECISION") == 0 && ::iswdigit(*val) )
			m_precision = ::_wtoi(val);
		else if (wcscmp(arg, L"START") == 0)
		{
			if (first_start)
			{
				m_prolog = val;
				first_start = false;
			}
			else
			{ 
				m_prolog += L"\n";
				m_prolog += val;
			}
		}
		else if (wcscmp(arg, L"END") == 0)
		{
			if (first_end)
			{
				m_epilog = val;
				first_end = false;
			}
			else
			{
				m_epilog += L"\n";
				m_epilog += val;
			}
		}		
	}
	fclose(file);
	BuildPrologEpilogFiles();
	m_inited = true;
	return true;
}

bool PostProcessing::CreateTmpFile(const wchar_t *fname, const wxString &context)
{
	FILE *file = _wfopen(fname, L"wt,ccs=UTF-8");
	if (file == NULL)
	{
		wxString msg = wxString::Format(_("Can not open create file %s"), fname);
		wxMessageBox(msg, _("Error opening file"));
		return false;
	}
	// Write a string into the file.
	size_t strSize = context.length();
	if (fwrite(context.wc_str(), sizeof(wchar_t), strSize, file) != strSize)
	{
		wxString msg = wxString::Format(_("Can not write to the file %s"), fname);
		wxMessageBox(msg, _("Error writing file"));
		fclose(file);
		return false;
	}
	fclose(file);
	return true;
}

void PostProcessing::BuildPrologEpilogFiles()
{

	m_prologfn.clear();
	m_epilogfn.clear();
	if (!m_prolog.IsEmpty())
	{
		std::wstring dst_fname = StandartPaths::Get()->GetTemporaryPath(L"prologue.nc");
		if (CreateTmpFile(dst_fname.c_str(), m_prolog))
			m_prologfn = dst_fname;

	}
	if (!m_epilog.IsEmpty())
	{
		std::wstring dst_fname = StandartPaths::Get()->GetTemporaryPath(L"epilogue.nc");
		if ( CreateTmpFile(dst_fname.c_str(), m_epilog) )
			m_epilogfn = dst_fname;
	}
}
