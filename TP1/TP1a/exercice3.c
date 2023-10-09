#include <stdio.h>
int main(int argc, char *argv[]) {
    if (argv[2] == NULL || argc > 3 || argc < 2) {
        printf("Veuillez entrer exactement deux fichiers\nl'usage:./exercice2 fichier1 fichier2\n");
    }
    else {
        FILE *fichier1 = fopen(argv[1], "r");
        FILE *fichier2 = fopen(argv[2], "a+");
        if (fichier1 == NULL) {
            printf("Impossible d'ouvrir le fichier Source\n");
        }
        int temp = 0;
        while (temp != EOF) {
           temp = fgetc(fichier1);
            fprintf(fichier2, "%c", temp);
        }
        printf("C fait :) ");
        fclose(fichier1);
        fclose(fichier2);
        return 0;
    }
}