#include <fstream>
#include <iostream>

#include "shader.hpp"

ShaderStage::ShaderStage(const std::filesystem::path& sourcePath, GLenum type) : m_type(type) {
	std::string source = LoadSource(sourcePath);
	CompileShader(source);
    m_refTracker = std::make_shared<int>();
}

ShaderStage::~ShaderStage() {
	if (m_refTracker.use_count() > 1) return;
	if (m_shader != 0) glDeleteShader(m_shader);
}

std::string ShaderStage::LoadSource(const std::filesystem::path& sourcePath) {
    std::ifstream file(sourcePath);
    std::string source = "";

    if (file.is_open()) {
        std::stringstream sourceBuffer;
        sourceBuffer << file.rdbuf();
        source = sourceBuffer.str();
        file.close();
        return source;
    }
    else throw std::runtime_error("Shader file not found: " + sourcePath.string());
}

void ShaderStage::CompileShader(std::string source) {
    m_shader = glCreateShader(m_type);

    if (!m_shader) {
        m_shader = -1;
        std::cerr << "Failed to create new shader.\n";
        return;
    }

    const char* sourceAsCharArray = source.c_str();
    glShaderSource(m_shader, 1, &sourceAsCharArray, nullptr);
    glCompileShader(m_shader);

    GLint success = 0;
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);

    if (!success) {
		GLint logLength = 0;
		glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<char> log(logLength);
        glGetShaderInfoLog(m_shader, 1024, NULL, log.data());
        std::cerr << log.data() << std::endl;
    }
}


Shader::Shader(ShaderStage vertex, ShaderStage fragment) {
    std::vector<ShaderStage> stages = { vertex, fragment };
	MakeProgram(std::move(stages));
}

Shader::~Shader() {
    if (m_refTracker.use_count() > 1) return;
    glDeleteProgram(m_program);
}

void Shader::MakeProgram(std::vector<ShaderStage> stages) {
    m_program = glCreateProgram();

    if (!m_program) {
        m_program = -1;
        return;
    }

    for (ShaderStage& stage : stages) {
        glAttachShader(m_program, stage.GetShader());
    }
    glLinkProgram(m_program);


    GLint success = 0;
    glGetProgramiv(m_program, GL_COMPILE_STATUS, &success);

    if (!success) {
		GLint logLength = 0;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<char> log(logLength);
        glGetProgramInfoLog(m_program, 1024, NULL, log.data());
        std::cerr << log.data() << std::endl;
    }
}
