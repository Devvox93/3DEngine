#include "Keyboard.h"
#include "Logger.h"

#define KEYDOWN(name, key) (name[key] & 0x80)

/**
* Function:	Keyboard::Keyboard(...)
* Description:	Keyboard constructor
*/
Keyboard::Keyboard(IDirectInputDevice8 *argDDevice)
{
	
}


/**
* Function:	Keyboard::~Keyboard()
* Description:	Keyboard destructor
*/
Keyboard::~Keyboard()
{

}