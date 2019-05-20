#include "wx/wx.h"
#include "wx/filename.h" // filename support

//! application headers
#include "defsext.h"     // additional definitions
#include "edit.h"        // edit module
#include "codedescription.h"
#include "configdata.h"
#include "appframe.h"


#if wxUSE_FFILE
#include "wx/ffile.h"
#elif wxUSE_FILE
#include "wx/file.h"
#endif

//----------------------------------------------------------------------------
// resources
//----------------------------------------------------------------------------


//============================================================================
// declarations
//============================================================================

// The (uniform) style used for the annotations.
const int ANNOTATION_STYLE = wxSTC_STYLE_LASTPREDEFINED + 1;

//============================================================================
// implementation
//============================================================================

//----------------------------------------------------------------------------
// Edit
//----------------------------------------------------------------------------

wxDEFINE_EVENT(FILE_MODIFYED_EVENT, wxCommandEvent);

wxBEGIN_EVENT_TABLE(Edit, wxStyledTextCtrl)
	// common
	EVT_SIZE(Edit::OnSize)
	// edit
	EVT_MENU(wxID_CLEAR, Edit::OnEditClear)
	EVT_MENU(wxID_CUT, Edit::OnEditCut)
	EVT_MENU(wxID_COPY, Edit::OnEditCopy)
	EVT_MENU(wxID_PASTE, Edit::OnEditPaste)
	EVT_MENU(wxID_SELECTALL, Edit::OnEditSelectAll)
	EVT_MENU(myID_SELECTLINE, Edit::OnEditSelectLine)
	EVT_MENU(wxID_REDO, Edit::OnEditRedo)
	EVT_MENU(wxID_UNDO, Edit::OnEditUndo)
	EVT_MENU(myID_INDENTINC, Edit::OnEditIndentInc)
	EVT_MENU(myID_INDENTRED, Edit::OnEditIndentRed)

	// find
	EVT_MENU(wxID_FIND, Edit::OnFind)
	EVT_MENU(myID_FINDNEXT, Edit::OnFindNext)
	EVT_MENU(myID_REPLACE, Edit::OnReplace)
	EVT_MENU(myID_REPLACENEXT, Edit::OnReplaceNext)
	EVT_MENU(myID_BRACEMATCH, Edit::OnBraceMatch)
	EVT_MENU(myID_GOTO, Edit::OnGoto)
	
	EVT_FIND(wxID_ANY, Edit::OnFindDialog)
	EVT_FIND_NEXT(wxID_ANY, Edit::OnFindDialog)
	EVT_FIND_REPLACE(wxID_ANY, Edit::OnFindDialog)
	EVT_FIND_REPLACE_ALL(wxID_ANY, Edit::OnFindDialog)
	EVT_FIND_CLOSE(wxID_ANY, Edit::OnFindDialog)


	// view
	EVT_MENU_RANGE(myID_HIGHLIGHTFIRST, myID_HIGHLIGHTLAST,
	Edit::OnHighlightLang)
	EVT_MENU(myID_DISPLAYEOL, Edit::OnDisplayEOL)
	EVT_MENU(myID_INDENTGUIDE, Edit::OnIndentGuide)
	EVT_MENU(myID_LINENUMBER, Edit::OnLineNumber)
	EVT_MENU(myID_LONGLINEON, Edit::OnLongLineOn)
	EVT_MENU(myID_WHITESPACE, Edit::OnWhiteSpace)
	EVT_MENU(myID_FOLDTOGGLE, Edit::OnFoldToggle)
	EVT_MENU(myID_OVERTYPE, Edit::OnSetOverType)
	EVT_MENU(myID_READONLY, Edit::OnSetReadOnly)
	EVT_MENU(myID_WRAPMODEON, Edit::OnWrapmodeOn)
	EVT_MENU(myID_CHARSETANSI, Edit::OnUseCharset)
	EVT_MENU(myID_CHARSETMAC, Edit::OnUseCharset)
	// annotations
	EVT_MENU(myID_ANNOTATION_ADD, Edit::OnAnnotationAdd)
	EVT_MENU(myID_ANNOTATION_REMOVE, Edit::OnAnnotationRemove)
	EVT_MENU(myID_ANNOTATION_CLEAR, Edit::OnAnnotationClear)
	EVT_MENU(myID_ANNOTATION_STYLE_HIDDEN, Edit::OnAnnotationStyle)
	EVT_MENU(myID_ANNOTATION_STYLE_STANDARD, Edit::OnAnnotationStyle)
	EVT_MENU(myID_ANNOTATION_STYLE_BOXED, Edit::OnAnnotationStyle)
	// extra
	EVT_MENU(myID_CHANGELOWER, Edit::OnChangeCase)
	EVT_MENU(myID_CHANGEUPPER, Edit::OnChangeCase)
	EVT_MENU(myID_CONVERTCR, Edit::OnConvertEOL)
	EVT_MENU(myID_CONVERTCRLF, Edit::OnConvertEOL)
	EVT_MENU(myID_CONVERTLF, Edit::OnConvertEOL)
	EVT_MENU(myID_MULTIPLE_SELECTIONS, Edit::OnMultipleSelections)
	EVT_MENU(myID_MULTI_PASTE, Edit::OnMultiPaste)
	EVT_MENU(myID_MULTIPLE_SELECTIONS_TYPING, Edit::OnMultipleSelectionsTyping)
	// stc
	EVT_STC_MARGINCLICK(wxID_ANY, Edit::OnMarginClick)
	EVT_STC_CHARADDED(wxID_ANY, Edit::OnCharAdded)
	EVT_STC_MODIFIED(wxID_ANY, Edit::OnChanged)

	EVT_STC_DWELLSTART(wxID_ANY, Edit::OnDwellStart)
	EVT_STC_DWELLEND(wxID_ANY, Edit::OnDwellEnd)
		
	EVT_KILL_FOCUS(Edit::OnKillFocus)
	EVT_KEY_DOWN( Edit::OnKeyDown )
	EVT_LEAVE_WINDOW(Edit::OnMouseLeave)

