#include <math.h>
#include "GCodeInterpreter.h"
#include "cmdparser.h"
#include "gcodeerrors.h"

using namespace Interpreter;


/****************************************************************************/

/*! convert_arc

Returned Value: int
   If one of the following functions returns an error code,
   this returns that error code.
	  convert_arc_comp1
	  convert_arc_comp2
	  convert_arc2
   If any of the following errors occur, this returns the error code shown.
   Otherwise, this returns INTERP_OK.
   1. The block has neither an r value nor any i,j,k values:
	  NCE_R_I_J_K_WORDS_ALL_MISSING_FOR_ARC
   2. The block has both an r value and one or more i,j,k values:
	  NCE_MIXED_RADIUS_IJK_FORMAT_FOR_ARC
   3. In the ijk format the XY-plane is selected and
	  the block has a k value: NCE_K_WORD_GIVEN_FOR_ARC_IN_XY_PLANE
   4. In the ijk format the YZ-plane is selected and
	  the block has an i value: NCE_I_WORD_GIVEN_FOR_ARC_IN_YZ_PLANE
   5. In the ijk format the XZ-plane is selected and
	  the block has a j value: NCE_J_WORD_GIVEN_FOR_ARC_IN_XZ_PLANE
   6. In either format any of the following occurs.
	  a. The XY-plane is selected and the block has no x or y value:
		 NCE_X_AND_Y_WORDS_MISSING_FOR_ARC_IN_XY_PLANE
	  b. The YZ-plane is selected and the block has no y or z value:
		 NCE_Y_AND_Z_WORDS_MISSING_FOR_ARC_IN_YZ_PLANE
	  c. The ZX-plane is selected and the block has no z or x value:
		 NCE_X_AND_Z_WORDS_MISSING_FOR_ARC_IN_XZ_PLANE
   7. The selected plane is an unknown plane:
	  NCE_BUG_PLANE_NOT_XY_YZ__OR_XZ
   8. The feed rate mode is UNITS_PER_MINUTE and feed rate is zero:
	  NCE_CANNOT_MAKE_ARC_WITH_ZERO_FEED_RATE
   9. The feed rate mode is INVERSE_TIME and the block has no f word:
	  NCE_F_WORD_MISSING_WITH_INVERSE_TIME_ARC_MOVE

Side effects:
   This generates and executes an arc command at feed rate
   (and, possibly a second arc command). It also updates the setting
   of the position of the tool point to the end point of the move.

Called by: convert_motion.

This converts a helical or circular arc.  The function calls:
convert_arc2 (when cutter radius compensation is off) or
convert_arc_comp1 (when cutter comp is on and this is the first move) or
convert_arc_comp2 (when cutter comp is on and this is not the first move).

If the ijk format is used, at least one of the offsets in the current
plane must be given in the block; it is common but not required to
give both offsets. The offsets are always incremental [NCMS, page 21].

If cutter compensation is in use, the path's length may increase or
decrease.  Also an arc may be added, to go around a corner, before the
original arc move.  For the purpose of calculating the feed rate when in
inverse time mode, this length increase or decrease is ignored.  The
feed is still set to the original programmed arc length divided by the F
number (with the above lower bound).  The new arc (if needed) and the
new longer or shorter original arc are taken at this feed.

*/


/*
void  GCodeInterpreter::arc_to(const Coords &position, bool cw)
{

	if (executor)
	{
		executor->arc_feed(position, cw);
	}
	runner.position = position;
}
*/

