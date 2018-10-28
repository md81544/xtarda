t: $(wildcard *.cpp)
	g++ -std=c++14 -O3 -Wall -Wextra -Werror -Wpedantic -o t $^ \
		-lsfml-graphics -lsfml-window -lsfml-system
