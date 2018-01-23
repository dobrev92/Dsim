#ifndef __VERTEX_INDEX_DATA_H__
#define __VERTEX_INDEX_DATA_H__

namespace Dsim {

class VertexBufferTmp;
class VertexDeclaration;
class VertexBufferBinding;
class IndexBufferTmp;
typedef std::shared_ptr<VertexBufferTmp> VertexBufferSharedPtr;
typedef std::shared_ptr<IndexBufferTmp> IndexBufferSharedPtr;

class VertexData
{
	protected:
	public:
		VertexData() {}
		VertexData(VertexDeclaration *dcl, VertexBufferBinding *bind);

		VertexDeclaration *vertDecl;
		VertexBufferBinding *vertBind;

		size_t vertexStart;
		size_t vertexCount;

		//Additional stuff to be added

		~VertexData();
};

class IndexData
{
	protected:
	public:
		IndexBufferSharedPtr indexBuffer;

		size_t indexStart;
		size_t indexCount;
};

}

#endif //__VERTEX_INDEX_DATA_H__

