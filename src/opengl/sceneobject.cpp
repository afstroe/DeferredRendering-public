#include "sceneobject.h"

matrix4<float> SceneObject::transformMatrix()
{
  matrix4<float> transform;
  transform.rotate_oy(static_cast<float>(constants::math::deg_to_rad) * m_attitude.h);
  transform.rotate_ox(-static_cast<float>(constants::math::deg_to_rad) * m_attitude.p);
  transform.rotate_oz(-static_cast<float>(constants::math::deg_to_rad) * m_attitude.r);

  transform.translate(m_position);

  return transform;
}