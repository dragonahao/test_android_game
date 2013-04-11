#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <GLES/gl.h>
#include <GLES/glext.h>

struct Point2f{
	Point2f(float _x = 0, float _y = 0):x(_x),y(_y){}
	float x;
	float y;
};

struct Point2i{
	Point2i(int _x = 0, int _y = 0):x(_x),y(_y){}
	int x;
	int y;
};

struct Point2s{
	Point2s(short _x = 0, short _y = 0):x(_x),y(_y){}
	short x;
	short y;
};

struct SizeI{
	SizeI(int _w = 0, int _h = 0):w(_w),h(_h){}
	int w;
	int h;
};

struct SizeF{
	SizeF(float _w = 0, float  _h = 0):w(_w),h(_h){}
	float w;
	float h;
};

struct Diagonal{
	Diagonal(Point2f _pos0,Point2f _pos1){
		pos0 = _pos0;
		pos1 = _pos1;
	}
	Diagonal(float _x0 = 0, float _y0 = 0, float _x1 = 0, float _y1 = 0){
		pos0.x = _x0;
		pos1.x = _x1;
		pos0.y = _y0;
		pos1.y = _y1;
	}
	Point2f pos0;
	Point2f pos1;
};

bool cmp1D(float Ax1, float Ax2, float Bx1, float Bx2);
bool vertical1Dcmp(const Diagonal& diag1, const Diagonal& diag2);

class Screen{
	static SizeI screenSize;
	static SizeF pixelSize;
	static SizeF viewSize;
public:
	static void setScreenSize(const SizeI& screenS);
	static Point2f pixel2view(const Point2i& point);
	static SizeI& getScreenSize();
	static SizeF& getPixelSize();
};

#endif
