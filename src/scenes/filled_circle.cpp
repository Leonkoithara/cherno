#include "filled_circle.h"

FilledCircle::FilledCircle()
{
	float positions[] = {
		0.0f, 0.0f,
		640.0f, 0.0f,
		640.0f, 480.0f,
		0.0f, 480.0f
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	va_ = new VertexArray();
	va_->bind();

	vb_ = new VertexBuffer((const void*)positions, 4 * 2 * sizeof(float));

	ib_ = new IndexBuffer(indices, 6);

	VertexBufferLayout layout;
	layout.push_element<float>(2);

	shader_ = new Shader("res/shaders/circle.shader");
	shader_->bind();

	va_->add_buffer(vb_, &layout);

	glm::mat4 ortho_proj = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f);
	shader_->set_uniform_mat4("u_projection", glm::value_ptr(ortho_proj));
	shader_->set_uniform1f("u_radius", 0.1f);
	shader_->set_uniform2f("u_view_dim", 480.0f, 480.0f);
}

FilledCircle::~FilledCircle()
{
	delete va_;
	delete ib_;
	delete shader_;

	delete vb_;
}

void FilledCircle::render()
{
	renderer_.clear();
	renderer_.draw(*va_, *ib_, *shader_);
}
