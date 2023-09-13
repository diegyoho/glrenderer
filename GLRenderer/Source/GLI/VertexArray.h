#pragma once

#include "GLObject.h"

#include <vector>
#include <type_traits>

namespace GLI
{
	class VertexBuffer;

	class VertexArray : public GLObject
	{
	private:

		struct VertexAttribute
		{
			unsigned int type;
			unsigned int count;
			bool normalized;
			unsigned int size;
		};

		std::vector<VertexBuffer*> buffers;

	public:

		struct Layout
		{
			std::vector<VertexAttribute*> layout;

			unsigned int stride{};

			template <typename... T, typename = std::enable_if<std::conjunction<std::is_convertible<T, VertexAttribute*>...>::value>::type>
			Layout(T... args) :
				layout{ args... }
			{
				for (const auto& vertexAttribute : layout)
				{
					this->AddStride(vertexAttribute->count * vertexAttribute->size);
				}
			}

			const VertexAttribute& operator[](unsigned int) const;

			inline size_t Count() const { return layout.size(); }
			inline unsigned int GetStride() const { return stride; }
			inline void AddStride(unsigned int size) { stride += size; }
		};

		VertexArray();
		VertexArray(VertexBuffer* buffer, const Layout& layout);
		virtual ~VertexArray() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void AddVertexBufferLayout(VertexBuffer* buffer, const Layout& layout);
		
		template<typename T>
		static VertexAttribute* MakeVertexAttribute(unsigned int count, bool normalized = false);
	};
}

