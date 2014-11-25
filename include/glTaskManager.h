#ifndef GLTASKMANAGER_H_
#define GLTASKMANAGER_H_

#include "glEvent.h"

class glEventChannel;

class glTaskManager {
public:

    // utility events
    struct glStartEvent : glEvent { };
    struct glStopEvent  : glEvent { };

    glTaskManager(glEventChannel &channel) :
        _channel(channel), _running(false) { }

    void sendStartEvent();
    bool shouldClose() { return !_running; }
    void pollEvents() { }

private:
    glEventChannel &_channel;
    bool _running;
};

#endif
