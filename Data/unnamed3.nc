xMin=0; //Specify X min of the rect:
yMin=0; //Specify Y min of the rect:
xD=80; //Width (delta X):
yD=100; //Width (delta Y):
radius=20; //Round radius:
zFull=4; //Thikness:
zDelta=1; //Step Z:
zSave=2; //Save Z:
d=6; //Mill diameter
rate=200; //Specify feed rate of cutting
zRate=50; //Specify Z feed rate of cutting
trc=1; //Tool correction: 1 - by contur, 2 inside, 3 ouside
ccw=0; //Direction: 0 - clockwise, 2- counter clockwise

include ("cut_roundrect.inc.gcmc");
DoCutRoundRect(xMin, yMin, xD, yD, radius, zFull, zSave, zDelta,d, rate,zRate,trc,ccw);