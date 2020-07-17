#include "cube.h"

namespace {
	static auto vertices = {
		// front
		vector3<float>(-1.0f, -1.0f,  1.0f),
		vector3<float>(1.0f, -1.0f,  1.0f),
		vector3<float>(1.0f,  1.0f,  1.0f),
		vector3<float>(-1.0f,  1.0f,  1.0f),
		// back
		vector3<float>(-1.0f, -1.0f, -1.0f),
		vector3<float>(1.0f, -1.0f, -1.0f),
		vector3<float>(1.0f,  1.0f, -1.0f),
		vector3<float>(-1.0f,  1.0f, -1.0f)
	};
	static std::vector<unsigned int> indices =
	{
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	// !!! these normals are rubbish they should be averaged per vertex 
	static auto normals = {
		// front
		vector3<float>(0.0f, 0.0f,  1.0f),
		vector3<float>(0.0f, 0.0f,  1.0f),
		vector3<float>(0.0f, 0.0f,  1.0f),		
		vector3<float>(0.0f, 0.0f,  1.0f),
		
		// back
		vector3<float>(0.0f, 0.0f, -1.0f),
		vector3<float>(0.0f, 0.0f, -1.0f),
		vector3<float>(0.0f,  0.0f, -1.0f),
		vector3<float>(0.0f,  0.0f, -1.0f)
	};
}

CubeVBO::CubeVBO():
	VertexBufferObject(vertices, indices, normals)
{	
	mode() = { GL_TRIANGLES, GL_FILL, GL_FRONT };

	//m_shader = Shader::fromFiles("res/shaders/simple.vert", "res/shaders/simple.frag");
}

std::unique_ptr<CubeVBO> CubeVBO::createUnique(Shader* shader)
{
	auto cubeVBO = std::make_unique<CubeVBO>();

	cubeVBO->shader() = shader;

	return cubeVBO;
}

void CubeVBO::draw(const matrix4<float>& projectionMatrix, const matrix4<float>& viewMatrix)
{
	auto _transformMatrix = transformMatrix();
	auto modelViewMatrix = _transformMatrix * viewMatrix;
	m_shader->set("projectionMatrix", glUniformMatrix4fv, 1, static_cast<GLboolean>(GL_FALSE), projectionMatrix.get_openglmatrix());
	m_shader->set("modelViewMatrix", glUniformMatrix4fv, 1, static_cast<GLboolean>(GL_FALSE), modelViewMatrix.get_openglmatrix());
	m_shader->set("modelMatrix", glUniformMatrix4fv, 1, static_cast<GLboolean>(GL_FALSE), _transformMatrix.get_openglmatrix());
	m_shader->set("color", glUniform3fv, 1, static_cast<float*>(m_color));

	// draw the VBO
	VertexBufferObject::draw();
}
