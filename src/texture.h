#ifndef TEXTURE
#define TEXTURE

#include <string>

class Texture
{
private:
	unsigned int gl_renderer_id_;
	std::string filepath_;
	unsigned char *local_buffer_;
	int width_, height_, bpp_;

public:
	Texture(const std::string&);
	~Texture();

	inline int get_width() { return width_; }
	inline int get_height() { return height_; }

	void bind(unsigned int);
	void unbind();
};

#endif
