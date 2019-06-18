#pragma once

#include "logconsole.h"
#include <vector>
//#include "CoordMotion.h"


struct TrackPoint
{
	TypeMove type;
	int line;
	Coords pt;
};

class ExecutorView : public ExecutorLog
{
public:
	ExecutorView(ILogger *_logger);
	~ExecutorView();

	void arc_feed(RunnerData *rd, double &end1, double &end2, double &center1, double &center2, int turn, double &end3, double &AA_end, double &BB_end, double &CC_end, double &u, double &v);

	std::vector<TrackPoint> *getTrack() { return &trj; }
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
	std::vector<TrackPoint> trj;
	//CCoordMotion *pcm;
};

