//
// Created by Rory Hedderman on 26/12/2023.
//

#include "noise.h"
#include "math_utils.h"

float perlin(float x, float y) {

    // Determine grid cell corner coordinates
    int x0 = (int)x;
    int y0 = (int)y;
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    // Compute Interpolation weights
    float sx = x - (float)x0;
    float sy = y - (float)y0;

    // Compute and interpolate top two corners
    float n0 = dotGridGradient(x0, y0, x, y);
    float n1 = dotGridGradient(x1, y0, x, y);
    float ix0 = interpolate(n0, n1, sx);

    // Compute and interpolate bottom two corners
    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    float ix1 = interpolate(n0, n1, sx);

    // Final step: interpolate between the two previously interpolated values, now in y
    float value = interpolate(ix0, ix1, sy);

    return value;
}
