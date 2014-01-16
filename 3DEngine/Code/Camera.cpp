#include <dinput.h>
#include "Camera.h"
#include "Logger.h"
#include <sstream>

#define PI 3.14159265f

Camera::Camera()
{
	speed = 0.0f;

	xMovement = 0.0f;
	yMovement = 0.0f;
	zMovement = 0.0f;

	yawMovement = 0.0f;
	pitchMovement = 0.0f;
	rollMovement = 0.0f;
}


Camera::~Camera()
{
}

void Camera::update()
{
	/*TripleFloat rot = getRotation();
	float theta = rot.y;
	float phi = rot.x;

	xMovement = speed*sinf(phi)*cosf(theta);
	yMovement = speed*sinf(phi)*sinf(theta);
	zMovement = speed*cosf(phi);*/

	TripleFloat tf = getPosition();
	tf.x += xMovement;
	tf.y += yMovement;
	tf.z += zMovement;
	setPosition(tf.x, tf.y, tf.z);

	// Voor Joystick
	TripleFloat tf2 = getRotation();
	tf2.x += yawMovement;
	tf2.y += pitchMovement;
	setRotation(tf2.x, tf2.y, tf2.z);
}

void Camera::moveCamera(int transformation, float speed)
{
	TripleFloat rot = getRotation();
	float yaw = rot.x, pitch = rot.y;

	switch (transformation) {
	case CAMERA_MOVE:
		//TODO: Fix tegenovergestelde Y-movement met -yaw
		xMovement = speed * sinf(yaw) * cosf(pitch);
		yMovement = speed * sinf(yaw) * sinf(pitch);
		zMovement = speed * cosf(yaw);

		break;
	case CAMERA_STRAFE:
		//TODO: Strafen fixen
		xMovement += speed * sinf(yaw + PI / 2) * cosf(pitch + PI / 2);
		zMovement += speed * cosf(yaw + PI / 2);

		break;
	case CAMERA_ELEVATE:
		yMovement += speed * sinf(pitch + PI / 2);

		break;
	}
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

	// Custom multiplyen van Matrices
	D3DXMATRIXA16 rot1;
	D3DXMatrixRotationYawPitchRoll(&rot1, yaw, 0.0f, 0.0f);
	D3DXMATRIXA16 rot2;
	D3DXMatrixRotationYawPitchRoll(&rot2, 0.0f, pitch, 0.0f);
	D3DXMatrixMultiply(&rotationMatrix, &rot1, &rot2);
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
	Logger::getInstance().log(INFO, "Camera KEYBOARD input gebruikt");

#pragma region "Keys"

#pragma region "Arrows"
	if (keyboardState[DIK_UPARROW] & 0x80)
	{
		Logger::getInstance().log(INFO, "Up arrow");
		/*speed = 0.1f;*/
		moveCamera(CAMERA_MOVE, 0.3f);
		
	}
	else if (keyboardState[DIK_DOWNARROW] & 0x80)
	{
		Logger::getInstance().log(INFO, "Down arrow");
		/*speed = -0.1f;*/
		moveCamera(CAMERA_MOVE, -0.3f);
	}
	else
	{
		/*speed = 0.0f;*/
		moveCamera(CAMERA_MOVE, 0.0f);
	}

	if (keyboardState[DIK_LEFTARROW] & 0x80)
	{
		Logger::getInstance().log(INFO, "Left arrow");

		/*xMovement = -0.1f;*/
		moveCamera(CAMERA_STRAFE, 0.3f);
	}
	else if (keyboardState[DIK_RIGHTARROW] & 0x80)
	{
		Logger::getInstance().log(INFO, "Right arrow");
		/*xMovement = 0.1f;*/
		moveCamera(CAMERA_STRAFE, -0.3f);
	}
	else
	{
		/*xMovement = 0.0f;*/
		moveCamera(CAMERA_STRAFE, 0.0f);
	}
#pragma endregion

#pragma region "WASD"
	if (keyboardState[DIK_W] & 0x80)
	{
		Logger::getInstance().log(INFO, "W key");

		pitchMovement = -0.1f;
	}
	else if (keyboardState[DIK_S] & 0x80)
	{
		Logger::getInstance().log(INFO, "S key");
		pitchMovement = 0.1f;
	}
	else
	{
		pitchMovement = 0.0f;
	}

	if (keyboardState[DIK_A] & 0x80)
	{
		Logger::getInstance().log(INFO, "A key");

		yawMovement = -0.1f;
	}
	else if (keyboardState[DIK_D] & 0x80)
	{
		Logger::getInstance().log(INFO, "D key");
		yawMovement = 0.1f;
	}
	else
	{
		yawMovement = 0.0f;
	}
#pragma endregion

#pragma region "Other"
	if (keyboardState[DIK_RSHIFT] & 0x80)
	{
		Logger::getInstance().log(INFO, "Right Shift");
		/*yMovement = -0.1f;*/
		moveCamera(CAMERA_ELEVATE, 0.3f);
	}
	else if (keyboardState[DIK_RCONTROL] & 0x80)
	{
		Logger::getInstance().log(INFO, "Right Control");
		/*yMovement = 0.1f;*/
		moveCamera(CAMERA_ELEVATE, -0.3f);
	}
	else
	{
		/*yMovement = 0.0f;*/
		moveCamera(CAMERA_ELEVATE, 0.0f);
	}
#pragma endregion

#pragma endregion
}

