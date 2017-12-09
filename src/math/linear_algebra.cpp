#include "math/linear_algebra.h"
#include <math.h>
#include "debug.h"

using namespace Dsim;

//functions on C single arrays
static void vector_add(scalar *out, scalar *vec1, scalar *vec2, unsigned int size);
static void vector_substract(scalar *out, scalar *vec1, scalar *vec2, unsigned int size);
static void vector_scale(scalar *out, scalar *vec, scalar s, unsigned int size);
static scalar vector_dot(scalar *vec1, scalar *vec2, unsigned int size);
static scalar vector_length(scalar *vec, unsigned int size);
static void vector_normalize(scalar *out, scalar *vec, unsigned int size);

//functions on C square arrays
static void matrix_scale(scalar *out, unsigned int size, scalar s);

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
	scalar l = Vector2Length(this);
	return l;
}

Vector2 * Vector2::normalize()
{
	Vector2Unit(this, this);
	return this;
}

Vector2 Dsim::operator+(const Vector2 & left, const Vector2 & right)
{
	Vector2 result;

	Vector2Add(&result, &left, &right);
	return result;
}

Vector2 Dsim::operator-(const Vector2 & left, const Vector2 & right)
{
	Vector2 result;

	Vector2Substract(&result, &left, &right);
	return result;
}

Vector2 Dsim::operator*(const Vector2 & left, const scalar & right)
{
	Vector2 result;

	Vector2ScalarMultiply(&result, &left, right);
	return result;
}

Vector2 Dsim::operator*(const scalar & left, const Vector2 & right)
{
	Vector2 result;

	Vector2ScalarMultiply(&result, &right, left);
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
	scalar l = Vector3Length(this);
	return l;
}

Vector3 * Vector3::normalize()
{
	Vector3Unit(this, this);
	return this;
}

Vector3 Dsim::operator+(const Vector3 & left, const Vector3 & right)
{
	Vector3 result;

	Vector3Add(&result, &left, &right);
	return result;
}

Vector3 Dsim::operator-(const Vector3 & left, const Vector3 & right)
{
	Vector3 result;

	Vector3Substract(&result, &left, &right);
	return result;
}

Vector3 Dsim::operator*(const Vector3 & left, const scalar & right)
{
	Vector3 result;

	Vector3ScalarMultiply(&result, &left, right);
	return result;
}

Vector3 Dsim::operator*(const scalar & left, const Vector3 & right)
{
	Vector3 result;

	Vector3ScalarMultiply(&result, &right, left);
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
	scalar l = Vector4Length(this);
	return l;
}

Vector4 * Vector4::normalize()
{
	Vector4Unit(this, this);
	return this;
}

Vector4 Dsim::operator+(const Vector4 & left, const Vector4 & right)
{
	Vector4 result;

	Vector4Add(&result, &left, &right);
	return result;
}

Vector4 Dsim::operator-(const Vector4 & left, const Vector4 & right)
{
	Vector4 result;

	Vector4Substract(&result, &left, &right);
	return result;
}

Vector4 Dsim::operator*(const Vector4 & left, const scalar & right)
{
	Vector4 result;

	Vector4ScalarMultiply(&result, &left, right);
	return result;
}

Vector4 Dsim::operator*(const scalar & left, const Vector4 & right)
{
	Vector4 result;

	Vector4ScalarMultiply(&result, &right, left);
	return result;
}

Matrix3x3::Matrix3x3(scalar s)
{
	Matrix3x3Identity((Matrix3x3 *)&elements[0][0]);
}

//TODO: Implement columnt Matrix3x3 constructor
Matrix3x3::Matrix3x3(Vector3 *column1, Vector3 *column2, Vector3 *column3)
{
	Matrix3x3Identity((Matrix3x3 *)&elements[0][0]);
}

scalar Matrix3x3::GetElement(unsigned int row, unsigned int col) const
{
	if (col > 2 || row > 2)
		return 0;

	return elements[col][row];
}

scalar Matrix3x3::SetElement(unsigned int row, unsigned int col, scalar value)
{
	if (col > 2 || row > 2)
		return 0;

	elements[col][row] = value;
	return elements[col][row];
}

Vector3 * Matrix3x3::GetColumn(Vector3 *out, unsigned int col) const
{
	if (!out || col > 2)
		return NULL;

	unsigned int i;
	for (i = 0; i < 3; i++) {
		out->SetElement(i, elements[col][i]);
	}

	return out;
}


Vector3 * Matrix3x3::GetRow(Vector3 *out, unsigned int row) const
{
	if (!out || row > 2)
		return NULL;

	unsigned int i;
	for (i = 0; i < 3; i++) {
		out->SetElement(i, elements[i][row]);
	}

	return out;
}

