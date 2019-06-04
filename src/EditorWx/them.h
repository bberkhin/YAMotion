#pragma once

#include "wx/aui/framemanager.h"
#include "wx/aui/dockart.h"
#include "wx/univ/theme.h"




class ThemArtProvider : public wxAuiDefaultDockArt
{
public:
	ThemArtProvider();
	~ThemArtProvider();
	virtual void UpdateColoursFromSystem() wxOVERRIDE;
};


//WX_USE_THEME(Win32);