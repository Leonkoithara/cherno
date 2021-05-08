#ifndef RENDERER
#define RENDERER

#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"

class Renderer
{
public:
	void clear();
	void draw(VertexArray&, IndexBuffer&, Shader&);
};

#endif
