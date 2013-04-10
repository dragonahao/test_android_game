LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := gamenative

LOCAL_CFLAGS := -DANDROID_NDK 

LOCAL_SRC_FILES := \
	graphics.h \
	graphics.cpp \
    score.h \
	score.cpp \
	note.h \
	note.cpp \
	texture.h \
	texture.cpp \
	gamemanager.h \
	gamemanager.cpp \
	action.h \
	gamenative.cpp \
	joystick.h \
	time_.h \
	
LOCAL_LDLIBS := -lGLESv1_CM -ldl -llog

include $(BUILD_SHARED_LIBRARY)