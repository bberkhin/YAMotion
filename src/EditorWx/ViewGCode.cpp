#include "wx/wx.h"


#if !wxUSE_GLCANVAS
#error "OpenGL required: set wxUSE_GLCANVAS to 1 and rebuild the library"
#endif

#include <wx/timer.h>
#include <wx/math.h>
#include "ViewGCode.h"
#include "defsext.h"     // additional definitions


#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtx/transform.hpp>

void make_cylinder(Object3d& edge, int divs); //из границы в плоскости XZ создаЄт объект вращени¤ вокруг z
void make_tool_simple(Object3d& tool); //создаeт объект сверло
void make_axis(const glm::vec4 &color, const glm::vec3 &rot, float len, Object3d& axis);

GLubyte space[] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

GLubyte letters[][13] = {
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18},
{0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
{0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
{0x00, 0x00, 0xfc, 0xce, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xce, 0xfc},
{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff},
{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xff},
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e},
{0x00, 0x00, 0x7c, 0xee, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3},
{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0},
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xff, 0xe7, 0xc3},
{0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf, 0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3},
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e},
{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
{0x00, 0x00, 0x3f, 0x6e, 0xdf, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c},
{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0xe0, 0xc0, 0xc0, 0xe7, 0x7e},
{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff},
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
{0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
{0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
{0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
{0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff}
};

static const GLubyte digits[][13] = {
{0x0,0x0, 0x18,0x3C,0x66,0xC3,0xC3,0xC3,0xC3,0xC3,0x66,0x3C,0x18},
{0x0,0x0, 0x7F,0x7F,0xC,0xC,0xC,0xC,0xC,0xC,0x6C,0x3C,0xC},
{0x0,0x0, 0xFF,0xFF,0xC0,0x60,0x30,0x18,0xC,0x6,0xC6,0x66,0x3C},
{0x0,0x0, 0x7E,0xC3,0x3,0x6,0xC,0x38,0xC,0x6,0x3,0xC3,0x7E},
{0x0,0x0, 0x6,0x6,0x6,0x6,0xFF,0xFF,0xC6,0xC6,0x66,0x36,0x1E},
{0x0,0x0, 0x7E,0xFF,0xC3,0x3,0x3,0xFF,0xFE,0xC0,0xC0,0xC0,0xFE},
{0x0,0x0, 0x7E,0xFF,0xC3,0xC3,0xC3,0xFF,0xFE,0xC0,0xC0,0xC0,0x7E},
{0x0,0x0, 0x60,0x60,0x60,0x60,0x30,0x18,0xC,0x6,0x3,0x3,0xFF},
{0x0,0x0, 0x7E,0xFF,0xC3,0xC3,0xC3,0x7E,0xC3,0xC3,0xC3,0xC3,0x7E},
{0x0,0x0, 0x7E,0xFF,0xC3,0x3,0x3,0x7F,0xC3,0xC3,0xC3,0xC3,0x7E} };

class SimulateCutting : public wxThread
{
public:
	SimulateCutting(ViewGCode *handler)
		: view(handler), wxThread(wxTHREAD_DETACHED)
	{

	}
	~SimulateCutting();

protected:
	virtual wxThread::ExitCode Entry();
	ViewGCode *view;
};



wxBEGIN_EVENT_TABLE(ViewGCode, wxGLCanvas)
	EVT_SIZE(ViewGCode::OnSize)
	EVT_PAINT(ViewGCode::OnPaint)
	EVT_CHAR(ViewGCode::OnChar)
	EVT_MOUSE_EVENTS(ViewGCode::OnMouseEvent)
	EVT_MENU_RANGE(myID_SETVIEWFIRST, myID_SETVIEWLAST, ViewGCode::OnSetView)
	EVT_MENU(myID_SEMULATE_START, ViewGCode::OnSemulateStart)
	EVT_MENU(myID_SEMULATE_PAUSE, ViewGCode::OnSemulatePause)
	EVT_MENU(myID_SEMULATE_STOP, ViewGCode::OnSemulateStop)

	EVT_UPDATE_UI_RANGE(myID_SETVIEWFIRST, myID_SETVIEWLAST, ViewGCode::OnSetViewUpdate)
	EVT_UPDATE_UI(myID_SEMULATE_START, ViewGCode::OnCmdUpdateSimulateStart)
	EVT_UPDATE_UI(myID_SEMULATE_PAUSE, ViewGCode::OnCmdUpdateSimulatePause)
	EVT_UPDATE_UI(myID_SEMULATE_STOP, ViewGCode::OnCmdUpdateSimulateStop)
	EVT_UPDATE_UI(myID_SEMULATE_GOTOBEGIN, ViewGCode::OnCmdUpdateSimulateStop)
	EVT_UPDATE_UI(myID_SEMULATE_GOTOEND, ViewGCode::OnCmdUpdateSimulateStop)
	
	//EVT_KEY_DOWN(ViewGCode::OnKeyDown)

	EVT_THREAD(CUTTING_SIMULATE_UPDATE, ViewGCode::OnSimulateUpdate)
	EVT_THREAD(CUTTING_SIMULATE_COMPLETE, ViewGCode::OnSimulateCompletion)

wxEND_EVENT_TABLE()

ViewGCode::ViewGCode(wxWindow *frame, wxWindow *parent,wxWindowID id, int* gl_attrib)
	: appframe(frame), wxGLCanvas(parent, id, gl_attrib, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS | wxFULL_REPAINT_ON_RESIZE)
	
{
	simulateCut = NULL;
	tickdelay = 50;
	distancefortick = 5.;

	// Explicitly create a new rendering context instance for this canvas.
	m_glRC = new wxGLContext(this);	

	m_gridStep = 100;
	m_showGrid = true;

	make_tool_simple(tool); //делаем квадратное сверло )

	make_axis(glm::vec4(1, 0, 0, 1), glm::vec3(0, 1, 0), 1.0f, axisX);
	make_axis(glm::vec4(0, 1, 0, 1), glm::vec3(-1, 0, 0), 1.0f, axisY);
	make_axis(glm::vec4(0, 0, 1, 1), glm::vec3(0, 0, 1), 1.0f, axisZ);
	_drawCalls = 0;
	_fps = 0;
	
}

ViewGCode::~ViewGCode()
{
	delete m_glRC;
}

void ViewGCode::initializeGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel(GL_FLAT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// makeRasters font

	GLuint i, j;
	fontOffset = glGenLists(128);
	for (i = 0, j = 'A'; i < 26; i++, j++) 
	{
		glNewList(fontOffset + j, GL_COMPILE);
		glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, letters[i]);
		glEndList();
	}
	glNewList(fontOffset + ' ', GL_COMPILE);
	glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, space);
	glEndList();

	for (i = 0, j = '0'; i < 10; i++, j++)
	{
		glNewList(fontOffset + j, GL_COMPILE);
		glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, digits[i]);
		glEndList();
	}
}




