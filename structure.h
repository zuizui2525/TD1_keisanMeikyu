#pragma once
#include <Novice.h>

struct Vector2 {
	float x;
	float y;
};

struct Grid {
	int beside;
	int vertical;
};

struct Map8x8 {
	int m[8][8];
};

struct Line {
	Vector2 startPos;
	Vector2 endPos;
	int color;
};

struct Box {
	Vector2 pos;
	float width;
	float height;
	float angle;
	int color;
	FillMode shape;
};

struct Circle {
	Vector2 pos;
	Vector2 radius;
	float angle;
	int color;
	FillMode shape;
};



