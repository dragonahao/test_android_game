#include "gamemanager.h"
#include "graphics.h"
#include <unistd.h>
#include "level.h"

pthread_mutex_t GameManager::mutex = PTHREAD_MUTEX_INITIALIZER;
int GameManager::texCounter = 0;

GameManager::GameManager() {
    lvl = new Level();
}

GameManager::~GameManager() {
	delete lvl;
}

void GameManager::lock() {
	pthread_mutex_lock( &mutex );
}

void GameManager::unlock() {
	pthread_mutex_unlock( &mutex );
}

GameManager& GameManager::getInstance() {
    static GameManager gameManager;
    return gameManager;
}

void GameManager::setTexture(int texID) {
	int textureCounter = texCounter;
	texCounter++;
	//add digit texture
	if(textureCounter < backgroundTex) {
		score.addDigit(textureCounter, texID);
		return ;
	}
	switch(textureCounter) {
		case backgroundTex: 
			background.setID(texID);
		break;
		case tubeTex: 
			rightTube.setID(texID);
			leftTube.setID(texID);
		break;
		case pushButtonUpTex:  
			joystick.setTex(Joystick::PBUp, texID, false);
		break;
		case pushButtonUpOnPressTex: 
			joystick.setTex(Joystick::PBUp, texID, true);
		break;	
		case pushButtonDownTex: 
			joystick.setTex(Joystick::PBDown, texID, false);
		break;	
		case pushButtonDownOnPressTex: 
			joystick.setTex(Joystick::PBDown, texID, true);
		break;
		case pushButtonLeftTex: 
			joystick.setTex(Joystick::PBLeft, texID, false);
		break;
		case pushButtonLeftOnPressTex: 
			joystick.setTex(Joystick::PBLeft, texID, true);
		break;
		case pushButtonRightTex: 
			joystick.setTex(Joystick::PBRight, texID, false);
		break;
		case pushButtonRightOnPressTex: 
			joystick.setTex(Joystick::PBRight, texID, true);
		break;
		case noteUpTex: 
			Note::setTex(Note::up, texID);
		break;
		case noteDownTex: 
			Note::setTex(Note::down, texID);
		break;
		case noteLeftTex: 
			Note::setTex(Note::left, texID);
		break;
		case noteRightTex: 
			Note::setTex(Note::right, texID);
		break;
	}
}

void GameManager::init(){
	background.setDiagonal(Diagonal(Point2f(-1, 1), Point2f(1, -1)));
	leftTube.setDiagonal(Diagonal(Point2f(-1, 0), Point2f(-0.7, -1)));
	rightTube.setDiagonal(Diagonal(Point2f(0.7, 0), Point2f(1, -1)));
	leftNoteList.setSpeed(lvl->getSpeed());
	leftNoteList.setMinDelayBetweenNotes(lvl->getMinDelayBetweenNotes());
	rightNoteList.setType(Note::toRight);
	rightNoteList.setSpeed(lvl->getSpeed());
	rightNoteList.setMinDelayBetweenNotes(lvl->getMinDelayBetweenNotes());
}

void GameManager::onTouchEvent(const TouchAction& touchAct) {
	Joystick::JoystickAction pb=joystick.onTouchEvent(touchAct);
	if(pb!=Joystick::PBNone) {
		userMove.push_back(pb);
	}
}

void GameManager::onResize(const int w,const int h) {
	Screen::setScreenSize(SizeI(w,h));
}

void GameManager::draw() {
    glViewport(0, 0, Screen::getScreenSize().w, Screen::getScreenSize().h);
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

static Joystick::JoystickAction noteDir2JAct(Note::Direction dir) {
	if(dir == Note::left)
		return Joystick::PBLeft;
	if(dir == Note::right)
		return Joystick::PBRight;
	if(dir == Note::up)
		return Joystick::PBUp;
	if(dir == Note::down)
		return Joystick::PBDown;
	return Joystick::PBNone;
}

void GameManager::loop() {
	while(1) {
		lock();
		for(list<Joystick::JoystickAction>::iterator it = userMove.begin(); it != userMove.end(); it++) {
			if(!leftNoteList.get()->empty()) {
				Note note = leftNoteList.get()->back();
				if(vertical1Dcmp(note.getDiagonal(), leftTube.getDiagonal())) {
					if(noteDir2JAct(note.getDirection()) == (*it)) {
						leftNoteList.get()->pop_back();
						lvl->addScore(score);
						continue;
					}
				}
			}
			if(!rightNoteList.get()->empty()) {
				Note note = rightNoteList.get()->back();
				if(vertical1Dcmp(note.getDiagonal(),rightTube.getDiagonal())) {
					if(noteDir2JAct(note.getDirection()) == (*it)) {
						rightNoteList.get()->pop_back();
						lvl->addScore(score);
					}
				}
			}
		}
		userMove.clear();
		if(!leftNoteList.get()->empty()) {
			if(leftNoteList.get()->back().getDiagonal().pos1.y < -1) {
				leftNoteList.get()->pop_back();
				lvl->delScore(score);
			}
		}
		if(!rightNoteList.get()->empty()) {
			if(rightNoteList.get()->back().getDiagonal().pos1.y < -1) {
				rightNoteList.get()->pop_back();
				lvl->delScore(score);
			}
		}
		if(score.value < 0)
			score.value = 0;
		leftNoteList.update();
		rightNoteList.update();
		unlock();
		usleep(updateTime);
	}
}
