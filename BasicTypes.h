#ifndef  BASICTYPES_H
#define BASICTYPES_H

typedef struct Colour {
	Colour() : r(0), g(0), b(0), a(0) {}
	Colour(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
		: r(_r), g(_g), b(_b), a(_a) {}
	unsigned char r, g, b, a;

} Colour;

#endif // ! BASICTYPES_H