void ViewGCode::resizeGL(int nWidth, int nHeight)
{
	glViewport(0, 0, nWidth, nHeight);
	camera.set_viewport(nWidth, nHeight);
}

void ViewGCode::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	// This is a dummy, to avoid an endless succession of paint messages.
	// OnPaint handlers must always create a wxPaintDC.
	wxPaintDC dc(this);

	// This is normally only necessary if there is more than one wxGLCanvas
	// or more than one wxGLContext in the application.
	SetCurrent(*m_glRC);

	initializeGL();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	camera.recalc_matrix();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	//draw_bounds();
	
	//draw_3d_grid();
	
	draw_track();
//	draw_real_track();
	//tool.draw();

	draw_axis();

	

	glDisable(GL_DEPTH_TEST);


	camera.screen_matrix();

	if (m_showGrid)
		draw_grid();

	draw_axis_letters();

	//draw_fps();
	
	if ( HasFocus() )
		draw_border();
	
	glFlush();
	SwapBuffers();
}

void ViewGCode::OnSize(wxSizeEvent& event)
{
	// This is normally only necessary if there is more than one wxGLCanvas
	// or more than one wxGLContext in the application.
	SetCurrent(*m_glRC);

	resizeGL(event.GetSize().x, event.GetSize().y);
}


