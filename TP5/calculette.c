/*
Author: BOUDELLAL Feth-Ellah 
calculette.c (c) 2023
Desc: UGA - L2 - INF304 
Created:  2023-10-09T15:04:25.661Z
*/

#include <stdio.h>
#include "commandes_calculette.h"
#include "type_pile.h"

int addition(PileEntiers *p){
    int val1 = sommet(p);
    depiler(p);
    int val2 = sommet(p);
    depiler(p);
    val1 = val1 + val2;
    empiler(p,val1);
    return val1;
}
int soustraction(PileEntiers *p){
    int val1 = sommet(p);
    depiler(p);
    int val2 = sommet(p);
    depiler(p);
    val1 = val2 - val1;
    empiler(p,val1);
    return val1;
}
int multiplication(PileEntiers *p){
    int val1 = sommet(p);
    depiler(p);
    int val2 = sommet(p);
    depiler(p);
    val1 = val1 * val2;
    empiler(p,val1);
    return val1;
}
int division(PileEntiers *p){
    int val1 = sommet(p);
    depiler(p);
    int val2 = sommet(p);
    depiler(p);
    if(val2 != 0){
        val1 = val1 / val2;
        empiler(p,val1);
    }
    else
    {
      printf("Ooopsyyy, La division sur 0 n'est pas possible :( ");
    }
    return val1;
}

int main(int argc, char **argv) {
  FILE *fichier = NULL;
  if (argc != 2) {
    printf("mauvaise utilisation : donnez un nom de fichier en argument\n");
    return 0;
  }

  fichier = ouvrir_commandes(argv[1]);
  PileEntiers p;
  creer_pile(&p);

  commande command;

  int value;

  while (!fin_commandes(fichier)) {
    command = commande_suivante(fichier);
    print_commandes(command);
    switch (command.cmd) {
    case VIDER_PILE:
      vider(&p);
      break;
    case DEPILER_SOMMET:
      depiler(&p);
      break;
    case EMPILER_VALEUR:
      empiler(&p, command.arg);
      break;
    case EFFECTUER_ADDITION:
      value = addition(&p);
      break;
    case EFFECTUER_SOUSTRACTION:
      value = soustraction(&p);
      break;
    case EFFECTUER_MULTIPLICATION:
      value = multiplication(&p);
      break;
    case EFFECTUER_DIVISION:
      value = division(&p);
      break;
    case COMMANDE_INCORRECTE:
      printf("Commande incorrecte !\n");
      break;
    }
    print(&p);
    printf("\n");
  }
  fermer_commandes(fichier);
  return 0;
}
