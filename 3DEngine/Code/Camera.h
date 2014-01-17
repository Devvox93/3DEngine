#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "Entity.h"
#include "KeyboardListener.h"
#include "MouseListener.h"
#include "JoystickListener.h"

enum { CAMERA_MOVE, CAMERA_STRAFE, CAMERA_ELEVATE, CAMERA_PITCH, CAMERA_YAW };

class Camera : public Entity, public KeyboardListener, public MouseListener, public JoystickListener
{
public:
	Camera();
	~Camera();
	void update();
	void setPosition(float x, float y, float z);
	void setRotation(float yaw, float pitch, float roll);
	void setScale(float scaleX, float scaleY, float scaleZ);
	TripleFloat getPosition();
	TripleFloat getRotation();
	TripleFloat getScale();
	void useKeyboardInput(std::array<unsigned char, 256> keyboardState);
	void useMouseInput(DIMOUSESTATE mouseState);
	void useJoystickInput(DIJOYSTATE2 joystickState);
private:
	float xMovement, yMovement, zMovement, yawMovement, pitchMovement, rollMovement, speed;
	void moveCamera(int transformation, float speed);
};
#endif