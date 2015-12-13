CXX = gcc
CPPFLAGS = -O2 -Wall -Wextra 
CPP_FILES := $(wildcard *.cpp)
OBJ_FILES = $(patsubst %.cpp,obj/%.o,$(CPP_FILES))


obj/%.o: $ %.cpp
    $(CXX) $(CPPFLAGS) -o $@

executable : $(OBJ_FILES) foo.a
    $(CXX) $(CPPFLAGS) $^ -o $@ 
