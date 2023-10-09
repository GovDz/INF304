/*
Author: BOUDELLAL Feth-Ellah 
type_pile.c (c) 2023
Desc: UGA - L2 - INF304 
Created:  2023-10-09T13:00:32.204Z
*/

#include <stdio.h> 
#include "type_pile.h"

void creer_pile(PileEntiers *p){
    p->n = 0;
}

int est_vide(PileEntiers *p){
    return p->n == 0; // La elle va retourner True si la pile n'a rien 
}

int sommet(PileEntiers *p){
    return p->tab[p->n];
    
}

int taille(PileEntiers *p){
    return p->n;
}

void print(PileEntiers *p){
    for (int i = p->n ; i > 0; i--)
    {
        printf("%d\n",p->tab[i]);
    }
    
    
}

void vider(PileEntiers *p){
    p->n = 0;
}

void empiler(PileEntiers *p, int x){
    if (taille(p) < TAILLE_MAX)
    {
        p->tab[p->n+1] = x;
        p->n = p->n + 1;
    }
    
}

int depiler(PileEntiers *p){
    if (!est_vide(p))
    {
        p->n = p->n - 1;
    }
    return p->tab[p->n];
    }
