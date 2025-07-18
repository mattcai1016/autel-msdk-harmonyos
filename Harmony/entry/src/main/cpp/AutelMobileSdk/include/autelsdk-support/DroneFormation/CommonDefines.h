#ifndef COMMONDEFINES_H
#define COMMONDEFINES_H

#include <math.h>
#include <stdio.h>

namespace DroneFormation {

#define MAX_WP_NUM 100  // maximum number of waypoints in a path
#define MAX_DRONE 20    // maximum number of drones
#define MAX_CORNERS 30  // maximum number of points in a polygon

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

#define INPI(a)             \
    {                       \
        if (a > M_PI)       \
            a -= 2 * M_PI;  \
        else if (a < -M_PI) \
            a += 2 * M_PI;  \
    }
#define INPIF(a) \
    { a -= floor((a + M_PI) / (2 * M_PI)) * 2 * M_PI; }

#define EARTH_RADIUS 6.371E+6

struct FormationTypeC {
    int type;  // formation type
    int num;   // num of aircrafts

    double start_angle;  // start angle
    double end_angle;    // end angle

    double radius;  // radius of C
};

struct Point {
    double x;
    double y;
};

struct Vector {
    double dx;
    double dy;
};

struct Line {
    Point start;
    Point end;
};

inline double deg2rad(double deg) {
    return deg * M_PI / 180;
}

inline double rad2deg(double rad) {
    return rad * 180 / M_PI;
}

}; //namespace AlgorithmLite
#endif