Matrix4x4::Matrix4x4(scalar s)
{
	Matrix4x4Identity((Matrix4x4 *)&elements[0][0]);
}

//TODO: Implement columnt Matrix4x4 constructor
Matrix4x4::Matrix4x4(Vector4 *col0, Vector4 *col1, Vector4 *col2, Vector4 *col3)
{
	Matrix4x4Identity((Matrix4x4 *)&elements[0][0]);
}

scalar Matrix4x4::GetElement(unsigned int row, unsigned int col) const
{
	if (col > 3 || row > 3)
		return 0;

	return elements[col][row];
}

scalar Matrix4x4::SetElement(unsigned int row, unsigned int col, scalar value)
{
	if (col > 3 || row > 3)
		return 0;

	elements[col][row] = value;
	return elements[col][row];
}

Vector4 * Matrix4x4::GetColumn(Vector4 *out, unsigned int col) const
{
	if (!out || col > 3)
		return NULL;

	unsigned int i;
	for (i = 0; i < 4; i++) {
		out->SetElement(i, elements[col][i]);
	}

	return out;
}


Vector4 * Matrix4x4::GetRow(Vector4 *out, unsigned int row) const
{
	if (!out || row > 3)
		return NULL;

	unsigned int i;
	for (i = 0; i < 4; i++) {
		out->SetElement(i, elements[i][row]);
	}

	return out;
}

Matrix4x4 Dsim::operator*(const Matrix4x4 & left, const Matrix4x4 & right)
{
	Matrix4x4 result;

	Matrix4x4Multiply(&result, &left, &right);
	return result;
}

//Vector arithmtic functions
//ADDITION
Vector2 * Dsim::Vector2Add(Vector2 *out, const Vector2 *first, const Vector2 *second)
{
	if (!out || !first || !second)
		return NULL;

	scalar *vec1 = first->GetPointer();
	scalar *vec2 = second->GetPointer();

	vector_add(out->GetPointer(),vec1, vec2, 2);
	return out;
}

Vector3 * Dsim::Vector3Add(Vector3 *out, const Vector3 *first, const Vector3 *second)
{
	if (!out || !first || !second)
		return NULL;

	scalar *vec1 = first->GetPointer();
	scalar *vec2 = second->GetPointer();

	vector_add(out->GetPointer(),vec1, vec2, 3);
	return out;
}

Vector4 * Dsim::Vector4Add(Vector4 *out, const Vector4 *first, const Vector4 *second)
{
	if (!out || !first || !second)
		return NULL;

	scalar *vec1 = first->GetPointer();
	scalar *vec2 = second->GetPointer();

	vector_add(out->GetPointer(),vec1, vec2, 4);
	return out;
}

//SUBSTRACTION
Vector2 * Dsim::Vector2Substract(Vector2 *out, const Vector2 *first, const Vector2 *second)
{
	if (!out || !first || !second)
		return NULL;

	scalar *vec1 = first->GetPointer();
	scalar *vec2 = second->GetPointer();

	vector_substract(out->GetPointer(), vec1, vec2, 2);
	return out;
}

Vector3 * Dsim::Vector3Substract(Vector3 *out, const Vector3 *first, const Vector3 *second)
{
	if (!out || !first || !second)
		return NULL;

	scalar *vec1 = first->GetPointer();
	scalar *vec2 = second->GetPointer();

	vector_substract(out->GetPointer(), vec1, vec2, 3);
	return out;
}

Vector4 * Dsim::Vector4Substract(Vector4 *out, const Vector4 *first, const Vector4 *second)
{
	if (!out || !first || !second)
		return NULL;

	scalar *vec1 = first->GetPointer();
	scalar *vec2 = second->GetPointer();

	vector_substract(out->GetPointer(), vec1, vec2, 4);
	return out;
}

//SCALAR MULTIPLICATION
Vector2 * Dsim::Vector2ScalarMultiply(Vector2 *out, const Vector2 *vec, scalar s)
{
	if (!out || !vec)
		return NULL;

	scalar *vector = vec->GetPointer();

	vector_scale(out->GetPointer(), vector, s, 2);
	return out;
}

Vector3 * Dsim::Vector3ScalarMultiply(Vector3 *out, const Vector3 *vec, scalar s)
{
	if (!out || !vec)
		return NULL;

	scalar *vector = vec->GetPointer();

	vector_scale(out->GetPointer(), vector, s, 3);
	return out;
}

Vector4 * Dsim::Vector4ScalarMultiply(Vector4 *out, const Vector4 *vec, scalar s)
{
	if (!out || !vec)
		return NULL;

	scalar *vector = vec->GetPointer();

	vector_scale(out->GetPointer(), vector, s, 4);
	return out;
}

