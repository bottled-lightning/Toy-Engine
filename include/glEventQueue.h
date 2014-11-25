#ifndef GLEVENTQUEUE_H_
#define GLEVENTQUEUE_H_

class glEventChannel;

class glEventQueue {
public:
    glEventQueue(glEventChannel &channel)
        : _channel(channel) { }
private:
    glEventChannel &_channel;
};

#endif
