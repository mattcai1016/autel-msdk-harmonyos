#ifndef CUTPOLYGON_H
#define CUTPOLYGON_H

#include "CommonDefines.h"

namespace DroneFormation {

#define MAX_POLYGONS 20

// class of Polygon, which is defined by a list of corners
class Polygon {
   protected:
    Point corners[MAX_CORNERS];
    int size;

   public:
    Polygon();
    Polygon(Point corners[], int num_point);

    Point *get_corners() { return corners; }
    int get_size() { return size; }

    void set_size(int size_) { size = size_; }
    void set_corner(int i, Point &corner) { corners[i] = corner; }
    void set_corners(Point corners[], int num_point);

   public:
    Polygon &operator=(Polygon &poly);

    // calculate the signed area of a polygon using the shoelace formula
    double area();

    // calculate the centroid of a polygon
    void get_centroid(Point *pt);

};

}
#endif
