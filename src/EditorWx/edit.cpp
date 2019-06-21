#include "wx/wx.h"
#include "wx/filename.h" // filename support

//! application headers
#include "defsext.h"     // additional definitions
#include "edit.h"        // edit module
#include "codedescription.h"
#include "configdata.h"
#include "prefs.h"
#include "app.h"
#include "appframe.h"

//#include "..\..\src\stc\ScintillaWX.h"


#if wxUSE_FFILE
#include "wx/ffile.h"
#elif wxUSE_FILE
#include "wx/file.h"
#endif


//----------------------------------------------------------------------------
// Edit
//----------------------------------------------------------------------------

wxDEFINE_EVENT(FILE_MODIFYED_EVENT, wxCommandEvent);

wxBEGIN_EVENT_TABLE(Edit, wxStyledTextCtrl)	
	EVT_CONTEXT_MENU(Edit::OnContextMenu)
	EVT_MENU(ID_INCLUDE_FILE_OPEN, Edit::OnIncludeOpen)
	// edit
	EVT_MENU(wxID_CLEAR, Edit::OnEditClear)
	EVT_MENU(wxID_CUT, Edit::OnEditCut)
	EVT_MENU(wxID_COPY, Edit::OnEditCopy)
	EVT_MENU(wxID_PASTE, Edit::OnEditPaste)
	EVT_MENU(wxID_SELECTALL, Edit::OnEditSelectAll)
	EVT_MENU(ID_SELECTLINE, Edit::OnEditSelectLine)
	EVT_MENU(wxID_REDO, Edit::OnEditRedo)
	EVT_MENU(wxID_UNDO, Edit::OnEditUndo)
	EVT_MENU(ID_INDENTINC, Edit::OnEditIndentInc)
	EVT_MENU(ID_INDENTRED, Edit::OnEditIndentRed)

	// find
	EVT_MENU(wxID_FIND, Edit::OnFind)
	EVT_MENU(ID_FINDNEXT, Edit::OnFindNext)
	EVT_MENU(ID_REPLACE, Edit::OnReplace)
	EVT_MENU(ID_REPLACENEXT, Edit::OnReplaceNext)
	EVT_MENU(ID_BRACEMATCH, Edit::OnBraceMatch)
	EVT_MENU(ID_GOTO, Edit::OnGoto)
	
	EVT_FIND(wxID_ANY, Edit::OnFindDialog)
	EVT_FIND_NEXT(wxID_ANY, Edit::OnFindDialog)
	EVT_FIND_REPLACE(wxID_ANY, Edit::OnFindDialog)
	EVT_FIND_REPLACE_ALL(wxID_ANY, Edit::OnFindDialog)
	EVT_FIND_CLOSE(wxID_ANY, Edit::OnFindDialog)


	// view
	EVT_MENU(ID_DISPLAYEOL, Edit::OnDisplayEOL)
	EVT_MENU(ID_INDENTGUIDE, Edit::OnIndentGuide)
	EVT_MENU(ID_LINENUMBER, Edit::OnLineNumber)
	EVT_MENU(ID_LONGLINEON, Edit::OnLongLineOn)
	EVT_MENU(ID_WHITESPACE, Edit::OnWhiteSpace)
	EVT_MENU(ID_FOLDTOGGLE, Edit::OnFoldToggle)
	EVT_MENU(ID_OVERTYPE, Edit::OnSetOverType)
	EVT_MENU(ID_READONLY, Edit::OnSetReadOnly)
	EVT_MENU(ID_WRAPMODEON, Edit::OnWrapmodeOn)
	EVT_MENU(ID_CHARSETANSI, Edit::OnUseCharset)
	EVT_MENU(ID_CHARSETMAC, Edit::OnUseCharset)
	// extra
	EVT_MENU(ID_CHANGELOWER, Edit::OnChangeCase)
	EVT_MENU(ID_CHANGEUPPER, Edit::OnChangeCase)
	EVT_MENU(ID_CONVERTCR, Edit::OnConvertEOL)
	EVT_MENU(ID_CONVERTCRLF, Edit::OnConvertEOL)
	EVT_MENU(ID_CONVERTLF, Edit::OnConvertEOL)
	EVT_MENU(ID_MULTIPLE_SELECTIONS, Edit::OnMultipleSelections)
	EVT_MENU(ID_MULTI_PASTE, Edit::OnMultiPaste)
	EVT_MENU(ID_MULTIPLE_SELECTIONS_TYPING, Edit::OnMultipleSelectionsTyping)
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



