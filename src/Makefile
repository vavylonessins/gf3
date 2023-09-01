build:
	clear
	g++ main.cpp -o ../dist/gf3 -Wall -Werror -Wno-unused-variable -Wno-array-bounds -O3 -Wextra -Wno-unused-parameter

run: build
	chmod +x ../dist/gf3
	clear
	@../dist/gf3
	@echo

clear:
	rm ../dist/gf3
