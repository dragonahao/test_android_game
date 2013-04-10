#include "score.h"
#include <unistd.h>
#include "texture.h"

void Score::draw(){
	int maxCountDigets=_MAX_SCORE_DIGET_;
	if(refreshCoord){
		int lenPixDiget=digetSize.w*maxCountDigets;
		float HDiget=(float)digetSize.h*Screen::getPixelSize().h;//digetSize.h/screenSize.h;
		float WDiget=(float)digetSize.w*Screen::getPixelSize().w;//digetSize.w/screenSize.w;
		float xPos=(float)lenPixDiget*Screen::getPixelSize().w/(-2);//(float)lenPixDiget/(Screen::getScreenSize().w*(-2));//(screenSize.w*(-2));
		float yStartPos=yPos;
		float _yPos;
		//__android_log_print(ANDROID_LOG_INFO, "com.android.game", "!!refreshCoord!!");
		int k=0;
		for(int i=0;i<maxCountDigets;i++){
			_yPos=yStartPos;
			digetDiagonal[k].x=xPos;
			digetDiagonal[k].y=_yPos;
			xPos+=WDiget;
			_yPos-=HDiget;
			digetDiagonal[k+1].x=xPos;
			digetDiagonal[k+1].y=_yPos;
			/*__android_log_print(ANDROID_LOG_INFO, "com.android.game", "Diget=%d",i);
			__android_log_print(ANDROID_LOG_INFO, "com.android.game", "digetDiagonal[%d] {x=%f,y=%f}",k,digetDiagonal[k].x,digetDiagonal[k].y);
			__android_log_print(ANDROID_LOG_INFO, "com.android.game", "digetDiagonal[%d] {x=%f,y=%f}",k+1,digetDiagonal[k+1].x,digetDiagonal[k+1].y);*/
			k+=2;
		}
		refreshCoord=false;
	}
	int number=value;
	int diget=0;
	int k=(maxCountDigets)*2-1;
	Texture tex;
	tex.setUseAlpha(true);
	for(int i=maxCountDigets-1;i>=0;i--){
		diget=number%10;
		number/=10;
		tex.setDiagonal(Diagonal(digetDiagonal[k-1],digetDiagonal[k]));
		tex.setID(texDigets[diget]);
		tex.draw();
		k-=2;
	}
}
