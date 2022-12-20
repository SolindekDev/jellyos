#pragma once

typedef struct Color {
    int r, g, b;
} Color;

typedef struct ColorWithAlpha {
    int r, g, b, a;
} ColorWithAlpha;

// Function for creating Color structure 
Color color(int r, int g, int b);

// Function for creating ColorWithAlpha structure 
ColorWithAlpha color_a(int r, int g, int b, int a);