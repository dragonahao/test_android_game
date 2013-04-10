#ifndef _NOTE_H_
#define _NOTE_H_

#include "graphics.h"
#include "texture.h"
#include "time_.h"
#include <android/log.h>

class Note : public Texture {
	//Пикселей в 10-3 сек.
	float speed;
	unsigned long minDeltaTime;
	void refresh();
	unsigned long tLastUpdate;
	static GLint texs[4];
	float xPos;
	float yPos;
	SizeI iSize;
public:
	enum Direction{
		left,
		right,
		up,
		down
	}direction;
	enum Alignment{
		toLeft,
		toRight
	};
	Note() : xPos(-1.0f), yPos(1.0f), speed(0.0f), tLastUpdate(0),minDeltaTime(0),direction(up){
		iSize=SizeI(128,128);
		setUseAlpha(true);
		refresh();
	}
	inline void setAlignment(Alignment alignment){
		if(alignment==toLeft){
			xPos=-1;
		}else{
			xPos=1-Screen::getPixelSize().w*iSize.w;
		}
		refresh();
	}
	inline void setSpeed(const float& _speed){
		speed=_speed;
		minDeltaTime=1/_speed;
		setID(texs[up]);
	}
	inline void setDirection(const Direction& dir){
		direction=dir;
		setID(texs[dir]);
	}
	Direction getDirection() {
		return direction;
	}
	void update();
	//void draw();
	static void setTex(Direction dir,const GLint& texID){
		texs[dir]=texID;
	}
};

#include <list>
using namespace std;

static int _rnd( int max ) {
    return (((float)max)*rand()/(RAND_MAX+1.0));//(1+(int) (((float)max)*rand()/(RAND_MAX+1.0)));
}


class NoteList{
	list<Note> listNote;
	float speed;
	Note::Alignment type;
	unsigned long tLastUpdate;
	unsigned long minDelta;
	void generate(){
		unsigned long tCurUpdate=Time::getCurrentms();
		unsigned long delta=tCurUpdate-tLastUpdate;
		if(!tLastUpdate){
			tLastUpdate=tCurUpdate;
			return;
		}
		if(minDelta>delta && !listNote.empty())
			return;
		tLastUpdate=tCurUpdate;
		Note note;
		note.setSpeed(speed);
		note.setAlignment(type);
		note.setDirection(static_cast<Note::Direction>(_rnd(4)));
		listNote.push_front(note);
		minDelta=10000;
	}
public:
	NoteList():tLastUpdate(0),speed(0),type(Note::toLeft),minDelta(0){}
	inline void update(){
		for(list<Note>::iterator it=listNote.begin();it!=listNote.end();it++){
			(*it).update();
		}
		generate();
	}
	inline void draw(){
		for(list<Note>::iterator it=listNote.begin();it!=listNote.end();it++){
			(*it).draw();
		}
	}
	inline void setSpeed(const float& _speed){
		speed=_speed;
	}
	inline void setType(const Note::Alignment & align){
		type=align;
	}

	list<Note>* get(){
		return &listNote;
	}
	void clear(){
		listNote.clear();
	}
};

#endif
