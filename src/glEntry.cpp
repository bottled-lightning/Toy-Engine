#include "../include/glEventChannel.h"
#include "../include/glEventManager.h"
#include "../include/glModule.h"

#include <iostream>
#include <memory>
#include <vector>
#include <chrono>

const int FRAMES_PER_SECOND = 60;

std::vector<std::unique_ptr<glModule>> loadModules();
void startupModules(std::vector<std::unique_ptr<glModule>> &modules);
void cleanupModules(std::vector<std::unique_ptr<glModule>> &modules);

int main(int argc, char **argv) {

	// dynamically load objects from modules folder
	std::vector<std::unique_ptr<glModule>> modules = loadModules();

	// manager class must listen on this statically created channel
	glEventManager manager(glModule::channel);

	startupModules(modules);
	while(!manager.shouldClose()) {
		manager.pollEvents();
		// management to keep framerate to 60Hz



	}
	cleanupModules(modules);

	return 0;
}

// takes advantage of RVO - return value optimization
std::vector<std::unique_ptr<glModule>> loadModules() {
	// dynamically load all objects in modules folder
	std::vector<std::unique_ptr<glModule>> modules;

	return modules;
}

void startupModules(std::vector<std::unique_ptr<glModule>> &modules) {
	for(auto &module : modules)
		module->startup();
}

void cleanupModules(std::vector<std::unique_ptr<glModule>> &modules) {
	for(auto &module : modules)
		module->cleanup();
}
