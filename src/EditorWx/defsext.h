
#ifndef _WX_DEFSEXT_H_
#define _WX_DEFSEXT_H_
//============================================================================

// ----------------------------------------------------------------------------
// standard IDs
// ----------------------------------------------------------------------------

enum {
    // menu IDs
    myID_PROPERTIES = wxID_HIGHEST,
	ID_GCODE_CHECK,
	ID_GCODE_SIMULATE,
	CHECK_GCODE_UPDATE,
	CHECK_GCODE_COMPLETE,
	CHECK_SIMULATE_UPDATE,
	CHECK_SIMULATE_COMPLETE,
	myID_SETVIEWFIRST,
	myID_SETVIEWLAST = myID_SETVIEWFIRST + 8,
	myID_EDIT_FIRST,
    myID_INDENTINC = myID_EDIT_FIRST,
    myID_INDENTRED,
    myID_FINDNEXT,
    myID_REPLACE,
    myID_REPLACENEXT,
    myID_BRACEMATCH,
    myID_GOTO,
    myID_PAGEACTIVE,
    myID_DISPLAYEOL,
    myID_INDENTGUIDE,
    myID_LINENUMBER,
    myID_LONGLINEON,
    myID_WHITESPACE,
    myID_FOLDTOGGLE,
    myID_OVERTYPE,
    myID_READONLY,
    myID_WRAPMODEON,
    myID_ANNOTATION_ADD,
    myID_ANNOTATION_REMOVE,
    myID_ANNOTATION_CLEAR,
    myID_ANNOTATION_STYLE_HIDDEN,
    myID_ANNOTATION_STYLE_STANDARD,
    myID_ANNOTATION_STYLE_BOXED,
    myID_CHANGECASE,
    myID_CHANGELOWER,
    myID_CHANGEUPPER,
    myID_HIGHLIGHTLANG,
    myID_HIGHLIGHTFIRST,
    myID_HIGHLIGHTLAST = myID_HIGHLIGHTFIRST + 10,
    myID_CONVERTEOL,
    myID_CONVERTCR,
    myID_CONVERTCRLF,
    myID_CONVERTLF,
    myID_MULTIPLE_SELECTIONS,
    myID_MULTI_PASTE,
    myID_MULTIPLE_SELECTIONS_TYPING,
    myID_CUSTOM_POPUP,
    myID_USECHARSET,
    myID_CHARSETANSI,
    myID_CHARSETMAC,
    myID_PAGEPREV,
    myID_PAGENEXT,
    myID_SELECTLINE,
    myID_EDIT_LAST = myID_SELECTLINE,
    myID_WINDOW_MINIMAL,
    // other IDs
    myID_STATUSBAR,
    myID_TITLEBAR,
    myID_ABOUTTIMER,
    myID_UPDATETIMER,

    // dialog find IDs
    myID_DLG_FIND_TEXT,

    // preferences IDs
    myID_PREFS_LANGUAGE,
    myID_PREFS_STYLETYPE,
    myID_PREFS_KEYWORDS,
};

// ----------------------------------------------------------------------------
// global items
// ----------------------------------------------------------------------------


#endif // _WX_DEFSEXT_H_
