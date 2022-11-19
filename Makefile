CC := clang

SDL2_INCLUDE_PATH := # put path here
SDL2_LIB_PATH := # put path here

CFLAGS := -O3
LDFLAGS := -O3 -lSDL2 -lm -I${SDL2_INCLUDE_PATH} -L${SDL2_LIB_PATH}
SRC_DIR := ./src
BIN_DIR := ./bin

SRCS := ${shell find ${SRC_DIR} -name '*.c'}
HDRS := ${SRCS:%.c=%.h}
OBJS := ${SRCS:%=${BIN_DIR}/%.o}
EXEC := ${BIN_DIR}/mandelbrot_c

${EXEC}: ${OBJS}
	${CC} ${OBJS} ${LDFLAGS} -o $@

${BIN_DIR}/%.c.o: %.c
	mkdir -p ${dir $@}
	${CC} -c $< ${CFLAGS} -o $@

.PHONY: clean

clean:
	rm -rf ${BIN_DIR}/*