#pragma once

#include <memory>
#include <span>
#include <optional>

#include <glad/glad.h>

#include "unique_buffer.hpp"


/**
 * Enums of the different buffer types.
 * 
 * The value of the enum represents the vertex attribute number.
 */
enum class Buffer : GLuint {
	VERTEX = 0,
	INDEX = 1,
	TEX_COORDS = 2
};


class Mesh {
public:
	Mesh(UniqueBuffer<float> vertices) : m_vertices(std::move(vertices)) {}
	~Mesh();

	inline void SetTextureCoordinates(UniqueBuffer<float> texCoords) {
		m_texCoords.emplace(std::move(texCoords));
	}

	inline void SetIndices(UniqueBuffer<unsigned int> indices) {
		m_indices.emplace(std::move(indices));
	}

	inline void SetVertexSize(unsigned int size) { m_vertexSize = size; }


	/**
	 * @brief Initialise OpenGL buffers.
	 * 
	 * Creates and populates the vertex array object and buffers for every
	 * initialised array. If a buffer has not been set, a buffer will not be
	 * created.
	 */
	void InitialiseBufferObjects();

protected:
	template<typename T>
	void CreateBuffer(GLuint& bufferDest, std::span<const T> data);

private:
	GLuint m_vertexArrayObject = -1;

	GLuint m_vertexBuffer = -1;
	GLuint m_indexBuffer = -1;
	GLuint m_texCoordBuffer = -1;

	UniqueBuffer<float> m_vertices;
	std::optional<UniqueBuffer<unsigned int>> m_indices;
	std::optional<UniqueBuffer<float>> m_texCoords;

	unsigned int m_vertexSize = 4;
};
