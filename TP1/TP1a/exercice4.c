#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argv[1] == NULL || argc > 3 || argc < 2) {
        printf("Veuillez entrer exactement 1 fichier\nl'usage:./exercice4 NomFichier \n");
    }
    else {
        FILE *fichier = fopen(argv[1], "r");
        char buffer[1000] ;
        int somme = 0;
        while (fgets(buffer, sizeof(buffer), fichier) != NULL) {
            char day[3];
            char month[20];
            char year[5];
            if (sscanf(buffer, "%2s %19s %4s", day, month, year) == 3) {
                int dayInt = atoi(day);
                int yearInt = atoi(year);
                somme += (dayInt + yearInt);
            }
        }

        printf("%d\n", somme);

        fclose(fichier);
        return 0;
    }


    }


/*
 * #include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argv[1] == NULL || argc > 3 || argc < 2) {
        printf("Veuillez entrer exactement 1 fichier\nl'usage:./exercice4 NomFichier \n");
    }
    else {
        FILE *fichier = fopen(argv[1], "r");
        char buffer[1000] ;
        int i = 0, somme = 0;
        while (fgets(buffer,1000, fichier)!= NULL) {
                somme += atoi(buffer);
        }
        printf("%d\n", somme);


        }
    }

 */