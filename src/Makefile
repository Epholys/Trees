# This is the Makefile for Doinakra, an Arkanoid clone, done in SFML 2.1

CC = g++
IDIR = ../include/
CFLAGS = -std=c++1y -Wall -Wextra -pedantic
IFLAGS = -I$(IDIR)
LFLAGS = -lsfml-window -lsfml-graphics -lsfml-system
OPTFLAGS := -O2
BUGFLAGS :=

TARGET := Trees
TARGETDIR = ../
OBJECTS = 	main.o Application.o Node.o Branch.o Leaf.o \
			RandomParameters.o Utility.o Tree.o

empty :=
space := $(empty) $(empty)

all : executable

executable : $(OBJECTS)
	$(CC) $(BUGFLAGS) $(CFLAGS) $(OPTFLAGS) $(OBJECTS) -o $(TARGET) $(LFLAGS)
	mv $(TARGET) $(TARGETDIR)

debug : OPTFLAGS :=
debug : BUGFLAGS := -g
debug : TARGET += .debug
debug : TARGET := $(subst $(space),,$(TARGET))
debug : executable

%.o : %.cpp
	$(CC) $(BUGFLAGS) $(CFLAGS) $(OPTFLAGS) -c $< $(IFLAGS) $(LFLAGS)

clean :
	rm *.o
