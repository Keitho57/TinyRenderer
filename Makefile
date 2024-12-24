# Variables
# The compiler
SYSCONF_LINK = g++
CPPFLAGS     = -I./include -std=c++11
LDFLAGS      =
# External libraries, lm is a maths library
LIBS         = -lm
# Where to outbut bin ary
DESTDIR = ./
# Name of final output
TARGET = main

OBJDIR = build

# generates athe list of all object files relating to cpp files in the directory
# wildcard *.cpp = find all cpp files
# $(patsubst %.cpp,%.o,...) replaces cpp with o
SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(SOURCES:src/%.cpp=$(OBJDIR)/%.o)

all: $(DESTDIR)$(TARGET)

# Make sure build/ exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

#  $(DESTDIR)$(TARGET) depends on all object files
#  -Wall: Enables all common warnings
# e.g. g++ -Wall -o main file1.o file2.o -lm
$(DESTDIR)$(TARGET): $(OBJECTS)
	$(SYSCONF_LINK) -Wall $(LDFLAGS) -o $(DESTDIR)$(TARGET) $(OBJECTS) $(LIBS)

#  e.g. g++ -Wall -c file1.cpp -o file1.o
$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	$(SYSCONF_LINK) -Wall $(CPPFLAGS) -c $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f $(DESTDIR)$(TARGET)
	-rm -f *.tga
	-rmdir $(OBJDIR)