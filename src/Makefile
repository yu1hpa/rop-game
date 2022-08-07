TARGET=main
ifeq ($(NODEBUG), 1)
	SRCS=main.c primitive.c deltatime.c easing.c components.c keyboard.c keybind.c map.c
	HEADERS=
	CCFLAGS=-Wall
else
	SRCS=main.c primitive.c deltatime.c easing.c components.c keyboard.c keybind.c map.c debug.c
	HEADERS=debug.h
	CCFLAGS=-Wall -DEBUG
endif

OBJS=${SRCS:.c=.o}


UNAME=$(shell uname)

ifeq ($(UNAME), Darwin)
	CC=gcc-11
	LD=gcc-11
	INCPATH=-I../../include/ -L../../lib -lglpng
	FRAMEWORK=-framework OpenGL -framework GLUT $(INCPATH)
else ifeq ($(UNAME), Linux)
	CC=gcc
	LD=gcc
	LIBS=-lglut -lGLU -lGL
else
	CC=i686-pc-cygwin-gcc
	LD=i686-pc-cygwin-gcc
	OBJS+=icon.o
	INCPATH=-I/usr/include/opengl
	LIBS=-lglut32 -lglu32 -lopengl32
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(OBJS) -o $@ $(FRAMEWORK) $(LIBS)

.c.o:
	$(CC) $(CCFLAGS) $(INCPATH) -c $<

$(OBJS): $(HEADERS) Makefile

clean:
	rm -f $(TARGET) $(OBJS)