bool GCodeInterpreter::arc_to(int motion, const Coords &position, const CmdParser &parser)       //!< either G_2 (cw arc) or G_3 (ccw arc)    
{
	bool first;                    /* flag set true if this is first move after comp true */
	int ijk_flag;                 /* flag set true if any of i,j,k present in NC code  */
	double end_x;
	double end_y;
	double end_z;
	double AA_end;
	double BB_end;
	double CC_end;
	double u_end = 0, v_end = 0, w_end = 0;

	//CHKS((settings->arc_not_allowed), (_("The move just after exiting cutter compensation mode must be straight, not an arc")));

	ijk_flag = parser.hasParam(PARAM_I) || parser.hasParam(PARAM_J) || parser.hasParam(PARAM_K);

	first = runner.cutter_comp_firstmove;

	IF_T_RET_F_SETSTATE((!parser.hasParam(PARAM_R) && (!ijk_flag)), PARAMETER_ERROR, YA_R_I_J_K_WORDS_ALL_MISSING_FOR_ARC);

	IF_T_RET_F_SETSTATE((parser.hasParam(PARAM_R) && (ijk_flag)), PARAMETER_ERROR, YA_MIXED_RADIUS_IJK_FORMAT_FOR_ARC);

	//if (settings->feed_mode == UNITS_PER_MINUTE) {
	//	CHKS((settings->feed_rate == 0.0),
	//		NCE_CANNOT_MAKE_ARC_WITH_ZERO_FEED_RATE);
	//}
	//else if (settings->feed_mode == UNITS_PER_REVOLUTION) {
	//	CHKS((settings->feed_rate == 0.0),
	//		NCE_CANNOT_MAKE_ARC_WITH_ZERO_FEED_RATE);
	//	CHKS((settings->speed[settings->active_spindle] == 0.0),
	//		_("Cannot feed with zero spindle speed in feed per rev mode"));
	//}
	//else if (settings->feed_mode == INVERSE_TIME) {
	//	CHKS((!block->f_flag),
	//		NCE_F_WORD_MISSING_WITH_INVERSE_TIME_ARC_MOVE);
	//}

	if (ijk_flag)
	{
		if (runner.plane == Plane_XY)
		{
			IF_T_RET_F_SETSTATE(parser.hasParam(PARAM_K), PARAMETER_ERROR, YA_SOMEWORD_GIVEN_FOR_ARC_IN_THE_PLANE, 'K',"XY");
			if (!parser.hasParam(PARAM_I))
				RET_F_SETSTATE(PARAMETER_ERROR, YA_SOMEWORDS_MISSING_IN_ABS_CENTERARC,'I');
			else if (!parser.hasParam(PARAM_J))
				RET_F_SETSTATE(PARAMETER_ERROR, YA_SOMEWORDS_MISSING_IN_ABS_CENTERARC, 'J');
		}
		else if (runner.plane == Plane_YZ)
		{
			IF_T_RET_F_SETSTATE(parser.hasParam(PARAM_I), PARAMETER_ERROR, YA_SOMEWORD_GIVEN_FOR_ARC_IN_THE_PLANE, 'I',"YZ" );
			if (!parser.hasParam(PARAM_J))
				RET_F_SETSTATE(PARAMETER_ERROR, YA_SOMEWORDS_MISSING_IN_ABS_CENTERARC, 'J');
			else if (!parser.hasParam(PARAM_K))
				RET_F_SETSTATE(PARAMETER_ERROR, YA_SOMEWORDS_MISSING_IN_ABS_CENTERARC, 'K');
		}
		else if (runner.plane == Plane_XZ)
		{
			IF_T_RET_F_SETSTATE(parser.hasParam(PARAM_J), PARAMETER_ERROR, YA_SOMEWORD_GIVEN_FOR_ARC_IN_THE_PLANE, 'J', "XZ" );
			if (!parser.hasParam(PARAM_I))
				RET_F_SETSTATE(PARAMETER_ERROR, YA_SOMEWORDS_MISSING_IN_ABS_CENTERARC, 'I');
			else if (!parser.hasParam(PARAM_K))
				RET_F_SETSTATE(PARAMETER_ERROR, YA_SOMEWORDS_MISSING_IN_ABS_CENTERARC, 'K');
		}
		else
		{
			RET_F_SETSTATE(PARAMETER_ERROR, YA_BUG_PLANE_NOT_XY_YZ_OR_XZ );
		}
	}
	else 	// in R format, we need some XYZ words specified because a full circle is not allowed.
	{
		// in R format, we need some XYZ words specified because a full circle is not allowed.
		if (runner.plane == Plane_XY)
		{
			IF_T_RET_F_SETSTATE(((!parser.hasParam(PARAM_X)) && (!parser.hasParam(PARAM_Y))), ///* && (!block->radius_flag) && (!block->theta_flag)*/
				PARAMETER_ERROR, YA_X_AND_Y_WORDS_MISSING_FOR_ARC_IN_XY_PLANE);
		}
		else if (runner.plane == Plane_YZ) {
			IF_T_RET_F_SETSTATE(((!parser.hasParam(PARAM_Y)) && (!parser.hasParam(PARAM_Z))),
				PARAMETER_ERROR, YA_Y_AND_Z_WORDS_MISSING_FOR_ARC_IN_YZ_PLANE);
		}
		else if (runner.plane == Plane_XZ) {
			IF_T_RET_F_SETSTATE(((!parser.hasParam(PARAM_X)) && (parser.hasParam(PARAM_Z))),
				PARAMETER_ERROR, YA_X_AND_Z_WORDS_MISSING_FOR_ARC_IN_XZ_PLANE);
		}
	}


	//CHP(find_ends(block, settings, &end_x, &end_y, &end_z,
	//	&AA_end, &BB_end, &CC_end,
	//	&u_end, &v_end, &w_end));

	end_x = position.x;
	end_y = position.y;
	end_z = position.z;
	AA_end = position.a;
	BB_end = position.b;
	CC_end = position.c;

	//settings->motion_mode = move;
	runner.motion_mode = motion;

	double i = 0, j = 0, k = 0;
	if (parser.getRParam(PARAM_I, &i))  i = to_mm(i);
	if (parser.getRParam(PARAM_J, &j))  j = to_mm(j);
	if (parser.getRParam(PARAM_K, &k))  k = to_mm(k);

	if (runner.plane == Plane_XY)
	{
		if ((!runner.cutter_comp_side) ||
			(runner.cutter_comp_radius == 0.0))
		{
			IF_F_RET_F(convert_arc2(motion, parser,
				&(runner.position.x), &(runner.position.y), &(runner.position.z),
				end_x, end_y, end_z,
				AA_end, BB_end, CC_end,
				u_end, v_end, w_end, i, j));
		}
		else if (first)
		{
			IF_F_RET_F(convert_arc_comp1(motion, parser, end_x, end_y, end_z,
				i, j, AA_end, BB_end, CC_end, u_end, v_end, w_end));
		}
		else {
			IF_F_RET_F(convert_arc_comp2(motion, parser, end_x, end_y, end_z,
				i, j, AA_end, BB_end, CC_end, u_end, v_end, w_end));
		}
	}
	else if (runner.plane == Plane_XZ)
	{
		if ((!runner.cutter_comp_side) ||
			(runner.cutter_comp_radius == 0.0))
		{
			IF_F_RET_F(convert_arc2(motion, parser,
				&(runner.position.z), &(runner.position.x), &(runner.position.y),
				end_z, end_x, end_y, AA_end, BB_end, CC_end, u_end, v_end, w_end, k, i));
		}
		else if (first)
		{
			IF_F_RET_F(convert_arc_comp1(motion, parser, end_z, end_x, end_y,
				k, i, AA_end, BB_end, CC_end, u_end, v_end, w_end));
		}
		else
		{
			IF_F_RET_F(convert_arc_comp2(motion, parser, end_z, end_x, end_y,
				k, i, AA_end, BB_end, CC_end, u_end, v_end, w_end));

		}
	}
	else if (runner.plane == Plane_YZ) {
		IF_F_RET_F(convert_arc2(motion, parser,
			&(runner.position.y), &(runner.position.z), &(runner.position.x),
			end_y, end_z, end_x, AA_end, BB_end, CC_end, u_end, v_end, w_end, j, k));
	}
	else
		RET_F_SETSTATE(PARAMETER_ERROR, YA_BUG_PLANE_NOT_XY_YZ_OR_XZ);
	return true;
}

