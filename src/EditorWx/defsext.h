
#ifndef _WX_DEFSEXT_H_
#define _WX_DEFSEXT_H_
//============================================================================

// ----------------------------------------------------------------------------
// standard IDs
// ----------------------------------------------------------------------------


#define MAX_EDITOR_FILE_SIZE 300000000
#define NUM_MENU_MACROS 30
#include "ilogger.h"

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
	ID_CLOSEACTIVETAB,
	ID_CLOSEALL,
	ID_CLOSEALLBUTTHIS,
	ID_ADDFIILEDIRTOPANE,
	CHECK_GCODE_UPDATE,
	DRAW_GCODE_UPDATE,
	CUTTING_SIMULATE_UPDATE,
	CUTTING_SIMULATE_COMPLETE,

	ID_WRITEFEEDBACK,
	ID_HELPGCMC,
	ID_HELPNC,
	ID_WHATNEWS,
	ID_SHOWWELCOME,
	ID_SHOWDIRPANE,
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
    
    // other IDs
    ID_ABOUTTIMER,
    ID_UPDATETIMER,

    // dialog find IDs
    ID_DLG_FIND_TEXT

    // preferences IDs
 //   ID_PREFS_LANGUAGE,
 //   ID_PREFS_STYLETYPE,
 //   ID_PREFS_KEYWORDS,

};

enum MsgStatusLevel
{
	MSLUndefened = 0,
	MSLWarning = LOG_WARNING,
	MSLError = LOG_ERROR,
	MSLInfo = LOG_INFORMATION,
	MSLFileStatus = LOG_INFORMATIONSUM

};

// ----------------------------------------------------------------------------
// global items
// ----------------------------------------------------------------------------

class  LogClientData : public wxClientData
{
public:
	LogClientData(const int &line, const MsgStatusLevel & type) : m_line(line), m_type(type) { }
	virtual ~LogClientData() { }
	void SetLine(const int &line) { m_line = line; }
	int GetLine() const { return m_line; }
	void SetType(const MsgStatusLevel &type) { m_type = type; }
	MsgStatusLevel GetType() const { return m_type; }
private:
	int m_line;
	MsgStatusLevel m_type;
};


// this is typically in a header: it just declares MY_EVENT event type
wxDECLARE_EVENT(FILE_MODIFYED_EVENT, wxCommandEvent);
wxDECLARE_EVENT(FILE_OPEN_EVENT, wxCommandEvent);
wxDECLARE_EVENT(FILE_REMOVE_EVENT, wxCommandEvent);
wxDECLARE_EVENT(FILE_RENAME_EVENT, wxCommandEvent);
wxDECLARE_EVENT(FILE_NEW_EVENT, wxCommandEvent);

// this is a definition so can't be in a header
#endif // _WX_DEFSEXT_H_
