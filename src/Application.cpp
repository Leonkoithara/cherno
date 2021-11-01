#include "scenes/scene_manager.h"
#include "scenes/textured_imgui.h"
#include "scenes/filled_circle.h"

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <functional>
#include <iostream>

void print_all_errors()
{
	while(auto error = glGetError())
	{
		std::cout << "OpenGL error: " << error << std::endl;
	}
}

double mousex, mousey;
SceneTemplate *scene;

static void cursor_position_callback(GLFWwindow *, double, double);
static void mouse_button_callback(GLFWwindow *, int, int, int);

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

	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);;

	SceneMenu scenemenu;

	scenemenu.register_scene<TexturedImgui>("Textured Imgui");
	scenemenu.register_scene<FilledCircle>("Filled Circle");

    while (!glfwWindowShouldClose(window))
    {
		scene = scenemenu.get_current_scene();
		scene->update(0.0f);
		scene->render();
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Hello User");

		if(scene != &scenemenu && ImGui::Button("Back"))
		{
			delete scene;
			scenemenu.set_current_scene(&scenemenu);
			scene = scenemenu.get_current_scene();
		}
		scene->imgui_update();
		
		ImGui::End();

		ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

	std::cout << "Exiting" << std::endl;

	if (scene != &scenemenu)
	    delete scene;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}

static void cursor_position_callback(GLFWwindow *window, double x, double y)
{
	mousex = x;
	mousey = y;
}

static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	if (scene != 0)
	{
		scene->mouse_click_event(mousex, mousey, button, action, mods);
	}
}
