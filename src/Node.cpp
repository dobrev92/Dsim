#include "Node.h"
#include "debug.h"

using namespace Dsim;

Node::Node()
{
	dbg_info("\n");
	mParent = NULL;
	mCachedTransformOutOfDate = true;

	mOrientation = Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
	mPosition = Vector3(0.0f, 0.0f, 0.0f);
	mScale = Vector3(1.0f, 1.0f, 1.0f);
}

void Node::AddChild(Node *child)
{
	dbg_info("\n");
	mChildren.push_back(child);
	child->SetParent(this);

	Update();
}

Vector3 Node::GetPosition()
{
	return mDerivedPosition;
}

Quaternion Node::GetOrientation()
{
	return mDerivedOrientation;
}

Vector3 Node::GetScale()
{
	return mDerivedScale;
}

Vector3 Node::WorldToLocalDirection(Vector3 worldDir, bool useScale)
{
	Vector3 result;
	Quaternion inv;

	QuaternionInverse(&inv, &mDerivedOrientation);
	if (useScale) {
		result = inv * (worldDir / mDerivedScale);
	} else {
		result = inv * worldDir;
	}

	return result;
}

void Node::Translate(scalar x, scalar y, scalar z, TransformSpace relativeTo)
{
	Vector3 distance(x, y, z);
	Translate(distance, relativeTo);
}

void Node::Translate(Vector3 distance, TransformSpace relativeTo)
{
	switch (relativeTo) {
		case TS_LOCAL:
			mPosition += mOrientation * distance;
			break;
		case TS_WORLD:
			if (mParent) {
				mPosition = mPosition + mParent->WorldToLocalDirection(distance, true);
			} else {
				mPosition += distance;
			}
			break;
		case TS_PARENT:
			mPosition += distance;
			break;
		}

		//Update and stuff
		Update();
}

void Node::Rotate(Quaternion q, TransformSpace relativeTo)
{
	Quaternion inv;

	switch (relativeTo) {
		case TS_LOCAL:
			mOrientation = mOrientation * q;
			break;
		case TS_WORLD:
			QuaternionInverse(&inv, &mDerivedOrientation);
			mOrientation = mOrientation * inv * q * mDerivedOrientation;
			break;
		case TS_PARENT:
			mOrientation = q * mOrientation;
			break;
		}

		//Update
		Update();
}

void Node::Rotate(Vector3 axis, scalar angle, TransformSpace relativeTo)
{
	Quaternion rot;
	QuaternionFromAxis(&rot, &axis, angle);

	Rotate(rot, relativeTo);
}

void Node::Update()
{
	//dbg_info("\n");
	if (mParent) {
		//used to rotate position based on parent's orientation
		mParentOrientation = mParent->GetOrientation();
		if (mInheritOrientation) {
			mDerivedOrientation = mParentOrientation * mOrientation;
		} else {
			mDerivedOrientation = mOrientation;
		}

		mParentScale = mParent->GetScale();
		if (mInheritScale) {
			mDerivedScale = mScale * mParentScale;
		} else {
			mDerivedScale = mScale;
		}

		mParentPosition = mParent->GetPosition();
		mDerivedPosition = mParentOrientation * (mParentScale * mPosition);
		mDerivedPosition += mParentPosition;
	} else {
		mDerivedOrientation = mOrientation;
		mDerivedScale = mScale;
		mDerivedPosition = mPosition;
	}

	mCachedTransformOutOfDate = true;
	return;
}

Matrix4x4 Node::GetFullTransform()
{
	if (mCachedTransformOutOfDate) {
		Matrix4x4WorldTransform(&mCachedTransform, &mDerivedPosition, &mDerivedOrientation, &mDerivedScale);
		mCachedTransformOutOfDate = false;
	}

	return mCachedTransform;
}

Node::~Node()
{
	unsigned int i;
	unsigned int size;

	dbg_info("\n");
	size = mChildren.size();
	for (i = 0; i < size; i++) {
		Node * node = mChildren.back();
		mChildren.pop_back();
		delete node;
	}
}

