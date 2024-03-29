#include "wx/wx.h"
#include "LexGCode.h"// Preferences
#include "prefs.h"
#include "wx/stc/stc.h"  // styled text control
#include "..\..\src\stc\scintilla\include\SciLexer.h"
#include "wx/jsonreader.h"
#include "standartpaths.h"
#include <wx/wfstream.h>




// G-Code 
const char* GCoddeWordlist = "abs acos asin atan cos exp fix fup ln round sin sqrt tan exists";
const char* GcmcWordlist1 = "abs acos asin atan atan_xy atan_xz atan_yz ceil comment cos count delete error exp fixpos_restore fixpos_set fixpos_store floor head "
"insert isangle isconst isdefined isdeg isdistance isdxf isfloat isgcode isinch isint ismm ismodemm isnone israd isrelative isscalar isstring issvg "
"isundef isvector isvectorlist layer layerstack length literal log10 log2 loge message normalize pause pi plane position pow relocate reverse rootate_xy rootate_xz rootate_yz "
"round scale sign sin sqrt svg_closepath tail tan to_chr to_deg to_distance to_float to_in to_inch to_int to_mm to_native to_none to_rad to_string to_val typeset undef warning "
"arc_ccw arc_ccw_r arc_cw arc_cw_r circle_ccw circle_ccw_r circle_cw circle_cw_r coolant drill dwell feedmode feedrate fixpos_restore fixpos_store goto goto_r move move_r pathmode "
"pause plane spindle spindlespeed toolchange rotate_xy rotate_xz rotate_yz";

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
//		"", // gcmc_sybatx;
//		"", //nc_syntax
	//	"", //them_id
		"", //theme_Name
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

void Preferences::UpdateAll(const wxString &themeid)
{
	Read();
	for (auto it = m_themes.begin(); it != m_themes.end(); ++it)
	{
		if ( it->id == themeid)
			SetTheme(*it);
	}
}

bool Preferences::Read()
{
	//Clear
	std::for_each(m_languages.begin(), m_languages.end(), [](LanguageInfo &p)
	{  return p.Clear(); });

	m_themes.clear();

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
	
	//root["theme"].AsString(m_common.theme_id);
	root["postpocessing"].AsString(m_common.postprocessing_fn);

	wxJSONValue &files = root["files"];
	if (files.IsArray())
	{

		for (unsigned int i = 0; i < static_cast<unsigned int>(files.Size()); ++i)
		{
			wxJSONValue &val = files.Item(i);
			wxString name = val["name"].AsString();
			wxString filename, filepattern;
			val["syntax"].AsString(filename);
			val["extensions"].AsString(filepattern);
			LanguageInfo *lang = FindByName(name, false);
			if (lang && !filename.empty())
				lang->SetFileName(filename);
			if (lang && !filepattern.empty())
				lang->SetFilePattern(filepattern);

		}
	}

	/*
	{
		"id": "BLACK",
		"name" : "Black theme",
		"nameru" : "������ ����",
		"window_colors" : "them_black.json",
		"GCODE" : "nc_syntax_black.json",
		}
	*/

	
	wxJSONValue &themes = root["themes"];
	if (themes.IsArray())
	{
		for (unsigned int i = 0; i < static_cast<unsigned int>(themes.Size()); ++i)
		{
			m_themes.push_back(ThemeInfo());
			ThemeInfo &ti = m_themes.back();
			wxJSONValue &val = themes.Item(i);
			ti.id = val["id"].AsString();
			wxString nameid = wxString("name") + StandartPaths::Get()->GetLanguageCatalog();
			ti.name = val[nameid].AsString();
			if ( ti.name.IsEmpty() )
				ti.name = val["name"].AsString();
			ti.wndcolorsfn = val["window_colors"].AsString();

			//m_colors->SetFileName(wndcolor);
			// for all lang
			for (auto itlan = m_languages.begin(); itlan != m_languages.end(); ++itlan)
			{
				wxString filename = val[itlan->GetName()].AsString();
				if (!filename.empty())
					ti.files_syntax_color.insert(std::make_pair(itlan->GetName(), filename));
					//itlan->SetFileName(filename);
			}
		}
	}
	return true;
}

