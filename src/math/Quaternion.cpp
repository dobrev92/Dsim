#include <cmath>
#include <cstring>

#include "math/Quaternion.h"
#include "debug.h"

using namespace Dsim;

Quaternion::Quaternion(scalar aW, scalar aX, scalar aY, scalar aZ)
{
	w = aW;
	x = aX;
	y = aY;
	z = aZ;
}

Quaternion::Quaternion(scalar amount, const Vector3 *axis)
{
	w = amount;
	x = axis->X();
	y = axis->Y();
	z = axis->Z();
}

scalar Quaternion::Length() const
{
	return QuaternionLength(this);
}

Quaternion * Quaternion::Normalize()
{
	return QuaternionUnit(this, this);
}

Quaternion Dsim::operator+(const Quaternion & left, const Quaternion & right)
{
	Quaternion result;

	QuaternionAdd(&result, &left, &right);
	return result;
}

Quaternion Dsim::operator-(const Quaternion & left, const Quaternion & right)
{
	Quaternion result;

	QuaternionSubstract(&result, &left, &right);
	return result;
}

Quaternion Dsim::operator*(const Quaternion & left, const scalar & right)
{
	Quaternion result;

	QuaternionScalarMultiply(&result, &left, right);
	return result;
}

Quaternion Dsim::operator*(const scalar & left, const Quaternion & right)
{
	Quaternion result;

	QuaternionScalarMultiply(&result, &right, left);
	return result;
}

Quaternion Dsim::operator*(const Quaternion & left, const Quaternion & right)
{
	Quaternion result;

	QuaternionMultiply(&result, &left, &right);
	return result;
}

Vector3 Dsim::operator*(const Quaternion & left, const Vector3 & right)
{
	Vector3 result;

	QuaternionRotate(&result, &left, &right);
	return result;
}

//ADD
Quaternion * Dsim::QuaternionAdd(Quaternion *out, const Quaternion *first, const Quaternion *second)
{
	if (!out || !first || !second)
		return NULL;

	out->SetW(first->W() + second->W());
	out->SetX(first->X() + second->X());
	out->SetY(first->Y() + second->Y());
	out->SetZ(first->Z() + second->Z());

	return out;
}

//SUBSTRACT
Quaternion * Dsim::QuaternionSubstract(Quaternion *out, const Quaternion *first, const Quaternion *second)
{
	if (!out || !first || !second)
		return NULL;

	out->SetW(first->W() - second->W());
	out->SetX(first->X() - second->X());
	out->SetY(first->Y() - second->Y());
	out->SetZ(first->Z() - second->Z());

	return out;
}

//SCALE
Quaternion * Dsim::QuaternionScalarMultiply(Quaternion *out, const Quaternion *quat, scalar s)
{
	if (!out || !quat)
		return NULL;

	out->SetW(quat->W() * s);
	out->SetX(quat->X() * s);
	out->SetY(quat->Y() * s);
	out->SetZ(quat->Z() * s);

	return out;
}

//LENGTH
scalar Dsim::QuaternionLength(const Quaternion *quat)
{
	if (!quat)
		return 0;

	scalar length;
	length =	quat->W() * quat->W() +
			quat->X() * quat->X() +
			quat->Y() * quat->Y() +
			quat->Z() * quat->Z();

	length = sqrt(length);
	return length;
}

Quaternion * Dsim::QuaternionUnit(Quaternion *out, const Quaternion *quat)
{
	if (!out || !quat)
		return NULL;

	Quaternion result;
	scalar length = QuaternionLength(quat);

	result = *quat * (1 / length);
	memcpy(out, &result, sizeof(Quaternion));
	return out;
}

Quaternion * Dsim::QuaternionInverse(Quaternion *out, const Quaternion *quat)
{
	if (!out || !quat)
		return NULL;

	Quaternion result;
	scalar invNormSq;

	invNormSq = QuaternionLength(quat) * QuaternionLength(quat);
	if (invNormSq <= 0.0f)
		return NULL;

	invNormSq = 1.0f / invNormSq;
	result = Quaternion(quat->W() * invNormSq, - quat->X() * invNormSq, - quat->Y() * invNormSq, - quat->Z() * invNormSq);

	memcpy(out, &result, sizeof(Quaternion));
	return out;
}

