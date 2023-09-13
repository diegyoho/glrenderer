#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLI/IndexBuffer.h"
#include "GLI/Renderer.h"
#include "GLI/Shader.h"
#include "GLI/Texture.h"
#include "GLI/Material.h"
#include "GLI/VertexArray.h"
#include "GLI/VertexBuffer.h"
#include "Window/Window.h"

int main()
{
    Window window;
    GLI::Renderer renderer;
    GLI::Shader basicShader{ "Resources/Shaders/Basic.shader" };

    GLI::Shader textureShader{ "Resources/Shaders/Texture.shader" };
    GLI::Texture avatar{ "Resources/Textures/logo.png" };

    GLI::Material M_Texture
    {
         &textureShader,
         GLI::Material::MakeProperty("color", 1.0f, 1.0f, 1.0f, 1.0f),
         GLI::Material::MakeProperty("textureSampler", &avatar, 0)
    };

    float positions[16] =
    {
        80.0f,   0.0f,   0.0f, 0.0f, // 0
       560.0f,   0.0f,   1.0f, 0.0f, // 1
       560.0f, 480.0f,   1.0f, 1.0f, // 2
        80.0f, 480.0f,   0.0f, 1.0f  // 3
    };

    unsigned int indices[6] =
    {
        0, 1, 2,
        0, 2, 3
    };

    GLI::VertexArray vao
    {
        GLI::VertexBuffer::Make(16, positions),
        GLI::VertexArray::Layout
        {
            GLI::VertexArray::MakeVertexAttribute<float>(2),
            GLI::VertexArray::MakeVertexAttribute<float>(2)
        }
    };

    glm::mat4 projection = glm::ortho(0.0f, (float)window.GetWidth(), 0.0f, (float)window.GetHeight(), -1.0f, 1.0f);

    GLI::IndexBuffer ibo{ 6, indices };

    vao.Unbind();

    window.Loop
    (
        [&]()
        {
            renderer.Clear();
            textureShader.Bind();
            textureShader.SetUniformMatrix4f("MVP", projection);
            renderer.Draw(vao, ibo, M_Texture);
        }
    );

    return 0;
}
