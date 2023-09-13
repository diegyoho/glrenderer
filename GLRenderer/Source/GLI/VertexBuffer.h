#pragma once

#include "IBuffer.h"

namespace GLI
{
	struct Vertex;

	class VertexBuffer : public IBuffer
	{
	private:
		
		template<typename T>
		VertexBuffer(unsigned int count, const T* data);
	
	public:

		template<typename T>
		static VertexBuffer* Make(unsigned int count, const T* data);
		
	};

	template VertexBuffer* VertexBuffer::Make(unsigned int, const int*);
	template VertexBuffer* VertexBuffer::Make(unsigned int, const unsigned int*);
	template VertexBuffer* VertexBuffer::Make(unsigned int, const float*);
	template VertexBuffer* VertexBuffer::Make(unsigned int, const Vertex*);
}

