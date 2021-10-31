#include "textured_imgui.h"

#include "../texture.h"

TexturedImgui::TexturedImgui() :
	offsets_{0.0f, 0.0f, 0.0f}
{
	float vbo[] = {
		100.0f, 100.0f, 0.0f, 0.0f,
		300.0f, 100.0f, 1.0f, 0.0f,
		300.0f,  300.0f, 1.0f, 1.0f,
		100.0f,  300.0f, 0.0f, 1.0f
	};
	unsigned int ibo[] = {
		0, 1, 2,
		2, 3, 0
	};
	va_ = new VertexArray();
	va_->bind();

	VertexBuffer *vb = new VertexBuffer((const void*)vbo, 4 * 4 * sizeof(float));

	ib_ = new IndexBuffer(ibo, 6);

	VertexBufferLayout *layout = new VertexBufferLayout();
	layout->push_element<float>(2);
	layout->push_element<float>(2);

	Texture *texture = new Texture("res/textures/blue.png");
	texture->bind(0);

	shader_ = new Shader("res/shaders/texture.shader");
	shader_->bind();

	va_->add_buffer(vb, layout);

	shader_->set_uniform1i("u_texture", 0);
	shader_->set_uniform4f("u_color", 1.0f, 1.0f, 1.0f, 1.0f);

	col_mul_ = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

	projection_ = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f);
	shader_->set_uniform_mat4("u_projection", glm::value_ptr(projection_));
	model_ = glm::mat4(1.0f);
	shader_->set_uniform_mat4("u_model", glm::value_ptr(model_));
}

TexturedImgui::~TexturedImgui() {}

void TexturedImgui::update(float deltatime)
{
	model_ = glm::translate(model_, glm::vec3(offsets_[0], offsets_[1], offsets_[2]));
	shader_->set_uniform4f("u_color", col_mul_.x, col_mul_.y, col_mul_.z, col_mul_.w);
	shader_->set_uniform_mat4("u_model", glm::value_ptr(model_));
}

void TexturedImgui::render()
{
	renderer_.clear();
	renderer_.draw(*va_, *ib_, *shader_);
}

void TexturedImgui::imgui_update()
{
	ImGui::ColorEdit4("color_multiplier", (float*)&col_mul_);
	ImGui::SliderFloat3("xyz offset", offsets_, -1.0f, 1.0f);
}
