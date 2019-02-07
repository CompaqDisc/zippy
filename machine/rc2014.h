#ifndef ZIPPY_MACHINE_RC2014_H_
#define ZIPPY_MACHINE_RC2014_H_

#include "machine.h"

class RC2014: public Machine {
public:
	RC2014();

	void Start();
	void TaskThread();
};

#endif