void ViewGCode::OnChar(wxKeyEvent& event)
{
	switch (event.GetKeyCode())
	{
	case wxT('+'):
	case WXK_ADD:
		camera.increase_scale( 1.1f );
		break;
	case wxT('-'):
	case WXK_SUBTRACT:
		camera.increase_scale(0.9f);
		break;

	case WXK_LEFT:
		camera.move_drag_cursor(-20, 0);
		break;

	case WXK_RIGHT:
		camera.move_drag_cursor(20, 0);
		break;

	case WXK_UP:
		camera.move_drag_cursor(0, 20);
		break;

	case WXK_DOWN:
		camera.move_drag_cursor(0, -20);
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
	if (event.LeftIsDown() && event.RightIsDown() && dragging == 0)
		return;

	if (event.LeftIsDown() || event.RightIsDown() )
	{
		if (!dragging)
		{
			dragging = event.RightIsDown() ? 1 : 2;
		}
		else if (dragging == 1)//event.RightIsDown())
		{
			camera.rotate_cursor(event.GetX(), event.GetY(), last_x, last_y);
			Refresh(false);
		}
		else if (dragging == 2) //if (event.LeftIsDown())
		{
			camera.move_drag_cursor(event.GetX()- last_x, last_y - event.GetY() );
			Refresh(false);
		}
		last_x = event.GetX();
		last_y = event.GetY();
	}
	else
	{
		dragging = 0;
	}

	if (event.GetEventType() == wxEVT_MOUSEWHEEL)
	{

		int wheelRotation = event.GetWheelRotation();
		int lines = wheelRotation / event.GetWheelDelta();
		
		float delta = event.GetWheelDelta();
		delta = 1 + lines * 0.1f; //+-1.1;
		camera.move_scale_cursor(event.GetX(), event.GetY(), delta);
		Refresh(false);
	}
	
}


void ViewGCode::clear()
{
	wxCriticalSectionLocker enter(critsect);
	track.clear();
	camera.set_box(CoordsBox(Coords(0, 0, 0), Coords(1000, 1000, 300)));
	camera.set_view(TOP);
	Refresh(false);	
}

void ViewGCode::setBox(const CoordsBox &bx)
{
//	box = bx; 	
	camera.set_box(bx);
	
	// prepare axis 
	//float len = camera.pix_to_mm(100.0f); // мм for 100 pix len
	
	Refresh(false);
}

void ViewGCode::setTrack(std::vector<TrackPoint> *ptr)
{	
	
	if (simulateCut)
	{
		wxCriticalSectionLocker enter(critsect);
		simulateCut->Delete();
		simulateCut = NULL;
	}
		

	std::vector<TrackPointGL> &tr = track;
	int i = 0;
	tr.resize(ptr->size());
	std::for_each(ptr->begin(), ptr->end(), // lambda
		[&tr,&i](TrackPoint &p) {  
		tr[i].isFast = p.type == fast ? true : false;
		tr[i].line = p.line;
		tr[i].position.x = p.pt.x;
		tr[i].position.y = p.pt.y;
		tr[i].position.z = p.pt.z;
		++i; } );
}


//--------------------------------------------------------------------
void ViewGCode::draw_fps()
{
	//++_drawCalls;
	//if (time.elapsed() > 1000)
	//{
	//	_fps = _drawCalls;
	//	_drawCalls = 0;
	//	time.restart();
	//}

	//QString text = QString::number(_fps);
	//QFont font("Arial", 15, QFont::Bold);
//	renderText(5, 20, text, font);
}

//--------------------------------------------------------------------
void ViewGCode::draw_track()
{
	wxCriticalSectionLocker enter(critsect);
	glBegin(GL_LINES);
	for (size_t i = 1; i < track.size(); ++i)
	{
		if ( simulateCut && i > simulateLastIndex)
		{
			// end last
			if ( end_simulate_point.isFast )
				glColor3f(1.0f, 0.0f, 0.0f );
			else
				glColor3f(1.0f, 1.0f, 1.0f);

			glVertex3f(track[i - 1].position.x, track[i - 1].position.y, track[i - 1].position.z);
			glVertex3f(end_simulate_point.position.x, end_simulate_point.position.y, end_simulate_point.position.z);
			break;
		}

		if (track[i].isFast)
		{
			//continue;
			glColor3f(1.0f, 0.0f, 0.0f );
		}
		else
			glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(track[i - 1].position.x, track[i - 1].position.y, track[i - 1].position.z);
		glVertex3f(track[i].position.x, track[i].position.y, track[i].position.z);
	}
	glEnd();

	//glBegin(GL_POINTS);
	//glColor3f(0.7f, 0.2f, 0.9f);
	//glPointSize(3.0f);
	//for (size_t i = 0; i < track.size(); ++i)
	//{
	//	glVertex3f(track[i].position.x, track[i].position.y, track[i].position.z);
	//}
	//glEnd();
}

//--------------------------------------------------------------------
void ViewGCode::draw_real_track()
{
	glColor3f(0.5f, 0.5f, 0.0f);
	/*glBegin(GL_LINE_STRIP);
	for(size_t i = 0; i < realTrack.size(); ++i)
		glVertex3f(realTrack[i].x, realTrack[i].y, realTrack[i].z);
	glEnd();
	*/
	glEnableClientState(GL_VERTEX_ARRAY);
	if (realTrack.size() > 0)
	{
		glVertexPointer(3, GL_FLOAT, 0, &realTrack[0]);
		glDrawArrays(GL_LINE_STRIP, 0, realTrack.size());

		glColor3f(0.2f, 0.7f, 0.9f);
		glPointSize(3.0f);
		glDrawArrays(GL_POINTS, 0, realTrack.size());
	}
	glDisableClientState(GL_VERTEX_ARRAY);

}

//--------------------------------------------------------------------
//создаёт объект стрлеку
void make_axis(const glm::vec4 &color, const glm::vec3 &rot, float len, Object3d& axis)
{
	axis.indices.clear();
	axis.verts.clear();
	axis.position = glm::vec3(0, 0, 0);
	axis.rotate = rot;
	axis.angle = 90;
	axis.scale = glm::vec3(1, 1, 1);

	float r     = len / 20;
	float pimpl = len / 4;
	float pimpr = len / 10;

	glm::vec3 simple[] =
	{
		glm::vec3(0, 0, 0),
		glm::vec3(r, 0, 0),
		glm::vec3(r, 0, len),
		glm::vec3(pimpr, 0, len),
		glm::vec3(0, 0, len+pimpl)
	};

	//glm::vec3 color(1,0,0);
	for (int i = 0; i < _countof(simple); ++i)
	{
		Vertex vert(simple[i], color);
		axis.verts.push_back(vert);
	}
	make_cylinder(axis, 20);
}



void ViewGCode::draw_axis()
{
	float len = camera.pix_to_mm(60);
	axisX.scale = glm::vec3(len, len, len);
	axisY.scale = glm::vec3(len, len, len);
	axisZ.scale = glm::vec3(len, len, len);

	axisX.draw();
	axisY.draw();
	axisZ.draw();


	
}



//--------------------------------------------------------------------
void ViewGCode::draw_bounds()
{
	glColor3f(0.0f, 1.0f, 0.0f);

	CoordsBox &box = camera.get_box();

	glBegin(GL_LINES);

//from Max
	glVertex3f(box.Max.x, box.Max.y, box.Min.z);
	glVertex3f(box.Max.x, box.Min.y, box.Min.z);
	
	glVertex3f(box.Max.x, box.Max.y, box.Min.z);
	glVertex3f(box.Min.x, box.Max.y, box.Min.z);
	
	glVertex3f(box.Max.x, box.Max.y, box.Max.z);
	glVertex3f(box.Max.x, box.Min.y, box.Max.z);
	
	glVertex3f(box.Max.x, box.Max.y, box.Max.z);
	glVertex3f(box.Min.x, box.Max.y, box.Max.z);
	
	glVertex3f(box.Max.x, box.Max.y, box.Min.z);
	glVertex3f(box.Max.x, box.Max.y, box.Max.z);

//from Min
	glVertex3f(box.Min.x, box.Min.y, box.Min.z);
	glVertex3f(box.Max.x, box.Min.y, box.Min.z);

	glVertex3f(box.Min.x, box.Min.y, box.Min.z);
	glVertex3f(box.Min.x, box.Max.y, box.Min.z);

	glVertex3f(box.Min.x, box.Min.y, box.Max.z);
	glVertex3f(box.Max.x, box.Min.y, box.Max.z);

	glVertex3f(box.Min.x, box.Min.y, box.Max.z);
	glVertex3f(box.Min.x, box.Max.y, box.Max.z);

	glVertex3f(box.Min.x, box.Min.y, box.Min.z);
	glVertex3f(box.Min.x, box.Min.y, box.Max.z);
//from Min\Max
	glVertex3f(box.Min.x, box.Max.y, box.Min.z);
	glVertex3f(box.Min.x, box.Max.y, box.Max.z);
	glVertex3f(box.Max.x, box.Min.y, box.Min.z);
	glVertex3f(box.Max.x, box.Min.y, box.Max.z);
	glEnd();
}

//--------------------------------------------------------------------
void ViewGCode::draw_3d_grid()
{
	CoordsBox &box = camera.get_box();
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);

	for (float x = box.Min.x; x < box.Max.x; x += m_gridStep)
	{
		glVertex3f(x, box.Min.y, box.Min.z);
		glVertex3f(x, box.Max.y, box.Min.z);
	}

	for (float y = box.Min.y; y < box.Max.y; y += m_gridStep)
	{
		glVertex3f(box.Min.x, y, box.Min.z);
		glVertex3f(box.Max.x, y, box.Min.z);
	}
	glEnd();
}
/*
//--------------------------------------------------------------------
void ViewGCode::draw_grid1()
{
	//при масштабе 1:1 квадрат занимает 500 пикселей, это его максимальный размер
	//на 1 толстую линию еще 10 тонких
	//если между совсем тонкими больше 2 пикселей, показываем и их

	float maxSize = 500.f / camera.scale;
	float quadSize = 1.f;

	while (quadSize < maxSize) //находим подходящий размер
		quadSize *= 10;
	while (quadSize > maxSize)
		quadSize /= 10;

	float width = m_windowWidth / camera.scale;
	float height = m_windowHeight / camera.scale;
	
	glm::vec4 pos0 = camera.viewProjection * glm::vec4(0.f, 0.f, 0.f, 1.f);
	pos0.x += 1.f;
	pos0.x *= -width / 2;
	pos0.y += 1.f;
	pos0.y *= -height / 2;

	float offsetX = -pos0.x + floor(pos0.x / quadSize) * quadSize;
	float offsetY = -pos0.y + floor(pos0.y / quadSize) * quadSize;

	

	glBegin(GL_LINES);

	//мелкая сетка
	float alpha = 0.2 + quadSize / maxSize * 0.7;
	glColor4f(0.8f, 0.5f, 0.0f, alpha / 3);
	for (float x = -width / 2; x < width / 2 + quadSize; x += quadSize / 10)
	{
		glVertex2f(x + offsetX, -height / 2);
		glVertex2f(x + offsetX, height / 2);
	}

	for (float y = -height / 2; y < height / 2 + quadSize; y += quadSize / 10)
	{
		glVertex2f(-width / 2, y + offsetY);
		glVertex2f(width / 2, y + offsetY);
	}

	//крупная сетка
	glColor4f(0.8f, 0.5f, 0.0f, 1.f / 3);
	for (float x = -width / 2; x < width / 2 + quadSize; x += quadSize)
	{
		glVertex2f(x + offsetX, -height / 2);
		glVertex2f(x + offsetX, height / 2);
	}

	for (float y = -height / 2; y < height / 2 + quadSize; y += quadSize)
	{
		glVertex2f(-width / 2, y + offsetY);
		glVertex2f(width / 2, y + offsetY);
	}

	//отрезок меры
	float line = quadSize / 10;
	float notch = 3.f / camera.scale;
	float offset = 15.f / camera.scale;
	float baseX = width / 2 - line - offset;
	float baseY = -height / 2 + offset;
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glVertex2f(baseX, baseY);
	glVertex2f(baseX + line, baseY);

	glVertex2f(baseX, baseY - notch);
	glVertex2f(baseX, baseY + notch);

	glVertex2f(baseX + line, baseY - notch);
	glVertex2f(baseX + line, baseY + notch);
	glEnd();

	//int exp = floor(log10(line) + 0.5f);
	//QString text;
	//switch (exp)
	//{
	//case -3: text = QString::fromLocal8Bit("1 мкм"); break;
	//case -2: text = QString::fromLocal8Bit("10 мкм"); break;
	//case -1: text = QString::fromLocal8Bit("100 мкм"); break;
	//case 0: text = QString::fromLocal8Bit("1 мм"); break;
	//case 1: text = QString::fromLocal8Bit("1 см"); break;
	//case 2: text = QString::fromLocal8Bit("10 см"); break;
	//case 3: text = QString::fromLocal8Bit("1 м"); break;
	//case 4: text = QString::fromLocal8Bit("10 м"); break;
	//default: text = "undef"; break;
	//}

	//QFont font("Arial", 10, QFont::Bold);
	//QFontMetrics fm(font);
	//QRect rect = fm.boundingRect(text);
	//int x = m_windowWidth - (offset + line / 2) * camera.scale - rect.width() / 2;
	//int y = m_windowHeight - (offset + notch) * camera.scale;
	//renderText(x, y, text, font);

	camera.translate = oldtranslate;
}

*/
void ViewGCode::draw_grid()
{
	glColor3f(0.0, 0.0, 1.0);

	//крупная сетка
	float hMax = camera.get_vp_height() >> 1;
	float hMin = -hMax;
	float wMax = camera.get_vp_width() >> 1;
	float wMin = -wMax;


	//500pix how many mm for aproximatly 500 pix
	float maxSize = camera.pix_to_mm(300.0f); // мм for 500 pix
	float quadSize = 1.f;
	while (quadSize < maxSize) //находим подходящий размер
		quadSize *= 10;
	while (quadSize > maxSize)
		quadSize /= 10;
	
	int i = floor(maxSize / quadSize);
	quadSize = camera.mm_to_pix(i*quadSize); //mm to pix


	glm::vec4 pos0 = camera.get_projection() * glm::vec4(0.f, 0.f, 0.f, 1.f);

	pos0.x += 1.f;
	pos0.x += wMin;
	pos0.y += 1.f;
	pos0.y += hMin;

	float offsetX = -pos0.x + floor(pos0.x / quadSize) * quadSize;
	float offsetY = -pos0.y + floor(pos0.y / quadSize) * quadSize;

	char s[128];
	sprintf(s, "HELLO WORD 1234579");
	print_string(glm::vec4(1, 1, 0, 1), 0, 0, s, strlen(s));

	glBegin(GL_LINES);
	float quadSizeS = quadSize / 10;

	if (quadSizeS >= 10)
	{
		//мелкая сетка
		float alpha = 0.1f;// +quadSize / maxSize * 0.7;
		glColor4f(0.8f, 0.5f, 0.0f, alpha );
		for (float x = wMin + offsetX; x < wMax + quadSize; x += quadSizeS)
		{
			glVertex2f(x, hMin);
			glVertex2f(x, hMax);
		}

		for (float y = hMin + offsetY; y < hMax + quadSize; y += quadSizeS)
		{
			glVertex2f(wMin, y);
			glVertex2f(wMax, y);
		}
	}
	if (quadSize >= 100)
	{
		//крупная сетка
		glColor4f(0.8f, 0.5f, 0.0f, 1.f / 3);

		for (float x = wMin + offsetX; x < wMax + quadSize; x += quadSize)
		{
			glVertex2f(x, hMin);
			glVertex2f(x, hMax);
		}

		for (float y = hMin + offsetY; y < hMax + quadSize; y += quadSize)
		{
			glVertex2f(wMin, y);
			glVertex2f(wMax, y);
		}
	}

	glEnd();
}


