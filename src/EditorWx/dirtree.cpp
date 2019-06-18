#include "wx/wx.h"
#include "wx/colordlg.h"
#include "wx/numdlg.h"

#include "wx/artprov.h"
#include "wx/image.h"
#include "wx/imaglist.h"
#include "wx/math.h"
#include "wx/renderer.h"
#include "wx/wupdlock.h"
#include "wx/event.h"
#include <wx/dir.h>
#include "them.h"
#include "flatbuttom.h"


#ifdef __WIN32__
    // this is not supported by native control
    #define NO_VARIABLE_HEIGHT
#endif

#include <filesystem>
#include "defsext.h"     // additional definitions
#include "dirtree.h"
#include "prefs.h"
#include "standartpaths.h"
//
#include "bitmaps/icon1.xpm"
#include "bitmaps/icon2.xpm"
#include "bitmaps/icon3.xpm"
#include "bitmaps/icon4.xpm"
#include "bitmaps/icon5.xpm"

//#include "state1.xpm"
//#include "state2.xpm"
//#include "state3.xpm"
//#include "state4.xpm"
//#include "state5.xpm"
//
//#include "unchecked.xpm"
//#include "checked.xpm"

#ifndef wxHAS_IMAGES_IN_RESOURCES
    #include "../sample.xpm"
#endif

wxDEFINE_EVENT(FILE_OPEN_EVENT, wxCommandEvent);
wxDEFINE_EVENT(FILE_REMOVE_EVENT, wxCommandEvent);
wxDEFINE_EVENT(FILE_RENAME_EVENT, wxCommandEvent);
wxDEFINE_EVENT(FILE_NEW_EVENT, wxCommandEvent);


// verify that the item is ok and insult the user if it is not
#define CHECK_ITEM( item ) if ( !item.IsOk() ) {                                 \
                             wxMessageBox("Please select some item first!", \
                                          "Tree sample error",              \
                                          wxOK | wxICON_EXCLAMATION,             \
                                          this);                                 \
                             return;                                             \
                           }


#if USE_GENERIC_TREECTRL
wxBEGIN_EVENT_TABLE(DirTreeCtrl, wxGenericTreeCtrl)
#else
wxBEGIN_EVENT_TABLE(DirTreeCtrl, wxTreeCtrl)
#endif
	EVT_MENU(ID_TREE_FILE_OPEN, DirTreeCtrl::OnFileOpen)
	EVT_MENU(ID_TREE_FILE_RENAME, DirTreeCtrl::OnFileReneme)
	EVT_MENU(ID_TREE_FILE_DELETE, DirTreeCtrl::OnFileDelete)
	EVT_MENU(ID_TREE_FOLDER_OPEN, DirTreeCtrl::OnFolderOpen)
	EVT_MENU(ID_TREE_FOLDER_REMOVE, DirTreeCtrl::OnFolderRemoveFromPoroject)
	EVT_MENU(ID_TREE_NEWNC, DirTreeCtrl::OnFileNew)
	EVT_MENU(ID_TREE_NEWGCMC, DirTreeCtrl::OnFileNew)

    EVT_TREE_BEGIN_LABEL_EDIT(wxID_ANY, DirTreeCtrl::OnBeginLabelEdit)
    EVT_TREE_END_LABEL_EDIT(wxID_ANY, DirTreeCtrl::OnEndLabelEdit)
    EVT_TREE_DELETE_ITEM(wxID_ANY, DirTreeCtrl::OnDeleteItem)
    EVT_TREE_SET_INFO(wxID_ANY, DirTreeCtrl::OnSetInfo)
    EVT_TREE_ITEM_EXPANDED(wxID_ANY, DirTreeCtrl::OnItemExpanded)
    EVT_TREE_ITEM_EXPANDING(wxID_ANY, DirTreeCtrl::OnItemExpanding)
    EVT_TREE_ITEM_COLLAPSED(wxID_ANY, DirTreeCtrl::OnItemCollapsed)
    EVT_TREE_ITEM_COLLAPSING(wxID_ANY, DirTreeCtrl::OnItemCollapsing)

    EVT_TREE_SEL_CHANGED(wxID_ANY, DirTreeCtrl::OnSelChanged)
    EVT_TREE_SEL_CHANGING(wxID_ANY, DirTreeCtrl::OnSelChanging)
    EVT_TREE_KEY_DOWN(wxID_ANY, DirTreeCtrl::OnTreeKeyDown)
    EVT_TREE_ITEM_ACTIVATED(wxID_ANY, DirTreeCtrl::OnItemActivated)
    
    // so many different ways to handle right mouse button clicks...
    //EVT_CONTEXT_MENU(DirTreeCtrl::OnContextMenu)
    // EVT_TREE_ITEM_MENU is the preferred event for creating context menus
    // on a tree control, because it includes the point of the click or item,
    // meaning that no additional placement calculations are required.
    EVT_TREE_ITEM_MENU(wxID_ANY, DirTreeCtrl::OnItemMenu)
    EVT_TREE_ITEM_RIGHT_CLICK(wxID_ANY, DirTreeCtrl::OnItemRClick)

    EVT_RIGHT_DOWN(DirTreeCtrl::OnRMouseDown)
    EVT_RIGHT_UP(DirTreeCtrl::OnRMouseUp)
    EVT_RIGHT_DCLICK(DirTreeCtrl::OnRMouseDClick)
