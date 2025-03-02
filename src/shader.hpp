#pragma once

#include <filesystem>

#include <glad/glad.h>

class Shader {
public:
	Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
	~Shader();

	/**
	 * @brief Activate the shader program for use in OpenGL draw calls.
	 */
	inline void BindShader() { glUseProgram(m_shaderProgram); }


protected:
	void LoadSource(const std::filesystem::path& sourcePath);
	void CompileShader(const std::filesystem::path& sourcePath);

	void MakeProgram();

private:
	GLuint m_shaderProgram;
};
