#pragma once

// we need OpenGL headers for GLfloat/GLint types used below
#if defined(__WXMAC__)
#   ifdef __DARWIN__
#       include <OpenGL/gl.h>
#       include <OpenGL/glu.h>
#   else
#       include <gl.h>
#       include <glu.h>
#   endif
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#endif

#include "wx/glcanvas.h"

#include "ExecutorView.h"

class ViewGCode : public wxGLCanvas
{
public:
	ViewGCode(wxWindow *parent,
		wxWindowID id = wxID_ANY,
		int *gl_attrib = NULL);

	virtual ~ViewGCode();

	void setTrack(std::vector<TrackPoint> *ptr) { track.assign( ptr->begin(), ptr->end() ); }
	void setBox(const CoordsBox &bx);
	
	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnChar(wxKeyEvent& event);
	void OnMouseEvent(wxMouseEvent& event);
	
	void InitMaterials();
	void InitGL();

private:
	void drawTrack();

private:
	wxGLContext* m_glRC;

	GLfloat m_xrot;
	GLfloat m_yrot;
	std::vector<TrackPoint> track;
	CoordsBox box;

	wxDECLARE_NO_COPY_CLASS(ViewGCode);
	wxDECLARE_EVENT_TABLE();
};

