#include <stdio.h>
int main(int argc, char *argv[]) {
    if (argv[2] == NULL || argc > 3 || argc < 2) {
        printf("Veuillez entrer exactement deux arguments\nl'usage:./exercice 1 2\n");
    }
    else {
        for (int i = 1; i < argc; i++) {
        printf("Argument %d: %s\n",i, argv[i]);
        }
    }
}