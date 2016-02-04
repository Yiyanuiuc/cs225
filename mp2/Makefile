EXENAME = testscene
OBJS = testscene.o scene.o image.o png.o rgbapixel.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

testscene.o : testscene.cpp scene.h image.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) testscene.cpp

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
