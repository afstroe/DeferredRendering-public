#include "opengl_ext.h"
#include "glext.h"
#include "glutils.h"

#include "VertexBufferObject.h"

VertexBufferObject::VertexBufferObject(const std::vector<vector3<float>>& vertices, const std::vector<unsigned int>& indices, const std::vector<vector3<float>>& normals)
{
  auto& vertexBuffer = buffer(Names::Vertex);
  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vector3<float>), vertices.data(), GL_STATIC_DRAW);

  auto& normalBuffer = buffer(Names::Normal);
  glGenBuffers(1, &normalBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
  glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vector3<float>), normals.data(), GL_STATIC_DRAW);


  auto& indexBuffer = buffer(Names::Index);
  glGenBuffers(1, &indexBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  m_numElements = indices.size();
}

std::unique_ptr<VertexBufferObject> VertexBufferObject::createUnique(const std::vector<vector3<float>>& vertices, const std::vector<unsigned int>& indices, const std::vector<vector3<float>>& normals)
{
  std::unique_ptr<VertexBufferObject> vbo(std::make_unique<VertexBufferObject>(vertices, indices, normals));

  return std::move(vbo);
}

VertexBufferObject::~VertexBufferObject()
{
  if (haveOpenGLContext())
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &buffer(Names::Vertex));
    glDeleteBuffers(1, &buffer(Names::Normal));
    glDeleteBuffers(1, &buffer(Names::Index));
  }
}

void VertexBufferObject::draw()
{
  glEnableClientState(GL_VERTEX_ARRAY);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer(Names::Index));

  glBindBuffer(GL_ARRAY_BUFFER, buffer(Names::Vertex));  
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  
  
  glBindBuffer(GL_ARRAY_BUFFER, buffer(Names::Normal));  
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  

  glPolygonMode(m_mode.faceMode, m_mode.fillMode);
  glDrawElements(m_mode.drawMode, static_cast<GLsizei>(m_numElements), GL_UNSIGNED_INT, nullptr);

  glDisableClientState(GL_VERTEX_ARRAY);
}
