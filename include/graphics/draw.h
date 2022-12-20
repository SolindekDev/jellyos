#pragma once

#include <utils/colors.h>
#include <utils/vec.h>

void draw_character(char c, int x, int y, Color fg, Color bg);

void draw_rect(Vec2 pos, Vec2 size, Color color);

void draw_circle(Vec2 center, int radius, Color color);

void draw_line(Vec2 start, Vec2 end, Color color);
