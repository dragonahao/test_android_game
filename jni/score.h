#ifndef __SCORE_H__
#define __SCORE_H__

#include <android/log.h>
#include "graphics.h"

#define _MAX_SCORE_ 65535
#define _MAX_SCORE_DIGET_ 5

class Score{
public:
	Score():value(0),refreshCoord(true),yPos(1){
		digetSize=SizeI(56,56);
	}
	bool addDiget(unsigned diget, int idTex){
		if(diget>9)
			return false;
		texDigets[diget]=idTex;
		return true;
	}
	inline void setDigetSize(const SizeI& size){
		digetSize=size;
		refreshCoord=true;
	}
	int value;
	void draw();
private:
	const GLfloat yPos;
	SizeI digetSize;
	bool refreshCoord;
	int texDigets[10];
	Point2f digetDiagonal[_MAX_SCORE_DIGET_*2];
};
#endif
