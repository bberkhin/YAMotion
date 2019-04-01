#include <math.h>
//#include <string>
//#include <iostream>
//#include <fstream>
#include "GCodeInterpreter.h"
#include "cmdparser.h"
#include "gcodeerrors.h"

using namespace Interpreter;

bool GCodeInterpreter::run_cycle(int motion, const Coords &position, const CmdParser &parser)
{
	IF_T_RET_F_SETSTATE((runner.feed == 0.0), PARAMETER_ERROR, YA_CANNOT_FEED_WITH_ZERO_FEED_RATE);
	//CHKS((settings->feed_mode == INVERSE_TIME), _("Cannot use inverse time feed with canned cycles"));
	IF_T_RET_F_SETSTATE((runner.cutter_comp_side), PARAMETER_ERROR, YA_CYCLES_WITH_CUT_COMP_ON);


	if (parser.hasParam(PARAM_R))
	{
		parser.getRParam(PARAM_R, &runner.cycle_r);
	}
	//if (!block->r_flag)
	//{
	//	if (settings->motion_mode == motion)
	//		block->r_number = settings->cycle_r;
	//	else
	//		ERS(NCE_R_CLEARANCE_PLANE_UNSPECIFIED_IN_CYCLE);
	//}

	int l_number = 1;
	if (parser.hasParam(PARAM_L))
	{
		parser.getIParam(PARAM_L, &l_number);
		IF_T_RET_F_SETSTATE((l_number == 0 || l_number < 0), PARAMETER_ERROR, YA_CANNOT_DO_ZERO_REPEATS_OF_CYCLE);
	}
	runner.cycle_l = l_number;

	if (runner.plane == Plane_XY)
	{
		IF_F_RET_F(run_cycle_xy(motion, position, parser));
	}
	else if (runner.plane == Plane_YZ) \
	{
		IF_F_RET_F(run_cycle_yz(motion, position, parser));
	}
	else if (runner.plane == Plane_XZ)
	{
		IF_F_RET_F(run_cycle_xz(motion, position, parser));
	}
	else
		RET_F_SETSTATE(INTERNAL_ERROR, YA_BUG_PLANE_NOT_XY_YZ_OR_XZ);
	
	runner.motion_mode = motion;
	return true;
}