void Camera::useMouseInput(DIMOUSESTATE mouseState)
{
	TripleFloat rot = getRotation();

	rot.x += (mouseState.lX / 100.0f);
	rot.y += (mouseState.lY / 100.0f);

	setRotation(rot.x, rot.y, rot.z);
}

void Camera::useJoystickInput(DIJOYSTATE2 joystickState)
{
	/*Logger::getInstance().log(INFO, "JoystickInput gebruikt ofzo");
	std::ostringstream oss;
	oss << "Data: lARx: " << joystickState.lARx << ", lARy: " << joystickState.lARy << ", lARz: " << joystickState.lARz << std::endl
		<< "lAX: " << joystickState.lAX << ", lAY: " << joystickState.lAY << ", lAZ: " << joystickState.lAZ << std::endl
		<< "lFTx: " << joystickState.lFRx << ", lFTy: " << joystickState.lFRy << ", lFTz: " << joystickState.lFRz << std::endl
		<< "lFX: " << joystickState.lFX << ", lFY: " << joystickState.lFY << ", lFZ: " << joystickState.lFZ << std::endl
		<< "lRx: " << joystickState.lRx << ", lRy: " << joystickState.lRy << ", lRz: " << joystickState.lRz << std::endl
		<< "lVRx: " << joystickState.lVRx << ", lVRy: " << joystickState.lVRy << ", lVRz: " << joystickState.lVRz << std::endl
		<< "lVX: " << joystickState.lVX << ", lVY: " << joystickState.lVY << ", lVZ: " << joystickState.lVZ << std::endl
		<< "lX: " << joystickState.lX << ", lY: " << joystickState.lY << ", lZ: " << joystickState.lZ << std::endl
		<< "Buttons:" << std::endl;
	//<< ", lX: " << joystickState.rgbButtons;
	for (int i = 0; i < 128; i++)
	{
		if (joystickState.rgbButtons[i] & 0x80) {
			oss << i << " ";
		}
	}
	oss << std::endl;

	oss << "More data: rgdwPOV[0]: " << joystickState.rgdwPOV[0] << ", rgdwPOV[1]: " << joystickState.rgdwPOV[1] << ", rgdwPOV[2]: " << joystickState.rgdwPOV[2] << ", rgdwPOV[3]: " << joystickState.rgdwPOV[3] << std::endl;
	oss << "rglASlider[0]: " << joystickState.rglASlider[0] << ", rglASlider[1]: " << joystickState.rglASlider[1] << std::endl;
	oss << "rglFSlider[0]: " << joystickState.rglFSlider << ", rglFSlider[1]: " << joystickState.rglFSlider[1] << std::endl;
	oss << "rglSlider[0]: " << joystickState.rglSlider[0] << ", rglSlider[1]: " << joystickState.rglSlider[1] << std::endl;
	oss << "rglVSlider[0]: " << joystickState.rglVSlider[0] << ", rglVSlider[1]: " << joystickState.rglVSlider[1] << std::endl;
	Logger::getInstance().log(INFO, oss.str());*/
	

	if (joystickState.rgdwPOV[0] < 4294967295 )
	{
		float degrees = joystickState.rgdwPOV[0] / 100;
		float radians = degrees*PI / 180.0f;
		xMovement = sin(radians) * 0.1f;
		yMovement = cos(radians) * 0.1f;
	}
	else 
	{
		xMovement = 0.0f;
		yMovement = 0.0f;
	}
	
	long deadzone = 3000;
	//32767
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

	//32767
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
	//32767
	long zAxis = joystickState.lZ - 32767;
	if ((zAxis + deadzoneZ < -deadzoneZ) || (zAxis - deadzoneZ > deadzoneZ))
	{
		zMovement = (-zAxis / 32767.0f) * 0.1f;
	}
	else {
		zMovement = 0.0f;
	}

}