/****************************************************************************/

/*! convert_arc2

Returned Value: int
   If arc_data_ijk or arc_data_r returns an error code,
   this returns that code.
   Otherwise, it returns INTERP_OK.

Side effects:
   This executes an arc command at feed rate. It also updates the
   setting of the position of the tool point to the end point of the move.

Called by: convert_arc.

This converts a helical or circular arc.

*/


bool GCodeInterpreter::convert_arc2(int motion,       //!< either G_2 (cw arc) or G_3 (ccw arc)    
	const CmdParser &parser,
	double *current1,       //!< pointer to current value of coordinate 1
	double *current2,       //!< pointer to current value of coordinate 2
	double *current3,       //!< pointer to current value of coordinate 3
	double &end1,    //!< coordinate 1 value at end of arc        
	double &end2,    //!< coordinate 2 value at end of arc        
	double &end3,    //!< coordinate 3 value at end of arc        
	double &AA_end,  //!< a-value at end of arc                   
	double &BB_end,  //!< b-value at end of arc                   
	double &CC_end,  //!< c-value at end of arc                   
	double &u, double &v, double &w, //!< values at end of arc
	double &offset1, //!< center, either abs or offset from current
	double &offset2)
{
	double center1;
	double center2;
	int turn;                     // number of full or partial turns CCW in arc 

	// Spiral tolerance is the amount of "spiral" allowed in a given arc segment, or (r2-r1)/theta
	//double spiral_abs_tolerance = (settings->length_units == CANON_UNITS_INCHES) ?
		//settings->center_arc_radius_tolerance_inch : settings->center_arc_radius_tolerance_mm;

	// Radius tolerance allows a bit of leeway on the minimum radius for a radius defined arc.
	//double radius_tolerance = (settings->length_units == CANON_UNITS_INCHES) ?
		//RADIUS_TOLERANCE_INCH : RADIUS_TOLERANCE_MM;

	double rval;
	int p_int = 1;
	if (parser.getRParam(PARAM_P, &rval))
		p_int = static_cast<int>(std::nearbyint(rval));



	double radius_tolerance = 0.001;  //bb xbz
	double spiral_abs_tolerance = 0.001;

	if (parser.getRParam(PARAM_R, &rval))
	{
		rval = to_mm(rval);
		IF_F_RET_F(arc_data_r(motion, *current1, *current2, end1, end2,
			rval, p_int, &center1, &center2, &turn, radius_tolerance));
	}
	else
	{
		IF_F_RET_F(arc_data_ijk(motion, *current1, *current2, end1, end2,
			offset1, offset2, p_int,
			&center1, &center2, &turn, radius_tolerance, spiral_abs_tolerance, SPIRAL_RELATIVE_TOLERANCE));
	}

	//inverse_time_rate_arc(*current1, *current2, *current3, center1, center2,
//		turn, end1, end2, end3, block, settings);

	executor->arc_feed(&runner, end1, end2, center1, center2, turn, end3, AA_end, BB_end, CC_end, u, v);
	//	ARC_FEED(block->line_number, end1, end2, center1, center2, turn, end3,
	//		AA_end, BB_end, CC_end, u, v, w);

	*current1 = end1;
	*current2 = end2;
	*current3 = end3;

	runner.position.a = AA_end;
	runner.position.b = BB_end;
	runner.position.c = CC_end;

	return true;
}


char GCodeInterpreter::arc_axis1(Plane plane)
{
	switch (plane)
	{
	case Plane_XY: return 'X';
	case Plane_XZ: return 'Z';
	case Plane_YZ: return 'Y';
	default: return '!';
	}
}

char GCodeInterpreter::arc_axis2(Plane plane)
{
	switch (plane)
	{
	case Plane_XY: return 'Y';
	case Plane_XZ: return 'X';
	case Plane_YZ: return 'Z';
	default: return '!';
	}
}


bool GCodeInterpreter::arc_data_ijk(int motion,       //!< either G_2 (cw arc) or G_3 (ccw arc)
	double &current_x,       //!< first coordinate of current point
	double &current_y,       //!< second coordinate of current point
	double &end_x,   //!< first coordinate of arc end point
	double &end_y,   //!< second coordinate of arc end point
	double &i_number,        //!<first coordinate of center (abs or incr)
	double &j_number,        //!<second coordinate of center (abs or incr)
	int p_number,
	double *center_x,       //!< pointer to first coordinate of center of arc
	double *center_y,       //!< pointer to second coordinate of center of arc
	int *turn,      //!< pointer to no. of full or partial circles CCW
	double radius_tolerance, //!<minimum radius tolerance
	double spiral_abs_tolerance,  //!<tolerance of start and end radius difference
	double spiral_rel_tolerance)
{
	double radius;                // radius to current point 
	double radius2;               // radius to end point    
	char a = arc_axis1(runner.plane), b = arc_axis2(runner.plane);

	if (runner.ijk_incremental)
	{
		*center_x = (current_x + i_number);
		*center_y = (current_y + j_number);
	}
	else
	{
		*center_x = (i_number);
		*center_y = (j_number);
	}

	radius = hypot((*center_x - current_x), (*center_y - current_y));
	radius2 = hypot((*center_x - end_x), (*center_y - end_y));

	IF_T_RET_F_SETSTATE(((radius < radius_tolerance) || (radius2 < radius_tolerance)), PARAMETER_ERROR,
		YA_ZERO_RADIUS_ARC_WITHARGS,
		a, current_x, b, current_y,
		a, *center_x, b, *center_y,
		a, end_x, b, end_y, radius, radius2);

	double abs_err = fabs(radius - radius2);
	double rel_err = abs_err / std::max(radius, radius2);
	IF_T_RET_F_SETSTATE((abs_err > spiral_abs_tolerance * 100.0) ||
		(rel_err > spiral_rel_tolerance && abs_err > spiral_abs_tolerance), PARAMETER_ERROR,
		YA_RADIUS_TO_STARTARC_DIF_RADIUS_FROM_END,
		a, current_x, b, current_y, a, *center_x, b, *center_y, a, end_x, b, end_y, radius, radius2, abs_err, rel_err * 100);

	if (motion == G_2)
		*turn = -1 * p_number;
	else
		*turn = 1 * p_number;
	return true;
}

