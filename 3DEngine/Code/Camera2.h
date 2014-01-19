#ifndef _CAMERA2_H_
#define _CAMERA2_H_

#include "Entity.h"
#include "KeyboardListener.h"
#include "MouseListener.h"
#include "JoystickListener.h"
class Camera2 : public Entity, public KeyboardListener, public MouseListener, public JoystickListener
{
public:
	Camera2();
	~Camera2();
	void update();
	void setPosition(float x, float y, float z);
	void setRotation(float yaw, float pitch, float roll);
	void setScale(float scaleX, float scaleY, float scaleZ);
	void multiplyMatrices();
	TripleFloat getPosition();
	TripleFloat getRotation();
	TripleFloat getScale();
	void useKeyboardInput(std::array<unsigned char, 256> keyboardState);
	void useMouseInput(DIMOUSESTATE mouseState);
	void useJoystickInput(DIJOYSTATE2 joystickState);
private:
	float xMovement, yMovement, zMovement, yawMovement, pitchMovement, rollMovement, movementAngle, movementSpeed;
	float spinAroundCurrentAngle, spinAroundX, spinAroundZ, spinAroundRadius;
	bool spinning;
	void changeMovement();
};
#endif