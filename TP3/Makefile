CC = clang -Wall -g

all: ensembles

ensembles.o: operations_ens.h sac.h type_ensemble.h
	$(CC) -c ensembles.c

sac.o: sac.c sac.h
	$(CC) -c sac.c

recherche.o: recherche.c recherche.h
	$(CC) -c recherche.c

operations_ens.o: operations_ens.c operations_ens.h
	$(CC) -c operations_ens.c

ensembles: sac.o operations_ens.o ensembles.o recherche.o
	$(CC) sac.o operations_ens.o ensembles.o recherche.o -o ensembles

clean:
	rm -f ensembles *.o
