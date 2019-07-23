#pragma once
#include "wx/htmllbox.h"
#include "defsext.h"




class FlatScrollBar;
typedef wxWindowWithItems<wxVListBox, wxItemContainer> BaseLogClass;

class LogWindow : public BaseLogClass
{
public:
	LogWindow(wxEvtHandler *_handler);
	LogWindow(wxWindow *parent, wxEvtHandler *_handler, wxWindowID id);
	~LogWindow();
	void Append(MsgStatusLevel lvl, const wchar_t *str, int linen = 0, bool update = false);
	void SetVScrollBar(wxScrollBar *bar);
	void SetHScrollBar(wxScrollBar *bar);

	void OnLboxSelect(wxCommandEvent& event);
	void OnLboxDClick(wxCommandEvent& event);
	void OnKeyDown(wxKeyEvent &event);
	void OnScroll(wxScrollEvent& evt);
	void Clear();

	virtual bool CanScroll(int orient) const { return true; }
	// configure the window scrollbars
	virtual void SetScrollbar(int orient,	int pos,	int thumbvisible,	int range,	bool refresh = true) ;
	virtual void SetScrollPos(int orient, int pos, bool refresh = true);
	virtual int GetScrollPos(int orient) const ;
	virtual int GetScrollThumb(int orient) const;
	virtual int GetScrollRange(int orient) const;
	// scroll window to the specified position
	virtual void ScrollWindow(int dx, int dy,	const wxRect* rect = NULL);


	// these must be overloaded otherwise the compiler will complain
	// about  wxItemContainerImmutable::[G|S]etSelection being pure virtuals...
	void SetSelection(int n)                 {	wxVListBox::SetSelection(n); }
	int GetSelection() const wxOVERRIDE 	 {	return wxVListBox::GetSelection(); 	}
	unsigned int GetCount() const wxOVERRIDE {	return m_items.GetCount();	}
	wxString GetString(unsigned int n) const wxOVERRIDE;
	// override default unoptimized wxItemContainer::GetStrings() function
	wxArrayString GetStrings() const	{	return m_items; 	}
	void SetString(unsigned int n, const wxString& s) wxOVERRIDE;
	// resolve ambiguity between wxItemContainer and wxVListBox versions
	
protected:
	virtual int DoInsertItems(const wxArrayStringsAdapter & items,
		unsigned int pos,
		void **clientData, wxClientDataType type) wxOVERRIDE;
	virtual void DoSetItemClientData(unsigned int n, void *clientData) wxOVERRIDE 	{	m_clientData[n] = clientData;	}
	virtual void *DoGetItemClientData(unsigned int n) const wxOVERRIDE	{		return m_clientData[n]; 	}
	// wxItemContainer methods
	virtual void DoClear() wxOVERRIDE;
	virtual void DoDeleteOneItem(unsigned int n) wxOVERRIDE;
	void UpdateCount();
protected:
	virtual void OnDrawItem(wxDC& dc, const wxRect& rect, size_t n) const;
	virtual wxCoord OnMeasureItem(size_t n) const;

private:
	void DoSinchronize();
private:
	wxScrollBar *m_vScrollBar;
	wxScrollBar *m_hScrollBar;
	wxEvtHandler *handler;
	wxArrayString   m_items;
	wxArrayPtrVoid  m_clientData;

	wxDECLARE_EVENT_TABLE();
};

