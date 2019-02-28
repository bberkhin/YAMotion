#pragma once
#include <vector>
#include "iexecutor.h"
#include "gcodedefs.h"


namespace Interpreter
{

	enum queued_canon_type {
		QSTRAIGHT_TRAVERSE, QSTRAIGHT_FEED, QARC_FEED, QSET_FEED_RATE, QDWELL, QSET_FEED_MODE,
		QMIST_ON, QMIST_OFF, QFLOOD_ON, QFLOOD_OFF,
		QSTART_SPINDLE_CLOCKWISE, QSTART_SPINDLE_COUNTERCLOCKWISE, QSTOP_SPINDLE_TURNING,
		QSET_SPINDLE_MODE, QSET_SPINDLE_SPEED,
		QCOMMENT, QM_USER_COMMAND, QSTART_CHANGE,
		QORIENT_SPINDLE, QWAIT_ORIENT_SPINDLE_COMPLETE
	};

	struct straight_traverse 
	{
		double dx, dy, dz;          // direction of original motion
		double x, y, z, a, b, c;
	};

	struct straight_feed 
	{
		double dx, dy, dz;          // direction of original motion
		double x, y, z, a, b, c;
	};

	struct arc_feed 
	{
		double original_turns;
		double end1, end2, center1, center2;
		int turn;
		double end3, a, b, c;		
	};

	struct queued_canon
	{
		queued_canon_type type;
		union {
			struct straight_traverse straight_traverse;
			struct straight_feed straight_feed;
			struct arc_feed arc_feed;
		} data;
	};

	class CompQueue
	{
	public:
		CompQueue(IExecutor *ix, RunnerData  *rd_);
		~CompQueue();

		void enqueue_straight_feed(
			double dx, double dy, double dz,
			double x, double y, double z, double a, double b, double c);
		void enqueue_straight_traverse(
			double dx, double dy, double dz,
			double x, double y, double z, double a, double b, double c);
		void enqueue_arc_feed(
			double original_arclen,
			double end1, double end2, double center1, double center2,
			int turn, double end3, double a, double b, double c);
		void dequeue_canons();
		void set_endpoint(double x, double y);
		bool move_endpoint_and_flush(double x, double y);
		queued_canon &front() { return qc.front(); }
		bool empty() { return qc.empty(); }
		InterError get_state() const { return state; }
	private:
		double latheorigin_x(double x);
		double latheorigin_z(double z);
		double find_turn(double x1, double y1, double center_x,
			double center_y, int turn, double x2, double y2);
	private:

		double endpoint[2];
		bool endpoint_valid;
		RunnerData  *rd;
		std::vector<queued_canon> qc;
		IExecutor *executor; //устройство, которое исполняет команды   
		InterError state;
	};

};