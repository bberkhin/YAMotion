#include "GCodeInterpreter.h"
#include "cmdparser.h"


using namespace Interpreter;

#pragma warning(disable:4996)


//====================================================================================================
bool  GCodeInterpreter::move_to(int motion, const Coords &position, const CmdParser &parser)
{

	if (motion == G_1)
	{
		IF_T_RET_F_SETSTATE((runner.feed == 0.0), PARAMETER_ERROR, "Ca not do G1 with  zero feed rate");
		IF_T_RET_F_SETSTATE(((runner.feed_mode == FeedMode_UnitPerRevolution) && (runner.spindlespeed == 0.0)), PARAMETER_ERROR, "Can not feed with zero spindle speed in feed per rev mode");
	}

	runner.motion_mode = motion;

	if ((runner.cutter_comp_side) && (runner.cutter_comp_radius > 0.0))    /* radius always is >= 0 */
	{
		IF_T_RET_F_SETSTATE((parser.getGCode(ModalGroup_MODAL_0) == G_53), PARAMETER_ERROR, "Can not use G53 with cutter radius compenstion");

		if (runner.plane == Plane_XZ)
		{
			if (runner.cutter_comp_firstmove)
				IF_F_RET_F(run_straight_comp1(motion, position.z, position.x, position.y, position.a, position.b, position.c));
			else
				IF_F_RET_F(run_straight_comp2(motion, position.z, position.x, position.y, position.a, position.b, position.c));
		}
		else if (runner.plane == Plane_XY)
		{
			if (runner.cutter_comp_firstmove)
				IF_F_RET_F(run_straight_comp1(motion, position.x, position.y, position.z, position.a, position.b, position.c));
			else
				IF_F_RET_F(run_straight_comp2(motion, position.x, position.y, position.z, position.a, position.b, position.c));
		}
		else
			RET_F_SETSTATE(PARAMETER_ERROR, "Invalid plane for cutter compensation");
	}
	else if (motion == G_0)
	{
		executor->straight_traverce(position);
		runner.position = position;
	}
	else if (motion == G_1)
	{
		executor->straight_feed(position);
		runner.position = position;
	}
	else if (motion == G_33)
	{
		RET_F_SETSTATE(PARAMETER_ERROR, "G33 not supported");
	}
	else if (motion == G_33_1)
	{
		RET_F_SETSTATE(PARAMETER_ERROR, "G33.1 not supported");
	}
	else if (motion == G_76)
	{
		RET_F_SETSTATE(PARAMETER_ERROR, "G76 not supported");
	}
	else
	{
		RET_F_SETSTATE(PARAMETER_ERROR, "Undefened motion G%f", motion / 10.);
	}
	return true;
}



/****************************************************************************/

/*! convert_straight_comp1

Returned Value: int
   If any of the following errors occur, this returns the error shown.
   Otherwise, it returns INTERP_OK.
   1. The side is not RIGHT or LEFT:
	  NCE_BUG_SIDE_NOT_RIGHT_OR_LEFT
   2. The destination tangent point is not more than a tool radius
	  away (indicating gouging): NCE_CUTTER_GOUGING_WITH_CUTTER_RADIUS_COMP
   3. The value of move is not G_0 or G_1
	  NCE_BUG_CODE_NOT_G0_OR_G1

Side effects:
   This executes a STRAIGHT_MOVE command at cutting feed rate
   or a STRAIGHT_TRAVERSE command.
   It also updates the setting of the position of the tool point
   to the end point of the move and updates the programmed point.

Called by: convert_straight.

This is called if cutter radius compensation is on and
settings->cutter_comp_firstmove is true, indicating that this is the
first move after cutter radius compensation is turned on.

The algorithm used here for determining the path is to draw a straight
line from the destination point which is tangent to a circle whose
center is at the current point and whose radius is the radius of the
cutter. The destination point of the cutter tip is then found as the
center of a circle of the same radius tangent to the tangent line at
the destination point.

*/


void GCodeInterpreter::comp_get(Coords *srs, double *x, double *y, double *z)
{
	if (runner.plane == Plane_XZ)
	{
		*x = srs->z;
		*y = srs->x;
		*z = srs->y;
	}
	else
	{
		*x = srs->x;
		*y = srs->y;
		*z = srs->z;
	}
}


