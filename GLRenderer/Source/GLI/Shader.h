#pragma once

#include "GLObject.h"

#include <glm/glm.hpp>

#include <string>
#include <unordered_map>

namespace GLI
{
	enum class ShaderType
	{
		None = -1,
		Vertex,
		Fragment,
		Count
	};

	struct ShaderProgramSource
	{
		std::string VertexShader;
		std::string FragmentShader;

		bool IsEmpty()
		{
			return VertexShader.empty() && FragmentShader.empty();
		}
	};

	class Shader : public GLObject
	{
	private:

		std::string filepath;
		std::unordered_map<std::string, int> uniformLocationCache;

	public:

		Shader(const std::string& filepath);
		virtual ~Shader() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void SetUniform1i(const std::string& name, int value);
		void SetUniform1i(const std::string& name, const int* values);
		void SetUniform2i(const std::string& name, const int* values);
		void SetUniform3i(const std::string& name, const int* values);
		void SetUniform4i(const std::string& name, const int* values);
		void SetUniform1f(const std::string& name, const float* values);
		void SetUniform3f(const std::string& name, const float* values);
		void SetUniform2f(const std::string& name, const float* values);
		void SetUniform4f(const std::string& name, const float* values);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniformMatrix4f(const std::string& name, glm::mat4 value);

		inline std::string GetFilepath() const { return filepath; }
		
		static ShaderProgramSource LoadShaderProgramSource(const std::string& filepath);
		static unsigned int CompileShader(ShaderType type, const std::string& source);
		static unsigned int CompileShaderProgram(ShaderProgramSource source);

	private:

		int GetUniformLocation(const std::string& name);
	};
}

