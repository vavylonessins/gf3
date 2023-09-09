build:
	clear
	g++ main.cpp -o ../dist/gf3 -Wall -Werror -Wno-unused-variable -Wno-array-bounds -Wno-unused-parameter -Wno-sequence-point -O3 -Wextra

run: build
	chmod +x ../dist/gf3
	clear
	@../dist/gf3
	@echo

debug:
	clear
	g++ main.cpp -o ../dist/gf3 -Wall -Werror -Wno-unused-variable -Wno-array-bounds -Wno-unused-parameter -Wno-sequence-point -O3 -Wextra -g
	chmod +x ../dist/gf3
	@gdb ../dist/gf3
	@echo

clear:
	rm ../dist/gf3
