
#ifndef _WX_DEFSEXT_H_
#define _WX_DEFSEXT_H_
//============================================================================

// ----------------------------------------------------------------------------
// standard IDs
// ----------------------------------------------------------------------------


#define MAX_EDITOR_FILE_SIZE 300000000
#define NUM_MENU_MACROS 30

enum {
	// menu IDs
	ID_PROPERTIES = wxID_HIGHEST,
	ID_OPENFILE,
	ID_NEWNC,
	ID_NEWGCMC,
	ID_GLOBALPREFS,
	ID_USERPREFS,
	ID_DOWNLOADUPDATE,
	ID_OPENRECENT,
	ID_MACROSES,
	ID_MATHCALC,
	ID_MATHEXPRESSION,
	ID_GCODE_CHECK,
	ID_GCODE_SIMULATE,
	ID_GCODE_CONVERTGCMC,
	ID_GCODE_KILLGCMCPROCESS,
	CHECK_GCODE_UPDATE,
	CHECK_GCODE_COMPLETE,
	CHECK_SIMULATE_UPDATE,
	CHECK_SIMULATE_COMPLETE,
	CUTTING_SIMULATE_UPDATE,
	CUTTING_SIMULATE_COMPLETE,
	ID_SELECTLANGUAGE,
	
	ID_SHOWWLCOME,
	ID_MACROSFIRST,
	ID_MACROSLAST = ID_MACROSFIRST + NUM_MENU_MACROS,
	ID_3D_FIRST,
	ID_SHOW2DGRID,
	ID_SETSHOWFIRST = ID_SHOW2DGRID,
	ID_SHOWBOUNDS,
	ID_SHOW3DGRID,
	ID_SHOWTOOL,
	ID_SHOWAXIS,
	ID_SETSHOWLAST = ID_SHOWAXIS,
	ID_SEMULATE_START,
	ID_SEMULATE_PAUSE,
	ID_SEMULATE_STOP,
	ID_SEMULATE_GOTOBEGIN,
	ID_SEMULATE_GOTOEND,	
	ID_3D_LAST = ID_SEMULATE_GOTOEND,
	ID_EDIT_FIRST,
    ID_INDENTINC = ID_EDIT_FIRST,
	ID_INCLUDE_FILE_OPEN,
	ID_SELECTLINE,
    ID_INDENTRED,
    ID_FINDNEXT,
    ID_REPLACE,
    ID_REPLACENEXT,
    ID_BRACEMATCH,
    ID_GOTO,
    ID_PAGEACTIVE,
    ID_DISPLAYEOL,
    ID_INDENTGUIDE,
    ID_LINENUMBER,
    ID_LONGLINEON,
    ID_WHITESPACE,
    ID_FOLDTOGGLE,
    ID_OVERTYPE,
    ID_READONLY,
    ID_WRAPMODEON,
    ID_CHANGECASE,
    ID_CHANGELOWER,
    ID_CHANGEUPPER,
    ID_HIGHLIGHTLANG,
    ID_CONVERTEOL,
    ID_CONVERTCR,
    ID_CONVERTCRLF,
    ID_CONVERTLF,
    ID_MULTIPLE_SELECTIONS,
    ID_MULTI_PASTE,
    ID_MULTIPLE_SELECTIONS_TYPING,
    ID_CUSTOM_POPUP,
    ID_USECHARSET,
    ID_CHARSETANSI,
    ID_CHARSETMAC,
    ID_PAGEPREV,
    ID_PAGENEXT,
    ID_EDIT_LAST = ID_PAGENEXT,
	ID_DIRTREE_FIRST,
	ID_TREE_FILE_OPEN = ID_DIRTREE_FIRST,
	ID_TREE_NEWNC,
	ID_TREE_NEWGCMC,
	ID_TREE_FILE_RENAME,
	ID_TREE_FILE_DELETE,
	ID_TREE_FOLDER_REMOVE,
	ID_TREE_FOLDER_OPEN, 
	ID_DIRTREE_LAST = ID_TREE_FOLDER_OPEN,
    ID_WINDOW_MINIMAL,
    // other IDs
    ID_STATUSBAR,
    ID_TITLEBAR,
    ID_ABOUTTIMER,
    ID_UPDATETIMER,

    // dialog find IDs
    ID_DLG_FIND_TEXT,

    // preferences IDs
    ID_PREFS_LANGUAGE,
    ID_PREFS_STYLETYPE,
    ID_PREFS_KEYWORDS,
};


// ----------------------------------------------------------------------------
// global items
// ----------------------------------------------------------------------------

class  IntClientData : public wxClientData
{
public:
	IntClientData(int i = 0) : m_data(i) { }
	virtual ~IntClientData() { }
	void SetData(int &data) { m_data = data; }
	int GetData() const { return m_data; }

private:
	int m_data;
};


// this is typically in a header: it just declares MY_EVENT event type
wxDECLARE_EVENT(FILE_MODIFYED_EVENT, wxCommandEvent);
wxDECLARE_EVENT(FILE_OPEN_EVENT, wxCommandEvent);
wxDECLARE_EVENT(FILE_REMOVE_EVENT, wxCommandEvent);
wxDECLARE_EVENT(FILE_RENAME_EVENT, wxCommandEvent);
wxDECLARE_EVENT(FILE_NEW_EVENT, wxCommandEvent);

// this is a definition so can't be in a header
#endif // _WX_DEFSEXT_H_
