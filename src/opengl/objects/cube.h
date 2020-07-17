#pragma once

#include <Windows.h>
#include "../VertexBufferObject.h"
#include "../sceneobject.h"

class CubeVBO : public VertexBufferObject, public SceneObject
{
public:
  CubeVBO();

  static std::unique_ptr<CubeVBO> createUnique(Shader* shader);

  void draw(const matrix4<float>& projectionMatrix, const matrix4<float>& viewMatrix) override;
};