/****************************************************************************/

/*! arc_data_r

Returned Value: int
   If any of the following errors occur, this returns the error shown.
   Otherwise, it returns INTERP_OK.
   1. The radius is too small to reach the end point:
	  NCE_ARC_RADIUS_TOO_SMALL_TO_REACH_END_POINT
   2. The current point is the same as the end point of the arc
	  (so that it is not possible to locate the center of the circle):
	  NCE_CURRENT_POINT_SAME_AS_END_POINT_OF_ARC

Side effects:
   This finds and sets the values of center_x, center_y, and turn.

Called by:
   convert_arc2
   convert_arc_comp2

This finds the center coordinates and number of full or partial turns
counterclockwise of a helical or circular arc in the r format. This
function is used by convert_arc2 for all three planes, so "x" and
"y" really mean "first_coordinate" and "second_coordinate" wherever
they are used here as suffixes of variable names.

If the value of the radius argument is negative, that means [NCMS,
page 21] that an arc larger than a semicircle is to be made.
Otherwise, an arc of a semicircle or less is made.

The algorithm used here is based on finding the midpoint M of the line
L between the current point and the end point of the arc. The center
of the arc lies on a line through M perpendicular to L.

*/


bool GCodeInterpreter::arc_data_r(int motion, //!< either G_2 (cw arc) or G_3 (ccw arc)	
	double &current_x, //!< first coordinate of current point
	double &current_y, //!< second coordinate of current point
	double &end_x,     //!< first coordinate of arc end point
	double &end_y,     //!< second coordinate of arc end point
	double &radius,    //!< radius of arc
	int p_number,
	double *center_x, //!< pointer to first coordinate of center of arc
	double *center_y, //!< pointer to second coordinate of center of arc
	int *turn,        //!< pointer to number of full or partial circles CCW
	double &tolerance) //!< tolerance of differing radii
{
	double abs_radius;            /* absolute value of given radius */
	double half_length;           /* distance from M to end point   */
	double mid_x;                 /* first coordinate of M          */
	double mid_y;                 /* second coordinate of M         */
	double offset;                /* distance from M to center      */
	double theta;                 /* angle of line from M to center */
	double turn2;                 /* absolute value of half of turn */

	IF_T_RET_F_SETSTATE(((end_x == current_x) && (end_y == current_y)), PARAMETER_ERROR, YA_CURRENT_POINT_SAME_AS_END_POINT_OF_ARC);
	abs_radius = fabs(radius);
	mid_x = (end_x + current_x) / 2.0;
	mid_y = (end_y + current_y) / 2.0;
	half_length = hypot((mid_x - end_x), (mid_y - end_y));

	IF_T_RET_F_SETSTATE(((half_length - abs_radius) > tolerance), PARAMETER_ERROR, YA_ARC_RADIUS_TOO_SMALL_TO_REACH_END_POINT);

	if ((half_length / abs_radius) > (1 - TINY))
		half_length = abs_radius;   /* allow a small error for semicircle */
	  /* check needed before calling asin   */
	if (((motion == G_2) && (radius > 0)) || ((motion != G_2) && (radius < 0)))
		theta = atan2((end_y - current_y), (end_x - current_x)) - M_PI_2l;
	else
		theta = atan2((end_y - current_y), (end_x - current_x)) + M_PI_2l;

	turn2 = asin(half_length / abs_radius);
	offset = abs_radius * cos(turn2);
	*center_x = mid_x + (offset * cos(theta));
	*center_y = mid_y + (offset * sin(theta));
	*turn = (motion == G_2) ? -1 * p_number : 1 * p_number;

	return true;
}


/****************************************************************************/

/*! convert_arc_comp1

Returned Value: int
   If arc_data_comp_ijk or arc_data_comp_r returns an error code,
   this returns that code.
   Otherwise, it returns INTERP_OK.

Side effects:
   This executes an arc command at
   feed rate. It also updates the setting of the position of
   the tool point to the end point of the move.

Called by: convert_arc.

This function converts a helical or circular arc, generating only one
arc. This is called when cutter radius compensation is on and this is
the first cut after the turning on.

The arc which is generated is derived from a second arc which passes
through the programmed end point and is tangent to the cutter at its
current location. The generated arc moves the tool so that it stays
tangent to the second arc throughout the move.

*/

