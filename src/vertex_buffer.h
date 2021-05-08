#ifndef VERTEX_BUFF
#define VERTEX_BUFF

class VertexBuffer
{
private:
	unsigned int gl_renderer_id;
public:
	VertexBuffer(const void*, unsigned int);
	~VertexBuffer();

	void bind();
	void unbind();
};

#endif
