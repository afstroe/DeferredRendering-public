#pragma once

#include "../utils/defines.h"
#include "../linearAlgebra/vector3.h"
#include "../linearAlgebra/matrix4.h"

class Camera
{
public:
  enum class Mode
  {
    ORTHO = 0,
    PERSPECTIVE
  };

  struct Perspective
  {
    float verticalAngle = 45.0f;    // degrees
    float aspectRatio = 4.0f / 3.0f;
    float nearPlane = 0.1f;          // meters
    float farPlane = 1000;          // meters
  };

  struct Ortho
  {
    float left = -0.5;
    float right = 0.5;
    float bottom = -0.5;
    float top = 0.5;
    float zNear = -1000;
    float zFar = 1000;
  };

  DECLARE_PROTECTED_TRIVIAL_ATTRIBUTE(vector3<float>, position);
  DECLARE_PROTECTED_TRIVIAL_ATTRIBUTE(vector3<float>, attitude);
  DECLARE_PROTECTED_TRIVIAL_ATTRIBUTE(Mode, mode);
  DECLARE_PROTECTED_TRIVIAL_ATTRIBUTE(Perspective, perspectiveData);
  DECLARE_PROTECTED_TRIVIAL_ATTRIBUTE(Ortho, parallelData);

  inline const float& heading() const
  {
    return m_attitude.h;
  }
  inline float& heading()
  {
    return m_attitude.h;
  }

  inline const float& pitch() const
  {
    return m_attitude.p;
  }
  inline float& pitch()
  {
    return m_attitude.p;
  }

  inline const float& roll() const
  {
    return m_attitude.r;
  }
  inline float& roll()
  {
    return m_attitude.r;
  }

  inline Camera() :
    m_mode(Mode::ORTHO)
  {

  }

  const matrix4<float> transform() const;
  const matrix4<float> projectionMatrix() const;
  const matrix4<float> viewMatrix() const;
  const matrix4<float> attitudeMatrix() const;
};