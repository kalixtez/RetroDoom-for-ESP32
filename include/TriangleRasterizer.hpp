#ifndef TRIANGLE_RASTERIZER_H
#define TRIANGLE_RASTERIZER_H

#include <Driver.hpp>

struct Slope // Slope info
{
    float slope;
    int line_span;
    float z1; // Depth of the vertices that define the slope. (Projected depth)
    float z2;
};

class TrigRasterizer
{
    public:
        TrigRasterizer();
    
    void interpolate_and_draw(Point, Point, Point);

};



#endif