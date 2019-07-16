#include "wx/wx.h"
#include "prefs.h"
#include "flatstaticline.h"



BEGIN_EVENT_TABLE(FlatStaticLine, wxWindow)
	EVT_PAINT(FlatStaticLine::OnPaint)
END_EVENT_TABLE()



bool FlatStaticLine::Create(wxWindow *parent,
	wxWindowID id,
	const wxPoint &pos,
	const wxSize &size,
	long style)
{
	if (!wxWindow::Create(parent, id, pos, size, style))
		return false;

	wxSize sizeReal = AdjustSize(size);
	if (sizeReal != size)
		SetSize(sizeReal);

	ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	SetForegroundColour(clrs->Get(ColourScheme::STATIC_LINE));
	return true;
}

void FlatStaticLine::OnPaint(wxPaintEvent & evt)
{
	// we never have a border, so don't call the base class version whcih draws
	// it
	wxSize sz = GetSize();
	wxCoord x2, y2;
	if (IsVertical())
	{
		x2 = 0;
		y2 = sz.y;
	}
	else // horizontal
	{
		x2 = sz.x;
		y2 = 0;
	}

	wxPaintDC dc(this);
	dc.SetPen(wxPen(GetForegroundColour()));
	dc.DrawLine(0, 0, x2, y2);
	//renderer->DrawLine(0, 0, x2, y2);
	evt.Skip();
}


wxSize FlatStaticLine::AdjustSize(const wxSize& size) const
{
	wxSize sizeReal(size);
	if (IsVertical())
	{
		if (size.x == wxDefaultCoord)
			sizeReal.x = GetDefaultSize();
	}
	else
	{
		if (size.y == wxDefaultCoord)
			sizeReal.y = GetDefaultSize();
	}

	return sizeReal;
}