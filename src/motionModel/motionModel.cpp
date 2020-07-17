#include "motionModel.h"
#include "../linearAlgebra/matrix4.h"
#include "../utils/debugout.h"
#include <Windows.h>


namespace {
  matrix4<float> attitudeMatrix(const vector3<float>& attitude)
  {
    matrix4<float> transform;
    transform.rotate_oy(static_cast<float>(constants::math::deg_to_rad) * attitude.h);
    transform.rotate_ox(-static_cast<float>(constants::math::deg_to_rad) * attitude.p);
    transform.rotate_oz(-static_cast<float>(constants::math::deg_to_rad) * attitude.r);
   
    return transform;
  }
}

void MotionModel::computeMotion()
{
  if (GetAsyncKeyState(VK_UP) & 0x8000)
  {
    vector3<float> forward(0, 0, -1);

    auto _attitudeMatrix = attitudeMatrix(eyeAttitude());
    _attitudeMatrix.transform(forward);

    m_eyePosition += forward;
  }

  if (GetAsyncKeyState(VK_DOWN) & 0x8000)
  {
    vector3<float> backward(0, 0, 1);

    auto _attitudeMatrix = attitudeMatrix(eyeAttitude());
    _attitudeMatrix.transform(backward);

    m_eyePosition += backward;
  }

  if (GetAsyncKeyState(VK_NUMPAD9) & 0x8000)
  {
    vector3<float> up(0, 1, 0);

    auto _attitudeMatrix = attitudeMatrix(eyeAttitude());
    _attitudeMatrix.transform(up);

    m_eyePosition += up;
  }

  if (GetAsyncKeyState(VK_NUMPAD3) & 0x8000)
  {
    vector3<float> down(0, -1, 0);

    auto _attitudeMatrix = attitudeMatrix(eyeAttitude());
    _attitudeMatrix.transform(down);

    m_eyePosition += down;
  }
  
  if (GetAsyncKeyState(VK_LEFT) & 0x8000)
  {
    m_eyeAttitude.h -= m_deltaAtt;
  }
  if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
  {
    m_eyeAttitude.h += m_deltaAtt;
  }
  if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
  {
    m_eyeAttitude.p += m_deltaAtt;
  }
  if (GetAsyncKeyState(VK_NUMPAD8) & 0x8000)
  {
    m_eyeAttitude.p -= m_deltaAtt;
  }
  if (GetAsyncKeyState(VK_NUMPAD6) & 0x8000)
  {
    m_eyeAttitude.r += m_deltaAtt;
  }
  if (GetAsyncKeyState(VK_NUMPAD4) & 0x8000)
  {
    m_eyeAttitude.r -= m_deltaAtt;
  }

}

