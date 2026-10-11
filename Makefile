PATH_TO_ALG := /home/wintape/javid/practice/alg/orchard

.PHONY: orchard clean

orchard:
	gcc --std=c99 -pipe -Wall -O3 -c $(PATH_TO_ALG)/main.c -o $(PATH_TO_ALG)/main.o
	gcc $(PATH_TO_ALG)/main.o -o $(PATH_TO_ALG)/orchard
	zip -j $(PATH_TO_ALG)/orchard.zip $(PATH_TO_ALG)/main.c

clean:
	rm -f $(PATH_TO_ALG)/main.o $(PATH_TO_ALG)/orchard $(PATH_TO_ALG)/orchard.zip
