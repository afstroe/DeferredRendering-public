#pragma once

#include "../utils/defines.h"
#include "../linearAlgebra/vector3.h"
#include "../linearAlgebra/matrix4.h"
#include "shaders.h"


class SceneObject
{
  DECLARE_PROTECTED_TRIVIAL_ATTRIBUTE(vector3<float>, position);
  DECLARE_PROTECTED_TRIVIAL_ATTRIBUTE(vector3<float>, attitude);
  DECLARE_PROTECTED_TRIVIAL_ATTRIBUTE(vector3<float>, color);
  Shader*& shader()
  {
    return m_shader;
  }
  const Shader* shader() const
  {
    return m_shader;
  }

public:
  matrix4<float> transformMatrix();

  virtual void draw(const matrix4<float>& projectionMatrix, const matrix4<float>& viewMatrix) = 0;

protected:
  Shader* m_shader = nullptr;
};