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

#include <wx/glcanvas.h>

#include <glm/glm.hpp>


#include "ExecutorView.h"


struct TrackPointGL
{
	bool isFast;
	glm::vec3 position;
};

enum View
{
	TOP = 0,
	BOTTOM,
	LEFT,
	RIGHT,
	FRONT,
	BACK
};

struct Camera
{
	float     scale;          //������� ����������
	glm::vec3 position;       //��� �������� ������
	glm::vec3 look;           //��������������� ������ ������
	glm::vec3 top;            //������ ���������� ������
	glm::vec3 translate;       //������ ���������� ������
	float     screenAngle;    //������� ������
	glm::mat4 viewProjection; //������� ������

	void recalc_matrix(int width, int height);     //����������� ������� ��������
	void rotate_cursor(float x, float y, float deltaX, float deltaY); //��������� �������� ������
	void screen_matrix(int width, int height);     //����� 2d �������
};

struct Vertex
{
	glm::vec3 position;
	glm::vec4 color;

	Vertex(glm::vec3 _position, glm::vec4 _color) :
		position(_position), color(_color) {};
};

struct Object3d
{
	glm::vec3           position; //���������
	glm::vec3           ortX;     //���������
	glm::vec3           ortY;
	std::vector<Vertex> verts;    //�������
	std::vector<int>    indices;  //������������

	void draw(); //���������� ������������
};



class ViewGCode : public wxGLCanvas
{
public:
	ViewGCode(wxWindow *parent,
		wxWindowID id = wxID_ANY,
		int *gl_attrib = NULL);

	virtual ~ViewGCode();

	//void setTrack(std::vector<TrackPointGL> *ptr) { track.assign( ptr->begin(), ptr->end() ); }
	void setTrack(std::vector<TrackPoint> *ptr);	
	void setBox(const CoordsBox &bx);
	
	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnChar(wxKeyEvent& event);
	void OnMouseEvent(wxMouseEvent& event);
	void initializeGL();
//command
	void OnSetView(wxCommandEvent &event);

private:
	void resizeGL(int nWidth, int nHeight);
	void move_scale_cursor(int x, int y, float delta);
	void move_drag_cursor(int x, int y, int deltaX, int deltaY);
	void recalc_matrices();
	void draw_bounds();
	void draw_3d_grid();
	void draw_grid();
	void draw_track();
	void draw_real_track();
	void draw_border();
	void draw_fps();
	void set_view(View view);
	void update_tool_coords(float x, float y, float z);

private:
	wxGLContext* m_glRC;
	
	std::vector<TrackPointGL> track;
	std::vector<glm::vec3> realTrack; //��������� ������ ���������
	
	CoordsBox box;
	int    m_windowWidth;  //������� ����
	int    m_windowHeight;

	float  m_zoneWidth;  //������� ���� ������
	float  m_zoneHeight;
	float  m_zoneTop;
	bool   m_showGrid;   //���������� �� ����� ��������
	float  m_gridStep;   //������ ������ �����
	
	float  scale_add;
	Camera camera;
    Object3d tool;
    int _drawCalls; //������� ��������� �� ��������� �������
    int _fps;

	wxDECLARE_NO_COPY_CLASS(ViewGCode);
	wxDECLARE_EVENT_TABLE();
};

