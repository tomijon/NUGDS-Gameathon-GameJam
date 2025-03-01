#include "mesh.hpp"


Mesh::~Mesh() {
	if (m_vertexBuffer == -1) glDeleteBuffers(1, &m_vertexBuffer);
	if (m_indexBuffer == -1) glDeleteBuffers(1, &m_indexBuffer);
	if (m_texCoordBuffer == -1) glDeleteBuffers(1, &m_texCoordBuffer);
	if (m_vertexArrayObject == -1) glDeleteVertexArrays(1, &m_vertexArrayObject);
}


void Mesh::InitialiseBufferObjects() {
	glGenVertexArrays(1, &m_vertexArrayObject);

	if (!m_vertexArrayObject) {
		m_vertexArrayObject = -1;
		return;
	}

	CreateBuffer<float>(m_vertexBuffer, m_vertices.GetBuffer());
	glVertexArrayVertexBuffer(
		m_vertexArrayObject,
		static_cast<GLuint>(Buffer::VERTEX),
		m_vertexBuffer,
		0,
		sizeof(GLfloat) * m_vertexSize);
	glVertexArrayAttribFormat(
		m_vertexArrayObject,
		static_cast<GLuint>(Buffer::VERTEX),
		m_vertexSize,
		GL_FLOAT,
		GL_FALSE,
		0);
	glVertexArrayAttribBinding(
		m_vertexArrayObject,
		static_cast<GLuint>(Buffer::VERTEX),
		static_cast<GLuint>(Buffer::VERTEX));
	glEnableVertexAttribArray(static_cast<GLuint>(Buffer::VERTEX));


	//if (m_indices.has_value()) {
	//	CreateBuffer<unsigned int>(m_indexBuffer, m_indices.value().GetBuffer());
	//}

}


template <typename T>
void Mesh::CreateBuffer(GLuint& bufferDest, std::span<const T> data) {
	glGenBuffers(1, &bufferDest);
	if (!bufferDest) {
		bufferDest = -1;
		return;
	}
	glNamedBufferData(bufferDest, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
}
