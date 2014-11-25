#include "../include/glEventChannel.h"
#include "../include/glTaskManager.h"
#include "../include/glEvent.h"

#include <iostream>

void glTaskManager::sendStartEvent() {
    _channel.broadcast(std::move(glStartEvent()));
    _running = true;
}
