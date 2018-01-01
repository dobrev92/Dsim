#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "linear_algebra.h"

namespace Dsim {

class Quaternion
{
	private:
		scalar w, x, y, z;
	public:
		Quaternion() {}
		Quaternion(scalar aW, scalar aX, scalar aY, scalar aZ);
		Quaternion(scalar amount, const Vector3 *axis);

		scalar W() const { return w; }
		scalar X() const { return x; }
		scalar Y() const { return y; }
		scalar Z() const { return z; }

		scalar SetW(scalar aW) { return w = aW; }
		scalar SetX(scalar aX) { return x = aX; }
		scalar SetY(scalar aY) { return y = aY; }
		scalar SetZ(scalar aZ) { return z = aZ; }

		scalar Length() const;
		Quaternion * Normalize();
};

//Operators
Quaternion operator+(const Quaternion & left, const Quaternion & right);
Quaternion operator-(const Quaternion & left, const Quaternion & right);
Quaternion operator*(const Quaternion & left, const scalar & right);
Quaternion operator*(const scalar & left, const Quaternion & right);
Quaternion operator*(const Quaternion & left, const Quaternion & right);
Vector3 operator*(const Quaternion & left, const Vector3 & right);

//Quaternion Add
Quaternion * QuaternionAdd(Quaternion *out, const Quaternion *first, const Quaternion *second);

//Substract
Quaternion * QuaternionSubstract(Quaternion *out, const Quaternion *first, const Quaternion *second);

//Scale
Quaternion * QuaternionScalarMultiply(Quaternion *out, const Quaternion *quat, scalar s);

//Quaternion length
scalar QuaternionLength(const Quaternion *quat);

//Unit Quaternion
Quaternion * QuaternionUnit(Quaternion *out, const Quaternion *quat);

//Quaternion Inverse
Quaternion * QuaternionInverse(Quaternion *out, const Quaternion *quat);

//Quaternion multiplication
Quaternion * QuaternionMultiply(Quaternion *out, const Quaternion *left, const Quaternion *right);

//Rotating a vector with a quaternion
Vector3 * QuaternionRotate(Vector3 *out, const Quaternion *quat, const Vector3 *v);

//Conversion to rotation matrix
Matrix3x3 * QuaternionToMatrix3x3(Matrix3x3 *out, const Quaternion *quat);
Matrix4x4 * QuaternionToMatrix4x4(Matrix4x4 *out, const Quaternion *quat);

}

#endif //__QUATERNION_H__

