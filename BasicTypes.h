#ifndef  BASICTYPES_H
#define BASICTYPES_H

typedef struct Colour {
	Colour() : r(0), g(0), b(0), a(255) {}
	Colour(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
		: r(_r), g(_g), b(_b), a(_a) {}
	Colour(int hex) //from hex value
	{
		int test = ((hex >> 16) & 0xFF) / 255.0;
		r = ((hex >> 16) & 0xFF);  // Extract the RR byte
		g = ((hex >> 8) & 0xFF);   // Extract the GG byte
		b = ((hex) & 0xFF);        // Extract the BB byte
		a = 255;
	}
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
	Vector2f operator*(float m) { x *= m; y *= m; return *this; }
	Vector2f operator+(const Vector2f v) { x += v.x; y += v.y; return *this; }
	float magnitude() { return sqrt(x * x + y * y); }
	float x;
	float y;
} Vector2f;

typedef struct Vector2i {
	Vector2i(int _x, int _y) : x(_x), y(_y) {}
	Vector2i() : x(0), y(0) {}
	bool operator==(const Vector2i v) { return (x == v.x && y == v.y); }
	bool operator!=(const Vector2i v) { return (x != v.x || y != v.y); }
	int x;
	int y;
} Vector2i;

#endif 
