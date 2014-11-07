#include "../include/glEventChannel.h"
#include "../include/glEventManager.h"
#include "../include/glModule.h"

#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include <thread>

const std::string modules_dynamic_library_path = "modules.dll";
const int FRAMES_PER_SECOND = 60;

std::vector<std::unique_ptr<glModule>> loadModules(const std::string &modules_path);
void startupModules(std::vector<std::unique_ptr<glModule>> &modules);
void cleanupModules(std::vector<std::unique_ptr<glModule>> &modules);

int main(int argc, char **argv) {
	// dynamically load objects from modules folder
	std::vector<std::unique_ptr<glModule>> modules = loadModules(modules_dynamic_library_path);

	// manager class must listen on this statically created channel
	glEventManager manager(glModule::channel);

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::milliseconds temp;

	startupModules(modules);
	// maintain loop to keep FPS of around 60
	while(!manager.shouldClose()) {
		start = std::chrono::system_clock::now();
		manager.pollEvents();
		end = std::chrono::system_clock::now();

		temp = end - start - (float) 1000 / FRAMES_PER_SECOND;
		if(temp > std::chrono::milliseconds(0))
			std::this_thread::sleep_for(temp);
	}
	cleanupModules(modules);

	return 0;
}

// takes advantage of RVO - return value optimization
std::vector<std::unique_ptr<glModule>> loadModules(const std::string &modules_path) {
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
