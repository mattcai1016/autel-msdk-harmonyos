// header for for swarm path schedule
#ifndef PATHSCHEDULE_H
#define PATHSCHEDULE_H

#include "CommonDefines.h"

namespace DroneFormation {

//void join_sort(Point a[], Point b[], int num, int index[]);
void join_sort(double a[][2], double b[][2], int num, int index[]);

//void join_path(Path paths[], int num, Path paths_new[], double speed);

void target_fmt(Point takeoff[], int num, Point &target, FormationTypeC &fmt, Point uav_pos[]);

// calculate distance between two positions (2d & 3d)
double distance2(double pos1[2], double pos2[2]);
double distance3(double pos1[3], double pos2[3]);

// calculate center of a list of positions
void center(Point pos[], int num, Point *center);
void center(double pos[][3], int num, double center[3]);

// gps and NED position conversion functions
void gps2ned(double pos_gps[3], double orig[3], double pos[3]);
void ned2gps(double pos[3], double orig[3], double pos_gps[3]);

void gps2ned(double pos_gps[][3], int num, double orig[3], double pos[][3]);

// get center position of a collections of positions
void center(double pos[][3], int num, double ct[3]);

};

#endif
