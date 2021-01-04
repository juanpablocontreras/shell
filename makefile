shellmake: shell.c
	gcc -o shell shell.c shellfunc.c constants.c -I