#include "environnement.h"
#include "interprete.h"
#include "programme.h"
#include "generation_terrains.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void gestion_erreur_terrain(erreur_terrain e) {
    switch (e) {
        case OK:
            break;
        case ERREUR_FICHIER:
            printf("Erreur lecture du terrain : erreur d'ouverture du fichier\n");
            exit(1);
        case ERREUR_LECTURE_LARGEUR:
            printf("Erreur lecture du terrain : erreur de lecture de la largeur\n");
            exit(1);
        case ERREUR_LECTURE_HAUTEUR:
            printf("Erreur lecture du terrain : erreur de lecture de la hauteur\n");
            exit(1);
        case ERREUR_LARGEUR_INCORRECTE:
            printf("Erreur lecture du terrain : largeur incorrecte\n");
            exit(1);
        case ERREUR_HAUTEUR_INCORRECTE:
            printf("Erreur lecture du terrain : hauteur incorrecte\n");
            exit(1);
        case ERREUR_CARACTERE_INCORRECT:
            printf("Erreur lecture du terrain : caractère incorrect\n");
            exit(1);
        case ERREUR_LIGNE_TROP_LONGUE:
            printf("Erreur lecture du terrain : ligne trop longue\n");
            exit(1);
        case ERREUR_LIGNE_TROP_COURTE:
            printf("Erreur lecture du terrain : ligne trop courte\n");
            exit(1);
        case ERREUR_LIGNES_MANQUANTES:
            printf("Erreur lecture du terrain : lignes manquantes\n");
            exit(1);
        case ERREUR_POSITION_ROBOT_MANQUANTE:
            printf(
                    "Erreur lecture du terrain : position initiale du robot manquante\n");
            exit(1);
    }
}
void displayUsage(char *programName) {
    printf("Utilisation : %s <fichier_programme> <N> <L> <H> <d> <graine> <nb_step_max> <fichier_res>\n", programName);
}

void handleProgramError(const char *errorMessage) {
    printf("Erreur : %s\n", errorMessage);
}

void displayResults(int totalTests, int successes, int failures, int falls, int crashes, int blocked, float avgSteps) {
    printf("Tests total : %d\n", totalTests);
    printf("Réussites : %d\n", successes);
    printf("Échecs : %d\n", failures);
    printf("  - Chutes dans l'eau : %d\n", falls);
    printf("  - Écrasements contre un rocher : %d\n", crashes);
    printf("  - Perdus : %d\n", blocked);
    printf("Nombre moyen de pas pour les réussites : %.2f\n", avgSteps);
}

void affichage_position_programme(erreur_programme e) {
    int i;
    printf("Ligne %d, colonne %d :\n", e.num_ligne, e.num_colonne);
    printf("%s\n", e.ligne);
    /* Impression de e.num_colonne-1 espaces */
    for (i = 1; i < e.num_colonne; i++) {
        printf(" ");
    }
    /* Impression d'un curseur de position */
    printf("^\n");
}

void gestion_erreur_programme(erreur_programme e) {
    switch (e.type_err) {
        case OK_PROGRAMME:
            break;
        case ERREUR_FICHIER_PROGRAMME:
            printf("Erreur lecture du programme : erreur d'ouverture du fichier\n");
            exit(2);
        case ERREUR_BLOC_NON_FERME:
            printf("Erreur lecture du programme : bloc non fermé\n");
            exit(2);
        case ERREUR_FERMETURE_BLOC_EXCEDENTAIRE:
            printf("Erreur lecture du programme : fermeture de bloc excédentaire\n");
            affichage_position_programme(e);
            exit(2);
        case ERREUR_COMMANDE_INCORRECTE:
            printf("Erreur lecture du programme : commande incorrecte\n");
            affichage_position_programme(e);
            exit(2);
    }
}

int main(int argc, char **argv) {
    Environnement envt;
    Programme prog;
    erreur_programme errp;
    etat_inter etat;
    resultat_inter res;
    Terrain T;
    Robot R;

    char *fichier_programme, *fichier_res;
    int N, l, h, graine, nb_step_max;
    float dObst;
    int nb_sorti = 0, nb_bloque = 0, nb_tombe = 0, nb_ecrase = 0, somme_pas = 0, pas;

    if (argc < 9) {
        displayUsage(argv[0]);
        return 1;
    }
    fichier_programme = argv[1];
    N = strtol(argv[2], NULL, 10);
    l = strtol(argv[3], NULL, 10);
    h = strtol(argv[4], NULL, 10);
    dObst = strtof(argv[5], NULL);
    graine = strtol(argv[6], NULL, 10);
    nb_step_max = strtol(argv[7], NULL, 10);
    fichier_res = argv[8];

    srand(graine);

    FILE *f = fopen(fichier_res, "w");
    if (f == NULL) {
        handleProgramError("Impossible d'ouvrir le fichier de résultats en écriture.");
        return 1;
    }
    fprintf(f, "%d\n", N);

    for (int i = 0; i < N; i++) {
        R.o = Est;
        R.x = l / 2;
        R.y = h / 2;
        envt.r = R;
        do {
            generation_aleatoire(&T, l, h, dObst);
        } while (!existe_chemin_vers_sortie(&T));
        envt.t = T;

        errp = lire_programme(&prog, fichier_programme);
        gestion_erreur_programme(errp);

        init_etat(&etat);
        pas = 0;
        do {
            res = exec_pas(&prog, &envt, &etat);
            pas++;
        } while (res == OK_ROBOT && pas < nb_step_max);

        switch (res) {
            case OK_ROBOT:
                fprintf(f, "-1\n");
                nb_bloque++;
                break;
            case SORTIE_ROBOT:
                fprintf(f, "%d\n", pas);
                nb_sorti++;
                somme_pas += pas;
                break;
            case ARRET_ROBOT:
                fprintf(f, "-1\n");
                nb_bloque++;
                break;
            case PLOUF_ROBOT:
                fprintf(f, "-2\n");
                nb_tombe++;
                break;
            case CRASH_ROBOT:
                fprintf(f, "-3\n");
                nb_ecrase++;
                break;
            case ERREUR_PILE_VIDE:
            case ERREUR_ADRESSAGE:
            case ERREUR_DIVISION_PAR_ZERO:
                fprintf(f, "-4\n");
                break;
        }
    }
    fclose(f);
    displayResults(N, nb_sorti, nb_bloque + nb_ecrase + nb_tombe, nb_tombe, nb_ecrase, nb_bloque,
                   (nb_sorti > 0) ? (float)somme_pas / (float)nb_sorti : 0.0);
    printf("Somme des pas : %d\n", somme_pas);

    return 0;
}