bool GCodeInterpreter::run_cycle_xy(int motion, const Coords &position, const CmdParser &parser)
{
	double aa, bb;
	double aa_increment = 0., bb_increment = 0.;
	double cc, clear_cc, old_cc;
	double r;

	double current_cc = runner.position.z;

	Plane plane = Plane_XY;

	if (runner.motion_mode != motion)
	{
		IF_T_RET_F_SETSTATE(!parser.hasParam(PARAM_Z), PARAMETER_ERROR, YA_Z_VALUE_UNSPECIFIED_IN_XY_PLANE_CANNED_CYCLE);
	}

	double z_number = runner.cycle_cc;
	if (parser.hasParam(PARAM_Z))
		parser.getRParam(PARAM_Z, &z_number);

	if (runner.cycle_il)
	{
		old_cc = runner.cycle_il.value();
	}
	else
	{
		old_cc = current_cc;
		runner.cycle_il = current_cc;
	}


	cc = z_number;
	r = runner.cycle_r;

	if (runner.incremental)
	{
		parser.getRParam(PARAM_X, &aa_increment);
		parser.getRParam(PARAM_Y, &bb_increment);
		aa = runner.position.x;
		bb = runner.position.y;
	}
	else
	{
		aa_increment = 0.;
		bb_increment = 0.;
		aa = position.x;
		bb = position.y;
	}


	IF_T_RET_F_SETSTATE((r < cc), PARAMETER_ERROR, YA_R_LESS_THAN_Z_IN_CYCLE_IN_XY_PLANE );

	// First motion of a canned cycle (maybe): if we're below the R plane,
	// rapid straight up to the R plane.
	if (old_cc < r)
	{
		Coords newZ = runner.position;
		newZ.z = r;
		executor->straight_traverce(newZ);
		old_cc = r;
		current_cc = old_cc;
	}

	clear_cc = (runner.retract_mode == CannedLevel_R) ? r : old_cc;

	if (parser.hasParam(PARAM_P))
		parser.getRParam(PARAM_P, &runner.cycle_p);
	else if (motion == G_82 && runner.motion_mode != G_82) // first time 82
		RET_F_SETSTATE(INTERNAL_ERROR, YA_DWELL_TIME_P_WORD_MISSING_WITH_G82);

	if (parser.hasParam(PARAM_Q))
		parser.getRParam(PARAM_Q, &runner.cycle_q);
	else if (motion == G_73 && runner.motion_mode != G_73) // first time 73
		RET_F_SETSTATE(INTERNAL_ERROR, YA_Q_WORD_MISSING_WITH_G73);
	else if (motion == G_83 && runner.motion_mode != G_83) // first time 83
		RET_F_SETSTATE(INTERNAL_ERROR, YA_Q_WORD_MISSING_WITH_G83 );

	//save_mode = GET_EXTERNAL_MOTION_CONTROL_MODE();
	//save_tolerance = GET_EXTERNAL_MOTION_CONTROL_TOLERANCE();
	//if (save_mode != CANON_EXACT_PATH)
	//	SET_MOTION_CONTROL_MODE(CANON_EXACT_PATH, 0);

	for (int repeat = runner.cycle_l; repeat > 0; repeat--)
	{
		aa = (aa + aa_increment);
		bb = (bb + bb_increment);
		if ((repeat == runner.cycle_l) && (current_cc > r))
		{
			cycle_traverse(aa, bb, current_cc);
			cycle_traverse(aa, bb, r);
		}
		else
		{
			/* we must be at CLEAR_CC already */
			cycle_traverse(aa, bb, clear_cc);
			if (clear_cc > r)
				cycle_traverse(aa, bb, r);
		}
		switch (motion)
		{
		case G_81:
			IF_F_RET_F(run_cycle_g81(aa, bb, clear_cc, cc));
			break;
		case G_82:
			IF_F_RET_F(run_cycle_g82(aa, bb, clear_cc, cc, runner.cycle_p));
			break;
		case G_73:
			IF_F_RET_F(run_cycle_g73(aa, bb, r, clear_cc, cc, runner.cycle_q));
			break;
		case G_83:
			IF_F_RET_F(run_cycle_g83(aa, bb, r, clear_cc, cc, runner.cycle_q));
			break;
		case G_74:
		case G_84:
			RET_F_SETSTATE(INTERNAL_ERROR, YA_G74_G84_NOTSUPPORTED);
			break;
		case G_85:
		case G_86:
		case G_87:
		case G_89:
		case G_88:
			RET_F_SETSTATE(INTERNAL_ERROR, YA_G85_G88_NOTSUPPORTED);
			break;
		default:
			RET_F_SETSTATE(INTERNAL_ERROR, "run_cycle_xy internal error can not be called");
		}
	}
	runner.position.x = aa;     /* CYCLE_MACRO updates aa and bb */
	runner.position.y = bb;
	runner.position.z = clear_cc;
	runner.cycle_cc = z_number;
	//if (save_mode != CANON_EXACT_PATH)
	//	SET_MOTION_CONTROL_MODE(save_mode, save_tolerance);
	return true;
}


