COMPILER = g++
COMPILER_FLAGS = -c -g -O0 -Wall -Werror
LINKER = g++

all: testimage testscene

testscene: testscene.o scene.o png.o rgbapixel.o image.o
	$(LINKER) testscene.o scene.o png.o rgbapixel.o image.o -lpng -o testscene
testscene.o: testscene.cpp scene.h png.h rgbapixel.h image.h
	$(COMPILER) $(COMPILER_FLAGS) testscene.cpp
scene.o: scene.h png.h rgbapixel.h image.h
	$(COMPILER) $(COMPILER_FLAGS) scene.cpp

testimage : testimage.o png.o rgbapixel.o image.o
	$(LINKER) testimage.o png.o rgbapixel.o image.o -lpng -o testimage
testimage.o: testimage.cpp png.h rgbapixel.h image.h
	$(COMPILER) $(COMPILER_FLAGS) testimage.cpp
png.o: png.h
	$(COMPILER) $(COMPILER_FLAGS) png.cpp
rgbapixel.o : rgbapixel.h png.h
	$(COMPILER) $(COMPILER_FLAGS) rgbapixel.cpp
image.o: image.h png.h
	$(COMPILER) $(COMPILER_FLAGS) image.cpp
clean: 
	rm -f *.o testimage testscene;

