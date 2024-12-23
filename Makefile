# Variables
# The compiler
SYSCONF_LINK = g++
CPPFLAGS     =
LDFLAGS      =
# External libraries, lm is a maths library
LIBS         = -lm
# Where to outbut bin ary
DESTDIR = ./
# Name of final output
TARGET  = main

# generates athe list of all object files relating to cpp files in the directory
# wildcard *.cpp = find all cpp files
# $(patsubst %.cpp,%.o,...) replaces cpp with o
OBJECTS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all: $(DESTDIR)$(TARGET)

#  $(DESTDIR)$(TARGET) depends on all object files
#  -Wall: Enables all common warnings
# e.g. g++ -Wall -o main file1.o file2.o -lm
$(DESTDIR)$(TARGET): $(OBJECTS)
	$(SYSCONF_LINK) -Wall $(LDFLAGS) -o $(DESTDIR)$(TARGET) $(OBJECTS) $(LIBS)

#  e.g. g++ -Wall -c file1.cpp -o file1.o
$(OBJECTS): %.o: %.cpp
	$(SYSCONF_LINK) -Wall $(CPPFLAGS) -c $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)
	-rm -f *.tga