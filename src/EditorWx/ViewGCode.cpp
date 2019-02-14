#include "wx/wx.h"


#if !wxUSE_GLCANVAS
#error "OpenGL required: set wxUSE_GLCANVAS to 1 and rebuild the library"
#endif

#include <wx/timer.h>
#include <wx/math.h>
#include "ViewGCode.h"

#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtx/transform.hpp>

void make_cylinder(Object3d& edge, int divs); //из границы в плоскости XZ создаЄт объект вращени¤ вокруг z
void make_tool_simple(Object3d& tool); //создаeт объект сверло

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

	m_zoneWidth = 2000;
	m_zoneHeight = 1000;
	m_zoneTop = 300;

	m_gridStep = 100;
	m_showGrid = true;

	camera.scale = 1;
	camera.position = glm::vec3(0, 0, 0);  //находится сверху
	camera.look = glm::vec3(0, 0, -1); //смотрит вниз
	camera.top = glm::vec3(0, 1, 0);  //смотрит ровно

//	m_lastMousePosition = QPoint(0, 0);
//	m_mousePressed = false;

	m_windowWidth = 0;
	m_windowHeight = 0;

	make_tool_simple(tool); //делаем квадратное сверло )
	for (int i = 0; i < 90000; ++i)
	{
		glm::vec3 val(5, 5, 5);
		realTrack.push_back(val);
	}

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

	/*getVertexArray();
	getColorArray();
	getIndexArray();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);*/
}

void ViewGCode::recalc_matrices()
{
	camera.recalc_matrix(m_windowWidth, m_windowHeight);
}

void ViewGCode::resizeGL(int nWidth, int nHeight)
{
	m_windowWidth = nWidth;
	m_windowHeight = nHeight;

	glViewport(0, 0, nWidth, nHeight);

	glMatrixMode(GL_PROJECTION);

	//recalc_matrices();
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

	glColor3f(0.0, 1.0, 1.0);

	/*glBegin(GL_POINTS);
		glVertex2f(0.05,0.05);
		glVertex2f(0.5,0.5);
	glEnd();*/

	initializeGL();
	recalc_matrices();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	draw_bounds();
	draw_3d_grid();
	draw_track();
	draw_real_track();
	tool.draw();
	glDisable(GL_DEPTH_TEST);

	camera.screen_matrix(m_windowWidth, m_windowHeight);

	if (m_showGrid)
		draw_grid();
	draw_fps();
	
	//if (hasFocus())
		draw_border();
	
	glFlush();
	SwapBuffers();
}

