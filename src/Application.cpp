#include "renderer.h"
#include "vendor/imgui/imgui.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"
#include "texture.h"

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

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
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

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
	shader->set_uniform4f("u_color", 1.0f, 1.0f, 1.0f, 1.0f);

	ImVec4 col_mul(1.0f, 1.0f, 1.0f, 1.0f);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

		shader->set_uniform4f("u_color", col_mul.x, col_mul.y, col_mul.z, col_mul.w);
        /* Render here */
		renderer.clear();

		renderer.draw(*va, *ib, *shader);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Hello Imgui");
		ImGui::ColorEdit4("color_multiplier", (float*)&col_mul);
		ImGui::End();

		ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

	delete vb;
	delete ib;
	delete shader;
	delete va;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
