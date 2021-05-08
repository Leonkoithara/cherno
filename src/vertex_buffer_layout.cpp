#include "vertex_buffer_layout.h"

template <typename T>
void VertexBufferLayout::push_element(unsigned int count)
{
	std::cout << "Don't do that my friend";
}

template<>
void VertexBufferLayout::push_element<float>(unsigned int count)
{
	elements.push_back({GL_FLOAT, count, GL_FALSE});
	stride += vertex_buff_elements::get_sizeof(GL_FLOAT) * count;
}
