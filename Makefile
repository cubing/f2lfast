all:
	jison ksolve_def_parser.jison -o ksolve_def_parser.js

test:
	node ksolve_def_parser.js puzzles/222.def