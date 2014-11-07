#ifndef GLEVENTMANAGER_H_
#define GLEVENTMANAGER_H_

class glEventChannel;

class glEventManager {
public:
	glEventManager(glEventChannel &channel) :
		_channel(channel) { }

	bool shouldClose() { return true; }
	void pollEvents() { }

private:
	glEventChannel &_channel;
};

#endif
