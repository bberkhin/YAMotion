// CoordMotion.h: interface for the CCoordMotion class.
/*********************************************************************/
/*         Copyright (c) 2003-2006  DynoMotion Incorporated          */
/*********************************************************************/



#if !defined(AFX_COORDMOTION_H_INCLUDED_)
#define AFX_COORDMOTION_H_INCLUDED_

#include <string>
#include "gcodedefs.h"
#include "TrajectoryPlanner.h"


class ILogger;

namespace Interpreter
{

	typedef void STRAIGHT_TRAVERSE_CALLBACK(double x, double y, double z, int sequence_number);

	typedef void STRAIGHT_TRAVERSE_SIX_AXIS_CALLBACK(double x, double y, double z, double a, double b, double c, int sequence_number);

	typedef void STRAIGHT_FEED_CALLBACK(double DesiredFeedRate_in_per_sec,
		double x, double y, double z, int sequence_number, int ID);

	typedef void STRAIGHT_FEED_CALLBACK_SIX_AXIS(double DesiredFeedRate_in_per_sec,
		double x, double y, double z, double a, double b, double c, int sequence_number, int ID);

	typedef void ARC_FEED_CALLBACK(bool ZeroLenAsFullCircles, double DesiredFeedRate_in_per_sec,
		Plane plane,
		double first_end, double second_end,
		double first_axis, double second_axis, int rotation,
		double axis_end_point,
		double first_start, double second_start, double axis_start_point, int sequence_number, int ID);
	typedef void ARC_FEED_SIX_AXIS_CALLBACK(bool ZeroLenAsFullCircles, double DesiredFeedRate_in_per_sec,
		Plane plane,
		double first_end, double second_end,
		double first_axis, double second_axis, int rotation,
		double axis_end_point, double a, double b, double c,
		double first_start, double second_start, double axis_start_point, int sequence_number, int ID);

	enum { STOPPED_NONE, STOPPED_INDEP, STOPPED_COORD, STOPPED_COORD_FINISHED };


	class IOutput
	{
	public:
		virtual  int WriteLine(const char *s) = 0;
		virtual  int WriteLineReadLine(const char *s, std::string &response) = 0;
		virtual  int ReadLineTimeOut(std::string &response) = 0;
		virtual  int WaitToken(bool b, int n, const char *s) = 0;
		virtual  int WaitToken(const char *s) = 0;
		virtual void ReleaseToken() = 0;
	};



	class CKinematics;
	
	class CCoordMotion
	{
	public:
		CCoordMotion(ILogger *plog, IOutput *_hrout);
		virtual ~CCoordMotion();
		void DownloadInit();
		int CheckMotionHalt(bool Coord);
		int ExecutionStop();
		double GetFeedRateOverride();
		double GetFeedRateRapidOverride();
		double GetSpindleRateOverride();
		void SetFeedRateOverride(double v);
		void SetFeedRateRapidOverride(double v);
		void SetHardwareFRORange(double v);
		double GetHardwareFRORange();
		void SetSpindleRateOverride(double v);
		int GetDestination(int axis, double *d);
		int GetPosition(int axis, double *d);
		int GetAxisDone(int axis, int *r);

		

		void SetAbort();
		void ClearAbort();
		bool GetAbort();

		void SetHalt();
		void ClearHalt();
		bool GetHalt();

		int FlushSegments();
		int WaitForSegmentsFinished(bool NoErrorOnDisable = false);
		int WaitForMoveXYZABCFinished();
		int DoKMotionCmd(const char *s, bool FlushBeforeUnbufferedOperation);
		int DoKMotionBufCmd(const char *s, int sequence_number = -1);
		MOTION_PARAMS *GetMotionParams();

		int MeasurePointAppendToFile(const char *name);
		int StraightTraverse(double x, double y, double z, double a, double b, double c, bool NoCallback = false, int sequence_number = -1, int ID = 0);
		int StraightTraverse(double x, double y, double z, double a, double b, double c, double u, double v, bool NoCallback = false, int sequence_number = -1, int ID = 0);

		int ArcFeed(double DesiredFeedRate_in_per_sec, Plane plane,
			double first_end, double second_end,
			double first_axis, double second_axis, int rotation,
			double axis_end_point, double a, double b, double c, int sequence_number, int ID);

