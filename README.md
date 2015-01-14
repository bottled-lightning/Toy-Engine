Toy Engine
==========
Toy Engine is a game or rendering engine that can be used from the command line. The tool looks for an environment variable TOYENGINE_CFG that contains the path to the configuration file for the project. `make modules` will compile a modules shared library from the modules plugins directory whose path must be specified in the configuration file.

As-is the current project compiles and runs a simple mandelbrot using two glModules, and as such a more complete project will likely use more modules. The modules require OpenGL 4.0 or higher to run and use glfw amd GLEW.

How to Build
============
- Install Boost Signals2, Boost Program Options, Boost Log
- For the demo modules, install OpenGL libraries, glfw and GLEW
- `cmake [-DBOOST_ROOT=path/to/boost]`
- `make all`
- `make modules` to build libmodules.so or .dll

Note: Due to limitations in cmake, adding modules to your project requires you to run cmake again before running `make modules`

Double note: MinGW on Windows specifically only partially supports the C++11 features we are planning to use so, at least on Windows, please use MSVC 13 and up or [MinGW-w64](http://mingw-w64.sourceforge.net/download.php#mingw-builds)

How to Run
==========
Toy-Engine executable looks for configuration file path in environment variable or labeled on the command line. The configuration file must have the path to the modules shared library outputted by `make modules` in order to dynamically load each plugin, or it must be specified on command line. Command line will always take precedence.

###Usage
- `export TOYENGINE_CFG=~/config.cfg && ./Toy-Engine`
- `./Toy-Engine -f ~/config.cfg`
