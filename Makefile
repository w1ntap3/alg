PATH_TO_ALG := /home/wintape/javid/practice/alg/orchard
PATH_TO_DANGLING := /home/wintape/javid/practice/alg/dangling

.PHONY: orchard dangling clean

orchard:
	gcc --std=c99 -pipe -Wall -O3 -c $(PATH_TO_ALG)/main.c -o $(PATH_TO_ALG)/main.o
	gcc $(PATH_TO_ALG)/main.o -o $(PATH_TO_ALG)/orchard
	zip -j $(PATH_TO_ALG)/orchard.zip $(PATH_TO_ALG)/main.c

dangling:
	gcc --std=c99 -pipe -Wall -O3 -c $(PATH_TO_DANGLING)/main.c -o $(PATH_TO_DANGLING)/main.o
	gcc $(PATH_TO_DANGLING)/main.o -o $(PATH_TO_DANGLING)/dangling
	zip -j $(PATH_TO_DANGLING)/dangling.zip $(PATH_TO_DANGLING)/main.c

clean:
	rm -f $(PATH_TO_ALG)/main.o $(PATH_TO_ALG)/orchard $(PATH_TO_ALG)/orchard.zip $(PATH_TO_DANGLING)/main.o $(PATH_TO_DANGLING)/dangling $(PATH_TO_DANGLING)/dangling.zip