void ViewGCode::OnSize(wxSizeEvent& event)
{
	if (!IsShownOnScreen())
		return;
	// This is normally only necessary if there is more than one wxGLCanvas
	// or more than one wxGLContext in the application.
	SetCurrent(*m_glRC);

	resizeGL(event.GetSize().x, event.GetSize().y);
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


void ViewGCode::setBox(const CoordsBox &bx)
{
	box = bx; 	
	Update();
}

void ViewGCode::setTrack(std::vector<TrackPoint> *ptr)
{
	std::vector<TrackPointGL> &tr = track;
	int i = 0;
	tr.resize(ptr->size());
	std::for_each(ptr->begin(), ptr->end(), // lambda
		[&tr,&i](TrackPoint &p) {  
		tr[i].isFast = p.type == fast ? true : false;
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
	//renderText(5, 20, text, font);
}

//--------------------------------------------------------------------
void ViewGCode::draw_track()
{
	glBegin(GL_LINES);
	for (size_t i = 1; i < track.size(); ++i)
	{
		if (track[i].isFast)
		{
			//continue;
			glColor4f(0.3f, 0.1f, 0.0f, 1.0f);
		}
		else
			glColor3f(0.1f, 0.3f, 0.0f);
		glVertex3f(track[i - 1].position.x, track[i - 1].position.y, track[i - 1].position.z);
		glVertex3f(track[i].position.x, track[i].position.y, track[i].position.z);
	}
	glEnd();

	glBegin(GL_POINTS);
	glColor3f(0.7f, 0.2f, 0.9f);
	glPointSize(3.0f);
	for (size_t i = 0; i < track.size(); ++i)
	{
		glVertex3f(track[i].position.x, track[i].position.y, track[i].position.z);
	}
	glEnd();
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
void ViewGCode::draw_bounds()
{
	glColor3f(0.0f, 0.3f, 0.3f);

	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(m_zoneWidth, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, m_zoneHeight, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, -m_zoneTop);

	glVertex3f(m_zoneWidth, 0, 0);
	glVertex3f(m_zoneWidth, m_zoneHeight, 0);
	glVertex3f(m_zoneWidth, 0, 0);
	glVertex3f(m_zoneWidth, 0, -m_zoneTop);

	glVertex3f(0, m_zoneHeight, 0);
	glVertex3f(m_zoneWidth, m_zoneHeight, 0);
	glVertex3f(0, m_zoneHeight, 0);
	glVertex3f(0, m_zoneHeight, -m_zoneTop);

	glVertex3f(0, 0, -m_zoneTop);
	glVertex3f(m_zoneWidth, 0, -m_zoneTop);
	glVertex3f(0, 0, -m_zoneTop);
	glVertex3f(0, m_zoneHeight, -m_zoneTop);

	glVertex3f(m_zoneWidth, m_zoneHeight, 0);
	glVertex3f(m_zoneWidth, m_zoneHeight, -m_zoneTop);
	glVertex3f(m_zoneWidth, 0, -m_zoneTop);
	glVertex3f(m_zoneWidth, m_zoneHeight, -m_zoneTop);
	glVertex3f(0, m_zoneHeight, -m_zoneTop);
	glVertex3f(m_zoneWidth, m_zoneHeight, -m_zoneTop);
	glEnd();
}

//--------------------------------------------------------------------
void ViewGCode::draw_3d_grid()
{
	glColor3f(0.3f, 0.0f, 0.0f);

	glBegin(GL_LINES);
	for (float x = 0; x < m_zoneWidth; x += m_gridStep)
	{
		glVertex3f(x, 0, -m_zoneTop);
		glVertex3f(x, m_zoneHeight, -m_zoneTop);
	}

	for (float y = 0; y < m_zoneHeight; y += m_gridStep)
	{
		glVertex3f(0, y, -m_zoneTop);
		glVertex3f(m_zoneWidth, y, -m_zoneTop);
	}
	glEnd();
}

//--------------------------------------------------------------------
void ViewGCode::draw_grid()
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
	glScalef(2.0 / m_windowWidth, 2.0 / m_windowHeight, 1);

	int borderSize = 3;
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < borderSize; ++i)
	{
		float offset = i + 0.5f;
		glVertex2f(offset, offset);
		glVertex2f(m_windowWidth - offset, offset);
		glVertex2f(m_windowWidth - offset, m_windowHeight - offset);
		glVertex2f(offset, m_windowHeight - offset);
		glVertex2f(offset, offset);
	}
	glEnd();
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
		if (realTrack.size() > maximum + tail)
		{
			realTrack.erase(realTrack.begin(), realTrack.begin() + tail);
		}
	}
	
	//update();
}

//--------------------------------------------------------------------
void ViewGCode::set_view(View view)
{
	glm::vec3 x(1, 0, 0), y(0, 1, 0), z(0, 0, 1);

	switch (view)
	{
		case View::TOP: camera.look = -z; camera.top = y; break;
		case View::BOTTOM: camera.look = z; camera.top = -y; break;
		case View::LEFT: camera.look = x; camera.top = z; break;
		case View::RIGHT: camera.look = -x; camera.top = z; break;
		case View::FRONT: camera.look = y; camera.top = z; break;
		case View::BACK: camera.look = -y; camera.top = z; break;
	}

	Update();
}

//--------------------------------------------------------------------
void Camera::recalc_matrix(int width, int height)
{
	glm::mat4 mView = glm::lookAt(position - look,
		position,
		top);

	float fscale = scale * 2; //1пиксель - 1мм, координаты на виджете от -1 до 1
	glm::mat4 mScale = glm::scale(glm::mat4(), glm::vec3(fscale / width, fscale / height, 1.f));

	//float angle = glm::pi<float>()/40;
	//glm::mat4 mProj  = glm::perspective(angle, 1.0f, 0.0f, 10000.0f);
	glm::mat4 mProj = glm::ortho(-1.f, 1.f, -1.f, 1.f, -1000.f, 10000.f);

	//сначала располагаем объекты перед камерой
	//потом масштабируем по размеру окна
	//и считаем искривление перспективы
	viewProjection = mProj * mScale * mView;

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(viewProjection));
}

//--------------------------------------------------------------------
void Camera::screen_matrix(int width, int height)
{
	float fscale = scale * 2; //1пиксель - 1мм, координаты на виджете от -1 до 1
	glm::mat4 mScale = glm::scale(glm::mat4(), glm::vec3(fscale / width, fscale / height, 1.f));

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(mScale));
}

//--------------------------------------------------------------------
void Camera::rotate_cursor(float x, float y, float deltaX, float deltaY)
{
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

	glm::mat4 rotation;
	rotation = glm::rotate(rotation, glm::sqrt(deltaX*deltaX + deltaY * deltaY), localAxis);

	look = glm::vec3(glm::vec4(look, 0) * rotation);
	//position = glm::vec3(glm::vec4(position,0) * rotation);
	top = glm::vec3(glm::vec4(top, 0) * rotation);
}

//--------------------------------------------------------------------
void Object3d::draw()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);

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
			glm::vec4 color(i % 2 * 0.2 + 0.4, 0, 0, 0.1f);
			Vertex to(pos, color);

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
	tool.ortX = glm::vec3(1, 0, 0);
	tool.ortY = glm::vec3(0, 1, 0);
	tool.indices.clear();
	tool.verts.clear();
	tool.position = glm::vec3(0, 0, 0);

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