#include "terrain.h"
#include <stdio.h>

int main(int argc, char **argv) {
  FILE *f;
  Terrain t;
  int x, y;

  if (argc < 2) {
    printf("Usage : %s <fichier>\n", argv[0]);
    return 1;
  }
  f = fopen(argv[1], "r");
  if(f == NULL){
        char *nomdefichier = argv[1];
        while (f == NULL){
            printf("Impossible d'ouvrir \"%s\" :(( Veuillez entrer un nom d'un fichier valid : \n",nomdefichier);
            scanf("%s", nomdefichier);
            f = fopen(nomdefichier, "r");
        }
  }
        // LA C EST POSSIBLE DE IGNORER LA DEUXIEME CONDITION CAR
        // LA DEUXIEME CONDITION EST VERIFIEE DE LA PREMIERE CONDITION
  else {
      if (lire_terrain(f, &t, &x, &y) == OK) {
          fclose(f);
          afficher_terrain(&t);
          printf("Position initiale du robot : (%d, %d)\n", x, y);
      };
      return 0;
    }
}