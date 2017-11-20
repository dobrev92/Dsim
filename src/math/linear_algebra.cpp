#include "math/linear_algebra.h"
#include <math.h>
#include "debug.h"

using namespace Dsim;

//functions on C single arrays
static void vector_add(scalar *vec1, scalar *vec2, scalar *res, unsigned int size);
static void vector_substract(scalar *vec1, scalar *vec2, scalar *res, unsigned int size);
static void vector_scale(scalar *vec, scalar s, scalar *res, unsigned int size);
static scalar vector_dot(scalar *vec1, scalar *vec2, unsigned int size);
static scalar vector_length(scalar *vec, unsigned int size);
static void vector_normalize(scalar *vec, scalar *res, unsigned int size);

//functions on C square arrays
static void matrix_scale(scalar *mat, unsigned int size, scalar s);

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

scalar Vector2::length() const
{
	scalar l = VectorLength2D(this);
	return l;
}

void Vector2::normalize()
{
	vector_normalize(elements, elements, 2);
}

Vector2 Dsim::operator+(const Vector2 & left, const Vector2 & right)
{
	Vector2 result;

	AddVector2D(&result, &left, &right);
	return result;
}

Vector2 Dsim::operator-(const Vector2 & left, const Vector2 & right)
{
	Vector2 result;

	SubstractVector2D(&result, &left, &right);
	return result;
}

Vector2 Dsim::operator*(const Vector2 & left, const scalar & right)
{
	Vector2 result;

	VecScalarMultiply2D(&result, &left, right);
	return result;
}

