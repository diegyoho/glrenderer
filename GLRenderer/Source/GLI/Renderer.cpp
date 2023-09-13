#include "Renderer.h"

#include <glad/glad.h>

#include "IndexBuffer.h"
#include "Material.h"
#include "VertexArray.h"

namespace GLI
{
	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ibo, const Material& material)
	{
		vao.Bind();
		material.Activate();

		glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