wxEND_EVENT_TABLE()

Edit::Edit (wxWindow *parent, wxWindowID id,  const wxPoint &pos, const wxSize &size, long style)
    : wxStyledTextCtrl (parent, id, pos, size, style) 
{

    m_filename = wxEmptyString;
	m_newfile = true;
    m_LineNrID = 0;
    m_DividerID = 1;
    m_FoldingID = 2;
	m_modified = false;

    // initialize language
    m_language = NULL;
	dlg_find = NULL;
	find_data.SetFlags(wxFR_DOWN);
	ConfigData *config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
	if (config)
		config->ReadFindAndReplase(&find_data);

    // default font for all styles
    SetViewEOL (g_CommonPrefs.displayEOLEnable);
    SetIndentationGuides (g_CommonPrefs.indentGuideEnable);
    SetEdgeMode (g_CommonPrefs.longLineOnEnable?
                 wxSTC_EDGE_LINE: wxSTC_EDGE_NONE);
    SetViewWhiteSpace (g_CommonPrefs.whiteSpaceEnable?
                       wxSTC_WS_VISIBLEALWAYS: wxSTC_WS_INVISIBLE);
    SetOvertype (g_CommonPrefs.overTypeInitial);
    SetReadOnly (g_CommonPrefs.readOnlyInitial);
    SetWrapMode (g_CommonPrefs.wrapModeInitial?
                 wxSTC_WRAP_WORD: wxSTC_WRAP_NONE);
    wxFont font(wxFontInfo(10).Family(wxFONTFAMILY_MODERN));
    StyleSetFont (wxSTC_STYLE_DEFAULT, font);
    StyleSetForeground (wxSTC_STYLE_DEFAULT, *wxBLACK);
    StyleSetBackground (wxSTC_STYLE_DEFAULT, *wxWHITE);
    StyleSetForeground (wxSTC_STYLE_LINENUMBER, wxColour ("DARK GREY"));
    StyleSetBackground (wxSTC_STYLE_LINENUMBER, *wxWHITE);
    StyleSetForeground(wxSTC_STYLE_INDENTGUIDE, wxColour ("DARK GREY"));


	// margin
	m_LineNrMargin = TextWidth(wxSTC_STYLE_LINENUMBER, "_99999");
	m_FoldingMargin = 16;
    InitializePrefs (g_LanguagePrefs[0].name);

    // set visibility
    SetVisiblePolicy (wxSTC_VISIBLE_STRICT|wxSTC_VISIBLE_SLOP, 1);
    SetXCaretPolicy (wxSTC_CARET_EVEN|wxSTC_VISIBLE_STRICT|wxSTC_CARET_SLOP, 1);
    SetYCaretPolicy (wxSTC_CARET_EVEN|wxSTC_VISIBLE_STRICT|wxSTC_CARET_SLOP, 1);

    // markers
    MarkerDefine (wxSTC_MARKNUM_FOLDER,        wxSTC_MARK_DOTDOTDOT, "BLACK", "BLACK");
    MarkerDefine (wxSTC_MARKNUM_FOLDEROPEN,    wxSTC_MARK_ARROWDOWN, "BLACK", "BLACK");
    MarkerDefine (wxSTC_MARKNUM_FOLDERSUB,     wxSTC_MARK_EMPTY,     "BLACK", "BLACK");
    MarkerDefine (wxSTC_MARKNUM_FOLDEREND,     wxSTC_MARK_DOTDOTDOT, "BLACK", "WHITE");
    MarkerDefine (wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_ARROWDOWN, "BLACK", "WHITE");
    MarkerDefine (wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY,     "BLACK", "BLACK");
    MarkerDefine (wxSTC_MARKNUM_FOLDERTAIL,    wxSTC_MARK_EMPTY,     "BLACK", "BLACK");

    // annotations
    AnnotationSetVisible(wxSTC_ANNOTATION_BOXED);
 
    CmdKeyClear (wxSTC_KEY_TAB, 0); // this is done by the menu accelerator key
    SetLayoutCache (wxSTC_CACHE_PAGE);
    UsePopUp(wxSTC_POPUP_ALL);

	CallTipSetBackground(*wxYELLOW);
	CallTipSetForeground(*wxBLACK);
	SetMouseDwellTime(2000);
	int ntsb = GetTabWidth();
	SetTabWidth(4);
}

