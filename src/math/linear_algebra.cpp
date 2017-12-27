#include "math/linear_algebra.h"
#include <math.h>
#include <cstring>

#include "debug.h"

using namespace Dsim;

//functions on C single arrays
static void vector_add(scalar *out, scalar *vec1, scalar *vec2, unsigned int size);
static void vector_substract(scalar *out, scalar *vec1, scalar *vec2, unsigned int size);
static void vector_multiply(scalar *out, scalar *vec1, scalar *vec2, unsigned int size);
static void vector_scale(scalar *out, scalar *vec, scalar s, unsigned int size);
static scalar vector_dot(scalar *vec1, scalar *vec2, unsigned int size);
static scalar vector_length(scalar *vec, unsigned int size);
static void vector_normalize(scalar *out, scalar *vec, unsigned int size);

//functions on C square arrays
static void matrix_scale(scalar *out, unsigned int size, scalar s);
static void matrix_transpose(scalar *out, scalar *mat, unsigned int size);

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

Vector2 Dsim::operator*(const Vector2 & left, const Vector2 & right)
{
	Vector2 result;

	Vector2Multiply(&result, &left, &right);
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

Vector3 Dsim::operator*(const Vector3 & left, const Vector3 & right)
{
	Vector3 result;

	Vector3Multiply(&result, &left, &right);
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

Vector4 Dsim::operator*(const Vector4 & left, const Vector4 & right)
{
	Vector4 result;

	Vector4Multiply(&result, &left, &right);
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

//Matrix2x2
Matrix2x2::Matrix2x2(scalar s)
{
	Matrix2x2Identity((Matrix2x2 *)&elements[0][0]);
}

//TODO: Implement column Matrix2x2 constructor
Matrix2x2::Matrix2x2(Vector2 *col0, Vector2 *col1)
{
	Matrix2x2Identity((Matrix2x2 *)&elements[0][0]);
}

scalar Matrix2x2::GetElement(unsigned int row, unsigned int col) const
{
	if (col > 1 || row > 1)
		return 0;

	return elements[col][row];
}

scalar Matrix2x2::SetElement(unsigned int row, unsigned int col, scalar value)
{
	if (col > 1 || row > 1)
		return 0;

	elements[col][row] = value;
	return elements[col][row];
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

Matrix3x3 Dsim::operator*(const Matrix3x3 & left, const Matrix3x3 & right)
{
	Matrix3x3 result;

	Matrix3x3Multiply(&result, &left, &right);
	return result;
}

Vector3 operator*(const Matrix3x3 & mat, const Vector3 & vec)
{
	Vector3 result;

	Matrix3x3TransformCoord(&result, &mat, &vec);
	return result;
}

//Matrix4x4
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

Vector4 operator*(const Matrix4x4 & mat, const Vector4 & vec)
{
	Vector4 result;

	Matrix4x4TransformCoord(&result, &mat, &vec);
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

//ELEMENTWISE MULTIPLICATION
Vector2 * Dsim::Vector2Multiply(Vector2 *out, const Vector2 *first, const Vector2 *second)
{
	if (!out || !first || !second)
		return NULL;

	scalar *vec1 = first->GetPointer();
	scalar *vec2 = second->GetPointer();

	vector_multiply(out->GetPointer(), vec1, vec2, 2);
	return out;
}

Vector3 * Dsim::Vector3Multiply(Vector3 *out, const Vector3 *first, const Vector3 *second)
{
	if (!out || !first || !second)
		return NULL;

	scalar *vec1 = first->GetPointer();
	scalar *vec2 = second->GetPointer();

	vector_multiply(out->GetPointer(), vec1, vec2, 3);
	return out;
}

Vector4 * Dsim::Vector4Multiply(Vector4 *out, const Vector4 *first, const Vector4 *second)
{
	if (!out || !first || !second)
		return NULL;

	scalar *vec1 = first->GetPointer();
	scalar *vec2 = second->GetPointer();

	vector_multiply(out->GetPointer(), vec1, vec2, 4);
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

//MATRIX SCALAR MULTIPLICATION
Matrix2x2 * Dsim::Matrix2x2ScalarMultiply(Matrix2x2 *out, const Matrix2x2 *mat, scalar s)
{
	if (!out || !mat)
		return NULL;

	vector_scale(out->GetPointer(), mat->GetPointer(), s, 4);
	return out;
}

Matrix3x3 * Dsim::Matrix3x3ScalarMultiply(Matrix3x3 *out, const Matrix3x3 *mat, scalar s)
{
	if (!out || !mat)
		return NULL;

	vector_scale(out->GetPointer(), mat->GetPointer(), s, 9);
	return out;
}

Matrix4x4 * Dsim::Matrix4x4ScalarMultiply(Matrix4x4 *out, const Matrix4x4 *mat, scalar s)
{
	if (!out || !mat)
		return NULL;

	vector_scale(out->GetPointer(), mat->GetPointer(), s, 16);
	return out;
}

//TRANSPOSE
Matrix2x2 * Dsim::Matrix2x2Transpose(Matrix2x2 *out, const Matrix2x2 *mat)
{
	if (!out || !mat)
		return NULL;

	matrix_transpose(out->GetPointer(), mat->GetPointer(), 2);
	return out;
}

Matrix3x3 * Dsim::Matrix3x3Transpose(Matrix3x3 *out, const Matrix3x3 *mat)
{
	if (!out || !mat)
		return NULL;

	matrix_transpose(out->GetPointer(), mat->GetPointer(), 3);
	return out;
}

Matrix4x4 * Dsim::Matrix4x4Transpose(Matrix4x4 *out, const Matrix4x4 *mat)
{
	if (!out || !mat)
		return NULL;

	matrix_transpose(out->GetPointer(), mat->GetPointer(), 4);
	return out;
}

//IDENTITY MATRICES
Matrix2x2 * Dsim::Matrix2x2Identity(Matrix2x2 *out)
{
	if (!out)
		return NULL;

	matrix_scale(out->GetPointer(), 2, 1);
	return out;
}

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

//Submatrices
Matrix2x2 * Dsim::Matrix3x3Submatrix(Matrix2x2 *out, const Matrix3x3 *mat, unsigned int row, unsigned int col)
{
	if (!out || !mat)
		return NULL;

	int i, j, k, l;
	k = 0;
	l = 0;

	Matrix2x2Identity(out);
	for (i = 0; i < 3; i++) {
		l = 0;
		if (i == row) {
			continue;
		}
		for (j = 0; j < 3; j++) {
			if (j == col) {
				continue;
			}
			out->SetElement(k, l, mat->GetElement(i, j));
		l++;
		}
	k++;
	}
	return out;
}

Matrix3x3 * Dsim::Matrix4x4Submatrix(Matrix3x3 *out, const Matrix4x4 *mat, unsigned int row, unsigned int col)
{
	if (!out || !mat)
		return NULL;

	int i, j, k, l;
	k = 0;
	l = 0;

	Matrix3x3Identity(out);
	for (i = 0; i < 4; i++) {
		l = 0;
		if (i == row) {
			continue;
		}
		for (j = 0; j < 4; j++) {
			if (j == col) {
				continue;
			}
			out->SetElement(k, l, mat->GetElement(i, j));
		l++;
		}
	k++;
	}
	return out;
}

//DETERMINANTS
scalar Dsim::Matrix2x2Determinant(const Matrix2x2 *mat)
{
	if (!mat)
		return 0;

	scalar ret = 	mat->GetElement(0, 0) * mat->GetElement(1, 1) -
			mat->GetElement(0, 1) * mat->GetElement(1, 0);

	return ret;
}

scalar Dsim::Matrix3x3Determinant(const Matrix3x3 *mat)
{
	if (!mat)
		return 0;

	int i;
	scalar det = 0;

	for (i = 0; i < 3; i++) {
		det += mat->GetElement(0, i) * Matrix3x3Cofactor(mat, 0, i);
	}

	return det;
}

scalar Dsim::Matrix4x4Determinant(const Matrix4x4 *mat)
{
	if (!mat)
		return 0;

	int i;
	scalar det = 0;

	for (i = 0; i < 4; i++) {
		det += mat->GetElement(0, i) * Matrix4x4Cofactor(mat, 0, i);
	}

	return det;
}

//COFACTORS
scalar Dsim::Matrix3x3Cofactor(const Matrix3x3 *mat, unsigned int row, unsigned int col)
{
	if (!mat || row > 2 || col > 2)
		return 0;

	scalar det, ret;
	Matrix2x2 submatrix;

	Matrix3x3Submatrix(&submatrix, mat, row, col);
	det = Matrix2x2Determinant(&submatrix);
	ret = pow(- 1, row + col) * det;
	return ret;
}

scalar Dsim::Matrix4x4Cofactor(const Matrix4x4 *mat, unsigned int row, unsigned int col)
{
	if (!mat || row > 3 || col > 3)
		return 0;

	scalar det, ret;
	Matrix3x3 submatrix;

	Matrix4x4Submatrix(&submatrix, mat, row, col);
	det = Matrix3x3Determinant(&submatrix);
	ret = pow(- 1, row + col) * det;

	return ret;
}

//COFACTOR MATRICES
Matrix3x3 * Dsim::Matrix3x3CofactorMatrix(Matrix3x3 *out, const Matrix3x3 *mat)
{
	if (!out || !mat)
		return NULL;

	unsigned int i, j;
	Matrix3x3 res;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			res.SetElement(i, j, Matrix3x3Cofactor(mat, i, j));
		}
	}

	memcpy(out, &res, sizeof(Matrix3x3));
	return out;
}

Matrix4x4 * Dsim::Matrix4x4CofactorMatrix(Matrix4x4 *out, const Matrix4x4 *mat)
{
	if (!out || !mat)
		return NULL;

	unsigned int i, j;
	Matrix4x4 res;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			res.SetElement(i, j, Matrix4x4Cofactor(mat, i, j));
		}
	}

	memcpy(out, &res, sizeof(Matrix4x4));
	return out;
}

//MATRIX INVERSE
Matrix2x2 * Dsim::Matrix2x2Inverse(Matrix2x2 *out, const Matrix2x2 *mat)
{
	return NULL;
}

Matrix3x3 * Dsim::Matrix3x3Inverse(Matrix3x3 *out, const Matrix3x3 *mat)
{
	if (!out || !mat)
		return NULL;

	Matrix3x3 ret;
	scalar det;

	Matrix3x3CofactorMatrix(&ret, mat);
	Matrix3x3Transpose(&ret, &ret);
	det = Matrix3x3Determinant(mat);
	Matrix3x3ScalarMultiply(&ret, &ret, 1 / det);
	memcpy(out, &ret, sizeof(Matrix3x3));
	return out;
}

Matrix4x4 * Dsim::Matrix4x4Inverse(Matrix4x4 *out, const Matrix4x4 *mat)
{
	if (!out || !mat)
		return NULL;

	Matrix4x4 ret;
	scalar det;

	Matrix4x4CofactorMatrix(&ret, mat);
	Matrix4x4Transpose(&ret, &ret);
	det = Matrix4x4Determinant(mat);
	Matrix4x4ScalarMultiply(&ret, &ret, 1 / det);
	memcpy(out, &ret, sizeof(Matrix4x4));
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

Matrix4x4 * Dsim::Matrix4x4Scale(Matrix4x4 *out, scalar x, scalar y, scalar z)
{
	if (!out)
		return NULL;

	Matrix4x4Identity(out);
	out->SetElement(0, 0, x);
	out->SetElement(1, 1, y);
	out->SetElement(2, 2, z);

	return out;
}

Matrix4x4 * Dsim::Matrix4x4Scale(Matrix4x4 *out, const Vector3 *s)
{
	if (!out || !s)
		return NULL;

	return Matrix4x4Scale(out, s->X(), s->Y(), s->Z());
}

//TRANSLATION
Matrix4x4 * Dsim::Matrix4x4Translation(Matrix4x4 *out, scalar x, scalar y, scalar z)
{
	if (!out)
		return NULL;

	Matrix4x4Identity(out);
	out->SetElement(0, 3, x);
	out->SetElement(1, 3, y);
	out->SetElement(2, 3, z);

	return out;
}

Matrix4x4 * Dsim::Matrix4x4Translation(Matrix4x4 *out, const Vector3 *trans)
{
	if (!out || !trans)
		return NULL;

	Matrix4x4Translation(out, trans->X(), trans->Y(), trans->Z());
}

//ROTATION MATRICES
Matrix3x3 * Dsim::Matrix3x3RotationX(Matrix3x3 *out, scalar angle)
{
	if (!out)
		return NULL;

	Matrix3x3Identity(out);
	out->SetElement(1, 1, cos(angle));
	out->SetElement(2, 1, - sin(angle));
	out->SetElement(1, 2, sin(angle));
	out->SetElement(2, 2, cos(angle));

	return out;
}

Matrix3x3 * Dsim::Matrix3x3RotationY(Matrix3x3 *out, scalar angle)
{
	if (!out)
		return NULL;

	Matrix3x3Identity(out);
	out->SetElement(0, 0, cos(angle));
	out->SetElement(2, 0, - sin(angle));
	out->SetElement(0, 2, sin(angle));
	out->SetElement(2, 2, cos(angle));

	return out;
}

Matrix3x3 * Dsim::Matrix3x3RotationZ(Matrix3x3 *out, scalar angle)
{
	if (!out)
		return NULL;

	Matrix3x3Identity(out);
	out->SetElement(0, 0, cos(angle));
	out->SetElement(1, 0, - sin(angle));
	out->SetElement(0, 1, sin(angle));
	out->SetElement(1, 1, cos(angle));

	return out;
}

Matrix3x3 * Dsim::Matrix3x3YawPitchRoll(Matrix3x3 *out, scalar yaw, scalar pitch, scalar roll)
{
	if (!out)
		return NULL;

	Matrix3x3 result, x, y, z;

	Matrix3x3RotationX(&x, pitch);
	Matrix3x3RotationY(&y, yaw);
	Matrix3x3RotationZ(&z, roll);

	result = z * x * y;
	memcpy(out, &result, sizeof(Matrix3x3));
	return out;
}

Matrix3x3 * Matrix3x3YawPitchRoll(Matrix3x3 *out, const Vector3 *angles)
{
	if (!out || !angles)
		return NULL;

	return Matrix3x3YawPitchRoll(out, angles->X(), angles->Y(), angles->Z());
}

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

Matrix4x4 * Dsim::Matrix4x4YawPitchRoll(Matrix4x4 *out, scalar yaw, scalar pitch, scalar roll)
{
	if (!out)
		return NULL;

	Matrix4x4 result, x, y, z;

	Matrix4x4RotationX(&x, pitch);
	Matrix4x4RotationY(&y, yaw);
	Matrix4x4RotationZ(&z, roll);

	result = z * x * y;
	memcpy(out, &result, sizeof(Matrix4x4));
	return out;
}

Matrix4x4 * Dsim::Matrix4x4YawPitchRoll(Matrix4x4 *out, const Vector3 *angles)
{
	if (!out || !angles)
		return NULL;

	return Matrix4x4YawPitchRoll(out, angles->X(), angles->Y(), angles->Z());
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

//TRANSFORM COORDINATES
Vector3 *Dsim::Matrix3x3TransformCoord(Vector3 *out, const Matrix3x3 *mat, const Vector3 *vec)
{
	if (!out || !mat || !vec)
		return NULL;

	unsigned int i;
	for (i = 0; i < 3; i++) {
		scalar value;
		Vector3 row;
		mat->GetRow(&row, i);
		value = Vector3Dot(&row, vec);
		out->SetElement(i, value);
	}

	return out;
}

Vector4 *Dsim::Matrix4x4TransformCoord(Vector4 *out, const Matrix4x4 *mat, const Vector4 *vec)
{
	if (!out || !mat || !vec)
		return NULL;

	unsigned int i;
	for (i = 0; i < 4; i++) {
		scalar value;
		Vector4 row;
		mat->GetRow(&row, i);
		value = Vector4Dot(&row, vec);
		out->SetElement(i, value);
	}

	return out;
}

//WORLD TRANSFORM
Matrix4x4 * Dsim::Matrix4x4WorldTransform(Matrix4x4 *out, const Vector3 *pos, const Vector3 *orientation, const Vector3 *scale)
{
	if (!out || !pos || !orientation || !scale)
		return NULL;

	Matrix4x4 trans, rot, scaling, result;

	Matrix4x4Translation(&trans, pos);
	Matrix4x4YawPitchRoll(&rot, orientation);
	Matrix4x4Scale(&scaling, scale);

	result = trans * rot * scaling;
	memcpy(out, &result, sizeof(Matrix4x4));
	return out;
}

//functions on C arrays
void vector_add(scalar *out, scalar *vec1, scalar *vec2, unsigned int size)
{
	if (!vec1 || !vec2 || !out || !size)
		return;

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

static void vector_multiply(scalar *out, scalar *vec1, scalar *vec2, unsigned int size)
{
	if (!vec1 || !vec2 || !out || !size)
		return;

	unsigned int i;

	for (i = 0; i < size; i++) {
		out[i] = vec1[i] * vec2[i];
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

//TODO: Make it in-place
void matrix_transpose(scalar *out, scalar *mat, unsigned int size)
{
	if (!out || !mat || size < 2)
		return;

	int i, j;
	scalar (*matrix)[size] = (scalar (*)[size]) mat;
	scalar temp[size][size];

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			temp[i][j] = matrix[j][i];
		}
	}

	memcpy(out, &temp, size * size * sizeof(scalar));
}
