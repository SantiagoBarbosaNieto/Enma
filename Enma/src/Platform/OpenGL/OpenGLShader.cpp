
#include "empch.h"
#include "Platform/OpenGL/OpenGLShader.h"


#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Enma
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex") return GL_VERTEX_SHADER;
		else if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;
		
		EM_CORE_ASSERT(false, "Unknown shader type '{0}'", type);
		return 0;
	}

	static std::string StringFromShaderType(GLenum type)
	{
		if (type == GL_VERTEX_SHADER) return "vertex";
		else if (type == GL_FRAGMENT_SHADER) return "fragment/pixel";

		EM_CORE_ASSERT(false, "Unknown GLenum type!");
		return "";
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		EM_PROFILE_FUNCTION();

		std::string source = ReadFile(filepath);

		auto shaderSources = OpenGLShader::Preprocess(source);
		Compile(shaderSources);

		//Extract default name from filepath
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;

		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);
	}


	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		:m_Name(name)
	{
		EM_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		EM_PROFILE_FUNCTION();

		glDeleteProgram(m_RendererID);
	}


	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		EM_PROFILE_FUNCTION();

		std::string result;

		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
				in.close();
			}
			else
			{
				EM_CORE_ERROR("Could not read from file '{0}'", filepath);
			}
		}
		else
		{
			EM_CORE_ERROR("Could not open file: '{0}'", filepath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::Preprocess(std::string& source)
	{
		EM_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			EM_CORE_ASSERT(eol != std::string::npos, "Syntax error!");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			EM_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specification!");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			EM_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = source.find(typeToken, nextLinePos);

			shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;

	}

	void OpenGLShader::Compile(const std::unordered_map < GLenum, std::string> shaderSources)
	{

		EM_PROFILE_FUNCTION();

		GLuint program = glCreateProgram();
		EM_CORE_ASSERT(shaderSources.size() <= 10, "Only 10 shaders supported!.. tried to allocate for {0} shaders", shaderSources.size());
		std::array<GLenum, 10> glShaderIDs;

		int glShaderIDIndex = 0;

		for (auto&& [type, src] : shaderSources)
		{
			// Create an empty shader handle
			GLuint shader = glCreateShader(type);

			// Send the shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* sourceCStr = src.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			// Compile the shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				// Use the infoLog as you see fit.
				EM_CORE_ERROR("Shader compilation failure! (Type: '{0}') -->", StringFromShaderType(type));
				EM_CORE_ERROR("--> {0}", infoLog.data());
				EM_CORE_ASSERT(false, "");

				break;
			}
			// Attach shader to program
			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}


		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			for (auto id : glShaderIDs)
			{
				glDetachShader(program, id);
				glDeleteShader(id);
			}


			// Use the infoLog as you see fit.
			EM_CORE_ERROR("Shader linking failure! -->");
			EM_CORE_ERROR("--> {0}", infoLog.data());
			EM_CORE_ASSERT(false, "");

			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		for (int i = 0; i < shaderSources.size(); i++)
		{
			auto shaderID = glShaderIDs[i];
			glDetachShader(program, shaderID);
		}

		m_RendererID = program;
	}

	void OpenGLShader::Bind() const
	{
		EM_PROFILE_FUNCTION();

		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		EM_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string name, int value)
	{
		EM_PROFILE_FUNCTION();

		UploadUniformInt(name, value);
	}


	void OpenGLShader::SetIntArray(const std::string name, int* values, uint32_t count)
	{
		EM_PROFILE_FUNCTION();

		UploadUniformIntArray(name, values, count);
	}

	void OpenGLShader::SetFloat(const std::string name, float value)
	{
		EM_PROFILE_FUNCTION();

		UploadUniformFloat(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string name, const glm::vec3& value)
	{
		EM_PROFILE_FUNCTION();

		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string name, const glm::vec4& value)
	{
		EM_PROFILE_FUNCTION();

		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetMat4(const std::string name, const glm::mat4& value)
	{
		EM_PROFILE_FUNCTION();

		UploadUniformMat4(name, value);
	}


	void OpenGLShader::UploadUniformInt(const std::string name, const int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformIntArray(const std::string name, int* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::UploadUniformFloat(const std::string name, const float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string name, const glm::vec2& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2fv(location, 1, glm::value_ptr(values));
	}
	 
	void OpenGLShader::UploadUniformFloat3(const std::string name, const glm::vec3& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3fv(location, 1, glm::value_ptr(values));
	}

	void OpenGLShader::UploadUniformFloat4(const std::string name, const glm::vec4& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4fv(location, 1, glm::value_ptr(values));
	}

	void OpenGLShader::UploadUniformMat3(const std::string name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));

	}

}

