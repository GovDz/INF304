//
// Created by Feth-Ellah on 12/1/23.
//

#ifndef TP07_OBSERVATEUR_H
#define TP07_OBSERVATEUR_H
typedef enum{ Initial,mesure,Erreur } Etats;
typedef enum{ A,D,G,M } Alphabets;
Etats initial();
Etats transition(Etats e, Alphabets c);
int BoolFinal(Etats e);
#endif //TP07_OBSERVATEUR_H