		int ArcFeed(double DesiredFeedRate_in_per_sec, Plane plane,
			double first_end, double second_end,
			double first_axis, double second_axis, int rotation,
			double axis_end_point, double a, double b, double c, double u, double v, int sequence_number, int ID);

		int ArcFeedAccel(double DesiredFeedRate_in_per_sec, double DesiredAccel, Plane plane,
			double first_end, double second_end,
			double first_axis, double second_axis, int rotation,
			double axis_end_point, double a, double b, double c, int sequence_number, int ID);

		int ArcFeedAccel(double DesiredFeedRate_in_per_sec, double DesiredAccel, Plane plane,
			double first_end, double second_end,
			double first_axis, double second_axis, int rotation,
			double axis_end_point, double a, double b, double c, double u, double v, int sequence_number, int ID);

		int StraightFeed(double DesiredFeedRate_in_per_sec,
			double x, double y, double z, double a, double b, double c, int sequence_number, int ID);

		int StraightFeed(double DesiredFeedRate_in_per_sec,
			double x, double y, double z, double a, double b, double c, double u, double v, int sequence_number, int ID);

		int StraightFeedAccel(double DesiredFeedRate_in_per_sec, double DesiredAccel,
			double x, double y, double z, double a, double b, double c, int sequence_number, int ID);

		int StraightFeedAccel(double DesiredFeedRate_in_per_sec, double DesiredAccel,
			double x, double y, double z, double a, double b, double c, double u, double v, int sequence_number, int ID);

		int StraightFeedAccelRapid(double DesiredFeedRate_in_per_sec, double DesiredAccel, bool RapidMode, bool NoCallback,
			double x, double y, double z, double a, double b, double c, int sequence_number, int ID);

		int StraightFeedAccelRapid(double DesiredFeedRate_in_per_sec, double DesiredAccel, bool RapidMode, bool NoCallback,
			double x, double y, double z, double a, double b, double c, double u, double v, int sequence_number, int ID);


		int Dwell(double seconds, int sequence_number = 0);

		int ReadCurAbsPosition(double *x, double *y, double *z, double *a, double *b, double *c, bool snap = false, bool NoGeo = false);
		int ReadCurAbsPosition(double *x, double *y, double *z, double *a, double *b, double *c, double *u, double *v, bool snap = false, bool NoGeo = false);

		void SetStraightTraverseCallback(STRAIGHT_TRAVERSE_CALLBACK *p);
		void SetStraightTraverseCallback(STRAIGHT_TRAVERSE_SIX_AXIS_CALLBACK *p);
		void SetStraightFeedCallback(STRAIGHT_FEED_CALLBACK *p);
		void SetStraightFeedCallback(STRAIGHT_FEED_CALLBACK_SIX_AXIS *p);
		void SetArcFeedCallback(ARC_FEED_CALLBACK *p);
		void SetArcFeedCallback(ARC_FEED_SIX_AXIS_CALLBACK *p);
		int DownloadDoneSegments();
		int OutputSegment(int iseg);
		int DoSpecialCommand(int iseg);
		int DoSpecialInitialCommands();
		void DoSegmentCallbacks(int i0, int n);
		void DoSegmentCallbacksRapid(int i0, int i1);
		int DoRateAdjustments(int i0, int i1);
		int DoRateAdjustmentsArc(int i, double radius, double theta0, double dtheta, double dcircle);

		int CheckSoftLimits(double x, double y, double z, double a, double b, double c, double u, double v, std::string &errmsg);
		int CheckSoftLimitsArc(double XC, double YC, double Z1,
			double SoftLimitPosX, double SoftLimitNegX,
			double SoftLimitPosY, double SoftLimitNegY,
			double SoftLimitPosZ, double SoftLimitNegZ,
			double a, double b, double c, double u, double v, bool DirIsCCW,
			double radius, double theta0, double dtheta,
			int x_axis, int y_axis, int z_axis,
			char XSTR, char YSTR, char ZSTR, std::string &errmsg);


		double m_TotalDownloadedTime;
		int m_nsegs_downloaded;
		double m_TimeAlreadyExecuted;

		int m_realtime_Sequence_number;  // latest sequence number where KFLOP is currently executing
		bool m_realtime_Sequence_number_valid;  // latest sequence number where KFLOP is currently executing is valid


