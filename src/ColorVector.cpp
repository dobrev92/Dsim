#include "ColorVector.h"
#include "debug.h"

using namespace Dsim;

const ColorVector ColorVector::ZERO = ColorVector(0.0,0.0,0.0,0.0);
const ColorVector ColorVector::Black = ColorVector(0.0,0.0,0.0);
const ColorVector ColorVector::White = ColorVector(1.0,1.0,1.0);
const ColorVector ColorVector::Red = ColorVector(1.0,0.0,0.0);
const ColorVector ColorVector::Green = ColorVector(0.0,1.0,0.0);
const ColorVector ColorVector::Blue = ColorVector(0.0,0.0,1.0);

ColorVector::ColorVector(float red, float green, float blue, float alpha)
{
	r = red;
	g = green;
	b = blue;
	a = alpha;
}

RGBA ColorVector::GetRGBA(void) const
{
	uint32 result;
	uint8 val8;

	result = 0;

	val8 = (uint8)(r * 255);
	result = val8 << 24;

	val8 = (uint8)(g * 255);
	result += val8 << 16;

	val8 = (uint8)(b * 255);
	result += val8 << 8;

	val8 = (uint8)(a * 255);
	result += val8;

	return result;
}

ARGB ColorVector::GetARGB(void) const
{
	uint32 result;
	uint8 val8;

	result = 0;

	val8 = (uint8)(a * 255);
	result = val8 << 24;

	val8 = (uint8)(r * 255);
	result += val8 << 16;

	val8 = (uint8)(g * 255);
	result += val8 << 8;

	val8 = (uint8)(b * 255);
	result += val8;

	return result;
}

BGRA ColorVector::GetBGRA(void) const
{
	uint32 result;
	uint8 val8;

	result = 0;

	val8 = (uint8)(b * 255);
	result = val8 << 24;

	val8 = (uint8)(g * 255);
	result += val8 << 16;

	val8 = (uint8)(r * 255);
	result += val8 << 8;

	val8 = (uint8)(a * 255);
	result += val8;

	return result;
}

ABGR ColorVector::GetABGR(void) const
{
	uint32 result;
	uint8 val8;

	result = 0;

	val8 = (uint8)(a * 255);
	result = val8 << 24;

	val8 = (uint8)(b * 255);
	result += val8 << 16;

	val8 = (uint8)(g * 255);
	result += val8 << 8;

	val8 = (uint8)(r * 255);
	result += val8;

	return result;
}

void ColorVector::SetRGBA(RGBA val)
{
	SetR(scalar((val >> 24) & 0xFF) / 255.0f);
	SetG(scalar((val >> 16) & 0xFF) / 255.0f);
	SetB(scalar((val >> 8) & 0xFF) / 255.0f);
	SetA(scalar(val & 0xFF) / 255.0f);
}

void ColorVector::SetARGB(ARGB val)
{
	SetA(scalar((val >> 24) & 0xFF) / 255.0f);
	SetR(scalar((val >> 16) & 0xFF) / 255.0f);
	SetG(scalar((val >> 8) & 0xFF) / 255.0f);
	SetB(scalar(val & 0xFF) / 255.0f);
}

void ColorVector::SetBGRA(BGRA val)
{
	SetB(scalar((val >> 24) & 0xFF) / 255.0f);
	SetG(scalar((val >> 16) & 0xFF) / 255.0f);
	SetR(scalar((val >> 8) & 0xFF) / 255.0f);
	SetA(scalar(val & 0xFF) / 255.0f);
}

void ColorVector::SetABGR(ABGR val)
{
	SetA(scalar((val >> 24) & 0xFF) / 255.0f);
	SetB(scalar((val >> 16) & 0xFF) / 255.0f);
	SetG(scalar((val >> 8) & 0xFF) / 255.0f);
	SetR(scalar(val & 0xFF) / 255.0f);
}

ColorVector ColorVector::Saturate(void)
{
	if (r < 0)
		r = 0;
	else if (r > 1)
		r = 1;

	if (g < 0)
		g = 0;
	else if (g > 1)
		g = 1;

	if (b < 0)
		b = 0;
	else if (b > 1)
		b = 1;

	if (a < 0)
		a = 0;
	else if (a > 1)
		a = 1;

	ColorVector result(r, g, b, a);
	return result;
}

ColorVector ColorVector::SaturateCopy(void)
{
	ColorVector result = *this;
	result.Saturate();
	return result;
}

bool Dsim::operator==(const ColorVector & left, const ColorVector & right)
{
	return ColorVectorAreEqual(&left, &right);
}

bool Dsim::operator!=(const ColorVector & left, const ColorVector & right)
{
	return !ColorVectorAreEqual(&left, &right);
}

bool Dsim::ColorVectorAreEqual(const ColorVector *first, const ColorVector *second)
{
	return ((first->R() == second->R()) &&
		(first->G() == second->G()) &&
		(first->B() == second->B()) &&
		(first->A() == second->A()));
}

