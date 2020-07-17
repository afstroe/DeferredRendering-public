#pragma once

#include "../utils/defines.h"
#include "../linearAlgebra/vector3.h"
class MotionModel
{
  DECLARE_PROTECTED_TRIVIAL_ATTRIBUTE(vector3<float>, eyePosition);
  DECLARE_PROTECTED_TRIVIAL_ATTRIBUTE(vector3<float>, eyeAttitude);
  DECLARE_PROTECTED_TRIVIAL_ATTRIBUTE(float, deltaPos);
  DECLARE_PROTECTED_TRIVIAL_ATTRIBUTE(float, deltaAtt);

  void computeMotion();
};