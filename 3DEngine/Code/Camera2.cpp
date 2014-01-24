#include "Camera2.h"
#include "Logger.h"
#include "Defines.h"
#include <sstream>

Camera2::Camera2()
{
	spinAroundCurrentAngle = spinAroundX = spinAroundZ = spinAroundRadius = 0.0f;
	spinning = false;
	xMovement = yMovement = zMovement = yawMovement = pitchMovement = rollMovement = movementSpeed = 0.0f;
	setPosition(0.0f, 100.0f, 0.0f);
	setRotation(0.0f, 0.0f, 0.0f);
};

Camera2::~Camera2()
{

};

void Camera2::update()
{
	if (!spinning)
	{
		TripleFloat tf = getPosition();
		tf.x += xMovement;
		tf.y += yMovement;
		tf.z += zMovement;
		setPosition(tf.x, tf.y, tf.z);

		TripleFloat tfr = getRotation();
		tfr.x += yawMovement;
		tfr.y += pitchMovement;
		tfr.z += rollMovement;
		setRotation(tfr.x, tfr.y, tfr.z);
	}
	else
	{
		TripleFloat tf = getPosition();
		tf.x = spinAroundX + (float)(sin(RADIANS(spinAroundCurrentAngle)) * spinAroundRadius);
		tf.z = spinAroundZ + (float)-(cos(RADIANS(spinAroundCurrentAngle)) * spinAroundRadius);
		setPosition(tf.x, tf.y, tf.z);

		TripleFloat tfr = getRotation();
		tfr.x = (float)-RADIANS(spinAroundCurrentAngle);
		setRotation(tfr.x, tfr.y, tfr.z);
		spinAroundCurrentAngle++;
		if (spinAroundCurrentAngle == 360.0f)
		{
			spinAroundCurrentAngle = 0.0f;
		}
	}
};

void Camera2::setPosition(float _x, float _y, float _z)
{
	x = -_x;
	y = -_y;
	z = -_z;
	D3DXMatrixTranslation(&positionMatrix, x, y, z);
	multiplyMatrices();
};

