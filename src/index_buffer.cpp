#include "index_buffer.h"

#include <GL/glew.h>

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : count_(count)
{
	glGenBuffers(1, &gl_renderer_id_);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &gl_renderer_id_); }

void IndexBuffer::bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_renderer_id_); }

void IndexBuffer::unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
