#pragma once

#include "logconsole.h"
#include <vector>
//#include "CoordMotion.h"
#include <glm/glm.hpp>
#include "ienvironment.h"

struct TrackPointGL
{
	bool isFast;
	int line;
	int speed;// mm to min
	glm::vec3 position;
};

typedef std::vector<TrackPointGL> TrackPoints;

class ExecutorView : public ExecutorLog
{
public:
	ExecutorView(ILogger *_logger, IEnvironment *penv);
	~ExecutorView();

	void arc_feed(RunnerData *rd, double &end1, double &end2, double &center1, double &center2, int turn, double &end3, double &AA_end, double &BB_end, double &CC_end, double &u, double &v);
	void set_feed_rate(double feed);
	TrackPoints &getTrack() { return m_points; }
protected:
	virtual void addTrackPoint(TypeMove type, const Coords &pt);
	virtual void output(const std::string &str);
	virtual void output(const std::string &str, const Coords &position);
	void ArcFeed(Plane plane,
		double first_end, double second_end,
		double first_axis, double second_axis, int rotation,
		double axis_end_point, double a, double b, double c);
private:
	ILogger *logger;
	TrackPoints m_points;
	double m_current_feed;
	double m_fast_speed;

	//CCoordMotion *pcm;
};

