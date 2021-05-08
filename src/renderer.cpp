#include "renderer.h"

#include <GL/glew.h>

void Renderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw(VertexArray &va, IndexBuffer &ib, Shader &shader)
{
	va.bind();
	ib.bind();
	shader.bind();

	glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, NULL);
}
