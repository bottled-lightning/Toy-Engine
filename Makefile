CC = g++

INCLUDE = -Iinclude/
LIBS = -lboost_program_options -ldl
LIBPATH =

FLAGS = -std=c++11 $(INCLUDE) $(LIBPATH) $(LIBS)
CFLAGS = -pedantic -Wall -Wextra

DEBUGFLAGS = -O0 -D _DEBUG -g
RELEASEFLAGS = -O2 -D NDEBUG -fwhole-program

TARGET = Toy-Engine
SOURCES = $(wildcard src/**/*.cpp src/*.cpp)
HEADERS = $(wildcard include/**/*.h include/*.h)
OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))

all: $(TARGET)

%.o: %.cpp $(HEADERS) $(COMMON)
	$(CC) $(FLAGS) $(CFLAGS) $(DEBUGFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(FLAGS) $(CFLAGS) $(DEBUGFLAGS)

release: $(SOURCES) $(HEADERS)
	$(CC) -o $(TARGET) $(SOURCES) $(FLAGS) $(CFLAGS) $(RELEASEFLAGS)

clean:
	rm -rf $(OBJECTS)
