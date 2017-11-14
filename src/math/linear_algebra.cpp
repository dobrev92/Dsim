#include "math/linear_algebra.h"
#include <math.h>
#include "debug.h"

using namespace Dsim;

//functions on C single arrays
static void vector_add(scalar *vec1, scalar *vec2, scalar *res, unsigned int size);
static void vector_substract(scalar *vec1, scalar *vec2, scalar *res, unsigned int size);
static void vector_scale(scalar *vec, scalar s, scalar *res, unsigned int size);
static scalar vector_dot(scalar *vec1, scalar *vec2, scalar *res, unsigned int size);
static scalar vector_length(scalar *vec, scalar *res, unsigned int size);
static void vector_normalize(scalar *vec, scalar *res, unsigned int size);

//functions on C square arrays
static void matrix_identity(scalar *mat, unsigned int size);

//Vector2
Vector2::Vector2()
{
	elements[0] = 0;
	elements[1] = 0;
}

Vector2::Vector2(scalar x, scalar y)
{
	elements[0] = x;
	elements[1] = y;
}

scalar Vector2::length()
{
	scalar l = vector_length(elements, NULL, 2);
	return l;
}

void Vector2::normalize()
{
	vector_normalize(elements, elements, 2);
}

Vector2 Dsim::operator+(const Vector2 & left, const Vector2 & right)
{
	Vector2 result = AddVector2D(left, right);
	return result;
}

Vector2 Dsim::operator-(const Vector2 & left, const Vector2 & right)
{
	Vector2 result = SubstractVector2D(left, right);
	return result;
}

Vector2 Dsim::operator*(const Vector2 & left, const scalar & right)
{
	Vector2 result = VecScalarMultiply2D(left, right);
	return result;
}

Vector2 Dsim::operator*(const scalar & left, const Vector2 & right)
{
	Vector2 result = VecScalarMultiply2D(right, left);
	return result;
}

//Vector3
Vector3::Vector3()
{
	elements[0] = 0;
	elements[1] = 0;
	elements[2] = 0;
}

Vector3::Vector3(scalar x, scalar y, scalar z)
{
	elements[0] = x;
	elements[1] = y;
	elements[2] = z;
}

scalar Vector3::length()
{
	scalar l = vector_length(elements, NULL, 3);
	return l;
}

void Vector3::normalize()
{
	vector_normalize(elements, elements, 3);
}

Vector3 Dsim::operator+(const Vector3 & left, const Vector3 & right)
{
	Vector3 result = AddVector3D(left, right);
	return result;
}

Vector3 Dsim::operator-(const Vector3 & left, const Vector3 & right)
{
	Vector3 result = SubstractVector3D(left, right);
	return result;
}

Vector3 Dsim::operator*(const Vector3 & left, const scalar & right)
{
	Vector3 result = VecScalarMultiply3D(left, right);
	return result;
}

Vector3 Dsim::operator*(const scalar & left, const Vector3 & right)
{
	Vector3 result = VecScalarMultiply3D(right, left);
	return result;
}

//Vector4
Vector4::Vector4()
{
    elements[0] = 0;
    elements[1] = 0;
    elements[2] = 0;
    elements[3] = 0;
}

Vector4::Vector4(scalar x, scalar y, scalar z, scalar w)
{
    elements[0] = x;
    elements[1] = y;
    elements[2] = z;
    elements[3] = w;
}

Vector4::Vector4(Vector3 vec, scalar w)
{
    elements[0] = vec.X();
    elements[1] = vec.Y();
    elements[2] = vec.Z();
    elements[3] = w;
}

scalar Vector4::length()
{
    scalar l = vector_length(elements, NULL, 4);
    return l;
}

void Vector4::normalize()
{
    vector_normalize(elements, elements, 4);
}

Vector4 Dsim::operator+(const Vector4 & left, const Vector4 & right)
{
	Vector4 result = AddVector4D(left, right);
	return result;
}

Vector4 Dsim::operator-(const Vector4 & left, const Vector4 & right)
{
	Vector4 result = SubstractVector4D(left, right);
	return result;
}

Vector4 Dsim::operator*(const Vector4 & left, const scalar & right)
{
	Vector4 result = VecScalarMultiply4D(left, right);
	return result;
}

Vector4 Dsim::operator*(const scalar & left, const Vector4 & right)
{
	Vector4 result = VecScalarMultiply4D(right, left);
	return result;
}

Matrix3x3::Matrix3x3()
{
}

//Vector arithmtic functions
//ADDITION
Vector2 Dsim::AddVector2D(Vector2 first, Vector2 second)
{
	Vector2 result;
	scalar *vec1 = first.GetPointer();
	scalar *vec2 = second.GetPointer();

	vector_add(vec1, vec2, result.GetPointer(), 2);
    	return result;
}

Vector3 Dsim::AddVector3D(Vector3 first, Vector3 second)
{
	Vector3 result;
	scalar *vec1 = first.GetPointer();
	scalar *vec2 = second.GetPointer();

	vector_add(vec1, vec2, result.GetPointer(), 3);
    	return result;
}

Vector4 Dsim::AddVector4D(Vector4 first, Vector4 second)
{
	Vector4 result;
	scalar *vec1 = first.GetPointer();
	scalar *vec2 = second.GetPointer();

	vector_add(vec1, vec2, result.GetPointer(), 4);
    	return result;
}

