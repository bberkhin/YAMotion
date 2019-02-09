#pragma once
#include <list>
#include <queue>
#include <memory>
#include "stdint.h"
#include <optional>


//#define NUM_AXES   4 //сколько осей используем (координаты плюс подчиненные им оси)
#define MAX_AXES   6 //сколько всего есть осей на контроллере
#define MAX_FEED_RATE 10000
#define MAX_SPINDELSPEED 60000
typedef double coord;//чтобы не путаться, координатный тип введём отдельно
typedef std::optional<double> optdouble;

#define MM_PER_INCHES 2.54
#define PI 3.14159265358979323846


struct Coords   //все координаты устройства
{
	union
	{
		struct
		{
			coord x, y, z, a, b, c;
		};
		struct
		{
			coord r[MAX_AXES];
		};
	};

	Coords() { for (int i = 0; i < MAX_AXES; ++i) r[i] = 0; }
	Coords(const coord &x_, const coord &y_, const coord &z_) :
		x(x_), y(y_), z(z_) {
		for (int i = 3; i < MAX_AXES; ++i) r[i] = 0; // лучше memset
	}
};

struct CoordsBox
{
	Coords Min;
	Coords Max;
	CoordsBox() : empty(true) { }
	CoordsBox(Coords Min, Coords Max) : empty(true) {
		addCoords(Min); addCoords(Max);
	}
	bool isEmpty() { return empty; }
	void setEmpty() { empty = true; }
	void addCoords(const Coords & pt)
	{
		if (empty)
		{
			Min = pt; Max = pt; empty = false;
		}
		else
		{
			for (int i = 0; i < MAX_AXES; ++i) Min.r[i] = std::min(Min.r[i], pt.r[i]);
			for (int i = 0; i < MAX_AXES; ++i) Max.r[i] = std::max(Max.r[i], pt.r[i]);
		}
	}
private:
	bool empty;
};

class IExecutor
{
public:
	virtual ~IExecutor() { }
	virtual void set_current_line(int nu_of_line) = 0;
	virtual void set_feed_rate(double feed) = 0;
	virtual void set_spindle_speed(double speed) = 0;
	virtual void set_css_spindlemode(double &diam, double &speed) = 0;
	virtual void set_regular_spindlemode() = 0;
	virtual void set_tool_change(int toolid) = 0;
	virtual void straight_feed(const Coords &position) = 0;
	virtual void straight_traverce(const Coords &position) = 0;
	virtual void arc_feed(const Coords &position, bool cw) = 0; // пока не знаю что сюда передовать  пусть будет так
	virtual void run_mcode(int id) = 0;
	virtual void set_end_programm() = 0;
	virtual void set_dwell(long millseconds) = 0;
	virtual void process_probe(const Coords &position) = 0;
};



