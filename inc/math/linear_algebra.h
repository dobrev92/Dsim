#ifndef __LINEAR_ALGEBRA_H__
#define __LINEAR_ALGEBRAH_H__

namespace Dsim {

#ifdef DOUBLEPRECISION
typedef double scalar;
#else 
typedef float scalar;
#endif

#define PI 3.14159265359

class Vector2
{
	private:
		scalar elements[2];
	public:
		Vector2();
		Vector2(scalar x, scalar y);

		scalar X() const { return elements[0]; }
		scalar Y() const { return elements[1]; }

		void SetX(scalar x) { elements[0] = x; }
		void SetY(scalar y) { elements[1] = y; }

		scalar GetElement(unsigned int e) const { return elements[e]; }
		scalar SetElement(unsigned int e, scalar value) { elements[e] = value; }

		scalar length() const;
		void normalize();

		scalar* GetPointer() const { return (scalar *)&elements[0]; }
};

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

		void SetX(scalar x) { elements[0] = x; }
		void SetY(scalar y) { elements[1] = y; }
		void SetZ(scalar z) { elements[2] = z; }

		scalar GetElement(unsigned int e) const { return elements[e]; }
		scalar SetElement(unsigned int e, scalar value) { elements[e] = value; }

		scalar length() const;
		void normalize();

		scalar* GetPointer() const { return (scalar *)&elements[0]; }
};

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
		void normalize();

		scalar* GetPointer() const { return (scalar *)&elements[0]; }
};

//Vector2
Vector2 operator+(const Vector2 & left, const Vector2 & right);
Vector2 operator-(const Vector2 & left, const Vector2 & right);
Vector2 operator*(const Vector2 & left, const scalar & right);
Vector2 operator*(const scalar & left, const Vector2 & right);

//Vector3
Vector3 operator+(const Vector3 & left, const Vector3 & right);
Vector3 operator-(const Vector3 & left, const Vector3 & right);
Vector3 operator*(const Vector3 & left, const scalar & right);
Vector3 operator*(const scalar & left, const Vector3 & right);

//vector4
Vector4 operator+(const Vector4 & left, const Vector4 & right);
Vector4 operator-(const Vector4 & left, const Vector4 & right);
Vector4 operator*(const Vector4 & left, const scalar & right);
Vector4 operator*(const scalar & left, const Vector4 & right);

class Matrix3x3 
{
	private:
		scalar elements[3][3];
	public:
		//Default constructor sets all elements to zero
		Matrix3x3() {}
		Matrix3x3(scalar s);
		Matrix3x3(Vector3 column1, Vector3 column2, Vector3 column3);
        
		//Get matrix element
		scalar GetElement(unsigned int col, unsigned int row);
		//Set matrix element
		void SetElement(unsigned int col, unsigned int row, scalar value);

		Vector3 GetColumn(unsigned int col);
		Vector3 GetRow(unsigned int row);

		scalar* GetPointer() { return &elements[0][0]; }
};

class Matrix4x4 
{
	private:
		scalar elements[4][4];
	public:
		//Default constructor sets all elements to zero
		Matrix4x4();
		Matrix4x4(Vector4 column1, Vector4 column2, Vector4 column3, Vector4 column4);
        
		//Get matrix element
		scalar GetElement(int row, int column);
		//Set matrix element
		void SetElement(int row, int column, scalar value);

		//Get Rows, from 0 to 3 for a 4x4 Matrix
		Vector4 GetRow(int row);
		//Get Columns, from 0 to 3
		Vector4 GetColumn(int column);

		scalar* GetPointer() { return &elements[0][0]; }
};



//Vector arithmetic functions
Vector2 * AddVector2D(Vector2 *out, const Vector2 *first, const Vector2 *second);
Vector3 * AddVector3D(Vector3 *out, const Vector3 *first, const Vector3 *second);
Vector4 * AddVector4D(Vector4 *out, const Vector4 *first, const Vector4 *second);

//substract second from first
Vector2 * SubstractVector2D(Vector2 *out, const Vector2 *first, const Vector2 *second);
Vector3 * SubstractVector3D(Vector3 *out, const Vector3 *first, const Vector3 *second);
Vector4 * SubstractVector4D(Vector4 *out, const Vector4 *first, const Vector4 *second);

//Vector multiplication by a scalar
Vector2 * VecScalarMultiply2D(Vector2 *out, const Vector2 *vec, scalar s);
Vector3 * VecScalarMultiply3D(Vector3 *out, const Vector3 *vec, scalar s);
Vector4 * VecScalarMultiply4D(Vector4 *out, const Vector4 *vec, scalar s);

//Dot products for all dimensions 
scalar DotProduct2D(const Vector2 *first, const Vector2 *second);
scalar DotProduct3D(const Vector3 *first, const Vector3 *second);
scalar DotProduct4D(const Vector4 *first, const Vector4 *second);

//Length
scalar VectorLength2D(const Vector2 *vec);
scalar VectorLength3D(const Vector3 *vec);
scalar VectorLength4D(const Vector4 *vec);

//Unit Vectors
Vector2 * GetUnitVector2D(Vector2 * out, const Vector2 *vec);
Vector3 * GetUnitVector3D(Vector3 * out, const Vector3 *vec);
Vector4 * GetUnitVector2D(Vector4 * out, const Vector4 *vec);

//cross product
Vector3 * VectorCross3D(Vector3 *out, const Vector3 *first, const Vector3 *second);

//Mtrix arithmetic functions
//Matrix2x2 Matrix2x2Identity();
Matrix3x3 Matrix3x3Identity(Matrix3x3 *out);
Matrix4x4 Matrix4x4Identity(Matrix4x4 *out);

//Scale Matrices;
Matrix3x3 Matrix3x3Scale(Matrix3x3 *out, scalar s);
Matrix3x3 Matrix3x3Scale(Matrix3x3 *out, Vector3 s);
Matrix3x3 Matrix3x3Scale(Matrix3x3 *out, scalar x, scalar y, scalar z);

//Rotation Matrices
Matrix3x3 Matrix3x3RotationX(Matrix3x3 *out, scalar angle);
Matrix3x3 Matrix3x3RotationY(Matrix3x3 *out, scalar angle);
Matrix3x3 Matrix3x3RotationY(Matrix3x3 *out, scalar angle);

//Matrix Multiplication
Matrix3x3 Matrix3x3Multiply(Matrix3x3 first, Matrix3x3 second);

}

#endif //__LINEAR_ALGEBRA_H__