bool GCodeInterpreter::convert_arc_comp1(int move,  //!< either G_2 (cw arc) or G_3 (ccw arc)            
	const CmdParser &parser,
	double &end_x,      //!< x-value at end of programmed (then actual) arc  
	double &end_y,      //!< y-value at end of programmed (then actual) arc  
	double &end_z,      //!< z-value at end of arc
	double &offset_x, double offset_y,
	double &AA_end,     //!< a-value at end of arc
	double &BB_end,     //!< b-value at end of arc
	double &CC_end,     //!< c-value at end of arc
	double &u_end, double &v_end, double &w_end) //!< uvw at end of arc
{
	double center_x, center_y;
	double gamma;                 /* direction of perpendicular to arc at end */
	int side;                     /* offset side - right or left              */
	double tool_radius;
	int turn;                     /* 1 for counterclockwise, -1 for clockwise */
	double cx, cy, cz; // current
	int plane = runner.plane;

	side = runner.cutter_comp_side;
	tool_radius = runner.cutter_comp_radius;   /* always is positive */

	double spiral_abs_tolerance = env->GetCenterArcRadiusTolerance();
	double radius_tolerance = RADIUS_TOLERANCE_MM;

	comp_get_current(&cx, &cy, &cz);

	IF_T_RET_F_SETSTATE((hypot((end_x - cx), (end_y - cy)) <= tool_radius),PARAMETER_ERROR, YA_RADIUS_OF_COMPENSTION_IS_NOT_GRATE_TOOL_RADIUS);

	int p_number = 1;
	parser.getIParam(PARAM_P, &p_number);

	if ( parser.hasParam(PARAM_R) ) 
	{
		double r_number;
		parser.getRParam(PARAM_R, &r_number);
		IF_F_RET_F(arc_data_comp_r(move, tool_radius, cx, cy, end_x, end_y,
			r_number, p_number,	&center_x, &center_y, &turn, radius_tolerance));
	}
	else 
	{
		IF_F_RET_F(arc_data_comp_ijk(move, tool_radius, cx, cy, end_x, end_y,
			offset_x, offset_y, p_number,
			&center_x, &center_y, &turn, radius_tolerance, spiral_abs_tolerance, SPIRAL_RELATIVE_TOLERANCE));
	}

	// the tool will end up in gamma direction from the programmed arc endpoint
	if TOOL_INSIDE_ARC(side, turn) 
	{
		// tool inside the arc: ends up toward the center
		gamma = atan2((center_y - end_y), (center_x - end_x));
	}
	else {
		// outside: away from the center
		gamma = atan2((end_y - center_y), (end_x - center_x));
	}

	runner.cutter_comp_firstmove = false;

	comp_set_programmed(end_x, end_y, end_z);
	
	// move endpoint to the compensated position.  This changes the radius and center.
	end_x += tool_radius * cos(gamma);
	end_y += tool_radius * sin(gamma);

	/* To find the new center:
	   imagine a right triangle ABC with A being the endpoint of the
	   compensated arc, B being the center of the compensated arc, C being
	   the midpoint between start and end of the compensated arc. AB_ang
	   is the direction of A->B.  A_ang is the angle of the triangle
	   itself.  We need to find a new center for the compensated arc
	   (point B). */

	double b_len = hypot(cy - end_y, cx - end_x) / 2.0;
	double AB_ang = atan2(center_y - end_y, center_x - end_x);
	double A_ang = atan2(cy - end_y, cx - end_x) - AB_ang;

	IF_T_RET_F_SETSTATE((fabs(cos(A_ang)) < TOLERANCE_EQUAL), PARAMETER_ERROR, YA_TOOL_RADIUS_NOT_LESS_THAN_ARC_RADIUS_WITH_COMP);
	
	double c_len = b_len / cos(A_ang);

	// center of the arc is c_len from end in direction AB
	center_x = end_x + c_len * cos(AB_ang);
	center_y = end_y + c_len * sin(AB_ang);

	/* center to endpoint distances matched before - they still should. */
	IF_T_RET_F_SETSTATE((fabs(hypot(center_x - end_x, center_y - end_y) -
		hypot(center_x - cx, center_y - cy)) > spiral_abs_tolerance), PARAMETER_ERROR, YA_BUG_IN_TOOL_RADIUS_COMP);

	// need this move for lathes to move the tool origin first.  otherwise, the arc isn't an arc.
	//if (runner.cutter_comp_orientation != 0 && runner.cutter_comp_orientation != 9) 
	//{
	//	cq.enqueue_straight_feed(0, 0, 0,	cx, cy, cz,	AA_end, BB_end, CC_end);
	//	cq.set_endpoint(cx, cy);
	//}

	cq.enqueue_arc_feed(
		cq.find_turn(cx, cy, center_x, center_y, turn, end_x, end_y),
		end_x, end_y, center_x, center_y, turn, end_z,
		AA_end, BB_end, CC_end);

	comp_set_current(end_x, end_y, end_z);
	runner.position.a = AA_end;
	runner.position.b = BB_end;
	runner.position.c = CC_end;
	return true;
}

