 
#ifndef _EDIT_H_
#define _EDIT_H_

#include <memory>
#include <wx/fdrepdlg.h>

//----------------------------------------------------------------------------
// information
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

//! wxWidgets headers

//! wxWidgets/contrib headers
#include "wx/stc/stc.h"  // styled text control

//! application headers
#include "prefs.h"       // preferences


//============================================================================
// declarations
//============================================================================

class ICodeDescription;
class FlatTipWindow;
//----------------------------------------------------------------------------
//! Edit
class Edit: public wxStyledTextCtrl {
    friend class EditProperties;
    friend class EditPrint;
	friend class FlatTipWindow;

public:
    //! constructor
	Edit(wxWindow *parent, wxWindowID id);
    ~Edit ();
	bool Create(wxWindow *parent, wxWindowID id);

    // event handlers
    // common
	void OnContextMenu(wxContextMenuEvent& event);
	
    // edit
    void OnEditRedo (wxCommandEvent &event);
    void OnEditUndo (wxCommandEvent &event);
    void OnEditClear (wxCommandEvent &event);
    void OnEditCut (wxCommandEvent &event);
    void OnEditCopy (wxCommandEvent &event);
    void OnEditPaste (wxCommandEvent &event);
	void OnIncludeOpen(wxCommandEvent& event);
    // find
    void OnFind (wxCommandEvent &event);
    void OnFindNext (wxCommandEvent &event);
    void OnReplace (wxCommandEvent &event);
    void OnReplaceNext (wxCommandEvent &event);
    void OnBraceMatch (wxCommandEvent &event);
    void OnGoto (wxCommandEvent &event);
	void OnFindDialog(wxFindDialogEvent& event);

    void OnEditIndentInc (wxCommandEvent &event);
    void OnEditIndentRed (wxCommandEvent &event);
    void OnEditSelectAll (wxCommandEvent &event);
    void OnEditSelectLine (wxCommandEvent &event);
	    //! view

    void OnDisplayEOL (wxCommandEvent &event);
    void OnIndentGuide (wxCommandEvent &event);
    void OnLineNumber (wxCommandEvent &event);
    void OnLongLineOn (wxCommandEvent &event);
    void OnWhiteSpace (wxCommandEvent &event);
    void OnFoldToggle (wxCommandEvent &event);
    void OnSetOverType (wxCommandEvent &event);
    void OnSetReadOnly (wxCommandEvent &event);
    void OnWrapmodeOn (wxCommandEvent &event);
    void OnUseCharset (wxCommandEvent &event);
    //! extra
    void OnChangeCase (wxCommandEvent &event);
    void OnConvertEOL (wxCommandEvent &event);
    void OnMultipleSelections(wxCommandEvent& event);
    void OnMultiPaste(wxCommandEvent& event);
    void OnMultipleSelectionsTyping(wxCommandEvent& event);

    // stc
    void OnMarginClick (wxStyledTextEvent &event);
    void OnCharAdded  (wxStyledTextEvent &event);
	void OnChanged(wxStyledTextEvent &event);
	void OnDwellStart(wxStyledTextEvent &event);
	void OnDwellEnd(wxStyledTextEvent &event);
    void OnKeyDown(wxKeyEvent &event);
	void OnKillFocus(wxFocusEvent &event);
	void OnMouseLeave(wxMouseEvent &event);

    //! language/lexer
	int GetFileType() {	return ((m_language != 0 ) ? m_language->GetFileType() : FILETYPE_UNKNOW); }

    //! load/save file
	bool NewFile(int filetype, const wxString &filename);
    bool LoadFile (const wxString &filename);
    bool SaveFile ();
    bool SaveFile (const wxString &filename);
    bool Modified ();
    wxString GetFileName () {return m_filename;}
	void SetFileName(const wxString &filename) { m_filename = filename; }
	void PasteFile(const wxString &fname, bool toend = false);
	bool IsNew() { return m_newfile; }

	//find
	void DoFind(wxEventType type, int flag, const wxString &strfind);
	void DoReplace(wxEventType type, int flag, const wxString &strfind, const wxString &strReplace);
	void UpdatePreferences();

	void DoSelectLine(int line);
	wxSize DoGetBestSize() const;

private:
	bool InitializePrefs(const LanguageInfo * language);	
	wxString GetGcmcIncludeFileName();
	bool DoLoadFile(const wxString& filename, int WXUNUSED(fileType));
	bool FlatTipActive() { return (m_ftooltip != 0); }
	void FlatTipCancel();

private:
    // file
    wxString m_filename;

    // language properties
    const LanguageInfo * m_language;

    // margin variables
    int m_LineNrID;
    int m_LineNrMargin;
    int m_FoldingID;
    int m_FoldingMargin;
    int m_DividerID;
	std::shared_ptr<ICodeDescription> code_description;
	//find
	wxFindReplaceDialog *dlg_find;
	wxFindReplaceData find_data;
	bool m_modified;
	bool m_newfile;
	FlatTipWindow *m_ftooltip;
    wxDECLARE_EVENT_TABLE();
};

#endif // _EDIT_H_