Edit::~Edit () 
{
	ConfigData *config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
	if (config)
		config->WriteFindAndReplase(&find_data);
}

//----------------------------------------------------------------------------
// common event handlers
void Edit::OnSize( wxSizeEvent& event ) {
    int x = GetClientSize().x +
            (g_CommonPrefs.lineNumberEnable? m_LineNrMargin: 0) +
            (g_CommonPrefs.foldEnable? m_FoldingMargin: 0);
    if (x > 0) SetScrollWidth (x);
    event.Skip();
}

// edit event handlers
void Edit::OnEditRedo (wxCommandEvent &WXUNUSED(event)) {
    if (!CanRedo()) return;
    Redo ();
}

void Edit::OnEditUndo (wxCommandEvent &WXUNUSED(event)) {
    if (!CanUndo()) return;
    Undo ();
}

void Edit::OnEditClear (wxCommandEvent &WXUNUSED(event)) {
    if (GetReadOnly()) return;
    Clear ();
}

void Edit::OnMouseLeave(wxMouseEvent &event)
{
	if (CallTipActive())
		CallTipCancel();
	event.Skip();
}

void Edit::OnKillFocus(wxFocusEvent& event)
{
	//if (CallTipActive())
		//CallTipCancel();
	event.Skip();
}


void Edit::OnKeyDown (wxKeyEvent &event)
{
    if (CallTipActive())
        CallTipCancel();
   
    event.Skip();
}

void Edit::OnEditCut (wxCommandEvent &WXUNUSED(event)) {
    if (GetReadOnly() || (GetSelectionEnd()-GetSelectionStart() <= 0)) return;
    Cut ();
}

void Edit::OnEditCopy (wxCommandEvent &WXUNUSED(event)) {
    if (GetSelectionEnd()-GetSelectionStart() <= 0) return;
    Copy ();
	
}

void Edit::OnEditPaste (wxCommandEvent &WXUNUSED(event)) {
    if (!CanPaste()) return;
    Paste ();
}

void Edit::OnEditIndentInc (wxCommandEvent &WXUNUSED(event)) {
    CmdKeyExecute (wxSTC_CMD_TAB);
}

void Edit::OnEditIndentRed (wxCommandEvent &WXUNUSED(event)) {
    CmdKeyExecute (wxSTC_CMD_BACKTAB);
}

void Edit::OnEditSelectAll (wxCommandEvent &WXUNUSED(event)) {
    SetSelection (0, GetTextLength ());
}

void Edit::OnEditSelectLine (wxCommandEvent &event ) 
{
	IntClientData *data = dynamic_cast<IntClientData *>(event.GetClientObject());
	
	if (data && data->GetData() >= 0)
	{
		int n = data->GetData() - 1 ;
		int lineStart = PositionFromLine(n);
		int lineEnd = PositionFromLine(n + 1);
		EnsureVisibleEnforcePolicy(n);
		SetFocus();
		//SetCurrentPos(lineStart);
		SetSelection(lineStart, lineEnd);
		
	}
}

void Edit::OnHighlightLang (wxCommandEvent &event) {
    InitializePrefs (g_LanguagePrefs [event.GetId() - myID_HIGHLIGHTFIRST].name);
}

void Edit::OnDisplayEOL (wxCommandEvent &WXUNUSED(event)) {
    SetViewEOL(!GetViewEOL());
}

void Edit::OnIndentGuide (wxCommandEvent &WXUNUSED(event)) {
    SetIndentationGuides (!GetIndentationGuides());
}

void Edit::OnLineNumber (wxCommandEvent &WXUNUSED(event)) {
    SetMarginWidth (m_LineNrID,
                    GetMarginWidth (m_LineNrID) == 0? m_LineNrMargin: 0);
}

void Edit::OnLongLineOn (wxCommandEvent &WXUNUSED(event)) {
    SetEdgeMode (GetEdgeMode() == 0? wxSTC_EDGE_LINE: wxSTC_EDGE_NONE);
}

void Edit::OnWhiteSpace (wxCommandEvent &WXUNUSED(event)) {
    SetViewWhiteSpace (GetViewWhiteSpace() == 0?
                       wxSTC_WS_VISIBLEALWAYS: wxSTC_WS_INVISIBLE);
}

void Edit::OnFoldToggle (wxCommandEvent &WXUNUSED(event)) {
    ToggleFold (GetFoldParent(GetCurrentLine()));
}

void Edit::OnSetOverType (wxCommandEvent &WXUNUSED(event)) {
    SetOvertype (!GetOvertype());
}

void Edit::OnSetReadOnly (wxCommandEvent &WXUNUSED(event)) {
    SetReadOnly (!GetReadOnly());
}

void Edit::OnWrapmodeOn (wxCommandEvent &WXUNUSED(event)) {
    SetWrapMode (GetWrapMode() == 0? wxSTC_WRAP_WORD: wxSTC_WRAP_NONE);
}

