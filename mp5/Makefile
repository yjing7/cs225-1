#*****************************************************
#  CS225 Fall 2006 MP5 Makefile
#
#  File originally written by Matt Buchanan in Fall 1995
#
#*****************************************************


#**************************************************************************
# List of .o files that EXENAME depends on.  Edit as appropriate for MP.

OBJS = png.o rgbapixel.o quadtree.o quadtree_given.o main.o


#**************************************************************************
# Change this line if you don't like 'a.out'.

EXENAME = mp5


#**************************************************************************
# Macros defining the C/C++ compiler and linker.

COMPILER = g++
WARNINGS = -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow
COMPILER_OPTS = -c -g -O0 -Wfatal-errors -Werror $(WARNINGS)
LINKER = g++


#**************************************************************************
# Rules for building EXENAME from OBJS and OBJS from your source.

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LINKER) $(OBJS) -lpng -o $(EXENAME)

png.o : png.cpp png.h rgbapixel.h
	$(COMPILER) -c $(COMPILER_OPTS) png.cpp

rgbapixel.o : rgbapixel.h rgbapixel.cpp
	$(COMPILER) -c $(COMPILER_OPTS) rgbapixel.cpp

quadtree.o : quadtree.cpp quadtree.h quadtree_given.h png.h rgbapixel.h
	$(COMPILER) -c $(COMPILER_OPTS) quadtree.cpp

quadtree_given.o : quadtree_given.cpp quadtree.h quadtree_given.h png.h rgbapixel.h
	$(COMPILER) -c $(COMPILER_OPTS) quadtree_given.cpp

main.o : main.cpp png.h rgbapixel.h quadtree.h
	$(COMPILER) -c $(COMPILER_OPTS) main.cpp

clean:
	-rm -f *.o $(EXENAME) mp5.out out*.png

tidy:
	-rm -rf ./doc

