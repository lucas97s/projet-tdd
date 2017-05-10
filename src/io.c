/**
 * \file io_t.c
 * \brief code pour les entrees et sorties mode texte
 * \author Lucas Schott
 */

#include "io.h"

/**
 * \fn void affiche_trait (int c)
 * \brief affiche des trais pour délimiter la grille
 * \param c, le nombre de colonnesde la grille
 * \return void
 * \post fonction d'affichage
 */
void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

/**
 * \fn void affiche_ligne (int c, int * ligne)
 * \brief affiche les lignes de cellules selon leu état (mortes, vivante, age)
 * \param c nomber de colonnes
 * \param ligne pointeur sur la ligne a afficher
 * \return void
 * \post fonction d'affichage
 */
void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) {printf ("|   ");}
		else if  (ligne[i] == -1 ) {printf ("| X ");}
		else {printf ("| %d ", ligne[i]);}
	printf("|\n");
	return;
}

/**
 * \fn void affiche_grille (grille g)
 * \brief affiche une grille au complet
 * \param g la grille à afficher
 * \return void
 * \post fonction d(affichage
 */
void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}
/**
 * \fn void efface_grille (grille g)
 * \brief efface une grille de l'ecran
 * \param g la grille a effacer
 * \return void
 * \post fonction d'affichage
 */
void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}

/**
 * \fn void debut_jeu (grille *g, grille *gc)
 * \brief focntion qui lance le jeu de la vie et qui gère l'interraction avec l'utilisateur
 * \param g pointeur sur une grille
 * \param gc pointeur sur une grille
 * \return void
 * \pre g et gc doivent avoir les meme dimensions
 * \post fonction contenant des fonctions d'affichage
 */
void debut_jeu(grille *g, grille *gc){
	char c = getchar();
	int compteur = 0; 
	int vieillissement = 0;
	int cyclique = 1;
	int periode;
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g,gc,cyclique,vieillissement);
				efface_grille(*g);
				printf("etape: %d ; ", ++compteur);
				if (cyclique) printf("cyclique ");
				else printf("non cyclique ");
				if (vieillissement) printf("avec vieillissement");
				else printf("sans vieillissement");
				affiche_grille(*g);
				break;
			}
			case 'c' :
			{
				if (cyclique) { cyclique = 0;}
				else { cyclique = 1;}
				break;
			}
			case 'v' :
			{
				if (vieillissement) {vieillissement = 0;}
				else {vieillissement = 1;}
				break;
			}
			case 'o' :
			{
				periode = est_oscillante(g,gc, cyclique, vieillissement);
				if ( periode > 0) printf("la grille est oscillante de periode %d", periode);
				else printf("la grille n'est pas oscillante         ");
			}
			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}
