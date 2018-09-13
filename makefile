.SURFIXES:	.cpp

TAR=main
SRCS=main.cpp \
	framework.cpp \
	vector.cpp \
	matrix.cpp \
	font.cpp \
	enemy.cpp \
	floor.cpp \
	light.cpp \
	camera.cpp \
	key.cpp \
	fighter.cpp \
	mouse.cpp \
	line.cpp \
	core.cpp \
	missile.cpp \
	ctrl.cpp \
	bomb.cpp \
	test.cpp 

#LIBS=-lglut32 -lopengl32 -lglu32  -static-libgcc -static-libstdc++ 
LIBS= -lopengl32 -lglu32  -static-libgcc -static-libstdc++ glut32.lib


$(TAR).exe	:	$(SRCS:.cpp=.o)
	g++ -m64 -o$(TAR) $^ $(LIBS)

.cpp.o:
#	clang++ -c -Wall -O3  $< -Ic:/msys64 -Wno-unused-variable -Wno-c++11-compat-deprecated-writable-strings -Wno-macro-redefined
	g++  -m64 -c -Wall -O3  $< -Ic:/msys64 -Wno-unknown-pragmas -Wno-unused-function
#	g++  -m64 -c -Wall -O3  $< -Ic:/msys64 
	
clean:
	rm *.o *.obj $(TAR) $(TAR).exe -f


