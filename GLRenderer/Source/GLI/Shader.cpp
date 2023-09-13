#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <glad/glad.h>

namespace GLI
{
	Shader::Shader(const std::string& filepath) :
		filepath{ filepath }
	{
		ShaderProgramSource source = LoadShaderProgramSource(filepath);

		if (!source.IsEmpty())
			id = CompileShaderProgram(source);
	}

	Shader::~Shader()
	{
		glDeleteProgram(id);
	}

	void Shader::Bind() const
	{
		glUseProgram(id);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::SetUniform1i(const std::string& name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1i(const std::string& name, const int* values)
	{
		glUniform1iv(GetUniformLocation(name), 1, values);
	}

	void Shader::SetUniform4f(const std::string& name, const float* values)
	{
		glUniform4fv(GetUniformLocation(name), 1, values);
	}

	void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
	{
		glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
	}

	void Shader::SetUniformMatrix4f(const std::string& name, glm::mat4 value)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
	}

	int Shader::GetUniformLocation(const std::string& name)
	{
		if (uniformLocationCache.find(name) != uniformLocationCache.end())
		{
			return uniformLocationCache[name];
		}

		int location = glGetUniformLocation(id, name.c_str());
		if (location == -1)
		{
			std::cerr << "[Shader] " << name << " uniform location wasn't found!" << std::endl;
		}

		uniformLocationCache[name] = location;

		return location;
	}

	ShaderProgramSource Shader::LoadShaderProgramSource(const std::string& filepath)
	{
		std::ifstream stream(filepath);
		if (!stream.is_open()) {
			std::cerr << "[Shader] File not succesfully read: " << filepath << std::endl;
			return ShaderProgramSource{};
		}

		std::stringstream ss[(int)ShaderType::Count];

		ShaderType type = ShaderType::None;

		std::string line;
		while (std::getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					type = ShaderType::Vertex;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					type = ShaderType::Fragment;
				}
			}
			else if (type != ShaderType::None)
			{
				ss[(int)type] << line << '\n';
			}
		}

		return ShaderProgramSource
		{
			ss[(int)ShaderType::Vertex].str(),
			ss[(int)ShaderType::Fragment].str()
		};
	}

	unsigned int Shader::CompileShader(ShaderType type, const std::string& source)
	{
		if (source.empty())
		{
			std::cerr << "[Shader] " << (type == ShaderType::Vertex ? "Vertex" : "Fragment") << " shader is empty!" << std::endl;
			return 0;
		}

		unsigned int id;

		id = glCreateShader((type == ShaderType::Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER));
		const char* scr = source.c_str();
		glShaderSource(id, 1, &scr, NULL);
		glCompileShader(id);

		int success;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			int lenght;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);

			try
			{
				char* log = (char*)alloca(lenght * sizeof(char));
				glGetShaderInfoLog(id, lenght, &lenght, log);

				std::cerr << "[Shader] " << (type == ShaderType::Vertex ? "Vertex" : "Fragment") << " shader has compilation errors: " << log << std::endl;
				throw std::runtime_error("[Shader] Compilation Error! ");
			}
			catch (...)
			{
			}
		}

		return id;
	}

	unsigned int Shader::CompileShaderProgram(ShaderProgramSource source)
	{
		unsigned int id;

		id = glCreateProgram();

		unsigned int vs = CompileShader(ShaderType::Vertex, source.VertexShader);
		unsigned int fs = CompileShader(ShaderType::Fragment, source.FragmentShader);

		glAttachShader(id, vs);
		glAttachShader(id, fs);
		glLinkProgram(id);

		int success;
		glGetShaderiv(id, GL_LINK_STATUS, &success);

		if (success == GL_FALSE)
		{
			int lenght;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
			try
			{
				char* log = (char*)alloca(lenght * sizeof(char));
				glGetShaderInfoLog(id, lenght, &lenght, log);

				std::cerr << "[Shader] Shader Program has linking errors: " << log << std::endl;
				throw std::runtime_error("[Shader] Linking Error! ");
			}
			catch (...)
			{
			}
		}

		glDeleteShader(vs);
		glDeleteShader(fs);

		return id;
	}
}
