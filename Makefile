CC := clang

SDL2_INCLUDE_PATH := # put path here
SDL2_LIB_PATH := # put path here

CFLAGS = -c -std=c17 -O3
LDFLAGS = -O3 -lSDL2 -lm

SRC = ${wildcard src/*.c}
OBJ = ${SRC:.c=.o}
EXEC := bin/mandelbrot_c

all: ${SRC} ${OBJ} ${EXEC}

${EXEC}: ${OBJ}
	${CC} -I${SDL2_INCLUDE_PATH} -L${SDL2_LIB_PATH} ${LDFLAGS} $^ -o $@

%.o: %.c ${HDR}
	${CC} ${CFLAGS} $< -o $@

clean:
	rm src/*.o ${EXEC}