void GCodeInterpreter::comp_set(Coords *srs, double x, double y, double z)
{
	if (runner.plane == Plane_XZ)
	{
		srs->z = x;
		srs->x = y;
		srs->y = z;
	}
	else
	{
		srs->x = x;
		srs->y = y;
		srs->z = z;
	}
}


void GCodeInterpreter::comp_set_current(double x, double y, double z)
{
	comp_set(&runner.position, x, y, z);
}
void GCodeInterpreter::comp_set_programmed(double x, double y, double z)
{
	comp_set(&runner.program, x, y, z);
}
void GCodeInterpreter::comp_get_current(double *x, double *y, double *z)
{
	comp_get(&runner.position, x, y, z);
}
void GCodeInterpreter::comp_get_programmed(double *x, double *y, double *z)
{
	comp_get(&runner.program, x, y, z);
}





bool GCodeInterpreter::run_straight_comp1(int move, double px, double py, double pz, double a, double b, double c)
{
	double alpha;
	double end_x, end_y;
	double cx, cy, cz;


	double radius = runner.cutter_comp_radius; /* always will be positive */
	int side = runner.cutter_comp_side;

	comp_get_current(&cx, &cy, &cz);
	double distance = hypot((px - cx), (py - cy));

	IF_T_RET_F_SETSTATE(((side != CutterCompType_LEFT) && (side != CutterCompType_RIGHT)),
		PARAMETER_ERROR, "Compensation type not left and not right");
	IF_T_RET_F_SETSTATE((distance <= radius), PARAMETER_ERROR, "Length of cutter compensation entry move is not greater than the tool radius");

	alpha = atan2(py - cy, px - cx) + (side == CutterCompType_LEFT ? M_PI_2l : -M_PI_2l);

	end_x = (px + (radius * cos(alpha)));
	end_y = (py + (radius * sin(alpha)));

	cq.set_endpoint(cx, cy);

	if (move == G_0)
	{
		cq.enqueue_straight_traverse(cos(alpha), sin(alpha), 0, end_x, end_y, pz, a, b, c);
	}
	else if (move == G_1)
	{
		cq.enqueue_straight_feed(cos(alpha), sin(alpha), 0, end_x, end_y, pz, a, b, c);
	}
	else
		RET_F_SETSTATE(INTERNAL_ERROR, "Not G0 nor G1");

	runner.cutter_comp_firstmove = false;

	comp_set_current(end_x, end_y, pz);
	comp_set_programmed(px, py, pz);
	return true;
}
/****************************************************************************/

/*! convert_straight_comp2

Returned Value: int
   If any of the following errors occur, this returns the error shown.
   Otherwise, it returns INTERP_OK.
   1. The compensation side is not RIGHT or LEFT:
	  NCE_BUG_SIDE_NOT_RIGHT_OR_LEFT
   2. A concave corner is found:
	  NCE_CONCAVE_CORNER_WITH_CUTTER_RADIUS_COMP

Side effects:
   This executes a STRAIGHT_FEED command at cutting feed rate
   or a STRAIGHT_TRAVERSE command.
   It also generates an ARC_FEED to go around a corner, if necessary.
   It also updates the setting of the position of the tool point to
   the end point of the move and updates the programmed point.

Called by: convert_straight.

This is called if cutter radius compensation is on and
settings->cutter_comp_firstmove is not true, indicating that this is not
the first move after cutter radius compensation is turned on.

The algorithm used here is:
1. Determine the direction of the last motion. This is done by finding
   the direction of the line from the last programmed point to the
   current tool tip location. This line is a radius of the tool and is
   perpendicular to the direction of motion since the cutter is tangent
   to that direction.
2. Determine the direction of the programmed motion.
3. If there is a convex corner, insert an arc to go around the corner.
4. Find the destination point for the tool tip. The tool will be
   tangent to the line from the last programmed point to the present
   programmed point at the present programmed point.
5. Go in a straight line from the current tool tip location to the
   destination tool tip location.

This uses an angle tolerance of TOLERANCE_CONCAVE_CORNER (0.01 radian)
to determine if:
1) an illegal concave corner exists (tool will not fit into corner),
2) no arc is required to go around the corner (i.e. the current line
   is in the same direction as the end of the previous move), or
3) an arc is required to go around a convex corner and start off in
   a new direction.

If a rotary axis is moved in this block and an extra arc is required
to go around a sharp corner, all the rotary axis motion occurs on the
arc.  An alternative might be to distribute the rotary axis motion
over the arc and the straight move in proportion to their lengths.

If the Z-axis is moved in this block and an extra arc is required to
go around a sharp corner, all the Z-axis motion occurs on the straight
line and none on the extra arc.  An alternative might be to distribute
the Z-axis motion over the extra arc and the straight line in
proportion to their lengths.

This handles the case of there being no XY motion.

This handles G0 moves. Where an arc is inserted to round a corner in a
G1 move, no arc is inserted for a G0 move; a STRAIGHT_TRAVERSE is made
from the current point to the end point. The end point for a G0
move is the same as the end point for a G1 move, however.

*/

