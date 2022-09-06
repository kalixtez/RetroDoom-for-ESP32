#include <TriangleRasterizer.hpp>
#include <tuple>
#include <bits/stdc++.h>

TrigRasterizer::TrigRasterizer()
{

}

// A polygon MUST BE PROPERLY triangulated before its points are passed to this function.
void TrigRasterizer::interpolate_and_draw(Point p1, Point p2, Point p3) // Triangles are nice. Well, more like simple. But simple usually means nice.
{
    auto t1 = std::tie(p1.y_coord, p1.x_coord, p1.z_depth); // Three tuples that contain the three coordinates of the triangle.
    auto t2 = std::tie(p2.y_coord, p2.x_coord, p2.z_depth); // Using tuples because of the class' relational operators.
    auto t3 = std::tie(p3.y_coord, p3.x_coord, p3.z_depth);

    // Order the points so t1, t2 and t3 are in ascending order (t1 having the smallest y coordinate and t3 the greatest).
    if(t1 > t2) std::swap(t1, t2);
    if(t1 > t3) std::swap(t1, t3);
    if(t2 > t3) std::swap(t2, t3);
    // After the instructions above the points will be sorted in ascending order.
    auto [y0, x0, z0, y1, x1, z1, y2, x2, z2] = std::tuple_cat(t1, t2, t3);

    if(x0 == x1 && x0 == x2)
    {

        for(int y = y0; y <= y2; y++)
            DriverLCD::draw_pixel(x0, y);

        return;
    }

    if(y0 == y1 && y0 == y2)
    {
        if(x0 > x2)
            std::swap(x0, x2);
        if(x0 > x1)
            std::swap(x0, x1);
        if(x1 > x2)
            std::swap(x1, x2);
        for(int x = x0; x <= x2; x++)
            DriverLCD::draw_pixel(x, y0);

        return;
    }

    Slope slope_1;
    if (y1 == y0)
        slope_1 = {0, 1, 0, 0};
    else
        slope_1 = {(x1 - x0)/(float)(y1 - y0), y1 - y0, z0, z1}; // Slope from the top to the middle. (shortside)
    Slope slope_2 = {(x2 - x0)/(float)(y2 - y0), y2 - y0, z0, z2}; // Slope from te top to the bottom (longside) 
    Slope slope_3;
    if (y2 == y1)
        slope_3 = {0, 1, 0, 0};
    else
        slope_3 = {(x2 - x1)/(float)(y2 - y1), y2 - y1, z1, z2}; // Slope from the middle to the bottom. (bottom shortside)
    // In order to know the start and endpoints of the scanline, we need to know first which slope 
    // is on the right and which slope is on the left.
    // Not using Bresenham's optimization (not using floats) because it's not necessary (simplicity, might change in a future).

    bool top_bottom_side = ((y1 - y0) * (x2 - x0) > (y2 - y0) * (x1 - x0)); // If this is true then the slope going from top to bottom is on the right.
    Slope slopes[2]; // If top-bottom edge is on the right then slopes[0] = slope_1 and slopes[1] = slopes_2, and the oposite if it's on the left.
    
    slopes[top_bottom_side] = slope_2;
    slopes[!top_bottom_side] = slope_1;
    // else, it's on the left.

    if(y0 == y1)
    {
        return;
        if(x0 > x1)
            std::swap(x0, x1);
        for(int st = x0; st <= x1; st++)
            DriverLCD::draw_pixel(st, y0);
    }

    else if(y1 == y2)
    {
        if(x1 > x2)
            std::swap(x1, x2);
        for(int st = x1; st <= x2; st++)
            DriverLCD::draw_pixel(st, y1);
    }

    for(int y = y0, xr = x0, xl = x0, yl = y0, yr = y0; y <= y2; y++) // Iterate through every scanline that composes the triangle.
    {
        if(y >= y1) // Change the (end or start) slope when we get to the middle-to-bottom slope.
        {
            (top_bottom_side) ? xl = x1 : xr = x1; // If the longside is on the right, then starting scanline coordinate (startx) will now be calculated as an "offset" of the x1 coordinate.
            (top_bottom_side) ? yl = y1 : yr = y1; // If the longside is on the right, then endpoint of the scanline (endx) will now be calculated as an "offset" of the x1 coordinate.
            slopes[!top_bottom_side] = slope_3;  // top-middle side it's always on the same side as the top-middle, which is slopes[!top_bottom_side]
        }

        int startx = (int)(xl + ((y - yl) * slopes[0].slope)), endx = (int)(xr + ((y - yr)*slopes[1].slope)); // *Puede que sea mejor usar floor().
        DriverLCD::draw_pixel(startx, y);
        DriverLCD::draw_pixel(endx, y);
      /*
        for(int sc_px = startx; sc_px <= endx; sc_px++)
        {
            
            
            float zrec_l = slopes[0].z1*(1 - (y - yl)/slopes[0].line_span) + (((y - yl)/slopes[0].line_span)) * slopes[0].z2;
            float zrec_r = slopes[1].z1*(1 - (y - yr)/slopes[1].line_span) + (((y - yr)/slopes[1].line_span)) * slopes[1].z2;
            float interpz = -1;
            if(endx != startx)
                interpz = zrec_l * (1 - (sc_px - startx)/(endx - startx)) + ((sc_px - startx)/(endx - startx)) * zrec_r;

            if(interpz <= DriverLCD::VIDEO_Z_BUFFER[84 * (y/8) + sc_px])
            { 
                DriverLCD::VIDEO_Z_BUFFER[84 * (y/8) + sc_px] = interpz;
                if(sc_px == startx || sc_px == endx)
                    DriverLCD::draw_pixel(sc_px, y);
            }    
        } 
        */
        }
}





