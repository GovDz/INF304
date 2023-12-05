//
// Created by Feth-Ellah on 12/1/23.
//


// J'ai utilisé des sources externes ( StackOverflow , Google, AI ... ) pour m'aider dans ce TP (09)
#include "observateur.h"
Etats initial()
{
    return Initial;
}

Etats transition(Etats e, Alphabets c) {
    switch (e) {
        case Initial:
            if (c == A) return Erreur;
            if (c == G || c == D) return Initial;
            if (c == M) return mesure;
            break;

        case mesure:
            if (c == A) return Initial;
            if (c == M || c == G || c == D) return mesure;
            break;

        case Erreur:
            return Erreur;
    }
    return Erreur;
}
int BoolFinal(Etats e) {
    return e != Erreur;
}