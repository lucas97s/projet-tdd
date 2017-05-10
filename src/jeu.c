/**
 * \file jeu.c
 * \brief code pour les fonctions du jeu
 * \author Lucas Schott
 */

#include "jeu.h"


/**
 * \fn int  compte_voisins_vivants_cyclique (int i, int j, grille g)
 * \brief compte le nombre de voisins vivants d'une cellules avec une grille cyclique
 * \param i ligne
 * \param j colonne
 * \param g grille
 * \return le nombre de voisins vivants
 */
int compte_voisins_vivants_cyclique (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);
	return v; 
}


/**
 * \fn int compte_voisins_vivants_non_cyclique (int i, int j, grille g)
 * \brief compte le nombre de voisins vivants d'une cellules avec une grille non cyclique
 * \param i lign
 * \param j colonne
 * \param g grille
 * \return le nombre de voisins vivants
 */
int compte_voisins_vivants_non_cyclique ( int i, int j, grille g)
{

	int a, b, c = 0;
	for (a= i - 1; a <= i + 1; a++)
	{
		for (b=j-1; b <= j + 1; b++)
		{
			if ( a == i && b == j)
			{
				continue;
			}
			if ( a >=0 && a < g.nbl && b >=0 && b < g.nbc)
			{
				c+= est_vivante(a, b, g);
			}
		}
	}
	return c;
}


/**
 * \fn int grilles_identiques (grille * g1, grille * g2)
 * \brief test si deux grilles sont identiques
 * \param g1 pointeur sur la premiere grille
 * \param g2 pointeur sur la deuxieme grille
 * \return int un boléen 1 si les grilles sont identiques, 0 sinon
 */
int grilles_identiques(grille * g1, grille * g2)
{
	int i,j,res=0;
	int nbl,nbc;
	if ( g1->nbl == g2->nbl && g1->nbc == g2->nbc )
	{
		res=1;
		nbl=g1->nbl;
		nbc=g2->nbc;
		for (j=0; j<nbc; j++)
		{
			for (i=0; i<nbl; i++)
			{
				if ( g1->cellules[i][j] != g2->cellules[i][j] )
				{
					return 0;
				}
			}
		}
	}
	return res;
}



/**
 * \fn int est_oscillante (grille * g, grille * gc, int cyclique, int vieillissante)
 * \brief teste si une grille est oscillante, en faisant évoluer une grille depuis un point de départ jusqu'à ce qu'elle trouveun shéma de répétition
 * \param g pointeur sur la premiere grille
 * \param gc pointeur sur la deuxieme grille
 * \cyclique entier definissant si la grille est cyclique ou non
 * \vieillissement entier definissant si les cellules vieillissent ou non
 * \return int un boléen 1 si la grille est oscillante, 0 si elle ne l'est pas
 * \pre g et gc doivent avoir la meme dimension
 * \post effet de bord: modification de g et de gc
 */
int est_oscillante(grille * g, grille * gc, int cyclique, int vieillissement)
{
	int compteur=0;
	grille g3;
	alloue_grille(g->nbl, g->nbc, &g3);
	copie_grille(*g, g3);
	do
	{
		evolue(&g3, gc, cyclique, vieillissement);
		compteur ++;
		if ( compteur > 100 )
		{
			compteur = 0;
			break;
		}
	}while ( grilles_identiques(g,&g3) == 0 );
	libere_grille(&g3);
	return compteur;
}


/**
 * \fn void evolue (grille *g, grille *gc, int cyclique, int vieillissement)
 * \brief fait evoluer les cellules selon leu environnement et leur état
 * \param g pointeur sur la premiere grille
 * \param gc pointeur sur la deuxieme grille
 * \cyclique entier definissane si la grille est cyclique ou non
 * \vieillissement entier definissant si les cellules vieillissent ou non
 * \return void
 * \pre g et gc doivent avoir la meme dimension
 * \post effet de bord: modification de g et de gc
 */
void evolue (grille *g, grille *gc, int cyclique, int vieillissement){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int (*compte_voisins_vivants) (int, int, grille);
	void (*set_vivante) (int, int, grille, int);
	if (cyclique == 1) {
		compte_voisins_vivants = compte_voisins_vivants_cyclique;}
	else { 
		compte_voisins_vivants = compte_voisins_vivants_non_cyclique;}
	if (vieillissement == 1)
	{
		set_vivante = set_vivante_v;
	}
	else
	{
		set_vivante = set_vivante_nv;
	}
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			if (est_non_viable(i,j,*g)) continue;
			else
			{
				v = compte_voisins_vivants (i, j, *gc);
				if (est_vivante(i,j,*g)) 
				{ // evolution d'une cellule vivante
					if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
					else
					{
						if (est_vieille(i,j,*g,gc->cellules[i][j]))
						{ set_morte(i,j,*g);}
						else
						{ set_vivante(i,j,*g,g->cellules[i][j]);}
					}
				}
				else 
				{ // evolution d'une cellule morte
					if ( v==3 ) set_vivante(i,j,*g,0);
				}
			}
		}
	}
	return;
}