void Edit::OnUseCharset (wxCommandEvent &event) {
    int Nr;
    int charset = GetCodePage();
    switch (event.GetId()) {
        case myID_CHARSETANSI: {charset = wxSTC_CHARSET_ANSI; break;}
        case myID_CHARSETMAC: {charset = wxSTC_CHARSET_ANSI; break;}
    }
    for (Nr = 0; Nr < wxSTC_STYLE_LASTPREDEFINED; Nr++) {
        StyleSetCharacterSet (Nr, charset);
    }
    SetCodePage (charset);
}

void Edit::OnAnnotationAdd(wxCommandEvent& WXUNUSED(event))
{
    const int line = GetCurrentLine();

    wxString ann = AnnotationGetText(line);
    ann = wxGetTextFromUser
          (
            wxString::Format("Enter annotation for the line %d", line),
            "Edit annotation",
            ann,
            this
          );
    if ( ann.empty() )
        return;

    AnnotationSetText(line, ann);
    AnnotationSetStyle(line, ANNOTATION_STYLE);

    // Scintilla doesn't update the scroll width for annotations, even with
    // scroll width tracking on, so do it manually.
    const int width = GetScrollWidth();

    // NB: The following adjustments are only needed when using
    //     wxSTC_ANNOTATION_BOXED annotations style, but we apply them always
    //     in order to make things simpler and not have to redo the width
    //     calculations when the annotations visibility changes. In a real
    //     program you'd either just stick to a fixed annotations visibility or
    //     update the width when it changes.

    // Take into account the fact that the annotation is shown indented, with
    // the same indent as the line it's attached to.
    int indent = GetLineIndentation(line);

    // This is just a hack to account for the width of the box, there doesn't
    // seem to be any way to get it directly from Scintilla.
    indent += 3;

    const int widthAnn = TextWidth(ANNOTATION_STYLE, ann + wxString(indent, ' '));

    if (widthAnn > width)
        SetScrollWidth(widthAnn);
}

void Edit::OnAnnotationRemove(wxCommandEvent& WXUNUSED(event))
{
    AnnotationSetText(GetCurrentLine(), wxString());
}

void Edit::OnAnnotationClear(wxCommandEvent& WXUNUSED(event))
{
    AnnotationClearAll();
}

void Edit::OnAnnotationStyle(wxCommandEvent& event)
{
    int style = 0;
    switch (event.GetId()) {
        case myID_ANNOTATION_STYLE_HIDDEN:
            style = wxSTC_ANNOTATION_HIDDEN;
            break;

        case myID_ANNOTATION_STYLE_STANDARD:
            style = wxSTC_ANNOTATION_STANDARD;
            break;

        case myID_ANNOTATION_STYLE_BOXED:
            style = wxSTC_ANNOTATION_BOXED;
            break;
    }

    AnnotationSetVisible(style);
}

void Edit::OnChangeCase (wxCommandEvent &event) {
    switch (event.GetId()) {
        case myID_CHANGELOWER: {
            CmdKeyExecute (wxSTC_CMD_LOWERCASE);
            break;
        }
        case myID_CHANGEUPPER: {
            CmdKeyExecute (wxSTC_CMD_UPPERCASE);
            break;
        }
    }
}

void Edit::OnConvertEOL (wxCommandEvent &event) {
    int eolMode = GetEOLMode();
    switch (event.GetId()) {
        case myID_CONVERTCR: { eolMode = wxSTC_EOL_CR; break;}
        case myID_CONVERTCRLF: { eolMode = wxSTC_EOL_CRLF; break;}
        case myID_CONVERTLF: { eolMode = wxSTC_EOL_LF; break;}
    }
    ConvertEOLs (eolMode);
    SetEOLMode (eolMode);
}

void Edit::OnMultipleSelections(wxCommandEvent& WXUNUSED(event)) {
    bool isSet = GetMultipleSelection();
    SetMultipleSelection(!isSet);
}

void Edit::OnMultiPaste(wxCommandEvent& WXUNUSED(event)) {
    int pasteMode = GetMultiPaste();
    if (wxSTC_MULTIPASTE_EACH == pasteMode) {
        SetMultiPaste(wxSTC_MULTIPASTE_ONCE);
    }
    else {
        SetMultiPaste(wxSTC_MULTIPASTE_EACH);
    }
}

void Edit::OnMultipleSelectionsTyping(wxCommandEvent& WXUNUSED(event)) {
    bool isSet = GetAdditionalSelectionTyping();
    SetAdditionalSelectionTyping(!isSet);
}

void Edit::OnCustomPopup(wxCommandEvent& evt)
{
    UsePopUp(evt.IsChecked() ? wxSTC_POPUP_NEVER : wxSTC_POPUP_ALL);
}

//! misc
void Edit::OnMarginClick (wxStyledTextEvent &event) {
    if (event.GetMargin() == 2) {
        int lineClick = LineFromPosition (event.GetPosition());
        int levelClick = GetFoldLevel (lineClick);
        if ((levelClick & wxSTC_FOLDLEVELHEADERFLAG) > 0) {
            ToggleFold (lineClick);
        }
    }
}

void Edit::OnCharAdded (wxStyledTextEvent &event) {
    char chr = (char)event.GetKey();
    int currentLine = GetCurrentLine();
    // Change this if support for mac files with \r is needed
    if (chr == '\n') {
        int lineInd = 0;
        if (currentLine > 0) {
            lineInd = GetLineIndentation(currentLine - 1);
        }
        if (lineInd == 0) return;
        SetLineIndentation (currentLine, lineInd);
        GotoPos(PositionFromLine (currentLine) + lineInd);
    }
	
}

