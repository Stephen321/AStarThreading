#ifndef  BASICTYPES_H
#define BASICTYPES_H

typedef struct Colour {
	Colour() : r(0), g(0), b(0), a(0) {}
	Colour(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
		: r(_r), g(_g), b(_b), a(_a) {}
	unsigned char r, g, b, a;

} Colour;

typedef struct BoundingBox {
	BoundingBox() : x(0), y(0), w(0), h(0) {}
	BoundingBox(int _x, int _y, int _w, int _h)
		: x(_x), y(_y), w(_w), h(_h) {}
	int x, y, w, h;
} BoundingBox;

typedef struct Vector2f {
	Vector2f(float _x, float _y) : x(_x), y(_y) {}
	Vector2f() : x(0.f), y(0.f) {}
	float x;
	float y;
} Vector2f;

typedef struct Vector2i {
	Vector2i(int _x, int _y) : x(_x), y(_y) {}
	Vector2i() : x(0), y(0) {}
	int x;
	int y;
} Vector2i;

#endif 
