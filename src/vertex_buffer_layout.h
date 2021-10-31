#ifndef VERTEX_BUFF_LAY
#define VERTEX_BUFF_LAY

#include <GL/glew.h>
#include <vector>
#include <iostream>

typedef struct
{
	unsigned int type;
	unsigned int count;
	bool normalized;

	static unsigned int get_sizeof(unsigned int type)
	{
		switch(type)
		{
		case GL_FLOAT :
			return sizeof(GLfloat);
		}

		return 0;
	}
}vertex_buff_elements;

class VertexBufferLayout
{
private:
	std::vector<vertex_buff_elements> elements;
	unsigned int stride;
public:
	VertexBufferLayout()
		:stride(0) {}
	~VertexBufferLayout() {}

	std::vector<vertex_buff_elements> get_elements() { return elements; }
	unsigned int get_stride() { return stride; }

	template <typename T>
	void push_element(unsigned int count);
};
#endif
