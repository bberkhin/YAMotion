#define USE_GENERIC_TREECTRL 0

#if USE_GENERIC_TREECTRL
#include "wx/generic/treectlg.h"
#ifndef wxTreeCtrl
#define wxTreeCtrl wxGenericTreeCtrl
#define sm_classwxTreeCtrl sm_classwxGenericTreeCtrl
#endif
#endif

#include "wx/treectrl.h"

// Define a new application type

class DirTreeItemData : public wxTreeItemData
{
public:
	DirTreeItemData(const wxString& desc, bool isfile = false) : m_path(desc), m_isfile(isfile)  { }
    wxString const& GetPtah() const { return m_path; }
	bool isFile() { return m_isfile; }

private:
    wxString m_path;
	bool m_isfile;
};

class DirTreeCtrl : public wxTreeCtrl
{
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
    virtual ~DirTreeCtrl(){}

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

    void OnRMouseDown(wxMouseEvent& event);
    void OnRMouseUp(wxMouseEvent& event);
    void OnRMouseDClick(wxMouseEvent& event);

    wxTreeItemId GetLastTreeITem() const;
    void GetItemsRecursively(const wxTreeItemId& idParent,
                             wxTreeItemIdValue cookie = 0);

    void CreateImageList(int size = 16);

    void AddPath(const wxString &path);
	
    void DoSortChildren(const wxTreeItemId& item, bool reverse = false)
        { m_reverseSort = reverse; wxTreeCtrl::SortChildren(item); }

    void DoToggleIcon(const wxTreeItemId& item);
    
    void ShowMenu(wxTreeItemId id, const wxPoint& pt);

    int ImageSize(void) const { return m_imageSize; }

    void SetAlternateImages(bool show) { m_alternateImages = show; }
    bool AlternateImages() const { return m_alternateImages; }

    void SetAlternateStates(bool show) { m_alternateStates = show; }
    bool AlternateStates() const { return m_alternateStates; }

    void ResetBrokenStateImages()
    {
        const size_t count = GetStateImageList()->GetImageCount();
        int state = count > 0 ? count - 1 : wxTREE_ITEMSTATE_NONE;
        DoResetBrokenStateImages(GetRootItem(), 0, state);
    }

protected:
    virtual int OnCompareItems(const wxTreeItemId& i1, const wxTreeItemId& i2) wxOVERRIDE;


private:
    // Find the very last item in the tree.
    void AddItemsRecursively( const wxTreeItemId& idParent, const wxString &path);

    void DoResetBrokenStateImages(const wxTreeItemId& idParent,
                                  wxTreeItemIdValue cookie, int state);

    void LogEvent(const wxString& name, const wxTreeEvent& event);

    int          m_imageSize;               // current size of images
    bool         m_reverseSort;             // flag for OnCompareItems
    wxTreeItemId m_draggedItem;             // item being dragged right now
    bool         m_alternateImages;
    bool         m_alternateStates;
	wxTreeItemId m_rootId;

    // NB: due to an ugly wxMSW hack you _must_ use wxDECLARE_DYNAMIC_CLASS();
    //     if you want your overloaded OnCompareItems() to be called.
    //     OTOH, if you don't want it you may omit the next line - this will
    //     make default (alphabetical) sorting much faster under wxMSW.
    wxDECLARE_DYNAMIC_CLASS(DirTreeCtrl);
    wxDECLARE_EVENT_TABLE();
};
