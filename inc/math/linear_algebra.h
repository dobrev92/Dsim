#ifndef __LINEAR_ALGEBRA_H__
#define __LINEAR_ALGEBRA_H__

namespace Dsim {

#ifdef DOUBLE_PRECISION
typedef double scalar;
#else 
typedef float scalar;
#endif

#define PI 3.14159265359
#define EULER 2.71828182846

//TODO: Redefine vector methods to return scalar
class Vector2
{
	private:
		scalar elements[2];
	public:
		Vector2();
		Vector2(scalar x, scalar y);

		scalar X() const { return elements[0]; }
		scalar Y() const { return elements[1]; }

		scalar SetX(scalar x) { elements[0] = x; }
		scalar SetY(scalar y) { elements[1] = y; }

		scalar GetElement(unsigned int e) const { return elements[e]; }
		scalar SetElement(unsigned int e, scalar value) { elements[e] = value; }

		scalar length() const;
		Vector2 * normalize();

		scalar* GetPointer() const { return (scalar *)&elements[0]; }
};

//Vector2 Operators
Vector2 operator+(const Vector2 & left, const Vector2 & right);
Vector2 operator-(const Vector2 & left, const Vector2 & right);
Vector2 operator*(const Vector2 & left, const scalar & right);
Vector2 operator*(const scalar & left, const Vector2 & right);


class Vector3
{
	private:
		scalar elements[3];
	public:
		Vector3();
		Vector3(scalar x, scalar y, scalar z);

		scalar X() const { return elements[0]; }
		scalar Y() const { return elements[1]; }
		scalar Z() const { return elements[2]; }

		scalar SetX(scalar x) { elements[0] = x; }
		scalar SetY(scalar y) { elements[1] = y; }
		scalar SetZ(scalar z) { elements[2] = z; }

		scalar GetElement(unsigned int e) const { return elements[e]; }
		scalar SetElement(unsigned int e, scalar value) { elements[e] = value; }

		scalar length() const;
		Vector3 * normalize();

		scalar* GetPointer() const { return (scalar *)&elements[0]; }
};

//Vector3 Operators
Vector3 operator+(const Vector3 & left, const Vector3 & right);
Vector3 operator-(const Vector3 & left, const Vector3 & right);
Vector3 operator*(const Vector3 & left, const scalar & right);
Vector3 operator*(const scalar & left, const Vector3 & right);


class Vector4
{
	private:
		scalar elements[4];
	public:
		Vector4();
		Vector4(scalar x, scalar y, scalar z, scalar w);
		Vector4(Vector3 vec, scalar w);

		scalar X() const { return elements[0]; }
		scalar Y() const { return elements[1]; }
		scalar Z() const { return elements[2]; }
		scalar W() const { return elements[3]; }

		void SetX(scalar x) { elements[0] = x; }
		void SetY(scalar y) { elements[1] = y; }
		void SetZ(scalar z) { elements[2] = z; }
		void SetW(scalar w) { elements[3] = w; }

		scalar GetElement(unsigned int e) const { return elements[e]; }
		scalar SetElement(unsigned int e, scalar value) { elements[e] = value; }

		scalar length() const;
		Vector4 * normalize();

		scalar* GetPointer() const { return (scalar *)&elements[0]; }
};

//Vector4 Operators
Vector4 operator+(const Vector4 & left, const Vector4 & right);
Vector4 operator-(const Vector4 & left, const Vector4 & right);
Vector4 operator*(const Vector4 & left, const scalar & right);
Vector4 operator*(const scalar & left, const Vector4 & right);

//TODO: Implement 2x2 Matrix class
class Matrix2x2
{
	private:
		scalar elements[2][2];

