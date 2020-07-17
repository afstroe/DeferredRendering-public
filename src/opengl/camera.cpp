#include "camera.h"
#include "../utils/constants.h"

const matrix4<float> Camera::transform() const
{
  return matrix4<float>();
}

const matrix4<float> Camera::projectionMatrix() const
{
	matrix4<float> projectionMatrix;
	switch (m_mode)
	{
	case Mode::PERSPECTIVE:
		projectionMatrix = matrix4<float>::perspective(m_perspectiveData.verticalAngle, m_perspectiveData.aspectRatio, m_perspectiveData.nearPlane, m_perspectiveData.farPlane);
		break;

	case Mode::ORTHO:
	default:
		projectionMatrix = matrix4<float>::ortho(m_parallelData.left, m_parallelData.right, m_parallelData.bottom, m_parallelData.top, m_parallelData.zNear, m_parallelData.zFar);
	}
	return projectionMatrix;
}

const matrix4<float> Camera::viewMatrix() const
{
	auto _viewMatrix = attitudeMatrix();
	
	_viewMatrix.translate(-m_position);

	return _viewMatrix;  
}

const matrix4<float> Camera::attitudeMatrix() const
{
	matrix4<float> transform;
	transform.rotate_oy(static_cast<float>(constants::math::deg_to_rad) * heading()); 
	transform.rotate_ox(-static_cast<float>(constants::math::deg_to_rad) * pitch()); 
	transform.rotate_oz(-static_cast<float>(constants::math::deg_to_rad) * roll());
	
	return transform;
}
