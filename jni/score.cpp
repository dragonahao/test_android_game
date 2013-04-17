#include "score.h"
#include <unistd.h>
#include "texture.h"

void Score::draw() {
	if(refreshCoord) {
		int lenPixDigit = digitSize.w * maxCountDigits;
		float HDigit = (float)digitSize.h * Screen::getPixelSize().h;
		float WDigit = (float)digitSize.w * Screen::getPixelSize().w;
		float xPos = (float)lenPixDigit * Screen::getPixelSize().w / (-2);
		float yStartPos = yPos;
		float _yPos;
		int k = 0;
		for(int i = 0; i < maxCountDigits; i++){
			_yPos=yStartPos;
			digitDiagonal[k].x = xPos;
			digitDiagonal[k].y = _yPos;
			xPos += WDigit;
			_yPos -= HDigit;
			digitDiagonal[k + 1].x = xPos;
			digitDiagonal[k + 1].y = _yPos;
			k += 2;
		}
		refreshCoord = false;
	}
	int number = value;
	int digit = 0;
	int k = (maxCountDigits) * 2 - 1;
	Texture tex;
	tex.setUseAlpha(true);
	for(int i = maxCountDigits - 1; i >= 0; i--){
		digit = number % 10;
		number /= 10;
		tex.setDiagonal(Diagonal(digitDiagonal[k-1], digitDiagonal[k]));
		tex.setID(texDigits[digit]);
		tex.draw();
		k -= 2;
	}
}

Score::Score():value(0), refreshCoord(true), yPos(1){
    digitSize = SizeI(56, 56);
    digitDiagonal = new Point2f[maxCountDigits * 2];
}

Score::~Score() {
    delete [] digitDiagonal;
}

bool Score::addDigit(unsigned digit, int idTex){
    if(digit > 9)
        return false;
    texDigits[digit] = idTex;
    return true;
}

inline void Score::setDigitSize(const SizeI& size){
    digitSize = size;
    refreshCoord = true;
}