	public:
		Matrix2x2() {}
		Matrix2x2(scalar s);
		Matrix2x2(Vector2 column1, Vector2 column2);
};

//Matrix2x2 Operators
Matrix2x2 operator+(const Matrix2x2 & left, const Matrix2x2 & right);
Matrix2x2 operator-(const Matrix2x2 & left, const Matrix2x2 & right);
Matrix2x2 operator*(const Matrix2x2 & left, const scalar & right);
Matrix2x2 operator*(const scalar & left, const Matrix2x2 & right);
Matrix2x2 operator*(const Matrix2x2 & left, const Matrix2x2 & right);


class Matrix3x3 
{
	private:
		scalar elements[3][3];
	public:
		//Default constructor sets all elements to zero
		Matrix3x3() {}
		Matrix3x3(scalar s);
		Matrix3x3(Vector3 *column1, Vector3 *column2, Vector3 *column3);
        
		//Get matrix element
		scalar GetElement(unsigned int row, unsigned int col) const;
		//Set matrix element
		scalar SetElement(unsigned int row, unsigned int col, scalar value);

		Vector3 * GetColumn(Vector3 *out, unsigned int col) const;
		Vector3 * GetRow(Vector3 *out, unsigned int row) const;

		scalar * GetPointer() const { return (scalar *) &elements[0][0]; }
};

//Matrix3x3 Operators
Matrix3x3 operator+(const Matrix3x3 & left, const Matrix3x3 & right);
Matrix3x3 operator-(const Matrix3x3 & left, const Matrix3x3 & right);
Matrix3x3 operator*(const Matrix3x3 & left, const scalar & right);
Matrix3x3 operator*(const scalar & left, const Matrix3x3 & right);
Matrix3x3 operator*(const Matrix3x3 & left, const Matrix3x3 & right);


class Matrix4x4 
{
	private:
		scalar elements[4][4];
	public:
		//Default constructor sets all elements to zero
		Matrix4x4() {}
		Matrix4x4(scalar s);
		Matrix4x4(Vector4 *col0, Vector4 *col1, Vector4 *col2, Vector4 *col3);
        
		//Get matrix element
		scalar GetElement(unsigned int row, unsigned int column) const;
		//Set matrix element
		scalar SetElement(unsigned int row, unsigned int column, scalar value);

		Vector4 * GetColumn(Vector4 *out, unsigned int col) const;
		Vector4 * GetRow(Vector4 *out, unsigned int row) const;

