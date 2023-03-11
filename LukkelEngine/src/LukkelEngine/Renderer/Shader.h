#pragma once
#include "LukkelEngine/Core/LKErrorHandler.h"
#include "glm/glm.hpp"

namespace LukkelEngine {

	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Shader
	{
	public:
		Shader() = default;
		Shader(const std::string& filepath);
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		~Shader();

		void bind() const;
		void unbind() const;

		int getUniformLocation(const std::string& name);
		void setUniform1i(const std::string& name, int value);
		void setUniform1f(const std::string& name, float value);
		void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void setUniformMat4f(const std::string& name, const glm::mat4& matrix);

		ShaderProgramSource parseShader(const std::string& filepath);
		ShaderProgramSource parseShaders(const std::string& vertexPath, const std::string& fragmentPath);
		unsigned int compileShader(unsigned int type, const std::string& source);
		unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);

	private:
		std::string m_FilePath;
		std::string m_VertexPath;
		std::string m_FragmentPath;
		std::unordered_map<std::string, int> m_UniformLocationCache;
		unsigned int m_RendererID;
	};

}
