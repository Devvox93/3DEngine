#include <dinput.h>
#include <sstream>
#include "Camera.h"
#include "Logger.h"
#include "Defines.h"

Camera::Camera()
{
	speed = 0.0f;
	xMovement = yMovement = zMovement = 0.0f;
	yawMovement = pitchMovement = rollMovement = 0.0f;
	moveForward = moveBackward = moveLeft = moveRight = moveUp = moveDown = speedUp = false;
};

Camera::~Camera()
{
};

void Camera::update()
{
	moveCamera();

	TripleFloat tf = getPosition();
	tf.x += xMovement;
	tf.y += yMovement;
	tf.z += zMovement;
	setPosition(tf.x, tf.y, tf.z);

	//For Joystick
	TripleFloat tf2 = getRotation();
	tf2.x += yawMovement;
	tf2.y += pitchMovement;
	setRotation(tf2.x, tf2.y, tf2.z);
};

void Camera::moveCamera()
{
	TripleFloat rot = getRotation();
	float yaw = rot.x;
	float pitch = rot.y;

	if (speedUp)
	{
		speed = SPEED * 3;
	}
	else
	{
		speed = SPEED;
	}

	if (moveBackward || moveLeft || moveDown)
	{
		speed = -speed;
	}

	if (moveForward || moveBackward)
	{
		xMovement = speed * sinf(yaw) * cosf(pitch);
		if (sinf(yaw) < 0)
		{
			yMovement = 2 * speed * sinf(yaw) * sinf(pitch);
		}
		else if (sinf(yaw) > 0)
		{
			yMovement = 2 * -speed * sinf(yaw) * sinf(pitch);
		}
		zMovement = speed * cosf(yaw);
	}
	else if (moveLeft || moveRight)
	{
		xMovement = speed * sinf(yaw - 80) * cosf(pitch);
		zMovement = speed * cosf(yaw - 80);
	}
	else if (moveUp || moveDown)
	{
		yMovement = speed;
	}
	else
	{
		xMovement = 0.0f;
		yMovement = 0.0f;
		zMovement = 0.0f;
	}
};

void Camera::setPosition(float _x, float _y, float _z)
{
	x = -_x;
	y = -_y;
	z = -_z;
	D3DXMatrixTranslation(&positionMatrix, x, y, z);
	multiplyMatrices();
};

void Camera::setRotation(float _yaw, float _pitch, float _roll)
{
	yaw = -_yaw;
	pitch = -_pitch;
	roll = -_roll;

	//Custom multiplying of Matrices
	D3DXMATRIXA16 rot1;
	D3DXMatrixRotationYawPitchRoll(&rot1, yaw, 0.0f, 0.0f);
	D3DXMATRIXA16 rot2;
	D3DXMatrixRotationYawPitchRoll(&rot2, 0.0f, pitch, 0.0f);
	D3DXMatrixMultiply(&rotationMatrix, &rot1, &rot2);
};

void Camera::setScale(float _scaleX, float _scaleY, float _scaleZ)
{
	scaleX = -_scaleX;
	scaleY = -_scaleY;
	scaleZ = -_scaleZ;
	D3DXMatrixScaling(&scaleMatrix, scaleX, scaleY, scaleZ);
	multiplyMatrices();
};

void Camera::multiplyMatrices()
{
	finalMatrix = positionMatrix;

	if (yaw != 0 || pitch != 0 || roll != 0) {
		D3DXMatrixMultiply(&finalMatrix, &positionMatrix, &rotationMatrix);
	}

	if (scaleX != 1 || scaleY != 1 || scaleZ != 1) {
		D3DXMatrixMultiply(&finalMatrix, &finalMatrix, &scaleMatrix);
	}
};

TripleFloat Camera::getPosition()
{
	return{ -x, -y, -z };
};

TripleFloat Camera::getRotation()
{
	return{ -yaw, -pitch, -roll };
};

TripleFloat Camera::getScale()
{
	return{ -scaleX, -scaleY, -scaleZ };
};

void Camera::useKeyboardInput(std::array<unsigned char, 256> keyboardState)
{
	if (keyboardState[DIK_UPARROW])
	{
		Logger::getInstance().log(INFO, "Up arrow");
		moveForward = true;
	}
	else
	{
		moveForward = false;
	}

	if (keyboardState[DIK_DOWNARROW])
	{
		Logger::getInstance().log(INFO, "Down arrow");
		moveBackward = true;
	}
	else
	{
		moveBackward = false;
	}

	if (keyboardState[DIK_LEFTARROW])
	{
		Logger::getInstance().log(INFO, "Left arrow");
		moveLeft = true;
	}
	else
	{
		moveLeft = false;
	}

	if (keyboardState[DIK_RIGHTARROW])
	{
		Logger::getInstance().log(INFO, "Right arrow");
		moveRight = true;
	}
	else
	{
		moveRight = false;
	}

	if (keyboardState[DIK_RSHIFT])
	{
		Logger::getInstance().log(INFO, "Right Shift");
		moveUp = true;
	}
	else
	{
		moveUp = false;
	}

	if (keyboardState[DIK_RCONTROL])
	{
		Logger::getInstance().log(INFO, "Right Control");
		moveDown = true;
	}
	else
	{
		moveDown = false;
	}

	if (keyboardState[DIK_NUMPAD0])
	{
		Logger::getInstance().log(INFO, "Numpad 0");
		speedUp = true;
	}
	else
	{
		speedUp = false;
	}
};

void Camera::useMouseInput(DIMOUSESTATE mouseState)
{
	TripleFloat rot = getRotation();
	rot.x += (mouseState.lX / 100.0f);
	rot.y += (mouseState.lY / 100.0f);
	setRotation(rot.x, rot.y, rot.z);
};

void Camera::useJoystickInput(DIJOYSTATE2 joystickState)
{
	if (joystickState.rgdwPOV[0] < 4294967295 )
	{
		float degrees = (float)joystickState.rgdwPOV[0] / 100;
		float radians = RADIANS(degrees);
		xMovement = sin(radians) * 0.1f;
		yMovement = cos(radians) * 0.1f;
	}
	else 
	{
		xMovement = 0.0f;
		yMovement = 0.0f;
	}
	
	long deadzone = 3000;
	long xAxis = joystickState.lX - 32767;
	if (xMovement == 0.0f && ((xAxis + deadzone < -deadzone) || (xAxis - deadzone > deadzone)))
	{
		xMovement = (xAxis / 32767.0f) * 0.1f;
	}

	long yAxis = joystickState.lY - 32767;
	if (yMovement == 0.0f && ((yAxis + deadzone < -deadzone) || (yAxis - deadzone > deadzone)))
	{
		yMovement = (-yAxis / 32767.0f) * 0.1f;
	}

	long yawAxis = joystickState.lRx - 32767;
	if (yawMovement == 0 && ((yawAxis + deadzone < -deadzone) || (yawAxis - deadzone > deadzone)))
	{
		yawMovement = (yawAxis / 32767.0f) * 0.1f;
	}

	long pitchAxis = joystickState.lRy - 32767;
	if (pitchMovement == 0 && ((pitchAxis + deadzone < -deadzone) || (pitchAxis - deadzone > deadzone)))
	{
		pitchMovement = (-pitchAxis / 32767.0f) * 0.1f;
	}
	
	long deadzoneZ = 100;
	long zAxis = joystickState.lZ - 32767;
	if ((zAxis + deadzoneZ < -deadzoneZ) || (zAxis - deadzoneZ > deadzoneZ))
	{
		zMovement = (-zAxis / 32767.0f) * 0.1f;
	}
	else {
		zMovement = 0.0f;
	}
};