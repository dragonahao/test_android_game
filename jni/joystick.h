#ifndef _JOISTICK_H_
#define _JOISTICK_H_

#include "action.h"
#include "time_.h"

class PushButton : public Texture{
	//10-3 s
	int texOnPress;
	int texOnRelease;
public:
	enum PBAction{
		PBNone,
		PBPress,
		PBRelease
	};
	PushButton() : lastAction(PBNone){
		setUseAlpha(true);
	}
	void setTexOnPress(int texID){
		texOnPress=texID;
	}
	void setTexOnRelease(int texID){
		texOnRelease=texID;
	}
	void draw(){
		if(lastAction==PBPress)
			setID(texOnPress);
		else
			setID(texOnRelease);
		Texture::draw();
	}
	PBAction pbOnTouch(const TouchAction& touchAct){
		if(touchAct.act==TouchAction::MOVE || touchAct.act==TouchAction::CANCEL){
			return PBNone;
		}
		lastAction=PBNone;
		Point2f pixel=Screen::pixel2view(Point2i(touchAct.x,touchAct.y));
		if(pixel.x>diagonal.pos0.x && pixel.x<diagonal.pos1.x){
			if(pixel.y<diagonal.pos0.y && pixel.y>diagonal.pos1.y){
				lastAction=touch2PBAction(touchAct.act);
				return lastAction;
			}
		}
		return PBNone;
	}
private:
	PBAction touch2PBAction(const TouchAction::Action & act){
		if(act==TouchAction::UP)
			return PBRelease;
		if(act==TouchAction::DOWN)
			return PBPress;
		return PBNone;
	}
	PBAction lastAction;
};

class Joystick{
	PushButton pbLeft;
	PushButton pbRight;
	PushButton pbUp;
	PushButton pbDown;
public:
	enum JoystickAction {
		PBNone=4,
		PBLeft=0,
		PBRight=2,
		PBUp=1,
		PBDown=3
	};
	Joystick(){
		pbUp.setDiagonal(Diagonal(-0.15f,0.4f,0.15f,0.0f));
		pbDown.setDiagonal(Diagonal(-0.15f,-0.4f,0.15f,-0.8f));
		pbLeft.setDiagonal(Diagonal(-0.45f,0.0f,-0.15f,-0.4f));
		pbRight.setDiagonal(Diagonal(0.15f,0.0f,0.45f,-0.4f));
	}
	void setTex(JoystickAction pbType,int texID,bool onPress=true){
		PushButton* pb;
		switch(pbType){
			case PBLeft:
				pb=&pbLeft;
			break;
			case PBRight:
				pb=&pbRight;
			break;
			case PBUp:
				pb=&pbUp;
			break;
			case PBDown:
				pb=&pbDown;
			break;
			default:return;
		}
		if(onPress)
			pb->setTexOnPress(texID);
		else
			pb->setTexOnRelease(texID);
	}
	JoystickAction onTouchEvent(const TouchAction& touchAct){
		if(pbLeft.pbOnTouch(touchAct)==PushButton::PBPress){
			//__android_log_print(ANDROID_LOG_INFO, "com.android.game", "~!~!~!~!~!OnTouch PB LEFT~~~~~");
			return PBLeft;
		}
		if(pbRight.pbOnTouch(touchAct)==PushButton::PBPress){
			//__android_log_print(ANDROID_LOG_INFO, "com.android.game", "~!~!~!~!~!OnTouch PB RIGHT~~~~~");
			return PBRight;
		}
		if(pbUp.pbOnTouch(touchAct)==PushButton::PBPress){
			//__android_log_print(ANDROID_LOG_INFO, "com.android.game", "~!~!~!~!~!OnTouch PB UP~~~~~");
			return PBUp;
		}
		if(pbDown.pbOnTouch(touchAct)==PushButton::PBPress){
			//__android_log_print(ANDROID_LOG_INFO, "com.android.game", "~!~!~!~!~!OnTouch PB DOWN~~~~~");
			return PBDown;
		}
		return PBNone;
	}
	void draw(){
		pbUp.draw();
		pbDown.draw();
		pbLeft.draw();
		pbRight.draw();
	}
};
#endif
