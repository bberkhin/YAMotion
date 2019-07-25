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

#include "them.h"

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
	bool visibleHSB;
	bool enableLogExecution;
	int tabWidth;	
	wxString gcmc_syntax;
	wxString nc_syntax;
	wxString theme_color;
};

//----------------------------------------------------------------------------
// LanguageInfo

#define FILETYPE_UNKNOW 0  
#define FILETYPE_NC   1
#define FILETYPE_GCMC 2
#define FILETYPE_JSON 3

//----------------------------------------------------------------------------
// StyleInfo
struct StyleInfo 
{
    wxString name;
    wxString foreground;
    wxString background;
    wxString fontname;
    int fontsize;
	bool bold;
	bool italic;
	bool underline;
    int lettercase;
	int style_Id;
	const char *words;
};

typedef std::vector<StyleInfo>  StylesInfos;
class LanguageInfo
{
public:
	LanguageInfo();
	LanguageInfo(const char *name, int file_type, int lexer, const char *filepattern);
	const StylesInfos &Styles() const { return m_styles; }
	const wxString & GetName() const { return m_name; }
	int	 GetFileType() const { return m_file_type;  }
	bool Match(const wxString &fname);
	int  Lexer() const { return m_lexer; }
	int  Fold() const { return m_fold; }
	void Init();
	void SetFileName(const wxString &filename) { m_filename = filename; }
	void SetFilePattern(const wxString &filename) { m_filepattern = filename; }
	void Clear();
	const StyleInfo *GetById(int id) const;

private:
	bool Read();
	void InitDef();
	void AddStyle(int id, const char *clr, const char *clrb, const char *fn, int fsize, bool bold = false, bool italic=false,  const char *words = 0);
private:
	StylesInfos m_styles;
	wxString m_name;
	wxString m_filename;
	wxString m_filepattern;
	int		 m_file_type;
	int      m_lexer;
	int      m_fold;
	


	bool	m_inited;
};

//class Preferences;
extern class Preferences global_pprefs;



class wxAuiDockArt;
class wxAuiTabArt;


class Preferences
{
public:
	Preferences();
	~Preferences();
	bool Read();
	static Preferences *Get() { return &global_pprefs; }
	const CommonInfo &Common() const { return m_common;  }
	wxAuiDockArt *GetArtProvider(bool createnew = false);
	wxAuiTabArt *GetTabArtProvider();
	ColourScheme *GetColorScheme();
	const wxColor & GetStdColor(ColourScheme::StdColour code);
	const LanguageInfo *FindByType(int type,bool init = true) ;
	const LanguageInfo *FindByFileName(const wxString &name, bool init = true);
	LanguageInfo *FindByName(const wxString &name, bool init = true);
private:
	bool DoRead(const wxString& fileName, bool errifnoexist);
private:
	CommonInfo m_common;
	std::vector<LanguageInfo>  m_languages;
	wxAuiDockArt *m_artprovider;
	wxAuiTabArt *m_tabartprovider;
	ColourScheme *m_colors;
};


#endif // _PREFS_H_
