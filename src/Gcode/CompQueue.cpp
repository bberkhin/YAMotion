#include "CompQueue.h"
#include "gcodeerrors.h"


using namespace Interpreter;

CompQueue::CompQueue(IExecutor *ix, RunnerData  *rd_) :
	executor(ix), rd(rd_), endpoint_valid(false)
{
	endpoint[0] = endpoint[1] = 0.0;
}


CompQueue::~CompQueue()
{

}



double CompQueue::latheorigin_x( double x) 
{
	int o = 0;// rd->cutter_comp_orientation;
	double r = rd->cutter_comp_radius;
	if (rd->plane != Plane_XZ) return x;

	if (o == 2 || o == 6 || o == 1) x -= r;
	if (o == 3 || o == 8 || o == 4) x += r;
	return x;
}

double CompQueue::latheorigin_z(double z) 
{
	int o = 0;// rd->cutter_comp_orientation;
	double r = rd->cutter_comp_radius;
	if (rd->plane != Plane_XZ) return z;

	if (o == 2 || o == 7 || o == 3) z -= r;
	if (o == 1 || o == 5 || o == 4) z += r;
	return z;
}


void CompQueue::enqueue_straight_feed(
	double dx, double dy, double dz,
	double x, double y, double z, double a, double b, double c)
{
	queued_canon q;
	q.type = QSTRAIGHT_FEED;

	switch (rd->plane) 
	{
	case Plane_XY:
		q.data.straight_feed.dx = dx;
		q.data.straight_feed.dy = dy;
		q.data.straight_feed.dz = dz;
		q.data.straight_feed.x = x;
		q.data.straight_feed.y = y;
		q.data.straight_feed.z = z;
		break;
	case Plane_XZ:
		q.data.straight_feed.dz = dx;
		q.data.straight_feed.dx = dy;
		q.data.straight_feed.dy = dz;
		q.data.straight_feed.z = x;
		q.data.straight_feed.x = y;
		q.data.straight_feed.y = z;
		break;
	default:
		break;
	}
	q.data.straight_feed.a = a;
	q.data.straight_feed.b = b;
	q.data.straight_feed.c = c;
	qc.push_back(q);
}

void CompQueue::enqueue_straight_traverse(
	double dx, double dy, double dz,
	double x, double y, double z, double a, double b, double c)
{
	queued_canon q;
	q.type = QSTRAIGHT_TRAVERSE;

	switch (rd->plane)
	{
	case Plane_XY:
		q.data.straight_traverse.dx = dx;
		q.data.straight_traverse.dy = dy;
		q.data.straight_traverse.dz = dz;
		q.data.straight_traverse.x = x;
		q.data.straight_traverse.y = y;
		q.data.straight_traverse.z = z;
		break;
	case Plane_XZ:
		q.data.straight_traverse.dz = dx;
		q.data.straight_traverse.dx = dy;
		q.data.straight_traverse.dy = dz;
		q.data.straight_traverse.z = x;
		q.data.straight_traverse.x = y;
		q.data.straight_traverse.y = z;
		break;
	default:
		break;
	}
	q.data.straight_traverse.a = a;
	q.data.straight_traverse.b = b;
	q.data.straight_traverse.c = c;
	qc.push_back(q);
}
void CompQueue::enqueue_arc_feed(
	double original_turns,
	double end1, double end2, double center1, double center2,
	int turn, double end3, double a, double b, double c)
{
	queued_canon q;
	q.type = QARC_FEED;
	q.data.arc_feed.original_turns = original_turns;
	q.data.arc_feed.end1 = end1;
	q.data.arc_feed.end2 = end2;
	q.data.arc_feed.center1 = center1;
	q.data.arc_feed.center2 = center2;
	q.data.arc_feed.turn = turn;
	q.data.arc_feed.end3 = end3;
	qc.push_back(q);
}

void CompQueue::set_endpoint(double x, double y)
{
	endpoint[0] = x; endpoint[1] = y;
	endpoint_valid = true;
}

void CompQueue::dequeue_canons()
{
	endpoint_valid = false;

	if (qc.empty()) return;
	Coords pos;
	double tmp = 0;
	for (unsigned int i = 0; i < qc.size(); i++) 
	{
		queued_canon &q = qc[i];

		switch (q.type) 
		{
		case QARC_FEED:
			pos.x = latheorigin_z(q.data.arc_feed.end1);
			pos.y = latheorigin_z(q.data.arc_feed.end2);
			pos.z = latheorigin_z(q.data.arc_feed.center1);
			pos.a = latheorigin_x(q.data.arc_feed.center2);
			executor->arc_feed(rd,
				pos.x, pos.y, pos.z, pos.a,
				q.data.arc_feed.turn,
				q.data.arc_feed.end3,
				q.data.arc_feed.a, q.data.arc_feed.b, q.data.arc_feed.c, tmp, tmp );
			break;
		case QSTRAIGHT_FEED:
			pos.a = q.data.straight_feed.a;
			pos.b = q.data.straight_feed.b;
			pos.c = q.data.straight_feed.c;
			pos.x = latheorigin_x(q.data.straight_feed.x);
			pos.y = q.data.straight_feed.y;
			pos.z = latheorigin_z(q.data.straight_feed.z);
			executor->straight_feed(pos);
			break;
		case QSTRAIGHT_TRAVERSE:
			pos.a = q.data.straight_feed.a;
			pos.b = q.data.straight_feed.b;
			pos.c = q.data.straight_feed.c;
			pos.x = latheorigin_x(q.data.straight_traverse.x);
			pos.y = q.data.straight_traverse.y;
			pos.z =	latheorigin_z(q.data.straight_traverse.z);
			executor->straight_traverce(pos);
			break;
		}
	}
	qc.clear();
}

