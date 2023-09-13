#pragma once

namespace GLI
{
	class IndexBuffer;
	class Material;
	class VertexArray;
	
	class Renderer
	{
	private:

	public:

		Renderer();
		~Renderer();

		void Clear();
		void Draw(const VertexArray& vao, const IndexBuffer& ibo, const Material& material);
	};
}