Edit::Edit(wxWindow *parent, wxWindowID id)
	: wxStyledTextCtrl()
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
	Create(parent, id);
	UpdatePreferences();

}

bool Edit::Create(wxWindow *parent, wxWindowID id)
{

	return wxStyledTextCtrl::Create(parent, id, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxHSCROLL | wxNO_BORDER | wxCLIP_CHILDREN);
}


Edit::~Edit () 
{
	ConfigData *config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
	if (config)
		config->WriteFindAndReplase(&find_data);
}

//----------------------------------------------------------------------------


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
        case ID_CHARSETANSI: {charset = wxSTC_CHARSET_ANSI; break;}
        case ID_CHARSETMAC: {charset = wxSTC_CHARSET_ANSI; break;}
    }
    for (Nr = 0; Nr < wxSTC_STYLE_LASTPREDEFINED; Nr++) {
        StyleSetCharacterSet (Nr, charset);
    }
    SetCodePage (charset);
}

void Edit::OnChangeCase (wxCommandEvent &event) 
{
    switch (event.GetId()) 
	{
        case ID_CHANGELOWER: 
	    {
            CmdKeyExecute (wxSTC_CMD_LOWERCASE);
            break;
        }
        case ID_CHANGEUPPER: {
            CmdKeyExecute (wxSTC_CMD_UPPERCASE);
            break;
        }
    }
}

