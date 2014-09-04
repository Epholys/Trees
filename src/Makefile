CC = g++
IDIR = ../include/
CFLAGS = -std=c++1y -Wall -Wextra -pedantic
IFLAGS = -I$(IDIR)
LFLAGS = -lsfml-system -lsfml-window -lsfml-graphics
OPTFLAGS := -O2
BUGFLAGS :=

TARGET := Trees
TARGETDIR = ../
OBJECTS = 	main.o Application.o Utility.o \
			Tree.o Node.o Branch.o Leaf.o RandomParameters.o \
			Component.o SliderMenu.o

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
