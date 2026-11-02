ALG_ROOT := /home/wintape/javid/practice/alg
PATH_TO_ALG := $(ALG_ROOT)/orchard
PATH_TO_DANGLING := $(ALG_ROOT)/dangling
PATH_TO_DRAWING := $(ALG_ROOT)/drawing_bin_tree

.PHONY: orchard dangling drawing_bin_tree clean

orchard:
	gcc --std=c99 -pipe -Wall -O3 -c $(PATH_TO_ALG)/main.c -o $(PATH_TO_ALG)/main.o
	gcc $(PATH_TO_ALG)/main.o -o $(PATH_TO_ALG)/orchard
	zip -j $(PATH_TO_ALG)/orchard.zip $(PATH_TO_ALG)/main.c

dangling:
	gcc --std=c99 -pipe -Wall -O3 -c $(PATH_TO_DANGLING)/main.c -o $(PATH_TO_DANGLING)/main.o
	gcc $(PATH_TO_DANGLING)/main.o -o $(PATH_TO_DANGLING)/dangling
	zip -j $(PATH_TO_DANGLING)/dangling.zip $(PATH_TO_DANGLING)/main.c

drawing_bin_tree:
	gcc --std=c99 -pipe -Wall -O3 -c $(PATH_TO_DRAWING)/main.c -o $(PATH_TO_DRAWING)/main.o
	gcc $(PATH_TO_DRAWING)/main.o -o $(PATH_TO_DRAWING)/drawing_bin_tree
	zip -j $(PATH_TO_DRAWING)/drawing_bin_tree.zip $(PATH_TO_DRAWING)/main.c

clean:
	rm -f $(PATH_TO_ALG)/main.o $(PATH_TO_ALG)/orchard $(PATH_TO_ALG)/orchard.zip $(PATH_TO_DANGLING)/main.o $(PATH_TO_DANGLING)/dangling $(PATH_TO_DANGLING)/dangling.zip $(PATH_TO_DRAWING)/main.o $(PATH_TO_DRAWING)/drawing_bin_tree $(PATH_TO_DRAWING)/drawing_bin_tree.zip
