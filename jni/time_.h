#ifndef _TIME__H_
#define _TIME__H_

#include <time.h>

class Time{
public:
	static unsigned long getCurrentms(){
		struct timeval  now;
		gettimeofday(&now, NULL);
		return (long)(now.tv_sec*1000 + now.tv_usec/1000);
	}
};
#endif
