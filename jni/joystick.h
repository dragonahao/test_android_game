#ifndef _JOISTICK_H_
#define _JOISTICK_H_

#include "action.h"
#include "time_.h"

class PushButton;

class Joystick{
	PushButton* pbLeft;
	PushButton* pbRight;
	PushButton* pbUp;
	PushButton* pbDown;
public:
	enum JoystickAction {
		PBNone = 4,
		PBLeft = 0,
		PBRight = 2,
		PBUp = 1,
		PBDown = 3
	};
	Joystick();
	~Joystick();
	void setTex(JoystickAction pbType, int texID, bool onPress = true);
	JoystickAction onTouchEvent(const TouchAction& touchAct);
	void draw();
};

#endif
