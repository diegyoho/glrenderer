#include "IBuffer.h"

#include <glad/glad.h>

#include "Mesh.h"

namespace GLI
{
	template<typename T>
	IBuffer::IBuffer(unsigned int target, unsigned int count, const T* data) :
		target{ target },
		count{ count }
	{
		glGenBuffers(1, &id);
		glBindBuffer(target, id);

		glBufferData(target, count * sizeof(T), data, GL_STATIC_DRAW);
	}

	IBuffer::~IBuffer()
	{
		glDeleteBuffers(1, &id);
	}

	void IBuffer::Bind() const
	{
		glBindBuffer(target, id);
	}

	void IBuffer::Unbind() const
	{
		glBindBuffer(target, 0);
	}
}
