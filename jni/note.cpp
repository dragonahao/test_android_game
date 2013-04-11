#include "note.h"

GLint Note::texs[4];

static int _rnd( int max ) {
    return (((float)max)*rand()/(RAND_MAX + 1.0));//(1+(int) (((float)max)*rand()/(RAND_MAX+1.0)));
}

void Note::update() {
	unsigned long tCurUpdate = Time::getCurrentms();
	unsigned long delta = tCurUpdate-tLastUpdate;
	if(!tLastUpdate){
		tLastUpdate = tCurUpdate;
		return;
	}
	if(minDeltaTime>delta)
		return;
	float step = delta * speed * Screen::getPixelSize().w;
	yPos = yPos - step;
	tLastUpdate = tCurUpdate;
	refresh();
}

void Note::refresh() {
	setDiagonal(Diagonal(Point2f(xPos,yPos),Point2f(xPos+Screen::getPixelSize().w*iSize.w,yPos-Screen::getPixelSize().h*iSize.h)));
}

Note::Note() : xPos(-1.0f), yPos(1.0f), speed(0.0f), tLastUpdate(0),minDeltaTime(0),direction(up) {
    iSize = SizeI(128, 128);
    setUseAlpha(true);
    refresh();
}

inline void Note::setAlignment(Alignment alignment) {
    if(alignment == toLeft){
        xPos = -1;
    }else{
        xPos = 1-Screen::getPixelSize().w * iSize.w;
    }
    refresh();
}

inline void Note::setSpeed(const float& _speed) {
    speed = _speed;
    minDeltaTime = 1/_speed;
    setID(texs[up]);
}

inline void Note::setDirection(const Direction& dir) {
    direction = dir;
    setID(texs[dir]);
}

Direction Note::getDirection() {
    return direction;
}

static void Note::setTex(Direction dir,const GLint& texID) {
    texs[dir] = texID;
}

void NoteList::generate() {
    unsigned long tCurUpdate = Time::getCurrentms();
    unsigned long delta = tCurUpdate-tLastUpdate;
    if(!tLastUpdate){
        tLastUpdate = tCurUpdate;
        return;
    }
    if(minDelta > delta && !listNote.empty())
        return;
    tLastUpdate = tCurUpdate;
    Note note;
    note.setSpeed(speed);
    note.setAlignment(type);
    note.setDirection(static_cast<Note::Direction>(_rnd(4)));
    listNote.push_front(note);
    //minDelta = 10000;
}

NoteList::NoteList():tLastUpdate(0), speed(0), type(Note::toLeft), minDelta(0) {

}

void NoteList::update(){
    for(list<Note>::iterator it = listNote.begin(); it != listNote.end(); it++) {
        (*it).update();
    }
    generate();
}

void NoteList::draw(){
    for(list<Note>::iterator it = listNote.begin(); it != listNote.end(); t++) {
        (*it).draw();
    }
}

void NoteList::setSpeed(const float& _speed) {
    speed = _speed;
}

void NoteList::setType(const Note::Alignment & align) {
    type = align;
}

list<Note>* NoteList::get() {
    return &listNote;
}

void NoteList::clear() {
    listNote.clear();
}
