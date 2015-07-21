HEADERS = cube_solver/cubepos.h
SOURCES = cube_solver/cubepos.cpp f2lfast.cpp
DEPENDENCIES = $(shell find . -iname "*.cpp")

# TODO: -O3
FLAGS = -DHALF -O2 -std=c++11

TARGET = f2lfast

.PHONY: all
all: ${TARGET}

${TARGET}: ${HEADERS} ${SOURCES} ${DEPENDENCIES}
	g++ ${FLAGS} ${SOURCES} -o ${TARGET}

.PHONY: test
test: ${TARGET}
	./${TARGET} --test