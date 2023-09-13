#include "IndexBuffer.h"

#include <glad/glad.h>

namespace GLI
{
	template<typename T>
	IndexBuffer::IndexBuffer(unsigned int count, const T* data) :
		IBuffer(GL_ELEMENT_ARRAY_BUFFER, count, data)
	{
	}
}
