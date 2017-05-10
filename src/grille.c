/**
 * \file grille.c
 * \brief code pour les grilles
 * \author Lucas Schott
 */

#include "grille.h"

/**
 * \fn void init_grille_from_file (char * filename, grille* g)
 * \brief initialise la grille selon le fichier texte donné en argument
 * \param filename un pointeur sur le fichier texte contenenant les données de la grille
 * \param g un pointeur sur la grille à initialiser
 * \return void
 * \post effet de bord, modification de la grille pointé par g
 */
void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0,non_viable=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante_nv(i,j,*g,0);
	}
	
	fscanf(pfile, "%d", & non_viable);
	for (n=0; n< non_viable; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_non_viable(i,j,*g);
	}
	
	fclose (pfile);
	return;
}

/**
 * \fn void copie_grille (grille gs, grille gd)
 * \brief copie la grille gs dans gd
 * \param gs une grille initialisé
 * \param gd une autre grille initialisé
 * \return void
 * \pre les deux grilles doivent etre alloué et avoir la même taille
 * \post effet de bord: modification de gd 
 */
void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}

/**
 * \fn void alloue_grille (int l, int c, grille *g)
 * \brief alloue une grille de taille l*c, et initialise toutes les cellules à mortes
 * \param l un entier, le nombre de lignes de la grille
 * \param c un entier, le nombre de colonnes de la grille
 * \param g un pointeur sur une grille
 * \return void
 * \post allocation de memoire, necessite l'utilisation de la fonction libere_grille
 */
void alloue_grille (int l, int c, grille* g)
{
	g->nbl = l;
	g->nbc = c;
	int i,j;
	g->cellules = (int**) malloc(l * sizeof(int*));
	for(i=0;i<l;i++)
	{
		g->cellules[i] = (int*) malloc(c * sizeof(int));
		for(j=0; j<c; j++)
		{
			g->cellules[i][j]=0;
		}
	}
	return;
}

/**
 * \fn void libere_grille (grille *g)
 * \brief libère une grille
 * \param g un pointeur sur une grille
 * \return  void
 * \pre libere de la mémoire, doit etre utilisé après un alloue_grille
 */
void libere_grille (grille* g)
{
	int i;
	for (i=0; i<g->nbl; i++)
		free(g->cellules[i]);
	free(g->cellules);
	return;
}
