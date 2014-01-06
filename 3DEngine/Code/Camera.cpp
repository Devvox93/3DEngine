#include <dinput.h>
#include "Camera.h"
#include "Logger.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::update()
{
	TripleFloat tf = getPosition();
	if (right)
	{
		tf.x += 0.1f;
	}
	if (left)
	{
		tf.x -= 0.1f;
	}
	if (up)
	{
		tf.y += 0.1f;
	}
	if (down)
	{
		tf.y -= 0.1f;
	}
	if (forward)
	{
		tf.z += 0.1f;
	}
	if (back)
	{
		tf.z -= 0.1f;
	}
	setPosition(tf.x, tf.y, tf.z);
}

void Camera::setPosition(float _x, float _y, float _z)
{
	x = -_x;
	y = -_y;
	z = -_z;
	D3DXMatrixTranslation(&positionMatrix, x, y, z);
	multiplyMatrices();
}

void Camera::setRotation(float _yaw, float _pitch, float _roll)
{
	yaw = -_yaw;
	pitch = -_pitch;
	roll = -_roll;
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);
	multiplyMatrices();
}

void Camera::setScale(float _scaleX, float _scaleY, float _scaleZ)
{
	scaleX = -_scaleX;
	scaleY = -_scaleY;
	scaleZ = -_scaleZ;
	D3DXMatrixScaling(&scaleMatrix, scaleX, scaleY, scaleZ);
	multiplyMatrices();
}

TripleFloat Camera::getPosition()
{
	return{ -x, -y, -z };
}

TripleFloat Camera::getRotation()
{
	return{ -yaw, -pitch, -roll };
}

TripleFloat Camera::getScale()
{
	return{ -scaleX, -scaleY, -scaleZ };
}

void Camera::useKeyboardInput(std::array<unsigned char, 256> keyboardState)
{
	Logger::getInstance().log(INFO, "Camera input gebruikt");

	if (keyboardState[DIK_UPARROW] & 0x80)
	{
		Logger::getInstance().log(INFO, "Up arrow");
		up = true;

	}
	else
	{
		up = false;
	}
	if (keyboardState[DIK_DOWNARROW] & 0x80)
	{
		Logger::getInstance().log(INFO, "Down arrow");
		down = true;
	}
	else
	{
		down = false;
	}
	if (keyboardState[DIK_LEFTARROW] & 0x80)
	{
		Logger::getInstance().log(INFO, "Left arrow");

		left = true;
	}
	else
	{
		left = false;
	}
	if (keyboardState[DIK_RIGHTARROW] & 0x80)
	{
		Logger::getInstance().log(INFO, "Right arrow");
		right = true;
	}
	else
	{
		right = false;
	}

	if (keyboardState[DIK_INSERT] & 0x80)
	{
		Logger::getInstance().log(INFO, "Insert");
		forward = true;
	}
	else
	{
		forward = false;
	}

	if (keyboardState[DIK_DELETE] & 0x80)
	{
		Logger::getInstance().log(INFO, "Delete");
		back = true;
	}
	else
	{
		back = false;
	}
}
