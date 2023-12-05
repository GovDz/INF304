#include "environnement.h"
#include "interprete.h"
#include "programme.h"

#include <stdio.h>
#include <stdlib.h>

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
    erreur_terrain errt;
    erreur_programme errp;
    etat_inter etat;
    resultat_inter res;
    char fichier_terrain[DIM_MAX];
    char fichier_programme[DIM_MAX];
    int nb_execution;
    char even_attendu,NF_attendu,ofinal;
    int pas = 0;
    int cord_x,cord_y,fx,fy;

    if (argc < 2) {
        printf("Usage: %s <fichier>\n", argv[0]);
        return 1;
    }

    FILE *f;

    f = fopen(argv[1], "r");

    if (f == NULL){
        return ERREUR_FICHIER;
    }

    if (fscanf(f, "%s", fichier_terrain) == 0){
        return ERREUR_FICHIER;
    }
    if (fscanf(f, "%s", fichier_programme) == 0){
        return ERREUR_FICHIER;
    }
    if (fscanf(f, "%d\n", &nb_execution) == 0){
        return ERREUR_FICHIER;
    }
    if (fscanf(f, "%c\n", &even_attendu) == 0){
        return ERREUR_FICHIER;
    }
    if (even_attendu == 'N' || even_attendu == 'F')
    {
        fscanf(f, "%d", &fx);
        fscanf(f, "%d", &fy);
        fscanf(f, "\n%c", &NF_attendu);
    }

    /* Initialisation de l'environnement : lecture du terrain,
       initialisation de la position du robot */
    errt = initialise_environnement(&envt, fichier_terrain);
    gestion_erreur_terrain(errt);

    /* Lecture du programme */
    errp = lire_programme(&prog, fichier_programme);
    gestion_erreur_programme(errp);

    /* Initialisation de l'état */
    init_etat(&etat);
    do {
        res = exec_pas(&prog, &envt, &etat);
        /* Affichage du terrain et du robot */
        afficher_envt(&envt);
        pas++;
    } while (res == OK_ROBOT && pas <= nb_execution);
    /* Affichage du résultat */
    switch (res) {
        case OK_ROBOT:
            if (even_attendu == 'N' || even_attendu == 'F')
            {
                position(&envt.r, &cord_x, &cord_y);
                switch (orient(&envt.r))
                {
                    case Nord:
                        ofinal = 'N';
                        break;
                    case Est:
                        ofinal = 'E';
                        break;
                    case Sud:
                        ofinal = 'S';
                        break;
                    case Ouest:
                        ofinal = 'O';
                        break;
                }
                if (cord_x == fx && cord_y == fy && ofinal == NF_attendu)
                    printf("OK\n");
                else
                    printf("Echec");
            }
            else
            printf("Robot sur une case libre, programme non terminé (ne devrait pas "
                   "arriver)\n");
            break;
        case SORTIE_ROBOT:
            if(even_attendu == 'S'){
                printf("OK");
                return 1;
            } else printf("ROBOT SORTIE\n");
            break;
        case ARRET_ROBOT:
            if (even_attendu == 'N' || even_attendu == 'F')
            {
                position(&envt.r, &cord_x, &cord_y);
                switch (orient(&envt.r))
                {
                    case Nord:
                        ofinal = 'N';
                        break;
                    case Est:
                        ofinal = 'E';
                        break;
                    case Sud:
                        ofinal = 'S';
                        break;
                    case Ouest:
                        ofinal = 'O';
                        break;
                }
                if (cord_x == fx && cord_y == fy && ofinal == NF_attendu)
                    printf("OK");
                else
                    printf("Echec, %d and %d\n",cord_x,cord_y);
            }
            else
            printf("Robot sur une case libre, programme terminé :-/\n");
            break;
        case PLOUF_ROBOT:
            if(even_attendu == 'P'){
                printf("OK");
                return 1;
            }
            else printf("Le robot est tombé dans l'eau :-(\n");
            break;
        case CRASH_ROBOT:
            if(even_attendu == 'O'){
                printf("OK");
                return 1;
            }
            printf("Le robot s'est écrasé sur un rocher X-(\n");
            break;
        case ERREUR_PILE_VIDE:
            printf("ERREUR : pile vide\n");
            break;
        case ERREUR_ADRESSAGE:
            printf("ERREUR : erreur d'adressage\n");
            break;
        case ERREUR_DIVISION_PAR_ZERO:
            printf("ERREUR : division par 0\n");
            break;
    }
}
