#ifndef SCENE_MGNER
#define SCENE_MGNER

class SceneManager
{
public:
	SceneManager() {}
	virtual ~SceneManager() {}

	virtual void update(float deltatime) {}
	virtual void render() {}
	virtual void imgui_update() {}
};

#endif