//MULTIPLY
Quaternion * Dsim::QuaternionMultiply(Quaternion *out, const Quaternion *left, const Quaternion *right)
{
	if (!out || !left || !right)
		return NULL;

	Quaternion result;

	result.SetW(left->W() * right->W() - left->X() * right->X() - left->Y() * right->Y() - left->Z() * right->Z());
	result.SetX(left->W() * right->X() + left->X() * right->W() + left->Y() * right->Z() - left->Z() * right->Y());
	result.SetY(left->W() * right->Y() + left->Y() * right->W() + left->Z() * right->X() - left->X() * right->Z());
	result.SetZ(left->W() * right->Z() + left->Z() * right->W() + left->X() * right->Y() - left->Y() * right->X());

	memcpy(out, &result, sizeof(Quaternion));
	return out;
}

//ROTATION
Vector3 * Dsim::QuaternionRotate(Vector3 *out, const Quaternion *quat, const Vector3 *v)
{
	if (!out || !quat || !v)
		return NULL;

	//nVidia SDK implementation
	Vector3 result, uv, uuv;
	Vector3 qvec(quat->X(), quat->Y(), quat->Z());

	Vector3Cross(&uv, &qvec, v);
	Vector3Cross(&uuv, &qvec, &uv);

	uv *= (2.0f * quat->W());
	uuv *= 2.0f;

	result = *v + uv + uuv;

	memcpy(out, &result, sizeof(Vector3));
	return out;
}

//CONVERSIONS
Matrix3x3 * Dsim::QuaternionToMatrix3x3(Matrix3x3* out, const Quaternion *quat)
{
	if (!out || !quat)
		return NULL;

	scalar w = quat->W();
	scalar x = quat->X();
	scalar y = quat->Y();
	scalar z = quat->Z();

	scalar fTx = x + x;
        scalar fTy = y + y;
        scalar fTz = z + z;
        scalar fTwx = fTx * w;
        scalar fTwy = fTy * w;
        scalar fTwz = fTz * w;
        scalar fTxx = fTx * x;
        scalar fTxy = fTy * x;
        scalar fTxz = fTz * x;
        scalar fTyy = fTy * y;
        scalar fTyz = fTz * y;
        scalar fTzz = fTz * z;

	out->SetElement(0, 0, 1.0f - (fTyy + fTzz));
	out->SetElement(0, 1, fTxy - fTwz);
	out->SetElement(0, 2, fTxz + fTwy);
	out->SetElement(1, 0, fTxy + fTwz);
	out->SetElement(1, 1, 1.0f - (fTxx + fTzz));
	out->SetElement(1, 2, fTyz - fTwx);
	out->SetElement(2, 0, fTxz - fTwy);
	out->SetElement(2, 1, fTyz + fTwx);
	out->SetElement(2, 2, 1.0f - (fTxx + fTyy));

	return out;
}

Matrix4x4 * Dsim::QuaternionToMatrix4x4(Matrix4x4* out, const Quaternion *quat)
{
	if (!out || !quat)
		return NULL;

	Matrix3x3 mat3;

	QuaternionToMatrix3x3(&mat3, quat);

	Matrix4x4 result(&mat3);
	memcpy(out, &result, sizeof(Matrix4x4));
	return out;
}

//FROM AXIS
Quaternion * Dsim::QuaternionFromAxis(Quaternion *out, const Vector3 *axis, scalar angle)
{
	if (!out || !axis)
		return NULL;

	//axis is unit length
        //
        // The quaternion representing the rotation is
        //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

	scalar halfAngle = angle / 2;
	scalar fSin = sin(halfAngle);

	out->SetW(cos(halfAngle));
	out->SetX(fSin * axis->X());
	out->SetY(fSin * axis->Y());
	out->SetZ(fSin * axis->Z());

	return out;
}