void ViewGCode::print_string(const glm::vec4 &color, int x, int y, char *s, int len )
{
	glPushAttrib(GL_LIST_BIT);
	//glColor3fv(&color.x);
	glColor3f(color.x, color.y, color.z);
	glRasterPos2i(x, y);	
	glListBase(fontOffset);
	glCallLists(len, GL_UNSIGNED_BYTE, (GLubyte *)s);
	glPopAttrib();
}


void ViewGCode::draw_axis_letters()// test draw axis Letter
{

	char s[4] = "XYZ";
	float move = camera.pix_to_mm(80); 
	glm::vec4 pos0 = camera.get_projection() * glm::vec4(move, 0.f, 0.f, 1.f);
	int xwnd = (pos0.x + 1) * (camera.get_vp_width() >> 1) - (camera.get_vp_width() >> 1);
	int ywnd = (pos0.y + 1) * (camera.get_vp_height() >> 1) - (camera.get_vp_height() >> 1);
	print_string(glm::vec4(1.0, 0.0, 0.0,1), xwnd, ywnd, s, 1);
	
	pos0 = camera.get_projection() * glm::vec4(0.f, move,  0.f, 1.f);
	xwnd = (pos0.x + 1) * (camera.get_vp_width() >> 1) - (camera.get_vp_width() >> 1);
	ywnd = (pos0.y + 1) * (camera.get_vp_height() >> 1) - (camera.get_vp_height() >> 1);
	print_string(glm::vec4(0.0, 1.0, 0.0, 1), xwnd, ywnd, s+1, 1);

	pos0 = camera.get_projection() * glm::vec4(0.f, 0.f, move, 1.f);
	xwnd = (pos0.x + 1) * (camera.get_vp_width() >> 1) - (camera.get_vp_width() >> 1);
	ywnd = (pos0.y + 1) * (camera.get_vp_height() >> 1) - (camera.get_vp_height() >> 1);
	print_string(glm::vec4(0.0, 0.0, 1.0, 1), xwnd, ywnd, s + 2, 1);
}

