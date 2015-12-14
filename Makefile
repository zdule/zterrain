CXX = g++
FLAGS =  -lGL -lGLEW -lGLU -lSDL
INCLUDES = -Iinclude
SOURCES := $(shell find * -name "*.cpp")
all : $(SOURCES)
	g++ $(INCLUDES) $^ -o Terrain  $(FLAGS)