Vector2 Dsim::operator*(const scalar & left, const Vector2 & right)
{
	Vector2 result;

	VecScalarMultiply2D(&result, &right, left);
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

scalar Vector3::length() const
{
	scalar l = VectorLength3D(this);
	return l;
}

void Vector3::normalize()
{
	vector_normalize(elements, elements, 3);
}

Vector3 Dsim::operator+(const Vector3 & left, const Vector3 & right)
{
	Vector3 result;

	AddVector3D(&result, &left, &right);
	return result;
}

Vector3 Dsim::operator-(const Vector3 & left, const Vector3 & right)
{
	Vector3 result;

	SubstractVector3D(&result, &left, &right);
	return result;
}

Vector3 Dsim::operator*(const Vector3 & left, const scalar & right)
{
	Vector3 result;

	VecScalarMultiply3D(&result, &left, right);
	return result;
}

Vector3 Dsim::operator*(const scalar & left, const Vector3 & right)
{
	Vector3 result;

	VecScalarMultiply3D(&result, &right, left);
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

scalar Vector4::length() const
{
    scalar l = VectorLength4D(this);
    return l;
}

void Vector4::normalize()
{
    vector_normalize(elements, elements, 4);
}

Vector4 Dsim::operator+(const Vector4 & left, const Vector4 & right)
{
	Vector4 result;

	AddVector4D(&result, &left, &right);
	return result;
}

Vector4 Dsim::operator-(const Vector4 & left, const Vector4 & right)
{
	Vector4 result;

	SubstractVector4D(&result, &left, &right);
	return result;
}

Vector4 Dsim::operator*(const Vector4 & left, const scalar & right)
{
	Vector4 result;

	VecScalarMultiply4D(&result, &left, right);
	return result;
}

Vector4 Dsim::operator*(const scalar & left, const Vector4 & right)
{
	Vector4 result;

	VecScalarMultiply4D(&result, &right, left);
	return result;
}

Matrix3x3::Matrix3x3(scalar s)
{
	Matrix3x3Identity((Matrix3x3 *)&elements[0][0]);
}

//TODO: Implement columnt Matrix3x3 constructor
Matrix3x3::Matrix3x3(Vector3 column1, Vector3 column2, Vector3 column3)
{
	Matrix3x3Identity((Matrix3x3 *)&elements[0][0]);
}

scalar Matrix3x3::GetElement(unsigned int col, unsigned int row)
{
	if (col > 2 || row > 2)
		return 0;

	return elements[col][row];
}

void Matrix3x3::SetElement(unsigned int col, unsigned int row, scalar value)
{
	if (col > 2 || row > 2)
		return;

	elements[col][row] = value;
}

Vector3 Matrix3x3::GetColumn(unsigned int col)
{
	unsigned int i;
	Vector3 ret(0, 0, 0);

	if (col > 2)
		return ret;

	for (i = 0; i < 3; i++) {
		ret.SetElement(i, elements[col][i]);
	}

	return ret;
}
	

Vector3 Matrix3x3::GetRow(unsigned int row)
{
	unsigned int i;
	Vector3 ret(0, 0, 0);

	if (row > 2)
		return ret;

	for (i = 0; i < 3; i++) {
		ret.SetElement(i, elements[i][row]);
	}

	return ret;
}

//Vector arithmtic functions
//ADDITION
Vector2 * Dsim::AddVector2D(Vector2 *out, const Vector2 *first, const Vector2 *second)
{
	if (!out || !first || !second)
		return NULL;

	scalar *vec1 = first->GetPointer();
	scalar *vec2 = second->GetPointer();

	vector_add(vec1, vec2, out->GetPointer(), 2);
    	return out;
}

Vector3 * Dsim::AddVector3D(Vector3 *out, const Vector3 *first, const Vector3 *second)
{
	if (!out || !first || !second)
		return NULL;

	scalar *vec1 = first->GetPointer();
	scalar *vec2 = second->GetPointer();

	vector_add(vec1, vec2, out->GetPointer(), 3);
    	return out;
}

Vector4 * Dsim::AddVector4D(Vector4 *out, const Vector4 *first, const Vector4 *second)
{
	if (!out || !first || !second)
		return NULL;

	scalar *vec1 = first->GetPointer();
	scalar *vec2 = second->GetPointer();

	vector_add(vec1, vec2, out->GetPointer(), 4);
    	return out;
}

//SUBSTRACTION
Vector2 * Dsim::SubstractVector2D(Vector2 *out, const Vector2 *first, const Vector2 *second)
{
	if (!out || !first || !second)
		return NULL;

	scalar *vec1 = first->GetPointer();
	scalar *vec2 = second->GetPointer();

	vector_substract(vec1, vec2, out->GetPointer(), 2);
    	return out;
}

Vector3 * Dsim::SubstractVector3D(Vector3 *out, const Vector3 *first, const Vector3 *second)
{
	if (!out || !first || !second)
		return NULL;

	scalar *vec1 = first->GetPointer();
	scalar *vec2 = second->GetPointer();

	vector_substract(vec1, vec2, out->GetPointer(), 3);
    	return out;
}

Vector4 * Dsim::SubstractVector4D(Vector4 *out, const Vector4 *first, const Vector4 *second)
{
	if (!out || !first || !second)
		return NULL;

	scalar *vec1 = first->GetPointer();
	scalar *vec2 = second->GetPointer();

	vector_substract(vec1, vec2, out->GetPointer(), 4);
    	return out;
}

//SCALAR MULTIPLICATION
Vector2 * Dsim::VecScalarMultiply2D(Vector2 *out, const Vector2 *vec, scalar s)
{
	if (!out || !vec)
		return NULL;

	scalar *vector = vec->GetPointer();

	vector_scale(vector, s, out->GetPointer(), 2);
    	return out;
}

Vector3 * Dsim::VecScalarMultiply3D(Vector3 *out, const Vector3 *vec, scalar s)
{
	if (!out || !vec)
		return NULL;

	scalar *vector = vec->GetPointer();

	vector_scale(vector, s, out->GetPointer(), 3);
    	return out;
}

Vector4 * Dsim::VecScalarMultiply4D(Vector4 *out, const Vector4 *vec, scalar s)
{
	if (!out || !vec)
		return NULL;

	scalar *vector = vec->GetPointer();

	vector_scale(vector, s, out->GetPointer(), 4);
    	return out;
}

//DOT PRODUCT
scalar Dsim::DotProduct2D(const Vector2 *first, const Vector2 *second)
{
	if (!first || !second)
		return 0;

	scalar result;

	scalar *vec1 = first->GetPointer();
	scalar *vec2 = second->GetPointer();

	result = vector_dot(vec1, vec2, 2);
    	return result;
}

scalar Dsim::DotProduct3D(const Vector3 *first, const Vector3 *second)
{
	if (!first || !second)
		return 0;

	scalar result;

	scalar *vec1 = first->GetPointer();
	scalar *vec2 = second->GetPointer();

	result = vector_dot(vec1, vec2, 3);
    	return result;
}

scalar Dsim::DotProduct4D(const Vector4 *first, const Vector4 *second)
{
	if (!first || !second)
		return 0;

	scalar result;

	scalar *vec1 = first->GetPointer();
	scalar *vec2 = second->GetPointer();

	result = vector_dot(vec1, vec2, 4);
    	return result;
}

//VECTOR LENGTH
scalar Dsim::VectorLength2D(const Vector2 *vec)
{
	if (!vec)
		return 0;

	return vector_length(vec->GetPointer(), 2);
}

scalar Dsim::VectorLength3D(const Vector3 *vec)
{
	if (!vec)
		return 0;

	return vector_length( vec->GetPointer(), 3);
}

scalar Dsim::VectorLength4D(const Vector4 *vec)
{
	if (!vec)
		return 0;

	return vector_length(vec->GetPointer(), 4);
}

//UNIT VECTORS
Vector2 * Dsim::GetUnitVector2D(Vector2 * out, const Vector2 *vec)
{
	if (!out || !vec)
		return NULL;

	vector_normalize(vec->GetPointer(), out->GetPointer(), 2);
	return out;
}

Vector3 * Dsim::GetUnitVector3D(Vector3 * out, const Vector3 *vec)
{
	if (!out || !vec)
		return NULL;

	vector_normalize(vec->GetPointer(), out->GetPointer(), 3);
	return out;
}

Vector4 * Dsim::GetUnitVector2D(Vector4 * out, const Vector4 *vec)
{
	if (!out || !vec)
		return NULL;

	vector_normalize(vec->GetPointer(), out->GetPointer(), 4);
	return out;
}

//CROSS PRODUCT
Vector3 * Dsim::VectorCross3D(Vector3 *out, const Vector3 *first, const Vector3 *second)
{
	scalar a, b, c;
	Vector3 i = Vector3(1, 0, 0);
	Vector3 j = Vector3(0, 1, 0);
	Vector3 k = Vector3(0, 0, 1);

	a = first->Y() * second->Z() - first->Z() * second->Y();
	b = first->Z() * second->X() - first->X() * second->Z();
	c = first->X() * second->Y() - first->Y() * second->X();

	AddVector3D(out, VecScalarMultiply3D(&i, &i, a), VecScalarMultiply3D(&j, &j, b));
	AddVector3D(out, out, VecScalarMultiply3D(&k, &k ,c));
	return out;
}

Matrix3x3 Dsim::Matrix3x3Identity(Matrix3x3 *mat)
{
	Matrix3x3 ret;

	matrix_scale(ret.GetPointer(), 3, 1);
	if(mat)
		*mat = ret;

	return ret;
}

//SCALE MATRICES
Matrix3x3 Matrix3x3Scale(Matrix3x3 *mat, scalar s)
{
	Matrix3x3 ret;

	matrix_scale(ret.GetPointer(), 3, s);
	if(mat)
		*mat = ret;

	return ret;
}

//ROTATION MATRICES
Matrix3x3 Matrix3x3RotationX(Matrix3x3 *mat, scalar angle);

//MATRIX MULTIPLICATION
//TODO: Implement a more efficient matrix multiplication
Matrix3x3 Dsim::Matrix3x3Multiply(Matrix3x3 first, Matrix3x3 second)
{
	Matrix3x3 result;

	for (int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			scalar value;
			Vector3 vec1 = first.GetRow(i);
			Vector3 vec2 = second.GetColumn(j);
			value = DotProduct3D(&vec1, &vec2);
			result.SetElement(i, j, value);
		}
	}

	return result;
}

//functions on C arrays
void vector_add(scalar *vec1, scalar *vec2, scalar *res, unsigned int size)
{
	if (!vec1 || !vec2 || !res || !size){
		return;
	}

	unsigned int i;

	for (i = 0; i < size; i++) {
		res[i] = vec1[i] + vec2[i];
	}
}

void vector_substract(scalar *vec1, scalar *vec2, scalar *res, unsigned int size)
{
	if (!vec1 || !vec2 || !res || !size)
		return;

	unsigned int i;

	for (i = 0; i < size; i++) {
		res[i] = vec1[i] - vec2[i];
	}
}

void vector_scale(scalar *vec, scalar s, scalar *res, unsigned int size)
{
	if (!vec || !res || !size)
		return;

	unsigned int i;

	for (i = 0; i < size; i++) {
		res[i] = vec[i] * s;
	}
}

scalar vector_dot(scalar *vec1, scalar *vec2, unsigned int size)
{
	if (!vec1 || !vec2 || !size)
		return 0;

	unsigned int i;
	scalar ret = 0;

	for (i = 0; i < size; i++) {
		ret += vec1[i] * vec2[i];
	}

	return ret;
}

scalar vector_length(scalar *vec, unsigned int size)
{
	if (!vec || !size)
		return 0;

	scalar ret = 0;

	ret = vector_dot(vec, vec, size);
	ret = sqrt(ret);

	return ret;
}

void vector_normalize(scalar *vec, scalar *res, unsigned int size)
{
	if (!vec || !res || !size)
		return;

	unsigned int i;
	unsigned int l = 0;

	l = vector_length(vec, size);

	for (i = 0; i < size; i++) {
		res[i] /= l;
	}
}

//functions on C square arrays
void matrix_scale(scalar *mat, unsigned int size, scalar s)
{
	if(!mat)
		return;

	int i, j;
	scalar (*matrix)[size] = (scalar (*)[size]) mat;

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if ( i == j) {
				matrix[i][j] = s;
			} else {
				matrix[i][j] = 0;
			}
		}
	}
}

