#ifndef _NOTE_H_
#define _NOTE_H_

#include "graphics.h"
#include "texture.h"
#include "time_.h"
#include <android/log.h>
#include <list>
using namespace std;

class Note : public Texture {
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
	};
	enum Alignment{
		toLeft,
		toRight
	};
	Note();
	void setAlignment(Alignment alignment);
	inline void setSpeed(const float& _speed);
	inline void setDirection(const Direction& dir);
	Direction getDirection();
	void update();
	static void setTex(Note::Direction dir,const GLint& texID);
private:
	Direction direction;
};

class NoteList{
	list<Note> listNote;
	float speed;
	Note::Alignment type;
	unsigned long tLastUpdate;
	unsigned long minDelta;
    void generate();
public:
    NoteList();
    void update();
    void draw();
    void setSpeed(const float& _speed);
    void setType(const Note::Alignment & align);
    list<Note>* get();
    void clear();
};

#endif
