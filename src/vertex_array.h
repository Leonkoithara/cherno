#ifndef VERTEX_ARR
#define VERTEX_ARR

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

class VertexArray
{
private:
	unsigned int gl_renderer_id;
public:
	VertexArray();
	~VertexArray();

	void bind();
	void unbind();
	void add_buffer(VertexBuffer *, VertexBufferLayout *);
};

#endif
