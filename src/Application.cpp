#include "index_buffer.h"
#include "vertex_buffer.h"
#include "vertex_array.h"
#include "vertex_buffer_layout.h"
#include "shader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

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
		-0.5f, -0.5f, //0
 		 0.5f, -0.5f, //1
		 0.5f,  0.5f, //2
		-0.5f,  0.5f, //3
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexArray *va = new VertexArray();
	va->bind();

	VertexBuffer *vb = new VertexBuffer((const void*)arr, 4 * 2 * sizeof(float));

	IndexBuffer *ib = new IndexBuffer(indices, 6);

	
	VertexBufferLayout *layout = new VertexBufferLayout();
	layout->push_element<float>(2);

	Shader *shader = new Shader("res/shaders/basic.shader");
	shader->bind();

	va->add_buffer(vb, layout);

	shader->set_uniform4f("u_color", 0.0f, 0.0f, 1.0f, 1.0f);
	float increment=0.01f, r=0.0f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

		shader->set_uniform4f("u_color", r, 0.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		if (r > 1.0f)
		{
			increment = -0.01f;
		}
		else if(r < 0.0f)
		{
			increment = 0.01f;
		}
		r += increment;
		
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
