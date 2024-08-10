all:
	cc *.c -lmpg123 -lao -o sound

clean:
	rm sound

re: clean all
