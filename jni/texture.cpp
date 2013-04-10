#include "texture.h"

void Texture::draw(){
		glDisable(GL_DITHER);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glEnable(GL_TEXTURE_2D);
		if(useAlpha){
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GEQUAL, 0.5);
		}
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindTexture(GL_TEXTURE_2D, idTexture);
	    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glVertexPointer(2, GL_FLOAT, 0, coords);
		glTexCoordPointer(2, GL_FLOAT, 0, coordsTex);
		/*for(int k=0;k<8;k+=2){
			__android_log_print(ANDROID_LOG_INFO, "com.android.game", "coords pos[%d]={%f,%f}",k, coords[k], coords[k+1]);
			__android_log_print(ANDROID_LOG_INFO, "com.android.game", "coordsTex pos[%d]={%f,%f}",k, coordsTex[k], coordsTex[k+1]);
		}*/
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, coordIndex);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		if(useAlpha)
			glDisable(GL_ALPHA_TEST);
		glDisable(GL_TEXTURE_2D);
}
