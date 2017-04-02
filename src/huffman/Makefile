CC = gcc
EXEC =
CFLAGS = -Wall -I ../../include -std=c99
SRCS = test_tree.c occurences.c ../../lib/tree_lib.c ../../lib/liste_lib.c ../../lib/bin_io.c  tree_from_length.c  huffman.c ../../lib/canonical.c
OBJS = $(SRCS:.c=.o)



all : test_tree.exe test_gilles.exe


#.c.o :
#	$(CC) $(CFLAGS) -c $<

test_gilles.o : test_gilles.c
	$(CC) $(CFLAGS) -c $<

test_tree.exe : $(OBJS)
	-@echo Creation de "l'executable" $@
	$(CC) $(OBJS) -o $@

test_gilles.exe : test_gilles.o
	-@echo Creation de "l'executable" $@
	$(CC) test_gilles.o occurences.o ../../lib/tree_lib.o ../../lib/liste_lib.o ../../lib/bin_io.o  tree_from_length.o  huffman.o -o $@

clean :
	@echo "Suppression des objets"
	-rm *.o *~ *.hf *.unhf