wxEND_EVENT_TABLE()



// DirTreeCtrl implementation
#if USE_GENERIC_TREECTRL
wxIMPLEMENT_DYNAMIC_CLASS(DirTreeCtrl, wxGenericTreeCtrl);
#else
wxIMPLEMENT_DYNAMIC_CLASS(DirTreeCtrl, wxTreeCtrl);
#endif

DirTreeCtrl::DirTreeCtrl(wxWindow *parent, const wxWindowID id )
          : wxTreeCtrl(parent, id, wxDefaultPosition,wxDefaultSize, wxTR_DEFAULT_STYLE | wxTR_EDIT_LABELS | wxTR_HIDE_ROOT| wxBORDER_NONE),
            m_alternateImages(true), m_watcher(NULL)
{
    m_reverseSort = false;

    CreateImageList();
	wxString initPath = StandartPaths::Get()->GetRootPath().c_str();
	m_rootId = AddRoot("Root",-1, -1, new DirTreeItemData("Root item"));
	//AddPath(initPath);
	Bind(wxEVT_FSWATCHER, &DirTreeCtrl::OnFileSystemEvent, this);
	
	SetDropTarget(new DnDFile(this));

}

DirTreeCtrl::~DirTreeCtrl()
{

}


void DirTreeCtrl::CreateImageList(int size)
{
    if ( size == -1 )
    {
        SetImageList(NULL);
        return;
    }
    if ( size == 0 )
        size = m_imageSize;
    else
        m_imageSize = size;

    // Make an image list containing small icons
    wxImageList *images = new wxImageList(size, size, true);

    // should correspond to TreeCtrlIcon_xxx enum
    wxBusyCursor wait;
    wxIcon icons[5];

    if (m_alternateImages)
    {
        icons[TreeCtrlIcon_File] = wxIcon(icon1_xpm);
        icons[TreeCtrlIcon_FileSelected] = wxIcon(icon2_xpm);
        icons[TreeCtrlIcon_Folder] = wxIcon(icon3_xpm);
        icons[TreeCtrlIcon_FolderSelected] = wxIcon(icon4_xpm);
        icons[TreeCtrlIcon_FolderOpened] = wxIcon(icon5_xpm);
    }
    else
    {
        wxSize iconSize(size, size);

        icons[TreeCtrlIcon_File] =
        icons[TreeCtrlIcon_FileSelected] = wxArtProvider::GetIcon(wxART_NORMAL_FILE, wxART_LIST, iconSize);
        icons[TreeCtrlIcon_Folder] =
        icons[TreeCtrlIcon_FolderSelected] =
        icons[TreeCtrlIcon_FolderOpened] = wxArtProvider::GetIcon(wxART_FOLDER, wxART_LIST, iconSize);
    }

    for ( size_t i = 0; i < WXSIZEOF(icons); i++ )
    {
        int sizeOrig = icons[0].GetWidth();
        if ( size == sizeOrig )
        {
            images->Add(icons[i]);
        }
        else
        {
            images->Add(wxBitmap(wxBitmap(icons[i]).ConvertToImage().Rescale(size, size)));
        }
    }

    AssignImageList(images);
}


int DirTreeCtrl::OnCompareItems(const wxTreeItemId& item1,
                               const wxTreeItemId& item2)
{
    if ( m_reverseSort )
    {
        // just exchange 1st and 2nd items
        return wxTreeCtrl::OnCompareItems(item2, item1);
    }
    else
    {
        return wxTreeCtrl::OnCompareItems(item1, item2);
    }
}

wxTreeItemId DirTreeCtrl::FindItemsRecursively(const wxTreeItemId& idParent, const wxString &path)
{	
	wxTreeItemIdValue cookie;
	wxTreeItemId child = GetFirstChild(idParent, cookie);
	while (child.IsOk())
	{
		DirTreeItemData *item = (DirTreeItemData *)GetItemData(child);
		if (item->GetPath() == path)
		{
			return child;
		}
		if ( ItemHasChildren(child) )
		{
			wxTreeItemId found = FindItemsRecursively(child, path);
			if (found.IsOk())
				return found;
		}
		child = GetNextChild(idParent, cookie);
	}
	return wxTreeItemId();
}