void Camera2::setRotation(float _yaw, float _pitch, float _roll)
{
	if (_pitch > RADIANS(90.0f))
	{
		_pitch = RADIANS(90.0f);
	}
	else if (_pitch < RADIANS(-90.0f))
	{
		_pitch = RADIANS(-90.0f);
	}

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

void Camera2::setScale(float _scaleX, float _scaleY, float _scaleZ)
{
	scaleX = -_scaleX;
	scaleY = -_scaleY;
	scaleZ = -_scaleZ;
	D3DXMatrixScaling(&scaleMatrix, scaleX, scaleY, scaleZ);
	multiplyMatrices();
};

void Camera2::multiplyMatrices()
{
	finalMatrix = positionMatrix;

	if (yaw != 0 || pitch != 0 || roll != 0) {
		D3DXMatrixMultiply(&finalMatrix, &positionMatrix, &rotationMatrix);
	}

	if (scaleX != 1 || scaleY != 1 || scaleZ != 1) {
		D3DXMatrixMultiply(&finalMatrix, &finalMatrix, &scaleMatrix);
	}
};

TripleFloat Camera2::getPosition()
{
	return{ -x, -y, -z };
};

TripleFloat Camera2::getRotation()
{
	return{ -yaw, -pitch, -roll };
};

TripleFloat Camera2::getScale()
{
	return{ -scaleX, -scaleY, -scaleZ };
};

void Camera2::useKeyboardInput(std::array<unsigned char, 256> keyboardState)
{
	if (keyboardState[DIK_RETURN] & 0x80 || keyboardState[DIK_1] & 0x80)
	{
		spinning = true;
		spinAroundX = 0.0f;
		spinAroundZ = 0.0f;
		spinAroundRadius = 100.0f;
		return;
	}
	else 
	{
		spinning = false;
	}
	int iz = 0;
	int ix = 0;

	if (keyboardState[DIK_UPARROW] & 0x80 || keyboardState[DIK_W] & 0x80)
	{
		iz += 1;
	}
	if (keyboardState[DIK_DOWNARROW] & 0x80 || keyboardState[DIK_S] & 0x80)
	{
		iz -= 1;
	}
	if (keyboardState[DIK_LEFTARROW] & 0x80 || keyboardState[DIK_A] & 0x80)
	{
		ix -= 1;
	}
	if (keyboardState[DIK_RIGHTARROW] & 0x80 || keyboardState[DIK_D] & 0x80)
	{
		ix += 1;
	}

	int upSpeed = 0;
	if (keyboardState[DIK_RSHIFT] & 0x80 || keyboardState[DIK_E] & 0x80)
	{
		upSpeed += 1;
	}
	if (keyboardState[DIK_RCONTROL] & 0x80 || keyboardState[DIK_Q] & 0x80)
	{
		upSpeed -= 1;
	}

	if (upSpeed == 1)
	{
		yMovement = 1.0f;
	}
	else if (upSpeed == -1)
	{
		yMovement = -1.0f;
	}
	else 
	{
		yMovement = 0.0f;
	}

	if (keyboardState[DIK_NUMPAD0] & 0x80 || keyboardState[DIK_TAB] & 0x80)
	{
		movementSpeed = 2.0f;
		yMovement *= 2.0f;
	}
	else
	{
		movementSpeed = 1.0f;
	}

	if (ix == 0 && iz == 0)
	{
		movementSpeed = 0.0f;
		xMovement = 0.0f;
		zMovement = 0.0f;
		return;
	}
	
	movementAngle = (float)atan2f((float)ix, (float)iz);
	changeMovement();
};

void Camera2::useMouseInput(DIMOUSESTATE mouseState)
{
	TripleFloat rot = getRotation();

	rot.x += (mouseState.lX / 100.0f);
	rot.y += (mouseState.lY / 100.0f);

	setRotation(rot.x, rot.y, rot.z);
	changeMovement();
};

void Camera2::useJoystickInput(DIJOYSTATE2 joystickState)
{
	if (joystickState.rgdwPOV[0] < 4294967295)
	{
		float degrees = (float)joystickState.rgdwPOV[0] / 100;
		movementAngle = (float)RADIANS(degrees);
		movementSpeed = 1.0f;
		changeMovement();
		return;
	}
	else
	{
		movementSpeed = 0.0f;
		changeMovement();
	}

	long deadzone = 3000;
	float ix = 0.0f;
	float iz = 0.0f;
	long xAxis = joystickState.lX - 32767;
	if ((xAxis + deadzone < -deadzone) || (xAxis - deadzone > deadzone))
	{
		ix = xAxis / 32767.0f;
	}

	long yAxis = joystickState.lY - 32767;
	if ((yAxis + deadzone < -deadzone) || (yAxis - deadzone > deadzone))
	{
		iz = -yAxis / 32767.0f;
	}
	
	long yawAxis = joystickState.lRx - 32767;
	if ((yawAxis + deadzone < -deadzone) || (yawAxis - deadzone > deadzone))
	{
		yawMovement = (yawAxis / 32767.0f) * 0.05f;
	}
	else 
	{
		yawMovement = 0.0f;
	}

	long pitchAxis = joystickState.lRy - 32767;
	if ((pitchAxis + deadzone < -deadzone) || (pitchAxis - deadzone > deadzone))
	{
		pitchMovement = (pitchAxis / 32767.0f) * 0.05f;
	}
	else
	{
		pitchMovement = 0.0f;
	}

	if (ix == 0 && iz == 0)
	{
		movementSpeed = 0.0f;
		xMovement = 0.0f;
		zMovement = 0.0f;
	}
	else {
		movementSpeed = sqrt(pow(ix, 2) + pow(iz, 2)) * 2.0f;
		movementAngle = atan2f(ix, iz);
		changeMovement();
	}

	long deadzoneZ = 100;
	long zAxis = joystickState.lZ - 32767;
	if ((zAxis + deadzoneZ < -deadzoneZ) || (zAxis - deadzoneZ > deadzoneZ))
	{
		yMovement = (-zAxis / 32767.0f);
	}
	else {
		yMovement = 0.0f;
	}
	if (joystickState.rgbButtons[0] & 0x80)
	{
		yMovement *= 2.0f;
	}
	if (ix == 0 && iz == 0)
	{
		movementSpeed = 0.0f;
		xMovement = 0.0f;
		zMovement = 0.0f;
	}
	else {
		movementSpeed = sqrt(pow(ix, 2) + pow(iz, 2)) * 2.0f;
		movementAngle = atan2f(ix, iz);
		if (joystickState.rgbButtons[0] & 0x80)
		{
			movementSpeed *= 2.0f;
		}
		changeMovement();
	}
};

void Camera2::changeMovement()
{
	float totalRadians = -yaw + movementAngle;
	xMovement = sin(totalRadians) * movementSpeed;
	zMovement = cos(totalRadians) * movementSpeed;
};