//--------------------------------------------------------------------
void ViewGCode::draw_border()
{
	glColor3f(0.0, 0.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslatef(-1.0, -1.0, 0);
	glScalef(2.0 / camera.get_vp_width(), 2.0 / camera.get_vp_height(), 1);

	int borderSize = 3;
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < borderSize; ++i)
	{
		float offset = i + 0.5f;
		glVertex2f(offset, offset);
		glVertex2f(camera.get_vp_width() - offset, offset);
		glVertex2f(camera.get_vp_width() - offset, camera.get_vp_height() - offset);
		glVertex2f(offset, camera.get_vp_height() - offset);
		glVertex2f(offset, offset);
	}
	glEnd();
	glPopMatrix();
}

//--------------------------------------------------------------------
void ViewGCode::update_tool_coords(float x, float y, float z)
{
	tool.position = glm::vec3(x, y, z);
	if (realTrack.empty() || realTrack.back() != tool.position)
	{
		int size = realTrack.size();
		if (size > 1)
		{
			auto prevDirect = realTrack[size - 1] - realTrack[size - 2];
			auto direct = tool.position - realTrack[size - 1];
			auto cosA = glm::dot(direct, prevDirect) / sqrt(glm::dot(direct, direct)*glm::dot(prevDirect, prevDirect));
			if (cosA < 1 /*- 0.00001*/)
				realTrack.push_back(tool.position);
			else
				realTrack.back() = tool.position;
		}
		else
			realTrack.push_back(tool.position);

		int maximum = 10000;
		int tail = 1000;
		if (realTrack.size() > static_cast<size_t>(maximum + tail))
		{
			realTrack.erase(realTrack.begin(), realTrack.begin() + tail);
		}
	}
	
	//update();
}

