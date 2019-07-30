
#pragma once
#define USE_GENERIC_TREECTRL 1

#include "wx/treectrl.h"


#if USE_GENERIC_TREECTRL
#include "wx/generic/treectlg.h"
#ifndef wxTreeCtrl
#define wxTreeCtrl wxGenericTreeCtrl
#define sm_classwxTreeCtrl sm_classwxGenericTreeCtrl
#endif
#endif



//C:\wxWidgets\include\wx\treectrl.h
//#include "C:/wxWidgets/include/wx/generic/treectlg.h"
#include "wx/fswatcher.h"
#include "wx/dnd.h"

// Define a new application type



class DirTreeItemData : public wxTreeItemData
{
public:
	DirTreeItemData(const wxString& desc, bool isfile = false) : m_path(desc), m_isfile(isfile)  { }
    wxString const& GetPath() const { return m_path; }
	void SetPath(const wxString &path) { m_path = path; }
	bool isFile() { return m_isfile; }

private:
    wxString m_path;
	bool m_isfile;
};

class DirTreeActor;


class DirTreeCtrl : public wxTreeCtrl
{
	friend class DnDFile;
	friend class DirTreeActor;
	friend class DirPane;
public:
    enum
    {
        TreeCtrlIcon_File,
        TreeCtrlIcon_FileSelected,
        TreeCtrlIcon_Folder,
        TreeCtrlIcon_FolderSelected,
        TreeCtrlIcon_FolderOpened
    };
	DirTreeCtrl() { m_alternateImages = false; m_alternateStates = false; }
    DirTreeCtrl(wxWindow *parent, const wxWindowID id = wxID_ANY );
	bool Create(wxWindow *parent, wxWindowID id );
	virtual ~DirTreeCtrl();
	// commands
	void OnFileOpen(wxCommandEvent &event);
	void OnFileReneme(wxCommandEvent &event);
	void OnFileDelete(wxCommandEvent &event);
	void OnFolderOpen(wxCommandEvent &event);
	void OnFileNew(wxCommandEvent &event);
	void OnFolderRemoveFromPoroject(wxCommandEvent &event);
// events
    void OnBeginDrag(wxTreeEvent& event);
    void OnBeginRDrag(wxTreeEvent& event);
    void OnEndDrag(wxTreeEvent& event);
    void OnBeginLabelEdit(wxTreeEvent& event);
    void OnEndLabelEdit(wxTreeEvent& event);
    void OnDeleteItem(wxTreeEvent& event);
    void OnContextMenu(wxContextMenuEvent& event);
    void OnItemMenu(wxTreeEvent& event);
    void OnGetInfo(wxTreeEvent& event);
    void OnSetInfo(wxTreeEvent& event);
    void OnItemExpanded(wxTreeEvent& event);
    void OnItemExpanding(wxTreeEvent& event);
    void OnItemCollapsed(wxTreeEvent& event);
    void OnItemCollapsing(wxTreeEvent& event);
    void OnSelChanged(wxTreeEvent& event);
    void OnSelChanging(wxTreeEvent& event);
    void OnTreeKeyDown(wxTreeEvent& event);
    void OnItemActivated(wxTreeEvent& event);
    void OnItemRClick(wxTreeEvent& event);
	void OnScroll(wxScrollEvent& evt);

    void OnRMouseDown(wxMouseEvent& event);
    void OnRMouseUp(wxMouseEvent& event);
    void OnRMouseDClick(wxMouseEvent& event);
	void OnFileSystemEvent(wxFileSystemWatcherEvent& event);
	void SetWatcher(wxFileSystemWatcher *watcher);
	wxSize DoGetBestSize() const;

public:
	void SetVScrollBar(wxScrollBar *bar);
	void SetHScrollBar(wxScrollBar *bar);

	virtual bool CanScroll(int orient) const { return true; }
	// configure the window scrollbars
	virtual void SetScrollbar(int orient, int pos, int thumbvisible, int range, bool refresh = true);
	virtual void SetScrollPos(int orient, int pos, bool refresh = true);
	virtual int GetScrollPos(int orient) const;
	virtual int GetScrollThumb(int orient) const;
	virtual int GetScrollRange(int orient) const;
	// scroll window to the specified position
	virtual void ScrollWindow(int dx, int dy, const wxRect* rect = NULL);



private:
	wxTreeItemId FindItemsRecursively(const wxTreeItemId& idParent, const wxString &path);
	bool ForEachItemRecursively(const wxTreeItemId& idParent, const wxString &path, DirTreeActor *pactor);
    wxTreeItemId GetLastTreeITem() const;
    void CreateImageList();
    void AddPath(const wxString &path);
    void DoSortChildren(const wxTreeItemId& item, bool reverse = false)
        { m_reverseSort = reverse; wxGenericTreeCtrl::SortChildren(item); }

    void DoToggleIcon(const wxTreeItemId& item);
	void UpdateThemeColor();
	void UpdateThemeColor(const wxTreeItemId& idParent, const wxColor &color);
	bool IsPathInTree(const wxString &path, bool root = true);

protected:
    virtual int OnCompareItems(const wxTreeItemId& i1, const wxTreeItemId& i2) wxOVERRIDE;
	void OpenFile(DirTreeItemData *item);



private:
    // Find the very last item in the tree.
    void AddItemsRecursively( const wxTreeItemId& idParent, const wxString &path);

    void DoResetBrokenStateImages(const wxTreeItemId& idParent,
                                  wxTreeItemIdValue cookie, int state);

    void LogEvent(const wxString& name, const wxTreeEvent& event);

    bool         m_reverseSort;             // flag for OnCompareItems
    wxTreeItemId m_draggedItem;             // item being dragged right now
    bool         m_alternateImages;
    bool         m_alternateStates;
	wxTreeItemId m_rootId;
	wxFileSystemWatcher *m_watcher;
	wxScrollBar *m_vScrollBar;
	wxScrollBar *m_hScrollBar;

    // NB: due to an ugly wxMSW hack you _must_ use wxDECLARE_DYNAMIC_CLASS();
    //     if you want your overloaded OnCompareItems() to be called.
    //     OTOH, if you don't want it you may omit the next line - this will
    //     make default (alphabetical) sorting much faster under wxMSW.
    wxDECLARE_DYNAMIC_CLASS(DirTreeCtrl);
    wxDECLARE_EVENT_TABLE();
};

class DnDFile : public wxFileDropTarget
{
public:
	DnDFile(DirTreeCtrl *pOwner) : m_pOwner(pOwner) {  }

	virtual bool OnDropFiles(wxCoord x, wxCoord y,
		const wxArrayString& filenames) wxOVERRIDE;

private:
	DirTreeCtrl *m_pOwner;
};

class  DirPane : public wxPanel
{
public:
	DirPane(wxWindow *parent);
	~DirPane();
	void SetWatcher(wxFileSystemWatcher *watcher) { m_ptree->SetWatcher(watcher); }
	void OnAddButton(wxCommandEvent &ev);
	void OnClose(wxCommandEvent &ev);
	void UpdateThemeColor();
	void AddPath(const wxString &path);
	void Save();
	bool Load();
private:

	DirTreeCtrl *m_ptree;
	wxDECLARE_EVENT_TABLE();
};
