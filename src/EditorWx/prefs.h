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
#include "wx/stc/stc.h"  // styled text control

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

struct CommonInfo {
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
};
extern const CommonInfo g_CommonPrefs;

//----------------------------------------------------------------------------
// LanguageInfo

struct LanguageInfo {
    const char *name;
    const char *filepattern;
    int lexer;
    struct {
        int type;
        const char *words;
    } styles [STYLE_TYPES_COUNT];
    int folds;
};

extern const LanguageInfo g_LanguagePrefs[];
extern const int g_LanguagePrefsSize;

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

extern const StyleInfo g_StylePrefs[];
extern const int g_StylePrefsSize;

#endif // _PREFS_H_
