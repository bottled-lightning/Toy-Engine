cmake_minimum_required(VERSION 2.6)
project(config_parser)

# necessary if files are built by our custom command
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_custom_command(
  OUTPUT config_parser.tab.cc config_parser.tab.hh lex.yy.c location.hh position.hh stack.hh
  COMMAND flex ${CMAKE_CURRENT_SOURCE_DIR}/config_scanner.l
  COMMAND bison ${CMAKE_CURRENT_SOURCE_DIR}/config_parser.yy
)

# don't want to use gcc for lex.yy.c
set_source_files_properties(lex.yy.c PROPERTIES LANGUAGE CXX)

add_library(config_parser SHARED
  config_driver.cpp
  config_parser.tab.cc
  lex.yy.c
)
