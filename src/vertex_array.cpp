#include "vertex_array.h"

#include <GL/glew.h>

VertexArray::VertexArray() { glGenVertexArrays(1, &gl_renderer_id); }

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &gl_renderer_id); }

void VertexArray::bind() { glBindVertexArray(gl_renderer_id); }

void VertexArray::unbind() { glBindVertexArray(0); }

void VertexArray::add_buffer(VertexBuffer *vb, VertexBufferLayout *layout)
{
	vb->bind();

	auto elements = layout->get_elements();
	unsigned int offset = 0;

	for (int i=0; i<elements.size(); i++)
	{
		auto ele = elements[i];
		glVertexAttribPointer(i, ele.count, ele.type, ele.normalized, layout->get_stride(), (const void*)offset);
		glEnableVertexAttribArray(i);

		offset += ele.count * vertex_buff_elements::get_sizeof(ele.type);
	}
}
