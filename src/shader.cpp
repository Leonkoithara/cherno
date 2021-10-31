#include "shader.h"

#include <GL/glew.h>

#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string &filepath) : gl_renderer_id(0)
{
	shader_src prog_src = parse_shader(filepath);

	gl_renderer_id = create_shader(prog_src.vertex, prog_src.fragment);
}

Shader::~Shader() { glDeleteProgram(gl_renderer_id); }

void Shader::bind() { glUseProgram(gl_renderer_id); }

void Shader::unbind() { glUseProgram(0); }

shader_src Shader::parse_shader(const std::string &filepath)
{
	enum type
	{
		NONE = -1,
		VERTEX,
		FRAGMENT
	};

	enum type shader_type = NONE;

	std::string line;
	std::fstream filestream(filepath);
	std::stringstream ss[2];

	while( getline(filestream, line) )
	{
		if( line.find("#shader") != std::string::npos )
		{
			if( line.find("vertex") != std::string::npos )
			{
				shader_type = VERTEX;
			}
			else if( line.find("fragment") != std::string::npos )
			{
				shader_type = FRAGMENT;
			}
		}
		else
		{
			ss[shader_type] << line << "\n";
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::compile_shader(unsigned int type, std::string &shader_src)
{
	unsigned int shader = glCreateShader(type);
	const char *src = shader_src.c_str();
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << (type==GL_VERTEX_SHADER? "VERTEX": "FRAGMENT") << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader;
}

unsigned int Shader::create_shader(std::string &vertex_shader, std::string &fragment_shader)
{
	unsigned int program = glCreateProgram();

	unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
	unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);

	int success;
	char infoLog[512];	
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
		
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::set_uniform1i(const std::string &uname, int value)
{
	int location = get_uniform_loc(uname);
	glUniform1i(location, value);
}

void Shader::set_uniform1f(const std::string &uname, float v0)
{
	int location = get_uniform_loc(uname);
	glUniform1f(location, v0);
}

void Shader::set_uniform2f(const std::string &uname, float v0, float v1)
{
	int location = get_uniform_loc(uname);
	glUniform2f(location, v0, v1);
}

void Shader::set_uniform4f(const std::string &uname, float v0, float v1, float v2, float v3)
{
	int location = get_uniform_loc(uname);
	glUniform4f(location, v0, v1, v2, v3);
}

void Shader::set_uniform_mat4(const std::string &uname, const float *data)
{
	int location = get_uniform_loc(uname);
	glUniformMatrix4fv(location, 1, GL_FALSE, data);
}

int Shader::get_uniform_loc(const std::string &uname)
{
	if (uniform_map.find(uname) != uniform_map.end())
	    return uniform_map[uname];

	int location = glGetUniformLocation(gl_renderer_id, uname.c_str());
	uniform_map[uname] = location;

	return location;
}
