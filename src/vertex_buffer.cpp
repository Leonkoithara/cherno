#include "vertex_buffer.h"

#include <GL/glew.h>

VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{
	glGenBuffers(1, &gl_renderer_id);
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &gl_renderer_id); }

void VertexBuffer::bind() { glBindBuffer(GL_ARRAY_BUFFER, gl_renderer_id); }

void VertexBuffer::unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
