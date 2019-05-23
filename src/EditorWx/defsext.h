
#ifndef _WX_DEFSEXT_H_
#define _WX_DEFSEXT_H_
//============================================================================

// ----------------------------------------------------------------------------
// standard IDs
// ----------------------------------------------------------------------------


#define MAX_EDITOR_FILE_SIZE 300000000

enum {
    // menu IDs
    myID_PROPERTIES = wxID_HIGHEST,
	ID_NEWNC,
	ID_NEWGCMC,
	ID_OPENFILE,
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
	ID_DOWNLOADUPDATE,
	ID_SHOWWLCOME,
	myID_3D_FIRST,
	myID_SETVIEWFIRST = myID_3D_FIRST,
	myID_SETVIEWLAST = myID_SETVIEWFIRST + 8,
	ID_SHOW2DGRID,
	ID_SETSHOWFIRST = ID_SHOW2DGRID,
	ID_SHOWBOUNDS,
	ID_SHOW3DGRID,
	ID_SHOWTOOL,
	ID_SHOWAXIS,
	ID_SETSHOWLAST = ID_SHOWAXIS,
	myID_SEMULATE_START,
	myID_SEMULATE_PAUSE,
	myID_SEMULATE_STOP,
	myID_SEMULATE_GOTOBEGIN,
	myID_SEMULATE_GOTOEND,	
	myID_3D_LAST = myID_SEMULATE_GOTOEND,
	myID_EDIT_FIRST,
    myID_INDENTINC = myID_EDIT_FIRST,
	myID_SELECTLINE,
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
    myID_EDIT_LAST = myID_PAGENEXT,
	ID_DIRTREE_FIRST,
	ID_TREE_FILE_OPEN = ID_DIRTREE_FIRST,
	ID_TREE_FILE_RENAME,
	ID_TREE_FILE_DELETE,
	ID_TREE_FOLDER_OPEN, 
	ID_DIRTREE_LAST = ID_TREE_FOLDER_OPEN,
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
// this is a definition so can't be in a header
#endif // _WX_DEFSEXT_H_