bool CompQueue::move_endpoint_and_flush(double x, double y)
{
	double x1;
	double y1;
	double x2;
	double y2;
	double dot;

	if (qc.empty()) return true;

	for (unsigned int i = 0; i < qc.size(); i++) {
		// there may be several moves in the queue, and we need to
		// change all of them.  consider moving into a concave corner,
		// then up and back down, then continuing on.  there will be
		// three moves to change.

		queued_canon &q = qc[i];

		switch (q.type) 
		{
		case QARC_FEED:
			double r1, r2, l1, l2;
			r1 = hypot(q.data.arc_feed.end1 - q.data.arc_feed.center1,
				q.data.arc_feed.end2 - q.data.arc_feed.center2);
			l1 = q.data.arc_feed.original_turns;
			q.data.arc_feed.end1 = x;
			q.data.arc_feed.end2 = y;
			r2 = hypot(x - q.data.arc_feed.center1,
				y - q.data.arc_feed.center2);
			l2 = find_turn(endpoint[0], endpoint[1],
				q.data.arc_feed.center1, q.data.arc_feed.center2,
				q.data.arc_feed.turn,
				x, y);
		
			if (fabs(r1 - r2) > .01)
				RET_F_SETSTATE(PARAMETER_ERROR, YA_CUTER_COMP_INVALID_ARC, r1, r2);
			if (l1 && endpoint_valid && fabs(l2) > (fabs(l1) + 0.0254)) 
			{
				RET_F_SETSTATE(PARAMETER_ERROR, YA_CUTER_COMP_ARC_MOVE);
			}
			q.data.arc_feed.end1 = x;
			q.data.arc_feed.end2 = y;
			break;
		case QSTRAIGHT_TRAVERSE:
			if (rd->plane == Plane_XY)
			{
				x1 = q.data.straight_traverse.dx; // direction of original motion
				y1 = q.data.straight_traverse.dy;
				x2 = x - endpoint[0];         // new direction after clipping
				y2 = y - endpoint[1];
			}
			else if (rd->plane == Plane_XZ)
			{
				x1 = q.data.straight_traverse.dz; // direction of original motion
				y1 = q.data.straight_traverse.dx;
				x2 = x - endpoint[0];         // new direction after clipping
				y2 = y - endpoint[1];
			}
			else
			{
				RET_F_SETSTATE(PARAMETER_ERROR, YA_CUTER_COMP_UNSUPPORTED_PLANE);
			}
			dot = x1 * x2 + y1 * y2; // not normalized; we only care about the angle
			if (endpoint_valid && dot < 0) {
				// oops, the move is the wrong way.  this means the
				// path has crossed because we backed up further
				// than the line is long.  this will gouge.
				RET_F_SETSTATE(PARAMETER_ERROR, YA_CUTER_COMP_STRAIGHT_TRAVERSE);
			}
			if (rd->plane == Plane_XY)
			{
				q.data.straight_traverse.x = x;
				q.data.straight_traverse.y = y;
			}
			else //Plane_XZ:
			{
				q.data.straight_traverse.z = x;
				q.data.straight_traverse.x = y;
			}
			break;
		case QSTRAIGHT_FEED:
			if (rd->plane == Plane_XY)
			{
				x1 = q.data.straight_feed.dx; // direction of original motion
				y1 = q.data.straight_feed.dy;
				x2 = x - endpoint[0];         // new direction after clipping
				y2 = y - endpoint[1];
			}
			else if (rd->plane == Plane_XZ)
			{
				x1 = q.data.straight_feed.dz; // direction of original motion
				y1 = q.data.straight_feed.dx;
				x2 = x - endpoint[0];         // new direction after clipping
				y2 = y - endpoint[1];
			}
			else
			{
				RET_F_SETSTATE(PARAMETER_ERROR, YA_CUTER_COMP_UNSUPPORTED_PLANE);
			}

			dot = x1 * x2 + y1 * y2;
			if (endpoint_valid && dot < 0) 
			{
				// oops, the move is the wrong way.  this means the
				// path has crossed because we backed up further
				// than the line is long.  this will gouge.
				RET_F_SETSTATE(PARAMETER_ERROR, YA_CUTER_COMP_STRAIGHT_FEED );
			}
			if (rd->plane == Plane_XY)
			{
				q.data.straight_feed.x = x;
				q.data.straight_feed.y = y;
			}
			else if (rd->plane == Plane_XZ)
			{				
				q.data.straight_feed.z = x;
				q.data.straight_feed.x = y;
			}
			break;
		default: 	break;
		}
	}
	dequeue_canons();
	set_endpoint(x, y);
	return true;
}

double CompQueue::find_turn(double x1,      //!< X-coordinate of start point       
	double y1,      //!< Y-coordinate of start point       
	double center_x,        //!< X-coordinate of arc center        
	double center_y,        //!< Y-coordinate of arc center        
	int turn,       //!< no. of full or partial circles CCW
	double x2,      //!< X-coordinate of end point         
	double y2)      //!< Y-coordinate of end point         
{
	double alpha;                 /* angle of first radius */
	double beta;                  /* angle of second radius */
	double theta;                 /* amount of turn of arc CCW - negative if CW */

	if (turn == 0)
		return 0.0;
	alpha = atan2((y1 - center_y), (x1 - center_x));
	beta = atan2((y2 - center_y), (x2 - center_x));
	if (turn > 0) {
		if (beta <= alpha)
			beta = (beta + (2 * M_PIl));
		theta = ((beta - alpha) + ((turn - 1) * (2 * M_PIl)));
	}
	else {                      /* turn < 0 */

		if (alpha <= beta)
			alpha = (alpha + (2 * M_PIl));
		theta = ((beta - alpha) + ((turn + 1) * (2 * M_PIl)));
	}
	return (theta);
}