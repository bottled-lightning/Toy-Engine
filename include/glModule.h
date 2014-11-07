#ifndef GLMODULE_H_
#define GLMODULE_H_

#include "glEventChannel.h"
// glSystemLocator?

class glModule {
public:
	virtual ~glModule() { }
	virtual void startup() { }
	virtual void cleanup() { }

	static glEventChannel channel;
};

glEventChannel glModule::channel;

#endif
