FLAGS = -Wall -Werror -Wextra

cat: clean
	gcc $(FLAGS) src/cat/cat.c -o cat

clean:
	rm -rf cat
