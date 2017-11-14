#ifndef __LINEAR_ALGEBRA_H__
#define __LINEARALGEBRAH_H__

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

		scalar X() { return elements[0]; }
		scalar Y() { return elements[1]; }

		void SetX(scalar x) { elements[0] = x; }
		void SetY(scalar y) { elements[1] = y; }

		scalar GetElement(unsigned int e) { return elements[e]; }
		scalar SetElement(unsigned int e, scalar value) { elements[e] = value; }

		scalar length();
		void normalize();

		scalar* GetPointer() { return elements; }
};

class Vector3
{
	private:
		scalar elements[3];
	public:
		Vector3();
		Vector3(scalar x, scalar y, scalar z);

		scalar X() { return elements[0]; }
		scalar Y() { return elements[1]; }
		scalar Z() { return elements[2]; }

		void SetX(scalar x) { elements[0] = x; }
		void SetY(scalar y) { elements[1] = y; }
		void SetZ(scalar z) { elements[2] = z; }

		scalar GetElement(unsigned int e) { return elements[e]; }
		scalar SetElement(unsigned int e, scalar value) { elements[e] = value; }

		scalar length();
		void normalize();

		scalar* GetPointer() { return elements; }
};

class Vector4
{
	private:
		scalar elements[4];
	public:
		Vector4();
		Vector4(scalar x, scalar y, scalar z, scalar w);
		Vector4(Vector3 vec, scalar w);

		scalar X() { return elements[0]; }
		scalar Y() { return elements[1]; }
		scalar Z() { return elements[2]; }
		scalar W() { return elements[3]; }

		void SetX(scalar x) { elements[0] = x; }
		void SetY(scalar y) { elements[1] = y; }
		void SetZ(scalar z) { elements[2] = z; }
		void SetW(scalar w) { elements[3] = w; }

		scalar GetElement(unsigned int e) { return elements[e]; }
		scalar SetElement(unsigned int e, scalar value) { elements[e] = value; }

		scalar length();
		void normalize();

		scalar* GetPointer() { return elements; }
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
		Matrix3x3();
		Matrix3x3(Vector3 column1, Vector3 column2, Vector3 column3);
        
		//Get matrix element
		scalar GetElement(int row, int column);
		//Set matrix element
		void SetElement(int row, int column, scalar value);

		//Get Rows, from 0 to 2 for a 3x3 Matrix
		Vector3 GetRow(int row);
		//Get Columns, from 0 to 2
		Vector3 GetColumn(int column);

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
Vector2 AddVector2D(Vector2 first, Vector2 second);
Vector3 AddVector3D(Vector3 first, Vector3 second);
Vector4 AddVector4D(Vector4 first, Vector4 second);

//substract second from first
Vector2 SubstractVector2D(Vector2 first, Vector2 second);
Vector3 SubstractVector3D(Vector3 first, Vector3 second);
Vector4 SubstractVector4D(Vector4 first, Vector4 second);

//Vector multiplication by a scalar
Vector2 VecScalarMultiply2D(Vector2 vec, scalar s);
Vector3 VecScalarMultiply3D(Vector3 vec, scalar s);
Vector4 VecScalarMultiply4D(Vector4 vec, scalar s);

//Dot products for all dimensions 
scalar DotProduct2D(Vector2 first, Vector2 second);
scalar DotProduct3D(Vector3 first, Vector3 second);
scalar DotProduct4D(Vector4 first, Vector4 second);

//cross product
Vector3 VectorCross3D(Vector3 first, Vector3 second);

//Mtrix arithmetic functions
//Matrix2x2 Matrix2x2Identity();
Matrix3x3 Matrix3x3Identity();
Matrix4x4 Matrix4x4Identity();

}

#endif //__LINEAR_ALGEBRA_H__
