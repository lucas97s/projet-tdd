/**
 * \file main.c
 * \brief code principal
 * \author Lucas Schott
 */

#include <stdio.h>
#include "grille.h"
#include "io.h"
#include "jeu.h"

/**
 * \fn int main (int argc, char ** argv)
 * \brief fonction principale du programme
 * \param argc le nombre d'arguments
 * \param argv un fichier texte contenant les données pour initialiser la grille
 * \return o un code de retour standard
 */
int main (int argc, char ** argv) {

	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	affiche_grille(g);
	
	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
