FLAGS = -Wall -Werror -Wextra

all: my_cat my_grep

my_cat: clean
	gcc $(FLAGS) src/cat/cat.c -o my_cat

my_grep: clean
	gcc $(FLAGS) src/grep/grep.c -o my_grep

clean:
	rm -rf my_cat
	rm -rf my_grep
