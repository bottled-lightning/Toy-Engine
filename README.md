Toy-Engine
==========

Simple Game Engine

- src directory contains glEntry.cpp which holds the main function
- modules directory is a "plugin" directory. The classes in here all inherit from glModule (defined in include directory) and are compiled into a dynamic library.
  - This dynamic library is loaded into glEntry and instantiates all classes defined within it
  - INI file used to specify program options for each module, as well as place module dynamic library is defined and the classes to be compiled

(NOTE: the included Makefile works for linux only. On Windows you are expected to compile using CL for Visual Studio or maybe cygwin. The Makefile should work for Cygwin)

###Inspirations

For inspiration we give thanks to http://gameprogrammingpatterns.com/ and http://www.grandmaster.nu/blog/
