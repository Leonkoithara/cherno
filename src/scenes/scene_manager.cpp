#include "scene_manager.h"

#include "../vendor/imgui/imgui.h"

SceneMenu::SceneMenu() : current_scene_(this) {}

SceneMenu::~SceneMenu() {}

void SceneMenu::render()
{
	renderer_.clear();
}

void SceneMenu::imgui_update()
{
	for (auto& scene : scenes_)
	{
		if(ImGui::Button(scene.first.c_str()))
		{
			current_scene_ = scene.second();
		}
	}
}
