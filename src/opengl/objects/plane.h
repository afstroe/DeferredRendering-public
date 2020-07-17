#pragma once

#include <Windows.h>
#include "../VertexBufferObject.h"
#include "../sceneobject.h"

class PlaneVBO : public VertexBufferObject, public SceneObject
{
public:
  PlaneVBO();

  static std::unique_ptr<PlaneVBO> createUnique(Shader* shader);

  void draw(const matrix4<float>& projectionMatrix, const matrix4<float>& viewMatrix) override;
};