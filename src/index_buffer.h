#ifndef INDEX_BUFF
#define INDEX_BUFF

class IndexBuffer
{
private:
	unsigned int gl_renderer_id_;
	unsigned int count_;
public:
	IndexBuffer(const unsigned int*, unsigned int);
	~IndexBuffer();

	unsigned int get_count() { return count_; }

	void bind();
	void unbind();
};

#endif
