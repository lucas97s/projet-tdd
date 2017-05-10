/**
 * \file grille.h
 * \brief header pour les grilles
 * \author Lucas Schott
 */

#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * \struct grille
 * \brief Déclaration de la structure de grille
 */
typedef struct {
	int nbl;   /**< nombre de lignes*/
	int nbc;   /**< nombre de colonnes*/
	int** cellules;   /**< tableau de tableau d'entier, représentant l'état des cellules*/
} grille;
 
// alloue une grille de taille l*c, et initialise toutes les cellules à mortes
void alloue_grille (int l, int c, grille* g);

// libère une grille
void libere_grille (grille* g);

// alloue et initalise la grille g à partir d'un fichier
void init_grille_from_file (char * filename, grille* g);


// rend vivante la cellule (i,j) de la grille g, avec vieillissement
static inline void set_vivante_v(int i, int j, grille g, int age){g.cellules[i][j] = age + 1;}

// rend vivante la cellule (i,j) de la grille g, sans vieillissement
static inline void set_vivante_nv(int i, int j, grille g, int age){g.cellules[i][j] = 1;}

// rend non_viable la cellule(i,j) de la grille g
static inline void set_non_viable(int i, int j, grille g){g.cellules[i][j] = -1;}

// teste si la cellule (i,j) de la grille g est non_viable
static inline int est_non_viable(int i, int j, grille g){return g.cellules[i][j] == -1;}

// rend morte la cellule (i,j) de la grille g
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

// teste si la cellule (i,j) de la grille g est vivante
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] >= 1;}

// teste si la cellule (i,j) de la grille g est trop vieille pour vivre
static inline int est_vieille(int i, int j, grille g, int age){return g.cellules[i][j] >7;}

// recopie gs dans gd (sans allocation)
void copie_grille (grille gs, grille gd);

#endif