void Edit::OnChanged(wxStyledTextEvent & ) 
{
	if ((Modified() && !m_modified) || (!Modified() && m_modified) )
	{
		m_modified = Modified();
	//	wxCommandEvent *ev = new wxCommandEvent(wxEVT_MENU, myID_SELECTLINE);
//		ev->SetClientObject(dataCmd);
		//wxQueueEvent(GetParent(), event.Clone() );
		wxCommandEvent event(FILE_MODIFYED_EVENT, GetId());
		event.SetEventObject(this);
		ProcessWindowEvent(event);
	}	
}

static wxString GetWord(const wxString &in, int pos)
{
	int start,end;
	const wchar_t *s = in.wc_str() + pos;
	for (start = pos; start >= 0; start--, s--)
	{
		if ( !(::iswalpha(*s) || ::iswdigit(*s)) )
		{
			start++;
			break;
		}
	}
	if (start < 0) 
		start = 0;
	s = in.wc_str() + pos;
	for (end = pos; *s != 0; s++, end++)
	{
		if (!(::iswalpha(*s) || ::iswdigit(*s)))
		{
			end--;
			break;
		}
	}
	if (end > start)
		return in.SubString(start, end);
	else
		return wxEmptyString;

}
void Edit::OnDwellStart(wxStyledTextEvent &event)
{
	if ( !HasFocus() )
		return;

	int pos = event.GetPosition();
	wxString strWord;
	int lineN = this->LineFromPosition(pos);
	wxString str = this->GetLineText(lineN);
	if (str.empty())
		return;

	int posOnLine  = pos - PositionFromLine(lineN);
	if (posOnLine >= 0 && posOnLine < static_cast<int>(str.length()))
	{
		strWord = GetWord( str, posOnLine);
	}

	if ( !code_description || code_description->file_type() != GetFileType() )
	{
		if (GetFileType() == FILETYPE_GCMC )
			code_description.reset(new GcmcCodeDescription());
		else
			code_description.reset(new GCodeDescription());
	}

	wxString strOut = code_description->get_description(str.c_str(), strWord.c_str() );
	if (strOut.size() > 1 )
		CallTipShow(pos, strOut);
}
void Edit::OnDwellEnd(wxStyledTextEvent &event)
{
	if (CallTipActive())
		CallTipCancel();
}


//----------------------------------------------------------------------------
// private functions
wxString Edit::DeterminePrefs (const wxString &filename) 
{
	// support only GCoDe
	 LanguageInfo const* curInfo;

	wxString filenamel = filename.Lower();
   // determine language from filepatterns
    int languageNr;
    for (languageNr = 0; languageNr < g_LanguagePrefsSize; languageNr++) {
        curInfo = &g_LanguagePrefs [languageNr];
        wxString filepattern = curInfo->filepattern;
        filepattern.MakeLower();
        while (!filepattern.empty()) 
		{
            wxString cur = filepattern.BeforeFirst (';');
            if ((cur == filenamel) ||
                (cur == (filenamel.BeforeLast ('.') + ".*")) ||
                (cur == ("*." + filenamel.AfterLast ('.')))) {
                return curInfo->name;
            }
            filepattern = filepattern.AfterFirst (';');
        }
    }
	return g_LanguagePrefs[0].name; // def return first type
}


wxString Edit::DeterminePrefs(int filetype)
{
	// support only GCoDe
	LanguageInfo const* curInfo;

	
	// determine language from filepatterns
	int languageNr;
	for (languageNr = 0; languageNr < g_LanguagePrefsSize; languageNr++)
	{
		curInfo = &g_LanguagePrefs[languageNr];
		if (curInfo->file_type == filetype)
			return curInfo->name;
	}
	return g_LanguagePrefs[0].name; // def return first type
}

