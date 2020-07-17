#include "plane.h"

namespace {
	static auto vertices = {
		vector3<float>( 100.0f, 0.0f,  100.0f),
		vector3<float>( 100.0f, 0.0f, -100.0f),
		vector3<float>(-100.0f, 0.0f, -100.0f),
		vector3<float>(-100.0f, 0.0f,  100.0f),
	};
	static std::vector<unsigned int> indices = {0, 1, 2, 3};
	static auto normals = {
		vector3<float>(0.0, 1.0f, 0.0f),
		vector3<float>(0.0, 1.0f, 0.0f),
		vector3<float>(0.0, 1.0f, 0.0f),
		vector3<float>(0.0, 1.0f, 0.0f),
	};
}

PlaneVBO::PlaneVBO():
	VertexBufferObject(vertices, indices, normals)
{
	mode() = { GL_QUADS, GL_FILL, GL_FRONT_AND_BACK };	

	//m_shader = Shader::fromFiles("res/shaders/simple.vert", "res/shaders/simple.frag");
}

std::unique_ptr<PlaneVBO> PlaneVBO::createUnique(Shader* shader)
{
	auto planeVBO = std::make_unique<PlaneVBO>();

	planeVBO->shader() = shader;

	return planeVBO;
}


void PlaneVBO::draw(const matrix4<float>& projectionMatrix, const matrix4<float>& viewMatrix)
{	
	auto _transformMatrix = transformMatrix();
	auto modelViewMatrix =  _transformMatrix * viewMatrix;
	m_shader->set("projectionMatrix", glUniformMatrix4fv, 1, static_cast<GLboolean>(GL_FALSE), projectionMatrix.get_openglmatrix());
	m_shader->set("modelViewMatrix", glUniformMatrix4fv, 1, static_cast<GLboolean>(GL_FALSE), modelViewMatrix.get_openglmatrix());
	m_shader->set("modelMatrix", glUniformMatrix4fv, 1, static_cast<GLboolean>(GL_FALSE), _transformMatrix.get_openglmatrix());
	m_shader->set("color", glUniform3fv, 1, static_cast<float*>(m_color));

	// draw the VBO
	VertexBufferObject::draw();	
}