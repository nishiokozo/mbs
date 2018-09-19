#.SURFIXES:	.cpp

TAR=main.exe

OBJS=\
	obj/main.o \
	obj/framework.o \
	obj/vector.o \
	obj/matrix.o \
	obj/font.o \
	obj/enemy.o \
	obj/floor.o \
	obj/light.o \
	obj/camera.o \
	obj/key.o \
	obj/fighter.o \
	obj/mouse.o \
	obj/line.o \
	obj/core.o \
	obj/missile.o \
	obj/ctrl.o \
	obj/bomb.o \
	obj/test.o \

#LIBS=-lglut32 -lopengl32 -lglu32  -static-libgcc -static-libstdc++ 
LIBS= -lopengl32 -lglu32  -static-libgcc -static-libstdc++ glut32.lib

FLGS = \
	-c \
	-m64 \
	-std=c++14 \
	-Wall \
	-Wno-unknown-pragmas \
	-Wno-unused-function \
	-Wno-unused-variable \

INCS = \
	-Ic:/msys64 \


#CC	= clang++
CC	= g++


$(TAR)	:	obj $(OBJS) $(SHDR)
	$(CC) -o $(TAR) $(OBJS) $(LIBS)

obj/%.o:%.cpp
	$(CC)  $(FLGS) $(INCS) $< -o $@

obj:
	mkdir obj

clean:
	rm -f *.exe
	rm -rf obj

