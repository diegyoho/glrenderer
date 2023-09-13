#pragma once

#include<vector>

#include <glm/glm.hpp>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace GLI
{

	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	class Mesh
	{
	private:

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		VertexArray* vao;
		VertexBuffer* vbo;
		IndexBuffer* ebo;

	public:

		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
		virtual ~Mesh();

		inline unsigned int GetVAO() const { return vao->GetID(); }
		inline unsigned int GetIndicesCount() const { return ebo->GetCount(); }
	};
}