void Preferences::SetTheme(const ThemeInfo &ti)
{
	m_colors->SetFileName(ti.wndcolorsfn);
		// for all lang
	for (auto itlan = m_languages.begin(); itlan != m_languages.end(); ++itlan)
	{

		auto itfsi = ti.files_syntax_color.find(itlan->GetName());
		if ( itfsi != ti.files_syntax_color.end() )
		{
			wxString filename = itfsi->second;
			if( !filename.empty() )
				itlan->SetFileName(filename);
		}
	}
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

void LanguageInfo::SetFileName(const wxString &filename)
{ 
	Clear();
	m_filename = filename; 
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
			AddStyle(SCE_GCODE_DEFAULT, "#999999", "", "", 10, 0, 0);
			AddStyle(SCE_GCODE_COMMENT, "#85a57c", "", "", 10, 0, 0);
			AddStyle(SCE_GCODE_COMMENT_ML, "#85a57c", "", "", 10, 0, 0);
			AddStyle(SCE_GCODE_G, "#55aadd", "", "", 10, true, 0);
			AddStyle(SCE_GCODE_M, "#55aadd", "", "", 10, true, 0);
			AddStyle(SCE_GCODE_PARAM, "#ee6677", "", "", 10, true, 0);
			AddStyle(SCE_GCODE_VAR, "#ee6677", "", "", 10, true, 0);
			AddStyle(SCE_GCODE_NUMBER, "#bbbbbb", "", "", 10, true, 0);
			AddStyle(SCE_GCODE_COORDINATE, "#ee6677", "", "", 10, true, 0);
			AddStyle(SCE_GCODE_WORD, "#ee6677", "", "", 10, true, 0, GCoddeWordlist);
			AddStyle(SCE_GCODE_OPERATORS, "#999999", "", "", 10, true, 0);
			AddStyle(SCE_GCODE_IDENTIFIER, "#999999", "", "", 10, 0, 0);
		break;
		case FILETYPE_GCMC:
			AddStyle(SCE_GCMC_DEFAULT, "#999999", "", "", 10, 0, 0);
			AddStyle(SCE_GCMC_COMMENT, "#85a57c", "", "", 10, 0, 0);
			AddStyle(SCE_GCMC_COMMENT_ML, "#85a57c", "", "", 10, 0, 0);
			AddStyle(SCE_GCMC_VAR, "#999999", "", "", 10, true, 0);
			AddStyle(SCE_GCMC_NUMBER, "#bbbbbb", "", "", 10, true, 0);
			AddStyle(SCE_GCMC_OPERATORS, "#999999", "", "", 10, true, 0);
			AddStyle(SCE_GCMC_IDENTIFIER, "#ffbb44", "", "", 10, 0, 0);
			AddStyle(SCE_GCMC_WORD1, "#55aadd", "", "", 10, true, 0, GcmcWordlist1);
			AddStyle(SCE_GCMC_WORD2,"#5cd08d", "","", 10, true, 0, GcmcWordlist2);
			AddStyle(SCE_GCMC_WORD3, "#999999", "", "", 10, true, 0, GcmcWordlist3);	
			AddStyle(SCE_GCMC_STRING, "#ee6677", "", "", 10, true, 0);
		break;
		case FILETYPE_JSON:
			AddStyle(SCE_JSON_DEFAULT, "WHITE", "", "", 10, 0, 0);
			AddStyle(SCE_JSON_NUMBER, "#ee6677", "", "", 10, true, 0);
			AddStyle(SCE_JSON_STRING, "#84e484", "", "", 10, true, 0); 
			AddStyle(SCE_JSON_STRINGEOL, "#84e484", "", "", 10, true, 0);
			AddStyle(SCE_JSON_PROPERTYNAME, "#55aadd", "", "", 10, true, 0);
			AddStyle(SCE_JSON_ESCAPESEQUENCE, "#84e484", "", "", 10, true, 0);
			AddStyle(SCE_JSON_LINECOMMENT, "#84e484", "", "", 10, 0, 0);
			AddStyle(SCE_JSON_BLOCKCOMMENT, "#84e484", "", "", 10, 0, 0);
			AddStyle(SCE_JSON_OPERATOR, "#ffffff", "", "", 10, true, 0);
			AddStyle(SCE_JSON_URI, "#ee6677", "", "", 10, true, 0);
			AddStyle(SCE_JSON_COMPACTIRI, "#ee6677", "", "", 10, true, 0);
			AddStyle(SCE_JSON_KEYWORD, "#ffbb44", "", "", 10, true, 0, jsonWordlist);
			AddStyle(SCE_JSON_LDKEYWORD, "#ffbb44", "", "", 10, true, 0, jsonWordlist);
			AddStyle(SCE_JSON_ERROR, "#FF0000", "RED", "", 10, true, 0);
		break;
		default:
			AddStyle(0, "WHITE", "", "", 10, 0, 0);
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
	unsigned int num_styles = static_cast<unsigned int>(styles.Size());

	for (unsigned int i = 0; i < num_styles ; ++i)
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
		wildCard = _("G-Code Files (*.ngc;*.nc)|*.ngc;*.nc");
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
	m_prolog = "G90 G80 G21 G49\n"; //START
	m_epilog = "M30\n"; //END
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
				m_prolog += L"\n";
				first_start = false;
			}
			else
			{ 				
				m_prolog += val;
				m_prolog += L"\n";
			}
		}
		else if (wcscmp(arg, L"END") == 0)
		{
			if (first_end)
			{
				m_epilog = val;
				m_epilog += L"\n";
				first_end = false;
			}
			else
			{				
				m_epilog += val;
				m_epilog += L"\n";
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

#if wxUSE_FFILE
	// Take care to use "b" to ensure that possibly non-native EOLs in the file
	// contents are not mangled when saving it.
	wxFFile file(fname, wxS("wb"));
#elif wxUSE_FILE
	wxFile file(filename, wxFile::write);
#endif

	if ( !file.IsOpened() )
	{
		wxString msg = wxString::Format(_("Can not open create file %s"), fname);
		wxMessageBox(msg, _("Error opening file"));
		return false;
	}

	if (!file.Write(context, *wxConvCurrent))
	{
		wxString msg = wxString::Format(_("Can not write to the file %s"), fname);
		wxMessageBox(msg, _("Error writing file"));
		return false;
	}
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