void Edit::OnConvertEOL (wxCommandEvent &event) {
    int eolMode = GetEOLMode();
    switch (event.GetId()) {
        case ID_CONVERTCR: { eolMode = wxSTC_EOL_CR; break;}
        case ID_CONVERTCRLF: { eolMode = wxSTC_EOL_CRLF; break;}
        case ID_CONVERTLF: { eolMode = wxSTC_EOL_LF; break;}
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
		wxCommandEvent event(FILE_MODIFYED_EVENT, GetId());
		event.SetEventObject(this);
		wxGetApp().GetFrame()->ProcessWindowEvent(event);
		//wxQueueEvent(&wxGetApp(), event.Clone());
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

void Edit::UpdatePreferences()
{

	ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	const CommonInfo &common_prefs = Preferences::Get()->Common();

	// default font for all styles
	SetViewEOL(common_prefs.displayEOLEnable);
	SetIndentationGuides(common_prefs.indentGuideEnable);
	SetEdgeMode(common_prefs.longLineOnEnable ?
		wxSTC_EDGE_LINE : wxSTC_EDGE_NONE);
	SetViewWhiteSpace(common_prefs.whiteSpaceEnable ?
		wxSTC_WS_VISIBLEALWAYS : wxSTC_WS_INVISIBLE);
	SetOvertype(common_prefs.overTypeInitial);
	SetReadOnly(common_prefs.readOnlyInitial);
	SetWrapMode(common_prefs.wrapModeInitial ?
		wxSTC_WRAP_WORD : wxSTC_WRAP_NONE);
	wxFont font(wxFontInfo(10).Family(wxFONTFAMILY_MODERN));
	StyleSetFont(wxSTC_STYLE_DEFAULT, font);
	
	StyleSetForeground(wxSTC_STYLE_DEFAULT, clrs->Get(ColourScheme::WINDOW_TEXT));
	StyleSetBackground(wxSTC_STYLE_DEFAULT, clrs->Get(ColourScheme::WINDOW));
	

	StyleSetForeground(wxSTC_STYLE_LINENUMBER, clrs->Get(ColourScheme::LINENUMBER_TEXT));
	StyleSetBackground(wxSTC_STYLE_LINENUMBER, clrs->Get(ColourScheme::LINENUMBER));

	StyleSetForeground(wxSTC_STYLE_INDENTGUIDE, clrs->Get(ColourScheme::LINENUMBER_TEXT));
	SetEdgeColumn(80);


	// margin
	m_LineNrMargin = TextWidth(wxSTC_STYLE_LINENUMBER, "_99999");
	m_FoldingMargin = 16;

	// set visibility
	SetVisiblePolicy(wxSTC_VISIBLE_STRICT | wxSTC_VISIBLE_SLOP, 1);
	SetXCaretPolicy(wxSTC_CARET_EVEN | wxSTC_VISIBLE_STRICT | wxSTC_CARET_SLOP, 1);
	SetYCaretPolicy(wxSTC_CARET_EVEN | wxSTC_VISIBLE_STRICT | wxSTC_CARET_SLOP, 1);

	// markers
	MarkerDefine(wxSTC_MARKNUM_FOLDER, wxSTC_MARK_DOTDOTDOT, "BLACK", "BLACK");
	MarkerDefine(wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_ARROWDOWN, "BLACK", "BLACK");
	MarkerDefine(wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY, "BLACK", "BLACK");
	MarkerDefine(wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_DOTDOTDOT, "BLACK", "WHITE");
	MarkerDefine(wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_ARROWDOWN, "BLACK", "WHITE");
	MarkerDefine(wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY, "BLACK", "BLACK");
	MarkerDefine(wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY, "BLACK", "BLACK");

	// annotations
	AnnotationSetVisible(wxSTC_ANNOTATION_BOXED);

	CmdKeyClear(wxSTC_KEY_TAB, 0); // this is done by the menu accelerator key
	SetLayoutCache(wxSTC_CACHE_PAGE);
	UsePopUp(wxSTC_POPUP_NEVER); //wxSTC_POPUP_ALL

	CallTipSetBackground(clrs->Get(ColourScheme::CALLTIP));
	CallTipSetForeground(clrs->Get(ColourScheme::CALLTIP_TEXT));
	SetCaretForeground(clrs->Get(ColourScheme::WINDOW_TEXT));

	SetMouseDwellTime(2000);

	SetUseHorizontalScrollBar(common_prefs.visibleHSB);
	
	// set spaces and indentation
	SetUseTabs(false);
	SetTabIndents(true);
	SetTabWidth(common_prefs.tabWidth);
	SetBackSpaceUnIndents(true);
	SetIndent(common_prefs.indentEnable ? common_prefs.tabWidth : 0);
	if (m_language)
	{
		// we need use FindByType to reinit lanfuage
		InitializePrefs(Preferences::Get()->FindByType(m_language->GetFileType()));
	}

}


bool Edit::InitializePrefs (const LanguageInfo * language)
{

	ColourScheme *clrs = Preferences::Get()->GetColorScheme();

    // initialize styles
    StyleClearAll();
	const CommonInfo &common_prefs = Preferences::Get()->Common();
	m_language = language;
    // set lexer and language
    SetLexer (m_language->Lexer());
    

    // set margin for line numbers
    SetMarginType (m_LineNrID, wxSTC_MARGIN_NUMBER);

	StyleSetForeground(wxSTC_STYLE_LINENUMBER, clrs->Get(ColourScheme::LINENUMBER_TEXT));
	StyleSetBackground(wxSTC_STYLE_LINENUMBER, clrs->Get(ColourScheme::LINENUMBER));


    SetMarginWidth (m_LineNrID, 0); // start out not visible
	if (common_prefs.lineNumberEnable )
		SetMarginWidth(m_LineNrID, m_LineNrMargin);

    // default fonts for all styles!

    int Nr;
    for (Nr = 0; Nr < wxSTC_STYLE_LASTPREDEFINED; Nr++) 
	{
        wxFont font(wxFontInfo(10).Family(wxFONTFAMILY_DEFAULT));
        StyleSetFont (Nr, font);
		StyleSetFontEncoding(Nr, wxFONTENCODING_CP1251);
    }

    // set common styles
    StyleSetForeground (wxSTC_STYLE_DEFAULT, clrs->Get(ColourScheme::WINDOW_TEXT));
    StyleSetForeground (wxSTC_STYLE_INDENTGUIDE, clrs->Get(ColourScheme::WINDOW_TEXT));
	StyleSetBackground(wxSTC_STYLE_DEFAULT, clrs->Get(ColourScheme::WINDOW));
	StyleSetBackground(wxSTC_STYLE_INDENTGUIDE, clrs->Get(ColourScheme::WINDOW));

#if 1
    // initialize settings
    if (common_prefs.syntaxEnable) 
	{
        int keywordnr = 0;
		const StylesInfos &styles = m_language->Styles();
		for (auto it = styles.begin(); it != styles.end(); ++it)
		{
			int style = it->style_Id;
            if (style == -1) continue;
			const StyleInfo &curType = *it;
            wxFont font(wxFontInfo(curType.fontsize)
                            .Family(wxFONTFAMILY_DEFAULT)
                            .FaceName(curType.fontname));
            StyleSetFont (style, font);
			StyleSetFontEncoding(style, wxFONTENCODING_CP1251);
            if (!curType.foreground.IsEmpty()) {
                StyleSetForeground (style, wxColour (curType.foreground));
            }
            if (!curType.background.IsEmpty()) {
                StyleSetBackground (style, wxColour (curType.background));
            }
            StyleSetBold (style, curType.bold);
            StyleSetItalic (style, curType.italic);
            StyleSetUnderline (style, false);
            StyleSetVisible (style, true);
            StyleSetCase (style, curType.lettercase);
            if (it->words)
			{
                SetKeyWords (keywordnr, it->words);
                keywordnr += 1;
            }
        }
    }

#endif
    // set margin as unused
    SetMarginType (m_DividerID, wxSTC_MARGIN_SYMBOL);
    SetMarginWidth (m_DividerID, 0);
    SetMarginSensitive (m_DividerID, false);

	/*
    // folding
    SetMarginType (m_FoldingID, wxSTC_MARGIN_SYMBOL);
    SetMarginMask (m_FoldingID, wxSTC_MASK_FOLDERS);
    StyleSetBackground (m_FoldingID, *wxWHITE);
    SetMarginWidth (m_FoldingID, 0);
    SetMarginSensitive (m_FoldingID, false);
    if (common_prefs.foldEnable) 
	{
        SetMarginWidth (m_FoldingID, m_language->Fold() != 0 ? m_FoldingMargin: 0);
        SetMarginSensitive (m_FoldingID, m_language->Fold() != 0);
        SetProperty ("fold", m_language->Fold() != 0 ? "1": "0");
        SetProperty ("fold.comment",
                     (m_language->Fold() & mySTC_FOLD_COMMENT) > 0? "1": "0");
        SetProperty ("fold.compact",
                     (m_language->Fold() & mySTC_FOLD_COMPACT) > 0? "1": "0");
        SetProperty ("fold.preprocessor",
                     (m_language->Fold() & mySTC_FOLD_PREPROC) > 0? "1": "0");
        SetProperty ("fold.html",
                     (m_language->Fold() & mySTC_FOLD_HTML) > 0? "1": "0");
        SetProperty ("fold.html.preprocessor",
                     (m_language->Fold() & mySTC_FOLD_HTMLPREP) > 0? "1": "0");
        SetProperty ("fold.comment.python",
                     (m_language->Fold() & mySTC_FOLD_COMMENTPY) > 0? "1": "0");
        SetProperty ("fold.quotes.python",
                     (m_language->Fold() & mySTC_FOLD_QUOTESPY) > 0? "1": "0");
    }
    SetFoldFlags (wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED |
                  wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED);

   */
    return true;
}

bool Edit::NewFile (int filetype, const wxString &filename)
{
	ClearAll();
	SetSavePoint();
	EmptyUndoBuffer();	
	InitializePrefs(Preferences::Get()->FindByType(filetype) );
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
	SelectNone();
    // determine lexer language
    wxFileName fname (m_filename);
    InitializePrefs ( Preferences::Get()->FindByFileName(fname.GetFullName()));
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


void Edit::OnIncludeOpen(wxCommandEvent& event)
{
	wxString incl_file = GetGcmcIncludeFileName();
	if (!incl_file.empty())
	{		
		wxCommandEvent event(FILE_OPEN_EVENT, GetId());
		event.SetString(incl_file);
		event.SetEventObject(this);
		ProcessWindowEvent(event);
	}
}

wxString Edit::GetGcmcIncludeFileName()
{
	int pos = GetCurrentPos();	
	wxString strWord;
	int lineN = LineFromPosition(pos);
	wxString str = GetLineText(lineN);
	if (str.empty())
		return str;
	int n =  0;
	//include("involute-gear.inc.gcmc");
	if ((n = str.Find(L"include")) != wxNOT_FOUND)
	{
		str = str.AfterFirst('\"');
		str = str.BeforeFirst('\"');
		return str;
	}
	return wxEmptyString;
}

void Edit::OnContextMenu(wxContextMenuEvent& event)
{
//	wxPoint clientpt = event.GetPosition();
//	wxPoint screenpt = ClientToScreen(clientpt);
	wxMenu menu(wxEmptyString);

	wxString incl_file = GetGcmcIncludeFileName();
	if (!incl_file.empty())
	{
		menu.Append(ID_INCLUDE_FILE_OPEN, wxString::Format(_("Open file: \"%s\""), incl_file));
	}
	menu.AppendSeparator();
	menu.Append(wxID_UNDO, _("Undo"));
	menu.AppendSeparator();
	menu.Append(wxID_CUT, _("Cut"));
	menu.Append(wxID_COPY, _("Copy"));
	menu.Append(wxID_PASTE, _("Paste"));
	menu.AppendSeparator();
	menu.Append(wxID_SELECTALL, "Select All");

	PopupMenu(&menu, ScreenToClient(event.GetPosition()) );
	event.Skip();
}