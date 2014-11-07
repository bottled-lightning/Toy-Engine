Toy-Engine
==========

Simple Game Engine

- src directoy contains glEntry.cpp which holds the main function
- modules directory is a plugin directory. The classes in here all inherit from glModule (defined in include directory) and are compiled into a dynamic library. 
  - This dynamic library is loaded into glEntry and instantiates all classes defined within it
