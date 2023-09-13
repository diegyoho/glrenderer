#include "Texture.h"

#include <iostream>

#include <glad/glad.h>
#include <stb_image.h>

namespace GLI
{
	Texture::Texture(const std::string& filepath) :
		filepath{ filepath }
	{
		id = LoadTexture(filepath, &width, &height, &channels, data);
	}
	
	Texture::~Texture()
	{
		glDeleteTextures(1, &id);
	}

	void Texture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}
	
	void Texture::Activate(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		Bind();
		// Weird code for studies purpose, never ever do it again. NEVER!
		// (this->*static_cast<void(GLObject::*)() const>(&GLObject::Bind))();
	}

	void Texture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	unsigned int Texture::LoadTexture(
		const std::string& filepath,
		int* width,
		int* height,
		int* channels,
		unsigned char* data
	)
	{
		if (filepath.empty())
		{
			std::cout << "[Texture] The filepath is empty!" << std::endl;
			return 0;
		}

		unsigned int id;
		glGenTextures(1, &id);

		stbi_set_flip_vertically_on_load(true);
		data = stbi_load(filepath.c_str(), width, height, channels, 0);

		if (data)
		{
			GLenum internalFormat{};
			GLenum format{};

			switch (*channels)
			{
			case 1:
				internalFormat = GL_R8;
				format = GL_RED;
				break;
			case 3:
				internalFormat = GL_RGB8;
				format = GL_RGB;
				break;
			case 4:
				internalFormat = GL_RGBA8;
				format = GL_RGBA;
				break;
			default:
				break;
			}

			glBindTexture(GL_TEXTURE_2D, id);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


			glTexImage2D(GL_TEXTURE_2D, 0, format, *width, *height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "[Texture] Failed to load at path: " << filepath << std::endl;
			stbi_image_free(data);
			
			*width = *height = *channels = 0;
			data = nullptr;

			return 0;
		}

		return id;
	}
}