bool GCodeInterpreter::run_cycle_xz(int motion, const Coords &position, const CmdParser &parser)
{

	double aa, bb;
	double aa_increment = 0., bb_increment = 0.;
	double cc, clear_cc, old_cc;
	double r;

	double current_cc = runner.position.y;

	Plane plane = Plane_XZ;

	if (runner.motion_mode != motion)
	{
		IF_T_RET_F_SETSTATE(!parser.hasParam(PARAM_Y), PARAMETER_ERROR, YA_Y_VALUE_UNSPECIFIED_IN_XZ_PLANE_CANNED_CYCLE );
	}

	double y_number = runner.cycle_cc;
	if (parser.hasParam(PARAM_Y))
		parser.getRParam(PARAM_Y, &y_number);

	if (runner.cycle_il)
	{
		old_cc = runner.cycle_il.value();
	}
	else
	{
		old_cc = current_cc;
		runner.cycle_il = current_cc;
	}


	cc = y_number;
	r = runner.cycle_r;

	if (runner.incremental)
	{
		parser.getRParam(PARAM_Z, &aa_increment);
		parser.getRParam(PARAM_X, &bb_increment);
		aa = runner.position.z;
		bb = runner.position.x;
	}
	else
	{
		aa_increment = 0.;
		bb_increment = 0.;
		aa = position.z;
		bb = position.x;
	}

	IF_T_RET_F_SETSTATE((r < cc), PARAMETER_ERROR, YA_R_LESS_THAN_Y_IN_CYCLE_IN_XZ_PLANE);



	// First motion of a canned cycle (maybe): if we're below the R plane,
	// rapid straight up to the R plane.
	if (old_cc < r)
	{
		Coords newZ = runner.position;
		newZ.z = r;
		executor->straight_traverce(newZ);
		old_cc = r;
		current_cc = old_cc;
	}

	clear_cc = (runner.retract_mode == CannedLevel_R) ? r : old_cc;

	if (parser.hasParam(PARAM_P))
		parser.getRParam(PARAM_P, &runner.cycle_p);
	else if (motion == G_82 && runner.motion_mode != G_82) // first time 82
		RET_F_SETSTATE(INTERNAL_ERROR, YA_DWELL_TIME_P_WORD_MISSING_WITH_G82);

	if (parser.hasParam(PARAM_Q))
		parser.getRParam(PARAM_Q, &runner.cycle_q);
	else if (motion == G_73 && runner.motion_mode != G_73) // first time 73
		RET_F_SETSTATE(INTERNAL_ERROR, YA_Q_WORD_MISSING_WITH_G73);
	else if (motion == G_83 && runner.motion_mode != G_83) // first time 83
		RET_F_SETSTATE(INTERNAL_ERROR, YA_Q_WORD_MISSING_WITH_G83);

	//save_mode = GET_EXTERNAL_MOTION_CONTROL_MODE();
	//save_tolerance = GET_EXTERNAL_MOTION_CONTROL_TOLERANCE();
	//if (save_mode != CANON_EXACT_PATH)
	//	SET_MOTION_CONTROL_MODE(CANON_EXACT_PATH, 0);

	for (int repeat = runner.cycle_l; repeat > 0; repeat--)
	{
		aa = (aa + aa_increment);
		bb = (bb + bb_increment);
		if ((repeat == runner.cycle_l) && (current_cc > r))
		{
			cycle_traverse(aa, bb, current_cc);
			cycle_traverse(aa, bb, r);
		}
		else
		{
			/* we must be at CLEAR_CC already */
			cycle_traverse(aa, bb, clear_cc);
			if (clear_cc > r)
				cycle_traverse(aa, bb, r);
		}
		switch (motion)
		{
		case G_81:
			IF_F_RET_F(run_cycle_g81(aa, bb, clear_cc, cc));
			break;
		case G_82:
			IF_F_RET_F(run_cycle_g82(aa, bb, clear_cc, cc, runner.cycle_p));
			break;
		case G_73:
			IF_F_RET_F(run_cycle_g73(aa, bb, r, clear_cc, cc, runner.cycle_q));
			break;
		case G_83:
			IF_F_RET_F(run_cycle_g83(aa, bb, r, clear_cc, cc, runner.cycle_q));
			break;
		case G_74:
		case G_84:
			RET_F_SETSTATE(INTERNAL_ERROR, YA_G74_G84_NOTSUPPORTED);
			break;
		case G_85:
		case G_86:
		case G_87:
		case G_89:
		case G_88:
			RET_F_SETSTATE(INTERNAL_ERROR, YA_G85_G88_NOTSUPPORTED);
			break;
		default:
			RET_F_SETSTATE(INTERNAL_ERROR, "run_cycle_xy internal error can not be called");
		}
	}
	runner.position.z = aa;     /* CYCLE_MACRO updates aa and bb */
	runner.position.x = bb;
	runner.position.y = clear_cc;
	runner.cycle_cc = y_number;

	//if (save_mode != CANON_EXACT_PATH)
	//	SET_MOTION_CONTROL_MODE(save_mode, save_tolerance);
	return true;
}



