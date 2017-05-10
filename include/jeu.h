/**
 * \file jeu.h
 * \brief header pour les fonctions du jeu
 * \author Lucas Schott
 */

#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

// modulo modifié pour traiter correctement les bords i=0 et j=0
// dans le calcul des voisins avec bords cycliques
static inline int modulo(int i, int m) {return (i+m)%m;}

int compte_voisins_vivants_cyclique (int i, int j, grille g);

int compte_voisins_vivants_non_cyclique (int i, int j, grille g);

int grilles_identiques(grille * g1, grille * g2);

int est_oscillante(grille * g, grille * gc, int cyclique, int vieillissement);

void evolue (grille *g, grille *gc, int cyclique, int vieillissement);

#endif
