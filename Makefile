all:
	jison ksolve_def_parser.jison -o ksolve_def_parser.js

test:
	node ksolve_def_parser.js puzzles/222.def

.PHONY: deploy
deploy:
	rsync -avz \
		--exclude .DS_Store \
		--exclude .git \
		--exclude .gitignore \
		--exclude .gitmodules \
		./ \
		cubing.net:~/cubing.net/ksolve-js-svg/
	echo "\nDone deploying. Go to https://www.cubing.net/ksolve-js-svg/\n"
