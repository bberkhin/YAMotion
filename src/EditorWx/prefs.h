//////////////////////////////////////////////////////////////////////////////
// File:        prefs.h
// Purpose:     STC test Preferences initialization
// Maintainer:  Wyo
// Created:     2003-09-01
// Copyright:   (c) wxGuide
// Licence:     wxWindows licence
//////////////////////////////////////////////////////////////////////////////

#ifndef _PREFS_H_
#define _PREFS_H_

//----------------------------------------------------------------------------
// informations
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

//! wxWidgets headers

//! wxWidgets/contrib headers

//! application headers


//============================================================================
// declarations
//============================================================================

//! general style types
#define mySTC_TYPE_DEFAULT 0

//----------------------------------------------------------------------------
//! style bits types
#define mySTC_STYLE_BOLD 1
#define mySTC_STYLE_ITALIC 2
#define mySTC_STYLE_UNDERL 4
#define mySTC_STYLE_HIDDEN 8

//----------------------------------------------------------------------------
//! general folding types
#define mySTC_FOLD_COMMENT 1
#define mySTC_FOLD_COMPACT 2
#define mySTC_FOLD_PREPROC 4

#define mySTC_FOLD_HTML 16
#define mySTC_FOLD_HTMLPREP 32

#define mySTC_FOLD_COMMENTPY 64
#define mySTC_FOLD_QUOTESPY 128

//----------------------------------------------------------------------------
//! flags
#define mySTC_FLAG_WRAPMODE 16


#define STYLE_TYPES_COUNT 32



//----------------------------------------------------------------------------
// CommonInfo

struct CommonInfo 
{
    // editor functionality prefs
    bool syntaxEnable;
    bool foldEnable;
    bool indentEnable;
    // display defaults prefs
    bool readOnlyInitial;
    bool overTypeInitial;
    bool wrapModeInitial;
    bool displayEOLEnable;
    bool indentGuideEnable;
    bool lineNumberEnable;
    bool longLineOnEnable;
    bool whiteSpaceEnable;
	int tabWidth;
	wxString gcmc_syntax;
	wxString nc_syntax;
	wxString theme_color;
};
extern CommonInfo g_CommonPrefs;

//----------------------------------------------------------------------------
// LanguageInfo

#define FILETYPE_UNKNOW 0  
#define FILETYPE_NC   1
#define FILETYPE_GCMC 2

//extern const LanguageInfo g_LanguagePrefs[];
//extern const int g_LanguagePrefsSize;

//----------------------------------------------------------------------------
// StyleInfo
struct StyleInfo {
    const wxString name;
    const wxString foreground;
    const wxString background;
    const wxString fontname;
    int fontsize;
    int fontstyle;
    int lettercase;
};

//extern const StyleInfo g_StylePrefs[];
//extern const int g_StylePrefsSize;

//struct LanguageInfo {
//	const char *name;
//	int file_type;
//	const char *filepattern;
//	int lexer;
//	struct {
//		int type;
//		const char *words;
//	} styles[STYLE_TYPES_COUNT];
//	int folds;
//};

typedef std::vector<StyleInfo>  StylesInfos;
class LanguageInfo
{
public:
	LanguageInfo(const wxString &filename);
	const StylesInfos &Styles() { return m_styles; }
	const wxString & GetName() const { return m_name; }
	int	 GetFileType() { return m_file_type;  }
	bool Match(const wxString &fname);
	int  Lexer() const { return lexer; }
	void Init();
private:
	bool Read();
private:
	StylesInfos m_styles;
	wxString m_name;
	wxString m_filename;
	wxString m_filepattern;
	int		 m_file_type;
	int      lexer;
	bool m_inited;
};

class Preferences
{
public:
	Preferences();
	~Preferences();
	bool Read();
	const CommonInfo &Common() const { return m_common;  }
	const LanguageInfo  &FindByType(int type);
	const LanguageInfo &FindByFileName(const wxString &name);
private:
	CommonInfo m_common;
	std::vector<LanguageInfo>  m_languages;
};



#endif // _PREFS_H_
