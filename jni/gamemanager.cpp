#include "gamemanager.h"
#include "graphics.h"
#include <unistd.h>

pthread_mutex_t GameManager::mutex = PTHREAD_MUTEX_INITIALIZER;

/*For test use only one level*/
class Level {
    int number;
    int plusScore;
    int minusScore;
public:
    Level() : number(0), plusScore(10), minusScore(-10) {}
    bool isNextLevel(Score & score) {
        return false;
    }
    void addScore(Score & score) {
        score.value += plusScore;
    }
    void delScore(Score & score) {
        score.value += minusScore;
    }
    float getSpeed() {
        return 0.036f;
    }
};

GameManager::GameManager():texCounter(0) {
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
	const int backgroundTex = 10;
	const int tubeTex = 11;

	const int pushButtonUpTex = 12;
	const int pushButtonUpOnPressTex = 13;
	const int pushButtonDownTex = 14;
    const int pushButtonDownOnPressTex = 15;
    const int pushButtonLeftTex = 16;
    const int pushButtonLeftOnPressTex = 17;
    const int pushButtonRightTex = 18;
    const int pushButtonRightOnPressTex = 19;

	const int noteUpTex = 20;
	const int noteDownTex = 21;
	const int noteLeftTex = 22;
	const int noteRightTex = 23;
	//add digit texture
	if(texCounter < backgroundTex)
		score.addDigit(texCounter, texID);
	if(texCounter == backgroundTex)
		background.setID(texID);
	if(texCounter == tubeTex) {
		rightTube.setID(texID);
		leftTube.setID(texID);
	}
	if(texCounter == pushButtonUpTex) {
		joystick.setTex(Joystick::PBUp, texID, false);
	}
	if(texCounter == pushButtonUpOnPressTex) {
		joystick.setTex(Joystick::PBUp, texID, true);
	}
	if(texCounter == pushButtonDownTex) {
		joystick.setTex(Joystick::PBDown, texID, false);
	}
	if(texCounter == pushButtonDownOnPressTex) {
		joystick.setTex(Joystick::PBDown, texID, true);
	}
	if(texCounter == pushButtonLeftTex) {
		joystick.setTex(Joystick::PBLeft, texID, false);
	}
	if(texCounter == pushButtonLeftOnPressTex) {
		joystick.setTex(Joystick::PBLeft, texID, true);
	}
	if(texCounter == pushButtonRightTex) {
		joystick.setTex(Joystick::PBRight, texID, false);
	}
	if(texCounter == pushButtonRightOnPressTex) {
		joystick.setTex(Joystick::PBRight, texID, true);
	}
	if(texCounter == noteUpTex) {
		Note::setTex(Note::up, texID);
	}
	if(texCounter == noteDownTex) {
		Note::setTex(Note::down, texID);
	}
	if(texCounter == noteLeftTex) {
		Note::setTex(Note::left, texID);
	}
	if(texCounter == noteRightTex) {
		Note::setTex(Note::right, texID);
	}
	texCounter++;
}

void GameManager::init(){
	background.setDiagonal(Diagonal(Point2f(-1, 1), Point2f(1, -1)));
	leftTube.setDiagonal(Diagonal(Point2f(-1, 0), Point2f(-0.7, -1)));
	rightTube.setDiagonal(Diagonal(Point2f(0.7, 0), Point2f(1, -1)));
	leftNoteList.setSpeed(lvl->getSpeed());
	rightNoteList.setType(Note::toRight);
	rightNoteList.setSpeed(lvl->getSpeed());
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
		usleep(1000);
	}
}