		char MainPath[MAX_PATH], MainPathRoot[MAX_PATH];

		int m_board_type;

		bool m_Simulate;

		bool m_ThreadingMode;            // Launches coordinated motion in spindle sync mode
		double m_ThreadingBaseSpeedRPS;  // Base Rev/sec speed where trajectory should run an real-time

		bool m_DisableSoftLimits;

		bool m_AxisDisabled;

		bool m_TCP_affects_actuators;

		int m_Stopping;
		int m_PreviouslyStopped, m_PreviouslyStoppedType, m_PreviouslyStoppedID, m_PreviouslyStoppedSeqNo;

		double m_Stoppedx, m_Stoppedy, m_Stoppedz, m_Stoppeda, m_Stoppedb, m_Stoppedc, m_Stoppedu, m_Stoppedv;
		double m_StoppedMidx, m_StoppedMidy, m_StoppedMidz, m_StoppedMida, m_StoppedMidb, m_StoppedMidc, m_StoppedMidu, m_StoppedMidv;
		double m_StoppedMachinex, m_StoppedMachiney, m_StoppedMachinez, m_StoppedMachinea, m_StoppedMachineb, m_StoppedMachinec, m_StoppedMachineu, m_StoppedMachinev;

		int SetAxisDefinitions(int x, int y, int z, int a, int b, int c);
		int SetAxisDefinitions(int x, int y, int z, int a, int b, int c, int u, int v);
		int GetAxisDefinitions(int *x, int *y, int *z, int *a, int *b, int *c);
		int GetAxisDefinitions(int *x, int *y, int *z, int *a, int *b, int *c, int *u, int *v);
		bool m_DefineCS_valid;
		int x_axis, y_axis, z_axis, a_axis, b_axis, c_axis, u_axis, v_axis;  // map board channel number to interperter axis 

		double current_x, current_y, current_z, current_a, current_b, current_c, current_u, current_v;

		STRAIGHT_TRAVERSE_CALLBACK *m_StraightTraverseCallback;
		STRAIGHT_TRAVERSE_SIX_AXIS_CALLBACK *m_StraightTraverseSixAxisCallback;
		STRAIGHT_FEED_CALLBACK *m_StraightFeedCallback;
		STRAIGHT_FEED_CALLBACK_SIX_AXIS *m_StraightFeedSixAxisCallback;

		void SetTPParams();

		int GetRapidSettings();
		int GetRapidSettingsAxis(int axis, double *Vel, double *Accel, double *Jerk, double *SoftLimitPos, double *SoftLimitNeg, double CountsPerInch);
		bool RapidParamsDirty;

		void SetPreviouslyStoppedAtSeg(SEGMENT *segs_to_check, int i);

		double FeedRateDistance(double dx, double dy, double dz, double da, double db, double dc, bool *PureAngle);
		double FeedRateDistance(double dx, double dy, double dz, double da, double db, double dc, double du, double dv, bool *PureAngle);
		int ConfigSpindle(int type, int axis, double UpdateTime, double Tau, double CountsPerRev);
		int GetSpindleRPS(float &speed);

		bool m_TapCycleInProgress;
		CKinematics *Kinematics;
	protected: //KMotionDLL functions
		

	private:
		ILogger *logger;
		IOutput *hrout;
		bool m_Abort;
		bool m_Halt;
		double m_FeedRateOverride;
		double m_FeedRateRapidOverride;
		double m_HardwareFRORange;
		double m_SpindleRateOverride;
		ARC_FEED_CALLBACK *m_ArcFeedCallback;
		ARC_FEED_SIX_AXIS_CALLBACK *m_ArcFeedSixAxisCallback;
		bool m_SegmentsStartedExecuting;
		int m_NumLinearNotDrawn;
		std::string WriteLineBuffer;
		double WriteLineBufferTime;
		int PutWriteLineBuffer(std::string s, double Time);
		int FlushWriteLineBuffer();
		int ClearWriteLineBuffer();
		int CommitPendingSegments(bool RapidMode);
		int LaunchCoordMotion();
		int UpdateRealTimeState(double T);
		void DetermineSoftwareHardwareFRO(double &HW, double &SW);
	};

};
#endif // !defined(AFX_COORDMOTION_H__36110031_9633_4D82_9C05_E1FDEC3AC8EA__INCLUDED_)
