#pragma once

#include "logconsole.h"
#include <vector>

struct TrackPoint
{
	TypeMove type;
	Coords pt;
};

class ExecutorView : public ExecutorLog
{
public:
	ExecutorView(wxEvtHandler *_logger);
    
	std::vector<TrackPoint> *getTrack() { return &trj; }
protected:
	virtual void addTrackPoint(TypeMove type, const Coords &pt);
	virtual void output(const std::string &str);
	virtual void output(const std::string &str, const Coords &position);
private:
	wxEvtHandler *logger;
	std::vector<TrackPoint> trj;
};

