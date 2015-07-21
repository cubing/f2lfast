HEADERS = cube_solver/cubepos.h
SOURCES = cube_solver/cubepos.cpp f2lfast.cpp
DEPENDENCIES = $(shell find . -iname "*.cpp")

# TODO: -O3
FLAGS = -DHALF -O2 -std=c++11

TARGET = f2lfast

.PHONY: all
all: test

${TARGET}: ${HEADERS} ${SOURCES} ${DEPENDENCIES}
	g++ ${FLAGS} ${SOURCES} -o ${TARGET}

.PHONY: test
test: ${TARGET}
	./${TARGET} --test


# Javascript options.
JS_OPT = -O2
JS_MEMORY = -s TOTAL_MEMORY=536870912
JS_USE_ASM_JS = 1
JS_FUNCTIONS = "['_solve']"

.PHONY: js
js: f2lfast-em.js

f2lfast-em.js:
	emcc -Wall \
		$(JS_OPT) -s \
		ASM_JS=$(JS_USE_ASM_JS) \
		$(JS_MEMORY) \
		-s EXPORTED_FUNCTIONS=$(JS_FUNCTIONS) \
		-o ./f2lfast-em.js \
		cube_solver/cubepos.cpp f2lfast.cpp
