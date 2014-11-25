#ifndef GLEVENTCHANNEL_H_
#define GLEVENTCHANNEL_H_

class glEvent;

class glEventChannel {
public:
    void broadcast(glEvent &event) { }
    void broadcast(glEvent &&event) { }
};

#endif
