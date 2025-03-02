#pragma once

#include <string>
#include <filesystem>

#include <glad/glad.h>


/**
 * Shader Stage class for storing an individual shader stage.
 * Compiles and creates a shader of given type. Deletes shader
 * upon going out of scope.
 */
class ShaderStage {
public:
	ShaderStage(const std::filesystem::path& sourcePath, GLenum type);
	~ShaderStage();

	inline GLenum GetShaderType() const { return m_type; }
	inline GLuint GetShader() const { return m_shader; }

protected:
	std::string LoadSource(const std::filesystem::path& sourcePath);
	void CompileShader(const std::filesystem::path& sourcePath);

private:
	GLenum m_type;
	GLuint m_shader;
};


class Shader {
public:
	Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
	~Shader();

	/**
	 * @brief Activate the shader program for use in OpenGL draw calls.
	 * 
	 * Marked as const as it doesn't change object state but it does change
	 * OpenGL state.
	 */
	inline void BindShader() const { glUseProgram(m_shaderProgram); }

protected:
	void MakeProgram();

private:
	GLuint m_shaderProgram;
};
