HEADERS = cube_solver/cubepos.h
SOURCES = cube_solver/cubepos.cpp f2lfast.cpp

# TODO: -O3
FLAGS = -DHALF -O2 -std=c++11

TARGET = f2lfast

.PHONY: all
all: test

# TODO: Remove .PHONY line once done testing.
.PHONY: ${TARGET}
${TARGET}: ${HEADERS} ${SOURCES}
	g++ ${FLAGS} ${SOURCES} -o ${TARGET}

.PHONY: test
test: ${TARGET}
	./${TARGET}