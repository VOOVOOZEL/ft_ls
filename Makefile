NAME = ls

FLAGS = -Wall -Werror -Wextra

all:
	gcc -I.. -o ls main.c -L. -lftprintf