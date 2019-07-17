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

class View3D : public wxGLCanvas
{
	friend class SimulateCutting;
public:
	View3D(wxWindow *parent,
		wxWindowID id = wxID_ANY,
		int *gl_attrib = NULL);

	virtual ~View3D();

	void setTrack(TrackPoints &tr);
	void setBox(const CoordsBox &bx);
	bool IsEmpty() { return track.empty(); }
	void clear();
	void setSimulationSpeed(double mm_per_sec);
	void setSimulationPos(int index, const TrackPointGL &endpt = TrackPointGL());
	TrackPoints &getTrack() { return track; }
	
	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnChar(wxKeyEvent& event);
	void OnMouseEvent(wxMouseEvent& event);
	void initializeGL();

//command
	void DoSetView(View stdview);
	void OnSetShow(wxCommandEvent &event);
	void OnSetShowUpdate(wxUpdateUIEvent& event);


private:
	void load_config();
	void save_config();
	void resizeGL(int nWidth, int nHeight);
	void draw_bounds();
	void draw_3d_grid();
	void draw_grid();
	void draw_track();
	void draw_border();
	void draw_axis();
	void draw_axis_letters();
	void update_tool_coords(float x, float y, float z);
	void print_string(const glm::vec4 &color, int x, int y, char *s, int len);
	
private:
	wxWindow *appframe;
	wxGLContext* m_glRC;
	TrackPoints track;
	std::vector<glm::vec3> realTrack; //пройденна¤ фрезой траектори¤

	bool   show2dGrid;
	bool   showbounds;
	bool   show3dGrid;
	bool   showTool;
	bool   showAxis;

	float  m_gridStep;   //размер ¤чейки сетки
	
	Camera camera;
    Object3d tool;
	Object3d axisX;
	Object3d axisY;
	Object3d axisZ;

	// sinulation stuff
	size_t simulateLastIndex;
	TrackPointGL end_simulate_point;
	GLuint fontOffset;
	glm::vec3 m_bgcolor;

	wxDECLARE_NO_COPY_CLASS(View3D);
	wxDECLARE_EVENT_TABLE();
};

