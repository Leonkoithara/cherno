#include "renderer.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"
#include "texture.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

void print_all_errors()
{
	while(auto error = glGetError())
	{
		std::cout << "OpenGL error: " << error << std::endl;
	}
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Error loading glew" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	float arr[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, //0
		 0.5f, -0.5f, 1.0f, 0.0f, //1
		 0.5f,  0.5f, 1.0f, 1.0f, //2
		-0.5f,  0.5f, 0.0f, 1.0f  //3
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Renderer renderer;

	VertexArray *va = new VertexArray();
	va->bind();

	VertexBuffer *vb = new VertexBuffer((const void*)arr, 4 * 4 * sizeof(float));

	IndexBuffer *ib = new IndexBuffer(indices, 6);

	VertexBufferLayout *layout = new VertexBufferLayout();
	layout->push_element<float>(2);
	layout->push_element<float>(2);

	Texture *texture = new Texture("res/textures/blue.png");
	texture->bind(0);

	Shader *shader = new Shader("res/shaders/texture.shader");
	shader->bind();

	va->add_buffer(vb, layout);

	shader->set_uniform1i("u_texture", 0);
	
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
		renderer.clear();

		renderer.draw(*va, *ib, *shader);
		
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

	delete vb;
	delete ib;
	delete shader;
	delete va;

    glfwTerminate();
    return 0;
}
