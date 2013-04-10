#include "note.h"

GLint Note::texs[4];

void Note::update(){
	unsigned long tCurUpdate=Time::getCurrentms();
	unsigned long delta=tCurUpdate-tLastUpdate;
	if(!tLastUpdate){
		tLastUpdate=tCurUpdate;
		return;
	}
	if(minDeltaTime>delta)
		return;
	float step=delta*speed*Screen::getPixelSize().w;
	yPos=yPos-step;
		//__android_log_print(ANDROID_LOG_INFO, "com.android.game", "UPDATE speed=%f,step=%f,delta=%d,minDeltaTime=%d,tCurUpdate=%d,tLastUpdate=%d,yPos=%f",speed,step,delta,minDeltaTime,tCurUpdate,tLastUpdate,yPos);
	tLastUpdate=tCurUpdate;
		/*for(int k=0;k<8;k+=2){
				__android_log_print(ANDROID_LOG_INFO, "com.android.game", "NEW pos[%d]={%f,%f}",k, coords[k], coords[k+1]);
			}*/
	refresh();
}

void Note::refresh(){
	setDiagonal(Diagonal(Point2f(xPos,yPos),Point2f(xPos+Screen::getPixelSize().w*iSize.w,yPos-Screen::getPixelSize().h*iSize.h)));
}
