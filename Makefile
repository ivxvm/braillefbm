CC      = gcc
CFLAGS  = -std=c18 -pedantic -Werror -g -lm
RM      = rm -f


default: all

all: braillefbm

braillefbm: ./src/braillefbm.c
	$(CC) $(CFLAGS) -o braillefbm ./src/braillefbm.c

clean veryclean:
	$(RM) braillefbm
