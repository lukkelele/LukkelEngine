#pragma once

#include <unordered_map>
#include <GLErrorHandler.h>
#include <glm/glm.hpp>

#define debug true

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
private:
	std::string m_filePath;
	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	unsigned int m_RendererID;
	Shader(const std::string& filepath);
	Shader();
	~Shader();

	void bind() const;
	void unbind() const;

	int getUniformLocation(const std::string& name);
	void setUniform1i(const std::string& name, int value);
	void setUniform1f(const std::string& name, float value);
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniformMat4f(const std::string& name, const glm::mat4& matrix);

	ShaderProgramSource parseShader(const std::string& filepath);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
private:
};