bool Edit::InitializePrefs (const wxString &name) {

    // initialize styles
    StyleClearAll();
    LanguageInfo const* curInfo = NULL;

    // determine language
    bool found = false;
    int languageNr;
    for (languageNr = 0; languageNr < g_LanguagePrefsSize; languageNr++) {
        curInfo = &g_LanguagePrefs [languageNr];
        if (curInfo->name == name) {
            found = true;
            break;
        }
    }
    if (!found) return false;

    // set lexer and language
    SetLexer (curInfo->lexer);
    m_language = curInfo;

    // set margin for line numbers
    SetMarginType (m_LineNrID, wxSTC_MARGIN_NUMBER);
    StyleSetForeground (wxSTC_STYLE_LINENUMBER, wxColour ("DARK GREY"));
    StyleSetBackground (wxSTC_STYLE_LINENUMBER, *wxWHITE);
    SetMarginWidth (m_LineNrID, 0); // start out not visible
	SetMarginWidth(m_LineNrID, m_LineNrMargin);

    // annotations style
    StyleSetBackground(ANNOTATION_STYLE, wxColour(244, 220, 220));
    StyleSetForeground(ANNOTATION_STYLE, *wxBLACK);
    StyleSetSizeFractional(ANNOTATION_STYLE,
            (StyleGetSizeFractional(wxSTC_STYLE_DEFAULT)*4)/5);

    // default fonts for all styles!
    int Nr;
    for (Nr = 0; Nr < wxSTC_STYLE_LASTPREDEFINED; Nr++) 
	{
        wxFont font(wxFontInfo(10).Family(wxFONTFAMILY_MODERN));
        StyleSetFont (Nr, font);
		StyleSetFontEncoding(Nr, wxFONTENCODING_CP1251);
    }

    // set common styles
    StyleSetForeground (wxSTC_STYLE_DEFAULT, wxColour ("DARK GREY"));
    StyleSetForeground (wxSTC_STYLE_INDENTGUIDE, wxColour ("DARK GREY"));

    // initialize settings
    if (g_CommonPrefs.syntaxEnable) {
        int keywordnr = 0;

        for (Nr = 0; Nr < STYLE_TYPES_COUNT; Nr++) 
		{
			int style = curInfo->styles[Nr].type;
            if (style == -1) continue;
            const StyleInfo &curType = g_StylePrefs [style];
            wxFont font(wxFontInfo(curType.fontsize)
                            .Family(wxFONTFAMILY_MODERN)
                            .FaceName(curType.fontname));
            StyleSetFont (style, font);
			StyleSetFontEncoding(style, wxFONTENCODING_CP1251);
            if (curType.foreground.length()) {
                StyleSetForeground (style, wxColour (curType.foreground));
            }
            if (curType.background.length()) {
                StyleSetBackground (style, wxColour (curType.background));
            }
            StyleSetBold (style, (curType.fontstyle & mySTC_STYLE_BOLD) > 0);
            StyleSetItalic (style, (curType.fontstyle & mySTC_STYLE_ITALIC) > 0);
            StyleSetUnderline (style, (curType.fontstyle & mySTC_STYLE_UNDERL) > 0);
            StyleSetVisible (style, (curType.fontstyle & mySTC_STYLE_HIDDEN) == 0);
            StyleSetCase (style, curType.lettercase);
            const char *pwords = curInfo->styles[Nr].words;
            if (pwords) 
			{
                SetKeyWords (keywordnr, pwords);
                keywordnr += 1;
            }
        }
    }

    // set margin as unused
    SetMarginType (m_DividerID, wxSTC_MARGIN_SYMBOL);
    SetMarginWidth (m_DividerID, 0);
    SetMarginSensitive (m_DividerID, false);

    // folding
    SetMarginType (m_FoldingID, wxSTC_MARGIN_SYMBOL);
    SetMarginMask (m_FoldingID, wxSTC_MASK_FOLDERS);
    StyleSetBackground (m_FoldingID, *wxWHITE);
    SetMarginWidth (m_FoldingID, 0);
    SetMarginSensitive (m_FoldingID, false);
    if (g_CommonPrefs.foldEnable) {
        SetMarginWidth (m_FoldingID, curInfo->folds != 0? m_FoldingMargin: 0);
        SetMarginSensitive (m_FoldingID, curInfo->folds != 0);
        SetProperty ("fold", curInfo->folds != 0? "1": "0");
        SetProperty ("fold.comment",
                     (curInfo->folds & mySTC_FOLD_COMMENT) > 0? "1": "0");
        SetProperty ("fold.compact",
                     (curInfo->folds & mySTC_FOLD_COMPACT) > 0? "1": "0");
        SetProperty ("fold.preprocessor",
                     (curInfo->folds & mySTC_FOLD_PREPROC) > 0? "1": "0");
        SetProperty ("fold.html",
                     (curInfo->folds & mySTC_FOLD_HTML) > 0? "1": "0");
        SetProperty ("fold.html.preprocessor",
                     (curInfo->folds & mySTC_FOLD_HTMLPREP) > 0? "1": "0");
        SetProperty ("fold.comment.python",
                     (curInfo->folds & mySTC_FOLD_COMMENTPY) > 0? "1": "0");
        SetProperty ("fold.quotes.python",
                     (curInfo->folds & mySTC_FOLD_QUOTESPY) > 0? "1": "0");
    }
    SetFoldFlags (wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED |
                  wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED);

    // set spaces and indentation
    SetTabWidth (4);
    SetUseTabs (false);
    SetTabIndents (true);
    SetBackSpaceUnIndents (true);
    SetIndent (g_CommonPrefs.indentEnable? 4: 0);

    // others
    SetViewEOL (g_CommonPrefs.displayEOLEnable);
    SetIndentationGuides (g_CommonPrefs.indentGuideEnable);
    SetEdgeColumn (80);
    SetEdgeMode (g_CommonPrefs.longLineOnEnable? wxSTC_EDGE_LINE: wxSTC_EDGE_NONE);
    SetViewWhiteSpace (g_CommonPrefs.whiteSpaceEnable?
                       wxSTC_WS_VISIBLEALWAYS: wxSTC_WS_INVISIBLE);
    SetOvertype (g_CommonPrefs.overTypeInitial);
    SetReadOnly (g_CommonPrefs.readOnlyInitial);
    SetWrapMode (g_CommonPrefs.wrapModeInitial?
                 wxSTC_WRAP_WORD: wxSTC_WRAP_NONE);

    return true;
}

