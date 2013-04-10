#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "note.h"
#include "score.h"
#include "texture.h"
#include "action.h"
#include "joystick.h"
#include <linux/stddef.h>
#include <list>
#include <pthread.h>

class GameManager{
	GameManager():texCount(0){}
	static GameManager* gameManager;
	int texCount;
	std::list<Joystick::JoystickAction> userMove;
	Score score;
	Texture background;
	Joystick joystick;
	Texture leftTube;
	Texture rightTube;
	NoteList leftNoteList;
	NoteList rightNoteList;
	static pthread_mutex_t mutex;
public:
	static void lock();
	static void unlock();
	static GameManager* getManaget(){
		if(gameManager!=NULL)
			return gameManager;
		else{
			gameManager=new GameManager();
			return gameManager;
		}
	}
	void init();
	void loop();
	void draw();
	void onTouchEvent(const TouchAction& touchAct);
	void onResize(const int w,const int h);
	void setTexture(int texID);
};
#endif
