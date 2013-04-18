#include "note.h"

GLint Note::texs[4];

static int _rnd( int max ) {
    return (((float)max) * rand() / (RAND_MAX + 1.0));
}

void Note::update() {
	unsigned long tCurUpdate = Time::getCurrentms();
	unsigned long delta = tCurUpdate-tLastUpdate;
	if(!tLastUpdate){
		tLastUpdate = tCurUpdate;
		return;
	}
	if(updateTime > delta)
		return;
	float step = delta * speed * Screen::getPixelSize().w;
	yPos = yPos - step;
	tLastUpdate = tCurUpdate;
	refresh();
}

void Note::refresh() {
	setDiagonal(Diagonal(Point2f(xPos,yPos),Point2f(xPos+Screen::getPixelSize().w*iSize.w,yPos-Screen::getPixelSize().h*iSize.h)));
}

Note::Note() : xPos(-1.0f), yPos(1.0f), speed(0.0f), tLastUpdate(0), updateTime(0), direction(up) {
    iSize = SizeI(128, 128);
    setUseAlpha(true);
    refresh();
}

void Note::setAlignment(Alignment alignment) {
    if(alignment == toLeft){
        xPos = -1;
    }else{
        xPos = 1 - Screen::getPixelSize().w * iSize.w;
    }
    refresh();
}

void Note::setSpeed(const float& _speed) {
    speed = _speed;
    updateTime = 1 / _speed;
    setID(texs[up]);
}

void Note::setDirection(const Direction& dir) {
    direction = dir;
    setID(texs[dir]);
}

Note::Direction Note::getDirection() {
    return direction;
}

void Note::setTex(Direction dir, const GLint& texID) {
    texs[dir] = texID;
}

void NoteList::generate() {
    unsigned long tCurUpdate = Time::getCurrentms();
    unsigned long delta = tCurUpdate-tLastUpdate;
    if(!tLastUpdate){
        tLastUpdate = tCurUpdate;
        return;
    }
    if(minDelayBetweenNotes > delta && !listNote.empty())
        return;
    tLastUpdate = tCurUpdate;
    Note note;
    note.setSpeed(speed);
    note.setAlignment(type);
    note.setDirection(static_cast<Note::Direction>(_rnd(4)));
    listNote.push_front(note);
    //minDelayBetweenNotes = 10000;
}

void NoteList::setMinDelayBetweenNotes(unsigned long minDelay) {
	minDelayBetweenNotes = minDelay;
}

NoteList::NoteList():tLastUpdate(0), speed(0), type(Note::toLeft), minDelayBetweenNotes(1000) {

}

void NoteList::update(){
    for(list<Note>::iterator it = listNote.begin(); it != listNote.end(); it++) {
        (*it).update();
    }
    generate();
}

void NoteList::draw(){
    for(list<Note>::iterator it = listNote.begin(); it != listNote.end(); it++) {
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