bool Edit::NewFile (int filetype, const wxString &filename)
{
	ClearAll();
	SetSavePoint();
	EmptyUndoBuffer();
	InitializePrefs(DeterminePrefs(filetype));
	m_modified = false;
	m_newfile = true;
	m_filename = filename;
	return true;
}


bool Edit::LoadFile (const wxString &filename) {

    // load file in edit and clear undo
    if ( !filename.empty() ) 
		m_filename = filename;

    wxStyledTextCtrl::LoadFile(m_filename);

    EmptyUndoBuffer();

    // determine lexer language
    wxFileName fname (m_filename);
    InitializePrefs (DeterminePrefs (fname.GetFullName()));
	m_modified = false;
	m_newfile = false;
    return true;
}

bool Edit::SaveFile ()
{
	if (!Modified()) return true;
    return SaveFile (m_filename);
}

bool Edit::SaveFile (const wxString &filename) 
{
	EmptyUndoBuffer();
	SetSavePoint();
    bool bok =  wxStyledTextCtrl::SaveFile(filename);
	if (bok)
	{
		m_filename = filename;
	}
	m_modified = false;
	m_newfile = false;
	return  bok;

}

bool Edit::Modified () {

    // return modified state
    return (GetModify() && !GetReadOnly());
}




void Edit::PasteFile(std::wstring fname, bool toend)
{
	wxString errtext;
	try
	{
		FILE *file = _wfopen(fname.c_str(), L"r");
		if (file == NULL)
		{
			std::string errmsg("Can not open file: ");
			throw std::exception(errmsg.c_str());
		}
		fseek(file, 0, SEEK_END);
		size_t size = ftell(file);
		fseek(file, 0, SEEK_SET);
		// Load data and add terminating 0
		std::vector<char> data;
		data.resize(size + 1);
		fread(&data.front(), 1, size, file);
		data[size] = 0;
		fclose(file);
		if (toend)
			InsertTextRaw(GetTextLength(), &data.front());
		else
			AddTextRaw(&data.front());
		SelectNone();
		return;
	}
	catch (std::exception &e)
	{
		errtext = e.what();
	}
	catch (...)
	{
		errtext = _T("Can not open file");
	}

	wxMessageBox(errtext, fname.c_str(),
		wxOK | wxICON_EXCLAMATION);
}





bool Edit::DoLoadFile(const wxString& filename, int WXUNUSED(fileType))
{
#if wxUSE_FFILE || wxUSE_FILE

#if wxUSE_FFILE
	// As above, we want to read the real EOLs from the file, e.g. without
	// translating them to just LFs under Windows, so that the original CR LF
	// are preserved when it's written back.
	wxFFile file(filename, wxS("rb"));
#else
	wxFile file(filename);
#endif

	if (file.IsOpened())
	{
		wxFileOffset len = file.Length();
		wxCHECK_MSG(len >= 0, false, wxT("invalid length"));
		size_t length = wx_truncate_cast(size_t, len );
		wxCHECK_MSG((wxFileOffset)length == len, false, wxT("huge file not supported"));
		clearerr(file.fp());
		wxCharBuffer buf(length);

		// note that real length may be less than file length for text files with DOS EOLs
		// ('\r's get dropped by CRT when reading which means that we have
		// realLen = fileLen - numOfLinesInTheFile)
		length = fread(buf.data(), 1, length, file.fp());
		if (file.Error())
		{
			wxLogSysError(_("Read error on file '%s'"), filename.c_str());
			return false;
		}
		buf.data()[length] = 0;
		wxBOM bomType = wxConvAuto::DetectBOM(buf.data(), length);
		int offset = 0;
		wxMBConv *conv = wxConvCurrent;
		bool delConv = false;
		switch (bomType)
		{

			case wxBOM_UTF32BE:
				conv = new wxMBConvUTF32BE;
				delConv = true;				
				offset = 4;
				break;
			case wxBOM_UTF32LE:
				conv = new wxMBConvUTF32LE;
				delConv = true;
				offset = 4;
				break;

			case wxBOM_UTF16BE:
				conv = new wxMBConvUTF16BE;
				delConv = true;
				offset = 2;
				break;
			case wxBOM_UTF16LE:
				conv = new wxMBConvUTF16LE;
				delConv = true;
				offset = 2;
				break;
			case wxBOM_UTF8:
				offset = 3;
				conv = &wxConvUTF8;
				break;
		}

		wxString text(buf.data()+ offset, *conv);
		if (delConv)
			delete conv;
		const wxString::size_type posLF = text.find('\n');
		if (posLF != wxString::npos)
		{
			// Set EOL mode to ensure that the new lines inserted into the
			// text use the same EOLs as the existing ones.
			if (posLF > 0 && text[posLF - 1] == '\r')
				SetEOLMode(wxSTC_EOL_CRLF);
			else
				SetEOLMode(wxSTC_EOL_LF);
		}
		//else: Use the default EOL for the current platform.

		SetValue(text);
		EmptyUndoBuffer();
		SetSavePoint();

		return true;
	}
#endif // !wxUSE_FFILE && !wxUSE_FILE

	return false;
}



