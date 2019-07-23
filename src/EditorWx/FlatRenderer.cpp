#include "wx/wx.h"
#include "wx/intl.h"

#include "FlatRenderer.h"



FlatRenderer::FlatRenderer()  : wxDelegateRendererNative(wxRendererNative::GetDefault())
{
}


FlatRenderer::~FlatRenderer()
{
}

void FlatRenderer::DrawItemSelectionRect(wxWindow *win, wxDC& dc, const wxRect& rect, int flags)
{
	dc.DrawRectangle(rect);
}