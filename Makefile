build: main.c liste.c
	gcc -Wall -Wextra -std=c99 main.c liste.c stive.c cozi.c tree.c -o lanParty

clean:
	rm -f *.o lanParty

.PHONY: pack clean