bool GCodeInterpreter::run_straight_comp2(int move,
	double px,    //!< X coordinate of programmed end point     
	double py,    //!< Y coordinate of programmed end point     
	double pz, double a, double b, double c)   //!< Z coordinate of end point                

{
	double alpha;
	double beta;
	double end_x, end_y, end_z;                 /* x-coordinate of actual end point */
	double gamma;
	double mid_x, mid_y;                 /* x-coordinate of end of added arc, if needed */
	double radius;
	int side;
	double small = TOLERANCE_CONCAVE_CORNER;      /* radians, testing corners */
	double opx, opy, opz;      /* old programmed beginning point */
	double theta;
	double cx, cy, cz;
	int concave;

	comp_get_current(&cx, &cy, &cz);
	comp_get_current(&end_x, &end_y, &end_z);
	comp_get_programmed(&opx, &opy, &opz);


	if ((py == opy) && (px == opx))
	{     /* no XY motion */
		if (move == G_0)
		{
			cq.enqueue_straight_traverse(px - opx, py - opy, pz - opz, cx, cy, pz, a, b, c);
		}
		else if (move == G_1)
		{
			cq.enqueue_straight_feed(px - opx, py - opy, pz - opz, cx, cy, pz, a, b, c);
		}
		else
			RET_F_SETSTATE(INTERNAL_ERROR, "Not G0 nor G1");
		// end already filled out, above
	}
	else
	{
		// some XY motion
		side = runner.cutter_comp_side;
		radius = runner.cutter_comp_radius;      /* will always be positive */
		theta = atan2(cy - opy, cx - opx);
		alpha = atan2(py - opy, px - opx);

		if (side == CutterCompType_LEFT)
		{
			if (theta < alpha)
				theta = (theta + (2 * M_PIl));
			beta = ((theta - alpha) - M_PI_2l);
			gamma = M_PI_2l;
		}
		else if (side == CutterCompType_RIGHT)
		{
			if (alpha < theta)
				alpha = (alpha + (2 * M_PIl));
			beta = ((alpha - theta) - M_PI_2l);
			gamma = -M_PI_2l;
		}
		else
			RET_F_SETSTATE(INTERNAL_ERROR, "Compensation type not left and not right");
		end_x = (px + (radius * cos(alpha + gamma)));
		end_y = (py + (radius * sin(alpha + gamma)));
		mid_x = (opx + (radius * cos(alpha + gamma)));
		mid_y = (opy + (radius * sin(alpha + gamma)));

		if ((beta < -small) || (beta > (M_PIl + small))) {
			concave = 1;
		}
		else if (beta > (M_PIl - small) &&
			(!cq.empty() && cq.front().type == QARC_FEED &&
			((side == CutterCompType_RIGHT && cq.front().data.arc_feed.turn > 0) ||
				(side == CutterCompType_LEFT && cq.front().data.arc_feed.turn < 0)))) {
			// this is an "h" shape, tool on right, going right to left
			// over the hemispherical round part, then up next to the
			// vertical part (or, the mirror case).  there are two ways
			// to stay to the "right", either loop down and around, or
			// stay above and right.  we're forcing above and right.
			concave = 1;
		}
		else
		{
			concave = 0;
			mid_x = (opx + (radius * cos(alpha + gamma)));
			mid_y = (opy + (radius * sin(alpha + gamma)));
		}

		if (!concave && (beta > small))
		{       /* ARC NEEDED */
			if (!cq.move_endpoint_and_flush(cx, cy))
			{
				state = cq.get_state();
				return false;
			}
		}
		else if (concave)
		{
			if (cq.front().type != QARC_FEED)
			{
				// line->line
				double retreat;
				// half the angle of the inside corner
				double halfcorner = (beta + M_PIl) / 2.0;
				IF_T_RET_F_SETSTATE((halfcorner == 0.0), PARAMETER_ERROR, "Zero degree inside corner is invalid for cutter compensation");
				retreat = radius / tan(halfcorner);
				// move back along the compensated path
				// this should replace the endpoint of the previous move
				mid_x = cx + retreat * cos(theta + gamma);
				mid_y = cy + retreat * sin(theta + gamma);
				// we actually want to move the previous line's endpoint here.  That's the same as 
				// discarding that line and doing this one instead.
				if (!cq.move_endpoint_and_flush(mid_x, mid_y))
				{
					state = cq.get_state();
					return false;
				}
			}
			else
			{
				// arc->line
				// beware: the arc we saved is the compensated one.
				arc_feed prev = cq.front().data.arc_feed;
				double oldrad = hypot(prev.center2 - prev.end2, prev.center1 - prev.end1);
				double oldrad_uncomp;

				// new line's direction
				double base_dir = atan2(py - opy, px - opx);
				double theta;
				double phi;

				theta = (prev.turn > 0) ? base_dir + M_PI_2l : base_dir - M_PI_2l;
				phi = atan2(prev.center2 - opy, prev.center1 - opx);
				if TOOL_INSIDE_ARC(side, prev.turn)
				{
					oldrad_uncomp = oldrad + radius;
				}
				else {
					oldrad_uncomp = oldrad - radius;
				}

				double alpha = theta - phi;
				// distance to old arc center perpendicular to the new line
				double d = oldrad_uncomp * cos(alpha);
				double d2;
				double angle_from_center;

				if TOOL_INSIDE_ARC(side, prev.turn) {
					d2 = d - radius;
					double l = d2 / oldrad;
					IF_T_RET_F_SETSTATE((l > 1.0 || l < -1.0), PARAMETER_ERROR, "Arc to straight motion makes a corner the compensated tool can't fit in without gouging");
					if (prev.turn > 0)
						angle_from_center = -acos(l) + theta + M_PIl;
					else
						angle_from_center = acos(l) + theta + M_PIl;
				}
				else {
					d2 = d + radius;
					double l = d2 / oldrad;
					IF_T_RET_F_SETSTATE((l > 1.0 || l < -1.0), PARAMETER_ERROR, "Arc to straight motion makes a corner the compensated tool can't fit in without gouging");
					if (prev.turn > 0)
						angle_from_center = acos(l) + theta + M_PIl;
					else
						angle_from_center = -acos(l) + theta + M_PIl;
				}
				mid_x = prev.center1 + oldrad * cos(angle_from_center);
				mid_y = prev.center2 + oldrad * sin(angle_from_center);
				if (!cq.move_endpoint_and_flush(mid_x, mid_y))
				{
					state = cq.get_state();
					return false;
				}
			}
		}
		else {
			// no arc needed, also not concave (colinear lines or tangent arc->line)
			cq.dequeue_canons();
			cq.set_endpoint(cx, cy);
		}
		if (move == G_0)
			cq.enqueue_straight_traverse(px - opx, py - opy, pz - opz, end_x, end_y, pz, a, b, c);
		else
			cq.enqueue_straight_feed(px - opx, py - opy, pz - opz, end_x, end_y, pz, a, b, c);
	}

	comp_set_current(end_x, end_y, pz);
	comp_set_programmed(px, py, pz);
	return true;
}