#pragma once

namespace GLI
{
	class GLObject
	{
	protected:

		unsigned int id{};

	public:

		virtual ~GLObject() = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		inline unsigned int GetID() const { return id; }
	};
}

