#include "z3D/z3D.h"
#include "colors.h"

void Colors_ChangeRainbowColorRGBAf(Color_RGBAf* color, float speed, float max) {
    if (color->r >= max && color->g < max && color->b <= 0)
        color->g += speed;
    else if (color->r > 0 && color->g >= max && color->b <= 0)
        color->r -= speed;
    else if (color->r <= 0 && color->g >= max && color->b < max)
        color->b += speed;
    else if (color->r <= 0 && color->g > 0 && color->b >= max)
        color->g -= speed;
    else if (color->r < max && color->g <= 0 && color->b >= max)
        color->r += speed;
    else if (color->r >= max && color->g <= 0 && color->b > 0)
        color->b -= speed;
}
