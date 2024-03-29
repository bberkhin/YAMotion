#include "wx/wx.h"


#if !wxUSE_GLCANVAS
#error "OpenGL required: set wxUSE_GLCANVAS to 1 and rebuild the library"
#endif

#include <wx/timer.h>
#include <wx/math.h>
#include "View3D.h"
#include "defsext.h"     // additional definitions
#include "configdata.h"
#include "app.h"
#include "appframe.h"    
#include "them.h"
#include "prefs.h"


#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtx/transform.hpp>

void make_cylinder(Object3d& edge, int divs); //�� ������� � ��������� XZ ������ ������ ������� ������ z
void make_tool_simple(Object3d& tool); //�����e� ������ ������
void make_axis(const glm::vec3 &color, const glm::vec3 &rot, float len, Object3d& axis);

GLubyte space[] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
//46
GLubyte dotsym[] =
{ 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

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



wxBEGIN_EVENT_TABLE(View3D, wxGLCanvas)
	EVT_SIZE(View3D::OnSize)
	EVT_PAINT(View3D::OnPaint)
	EVT_CHAR(View3D::OnChar)
	EVT_MOUSE_EVENTS(View3D::OnMouseEvent)
wxEND_EVENT_TABLE()

#define SET_COLOR(clr,index) color_ = clrs->Get(index); \
	clr.r = color_.Red() / 255.f;\
	clr.g = color_.Green() / 255.f;\
	clr.b = color_.Blue() / 255.f

View3D::View3D( wxWindow *parent,wxWindowID id, int* gl_attrib)
	:  wxGLCanvas(parent, id, gl_attrib, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS | wxFULL_REPAINT_ON_RESIZE)	
{	
	
	simulateLastIndex = wxNOT_FOUND;
	// Explicitly create a new rendering context instance for this canvas.
	m_glRC = new wxGLContext(this);	

	m_gridStep = 100;

	
	ConfigData *config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
	wxASSERT(config);
	m_viewstyle = config->GetViewStyle();
	make_tool_simple(tool); //������ ���������� ������ )
	UpdatePreferenses();
}

View3D::~View3D()
{
	delete m_glRC;
}

void View3D::UpdatePreferenses()
{
	ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	wxColor color_;
	SET_COLOR(m_bgcolor, ColourScheme::WINDOW_3DVIEW);
	SET_COLOR(m_boxcolor, ColourScheme::VIEW3D_BOX);
	SET_COLOR(m_fastcolor, ColourScheme::VIEW3D_G0);
	SET_COLOR(m_feedcolor, ColourScheme::VIEW3D_G1);
	SET_COLOR(m_xaxiscolor, ColourScheme::VIEW3D_XAXIS);
	SET_COLOR(m_yaxiscolor, ColourScheme::VIEW3D_YAXIS);
	SET_COLOR(m_zaxiscolor, ColourScheme::VIEW3D_ZAXIS);


	make_axis(m_xaxiscolor, glm::vec3(0, 1, 0), 1.0f, axisX);
	make_axis(m_yaxiscolor, glm::vec3(-1, 0, 0), 1.0f, axisY);
	make_axis(m_zaxiscolor, glm::vec3(0, 0, 1), 1.0f, axisZ);
}

void View3D::initializeGL()
{
	glClearColor(m_bgcolor.r, m_bgcolor.g, m_bgcolor.b, 0.0f);
	
	
	glShadeModel(GL_FLAT);
	glEnable(GL_CULL_FACE);
	/*
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	*/

	// prepare font
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
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
	
	glNewList(fontOffset + '.', GL_COMPILE);
	glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, dotsym);
	glEndList();
	
	glNewList(fontOffset + ',', GL_COMPILE);
	glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, dotsym);
	glEndList();

	for (i = 0, j = '0'; i < 10; i++, j++)
	{
		glNewList(fontOffset + j, GL_COMPILE);
		glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, digits[i]);
		glEndList();
	}
}




void View3D::resizeGL(int nWidth, int nHeight)
{
	glViewport(0, 0, nWidth, nHeight);
	camera.set_viewport(nWidth, nHeight);
}

void View3D::OnPaint(wxPaintEvent& WXUNUSED(event))
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

	//glEnable(GL_DEPTH_TEST);
	


	if (m_viewstyle&VSTYLE_SHOWBOX)
		draw_bounds();
	
	//if (m_viewstyle&VSTYLE_SHOWGRID3D)
		//draw_3d_grid();
	
	draw_track();
	
//	if (m_viewstyle&VSTYLE_SHOWTOOL)
//		tool.draw();

	if (m_viewstyle&VSTYLE_SHOWAXIS)
		draw_axis();

	glDisable(GL_DEPTH_TEST);

	camera.screen_matrix();

