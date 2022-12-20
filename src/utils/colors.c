#include <utils/colors.h>

// TODO: implement color from hex

// Function for creating Color structure 
Color color(int r, int g, int b) {
    Color _color;
    _color.r = r; _color.g = g; _color.b = b;
    
    return _color;
}

// Function for creating ColorWithAlpha structure 
ColorWithAlpha color_a(int r, int g, int b, int a) {
    ColorWithAlpha _color_a;
    _color_a.r = r; _color_a.g = g; _color_a.b = b; _color_a.a = a;
    
    return _color_a;
}