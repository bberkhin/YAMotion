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
	int line;
	glm::vec3 position;
};

enum View
{
	TOP = 0,
	BOTTOM,
	LEFT,
	RIGHT,
	FRONT,
	BACK,
	ISOMETR
};

class Camera
{
public:
	Camera();
	void recalc_matrix();     //пересчитать матрицу проекции
	void screen_matrix();     //вывод 2d графики
	void set_viewport(int width, int height);
	void rotate_cursor(int xc, int yc, int xprev, int yprev); //обработка поворота камеры
	void move_scale_cursor(int x, int y, float delta);
	void move_drag_cursor(int deltaX, int deltaY);
	void set_view(View view);
	void increase_scale(float dscl);
	float mm_to_pix(float valmm);
	float pix_to_mm(float pix);
	void set_box(const CoordsBox &bx);
	int get_vp_width() {return width_vp;	}
	int get_vp_height() { return height_vp; }
	CoordsBox &get_box() { return box; }
	const glm::mat4 &get_projection() {	return viewProjection; }
private:
	void reset_matrix(float scale_add_);
	void update_scale();
private:
	//float     scale_origin;          //масштаб изображени¤
	glm::vec3  scale_origin;
	float     k_view;
	glm::vec3 translate_origin;      //текущий сдвиг
	float  scale_add;
	glm::vec3 translate_add;
	float k_pix_in_mm;

	glm::vec3 position;       //где находитс¤ камера
	glm::vec3 look;           //нормализованный вектор взгл¤да
	glm::vec3 top;            //вектор ориентации камеры
	     
//	float     screenAngle;    //поворот экрана
	glm::mat4 viewProjection; //матрица камеры
	int width_vp;             // viewport 
	int height_vp;			  // viewport 
	CoordsBox box;
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
	glm::vec3           position; //положение
	glm::vec3           rotate;     //ориентаци¤
	float				angle;
	glm::vec3           scale;     //ориентаци¤
	std::vector<Vertex> verts;    //вершины
	std::vector<int>    indices;  //треугольники

	void draw(); //нарисовать треугольники
};


class SimulateCutting;

class ViewGCode : public wxGLCanvas
{
	friend class SimulateCutting;
public:
	ViewGCode(wxWindow *frame, wxWindow *parent,
		wxWindowID id = wxID_ANY,
		int *gl_attrib = NULL);

	virtual ~ViewGCode();

	//void setTrack(std::vector<TrackPointGL> *ptr) { track.assign( ptr->begin(), ptr->end() ); }
	void setTrack(std::vector<TrackPoint> *ptr);	
	void setBox(const CoordsBox &bx);
	void clear();
	void processClosing();
	void setSimulationSpeed(double mm_per_sec);
	
	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnChar(wxKeyEvent& event);
	void OnMouseEvent(wxMouseEvent& event);
	void initializeGL();
//command
	void OnSetView(wxCommandEvent &event);
	void OnSemulateStart(wxCommandEvent &event);
	void OnSemulatePause(wxCommandEvent &event);
	void OnSemulateStop(wxCommandEvent &event);
	void OnSimulateUpdate(wxThreadEvent&);
	void OnSimulateCompletion(wxThreadEvent&);
	void OnSetViewUpdate(wxUpdateUIEvent& event);
	void OnCmdUpdateSimulateStart(wxUpdateUIEvent& event);
	void OnCmdUpdateSimulateStop(wxUpdateUIEvent& event);
	void OnCmdUpdateSimulatePause(wxUpdateUIEvent& event);



private:
	void resizeGL(int nWidth, int nHeight);
	void draw_bounds();
	void draw_3d_grid();
	void draw_grid();
	void draw_track();
	void draw_real_track();
	void draw_border();
	void draw_axis();
	void draw_axis_letters();
	void update_tool_coords(float x, float y, float z);
	void print_string(const glm::vec4 &color, int x, int y, char *s, int len);
	std::vector<TrackPointGL> &getTrack() { return track; }
	int get_tick_delay() { return tickdelay; }
	double get_tick_distance() { return distancefortick; }
	
	//int tickdelay = 50;
	//double distancefortick = 5.f;
	
private:
	wxWindow *appframe;
	wxGLContext* m_glRC;
	std::vector<TrackPointGL> track;
	std::vector<glm::vec3> realTrack; //пройденна¤ фрезой траектори¤

	bool   m_showGrid;   //показывать ли сетку масштаба
	float  m_gridStep;   //размер ¤чейки сетки
	
	Camera camera;
    Object3d tool;
	Object3d axisX;
	Object3d axisY;
	Object3d axisZ;

	// sinulation stuff
	SimulateCutting *simulateCut;
	size_t simulateLastIndex;
	int cur_gcode_line;
	TrackPointGL end_simulate_point;
	wxCriticalSection critsect;
	int tickdelay;
	double distancefortick;
	GLuint fontOffset;
	

	wxDECLARE_NO_COPY_CLASS(ViewGCode);
	wxDECLARE_EVENT_TABLE();
};

