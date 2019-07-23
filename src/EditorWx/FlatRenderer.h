#pragma once

#include <wx/renderer.h>
#include <wx/apptrait.h>


// A renderer class draws the header buttons in a "special" way
class FlatRenderer : public wxDelegateRendererNative
{
public:
	FlatRenderer();
	~FlatRenderer();
	virtual void DrawItemSelectionRect(wxWindow *win, wxDC& dc, const wxRect& rect, int flags = 0);
};

// To use a different renderer from the very beginning we must override
// wxAppTraits method creating the renderer (another, simpler, alternative is
// to call wxRendererNative::Set() a.s.a.p. which should work in 99% of the
// cases, but we show this here just for completeness)
class FlatTraits : public wxGUIAppTraits
{
	virtual wxRendererNative *CreateRenderer() wxOVERRIDE
	{
		// it will be deleted on program shutdown by wxWidgets itself
		return new FlatRenderer;
	}
};

