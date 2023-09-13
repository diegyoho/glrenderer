#include "Mesh.h"

namespace GLI
{
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) :
		vertices{ vertices },
		indices{ indices }
	{
        vbo = VertexBuffer::Make(vertices.size(), &vertices[0]);
        vao = new VertexArray
        {
            vbo,
            VertexArray::Layout
            {
                VertexArray::MakeVertexAttribute<float>(3),
                VertexArray::MakeVertexAttribute<float>(3),
                VertexArray::MakeVertexAttribute<float>(2)
            }
        };

        ebo = new IndexBuffer{ (unsigned int) indices.size(), &indices[0] };

        vao->Unbind();
	}

	Mesh::~Mesh()
	{
        delete vao;
        delete ebo;
	}
}
