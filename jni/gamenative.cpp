#include <jni.h>
#include <sys/time.h>
#include <time.h>
#include <android/log.h>
#include <stdlib.h>
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#include "score.h"
#include "note.h"
#include "texture.h"
#include "graphics.h"
#include "action.h"
#include "gamemanager.h"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void
Java_com_android_game_GameGLSurfaceView_nativeOnTouch(JNIEnv*  env, jobject  thiz, jint event, jfloat x, jfloat y);
JNIEXPORT void
Java_com_android_game_GameRenderer_nativeRender( JNIEnv*  env );
JNIEXPORT void
Java_com_android_game_GameRenderer_nativeResize( JNIEnv*  env, jobject  thiz, jint w, jint h );
JNIEXPORT void
Java_com_android_game_GameRenderer_nativeInit( JNIEnv*  env );
JNIEXPORT void
Java_com_android_game_GameRenderer_nativePushTexture(JNIEnv* env, jobject thiz, jintArray arr, jint w, jint h) {
	int len = w * h;
    int i = 0;
    int* iBody = (int *)env->GetIntArrayElements(arr, 0);
    int texID;
    len *= 4;
    char* cImgData = new char[len];
    char* cBody = (char*)iBody;
	// This converts the ARGB data from Java into RGBA data OpenGL can use.
	 for(i = 0; i < len; i += 4) {
		 cImgData[i] = cBody[i + 2];
		 cImgData[i + 1] = cBody[i + 1];
		 cImgData[i + 2] = cBody[i];
		 cImgData[i + 3] = cBody[i + 3];
	 }
	glGenTextures(1,(GLuint*)&texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)cImgData);
	GameManager::getInstance().setTexture(texID);
	delete [] cImgData;
}
#ifdef __cplusplus
}
#endif

void* GameThread(void*) {
	GameManager::getInstance().loop();
	return (void*)0;
}

/* Call to initialize the graphics state */
JNIEXPORT void
Java_com_android_game_GameRenderer_nativeInit( JNIEnv*  env ) {
	GameManager::getInstance().init();
	pthread_t thread = 0;
	pthread_create(&thread, NULL, &GameThread, NULL);
	pthread_detach(thread);
}

JNIEXPORT void
Java_com_android_game_GameRenderer_nativeResize( JNIEnv*  env, jobject  thiz, jint w, jint h ) {
	GameManager::lock();
	GameManager::getInstance().onResize(w, h);
	GameManager::unlock();
}

/* Call to render the next GL frame */
JNIEXPORT void
Java_com_android_game_GameRenderer_nativeRender( JNIEnv*  env ) {
	GameManager::lock();
	GameManager::getInstance().draw();
	GameManager::unlock();
}

JNIEXPORT void
Java_com_android_game_GameGLSurfaceView_nativeOnTouch(JNIEnv*  env, jobject  thiz,jint event,jfloat x,jfloat y) {
	GameManager::lock();
	TouchAction touchAct;
	touchAct.act = (TouchAction::Action)event;
	touchAct.x = x;
	touchAct.y = y;
	GameManager::getInstance().onTouchEvent(touchAct);
	GameManager::unlock();
}


