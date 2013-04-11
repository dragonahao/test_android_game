#ifndef __SCORE_H__
#define __SCORE_H__

#include <android/log.h>
#include "graphics.h"

class Score {
public:
	Score();
	~Score();
	bool addDiget(unsigned diget, int idTex);
	void setDigetSize(const SizeI& size);
	int value;
	void draw();
private:
	const GLfloat yPos;
	SizeI digetSize;
	bool refreshCoord;
	int texDigets[10];
	static const int maxCountDigets = 5;
	Point2f* digetDiagonal;
};
#endif
