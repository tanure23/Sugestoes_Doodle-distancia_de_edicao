all: main.c utils.c
	gcc -o tp2 main.c utils.c -I. -lm -Wall -Wextra -Werror -std=c99 -pedantic -O2
	# gcc -o tp2 main.c utils.c -I. -lm -Wall -Wextra -std=c99 -pedantic -O2