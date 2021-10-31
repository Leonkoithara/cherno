#include "scene_manager.h"
#include "../vertex_buffer.h"
#include "../index_buffer.h"
#include "../shader.h"
#include "../texture.h"
#include "../vendor/imgui/imgui.h"
#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../vendor/glm/gtc/type_ptr.hpp"

#include <iostream>

class TexturedImgui : public SceneTemplate
{
private:
	VertexArray *va_;
	IndexBuffer *ib_;
	Shader *shader_;
	Renderer renderer_;
	
	ImVec4 col_mul_;
	float offsets_[3];
	glm::mat4 model_;
	glm::mat4 projection_;

	Texture *texture_;
	VertexBuffer *vb_;
	
public:
	TexturedImgui();
	~TexturedImgui();

	void update(float deltatime) override;
	void render() override;
	void imgui_update() override;
};
