#ifndef _ACTION_H_
#define _ACTION_H_

struct TouchAction {
	enum Action {
		CANCEL=3,
		MOVE=2,
		UP=1,
		DOWN=0}	act;
	float x;
	float y;
};

/*struct TouchActionList {
	struct TouchAction action[100];
	int count;
} touchActionList;*/
#endif
