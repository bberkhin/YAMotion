#include "wx/wx.h"

#include "ExecutorView.h"
#include <iostream>
#include <string>
//#include <fstream>
#include <stdio.h>
#include "defsext.h"     // Additional definitions
//#include "CoordMotion.h" 

using namespace std;
using namespace Interpreter;

ExecutorView::ExecutorView(ILogger *_logger, IEnvironment *penv, wxThread *thr) :
	ExecutorLogWnd(_logger, thr, false)
{
	//pcm = new CCoordMotion( logger, 0 );
	//pcm->m_DisableSoftLimits = true;
	//pcm->m_Simulate = true;
	m_current_feed = penv->GetDefaultFeedRate();
	m_fast_speed = penv->GetDefaultMoveSpeed();
}

ExecutorView::~ExecutorView()
{
	//if (pcm)
		//delete pcm;
}

void ExecutorView::output(const std::string &str)
{
	if (!logger)
	return;
}

void ExecutorView::output(const std::string &str, const Coords &position)
{

}

 void ExecutorView::addTrackPoint(TypeMove type, const Coords &position)
 {
	 ExecutorLog::addTrackPoint(type, position);
	 TrackPointGL point;

	 point.isFast = type == fast ? true : false;
	 point.line = nline;
	 point.position.x = position.x;
	 point.position.y = position.y;
	 point.position.z = position.z;
	 point.speed = (type == fast) ? m_fast_speed : m_current_feed;
	 m_points.push_back(point);	 

 }

 void ExecutorView::set_feed_rate(double feed)
 {
	 if (feed <= 1 || feed > MAX_FEED_RATE)
		 logger->log(LOG_ERROR, _("Line %d: Error feedrate value %g"), nline, feed );
	else
		m_current_feed = feed;
 }


 void ExecutorView::arc_feed(RunnerData *rd, double &end1, double &end2, double &center1, double &center2, int rotation, double &end3, double &a, double &b, double &c, double &u, double &v)
 {
	 if (rd->plane == Plane_XY)
	 {
		 ArcFeed(rd->plane,
			 end1 + rd->tool_xoffset,
			 end2 + rd->tool_yoffset,
			 center1 + rd->tool_xoffset,
			 center2 + rd->tool_yoffset,
			 (rotation == 1 ? 1 : 0),
			 end3 + rd->tool_length_offset,
			 a, b, c);
	 }
	 else if (rd->plane == Plane_XZ)
	 {
		 // Actually more like ZX plane
		 ArcFeed(rd->plane,
			 end1 + rd->tool_length_offset,
			 end2 + rd->tool_xoffset,
			 center1 + rd->tool_length_offset,
			 center2 + rd->tool_xoffset,
			 (rotation == 1 ? 1 : 0),
			 end3 + rd->tool_yoffset,
			 a, b, c);
	 }
	 else
	 {
		 ArcFeed(rd->plane,
			 end1 + rd->tool_yoffset,
			 end2 + rd->tool_length_offset,
			 center1 + rd->tool_yoffset,
			 center2 + rd->tool_length_offset,
			 (rotation == 1 ? 1 : 0),
			 end3 + rd->tool_xoffset,
			 a, b, c);
	 }
 }


 void ExecutorView::ArcFeed(Plane plane,
	 double first_end, double second_end,
	 double first_axis, double second_axis, int rotation,
	 double axis_end_point, double a, double b, double c)
 {

	 double invd, radius, theta0, theta1, d_theta, dxy, theta;
	 double sum2;
	 int n_segs, i;
	 double first_start, second_start, axis_start_point;
	 Coords pt;

	 if (plane == Plane_XY)
	 {
		 first_start = cur_position.x;
		 second_start = cur_position.y;
		 axis_start_point = cur_position.z;
	 }
	 else if (plane == Plane_XZ)
	 {
		 first_start = cur_position.z;
		 second_start = cur_position.x;
		 axis_start_point = cur_position.y;
	 }
	 else // YZ
	 {
		 first_start = cur_position.y;
		 second_start = cur_position.z;
		 axis_start_point = cur_position.x;
	 }

	 double dx = first_start - first_axis;
	 double dy = second_start - second_axis;
	 double dz = axis_end_point - axis_start_point;

	 radius = sqrt(dx*dx + dy * dy);

	 theta0 = atan2(second_start - second_axis, first_start - first_axis);
	 theta1 = atan2(second_end - second_axis, first_end - first_axis);

	 d_theta = theta1 - theta0;

	 if (fabs(d_theta) < THETA_SIGMA) d_theta = 0;  // force super small arcs to zero

	 if (rotation)
	 {
		 if (d_theta <= 0.0f) d_theta += TWO_PI; // CCW delta should be +  
	 }
	 else
	 {
		 if (d_theta >= 0.0f) d_theta -= TWO_PI;  // CW delta should be -
	 }



	 dxy = d_theta * radius;  // path length along circle                                   

	 sum2 = dxy * dxy + dz * dz;

	 if (sum2 > 0.0f)
		 invd = 1.0f / sqrt(sum2); // inverse total length
	 else
		 sum2 = 0.0f;

	 // compute number of line segments to achieve desired tolerance
	 //
	 //
	 // given tolerance T and Radius R the largest angle of a segment is:
	 //
	 // max_theta = acos(1 - T/radius)
	 // but actually for now just do N_SEG sided circles
	 int N_SEG = 100;
	 n_segs = (int)fabs(N_SEG * d_theta / TWO_PI) + 1;

	 for (i = 1; i <= n_segs; i++)
	 {
		 double xp, yp, zp;

		 theta = theta0 + (double)i * d_theta / n_segs;

		 xp = radius * cos(theta) + first_axis;
		 yp = radius * sin(theta) + second_axis;
		 zp = (double)i * dz / n_segs + axis_start_point;

		 if (plane == Plane_XY)
		 {
			 pt.x = xp;
			 pt.y = yp;
			 pt.z = zp;
		 }
		 else if (plane == Plane_XZ)
		 {
			 pt.x = yp;
			 pt.y = zp;
			 pt.z = xp;
		 }
		 else // YZ
		 {
			 pt.x = zp;
			 pt.y = xp;
			 pt.z = yp;
		 }


		 //// rotation about X axis changes Y and Z Axis as a function of A
		 //if (TheFrame->GViewDlg.m_IncludeA && MP->DegreesA && MP->RadiusA > 0.0)
		 //{
			// double Theta = a * PI / 180.0;
			// double y0 = y + MP->RadiusA;
			// y = y0 * cos(Theta) - z * sin(Theta);
			// z = y0 * sin(Theta) + z * cos(Theta);
		 //}

		 //// rotation about Y axis changes Z and X Axis as a function of B
		 //if (TheFrame->GViewDlg.m_IncludeB && MP->DegreesB && MP->RadiusB > 0.0)
		 //{
			// double Theta = b * PI / 180.0;
			// double z0 = z + MP->RadiusB;
			// z = z0 * cos(Theta) - x * sin(Theta);
			// x = z0 * sin(Theta) + x * cos(Theta);
		 //}

		 //// rotation about Z axis changes X and Y Axis as a function of C
		 //if (TheFrame->GViewDlg.m_IncludeC && MP->DegreesC && MP->RadiusC > 0.0)
		 //{
			// double Theta = c * PI / 180.0;
			// double x0 = x + MP->RadiusC;
			// x = x0 * cos(Theta) - y * sin(Theta);
			// y = x0 * sin(Theta) + y * cos(Theta);
		 //}
		 addTrackPoint(feedarc, pt);
	 }
 }
