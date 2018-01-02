#ifndef __NODE_H__
#define __NODE_H__

#include <vector>

#include "math/linear_algebra.h"
#include "math/Quaternion.h"

namespace Dsim {

typedef enum {
	//Transform relative to local space
	TS_LOCAL,
	//Transform is relatice to the space of parent node
	TS_PARENT,
	//Transform is relatice to world space
	TS_WORLD,
} TransformSpace;

//TODO: This needs to be redefined and optimized.
class Node
{
	protected:
		typedef std::vector<Node *> ChildrenList;
		typedef std::vector<Node *>::iterator NodeIterator;

		Node *mParent;
		ChildrenList mChildren;

		//position
		Vector3 mPosition;
		//orientation
		Quaternion mOrientation;
		//scale
		Vector3 mScale;

		Vector3 mParentPosition;
		Quaternion mParentOrientation;
		Vector3 mParentScale;

		Vector3 mDerivedPosition;
		Quaternion mDerivedOrientation;
		Vector3 mDerivedScale;

		bool mInheritOrientation;
		bool mInheritScale;

		bool mCachedTransformOutOfDate;
		Matrix4x4 mCachedTransform;
	public:
		Node();
		
		void SetParent(Node *parent) { mParent = parent; }
		void AddChild(Node *child);

		Vector3 GetPosition();
		Quaternion GetOrientation();
		Vector3 GetScale();

		Vector3 WorldToLocalDirection(Vector3 worldDir, bool useScale);
		Vector3 LocalToWorldDirection(Vector3 localDir, bool useScale);

		void Translate(scalar x, scalar y, scalar z, TransformSpace relativeTo = TS_PARENT);
		void Translate(Vector3 distance, TransformSpace relativeTo = TS_PARENT);
		void Translate(Vector3 dir, scalar distance, TransformSpace relativeTo = TS_PARENT);

		//TODO: optimize there for quaternions or 3x3 orientation matrices
		void Rotate(Quaternion q, TransformSpace relativeTo = TS_LOCAL);
		void Rotate(Vector3 axis, scalar angle, TransformSpace relativeTo = TS_LOCAL);

		virtual void Yaw(scalar angle, TransformSpace relativeTo = TS_LOCAL) {}
		virtual void Pitch(scalar angle, TransformSpace relativeTo = TS_LOCAL) {}
		virtual void Roll(scalar angle, TransformSpace relativeTo = TS_LOCAL) {}

		virtual void Update();

		virtual Matrix4x4 GetFullTransform();

		virtual ~Node();
};

}

#endif //__NODE_H__
