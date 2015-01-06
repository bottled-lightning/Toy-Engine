Toy Engine
==========
Toy Engine is a game or rendering engine that can be used from the command line. The tool looks for an environment variable TOYENGINE_CFG that contains the path to the configuration file for the project. `make modules` will compile a modules shared library from the modules plugins directory whose path must be specified in the configuration file. You may optionally employ flex and bison to create own config file grammar.

As-is the current project compiles and runs a simple mandelbrot using two glModules, and as such a more complete project will likely use more modules. The modules require OpenGL 4.0 or higher to run and use glfw amd GLEW.

How to Build
============
- install flex and bison (optional), Boost Signals2, Boost Program Options, Boost Log
- for the demo modules, install OpenGL libraries, glfw and GLEW
- (optional) configure flex and bison to generate custom grammar modules and `make configuration` (planned, not yet implemented!!!)
- `cmake -D BOOST_INCLUDE_PATH=/path/to/boost -D BOOST_LIB_PATH=/path/to/boost/lib`
- `make all`
- `make modules` to build modules.so or .dll

Note: Due to limitations in cmake, adding modules to your project requires you to run cmake again before running `make modules`
Double note: MinGW on Windows specifically only partially supports the C++11 features we are planning to use so, at least on Windows, please use MSVC 13 and up or [MinGW-w64](http://mingw-w64.sourceforge.net/download.php#mingw-builds)

MSVC++ will compile the project just fine, but the makefile will not support it.

###How to Use Custom Grammar
- edit provided flex and bison files and compile as normally
- `make configuration` to generate c header files and config_parser.so

How to Run
==========
Toy-Engine executable looks for configuration file path in environment variable or labeled on the command line. The configuration file must have the path to the modules shared library outputted by `make modules` in order to dynamically load each plugin.

###Usage
- `TOYENGINE_CFG=~/config.cfg && ./Toy-Engine`
- `./Toy-Engine -I ~/config.cfg`
