#include "Node.h"
#include "debug.h"

using namespace Dsim;

Node::Node()
{
	dbg_info("\n");
	mParent = NULL;
	mCachedTransformOutOfDate = true;
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

Vector3 Node::GetOrientation()
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
	Matrix3x3 inv;

	Matrix3x3YawPitchRoll(&inv, &mDerivedOrientation);
	Matrix3x3Inverse(&inv, &inv);
	if (useScale) {
		result = inv * (worldDir / mDerivedScale);
	} else {
		result = inv * worldDir;
	}

	return result;
}

void Node::Translate(Vector3 distance, TransformSpace relativeTo)
{
	//Used to transform some coordinates
	//TODO: This should be optimized
	Matrix3x3 trans;

	switch (relativeTo) {
		case TS_LOCAL:
			Matrix3x3YawPitchRoll(&trans, &mOrientation);
			mPosition = trans * distance;
			break;
		case TS_WORLD:
			if (mParent) {
				mPosition = mPosition + mParent->WorldToLocalDirection(distance, true);
			} else {
				mPosition = mPosition + distance;
			}
			break;
		case TS_PARENT:
			mPosition = mPosition + distance;
			break;
		}

		//Update and stuff
		Update();
}

void Node::Update()
{
	//dbg_info("\n");
	if (mParent) {
		//used to rotate position based on parent's orientation
		Matrix3x3 rot;

		mParentOrientation = mParent->GetOrientation();
		if (mInheritOrientation) {
			mDerivedOrientation = mOrientation + mParentOrientation;
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
		Matrix3x3YawPitchRoll(&rot, &mParentOrientation);
		mDerivedPosition = rot * (mParentScale * mPosition);
		mDerivedPosition = mDerivedPosition + mParentPosition;
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