//SUBSTRACTION
Vector2 Dsim::SubstractVector2D(Vector2 first, Vector2 second)
{
	Vector2 result;
	scalar *vec1 = first.GetPointer();
	scalar *vec2 = second.GetPointer();

	vector_substract(vec1, vec2, result.GetPointer(), 2);
    	return result;
}

Vector3 Dsim::SubstractVector3D(Vector3 first, Vector3 second)
{
	Vector3 result;
	scalar *vec1 = first.GetPointer();
	scalar *vec2 = second.GetPointer();

	vector_substract(vec1, vec2, result.GetPointer(), 3);
    	return result;
}

Vector4 Dsim::SubstractVector4D(Vector4 first, Vector4 second)
{
	Vector4 result;
	scalar *vec1 = first.GetPointer();
	scalar *vec2 = second.GetPointer();

	vector_substract(vec1, vec2, result.GetPointer(), 4);
    	return result;
}

//SCALAR MULTIPLICATION
Vector2 Dsim::VecScalarMultiply2D(Vector2 vec, scalar s)
{
	Vector2 result;
	scalar *vector = vec.GetPointer();

	vector_scale(vector, s, result.GetPointer(), 2);
    	return result;
}

Vector3 Dsim::VecScalarMultiply3D(Vector3 vec, scalar s)
{
	Vector3 result;
	scalar *vector = vec.GetPointer();

	vector_scale(vector, s, result.GetPointer(), 3);
    	return result;
}

Vector4 Dsim::VecScalarMultiply4D(Vector4 vec, scalar s)
{
	Vector4 result;
	scalar *vector = vec.GetPointer();

	vector_scale(vector, s, result.GetPointer(), 4);
    	return result;
}

//DOT PRODUCT
scalar Dsim::DotProduct2D(Vector2 first, Vector2 second)
{
	scalar result;
	scalar *vec1 = first.GetPointer();
	scalar *vec2 = second.GetPointer();

	result = vector_dot(vec1, vec2, NULL, 2);
    	return result;
}

scalar Dsim::DotProduct3D(Vector3 first, Vector3 second)
{
	scalar result;
	scalar *vec1 = first.GetPointer();
	scalar *vec2 = second.GetPointer();

	result = vector_dot(vec1, vec2, NULL, 3);
    	return result;
}

scalar Dsim::DotProduct4D(Vector4 first, Vector4 second)
{
	scalar result;
	scalar *vec1 = first.GetPointer();
	scalar *vec2 = second.GetPointer();

	result = vector_dot(vec1, vec2, NULL, 4);
    	return result;
}

//CROSS PRODUCT
Vector3 Dsim::VectorCross3D(Vector3 first, Vector3 second)
{
	Vector3 result;
	Vector3 i = Vector3(1, 0, 0);
	Vector3 j = Vector3(0, 1, 0);
	Vector3 k = Vector3(0, 0, 1);
	scalar a, b, c;
	a = first.Y()*second.Z() - first.Z()*second.Y();
	b = first.Z()*second.X() - first.X()*second.Z();
	c = first.X()*second.Y() - first.Y()*second.X();
	result = AddVector3D(VecScalarMultiply3D(i,a), VecScalarMultiply3D(j,b));
	result = AddVector3D(result, VecScalarMultiply3D(k,c));
	return result;
}

//functions on C arrays
void vector_add(scalar *vec1, scalar *vec2, scalar *res, unsigned int size)
{
	unsigned int i;
	if (!vec1 || !vec2 || !res || !size){
		dbg_info("returning\n");
		return;
	}

	for (i = 0; i < size; i++) {
		res[i] = vec1[i] + vec2[i];
	}
}

void vector_substract(scalar *vec1, scalar *vec2, scalar *res, unsigned int size)
{
	unsigned int i;
	if (!vec1 || !vec2 || !res || !size)
		return;

	for (i = 0; i < size; i++) {
		res[i] = vec1[i] - vec2[i];
	}
}

void vector_scale(scalar *vec, scalar s, scalar *res, unsigned int size)
{
	unsigned int i;
	if (!vec || !res || !size)
		return;

	for (i = 0; i < size; i++) {
		res[i] = vec[i] * s;
	}
}

scalar vector_dot(scalar *vec1, scalar *vec2, scalar *res, unsigned int size)
{
	unsigned int i;
	scalar ret = 0;
	if (!vec1 || !vec2 || !size)
		return 0;

	for (i = 0; i < size; i++) {
		ret += vec1[i] * vec2[i];
	}

	if (res)
		*res = ret;

	return ret;
}

scalar vector_length(scalar *vec, scalar *res, unsigned int size)
{
	scalar ret = 0;
	if (!vec || !size)
		return 0;

	ret = vector_dot(vec, vec, NULL, size);
	ret = sqrt(ret);

	if (res)
		*res = ret;

	return ret;
}

void vector_normalize(scalar *vec, scalar *res, unsigned int size)
{
	unsigned int i;
	unsigned int l = 0;
	if (!vec || !res || !size)
		return;

	l = vector_length(vec, NULL, size);

	for (i = 0; i < size; i++) {
		res[i] /= l;
	}
}

//functions on C square arrays
void matrix_identity(scalar *mat, unsigned int size)
{
	scalar (*matrix)[size] = (scalar (*)[size]) mat;
	dbg_info("matrix[0][0] = %f\n", matrix[0]);
}