		scalar* GetPointer() { return &elements[0][0]; }
};

//Matrix4x4 Operators
Matrix4x4 operator+(const Matrix4x4 & left, const Matrix4x4 & right);
Matrix4x4 operator-(const Matrix4x4 & left, const Matrix4x4 & right);
Matrix4x4 operator*(const Matrix4x4 & left, const scalar & right);
Matrix4x4 operator*(const scalar & left, const Matrix4x4 & right);
Matrix4x4 operator*(const Matrix4x4 & left, const Matrix4x4 & right);


//Vector arithmetic functions
//add vectors first and second
Vector2 * Vector2Add(Vector2 *out, const Vector2 *first, const Vector2 *second);
Vector3 * Vector3Add(Vector3 *out, const Vector3 *first, const Vector3 *second);
Vector4 * Vector4Add(Vector4 *out, const Vector4 *first, const Vector4 *second);

//substract second from first
Vector2 * Vector2Substract(Vector2 *out, const Vector2 *first, const Vector2 *second);
Vector3 * Vector3Substract(Vector3 *out, const Vector3 *first, const Vector3 *second);
Vector4 * Vector4Substract(Vector4 *out, const Vector4 *first, const Vector4 *second);

//Vector multiplication by a scalar
Vector2 * Vector2ScalarMultiply(Vector2 *out, const Vector2 *vec, scalar s);
Vector3 * Vector3ScalarMultiply(Vector3 *out, const Vector3 *vec, scalar s);
Vector4 * Vector4ScalarMultiply(Vector4 *out, const Vector4 *vec, scalar s);

//Dot products for all dimensions 
scalar Vector2Dot(const Vector2 *first, const Vector2 *second);
scalar Vector3Dot(const Vector3 *first, const Vector3 *second);
scalar Vector4Dot(const Vector4 *first, const Vector4 *second);

//Length
scalar Vector2Length(const Vector2 *vec);
scalar Vector3Length(const Vector3 *vec);
scalar Vector4Length(const Vector4 *vec);

//Unit Vectors
Vector2 * Vector2Unit(Vector2 * out, const Vector2 *vec);
Vector3 * Vector3Unit(Vector3 * out, const Vector3 *vec);
Vector4 * Vector4Unit(Vector4 * out, const Vector4 *vec);

//cross product
Vector3 * Vector3Cross(Vector3 *out, const Vector3 *first, const Vector3 *second);

//Mtrix arithmetic functions
//add
Matrix2x2 * Matrix2x2Add(Matrix2x2 *out, const Matrix2x2 *first, const Matrix2x2 *second);
Matrix3x3 * Matrix3x3Add(Matrix3x3 *out, const Matrix3x3 *first, const Matrix3x3 *second);
Matrix4x4 * Matrix4x4Add(Matrix4x4 *out, const Matrix4x4 *first, const Matrix4x4 *second);

//substract
Matrix2x2 * Matrix2x2Substract(Matrix2x2 *out, const Matrix2x2 *first, const Matrix2x2 *second);
Matrix3x3 * Matrix3x3Substract(Matrix3x3 *out, const Matrix3x3 *first, const Matrix3x3 *second);
Matrix4x4 * Matrix4x4Substract(Matrix4x4 *out, const Matrix4x4 *first, const Matrix4x4 *second);

//Matrix multiplication by a scalar
Matrix2x2 * Matrix2x2ScalarMultiply(Matrix2x2 *out, const Matrix2x2 *vec, scalar s);
Matrix3x3 * Matrix2x2ScalarMultiply(Matrix3x3 *out, const Matrix3x3 *vec, scalar s);
Matrix4x4 * Matrix4x4ScalarMultiply(Matrix4x4 *out, const Matrix4x4 *vec, scalar s);

//Identity
Matrix2x2 * Matrix2x2Identity(Matrix2x2 *out);
Matrix3x3 * Matrix3x3Identity(Matrix3x3 *out);
Matrix4x4 * Matrix4x4Identity(Matrix4x4 *out);

//Scale Matrices;
Matrix3x3 * Matrix3x3Scale(Matrix3x3 *out, scalar s);
Matrix3x3 * Matrix3x3Scale(Matrix3x3 *out, const Vector3 *s);
Matrix3x3 * Matrix3x3Scale(Matrix3x3 *out, scalar x, scalar y, scalar z);

Matrix4x4 * Matrix4x4Scale(Matrix4x4 *out, scalar s);
Matrix4x4 * Matrix4x4Scale(Matrix4x4 *out, const Vector4 *s);
Matrix4x4 * Matrix3x4Scale(Matrix4x4 *out, scalar x, scalar y, scalar z, scalar w);

//Rotation Matrices, angle is in radians
Matrix3x3 * Matrix3x3RotationX(Matrix3x3 *out, scalar angle);
Matrix3x3 * Matrix3x3RotationY(Matrix3x3 *out, scalar angle);
Matrix3x3 * Matrix3x3RotationZ(Matrix3x3 *out, scalar angle);

Matrix4x4 * Matrix4x4RotationX(Matrix4x4 *out, scalar angle);
Matrix4x4 * Matrix4x4RotationY(Matrix4x4 *out, scalar angle);
Matrix4x4 * Matrix4x4RotationZ(Matrix4x4 *out, scalar angle);

//View Matrices
Matrix4x4 * Matrix4x4ViewLookAt(Matrix4x4 * out, Vector3 *pos, Vector3 *lookAt, Vector3 *up);

//Projection Matrices
Matrix4x4 * Matrix4x4PerspectiveFov(Matrix4x4 *out, scalar fov, scalar ar, scalar z_near, scalar z_far);

//Matrix Multiplication
Matrix2x2 * Matrix2x2Multiply(Matrix2x2 *out, const Matrix2x2 *first, const Matrix2x2 *second);
Matrix3x3 * Matrix3x3Multiply(Matrix3x3 *out, const Matrix3x3 *first, const Matrix3x3 *second);
Matrix4x4 * Matrix4x4Multiply(Matrix4x4 *out, const Matrix4x4 *first, const Matrix4x4 *second);

}

#endif //__LINEAR_ALGEBRA_H__