bool GCodeInterpreter::run_cycle_yz(int motion, const Coords &position, const CmdParser &parser)
{

	double aa, bb;
	double aa_increment = 0., bb_increment = 0.;
	double cc, clear_cc, old_cc;
	double r;

	double current_cc = runner.position.x;

	Plane plane = Plane_YZ;

	if (runner.motion_mode != motion)
	{
		IF_T_RET_F_SETSTATE(!parser.hasParam(PARAM_X), PARAMETER_ERROR, YA_X_VALUE_UNSPECIFIED_IN_YZ_PLANE_CANNED_CYCLE);
	}

	double x_number = runner.cycle_cc;
	if (parser.hasParam(PARAM_X))
		parser.getRParam(PARAM_X, &x_number);

	if (runner.cycle_il)
	{
		old_cc = runner.cycle_il.value();
	}
	else
	{
		old_cc = current_cc;
		runner.cycle_il = current_cc;
	}


	cc = x_number;
	r = runner.cycle_r;

	if (runner.incremental)
	{
		parser.getRParam(PARAM_Y, &aa_increment);
		parser.getRParam(PARAM_Z, &bb_increment);
		aa = runner.position.z;
		bb = runner.position.x;
	}
	else
	{
		aa_increment = 0.;
		bb_increment = 0.;
		aa = position.y;
		bb = position.z;
	}

	IF_T_RET_F_SETSTATE((r < cc), PARAMETER_ERROR, YA_R_LESS_THAN_X_IN_CYCLE_IN_YZ_PLANE );



	// First motion of a canned cycle (maybe): if we're below the R plane,
	// rapid straight up to the R plane.
	if (old_cc < r)
	{
		Coords newZ = runner.position;
		newZ.z = r;
		executor->straight_traverce(newZ);
		old_cc = r;
		current_cc = old_cc;
	}

	clear_cc = (runner.retract_mode == CannedLevel_R) ? r : old_cc;

	if (parser.hasParam(PARAM_P))
		parser.getRParam(PARAM_P, &runner.cycle_p);
	else if (motion == G_82 && runner.motion_mode != G_82) // first time 82
		RET_F_SETSTATE(INTERNAL_ERROR, YA_DWELL_TIME_P_WORD_MISSING_WITH_G82);

	if (parser.hasParam(PARAM_Q))
		parser.getRParam(PARAM_Q, &runner.cycle_q);
	else if (motion == G_73 && runner.motion_mode != G_73) // first time 73
		RET_F_SETSTATE(INTERNAL_ERROR, YA_Q_WORD_MISSING_WITH_G73);
	else if (motion == G_83 && runner.motion_mode != G_83) // first time 83
		RET_F_SETSTATE(INTERNAL_ERROR, YA_Q_WORD_MISSING_WITH_G83);

	//save_mode = GET_EXTERNAL_MOTION_CONTROL_MODE();
	//save_tolerance = GET_EXTERNAL_MOTION_CONTROL_TOLERANCE();
	//if (save_mode != CANON_EXACT_PATH)
	//	SET_MOTION_CONTROL_MODE(CANON_EXACT_PATH, 0);

	for (int repeat = runner.cycle_l; repeat > 0; repeat--)
	{
		aa = (aa + aa_increment);
		bb = (bb + bb_increment);
		if ((repeat == runner.cycle_l) && (current_cc > r))
		{
			cycle_traverse(aa, bb, current_cc);
			cycle_traverse(aa, bb, r);
		}
		else
		{
			/* we must be at CLEAR_CC already */
			cycle_traverse(aa, bb, clear_cc);
			if (clear_cc > r)
				cycle_traverse(aa, bb, r);
		}
		switch (motion)
		{
		case G_81:
			IF_F_RET_F(run_cycle_g81(aa, bb, clear_cc, cc));
			break;
		case G_82:
			IF_F_RET_F(run_cycle_g82(aa, bb, clear_cc, cc, runner.cycle_p));
			break;
		case G_73:
			IF_F_RET_F(run_cycle_g73(aa, bb, r, clear_cc, cc, runner.cycle_q));
			break;
		case G_83:
			IF_F_RET_F(run_cycle_g83(aa, bb, r, clear_cc, cc, runner.cycle_q));
			break;
		case G_74:
		case G_84:
			RET_F_SETSTATE(INTERNAL_ERROR, YA_G74_G84_NOTSUPPORTED);
			break;
		case G_85:
		case G_86:
		case G_87:
		case G_89:
		case G_88:
			RET_F_SETSTATE(INTERNAL_ERROR, YA_G85_G88_NOTSUPPORTED);
			break;
		default:
			RET_F_SETSTATE(INTERNAL_ERROR, "run_cycle_xy internal error can not be called");
		}
	}
	runner.position.y = aa;     /* CYCLE_MACRO updates aa and bb */
	runner.position.z = bb;
	runner.position.x = clear_cc;
	runner.cycle_cc = x_number;

	//if (save_mode != CANON_EXACT_PATH)
	//	SET_MOTION_CONTROL_MODE(save_mode, save_tolerance);
	return true;
}