void DirTreeCtrl::AddItemsRecursively(const wxTreeItemId& idParent, const wxString &path)
{
	
	wxFileName fn(path);
	wxTreeItemId id = AppendItem(idParent, fn.GetFullName(), TreeCtrlIcon_Folder, TreeCtrlIcon_Folder+1, new DirTreeItemData(fn.GetFullPath()));
	SetItemTextColour(id, Preferences::Get()->GetArtProvider()->GetColor(wxAUI_DOCKART_INACTIVE_CAPTION_TEXT_COLOUR));

		
	for (auto& p : std::filesystem::directory_iterator(path.wc_str()))
	{
		if (p.is_directory())
			AddItemsRecursively(id, p.path().c_str());
	}
	
	for (auto& p : std::filesystem::directory_iterator(path.wc_str()))
	{
		if (p.is_regular_file())
		{
			wxTreeItemId id1 = AppendItem(id, p.path().filename().c_str(), TreeCtrlIcon_File, TreeCtrlIcon_File + 1, new DirTreeItemData(p.path().c_str(), true));
			SetItemTextColour(id1, Preferences::Get()->GetArtProvider()->GetColor(wxAUI_DOCKART_INACTIVE_CAPTION_TEXT_COLOUR));
		}
	}
}

void DirTreeCtrl::AddPath(const wxString &path)                     
{
	
	wxFileName fn = path;
	if (std::filesystem::is_directory(path.wc_str()))
	{
		AddItemsRecursively(m_rootId, path);
		if (m_watcher)
		{
			wxFileName fn = wxFileName::DirName(path);
			m_watcher->AddTree(fn, wxFSW_EVENT_DELETE | wxFSW_EVENT_CREATE | wxFSW_EVENT_RENAME);
		}
	}
	else if (std::filesystem::is_regular_file(path.wc_str()))
	{
		//just open file in the editor

		wxCommandEvent event(FILE_OPEN_EVENT, GetId());
		event.SetString(path);
		event.SetEventObject(this);
		ProcessWindowEvent(event);
		/*
		AppendItem(m_rootId, fn.GetFullName(), TreeCtrlIcon_File, TreeCtrlIcon_File + 1, new DirTreeItemData(path, true));
		if (m_watcher)
		{
			wxString s2 = fn.GetPath();
			fn = wxFileName::DirName(s2);
			//m_watcher->AddTree(fn, wxFSW_EVENT_DELETE | wxFSW_EVENT_CREATE | wxFSW_EVENT_RENAME);
			m_watcher->Add(fn, wxFSW_EVENT_DELETE | wxFSW_EVENT_CREATE | wxFSW_EVENT_RENAME);
		}
		*/
	}
}

wxTreeItemId DirTreeCtrl::GetLastTreeITem() const
{
    wxTreeItemId item = GetRootItem();
    for ( ;; )
    {
        wxTreeItemId itemChild = GetLastChild(item);
        if ( !itemChild.IsOk() )
            break;

        item = itemChild;
    }

    return item;
}


void DirTreeCtrl::DoToggleIcon(const wxTreeItemId& item)
{
    int image = GetItemImage(item) == TreeCtrlIcon_Folder
                    ? TreeCtrlIcon_File
                    : TreeCtrlIcon_Folder;
    SetItemImage(item, image, wxTreeItemIcon_Normal);

    image = GetItemImage(item, wxTreeItemIcon_Selected) == TreeCtrlIcon_FolderSelected
                    ? TreeCtrlIcon_FileSelected
                    : TreeCtrlIcon_FolderSelected;
    SetItemImage(item, image, wxTreeItemIcon_Selected);
}

void DirTreeCtrl::DoResetBrokenStateImages(const wxTreeItemId& idParent,
                                          wxTreeItemIdValue cookie, int state)
{
    wxTreeItemId id;

    if ( !cookie )
        id = GetFirstChild(idParent, cookie);
    else
        id = GetNextChild(idParent, cookie);

    if ( !id.IsOk() )
        return;

    int curState = GetItemState(id);
    if ( curState != wxTREE_ITEMSTATE_NONE && curState > state )
        SetItemState(id, state);

    if (ItemHasChildren(id))
        DoResetBrokenStateImages(id, 0, state);

    DoResetBrokenStateImages(idParent, cookie, state);
}

void DirTreeCtrl::LogEvent(const wxString& name, const wxTreeEvent& event)
{
    wxTreeItemId item = event.GetItem();
    wxString text;
    if ( item.IsOk() )
        text << '"' << GetItemText(item).c_str() << '"';
    else
        text = "invalid item";
    //wxLogMessage("%s(%s)", name, text);
}