// view


void ViewGCode::OnSetView(wxCommandEvent &event)
{
	camera.set_view(View(event.GetId() - myID_SETVIEWFIRST) );
	Refresh(false);
}

void ViewGCode::OnSetViewUpdate(wxUpdateUIEvent& event)
{
	event.Enable(true);
}

class SimulateThreadEvent : public wxThreadEvent
{
public:
	SimulateThreadEvent(int tillIndex_, TrackPointGL &end_point_) :
		tillindex(tillIndex_), end_point(end_point_), wxThreadEvent(wxEVT_THREAD, CUTTING_SIMULATE_UPDATE)
	{
	}
	~SimulateThreadEvent() 
	{ 
	}
	wxThreadEvent *Clone() { return new SimulateThreadEvent(tillindex, end_point); }
	int get_index() { return tillindex; }
	TrackPointGL &get_end_point() { return end_point;  }
private:
	int tillindex;
	TrackPointGL end_point;
};

wxThread::ExitCode SimulateCutting::Entry()
{

	size_t tracksize;
	TrackPointGL end_point;
	std::vector<TrackPointGL> &track = view->getTrack();
	tracksize = track.size();
	if (tracksize < 2) // nothing to do
	{
		wxQueueEvent(view, new wxThreadEvent(wxEVT_THREAD, CUTTING_SIMULATE_COMPLETE));
		return 0;
	}
	end_point = track[0];
	
	int tickdelay = view->get_tick_delay();
	double distancefortick = view->get_tick_distance();
	double segmentdist = 0;
	double currentdistoftick = 0;
	TrackPointGL second;
	
	size_t i = 1;
	while( i < tracksize )
	{
		{
			wxCriticalSectionLocker enter(view->critsect);
			second = track[i];
		}

		if (TestDestroy())
			break;
		
		segmentdist = glm::distance(end_point.position, second.position);
		if (currentdistoftick + segmentdist < distancefortick) // add point to the step
		{
			//int segmentdelay = static_cast<int>(tickdelay * (segmentdist / distancefortick));
			//currentdistoftick = 0;	
			//end_point = second;
			//SimulateThreadEvent event(i - 1, end_point);
			//wxQueueEvent(view, event.Clone());
			//if (segmentdelay > 1 )
			//	wxMilliSleep(segmentdelay);
			//++i;


			currentdistoftick += segmentdist;
			end_point = second;
			++i;
		}
		else // we should fine next end_point on the same segment
		{
			double needdistanse = (currentdistoftick + segmentdist) - distancefortick;
			float k = 1.f - float(needdistanse / segmentdist);

			glm::vec3 move = k*(second.position - end_point.position);
			end_point.position = end_point.position + move;
			end_point.line = second.line;
			currentdistoftick = 0;
			wxMilliSleep(tickdelay);

			SimulateThreadEvent event(i-1, end_point);
			wxQueueEvent(view, event.Clone());
		}
	}
	SimulateThreadEvent event(i - 1, second);
	wxQueueEvent(view, event.Clone());

	wxQueueEvent(view, new wxThreadEvent(wxEVT_THREAD, CUTTING_SIMULATE_COMPLETE));
	return 0;
}

SimulateCutting::~SimulateCutting()
{
	wxCriticalSectionLocker enter(view->critsect);
	view->simulateCut = NULL;
}

void ViewGCode::setSimulationSpeed(double mm_per_sec)
{
	// tickdelay will safe th coonstsnt 
	distancefortick = mm_per_sec * (tickdelay / 1000.f);
}

void ViewGCode::processClosing()
{
	{
		wxCriticalSectionLocker enter(critsect);
		if (simulateCut)         // does the thread still exist?
		{
			simulateCut->Delete();
		}
	}       // exit from the critical section to give the thread
			// the possibility to enter its destructor
			// (which is guarded with m_pThreadCS critical section!)
	while (1)
	{
		{ // was the ~MyThread() function executed?
			wxCriticalSectionLocker enter(critsect);
			if (!simulateCut ) break;
		}
		// wait for thread completion
		wxThread::This()->Sleep(1);
	}
}

void ViewGCode::OnSemulateStart(wxCommandEvent &event)
{
	if (simulateCut)
	{
		if ( !simulateCut->IsRunning() )
			simulateCut->Resume();
		return;
	}

	simulateLastIndex = 0;
	cur_gcode_line = 0;
	simulateCut = new SimulateCutting(this);
	
	if (simulateCut->Run() != wxTHREAD_NO_ERROR)
	{
		delete simulateCut;
		simulateCut = NULL;
	}

	Refresh(false);

}

void ViewGCode::OnSimulateUpdate(wxThreadEvent& ev)
{
	static IntClientData dataCmd;
	SimulateThreadEvent &evs = dynamic_cast<SimulateThreadEvent &>(ev);
	simulateLastIndex = evs.get_index();
	end_simulate_point = evs.get_end_point();

	if (cur_gcode_line != end_simulate_point.line)
	{
		cur_gcode_line = end_simulate_point.line;
		dataCmd.SetData(cur_gcode_line);
		wxCommandEvent *ev = new wxCommandEvent(wxEVT_MENU, myID_SELECTLINE);
		ev->SetClientObject(&dataCmd);
		wxQueueEvent(appframe, ev);
	}
	Refresh(false);
}


void ViewGCode::OnCmdUpdateSimulateStart(wxUpdateUIEvent& event)
{
	if (track.empty() || (simulateCut && simulateCut->IsRunning()) )
		event.Enable(false);
	else
		event.Enable(true);
}

