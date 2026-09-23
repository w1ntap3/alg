.PHONY: orchard

orchard:
	gcc --std=c99 -pipe -Wall -O3 -c ./orchard/main.c -o ./orchard/main.o
	gcc ./orchard/main.o -o ./orchard/orchard
	./orchard/orchard
