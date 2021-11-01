#include "scene_manager.h"

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../vendor/glm/gtc/type_ptr.hpp"

class FilledCircle : public SceneTemplate
{
private:
	VertexArray *va_;
	IndexBuffer *ib_;
	Shader *shader_;
	Renderer renderer_;

	VertexBuffer *vb_;

public:
	FilledCircle();
	~FilledCircle();

	void render() override;
	void mouse_click_event(double x, double y, int button, int action, int mods) override;
};
