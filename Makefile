all:
	cc -Wall -Wextra -Werror *.c -lmpg123 -lao -o sound

clean:
	rm sound

re: clean all
