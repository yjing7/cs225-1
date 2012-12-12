EXENAME=testFills
OBJS=testFills.o animation.o rgbapixel.o png.o solidColorPicker.o gridColorPicker.o gradientColorPicker.o rainbowColorPicker.o

COMPILER = g++
WARNINGS = -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow
COMPILER_OPTS = -c -g -O0 -Wfatal-errors -Werror $(WARNINGS)
LINKER = g++

all: $(EXENAME) testStackQueue

$(EXENAME): $(OBJS)
	$(LINKER) $(OBJS) -lpng -o $(EXENAME)

testStackQueue: testStackQueue.o
	$(LINKER) -o testStackQueue testStackQueue.o

testStackQueue.o: testStackQueue.cpp stack.h stack.cpp queue.h queue.cpp
	$(COMPILER) $(COMPILER_OPTS) testStackQueue.cpp

testFills.o: testFills.cpp $(wildcard *.h)
	$(COMPILER) $(COMPILER_OPTS) testFills.cpp

png.o: png.h png.cpp
	$(COMPILER) $(COMPILER_OPTS) png.cpp

rgbapixel.o: rgbapixel.h rgbapixel.cpp
	$(COMPILER) $(COMPILER_OPTS) rgbapixel.cpp

animation.o: animation.cpp animation.h
	$(COMPILER) $(COMPILER_OPTS) animation.cpp

solidColorPicker.o: colorPicker.h solidColorPicker.cpp solidColorPicker.h
	$(COMPILER) $(COMPILER_OPTS) solidColorPicker.cpp

gridColorPicker.o: colorPicker.h gridColorPicker.cpp gridColorPicker.h
	$(COMPILER) $(COMPILER_OPTS) gridColorPicker.cpp

gradientColorPicker.o: colorPicker.h gradientColorPicker.cpp gradientColorPicker.h
	$(COMPILER) $(COMPILER_OPTS) gradientColorPicker.cpp

rainbowColorPicker.o: colorPicker.h rainbowColorPicker.cpp rainbowColorPicker.h
	$(COMPILER) $(COMPILER_OPTS) rainbowColorPicker.cpp

doc: $(wildcard *.h) $(wildcard *.cpp)
	doxygen mp4.doxygen

clean:
	-rm -rf $(EXENAME) testStackQueue *.o images/ frames/ doc/ testStackQueue.out testFills.out

