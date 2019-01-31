#include "wx/wx.h"


#if !wxUSE_GLCANVAS
#error "OpenGL required: set wxUSE_GLCANVAS to 1 and rebuild the library"
#endif

#include <wx/timer.h>
#include <wx/math.h>
#include "ViewGCode.h"

// global options which can be set through command-line options
//TEMPORARY


GLboolean g_smooth = GL_TRUE;
GLboolean g_lighting = GL_TRUE;



//---------------------------------------------------------------------------
// ViewGCode
//---------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(ViewGCode, wxGLCanvas)
EVT_SIZE(ViewGCode::OnSize)
EVT_PAINT(ViewGCode::OnPaint)
EVT_CHAR(ViewGCode::OnChar)
EVT_MOUSE_EVENTS(ViewGCode::OnMouseEvent)
wxEND_EVENT_TABLE()

ViewGCode::ViewGCode(wxWindow *parent,
	wxWindowID id,
	int* gl_attrib)
	: wxGLCanvas(parent, id, gl_attrib)
{
	m_xrot = 0;
	m_yrot = 0;

	// Explicitly create a new rendering context instance for this canvas.
	m_glRC = new wxGLContext(this);	
}

ViewGCode::~ViewGCode()
{
	delete m_glRC;
}


void ViewGCode::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	// This is a dummy, to avoid an endless succession of paint messages.
	// OnPaint handlers must always create a wxPaintDC.
	wxPaintDC dc(this);

	// This is normally only necessary if there is more than one wxGLCanvas
	// or more than one wxGLContext in the application.
	SetCurrent(*m_glRC);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(m_yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(m_xrot, 1.0f, 0.0f, 0.0f);

	// draw the surface

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -2.0f);
	glRotatef(m_xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(m_yrot, 0.0f, 1.0f, 0.0f);

	//drawBox();
	drawTrack();
	


	glPopMatrix();
	glFlush(); // Not really necessary: buffer swapping below implies glFlush()
	SwapBuffers();
}

void ViewGCode::OnSize(wxSizeEvent& event)
{
	if (!IsShownOnScreen())
		return;
	// This is normally only necessary if there is more than one wxGLCanvas
	// or more than one wxGLContext in the application.
	SetCurrent(*m_glRC);

	// It's up to the application code to update the OpenGL viewport settings.
	// This is OK here only because there is only one canvas that uses the
	// context. See the cube sample for that case that multiple canvases are
	// made current with one context.
	glViewport(0, 0, event.GetSize().x, event.GetSize().y);
}

void ViewGCode::OnChar(wxKeyEvent& event)
{
	switch (event.GetKeyCode())
	{
	case WXK_ESCAPE:
		wxTheApp->ExitMainLoop();
		return;

	case WXK_LEFT:
		m_yrot -= 15.0;
		break;

	case WXK_RIGHT:
		m_yrot += 15.0;
		break;

	case WXK_UP:
		m_xrot += 15.0;
		break;

	case WXK_DOWN:
		m_xrot -= 15.0;
		break;

	case 's': case 'S':
		g_smooth = !g_smooth;
		if (g_smooth)
			glShadeModel(GL_SMOOTH);
		else
			glShadeModel(GL_FLAT);
		break;

	case 'l': case 'L':
		g_lighting = !g_lighting;
		if (g_lighting)
			glEnable(GL_LIGHTING);
		else
			glDisable(GL_LIGHTING);
		break;

	default:
		event.Skip();
		return;
	}

	Refresh(false);
}

void ViewGCode::OnMouseEvent(wxMouseEvent& event)
{
	static int dragging = 0;
	static float last_x, last_y;

	// Allow default processing to happen, or else the canvas cannot gain focus
	// (for key events).
	event.Skip();

	if (event.LeftIsDown())
	{
		if (!dragging)
		{
			dragging = 1;
		}
		else
		{
			m_yrot += (event.GetX() - last_x)*1.0;
			m_xrot += (event.GetY() - last_y)*1.0;
			Refresh(false);
		}
		last_x = event.GetX();
		last_y = event.GetY();
	}
	else
	{
		dragging = 0;
	}
}

void ViewGCode::InitMaterials()
{
	static const GLfloat ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	static const GLfloat diffuse[4] = { 0.5f, 1.0f, 1.0f, 1.0f };
	static const GLfloat position0[4] = { 0.0f, 0.0f, 20.0f, 0.0f };
	static const GLfloat position1[4] = { 0.0f, 0.0f, -20.0f, 0.0f };
	static const GLfloat front_mat_shininess[1] = { 60.0f };
	static const GLfloat front_mat_specular[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	static const GLfloat front_mat_diffuse[4] = { 0.5f, 0.28f, 0.38f, 1.0f };
	/*
	static const GLfloat back_mat_shininess[1] = {60.0f};
	static const GLfloat back_mat_specular[4] = {0.5f, 0.5f, 0.2f, 1.0f};
	static const GLfloat back_mat_diffuse[4] = {1.0f, 1.0f, 0.2f, 1.0f};
	*/
	static const GLfloat lmodel_ambient[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static const GLfloat lmodel_twoside[1] = { GL_FALSE };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, position1);
	glEnable(GL_LIGHT1);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_twoside);
	glEnable(GL_LIGHTING);

	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, front_mat_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, front_mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, front_mat_diffuse);
}

void ViewGCode::InitGL()
{
	// Make the new context current (activate it for use) with this canvas.
	SetCurrent(*m_glRC);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	InitMaterials();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 3.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -2.0f);

	
	InitMaterials();
}

void ViewGCode::setBox(const CoordsBox &bx)
{
	
	box = bx; 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if ( box.isEmpty() )
		glFrustum(-0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 3.0f);
	else
		glFrustum(box.Min.x, box.Max.x, box.Min.y, box.Max.y, 1.0f, 3.0f);
	//glFrustum(box.Min.x, box.Max.x, box.Min.y, box.Max.y, box.Min.z, box.Max.z);
}


void ViewGCode::drawTrack()
{
	glBegin(GL_LINES);
	size_t len = track.size();
	for (size_t i = 1; i < len ; ++i)
	{
		if (track[i].type == TypeMove::fast )
		{
			//continue;
			glColor4f(0.3f, 0.1f, 0.0f, 1.0f);
		}
		else
			glColor3f(0.1f, 0.3f, 0.0f);
		glVertex3f(track[i - 1].pt.x, track[i - 1].pt.y, track[i - 1].pt.z);
		glVertex3f(track[i].pt.x, track[i].pt.y, track[i].pt.z);
	}
	glEnd();

	glBegin(GL_POINTS);
	glColor3f(0.7f, 0.2f, 0.9f);
	glPointSize(3.0f);
	for (size_t i = 0; i < len; ++i)
	{
		glVertex3f(track[i].pt.x, track[i].pt.y, track[i].pt.z);
	}
	glEnd();
}