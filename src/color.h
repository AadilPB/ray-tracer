#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"

#include <vector>

using color = vec3;

inline double linear_to_gamma(double linear_component)
{
    if (linear_component > 0)
        return std::sqrt(linear_component);

    return 0;
}

void write_color(const color& pixel_color, std::vector<uint8_t>& pixel_data, int position)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Apply linear to gamme transform for gamma 2
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    // Convert the [0, 1] component values to the byte range [0, 255].
    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    //Push pixel colour components to 1D dynamic array
    pixel_data.at(position)     = rbyte;
    pixel_data.at(position + 1) = gbyte;
    pixel_data.at(position + 2) = bbyte;

}



#endif