///****************************************************************************/
//
///*! convert_arc_comp2
//
//Returned Value: int
//   If arc_data_ijk or arc_data_r returns an error code,
//   this returns that code.
//   If any of the following errors occurs, this returns the error code shown.
//   Otherwise, it returns INTERP_OK.
//   1. A concave corner is found: NCE_CONCAVE_CORNER_WITH_CUTTER_RADIUS_COMP
//   2. The tool will not fit inside an arc:
//	  NCE_TOOL_RADIUS_NOT_LESS_THAN_ARC_RADIUS_WITH_COMP
//
//Side effects:
//   This executes an arc command feed rate. If needed, at also generates
//   an arc to go around a convex corner. It also updates the setting of
//   the position of the tool point to the end point of the move.
//Called by: convert_arc.
//
//This function converts a helical or circular arc. The axis must be
//parallel to the z-axis. This is called when cutter radius compensation
//is on and this is not the first cut after the turning on.
//
//If one or more rotary axes is moved in this block and an extra arc is
//required to go around a sharp corner, all the rotary axis motion
//occurs on the main arc and none on the extra arc.  An alternative
//might be to distribute the rotary axis motion over the extra arc and
//the programmed arc in proportion to their lengths.
//
//If the Z-axis is moved in this block and an extra arc is required to
//go around a sharp corner, all the Z-axis motion occurs on the main arc
//and none on the extra arc.  An alternative might be to distribute the
//Z-axis motion over the extra arc and the main arc in proportion to
//their lengths.
//
//*/
//
bool GCodeInterpreter::convert_arc_comp2(int move,  //!< either G_2 (cw arc) or G_3 (ccw arc)          
	const CmdParser &parser,
	double end_x,      //!< x-value at end of programmed (then actual) arc
	double end_y,      //!< y-value at end of programmed (then actual) arc
	double end_z,      //!< z-value at end of arc 
	double offset_x, double offset_y,
	double AA_end,     //!< a-value at end of arc
	double BB_end,     //!< b-value at end of arc
	double CC_end,     //!< c-value at end of arc
	double u, double v, double w) //!< uvw at end of arc
{
	double alpha;                 /* direction of tangent to start of arc */
	double arc_radius;
	double beta;                  /* angle between two tangents above */
	double centerx, centery;              /* center of arc */
	double delta;                 /* direction of radius from start of arc to center of arc */
	double gamma;                 /* direction of perpendicular to arc at end */
	double midx, midy;
	int side;
	double small = TOLERANCE_CONCAVE_CORNER;      /* angle for testing corners */
	double opx, opy, opz;
	double theta;                 /* direction of tangent to last cut */
	double tool_radius;
	int turn;                     /* number of full or partial circles CCW */
	int plane = runner.plane;
	double cx, cy, cz;
	double new_end_x, new_end_y;

	double spiral_abs_tolerance = env->GetCenterArcRadiusTolerance();
	double radius_tolerance = RADIUS_TOLERANCE_MM;

	/* find basic arc data: center_x, center_y, and turn */

	comp_get_programmed(&opx, &opy, &opz);
	comp_get_current(&cx, &cy, &cz);

	int p_number = 1;
	parser.getIParam(PARAM_P, &p_number);

	if (parser.hasParam(PARAM_R))
	{
		double r_number;
		parser.getRParam(PARAM_R, &r_number);
		IF_F_RET_F(arc_data_r(move,opx, opy, end_x, end_y,
			r_number, p_number,	&centerx, &centery, &turn, radius_tolerance));
	}
	else 
	{
		IF_F_RET_F(arc_data_ijk(move, opx, opy, end_x, end_y,			
			offset_x, offset_y, p_number, &centerx, &centery, &turn, radius_tolerance, spiral_abs_tolerance, SPIRAL_RELATIVE_TOLERANCE));
	}

	//inverse_time_rate_arc(opx, opy, opz, centerx, centery,
//		turn, end_x, end_y, end_z, block, settings);

	side = runner.cutter_comp_side;
	tool_radius = runner.cutter_comp_radius;   /* always is positive */
	arc_radius = hypot((centerx - end_x), (centery - end_y));
	theta = atan2(cy - opy, cx - opx);
	theta = (side == CutterCompType_LEFT) ? (theta - M_PI_2l) : (theta + M_PI_2l);
	delta = atan2(centery - opy, centerx - opx);
	alpha = (move == G_3) ? (delta - M_PI_2l) : (delta + M_PI_2l);
	beta = (side == CutterCompType_LEFT) ? (theta - alpha) : (alpha - theta);

	// normalize beta -90 to +270?
	beta = (beta > (1.5 * M_PIl)) ? (beta - (2 * M_PIl)) : (beta < -M_PI_2l) ? (beta + (2 * M_PIl)) : beta;

	if (((side == CutterCompType_LEFT) && (move == G_3)) || ((side == CutterCompType_RIGHT) && (move == G_2))) {
		// we are cutting inside the arc
		gamma = atan2((centery - end_y), (centerx - end_x));
		IF_T_RET_F_SETSTATE((arc_radius <= tool_radius),PARAMETER_ERROR, YA_TOOL_RADIUS_NOT_LESS_THAN_ARC_RADIUS_WITH_COMP);
	}
	else 
	{
		gamma = atan2((end_y - centery), (end_x - centerx));
		delta = (delta + M_PIl);
	}

	// move arc endpoint to the compensated position
	new_end_x = end_x + tool_radius * cos(gamma);
	new_end_y = end_y + tool_radius * sin(gamma);

	if (beta < -small ||
		beta > M_PIl + small ||
		// special detection for convex corner on tangent arc->arc (like atop the middle of "m" shape)
		// or tangent line->arc (atop "h" shape)
		(fabs(beta - M_PIl) < small && !TOOL_INSIDE_ARC(side, turn))
		) {
		// concave
		if (cq.front().type != QARC_FEED) {
			// line->arc
			double cy = arc_radius * sin(beta - M_PI_2l);
			double toward_nominal;
			double dist_from_center;
			double angle_from_center;

			if TOOL_INSIDE_ARC(side, turn) 
			{
				// tool is inside the arc
				dist_from_center = arc_radius - tool_radius;
				toward_nominal = cy + tool_radius;
				double l = toward_nominal / dist_from_center;
				IF_T_RET_F_SETSTATE((l > 1.0 || l < -1.0), PARAMETER_ERROR, YA_ARC_MOVE_IN_CORNER_CANATBEREACH);
				if (turn > 0) 
				{
					angle_from_center = theta + asin(l);
				}
				else 
				{
					angle_from_center = theta - asin(l);
				}
			}
			else 
			{
				dist_from_center = arc_radius + tool_radius;
				toward_nominal = cy - tool_radius;
				double l = toward_nominal / dist_from_center;
				IF_T_RET_F_SETSTATE((l > 1.0 || l < -1.0), PARAMETER_ERROR, YA_ARC_MOVE_IN_CORNER_CANATBEREACH);
				if (turn > 0)
				{
					angle_from_center = theta + M_PIl - asin(l);
				}
				else 
				{
					angle_from_center = theta + M_PIl + asin(l);
				}
			}

			midx = centerx + dist_from_center * cos(angle_from_center);
			midy = centery + dist_from_center * sin(angle_from_center);

			IF_F_RET_F(cq.move_endpoint_and_flush(midx, midy));
		}
		else {
			// arc->arc
			struct arc_feed &prev = cq.front().data.arc_feed;
			double oldrad = hypot(prev.center2 - prev.end2, prev.center1 - prev.end1);
			double newrad;
			if TOOL_INSIDE_ARC(side, turn) 
			{
				newrad = arc_radius - tool_radius;
			}
			else 
			{
				newrad = arc_radius + tool_radius;
			}

			double arc_cc, pullback, cc_dir, a;
			arc_cc = hypot(prev.center2 - centery, prev.center1 - centerx);

			IF_T_RET_F_SETSTATE((oldrad == 0 || arc_cc == 0), PARAMETER_ERROR, YA_ARC_TO_ARC_INVALID_ARC_HAVE_SME_CENTERS);
			a = (SQ(oldrad) + SQ(arc_cc) - SQ(newrad)) / (2 * oldrad * arc_cc);

			IF_T_RET_F_SETSTATE((a > 1.0 || a < -1.0), PARAMETER_ERROR, YA_ARC_TO_ARC_MAKE_CORNER_OFCOMP);
			pullback = acos(a);
			cc_dir = atan2(centery - prev.center2, centerx - prev.center1);

			double dir;
			if TOOL_INSIDE_ARC(side, prev.turn) {
				if (turn > 0)
					dir = cc_dir + pullback;
				else
					dir = cc_dir - pullback;
			}
			else {
				if (turn > 0)
					dir = cc_dir - pullback;
				else
					dir = cc_dir + pullback;
			}

			midx = prev.center1 + oldrad * cos(dir);
			midy = prev.center2 + oldrad * sin(dir);

			IF_F_RET_F(cq.move_endpoint_and_flush(midx, midy));
		}
		cq.enqueue_arc_feed(
			cq.find_turn(opx, opy, centerx, centery, turn, end_x, end_y),
			new_end_x, new_end_y, centerx, centery, turn, end_z, AA_end, BB_end, CC_end);
	}
	else if (beta > small) /* convex, two arcs needed */
	{           
		midx = opx + tool_radius * cos(delta);
		midy = opy + tool_radius * sin(delta);
		cq.dequeue_canons();
		cq.enqueue_arc_feed(
			0.0, // doesn't matter since we won't move this arc's endpoint
			midx, midy, opx, opy, ((side == CutterCompType_LEFT) ? -1 : 1),
			cz,	AA_end, BB_end, CC_end);
		cq.dequeue_canons();
		cq.set_endpoint(midx, midy);
		cq.enqueue_arc_feed(
			cq.find_turn(opx, opy, centerx, centery, turn, end_x, end_y),
			new_end_x, new_end_y, centerx, centery, turn, end_z,
			AA_end, BB_end, CC_end);
	}
	else                      /* convex, one arc needed */
	{ 
		cq.dequeue_canons();
		cq.set_endpoint(cx, cy);
		cq.enqueue_arc_feed(
		cq.find_turn(opx, opy, centerx, centery, turn, end_x, end_y),
			new_end_x, new_end_y, centerx, centery, turn, end_z, AA_end, BB_end, CC_end);
	}

	comp_set_programmed( end_x, end_y, end_z);
	comp_set_current( new_end_x, new_end_y, end_z);
	runner.position.a = AA_end;
	runner.position.b = BB_end;
	runner.position.c = CC_end;
	return true;
}





