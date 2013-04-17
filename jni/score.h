#ifndef __SCORE_H__
#define __SCORE_H__

#include <android/log.h>
#include "graphics.h"

class Score {
public:
	Score();
	~Score();
	bool addDigit(unsigned digit, int idTex);
	void setDigitSize(const SizeI& size);
	int value;
	void draw();
private:
	const GLfloat yPos;
	SizeI digitSize;
	bool refreshCoord;
	int texDigits[10];
	static const int maxCountDigits = 5;
	Point2f* digitDiagonal;
};
#endif
