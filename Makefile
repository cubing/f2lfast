SOURCES = cube_solver/cubepos.h cube_solver/cubepos.cpp f2lfast.cpp
FLAGS = -DHALF -O3

f2lfast: ${SOURCES}
	g++ ${FLAGS} ${SOURCES}
	mv a.out f2lfast