#include "VertexBuffer.h"

#include <glad/glad.h>

namespace GLI
{
	template<typename T>
	VertexBuffer::VertexBuffer(unsigned int count, const T* data) :
		IBuffer(GL_ARRAY_BUFFER, count, data)
	{
	}

	template<typename T>
	VertexBuffer* VertexBuffer::Make(unsigned int count, const T* data)
	{
		return new VertexBuffer{ count, data };
	}
}
