#ifndef __COLOR_VECTOR_H__
#define __COLOR_VECTOR_H__

#include "Platform.h"

namespace Dsim {

typedef uint32 RGBA;
typedef uint32 ARGB;
typedef uint32 ABGR;
typedef uint32 BGRA;

class ColorVector
{
	protected:
		scalar r;	//RED
		scalar g;	//GREEN
		scalar b;	//BLUE
		scalar a;	//ALPHA
	public:
		static const ColorVector ZERO;
        	static const ColorVector Black;
		static const ColorVector White;
		static const ColorVector Red;
		static const ColorVector Green;
		static const ColorVector Blue;

		ColorVector(scalar red = 0.0f, scalar green = 0.5f, scalar blue = 0.0f, scalar alpha = 1.0f);

		scalar SetR(scalar val) { r = val; return r; }
		scalar SetG(scalar val) { g = val; return g; }
		scalar SetB(scalar val) { b = val; return b; }
		scalar SetA(scalar val) { a = val; return a; }

		scalar R() const { return r; }
		scalar G() const { return g; }
		scalar B() const { return b; }
		scalar A() const { return a; }

		RGBA GetRGBA(void) const;
		ARGB GetARGB(void) const;
		BGRA GetBGRA(void) const;
		ABGR GetABGR(void) const;

		void SetRGBA(RGBA val);
		void SetARGB(ARGB val);
		void SetBGRA(BGRA val);
		void SetABGR(ABGR val);

		ColorVector Saturate(void);
		ColorVector SaturateCopy(void);

		scalar * GetPointer() const { return (scalar *)&r; }
};

bool operator==(const ColorVector & left, const ColorVector & right);
bool operator!=(const ColorVector & left, const ColorVector & right);
ColorVector operator+(const ColorVector & left, const ColorVector & right);
ColorVector operator-(const ColorVector & left, const ColorVector & right);
ColorVector operator*(const ColorVector & left, const ColorVector & right);
ColorVector operator*(const ColorVector & left, const scalar & right);
ColorVector operator*(const scalar & left, const ColorVector & right);
ColorVector operator/(const ColorVector & left, const ColorVector & right);
ColorVector & operator+=(ColorVector & left, const ColorVector & right);
ColorVector & operator*=(ColorVector & left, const ColorVector & right);
ColorVector & operator*=(ColorVector & left, const scalar & right);



bool ColorVectorAreEqual(const ColorVector *first, const ColorVector *second);

}

#endif //__COLOR_VECTOR_H__
