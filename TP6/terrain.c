
#include "terrain.h"
#include "robot.h"
#include <stdio.h>
#include <string.h>

erreur_terrain lire_terrain(FILE *f, Terrain *t, int *x, int *y) {
  int l, h;   // Dimensions du terrain
  int rx, ry; // Coordonnées initiales du robot

  if (f == NULL) {
    return ERREUR_FICHIER;
  }

  // Lecture de la largeur
  // À compléter
    //fscanf(f,"%d",&l);
    // fscanf renvoie le nombre de valeurs lues, et la valeur EOF si la
    //fin du fichier est atteinte avant la première valeur lue
    if(fscanf(f,"%d",&l)  != 1){
        printf("Opssy :(, y'a un erreur, impossible de lire la longeur");
        return  ERREUR_LECTURE_LARGEUR;
    }
    if( fscanf(f,"%d",&h)  != 1){
        printf("Opssy :(, y'a un erreur, impossible de lire la hauteur");
        return  ERREUR_LECTURE_HAUTEUR;
    }
    if (t->hauteur >= DIM_MAX){
        printf("Opssy :(, La hauteur doit être inferieur à DIM MAX.\n");
        return ERREUR_HAUTEUR;
    }
    if (t->largeur >= DIM_MAX){
        printf("Opssy :(, La largeur doit être inferieur à DIM MAX.\n");
        return ERREUR_LARGEUR;
    }


  // Lecture de la hauteur
  // À compléter
    fscanf(f,"%d",&h);
    t->largeur = l;
    t->hauteur = h;
     int isposition = 0;
  // Lecture du terrain
    fscanf(f,"\n");
  // À compléter
  for(int i=0; i < h; i++){
        for(int j=0; j < l; j++){
            char c;
            fscanf(f,"%c",&c);
            if(c == EOF){
                return ERREUR_LIGNES_MANQUANTES;
            }
                switch(c){
                    case '.':
                        t->tab[i][j] = LIBRE;
                        break;
                    case '#':
                        t->tab[i][j] = ROCHER;
                        break;
                    case '~':
                        t->tab[i][j] = EAU;
                        break;
                    case 'C':
                        rx = i;
                        ry = j;
                        isposition++;
                        t->tab[i][j] = LIBRE;

                        break;
                    case '\n':
                        if(j != 0){
                            printf("ERREUR LIGNE COURTE");
                            return ERREUR_LIGNE_TROP_COURTE;
                        }
                        break;
                    default:
                        printf("ERREUR Caractere inexistant");
                        return ERREUR_CARACTERE_INEXISTANT;
                }
        }
      fscanf(f,"\n");
  }

  // Initialisation de la position du robot
  if(!isposition){
      return ERREUR_POSITION_ROBOT_MANQUANTES; // pas de position
  }
  // À compléter
    *x = rx;
    *y = ry;
  return OK;
}
int largeur(Terrain *t){
    return t->largeur;
}
int hauteur(Terrain *t){
    return t->hauteur;
}
/* Indique si la case de coordonnées (x,y) est libre
   Renvoie vrai ssi les 3 conditions suivantes sont vraies :
    - 0 <= x < largeur
    - 0 <= y < hauteur
    - t.tab[x][y] = LIBRE */
int est_case_libre(Terrain *t, int x, int y){
    //if(0 < x <= largeur(t) && 0 <= y < hauteur(t) && t->tab[x][y] == LIBRE){ return 1;}
    //else return 0;
    return (0 < x <= largeur(t) && 0 <= y < hauteur(t) && t->tab[x][y] == LIBRE);
}
void afficher_terrain(Terrain *t){
    for (int i = 0; i < hauteur(t); i++){
        for(int j = 0; j < largeur(t); j++){
            switch (t->tab[i][j]) {
                case LIBRE :
                    printf(".");
                    break;
                case EAU :
                    printf("~");
                    break;
                case ROCHER :
                    printf("#");
                    break;
                default:
                    break;
            }
        }
        printf("\n");
}
}
void ecrire_terrain(FILE *f, Terrain *t, int x, int y){
        fprintf(f,"%d %d ",t->largeur,t->hauteur);// Dimension
            t->tab[x][y] = 'C';
    for (int i = 0; i < hauteur(t); i++){
        for(int j = 0; j < largeur(t); j++){
            switch (t->tab[i][j]) {
                case LIBRE :
                    if(i == x && j == x){
                        fprintf(f, "C");
                    }
                    else{
                        fprintf(f,".");
                    }
                    break;
                case EAU :
                    fprintf(f,"~");
                    break;
                case ROCHER :
                    fprintf(f,"#");
                    break;
                default:
                    break;
            }
        }
        fprintf(f,"\n");
    }

    }

/* À compléter */
