#pragma once

#include "GLObject.h"

namespace GLI
{
	struct Vertex;

	class IBuffer : public GLObject
	{
	protected:

		unsigned int target{};
		unsigned int count{};

	public:

		template<typename T>
		IBuffer(unsigned int target, unsigned int count, const T* data);
		virtual ~IBuffer() override = 0;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		inline unsigned int GetID() const { return id; }
		inline unsigned int GetCount() const { return count; }
	};

	template IBuffer::IBuffer(unsigned int, unsigned int, const int*);
	template IBuffer::IBuffer(unsigned int, unsigned int, const unsigned int*);
	template IBuffer::IBuffer(unsigned int, unsigned int, const float*);
	template IBuffer::IBuffer(unsigned int, unsigned int, const Vertex*);
}

