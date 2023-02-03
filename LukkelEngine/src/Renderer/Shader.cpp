#include <Shader.h>

namespace LukkelEngine {

	Shader::Shader() {} 

	Shader::Shader(const std::string& filePath)
		: m_filePath(filePath)   // keep for debug purposes
	{
		ShaderProgramSource source = parseShader(filePath);
		m_RendererID = createShader(source.VertexSource, source.FragmentSource);
	}

	Shader::~Shader()
	{
		GLCall(glDeleteProgram(m_RendererID));	// successful if m_RendererID isn't 0
	}

	void Shader::bind() const
	{
		GLCall(glUseProgram(m_RendererID));
	}

	void Shader::unbind() const
	{
		GLCall(glUseProgram(0));
	}

	void Shader::setUniform1i(const std::string& name, int value)
	{
		GLCall(glUniform1i(getUniformLocation(name), value));
	}

	void Shader::setUniform1f(const std::string& name, float value)
	{
		GLCall(glUniform1f(getUniformLocation(name), value));
	}

	void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
	{
		int location = getUniformLocation(name);
		GLCall(glUniform4f(location, v0, v1, v2, v3));
	}

	void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix)
	{
		GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
	}

	int Shader::getUniformLocation(const std::string& name)
	{
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];

		GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
		if (location == -1) 
			std::cout << "[SHADER] Warning: uniform " << name << " isn't in use" << std::endl;

		m_UniformLocationCache[name] = location;
		return location;
	}

	unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		unsigned int program = glCreateProgram();
		unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
		
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		// NOTE: Detach shaders instead of deleting IF needed for debugging 
		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}

	ShaderProgramSource Shader::parseShader(const std::string& filepath)
	{
		enum class ShaderType
		{
			NONE = -1,
			VERTEX = 0,
			FRAGMENT = 1
		};

		std::ifstream stream(filepath);
		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;

		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos) {
				if (line.find("vertex") != std::string::npos)
					// set vertex mode
					type = ShaderType::VERTEX;
				else if (line.find("fragment") != std::string::npos)
					// set fragment mode
					type = ShaderType::FRAGMENT;
			} else { // Use ShaderType to append lines appropriately 
				if (type != ShaderType::NONE)
					ss[(int)type] << line << '\n';
			}
		}
		// Return the strings of the parsed shaders using struct ShaderProgramSource 
		if (debug)
		{
			std::cout << "Parsed shaderfile:\n" << std::endl;
			std::cout << "VERTEX SHADER" << std::endl;
			std::cout << ss[0].str() << std::endl;
			std::cout << "FRAGMENT SHADER" << std::endl;
			std::cout << ss[1].str() << std::endl;
		}
		std::cout << "Returning parsed shader" << std::endl;
		return { ss[0].str(), ss[1].str() };
	}

	unsigned int Shader::compileShader(unsigned int type, const std::string& source)
	{
		unsigned int id = glCreateShader(type);
		// make sure source is available when compiling takes place 
		const char* src = source.c_str();   // &source[0] 
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		// Error handling
		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)_malloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			printf("Failed to compile %s shader!\n%s", type == GL_VERTEX_SHADER ? "vertex" : "fragment", message);
			glDeleteShader(id);
			return 0;
		}
		return id;
	}

}
