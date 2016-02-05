EXENAME = testscene testimage testscene-asan testimage-asan

OBJSS = testscene.o scene.o image.o png.o rgbapixel.o
OBJSI = testimage.o image.o png.o rgbapixel.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

all : $(EXENAME)

#$(EXENAME) : $(OBJS)
#	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

testscene-asan : $(OBJSS)
	$(LD) $(OBJSS) $(LDFLAGS) $(ASANFLAGS) -o testscene-asan

testimage-asan : $(OBJSI)
	$(LD) $(OBJSI) $(LDFLAGS) $(ASANFLAGS) -o testimage-asan

testscene : $(OBJSS)
	$(LD) $(OBJSS) $(LDFLAGS) -o testscene

testimage : $(OBJSI)
	$(LD) $(OBJSI) $(LDFLAGS) -o testimage

testscene.o : testscene.cpp scene.h image.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) testscene.cpp

testimage.o : testimage.cpp image.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) testimage.cpp

scene.o : scene.cpp scene.h image.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) scene.cpp

image.o : image.cpp image.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) image.cpp

png.o : png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

clean :
	-rm -f *.o $(EXENAME)