// avoid repetition
#define TREE_EVENT_HANDLER(name)                                 \
void DirTreeCtrl::name(wxTreeEvent& event)                        \
{                                                                \
    LogEvent(#name, event);                                  \
    event.Skip();                                                \
}

TREE_EVENT_HANDLER(OnBeginRDrag)
TREE_EVENT_HANDLER(OnDeleteItem)
TREE_EVENT_HANDLER(OnGetInfo)
TREE_EVENT_HANDLER(OnSetInfo)
TREE_EVENT_HANDLER(OnItemExpanded)
TREE_EVENT_HANDLER(OnItemExpanding)
TREE_EVENT_HANDLER(OnItemCollapsed)
TREE_EVENT_HANDLER(OnSelChanged)
TREE_EVENT_HANDLER(OnSelChanging)

#undef TREE_EVENT_HANDLER

void LogKeyEvent(const wxString& name, const wxKeyEvent& event)
{
    wxString key;
    long keycode = event.GetKeyCode();
    {
        switch ( keycode )
        {
            case WXK_BACK: key = "BACK"; break;
            case WXK_TAB: key = "TAB"; break;
            case WXK_RETURN: key = "RETURN"; break;
            case WXK_ESCAPE: key = "ESCAPE"; break;
            case WXK_SPACE: key = "SPACE"; break;
            case WXK_DELETE: key = "DELETE"; break;
            case WXK_START: key = "START"; break;
            case WXK_LBUTTON: key = "LBUTTON"; break;
            case WXK_RBUTTON: key = "RBUTTON"; break;
            case WXK_CANCEL: key = "CANCEL"; break;
            case WXK_MBUTTON: key = "MBUTTON"; break;
            case WXK_CLEAR: key = "CLEAR"; break;
            case WXK_SHIFT: key = "SHIFT"; break;
            case WXK_ALT: key = "ALT"; break;
            case WXK_CONTROL: key = "CONTROL"; break;
            case WXK_MENU: key = "MENU"; break;
            case WXK_PAUSE: key = "PAUSE"; break;
            case WXK_CAPITAL: key = "CAPITAL"; break;
            case WXK_END: key = "END"; break;
            case WXK_HOME: key = "HOME"; break;
            case WXK_LEFT: key = "LEFT"; break;
            case WXK_UP: key = "UP"; break;
            case WXK_RIGHT: key = "RIGHT"; break;
            case WXK_DOWN: key = "DOWN"; break;
            case WXK_SELECT: key = "SELECT"; break;
            case WXK_PRINT: key = "PRINT"; break;
            case WXK_EXECUTE: key = "EXECUTE"; break;
            case WXK_SNAPSHOT: key = "SNAPSHOT"; break;
            case WXK_INSERT: key = "INSERT"; break;
            case WXK_HELP: key = "HELP"; break;
            case WXK_NUMPAD0: key = "NUMPAD0"; break;
            case WXK_NUMPAD1: key = "NUMPAD1"; break;
            case WXK_NUMPAD2: key = "NUMPAD2"; break;
            case WXK_NUMPAD3: key = "NUMPAD3"; break;
            case WXK_NUMPAD4: key = "NUMPAD4"; break;
            case WXK_NUMPAD5: key = "NUMPAD5"; break;
            case WXK_NUMPAD6: key = "NUMPAD6"; break;
            case WXK_NUMPAD7: key = "NUMPAD7"; break;
            case WXK_NUMPAD8: key = "NUMPAD8"; break;
            case WXK_NUMPAD9: key = "NUMPAD9"; break;
            case WXK_MULTIPLY: key = "MULTIPLY"; break;
            case WXK_ADD: key = "ADD"; break;
            case WXK_SEPARATOR: key = "SEPARATOR"; break;
            case WXK_SUBTRACT: key = "SUBTRACT"; break;
            case WXK_DECIMAL: key = "DECIMAL"; break;
            case WXK_DIVIDE: key = "DIVIDE"; break;
            case WXK_F1: key = "F1"; break;
            case WXK_F2: key = "F2"; break;
            case WXK_F3: key = "F3"; break;
            case WXK_F4: key = "F4"; break;
            case WXK_F5: key = "F5"; break;
            case WXK_F6: key = "F6"; break;
            case WXK_F7: key = "F7"; break;
            case WXK_F8: key = "F8"; break;
            case WXK_F9: key = "F9"; break;
            case WXK_F10: key = "F10"; break;
            case WXK_F11: key = "F11"; break;
            case WXK_F12: key = "F12"; break;
            case WXK_F13: key = "F13"; break;
            case WXK_F14: key = "F14"; break;
            case WXK_F15: key = "F15"; break;
            case WXK_F16: key = "F16"; break;
            case WXK_F17: key = "F17"; break;
            case WXK_F18: key = "F18"; break;
            case WXK_F19: key = "F19"; break;
            case WXK_F20: key = "F20"; break;
            case WXK_F21: key = "F21"; break;
            case WXK_F22: key = "F22"; break;
            case WXK_F23: key = "F23"; break;
            case WXK_F24: key = "F24"; break;
            case WXK_NUMLOCK: key = "NUMLOCK"; break;
            case WXK_SCROLL: key = "SCROLL"; break;
            case WXK_PAGEUP: key = "PAGEUP"; break;
            case WXK_PAGEDOWN: key = "PAGEDOWN"; break;
            case WXK_NUMPAD_SPACE: key = "NUMPAD_SPACE"; break;
            case WXK_NUMPAD_TAB: key = "NUMPAD_TAB"; break;
            case WXK_NUMPAD_ENTER: key = "NUMPAD_ENTER"; break;
            case WXK_NUMPAD_F1: key = "NUMPAD_F1"; break;
            case WXK_NUMPAD_F2: key = "NUMPAD_F2"; break;
            case WXK_NUMPAD_F3: key = "NUMPAD_F3"; break;
            case WXK_NUMPAD_F4: key = "NUMPAD_F4"; break;
            case WXK_NUMPAD_HOME: key = "NUMPAD_HOME"; break;
            case WXK_NUMPAD_LEFT: key = "NUMPAD_LEFT"; break;
            case WXK_NUMPAD_UP: key = "NUMPAD_UP"; break;
            case WXK_NUMPAD_RIGHT: key = "NUMPAD_RIGHT"; break;
            case WXK_NUMPAD_DOWN: key = "NUMPAD_DOWN"; break;
            case WXK_NUMPAD_PAGEUP: key = "NUMPAD_PAGEUP"; break;
            case WXK_NUMPAD_PAGEDOWN: key = "NUMPAD_PAGEDOWN"; break;
            case WXK_NUMPAD_END: key = "NUMPAD_END"; break;
            case WXK_NUMPAD_BEGIN: key = "NUMPAD_BEGIN"; break;
            case WXK_NUMPAD_INSERT: key = "NUMPAD_INSERT"; break;
            case WXK_NUMPAD_DELETE: key = "NUMPAD_DELETE"; break;
            case WXK_NUMPAD_EQUAL: key = "NUMPAD_EQUAL"; break;
            case WXK_NUMPAD_MULTIPLY: key = "NUMPAD_MULTIPLY"; break;
            case WXK_NUMPAD_ADD: key = "NUMPAD_ADD"; break;
            case WXK_NUMPAD_SEPARATOR: key = "NUMPAD_SEPARATOR"; break;
            case WXK_NUMPAD_SUBTRACT: key = "NUMPAD_SUBTRACT"; break;
            case WXK_NUMPAD_DECIMAL: key = "NUMPAD_DECIMAL"; break;
            case WXK_BROWSER_BACK: key = "BROWSER_BACK"; break;
            case WXK_BROWSER_FORWARD: key = "BROWSER_FORWARD"; break;
            case WXK_BROWSER_REFRESH: key = "BROWSER_REFRESH"; break;
            case WXK_BROWSER_STOP: key = "BROWSER_STOP"; break;
            case WXK_BROWSER_SEARCH: key = "BROWSER_SEARCH"; break;
            case WXK_BROWSER_FAVORITES: key = "BROWSER_FAVORITES"; break;
            case WXK_BROWSER_HOME: key = "BROWSER_HOME"; break;
            case WXK_VOLUME_MUTE: key = "VOLUME_MUTE"; break;
            case WXK_VOLUME_DOWN: key = "VOLUME_DOWN"; break;
            case WXK_VOLUME_UP: key = "VOLUME_UP"; break;
            case WXK_MEDIA_NEXT_TRACK: key = "MEDIA_NEXT_TRACK"; break;
            case WXK_MEDIA_PREV_TRACK: key = "MEDIA_PREV_TRACK"; break;
            case WXK_MEDIA_STOP: key = "MEDIA_STOP"; break;
            case WXK_MEDIA_PLAY_PAUSE: key = "MEDIA_PLAY_PAUSE"; break;
            case WXK_LAUNCH_MAIL: key = "LAUNCH_MAIL"; break;
            case WXK_LAUNCH_APP1: key = "LAUNCH_APP1"; break;
            case WXK_LAUNCH_APP2: key = "LAUNCH_APP2"; break;

            default:
            {
               if ( keycode < 128 && wxIsprint((int)keycode) )
                   key.Printf("'%c'", (char)keycode);
               else if ( keycode > 0 && keycode < 27 )
                   key.Printf("Ctrl-%c", 'A' + keycode - 1);
               else
                   key.Printf("unknown (%ld)", keycode);
            }
        }
    }

    wxLogMessage( "%s event: %s (flags = %c%c%c%c)",
                  name,
                  key,
                  event.ControlDown() ? 'C' : '-',
                  event.AltDown() ? 'A' : '-',
                  event.ShiftDown() ? 'S' : '-',
                  event.MetaDown() ? 'M' : '-');
}

void DirTreeCtrl::OnTreeKeyDown(wxTreeEvent& event)
{
    //LogKeyEvent("Tree key down ", event.GetKeyEvent());
    event.Skip();
}


void DirTreeCtrl::OnBeginLabelEdit(wxTreeEvent& event)
{
    //wxLogMessage("OnBeginLabelEdit");

    // for testing, prevent this item's label editing
    wxTreeItemId itemId = event.GetItem();
    
}

void DirTreeCtrl::OnEndLabelEdit(wxTreeEvent& event)
{
	wxTreeItemId itemId = event.GetItem();
	wxCHECK_RET(itemId.IsOk(), "should have a valid item");
	DirTreeItemData *item = (DirTreeItemData *)GetItemData(itemId);
	wxString old_path = item->GetPath();
	wxFileName fn(old_path);
	wxString new_name = event.GetLabel();
	fn.SetFullName(new_name);
	try
	{
		std::filesystem::rename(old_path.wc_str(), fn.GetFullPath().wc_str());

		wxCommandEvent event(FILE_RENAME_EVENT, GetId());
		wxStringClientData string_data;
		event.SetString(old_path);
		string_data.SetData(fn.GetFullPath());
		event.SetClientObject(&string_data);			
		ProcessWindowEvent(event);
	}
	catch(...)
	{
		wxMessageBox(wxString::Format(_("Can not rename %s"), item->GetPath()), _("Renaming file"), wxOK | wxICON_INFORMATION);
		event.Veto();
    }
}

void DirTreeCtrl::OnItemCollapsing(wxTreeEvent& event)
{
    //wxLogMessage("OnItemCollapsing");

    // for testing, prevent the user from collapsing the first child folder
    wxTreeItemId itemId = event.GetItem();	
    // event.Veto();
}

void DirTreeCtrl::OnItemActivated(wxTreeEvent& event)
{
    // show some info about this item
	wxTreeItemId itemId = event.GetItem();
	wxCHECK_RET(itemId.IsOk(), "should have a valid item");
	DirTreeItemData *item = (DirTreeItemData *)GetItemData(itemId);
	OpenFile(item);
}

void DirTreeCtrl::OpenFile(DirTreeItemData *item)
{
	if (item != NULL && item->isFile())
	{
		wxCommandEvent event(FILE_OPEN_EVENT, GetId());
		event.SetString(item->GetPath());
		event.SetEventObject(this);
		ProcessWindowEvent(event);
	}
}


void DirTreeCtrl::OnItemMenu(wxTreeEvent& event)
{
    wxTreeItemId itemId = event.GetItem();
    wxCHECK_RET( itemId.IsOk(), "should have a valid item" );

    DirTreeItemData *item = (DirTreeItemData *)GetItemData(itemId);
    wxPoint clientpt = event.GetPoint();
    wxPoint screenpt = ClientToScreen(clientpt);

    //wxLogMessage("OnItemMenu for item \"%s\" at screen coords (%i, %i)", item ? item->GetDesc() : wxString("unknown"), screenpt.x, screenpt.y);

    //ShowMenu(itemId, clientpt);
	wxMenu menu(wxEmptyString);

	if (item->isFile())
	{
		menu.Append(ID_TREE_FILE_OPEN, _("&Open"));
		menu.Append(ID_TREE_FILE_RENAME, _("&Rename"));
		menu.Append(ID_TREE_FILE_DELETE, _("&Delete"));
		menu.AppendSeparator();
	}
	else
	{
		menu.Append(ID_TREE_NEWNC, _("&ew NC File"));
		menu.Append(ID_TREE_NEWGCMC, _("New GCMC File"));
		menu.Append(ID_TREE_FILE_RENAME, _("Rename"));
		menu.Append(ID_TREE_FOLDER_OPEN, _("Open Folder"));
		if(GetItemParent(itemId) == m_rootId)
			menu.Append(ID_TREE_FOLDER_REMOVE, _("Remove Folder from Project"));
	}
	
	SelectItem(itemId);
	PopupMenu(&menu, clientpt);

	event.Skip();
}

void DirTreeCtrl::OnContextMenu(wxContextMenuEvent& event)
{
    wxPoint pt = event.GetPosition();

    wxLogMessage("OnContextMenu at screen coords (%i, %i)", pt.x, pt.y);

    event.Skip();
}

void DirTreeCtrl::OnItemRClick(wxTreeEvent& event)
{
    wxTreeItemId itemId = event.GetItem();
    wxCHECK_RET( itemId.IsOk(), "should have a valid item" );

    DirTreeItemData *item = (DirTreeItemData *)GetItemData(itemId);

    //wxLogMessage("Item \"%s\" right clicked", item ? item->GetDesc() : wxString("unknown"));

    event.Skip();
}

void DirTreeCtrl::OnRMouseDown(wxMouseEvent& event)
{
    //wxLogMessage("Right mouse button down");

    event.Skip();
}

void DirTreeCtrl::OnRMouseUp(wxMouseEvent& event)
{
    //wxLogMessage("Right mouse button up");

    event.Skip();
}

void DirTreeCtrl::OnRMouseDClick(wxMouseEvent& event)
{
    wxTreeItemId id = HitTest(event.GetPosition());
    if ( !id )
    {
        //wxLogMessage("No item under mouse");
    }
    else
    {
        DirTreeItemData *item = (DirTreeItemData *)GetItemData(id);
        if ( item )
        {
            //wxLogMessage("Item '%s' under mouse", item->GetDesc());
        }
    }

    event.Skip();
}

// commands


void DirTreeCtrl::OnFileNew(wxCommandEvent &ev)
{
	wxTreeItemId id = GetSelection();
	if (!id)
		return;
	DirTreeItemData *item = (DirTreeItemData *)GetItemData(id);
	wxString defptah;
	
	if (item->isFile())
	{
		wxFileName fn = item->GetPath();
		defptah = fn.GetPath();
	}
	else
		defptah = item->GetPath();

	wxCommandEvent event(FILE_NEW_EVENT, GetId());
	event.SetInt((ev.GetId() == ID_TREE_NEWGCMC) ? FILETYPE_GCMC : FILETYPE_NC);
	event.SetString(defptah);
	event.SetEventObject(this);
	ProcessWindowEvent(event);

}

void DirTreeCtrl::OnFileOpen(wxCommandEvent &WXUNUSED(event))
{
	wxTreeItemId id = GetSelection();
	if (!id)
		return;
	DirTreeItemData *item = (DirTreeItemData *)GetItemData(id);
	OpenFile(item);
}

void DirTreeCtrl::OnFileReneme(wxCommandEvent &WXUNUSED(event))
{
	wxTreeItemId id = GetSelection();
	if (!id)
		return;
	DirTreeItemData *item = (DirTreeItemData *)GetItemData(id);
	EditLabel(id);

}
void DirTreeCtrl::OnFileDelete(wxCommandEvent &WXUNUSED(event))
{
	wxTreeItemId id = GetSelection();
	wxCHECK_RET(id.IsOk(), "should have a valid item");
	DirTreeItemData *item = (DirTreeItemData *)GetItemData(id);
	try
	{
		wxString path = item->GetPath();
		if( item->isFile() )
			std::filesystem::remove( item->GetPath().wc_str());
		else
		{
			std::filesystem::remove_all(item->GetPath().wc_str());
		}
		
		if ( !path.empty() )
		{
			wxCommandEvent event(FILE_REMOVE_EVENT, GetId());
			event.SetString(path);
			event.SetEventObject(this);
			ProcessWindowEvent(event);
		}
	}
	catch (...)
	{
		wxMessageBox(wxString::Format(_("Can not remove %s"), item->GetPath()), _("Removing file(s)"), wxOK | wxICON_INFORMATION);
	}
}

void DirTreeCtrl::OnFolderOpen(wxCommandEvent &WXUNUSED(event))
{
	wxTreeItemId id = GetSelection();
	wxCHECK_RET(id.IsOk(), "should have a valid item");
	DirTreeItemData *item = (DirTreeItemData *)GetItemData(id);
//	wxShell( wxString("start /B  ") + item->GetPath() );
	wxExecute(wxString("explorer ") + item->GetPath(), wxEXEC_ASYNC, NULL);	
}



void DirTreeCtrl::OnFolderRemoveFromPoroject(wxCommandEvent &WXUNUSED(event))
{
	wxTreeItemId id = GetSelection();
	wxCHECK_RET(id.IsOk(), "should have a valid item");
	DirTreeItemData *item = (DirTreeItemData *)GetItemData(id);
	wxCHECK_RET(!item->isFile(), "should be a folder");
	wxCHECK_RET((GetItemParent(id) == m_rootId), "should be a root folder");
	if (m_watcher)
	{
		wxFileName fn = wxFileName::DirName(item->GetPath());
		m_watcher->RemoveTree(fn);
	}
	Delete(id);
	
}


void DirTreeCtrl::SetWatcher(wxFileSystemWatcher *watcher)
{
	if (m_watcher)
		return;
	m_watcher = watcher;

	wxTreeItemIdValue cookie;
	wxTreeItemId child = GetFirstChild(m_rootId, cookie);
	while (child.IsOk())
	{
		DirTreeItemData *item = (DirTreeItemData *)GetItemData(child);		
		wxFileName fn = wxFileName::DirName(item->GetPath());
		m_watcher->AddTree(fn);
		child = GetNextChild(m_rootId, cookie);
	}
}

class DirTreeActor
{
public:
	DirTreeActor(DirTreeCtrl *pOwner, int type, const wxFileName &newname) : m_pOwner(pOwner), m_type(type),m_newname(newname) { }
	void Do(const wxTreeItemId &id, DirTreeItemData *item )
	{		
		if (!id.IsOk())
			return;

		if (m_type == wxFSW_EVENT_CREATE)
		{
			wxTreeItemId idexist = m_pOwner->FindItemsRecursively(id, m_newname.GetFullPath());
			if (!idexist.IsOk() &&  std::filesystem::is_regular_file(m_newname.GetFullPath().wc_str()))
			{
				wxTreeItemId idnew = m_pOwner->AppendItem(id, m_newname.GetFullName(), DirTreeCtrl::TreeCtrlIcon_File, DirTreeCtrl::TreeCtrlIcon_File + 1, new DirTreeItemData(m_newname.GetFullPath(), true));
				m_pOwner->SetItemTextColour(idnew, Preferences::Get()->GetArtProvider()->GetColor(wxAUI_DOCKART_INACTIVE_CAPTION_TEXT_COLOUR));
			}
			else if (!idexist.IsOk() && std::filesystem::is_directory(m_newname.GetFullPath().wc_str()))
			{
				m_pOwner->AddItemsRecursively(id, m_newname.GetFullPath());
			}
		}
		else if (m_type == wxFSW_EVENT_RENAME)
		{
			// set items label
			m_pOwner->SetItemText(id, m_newname.GetFullName());
			item->SetPath(m_newname.GetFullPath());
		}
		else if (m_type == wxFSW_EVENT_DELETE) // DELETE
		{
			m_pOwner->Delete(id);
		}


	}
private:
	DirTreeCtrl *m_pOwner;
	int m_type;
	wxFileName m_newname;
	
};

bool DirTreeCtrl::ForEachItemRecursively(const wxTreeItemId& idParent, const wxString &path, DirTreeActor *pactor)
{
	wxTreeItemIdValue cookie;
	wxTreeItemId child = GetFirstChild(idParent, cookie);
	bool stop;
	bool isRoot = (idParent == m_rootId);
	while (child.IsOk())
	{
		DirTreeItemData *item = (DirTreeItemData *)GetItemData(child);
		if (item && item->GetPath() == path)
		{
			pactor->Do( child, item);
			if (!isRoot)
				return true;
		}
		else if (ItemHasChildren(child))
		{
			stop = ForEachItemRecursively(child, path, pactor);			
			if (stop & !isRoot)
				return true;
		}
		child = GetNextChild(idParent, cookie);
	}
	return false;
}



void DirTreeCtrl::OnFileSystemEvent(wxFileSystemWatcherEvent& event)
{

	int type = event.GetChangeType();
	DirTreeActor actor(this,type, event.GetNewPath());
	if (type == wxFSW_EVENT_CREATE)
	{
		wxString path = event.GetNewPath().GetPath();
		ForEachItemRecursively(m_rootId, path, &actor);
	}
	if ((type == wxFSW_EVENT_DELETE) || (type == wxFSW_EVENT_RENAME))
	{
		ForEachItemRecursively(m_rootId, event.GetPath().GetFullPath(), &actor);
	}

}

void DirTreeCtrl::UpdateThemeColor(const wxTreeItemId& idParent, const wxColor &color)
{

	SetItemTextColour(idParent, color);
	wxTreeItemIdValue cookie;
	wxTreeItemId child = GetFirstChild(idParent, cookie);
	bool isRoot = (idParent == m_rootId);
	while (child.IsOk())
	{
		SetItemTextColour(child, color);
		if (ItemHasChildren(child))
		{
			UpdateThemeColor(child, color);
		}
		child = GetNextChild(idParent, cookie);
	}
}

void DirTreeCtrl::UpdateThemeColor()
{
	UpdateThemeColor(m_rootId, Preferences::Get()->GetArtProvider()->GetColor(wxAUI_DOCKART_INACTIVE_CAPTION_TEXT_COLOUR));
}


bool DnDFile::OnDropFiles(wxCoord, wxCoord, const wxArrayString& filenames)
{
	size_t nFiles = filenames.GetCount();
	wxString str;	
	if (m_pOwner != NULL)
	{
		for (size_t n = 0; n < nFiles; n++)
			m_pOwner->AddPath(filenames[n]);
	}

	return true;
}



#define ID_ADDFILEBT 100


wxBEGIN_EVENT_TABLE(DirPane, wxPanel)
EVT_BUTTON(ID_ADDFILEBT, DirPane::OnAddButton)
wxEND_EVENT_TABLE()

DirPane::DirPane(wxWindow *parent)
	: wxPanel(parent)
{

	m_ptree = new DirTreeCtrl(this, wxID_ANY);
	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
	wxStaticText *txt = new wxStaticText(this, wxID_ANY, _("Faforite files and folders:"));
	totalpane->Add(txt);
	totalpane->Add(m_ptree, wxEXPAND, wxEXPAND); //wxEXPAND
	totalpane->Add(0, 10);
	
	FlatButton *padd = new FlatButton(this, ID_ADDFILEBT, _("Add folders") );//| wxBORDER_NONE); 
	//wxButton *padd = new wxButton(this, ID_ADDFILEBT, _("Add folders"), wxDefaultPosition, wxDefaultSize, wxBU_LEFT);//| wxBORDER_NONE); 
	wxBitmap bmp = wxArtProvider::GetBitmap(wxART_GOTO_LAST, wxART_OTHER, FromDIP(wxSize(16, 16)));
	//padd->SetBitmap(bmp, wxRIGHT);
	padd->SetBitmap(bmp);

	totalpane->Add(padd,0, wxEXPAND);
	SetSizerAndFit(totalpane);
	UpdateThemeColor();
}

void DirPane::UpdateThemeColor()
{

	wxColor bgColor = Preferences::Get()->GetArtProvider()->GetColor(wxAUI_DOCKART_BACKGROUND_COLOUR);
	wxColor fgColor = Preferences::Get()->GetArtProvider()->GetColor(wxAUI_DOCKART_INACTIVE_CAPTION_TEXT_COLOUR);

	SetBackgroundColour(bgColor);
	wxWindowList::compatibility_iterator node = GetChildren().GetFirst();
	while (node)
	{
		wxWindow* child = node->GetData();
		child->SetBackgroundColour(bgColor);
		child->SetForegroundColour(fgColor);
		node = node->GetNext();
	}
	m_ptree->UpdateThemeColor();
}

void DirPane::OnAddButton(wxCommandEvent& WXUNUSED(ev))
{
	wxDirDialog dlg(NULL, _("Select directory"), "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
	if (dlg.ShowModal() == wxID_OK)
	{
		m_ptree->AddPath(dlg.GetPath());
	}
}

DirPane::~DirPane()
{
}
