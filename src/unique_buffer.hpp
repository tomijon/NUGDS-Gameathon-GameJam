#pragma once

/**
 * @brief Templated UniqueBuffer.
 * 
 * Basically a buffer made using a unique_ptr but allows the size of the buffer
 * to be tracked.
 */
template <typename Type>
class UniqueBuffer {
public:
	/**
	 * Constructor for the UniqueBuffer Class.
	 * @param size The number of elements in the buffer.
	 * @param buffer The buffer to make read-only.
	 */
	UniqueBuffer(size_t size, std::unique_ptr<Type[]> buffer) : m_size(size), m_buffer(std::move(buffer)) {}

	/**
	 * @brief Get a read-only span of the buffer.
	 * 
	 * A span is used to prevent you from accidentally manually deleting
	 * the raw pointer. 
	 */
	inline const std::span<const Type> GetBuffer() const { return { m_buffer.get(), static_cast<size_t>(m_size) }; }

	inline int Size() const { return m_size; }

private:
	int m_size;
	std::unique_ptr<const Type[]> m_buffer;
};

