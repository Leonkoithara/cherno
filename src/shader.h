#ifndef SHADER
#define SHADER

#include <string>
#include <unordered_map>

typedef struct
{
	std::string vertex;
	std::string fragment;
} shader_src;

class Shader
{
private:
	unsigned int gl_renderer_id;
	std::unordered_map<std::string, int> uniform_map;

	shader_src parse_shader(const std::string&);
	unsigned int compile_shader(unsigned int, std::string&);
	unsigned int create_shader(std::string&, std::string&);
public:
	Shader(const std::string &filename);
	~Shader();

	void bind();
	void unbind();

	void set_uniform1i(const std::string&, int);
	void set_uniform1f(const std::string&, float);
	void set_uniform2f(const std::string&, float, float);
	void set_uniform4f(const std::string&, float, float, float, float);
	void set_uniform_mat4(const std::string&, const float*);
	
	int get_uniform_loc(const std::string&);
};

#endif