//	if (m_viewstyle&VSTYLE_SHOWGRID)
//		draw_grid();

	if (m_viewstyle&VSTYLE_SHOWAXIS)
		draw_axis_letters();
		
//	if ( HasFocus() )
	//	draw_border();
	
	glFlush();
	SwapBuffers();
}

void View3D::OnSize(wxSizeEvent& event)
{
	// This is normally only necessary if there is more than one wxGLCanvas
	// or more than one wxGLContext in the application.
	SetCurrent(*m_glRC);

	resizeGL(event.GetSize().x, event.GetSize().y);
}


void View3D::OnChar(wxKeyEvent& event)
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

void View3D::OnMouseEvent(wxMouseEvent& event)
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
			CaptureMouse();
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
	else if ( dragging )
	{
		ReleaseMouse();
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


void View3D::clear()
{
	track.clear();
	camera.set_box(CoordsBox(Coords(0, 0, 0), Coords(1000, 1000, 300)));
	camera.set_view(TOP);
	Refresh(false);	
}

void View3D::setBox(const CoordsBox &bx)
{
	CoordsBox boxOk = CheckBox(bx);
	camera.set_box(boxOk);
	Refresh(false);
}

CoordsBox View3D::CheckBox(const CoordsBox &bx)
{
	CoordsBox boxOk = bx;
	if (boxOk.Max.x == boxOk.Min.x)
	{
		boxOk.Min.x -= 0.5;
		boxOk.Max.x += 0.5;
	}
	if (boxOk.Max.y == boxOk.Min.y)
	{
		boxOk.Min.y -= 0.5;
		boxOk.Max.y += 0.5;
	}
	if (boxOk.Max.z == boxOk.Min.z)
	{
		boxOk.Min.z -= 0.5;
		boxOk.Max.z += 0.5;
	}
	return boxOk;
}

void View3D::setTrack(TrackPoints &ptr)
{	
	track.swap(ptr);	
}


//--------------------------------------------------------------------
void View3D::draw_track()
{
	//wxCriticalSectionLocker enter(critsect);
	glBegin(GL_LINES);
	for (size_t i = 1; i < track.size(); ++i)
	{
		if (simulateLastIndex != wxNOT_FOUND && i > simulateLastIndex)
		{
			// end last
			if ( end_simulate_point.isFast )
				glColor3fv(&m_fastcolor.x);
			else
				glColor3fv(&m_feedcolor.x);

			glVertex3f(track[i - 1].position.x, track[i - 1].position.y, track[i - 1].position.z);
			glVertex3f(end_simulate_point.position.x, end_simulate_point.position.y, end_simulate_point.position.z);
			break;
		}
		
		if (track[i].isFast && !(m_viewstyle&VSTYLE_SHOWFASTMOVE))
			continue;

		if (track[i].isFast)
		{
			//continue;
			glColor3fv(&m_fastcolor.x);
		}
		else
		{
			glColor3fv(&m_feedcolor.x);
		}
		glVertex3f(track[i - 1].position.x, track[i - 1].position.y, track[i - 1].position.z);
		glVertex3f(track[i].position.x, track[i].position.y, track[i].position.z);
	}
	glEnd();
}


//--------------------------------------------------------------------
//������ ������ �������
void make_axis(const glm::vec3 &color, const glm::vec3 &rot, float len, Object3d& axis)
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



void View3D::draw_axis()
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
void View3D::draw_bounds()
{
	glColor3fv(&m_boxcolor.x);

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
void View3D::draw_3d_grid()
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
void View3D::draw_grid1()
{
	//��� �������� 1:1 ������� �������� 500 ��������, ��� ��� ������������ ������
	//�� 1 ������� ����� ��� 10 ������
	//���� ����� ������ ������� ������ 2 ��������, ���������� � ��

	float maxSize = 500.f / camera.scale;
	float quadSize = 1.f;

	while (quadSize < maxSize) //������� ���������� ������
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

	//������ �����
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

	//������� �����
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

	//������� ����
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
	//case -3: text = QString::fromLocal8Bit("1 ���"); break;
	//case -2: text = QString::fromLocal8Bit("10 ���"); break;
	//case -1: text = QString::fromLocal8Bit("100 ���"); break;
	//case 0: text = QString::fromLocal8Bit("1 ��"); break;
	//case 1: text = QString::fromLocal8Bit("1 ��"); break;
	//case 2: text = QString::fromLocal8Bit("10 ��"); break;
	//case 3: text = QString::fromLocal8Bit("1 �"); break;
	//case 4: text = QString::fromLocal8Bit("10 �"); break;
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
void View3D::draw_grid()
{
	glColor3f(0.0, 0.0, 1.0);

	//������� �����
	float hMax = camera.get_vp_height() >> 1;
	float hMin = -hMax;
	float wMax = camera.get_vp_width() >> 1;
	float wMin = -wMax;


	//500pix how many mm for aproximatly 500 pix
	float maxSize = camera.pix_to_mm(300.0f); // �� for 500 pix
	float quadSize = 1.f;
	while (quadSize < maxSize) //������� ���������� ������
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


	glBegin(GL_LINES);
	float quadSizeS = quadSize / 10;

	if (quadSizeS >= 30)
	{
	//������ �����
		float alpha = 0.1f;// +quadSize / maxSize * 0.7;
		glColor4f(0.8f, 0.5f, 0.0f, alpha);
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
		//������� �����
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

	// draw scale
	int n;
	if (quadSize >= 100)
	{
		glm::vec4 clr(1, 1, 0, 1);
		int offset = 2;
		for (float x = wMin + offsetX; x < wMax + quadSize; x += quadSize)
		{
			sprintf(s, "%.2f", x );
			n = strlen(s);
			print_string(clr, x - (n >> 1) * 8, hMin + offset, s, n );

		}

		for (float y = hMin + offsetY; y < hMax + quadSize; y += quadSize)
		{
			sprintf(s, "%.2f", y);
			n = strlen(s);
			print_string(clr, wMin + offset, y-6, s, n);
		}
	}
}


void View3D::print_string(const glm::vec3 &color, int x, int y, char *s, int len )
{
	glPushAttrib(GL_LIST_BIT);
	//glColor3fv(&color.x);
	glColor3fv(&color.x);
	glRasterPos2i(x, y);	
	glListBase(fontOffset);
	glCallLists(len, GL_UNSIGNED_BYTE, (GLubyte *)s);
	glPopAttrib();
}


void View3D::draw_axis_letters()// test draw axis Letter
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
void View3D::draw_border()
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
void View3D::update_tool_coords(float x, float y, float z)
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


void View3D::DoSetView(View stdview)
{
	camera.set_view(stdview);
	Refresh(false);
}


void View3D::ToggleStyle( int style)
{
	if (m_viewstyle & style)
		m_viewstyle &= (~style);
	else
		m_viewstyle |= style;

	ConfigData *config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
	if(config)
		config->SetViewStyle( m_viewstyle );

	Refresh(false);
}


void View3D::setSimulationPos(int index, const TrackPointGL &endpt )
{
	simulateLastIndex = index;
	end_simulate_point = endpt;
	Refresh(false);
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
//�� ������� � ��������� XZ ������ ������ �������� ������ z
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
			glm::vec3 color(0.8, 0, 0 );
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
//������ ������ ������
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
		glm::vec3 color(i % 2 * 0.2 + 0.4, 0, 0/*, 0.1f*/);
		Vertex vert(simple[i], color);
		tool.verts.push_back(vert);
	}

	make_cylinder(tool, 20);
}



Camera::Camera() :
	position(0, 0, 0),  //��������� ������
	look(0, 0, -1), //������� ����
	top(0, 1, 0),  //������� �����
	k_pix_in_mm(1)
{
	set_box(CoordsBox(Coords(0, 0, 0), Coords(1000, 1000, 300)));
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

	//glm::vec3 translate_add1 = scale_origin * scale_add;
	glm::mat3x3 m(scale_add);
	m *= scale_origin;
	
	translate_add += (m * ((worldCoordinates1 - worldCoordinates)));
	//translate_add += ((worldCoordinates1 - worldCoordinates) * (scale_origin*scale_add) );

}


void Camera::reset_matrix(float scale_add_)
{
	k_pix_in_mm = 1;
	scale_add = scale_add_;
	translate_add = glm::vec3();
}


void Camera::recalc_matrix()
{
//	wxLogMessage("recalc_matrix: look: %f %f %f", look.x, look.y, look.z);

	if (box.isEmpty())
		return;

	glm::vec3 translate = translate_origin + translate_add;
	glm::vec3 scale = scale_origin * scale_add;

	float scale_wnd = 2.0f / width_vp; // ��� ������ ����� ���������� � -1 �� 1
	k_pix_in_mm = scale_wnd / scale.x;


	//�� ����� ��������� ������ ������ ������� ���������� �� ������, ������� ��� ���� ������ ��������� ������ ������.
	//������������� � ������ ��������������, ����� ������� � � ����� ��������

	glm::mat4 mView = glm::lookAt(position - look, position, top);

	glm::mat4 mTrans(1.0f);
	mTrans = glm::translate(mTrans, translate);
	mTrans = glm::scale(mTrans, scale);

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

//	float fscale = scale * 2; //1������� - 1��, ���������� �� ������� �� -1 �� 1
//	glm::mat4 mScale = glm::scale(glm::mat4(1.0f), glm::vec3(fscale / width_vp, fscale / height_vp, 1.f));
	
// 1 ������� == 1 ��, ���������� �� ������� �� -1 �� 1

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glTranslatef(-1.0, -1.0, 0);
	glScalef(2.0 / get_vp_width(), 2.0 / get_vp_height(), 1);
}


//--------------------------------------------------------------------
void Camera::rotate_cursor(int xc, int yc, int xprev, int yprev)
{
	// some magic
//	wxLogMessage("befor: x=%d y=%d xprev=%d yprev=%d look: %f %f %f", xc, yc, xprev,yprev, look.x, look.y, look.z);
	float scl = 5.1f;
	float x = (float(xprev) / width_vp - 0.5) * 2;
	float y = (1 - float(yprev) / height_vp - 0.5) * 2;
	float newX = (float(xc) / width_vp - 0.5) * 2;
	float newY = (1 - float(yc) / height_vp - 0.5) * 2;
	if (newX == x || newY == y)
	{
		// do nothing
		//wxLogMessage("(newX == x || newY == y) == true");
		return;
	}
	float deltaX = scl * (newX - x);
	float deltaY = scl * (newY - y);
	
	glm::vec3 axisX = glm::cross(look, top);
	glm::vec3 axisY = top;
	glm::vec3 axisZ = -look;

	//������� ��� � ������������ ������,
	//����� ��������� � � ���������� ������������
	//� ������������ ������� ������ ������������ ���� ���
	glm::vec3 axisToCursor(x, y, glm::sqrt(glm::abs(1 - x * x - y * y)));
	glm::vec3 cursorOffset(deltaX, deltaY, 0);
	glm::vec3 axis = glm::cross(axisToCursor, cursorOffset);
	glm::vec3 localAxis = axis.x * axisX + axis.y * axisY + axis.z * axisZ;

	glm::mat4 rotation(1.0f);
	rotation = glm::rotate(rotation, glm::sqrt(deltaX*deltaX + deltaY * deltaY), localAxis);

	look = glm::vec3(glm::vec4(look, 0) * rotation);
	//position = glm::vec3(glm::vec4(position,0) * rotation);
	top = glm::vec3(glm::vec4(top, 0) * rotation);
	//wxLogMessage("after: x=%d y=%d xprev=%d yprev=%d look: %f %f %f", xc, yc, xprev, yprev, look.x, look.y, look.z);
	
}

//--------------------------------------------------------------------
void Camera::set_view(View view)
{
	glm::vec3 x(1, 0, 0), y(0, 1, 0), z(0, 0, 1);
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
	update_scale();
	reset_matrix(scale_add);
}

void Camera::update_scale()
{
	wxASSERT(box.Max.x != box.Min.x);
	wxASSERT(box.Max.y != box.Min.y);
	//wxASSERT(box.Max.z != box.Min.z);
	// box must be in [-1;1] range
	float k_view = 1;
	if (height_vp != 0)
		k_view = float(width_vp) / float(height_vp);


	if (k_view < 1)
	{
		scale_origin.x = (2.0f / (box.Max.x - box.Min.x));
		scale_origin.y = k_view * scale_origin.x;
		scale_origin.z = scale_origin.y;
	}
	else
	{
		scale_origin.y = (2.0f / (box.Max.y - box.Min.y));
		scale_origin.x = scale_origin.y / k_view;;
		scale_origin.z = scale_origin.x;
	}
	//scale_origin.z = box.Max.z != box.Min.z ? 2.0f / (box.Max.z - box.Min.z) : glm::min(scale_origin.x, scale_origin.y);

	//scale_origin.z =  glm::min(scale_origin.x, scale_origin.y);
	scale_add = 0.9f;
	float xcenter = box.Max.x / 2.0f + box.Min.x / 2.0f;
	float ycenter = box.Max.y / 2.0f + box.Min.y / 2.0f;
	float zcenter = box.Max.z / 2.0f + box.Min.z / 2.0f;
	
	//glm::vec3 center = -1*glm::vec3(box.Max.x / 2.0f + box.Min.x / 2.0f, box.Max.y / 2.0f + box.Min.y / 2.0f, box.Max.z / 2.0f + box.Min.z / 2.0f);
	//translate_origin = glm::scale()
	
	
	translate_origin = glm::vec3(-xcenter * scale_origin.x*scale_add, -ycenter * scale_origin.y*scale_add, -zcenter * scale_origin.z*scale_add);
}


void Camera::set_viewport(int width, int height)
{
	width_vp = width;             // viewport 
	height_vp = height;
	update_scale();
	//k_view = float(width_vp) / float(height_vp);
}
