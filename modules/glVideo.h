#ifndef GLVIDEO_H_
#define GLVIDEO_H_

#include "../include/glModule.h"

class glVideo : public glModule {
public:
    using glModule::glModule;
    // this constructor should not be necessary in gcc
	glVideo(const char *name)
		: glModule(name) { }
	virtual ~glVideo() { }

	virtual void startup() override { glModule::startup(); }
	virtual void cleanup() override { glModule::cleanup(); }
};

DEFINE_MODULE(glVideo);

#endif