//DOT PRODUCT
scalar Dsim::Vector2Dot(const Vector2 *first, const Vector2 *second)
{
	if (!first || !second)
		return 0;

	scalar result;

	scalar *vec1 = first->GetPointer();
	scalar *vec2 = second->GetPointer();

	result = vector_dot(vec1, vec2, 2);
	return result;
}

scalar Dsim::Vector3Dot(const Vector3 *first, const Vector3 *second)
{
	if (!first || !second)
		return 0;

	scalar result;

	scalar *vec1 = first->GetPointer();
	scalar *vec2 = second->GetPointer();

	result = vector_dot(vec1, vec2, 3);
	return result;
}

scalar Dsim::Vector4Dot(const Vector4 *first, const Vector4 *second)
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
scalar Dsim::Vector2Length(const Vector2 *vec)
{
	if (!vec)
		return 0;

	return vector_length(vec->GetPointer(), 2);
}

scalar Dsim::Vector3Length(const Vector3 *vec)
{
	if (!vec)
		return 0;

	return vector_length( vec->GetPointer(), 3);
}

scalar Dsim::Vector4Length(const Vector4 *vec)
{
	if (!vec)
		return 0;

	return vector_length(vec->GetPointer(), 4);
}

//UNIT VECTORS
Vector2 * Dsim::Vector2Unit(Vector2 * out, const Vector2 *vec)
{
	if (!out || !vec)
		return NULL;

	vector_normalize(out->GetPointer(), vec->GetPointer(), 2);
	return out;
}

Vector3 * Dsim::Vector3Unit(Vector3 * out, const Vector3 *vec)
{
	if (!out || !vec)
		return NULL;

	vector_normalize(out->GetPointer(), vec->GetPointer(), 3);
	return out;
}

Vector4 * Dsim::Vector4Unit(Vector4 * out, const Vector4 *vec)
{
	if (!out || !vec)
		return NULL;

	vector_normalize(out->GetPointer(), vec->GetPointer(), 4);
	return out;
}

//CROSS PRODUCT
Vector3 * Dsim::Vector3Cross(Vector3 *out, const Vector3 *first, const Vector3 *second)
{
	scalar a, b, c;
	Vector3 i = Vector3(1, 0, 0);
	Vector3 j = Vector3(0, 1, 0);
	Vector3 k = Vector3(0, 0, 1);

	a = first->Y() * second->Z() - first->Z() * second->Y();
	b = first->Z() * second->X() - first->X() * second->Z();
	c = first->X() * second->Y() - first->Y() * second->X();

	Vector3Add(out, Vector3ScalarMultiply(&i, &i, a), Vector3ScalarMultiply(&j, &j, b));
	Vector3Add(out, out, Vector3ScalarMultiply(&k, &k ,c));
	return out;
}

//IDENTITY MATRICES
Matrix3x3 * Dsim::Matrix3x3Identity(Matrix3x3 *out)
{
	if (!out)
		return NULL;

	matrix_scale(out->GetPointer(), 3, 1);
	return out;
}

Matrix4x4 * Dsim::Matrix4x4Identity(Matrix4x4 *out)
{
	if (!out)
		return NULL;

	matrix_scale(out->GetPointer(), 4, 1);
	return out;
}

//SCALE MATRICES
Matrix3x3 * Dsim::Matrix3x3Scale(Matrix3x3 *out, scalar s)
{
	if (!out)
		return NULL;

	matrix_scale(out->GetPointer(), 3, s);
	return out;
}

Matrix4x4 * Dsim::Matrix4x4Scale(Matrix4x4 *out, scalar s)
{
	if (!out)
		return NULL;

	matrix_scale(out->GetPointer(), 4, s);
	return out;
}

//ROTATION MATRICES
//TODO: Implement 3x3 and rotation matrices
Matrix4x4 * Dsim::Matrix4x4RotationX(Matrix4x4 *out, scalar angle)
{
	if (!out)
		return NULL;

	Matrix4x4Identity(out);
	out->SetElement(1, 1, cos(angle));
	out->SetElement(2, 1, - sin(angle));
	out->SetElement(1, 2, sin(angle));
	out->SetElement(2, 2, cos(angle));

	return out;
}

Matrix4x4 * Dsim::Matrix4x4RotationY(Matrix4x4 *out, scalar angle)
{
	if (!out)
		return NULL;

	Matrix4x4Identity(out);
	out->SetElement(0, 0, cos(angle));
	out->SetElement(2, 0, - sin(angle));
	out->SetElement(0, 2, sin(angle));
	out->SetElement(2, 2, cos(angle));

	return out;
}

