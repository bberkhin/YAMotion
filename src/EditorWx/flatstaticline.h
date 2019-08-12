#pragma once
#include "wx\statline.h"

class FlatStaticLine : public wxWindow
{
public:
	// constructors and pseudo-constructors
	FlatStaticLine() { }

	FlatStaticLine(wxWindow *parent,
		const wxPoint &pos,
		wxCoord length,
		long style = wxLI_HORIZONTAL)
	{
		Create(parent, wxID_ANY, pos,
			style & wxLI_VERTICAL ? wxSize(wxDefaultCoord, length)
			: wxSize(length, wxDefaultCoord),
			style);
	}

	FlatStaticLine(wxWindow *parent,
		wxWindowID id = wxID_ANY,
		const wxPoint &pos = wxDefaultPosition,
		const wxSize &size = wxDefaultSize,
		long style = wxLI_HORIZONTAL)
	{
		Create(parent, id, pos, size, style);
	}

	FlatStaticLine(wxWindow *parent, long style)
	{
		Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, style);
	}

	bool Create(wxWindow *parent,
		wxWindowID id = wxID_ANY,
		const wxPoint &pos = wxDefaultPosition,
		const wxSize &size = wxDefaultSize,
		long style = wxLI_HORIZONTAL);

	bool IsVertical() const { return (GetWindowStyle() & wxLI_VERTICAL) != 0; }
	static int GetDefaultSize() { return 2; }
protected:
	wxSize AdjustSize(const wxSize& size) const;
protected:
	void OnPaint(wxPaintEvent & evt);

private:
	DECLARE_EVENT_TABLE()
};

