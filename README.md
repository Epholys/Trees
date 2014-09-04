# Trees
## A Random Tree Generator in C++14 and SFML2.1

![Image](../master/media/screenshot/example.png?raw=true)

### Features

* Randomized parameters including colors, angle, number of leaves and branches, etc...
* Some parameters customizable via a simple menu
* Zoom and movement via the mouse
* Send differents parameters for each iteration of growth

### Control

* _Space_ to generate a new Tree
* _Enter_ to grow some subbranches
* _F_ to grow the leaves (end of all the iterations)
* _Mouse's wheel_ to zoom
* _Mouse's left button_ to move th view

### How do I get this ?

* _Windows_ : download the bin/Tree.win32.zip, unzip it where you like and simply launch the .exe file (make sure the media folder and all the .dll are in the same folder than the executable) (NOTE: Windows version isn't the last version of the program)
* _Linux_ : it is recommended to compile your own version. You must have a C++11-compliant compiler (like g++4.8.2) and SFML2.1 libraries installed

### Want to contribute? Read this !

_I have the bad habit not to comment my code, so be warned._

Some features I'd like to see :
* More optimisation than a simple culling, as this program has an INSANE amount of draw calls
* Cleaner random generations with more options to Random*Parameters and in the menu
* Everything you want to add :)

### Additionnal information

Workspace : Ubtuntu 14.04LTS, g++4.8.2, SFML2.1, emacs24.3.1, x86-64 & Windows8 with VirtualBox
