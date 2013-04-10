#include "gamemanager.h"
#include "graphics.h"
#include <unistd.h>

GameManager* GameManager::gameManager=NULL;

pthread_mutex_t GameManager::mutex = PTHREAD_MUTEX_INITIALIZER;

void GameManager::lock(){
	pthread_mutex_lock( &mutex );
}

void GameManager::unlock(){
	pthread_mutex_unlock( &mutex );
}

void GameManager::setTexture(int texID){
	if(texCount<10)
	 	 score.addDiget(texCount,texID);
	if(texCount==10)
		background.setID(texID);
	if(texCount==11){
		rightTube.setID(texID);
		leftTube.setID(texID);
	}
	if(texCount==12){
		joystick.setTex(Joystick::PBUp, texID, false);
	}
	if(texCount==13){
		joystick.setTex(Joystick::PBUp, texID, true);
	}
	if(texCount==14){
		joystick.setTex(Joystick::PBDown, texID, false);
	}
	if(texCount==15){
		joystick.setTex(Joystick::PBDown, texID, true);
	}
	if(texCount==16){
		joystick.setTex(Joystick::PBLeft, texID, false);
	}
	if(texCount==17){
		joystick.setTex(Joystick::PBLeft, texID, true);
	}
	if(texCount==18){
		joystick.setTex(Joystick::PBRight, texID, false);
	}
	if(texCount==19){
		joystick.setTex(Joystick::PBRight, texID, true);
	}
	if(texCount==20){
		Note::setTex(Note::up,texID);
	}
	if(texCount==21){
		Note::setTex(Note::down, texID);
	}
	if(texCount==22){
		Note::setTex(Note::left, texID);
	}
	if(texCount==23){
		Note::setTex(Note::right, texID);
	}
	texCount++;
	__android_log_print(ANDROID_LOG_INFO, "com.android.game", "textures[%d]=%d", texCount, texID);
}

void GameManager::init(){
	background.setDiagonal(Diagonal(Point2f(-1,1),Point2f(1,-1)));
	leftTube.setDiagonal(Diagonal(Point2f(-1,0),Point2f(-0.7,-1)));
	rightTube.setDiagonal(Diagonal(Point2f(0.7,0),Point2f(1,-1)));
	leftNoteList.setSpeed(0.036f);
	rightNoteList.setType(Note::toRight);
	rightNoteList.setSpeed(0.036f);
	//userMove.clear();
}

void GameManager::onTouchEvent(const TouchAction& touchAct){
	Joystick::JoystickAction pb=joystick.onTouchEvent(touchAct);
	if(pb!=Joystick::PBNone){
		userMove.push_back(pb);
	}
		//__android_log_print(ANDROID_LOG_INFO, "com.android.game", "OnTouch event=%d,X=%f,Y=%f",touchAct.act,touchAct.x,touchAct.y);
}

void GameManager::onResize(const int w,const int h){
	Screen::setScreenSize(SizeI(w,h));
	__android_log_print(ANDROID_LOG_INFO, "com.android.game", "resize w=%d h=%d", w, h);
}

void GameManager::draw(){
		glViewport(0, 0, Screen::getScreenSize().w, Screen::getScreenSize().h);
		//__android_log_print(ANDROID_LOG_INFO, "com.android.game", "resize w=%d h=%d", Screen::getScreenSize().w, Screen::getScreenSize().h);
	    glClearColor(.0f,.0f,.5f,1);
	    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	    glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
	    //gluPerspective(45, (float)width / height, 0.5f, 150);
	    glMatrixMode(GL_MODELVIEW);
	    glLoadIdentity();
	    background.draw();
	    rightTube.draw();
	    leftTube.draw();
	    score.draw();
	    leftNoteList.draw();
	    rightNoteList.draw();
	    joystick.draw();
}

Joystick::JoystickAction noteDir2JAct(Note::Direction dir){
	if(dir==Note::left)
		return Joystick::PBLeft;
	if(dir==Note::right)
		return Joystick::PBRight;
	if(dir==Note::up)
		return Joystick::PBUp;
	if(dir==Note::down)
		return Joystick::PBDown;
	return Joystick::PBNone;
}

void GameManager::loop(){
	while(1){
		lock();
		for(list<Joystick::JoystickAction>::iterator it=userMove.begin();it!=userMove.end();it++){
			if(!leftNoteList.get()->empty()){
				Note note=leftNoteList.get()->back();
				if(vertical1Dcmp(note.getDiagonal(),leftTube.getDiagonal())){
					if(noteDir2JAct(note.getDirection())==(*it)){
						leftNoteList.get()->pop_back();
						score.value+=10;
						continue;
					}
				}
			}
			if(!rightNoteList.get()->empty()){
				Note note=rightNoteList.get()->back();
				if(vertical1Dcmp(note.getDiagonal(),rightTube.getDiagonal())){
					if(noteDir2JAct(note.getDirection())==(*it)){
						rightNoteList.get()->pop_back();
						score.value+=10;
					}
				}
			}
		}
		userMove.clear();
		if(!leftNoteList.get()->empty()){
			if(leftNoteList.get()->back().getDiagonal().pos1.y<-1){
				leftNoteList.get()->pop_back();
				score.value-=10;
			}
		}
		if(!rightNoteList.get()->empty()){
			if(rightNoteList.get()->back().getDiagonal().pos1.y<-1){
				rightNoteList.get()->pop_back();
				score.value-=10;
			}
		}
		if(score.value<0)
			score.value=0;
		leftNoteList.update();
		rightNoteList.update();
		unlock();
		usleep(1000);
	}
}
