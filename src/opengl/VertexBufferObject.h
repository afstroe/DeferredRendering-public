#pragma once

#include <vector>
#include <memory>
#include <gl/GL.h>

#include "../linearAlgebra/vector3.h"
#include "../utils/defines.h"

class VertexBufferObject
{
public:
  enum class Names
  {
    Vertex = 0,
    Normal,

    Index,
    Count
  };

  struct Mode
  {
    GLuint drawMode = GL_TRIANGLES;
    GLuint fillMode = GL_FILL;
    GLuint faceMode = GL_FRONT;
  }; 

public:
  VertexBufferObject() = default;

  VertexBufferObject(const std::vector<vector3<float>>& vertices, const std::vector<unsigned int>& indices, const std::vector<vector3<float>>& normals);

  static std::unique_ptr<VertexBufferObject> createUnique(const std::vector<vector3<float>>& vertices, const std::vector<unsigned int>& indices, const std::vector<vector3<float>>& normals);

  ~VertexBufferObject();


  DECLARE_PROTECTED_TRIVIAL_ATTRIBUTE(Mode, mode);

public:
  // don't use Names::Count; i don't want to place a guard here;
  GLuint buffer(Names name) const
  {
    return m_buffer[static_cast<size_t>(name)];
  }

  void draw();
protected:

  // not for public use
  GLuint& buffer(Names name)
  {
    return m_buffer[static_cast<size_t>(name)];
  }

  GLuint m_buffer[static_cast<size_t>(Names::Count)];

  size_t m_numElements;
};

using VertexBufferObjectPtr = std::unique_ptr<VertexBufferObject>;