bool GCodeInterpreter::cycle_move(bool tavers, double e1, double e2, double e3, Plane pl)
{
	if (pl == Plane_NONE)
		pl = runner.plane;

	Coords pos = runner.position;
	if (pl == Plane_XY)
		pos.Set(e1, e2, e3, false);
	else if (pl == Plane_YZ)
		pos.Set(e3, e1, e2, false);
	else if (pl == Plane_XZ)
		pos.Set(e2, e3, e1, false);
	else
		pos.Set(e1, e2, e3, false);

	if (tavers)
		executor->straight_traverce(pos);
	else
		executor->straight_feed(pos);
	return true;
}

bool GCodeInterpreter::run_cycle_g81(double x, double y, double clear_z, double bottom_z)
{
	cycle_feed(x, y, bottom_z);
	cycle_traverse(x, y, clear_z);
	return true;
}

bool GCodeInterpreter::run_cycle_g82(
	double x,  //!< x-value where cycle is executed 
	double y,  //!< y-value where cycle is executed 
	double clear_z,    //!< z-value of clearance plane      
	double bottom_z,   //!< value of z at bottom of cycle   
	double dwell)      //!< dwell time                      
{
	cycle_feed(x, y, bottom_z);
	executor->set_dwell(static_cast<long>(dwell));
	cycle_traverse(x, y, clear_z);
	return true;
}

bool GCodeInterpreter::run_cycle_g83(
	double x,  //!< x-value where cycle is executed 
	double y,  //!< y-value where cycle is executed 
	double r,  //!< initial z-value                 
	double clear_z,    //!< z-value of clearance plane      
	double bottom_z,   //!< value of z at bottom of cycle   
	double delta)      //!< size of z-axis feed increment   
{
	/* Moved the check for negative Q values here as a sign
		may be used with user defined M functions
		Thanks to Billy Singleton for pointing it out... */
	IF_T_RET_F_SETSTATE((delta <= 0.0), PARAMETER_ERROR, YA_NEGATIVE_OR_ZERO_Q_VALUE_USED );

	double rapid_delta = G83_RAPID_DELTAMM;

	for (double current_depth = (r - delta);
		current_depth > bottom_z; current_depth = (current_depth - delta))
	{
		cycle_feed(x, y, current_depth);
		cycle_traverse(x, y, r);
		cycle_traverse(x, y, current_depth + rapid_delta);
	}
	cycle_feed(x, y, bottom_z);
	cycle_traverse(x, y, clear_z);
	return true;
}

bool GCodeInterpreter::run_cycle_g73(
	double x,  //!< x-value where cycle is executed 
	double y,  //!< y-value where cycle is executed 
	double r,  //!< initial z-value                 
	double clear_z,    //!< z-value of clearance plane      
	double bottom_z,   //!< value of z at bottom of cycle   
	double delta)      //!< size of z-axis feed increment   
{
	/* Moved the check for negative Q values here as a sign
	   may be used with user defined M functions
	   Thanks to Billy Singleton for pointing it out... */

	IF_T_RET_F_SETSTATE((delta <= 0.0), PARAMETER_ERROR, YA_NEGATIVE_OR_ZERO_Q_VALUE_USED);

	double rapid_delta = G83_RAPID_DELTAMM;

	for (double current_depth = (r - delta);
		current_depth > bottom_z; current_depth = (current_depth - delta))
	{
		cycle_feed(x, y, current_depth);
		cycle_traverse(x, y, current_depth + rapid_delta);
	}
	cycle_feed(x, y, bottom_z);
	cycle_traverse(x, y, clear_z);

	return true;
}
