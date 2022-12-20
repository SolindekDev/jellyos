#pragma once

typedef struct Vec2 {
    int x, y;
} Vec2;

typedef struct Vec3 {
    int x, y, z;
} Vec3;

// Function for creating Vec2 structure 
Vec2 vec2(int x, int y);

// Function for creating Vec3 structure 
Vec3 vec3(int x, int y, int z);