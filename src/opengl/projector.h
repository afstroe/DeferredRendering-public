#pragma once

#include "sceneobject.h"
#include <Windows.h>
#include <gl/GL.h>

class Projector : public SceneObject
{
public:
  void draw(const matrix4<float>& projectionMatrix, const matrix4<float>& viewMatrix) override;

  void createTexture();

  const GLuint& texName() const 
  {
    return m_texName;
  }
protected:

  GLuint m_texName = 0;
};