/***********************************************************************/

/*! arc_data_comp_ijk

Returned Value: int
   If any of the following errors occur, this returns the error code shown.
   Otherwise, it returns INTERP_OK.
   1. The two calculable values of the radius differ by more than
	  tolerance: NCE_RADIUS_TO_END_OF_ARC_DIFFERS_FROM_RADIUS_TO_START
   2. move is not G_2 or G_3: NCE_BUG_CODE_NOT_G2_OR_G3

Side effects:
   This finds and sets the values of center_x, center_y, and turn.

Called by: convert_arc_comp1

This finds the center coordinates and number of full or partial turns
counterclockwise of a helical or circular arc in ijk-format in the XY
plane. The center is computed easily from the current point and center
offsets, which are given. It is checked that the end point lies one
tool radius from the arc.


*/

bool GCodeInterpreter::arc_data_comp_ijk(int move,  //!<either G_2 (cw arc) or G_3 (ccw arc)
	double tool_radius,        //!<radius of the tool
	double current_x,  //!<first coordinate of current point
	double current_y,  //!<second coordinate of current point
	double end_x,      //!<first coordinate of arc end point
	double end_y,      //!<second coordinate of arc end point
	double i_number,   //!<first coordinate of center (abs or incr)
	double j_number,   //!<second coordinate of center (abs or incr)
	int p_number,
	double *center_x,  //!<pointer to first coordinate of center of arc
	double *center_y,  //!<pointer to second coordinate of center of arc
	int *turn, //!<pointer to number of full or partial circles CCW
	double radius_tolerance, //!<minimum radius tolerance
	double spiral_abs_tolerance,  //!<tolerance of start and end radius difference
	double spiral_rel_tolerance)
{
	double arc_radius;
	double radius2;
	CutterCompType side = runner.cutter_comp_side;
	char a = arc_axis1(runner.plane), b = arc_axis2(runner.plane);

	if (!runner.ijk_incremental) 
	{
		*center_x = (i_number);
		*center_y = (j_number);
	}
	else 
	{
		*center_x = (current_x + i_number);
		*center_y = (current_y + j_number);
	}
	arc_radius = hypot((*center_x - current_x), (*center_y - current_y));
	radius2 = hypot((*center_x - end_x), (*center_y - end_y));
	IF_T_RET_F_SETSTATE(((arc_radius < radius_tolerance) || (radius2 < radius_tolerance)),PARAMETER_ERROR,
		YA_ZERO_RADIUS_ARC_WITHARGS,
		a, current_x, b, current_y,
		a, *center_x, b, *center_y,
		a, end_x, b, end_y, arc_radius, radius2);

	double abs_err = fabs(arc_radius - radius2);
	double rel_err = abs_err / std::max(arc_radius, radius2);

	IF_T_RET_F_SETSTATE((abs_err > spiral_abs_tolerance * 100.0) ||
		(rel_err > spiral_rel_tolerance && abs_err > spiral_abs_tolerance), PARAMETER_ERROR,
		YA_RADIUS_TO_STARTARC_DIF_RADIUS_FROM_END,
		a, current_x, b, current_y,
		a, *center_x, b, *center_y,
		a, end_x, b, end_y, arc_radius, radius2,
		abs_err, rel_err * 100);

	IF_T_RET_F_SETSTATE(((arc_radius <= tool_radius) && (((side == CutterCompType_LEFT) && (move == G_3)) ||
		((side == CutterCompType_RIGHT) && (move == G_2)))), PARAMETER_ERROR, YA_TOOL_RADIUS_NOT_LESS_THAN_ARC_RADIUS_WITH_COMP);

	/* This catches an arc too small for the tool, also */
	if (move == G_2)
		*turn = -1 * p_number;
	else if (move == G_3)
		*turn = 1 * p_number;
	else
		RET_F_SETSTATE(INTERNAL_ERROR,YA_BUG_CODE_NOT_G2_OR_G3);

	return true;
}

