#include "graphics.h"
#include <android/log.h>

SizeI Screen::screenSize=SizeI(0,0);
SizeF Screen::pixelSize=SizeF(0,0);
SizeF Screen::viewSize=SizeF(2,2);

void Screen::setScreenSize(const SizeI &screenS) {
	screenSize=screenS;
	pixelSize.w=(float)1/(screenSize.w);//*viewSize.w);
	pixelSize.h=(float)1/(screenSize.h);//*viewSize.h);
}

Point2f Screen::pixel2view(const Point2i& point){
	float x=point.x*pixelSize.w*2;
	float y=point.y*pixelSize.h*2;
	x=x-1;
	y=1-y;
	return Point2f(x,y);
}

SizeI& Screen::getScreenSize() {
	return screenSize;
}

SizeF& Screen::getPixelSize() {
	return pixelSize;
}

bool cmp1D(float Ax1,float Ax2,float Bx1,float Bx2){
	if(Ax1==Bx1 || Ax1==Bx2 || Ax2==Bx1 || Ax2==Bx2)
		return true;
	if(Bx1>Bx2){
		float tmp=Bx2;
		Bx2=Bx1;
		Bx1=tmp;
	}

	if(Bx1<Ax1 && Ax1<Bx2)
		return true;
	if(Bx1<Ax2 && Ax2<Bx2)
		return true;

	if(Ax1>Ax2){
		float tmp=Ax2;
		Ax2=Ax1;
		Ax1=tmp;
	}
	if(Ax1<Bx1 && Bx1<Ax2)
		return true;
	if(Ax1<Bx2 && Bx2<Ax2)
		return true;
	__android_log_print(ANDROID_LOG_INFO, "com.android.game", "cmp1D return false;");
	return false;
}

bool vertical1Dcmp(const Diagonal& diag1,const Diagonal& diag2){
	__android_log_print(ANDROID_LOG_INFO, "com.android.game", "diag1.pos0.y=%f,diag1.pos1.y=%f,diag2.pos0.y=%f,diag2.pos1.y=%f",diag1.pos0.y,diag1.pos1.y,diag2.pos0.y,diag2.pos1.y);
	return cmp1D(diag1.pos0.y,diag1.pos1.y,diag2.pos0.y,diag2.pos1.y);
}