void Edit::OnFindNext(wxCommandEvent &WXUNUSED(event)) {
}


void Edit::OnReplaceNext(wxCommandEvent &WXUNUSED(event)) {
}


void Edit::OnReplace(wxCommandEvent& WXUNUSED(event))
{
	if (dlg_find)
	{
		wxDELETE(dlg_find);
	}
	else
	{
		dlg_find = new wxFindReplaceDialog(	this,&find_data,_("Find and replace"),	wxFR_REPLACEDIALOG);

		dlg_find->Show(true);
	}
}

void Edit::OnFind(wxCommandEvent& WXUNUSED(event))
{
	if (dlg_find)
	{
		wxDELETE(dlg_find);
	}
	else
	{
		dlg_find = new wxFindReplaceDialog(	this,&find_data, _("Find"),wxFR_NOWHOLEWORD );
		dlg_find->Show(true);
	}
}

void Edit::OnFindDialog(wxFindDialogEvent& event)
{
	wxEventType type = event.GetEventType();
	if (type == wxEVT_FIND || type == wxEVT_FIND_NEXT)
	{
		//flags & wxFR_DOWN wxFR_WHOLEWORD & wxFR_MATCHCASE
		DoFind(type, event.GetFlags(), event.GetFindString() );		
	}
	else if (type == wxEVT_FIND_REPLACE ||
		type == wxEVT_FIND_REPLACE_ALL)
	{
		DoReplace(type, event.GetFlags(), event.GetFindString(), event.GetReplaceString() );		
	}
	else if (type == wxEVT_FIND_CLOSE)
	{
		wxFindReplaceDialog *dlg = event.GetDialog();
		if (dlg == dlg_find)
			dlg_find = NULL;
		dlg->Destroy();
	}
	else
	{
		wxLogError("Unknown find dialog event!");
	}
}




void Edit::OnBraceMatch(wxCommandEvent &WXUNUSED(event)) 
{
	int min = GetCurrentPos();
	int max = BraceMatch(min);
	if (max > (min + 1)) {
		BraceHighlight(min + 1, max);
		SetSelection(min + 1, max);
	}
	else {
		BraceBadLight(min);
	}
}

void Edit::OnGoto(wxCommandEvent &WXUNUSED(event)) 
{
}


void Edit::DoFind(wxEventType type, int flag, const wxString &strfind)
{
	int pos = GetCurrentPos();	
	
	int flag_cts = 0;
	if (flag & wxFR_WHOLEWORD) flag_cts |= wxSTC_FIND_WHOLEWORD;
	if (flag & wxFR_MATCHCASE) flag_cts |= wxSTC_FIND_MATCHCASE;

	if (!(flag & wxFR_DOWN))
	{
		pos -= strfind.Length();
		if (pos < 0) pos = 0;
	}
	SetSelection(pos, pos);
	SearchAnchor();
	if (flag & wxFR_DOWN)
		pos = SearchNext(flag, strfind);
	else
		pos = SearchPrev(flag, strfind);
	if (pos != wxSTC_INVALID_POSITION)
	{
		SetSelection(pos, pos + strfind.Length());
		EnsureCaretVisible();
	}
	else
	{
		wxMessageBox(wxString::Format(_("\"%s\" Not found"), strfind), _("Find result"), wxOK | wxICON_INFORMATION, this);
	}
}

void Edit::DoReplace(wxEventType type, int flag, const wxString &strfind, const wxString &strReplace)
{
	int pos = GetCurrentPos();
	int flag_cts = 0;
	if (flag & wxFR_WHOLEWORD) flag_cts |= wxSTC_FIND_WHOLEWORD;
	if (flag & wxFR_MATCHCASE) flag_cts |= wxSTC_FIND_MATCHCASE;
	bool done = false;

	if (type == wxEVT_FIND_REPLACE_ALL)
		pos = 0;

	do
	{	
		if (GetSelectionEnd() == pos)
			pos -= strfind.Length();

		if (pos < 0) 
			pos = 0;

		SetSelection(pos, pos);
		SearchAnchor();
		pos = SearchNext(flag, strfind);
		if (pos != wxSTC_INVALID_POSITION)
		{
			SetTargetRange(pos, pos + strfind.Length());
			ReplaceTarget(strReplace);
			if (type != wxEVT_FIND_REPLACE_ALL) // search the next
			{
				//SetSelection(pos, pos);

				SetSelection(pos, strReplace.Length() );
				SearchAnchor();
				pos = SearchNext(flag, strfind);
				if (pos != wxSTC_INVALID_POSITION)
				{
					SetSelection(pos, pos + strfind.Length());
					EnsureCaretVisible();
				}
			}		
			done = true;
		}
	} while ((type == wxEVT_FIND_REPLACE_ALL) && (pos != wxSTC_INVALID_POSITION));
	
	if ( !done )
	{
		wxMessageBox(wxString::Format(_("\"%s\" Not found"), strfind), _("Find result"), wxOK | wxICON_INFORMATION, this);
	}
	else if (type == wxEVT_FIND_REPLACE_ALL)
	{
		SetEmptySelection(0);
	}

	
}