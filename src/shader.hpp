#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include <glad/glad.h>


/**
 * Shader Stage class for storing an individual shader stage.
 * Compiles and creates a shader of given type. Deletes shader
 * upon going out of scope (and all references are gone).
 */
class ShaderStage {
public:
	ShaderStage(const std::filesystem::path& sourcePath, GLenum type);
	~ShaderStage();

	inline GLenum GetShaderType() const { return m_type; }
	inline GLuint GetShader() const { return m_shader; }

protected:
	std::string LoadSource(const std::filesystem::path& sourcePath);
	void CompileShader(const std::string source);

private:
	std::shared_ptr<int> m_refTracker = nullptr; // Tracking how many instances of this shader object there are.
	GLenum m_type = -1;
	GLuint m_shader = -1;
};


class Shader {
public:
	Shader(ShaderStage vertex, ShaderStage fragment);
	~Shader();

	/**
	 * @brief Activate the shader program for use in OpenGL draw calls.
	 * 
	 * Marked as const as it doesn't change object state but it does change
	 * OpenGL state.
	 */
	inline void BindShader() const { glUseProgram(m_program); }

	GLuint GetProgramID() const { return m_program; }

protected:
	void MakeProgram(std::vector<ShaderStage> stages);

private:
	std::shared_ptr<int> m_refTracker = nullptr; // Tracking how many program instances there are.
	GLuint m_program;
};