/****************************************************************************/

/*! arc_data_comp_r

Returned Value: int
   If any of the following errors occur, this returns the error code shown.
   Otherwise, it returns INTERP_OK.
   1. The arc radius is too small to reach the end point:
	  NCE_RADIUS_TOO_SMALL_TO_REACH_END_POINT
   2. The arc radius is not greater than the tool_radius, but should be:
	  NCE_TOOL_RADIUS_NOT_LESS_THAN_ARC_RADIUS_WITH_COMP
   3. An imaginary value for offset would be found, which should never
	  happen if the theory is correct: NCE_BUG_IN_TOOL_RADIUS_COMP

Side effects:
   This finds and sets the values of center_x, center_y, and turn.

Called by: convert_arc_comp1

This finds the center coordinates and number of full or partial turns
counterclockwise of a helical or circular arc (call it arc1) in
r-format in the XY plane.  Arc2 is constructed so that it is tangent
to a circle whose radius is tool_radius and whose center is at the
point (current_x, current_y) and passes through the point (end_x,
end_y). Arc1 has the same center as arc2. The radius of arc1 is one
tool radius larger or smaller than the radius of arc2.

If the value of the big_radius argument is negative, that means [NCMS,
page 21] that an arc larger than a semicircle is to be made.
Otherwise, an arc of a semicircle or less is made.

The algorithm implemented here is to construct a line L from the
current point to the end point, and a perpendicular to it from the
center of the arc which intersects L at point P. Since the distance
from the end point to the center and the distance from the current
point to the center are known, two equations for the length of the
perpendicular can be written. The right sides of the equations can be
set equal to one another and the resulting equation solved for the
length of the line from the current point to P. Then the location of
P, the length of the perpendicular, the angle of the perpendicular,
and the location of the center, can be found in turn.

This needs to be better documented, with figures. There are eight
possible arcs, since there are three binary possibilities: (1) tool
inside or outside arc, (2) clockwise or counterclockwise (3) two
positions for each arc (of the given radius) tangent to the tool
outline and through the end point. All eight are calculated below,
since theta, radius2, and turn may each have two values.

To see two positions for each arc, imagine the arc is a hoop, the
tool is a cylindrical pin, and the arc may rotate around the end point.
The rotation covers all possible positions of the arc. It is easy to
see the hoop is constrained by the pin at two different angles, whether
the pin is inside or outside the hoop.

*/

bool GCodeInterpreter::arc_data_comp_r(int move,    //!< either G_2 (cw arc) or G_3 (ccw arc)
	double tool_radius,  //!< radius of the tool
	double current_x,    //!< first coordinate of current point
	double current_y,    //!< second coordinate of current point
	double end_x,        //!< first coordinate of arc end point
	double end_y,        //!< second coordinate of arc end point
	double big_radius,   //!< radius of arc
	int p_number,
	double *center_x,    //!< pointer to first coordinate of center of arc
	double *center_y,    //!< pointer to second coordinate of center of arc
	int *turn,           //!< pointer to number of full or partial circles CCW
	double tolerance)    //!< tolerance of differing radii
{
	double abs_radius;            // absolute value of big_radius

	CutterCompType side = runner.cutter_comp_side;

	abs_radius = fabs(big_radius);
	IF_T_RET_F_SETSTATE(((abs_radius <= tool_radius) && (((side == CutterCompType_LEFT) && (move == G_3)) ||
		((side == CutterCompType_RIGHT) && (move == G_2)))), PARAMETER_ERROR, YA_TOOL_RADIUS_NOT_LESS_THAN_ARC_RADIUS_WITH_COMP);


	return arc_data_r(move, current_x, current_y, end_x, end_y, big_radius, p_number,
		center_x, center_y, turn, tolerance);

}
