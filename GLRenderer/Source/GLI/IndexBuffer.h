#pragma once

#include "IBuffer.h"

namespace GLI
{
	class IndexBuffer : public IBuffer
	{
	public:

		template<typename T>
		IndexBuffer(unsigned int count, const T* data);
	};

	template IndexBuffer::IndexBuffer(unsigned int, const unsigned int*);
}