Matrix4x4 * Dsim::Matrix4x4RotationZ(Matrix4x4 *out, scalar angle)
{
	if (!out)
		return NULL;

	Matrix4x4Identity(out);
	out->SetElement(0, 0, cos(angle));
	out->SetElement(1, 0, - sin(angle));
	out->SetElement(0, 1, sin(angle));
	out->SetElement(1, 1, cos(angle));

	return out;
}


//VIEW Matrices
Matrix4x4 * Dsim::Matrix4x4ViewLookAt(Matrix4x4 * out, Vector3 *pos, Vector3 *lookAt, Vector3 *up)
{
	if (!out || !pos || !lookAt || !up)
		return NULL;

	Vector3 temp;
	Vector3 tempUp;
	Vector3 right;
	Vector3 look = *pos - *lookAt;

	look.normalize();
	Vector3Cross(&right, up, &look);
	right.normalize();

	Vector3Cross(&tempUp, &look, &right);
	tempUp.normalize();

	Matrix4x4Identity(out);
	out->SetElement(0, 0, right.X());
	out->SetElement(1, 0, right.Y());
	out->SetElement(2, 0, right.Z());
	out->SetElement(0, 1, tempUp.X());
	out->SetElement(1, 1, tempUp.Y());
	out->SetElement(2, 1, tempUp.Z());
	out->SetElement(0, 2, look.X());
	out->SetElement(1, 2, look.Y());
	out->SetElement(2, 2, look.Z());
	out->SetElement(0, 3, - Vector3Dot(&right, pos));
	out->SetElement(1, 3, - Vector3Dot(&tempUp, pos));
	out->SetElement(2, 3, - Vector3Dot(&look, pos));

	return out;
}

//PROJECTION MATRICES
Matrix4x4 * Dsim::Matrix4x4PerspectiveFov(Matrix4x4 *out, scalar fov, scalar ar, scalar z_near, scalar z_far)
{
	if (!out || !fov || !ar || !z_near || !z_far)
		return NULL;

	Matrix4x4Identity(out);

	scalar _cot = 1 / tan(fov / 2);

	out->SetElement(0, 0, _cot/ar);
	out->SetElement(1, 1, _cot);
	out->SetElement(2, 2, (scalar)((z_near + z_far) / (z_near - z_far)));
	out->SetElement(2, 3, (scalar)(2 * z_near*z_far / (z_near - z_far)));
	out->SetElement(3, 2, - 1);

	return out;
}

//MATRIX MULTIPLICATION
//TODO: Implement a more efficient matrix multiplication
Matrix3x3 * Dsim::Matrix3x3Multiply(Matrix3x3 *out, const Matrix3x3 *first, const Matrix3x3 *second)
{
	if (!out || !first || !second)
		return NULL;

	unsigned int i, j;
	for (i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			scalar value;
			Vector3 vec1, vec2;
			first->GetRow(&vec1, i);
			second->GetColumn(&vec2, j);
			value = Vector3Dot(&vec1, &vec2);
			out->SetElement(i, j, value);
		}
	}

	return out;
}

Matrix4x4 * Dsim::Matrix4x4Multiply(Matrix4x4 *out, const Matrix4x4 *first, const Matrix4x4 *second)
{
	if (!out || !first || !second)
		return NULL;

	unsigned int i, j;
	for (i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			scalar value;
			Vector4 vec1, vec2;
			first->GetRow(&vec1, i);
			second->GetColumn(&vec2, j);
			value = Vector4Dot(&vec1, &vec2);
			out->SetElement(i, j, value);
		}
	}

	return out;
}

//functions on C arrays
void vector_add(scalar *out, scalar *vec1, scalar *vec2, unsigned int size)
{
	if (!vec1 || !vec2 || !out || !size){
		return;
	}

	unsigned int i;

	for (i = 0; i < size; i++) {
		out[i] = vec1[i] + vec2[i];
	}
}

void vector_substract(scalar *out, scalar *vec1, scalar *vec2, unsigned int size)
{
	if (!vec1 || !vec2 || !out || !size)
		return;

	unsigned int i;

	for (i = 0; i < size; i++) {
		out[i] = vec1[i] - vec2[i];
	}
}

void vector_scale(scalar *out, scalar *vec, scalar s, unsigned int size)
{
	if (!vec || !out || !size)
		return;

	unsigned int i;

	for (i = 0; i < size; i++) {
		out[i] = vec[i] * s;
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

void vector_normalize(scalar *out, scalar *vec, unsigned int size)
{
	if (!vec || !out || !size)
		return;

	unsigned int i;
	unsigned int l = 0;

	l = vector_length(vec, size);

	for (i = 0; i < size; i++) {
		out[i] /= l;
	}
}

//functions on C square arrays
void matrix_scale(scalar *out, unsigned int size, scalar s)
{
	if(!out)
		return;

	int i, j;
	scalar (*matrix)[size] = (scalar (*)[size]) out;

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

