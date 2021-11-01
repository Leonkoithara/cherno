#ifndef SCENE_TMPL
#define SCENE_TMPL

#include "../renderer.h"

#include <functional>
#include <vector>
#include <string>

class SceneTemplate
{
public:
	SceneTemplate() {}
	virtual ~SceneTemplate() {}

	virtual void update(float deltatime) {}
	virtual void render() {}
	virtual void imgui_update() {}

	virtual void mouse_click_event(double x, double y, int button, int action, int mods) {}
};

class SceneMenu : public SceneTemplate
{
private:
	SceneTemplate *current_scene_;
	std::vector<std::pair<std::string, std::function<SceneTemplate*()>>> scenes_;

	Renderer renderer_;
public:
	SceneMenu();
	~SceneMenu();

	template<typename T>
	void register_scene(const std::string &name)
	{
		scenes_.push_back(std::make_pair(name, [](){ return new T(); }));
	}
	SceneTemplate* get_current_scene()
	{
		return current_scene_;
	}
	void set_current_scene(SceneTemplate *scene)
	{
		current_scene_ = scene;
	}

	void render() override;
	void imgui_update() override;
};

#endif