void ViewGCode::OnCmdUpdateSimulateStop(wxUpdateUIEvent& event)
{
	if (simulateCut )
		event.Enable(true);
	else
		event.Enable(false);
}


void ViewGCode::OnCmdUpdateSimulatePause(wxUpdateUIEvent& event)
{
	if (simulateCut && simulateCut->IsRunning())
		event.Enable(true);
	else
		event.Enable(false);
}


void ViewGCode::OnSimulateCompletion(wxThreadEvent&)
{
	; // do somt
}

void ViewGCode::OnSemulatePause(wxCommandEvent &event)
{
	if (simulateCut && simulateCut->IsRunning())
		simulateCut->Pause();
}

void ViewGCode::OnSemulateStop(wxCommandEvent &event)
{
	if ( simulateCut )
		simulateCut->Delete();
}

//--------------------------------------------------------------------
void Object3d::draw()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	if (angle != 0)
		glRotatef(angle, rotate.x, rotate.y, rotate.z);
	glScalef(scale.x, scale.y, scale.z);
	
	glBegin(GL_TRIANGLES);
	for (size_t i = 0; i < indices.size(); ++i)
	{
		auto &vert = verts[indices[i]];
		glColor3fv(&vert.color.x);
		glVertex3fv(&vert.position.x);
	}
	glEnd();
	glPopMatrix();
}

//--------------------------------------------------------------------
//из границы в плоскости XZ создаёт объект вращения вокруг z
void make_cylinder(Object3d& edge, int divs)
{
	int countPoints = edge.verts.size();

	auto push_quad = [&edge, &countPoints](int x1, int x2, int y1, int y2)
	{
		edge.indices.push_back(x1 * countPoints + y1);
		edge.indices.push_back(x2 * countPoints + y1);
		edge.indices.push_back(x1 * countPoints + y2);


		edge.indices.push_back(x2 * countPoints + y2);
		edge.indices.push_back(x1 * countPoints + y2);
		edge.indices.push_back(x2 * countPoints + y1);
	};

	for (int i = 1; i < divs; ++i)
	{
		float phi = float(i) / divs * 2 * glm::pi<float>();
		float cosPhi = std::cos(phi);
		float sinPhi = std::sin(phi);

		for (int j = 0; j < countPoints; ++j)
		{
			auto &from = edge.verts[j];
			glm::vec3 pos;
			pos.x = from.position.x * cosPhi - from.position.y * sinPhi;
			pos.y = from.position.y * cosPhi + from.position.x * sinPhi;
			pos.z = from.position.z;
			glm::vec4 color(0.8, 0, 0, 1);
			Vertex to(pos, from.color);

			edge.verts.push_back(to);
			if (j != 0)
				push_quad(i - 1, i, j - 1, j);
		}
	}

	for (int j = 1; j < countPoints; ++j)
		push_quad(divs - 1, 0, j - 1, j);
}

//--------------------------------------------------------------------
//создаёт объект сверло
void make_tool_simple(Object3d& tool)
{
	tool.indices.clear();
	tool.verts.clear();
	tool.position = glm::vec3(1, 1, 0);
	tool.angle = 0;
	tool.rotate = glm::vec3(0, 0, 0);

	glm::vec3 simple[] =
	{
		glm::vec3(0, 0, 0),
		glm::vec3(10, 0, 10),
		glm::vec3(0, 0, 10),
	};

	//glm::vec3 color(1,0,0);
	for (int i = 0; i < _countof(simple); ++i)
	{
		glm::vec4 color(i % 2 * 0.2 + 0.4, 0, 0, 0.1f);
		Vertex vert(simple[i], color);
		tool.verts.push_back(vert);
	}

	make_cylinder(tool, 20);
}



Camera::Camera() :
	position(0, 0, 0),  //находится сверху
	look(0, 0, -1), //смотрит вниз
	top(0, 1, 0),  //смотрит ровно
	k_pix_in_mm(1)
{
	set_box(CoordsBox(Coords(0, 0, 0), Coords(1000, 1000, 300)));
}

void Camera::set_viewport(int width, int height)
{
	width_vp = width;             // viewport 
	height_vp = height;
}

void Camera::move_scale_cursor(int x, int y, float delta)
{

	glm::vec3 windowCoordinates = glm::vec3(x, y, 0.0f);

	glm::vec4 viewport = glm::vec4(0.0f, 0.0f, width_vp, height_vp);
	glm::vec3 worldCoordinates = glm::unProject(windowCoordinates, glm::mat4(1.0f), viewProjection, viewport);
	worldCoordinates = glm::vec3(worldCoordinates.x, worldCoordinates.y, worldCoordinates.z);
	scale_add *= delta;
	recalc_matrix();
	glm::vec3 windowCoordinates1 = glm::project(worldCoordinates, glm::mat4(1.0f), viewProjection, viewport);

	move_drag_cursor( windowCoordinates1.x - windowCoordinates.x, windowCoordinates1.y - windowCoordinates.y);
}


void Camera::move_drag_cursor(int deltaX, int deltaY)
{
	// Unproject Window Coordinates
	int x = width_vp >> 1;
	int y = height_vp >> 1;
	glm::vec3 windowCoordinates = glm::vec3(x, y, 0.0f);
	glm::vec3 windowCoordinates1 = glm::vec3(x + deltaX, y + deltaY, 0.0f);

	glm::vec4 viewport = glm::vec4(0.0f, 0.0f, (float)width_vp, (float)height_vp);

	glm::vec3 worldCoordinates = glm::unProject(windowCoordinates, glm::mat4(1.0f), viewProjection, viewport);
	glm::vec3 worldCoordinates1 = glm::unProject(windowCoordinates1, glm::mat4(1.0f), viewProjection, viewport);

	translate_add += ((worldCoordinates1 - worldCoordinates) * (scale_origin*scale_add) );

}


