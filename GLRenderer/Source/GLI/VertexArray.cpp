#include "VertexArray.h"

#include <glad/glad.h>

#include "VertexBuffer.h"

namespace GLI
{
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &id);
    }

    VertexArray::VertexArray(VertexBuffer* buffer, const Layout& layout) :
        VertexArray()
    {
        AddVertexBufferLayout(buffer, layout);
    }

    VertexArray::~VertexArray()
    {
        for (const auto& buffer : buffers)
        {
            if(buffer)
                delete buffer;
        }

        glDeleteVertexArrays(1, &id);
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(id);
    }

    void VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void VertexArray::AddVertexBufferLayout(VertexBuffer* buffer, const Layout& layout)
    {
        buffers.push_back(buffer);
        Bind();
        buffer->Bind();

        unsigned int offset{ 0 };

        for (size_t i = 0; i < layout.Count(); ++i)
        {
            auto& layoutElement = layout[i];

            glEnableVertexAttribArray(i);
            glVertexAttribPointer(
                i, layoutElement.count, layoutElement.type,
                layoutElement.normalized, layout.GetStride(), (const void*)offset
            );

            offset += layoutElement.count * layoutElement.size;
        }
    }

    template<>
    VertexArray::VertexAttribute* VertexArray::MakeVertexAttribute<float>(unsigned int count, bool normalized)
    {
        return new VertexAttribute{ GL_FLOAT , count, normalized, sizeof(float) };
    }

    const VertexArray::VertexAttribute& VertexArray::Layout::operator[](unsigned int index) const
    {
        return *layout[index];
    }
}