void Camera::reset_matrix(float scale_add_)
{
	k_pix_in_mm = 1;
	scale_add = scale_add_;
	translate_add = glm::vec3();
}


void Camera::recalc_matrix()
{
	if (box.isEmpty())
		return;

	glm::vec3 translate = translate_origin + translate_add;
	float scale = scale_origin * scale_add;

	float scale_wnd = 2.0f / width_vp; // это ширина бокса вписанного в -1 до 1
	k_pix_in_mm = scale_wnd / scale;


	//Во время умножения матриц правая матрица умножается на вектор, поэтому вам надо читать умножения справа налево.
	//Рекомендуется в начале масштабировать, затем вращать и в конце сдвигать

	glm::mat4 mView = glm::lookAt(position - look, position, top);

	glm::mat4 mTrans(1.0f);
	mTrans = glm::translate(mTrans, translate);
	mTrans = glm::scale(mTrans, glm::vec3(scale, scale, scale));

	glm::mat4 mProj = glm::ortho(-1.f, 1.f, -1.f, 1.f, -1000.f, 10000.f);

	viewProjection = mProj * mView * mTrans;

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( glm::value_ptr(viewProjection) );
}

float Camera::mm_to_pix(float valmm)
{
	return valmm / k_pix_in_mm;
}
float Camera::pix_to_mm(float pix)
{
	return pix*k_pix_in_mm;
}

//--------------------------------------------------------------------
void Camera::screen_matrix()
{

//	float fscale = scale * 2; //1пиксель - 1мм, координаты на виджете от -1 до 1
//	glm::mat4 mScale = glm::scale(glm::mat4(1.0f), glm::vec3(fscale / width_vp, fscale / height_vp, 1.f));
	
// 1 пиксель == 1 мм, координаты на виджете от -1 до 1

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glTranslatef(-1.0, -1.0, 0);
	glScalef(2.0 / get_vp_width(), 2.0 / get_vp_height(), 1);
}


//--------------------------------------------------------------------
void Camera::rotate_cursor(int xc, int yc, int xprev, int yprev)
//(float x, float y, float deltaX, float deltaY)
{
// some magic
	float scl = 5.1f;
	float x = (float(xprev) / width_vp - 0.5) * 2;
	float y = (1 - float(yprev) / height_vp - 0.5) * 2;
	float newX = (float(xc) / width_vp - 0.5) * 2;
	float newY = (1 - float(yc) / height_vp - 0.5) * 2;
	float deltaX = scl * (newX - x);
	float deltaY = scl * (newY - y);
	
	glm::vec3 axisX = glm::cross(look, top);
	glm::vec3 axisY = top;
	glm::vec3 axisZ = -look;

	//считаем ось в пространстве камеры,
	//потом переводим её в глобальное пространство
	//и поворачиваем вектора камеры относительно этой оси
	glm::vec3 axisToCursor(x, y, glm::sqrt(glm::abs(1 - x * x - y * y)));
	glm::vec3 cursorOffset(deltaX, deltaY, 0);
	glm::vec3 axis = glm::cross(axisToCursor, cursorOffset);
	glm::vec3 localAxis = axis.x * axisX + axis.y * axisY + axis.z * axisZ;

	glm::mat4 rotation(1.0f);
	rotation = glm::rotate(rotation, glm::sqrt(deltaX*deltaX + deltaY * deltaY), localAxis);

	look = glm::vec3(glm::vec4(look, 0) * rotation);
	//position = glm::vec3(glm::vec4(position,0) * rotation);
	top = glm::vec3(glm::vec4(top, 0) * rotation);
}

//--------------------------------------------------------------------
void Camera::set_view(View view)
{
	glm::vec3 x(1, 0, 0), y(0, 1, 0), z(0, 0, 1);

	//position(0, 0, 0),  //находится сверху
	//look(0, 0, -1), //смотрит вниз
	//top(0, 1, 0)  //смотрит ровно

	switch (view)
	{
		case View::TOP: look = -z; top = y; break;
		case View::BOTTOM: look = z; top = -y; break;
		case View::LEFT: look = x; top = z; break;
		case View::RIGHT: look = -x; top = z; break;
		case View::FRONT: look = y; top = z; break;
		case View::BACK: look = -y; top = z; break;
		case View::ISOMETR: look = glm::vec3(1, 1, -1); top = glm::vec3(0.5, 0.5, 0); break;
	}
	reset_matrix(view == View::ISOMETR ? 0.8f : 0.9f );	
}

void Camera::increase_scale(float dscl)
{
	scale_add *= dscl;
}

void Camera::set_box(const CoordsBox &bx)
{
	box = bx;
	// box must be in [-1;1] range
	float scalex = 2.0f / (box.Max.x - box.Min.x);
	float scaley = 2.0f / (box.Max.y - box.Min.y);
	//float scalez = 2.0f / (box.Max.z - box.Min.z);
	scale_origin = glm::min(scalex, scaley);//  glm::min(glm::min(scalex, scaley), scalez);
	scale_add = 0.9f;
	float xcenter = box.Max.x / 2.0f + box.Min.x / 2.0f;
	float ycenter = box.Max.y / 2.0f + box.Min.y / 2.0f;
	float zcenter = box.Max.z / 2.0f + box.Min.z / 2.0f;
	translate_origin = glm::vec3(-xcenter * scale_origin*scale_add, -ycenter * scale_origin*scale_add, -zcenter * scale_origin*scale_add);

	reset_matrix(scale_add);
}