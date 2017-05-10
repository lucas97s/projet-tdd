

/**
 * \file io_g.c
 * \brief code pour les entrees et sorties mode graphique
 * \author Lucas Schott
 */

#include "io_g.h"
#include <string.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>

#define SIZE 50


/**
 * \fn void affiche_ligne (int c, int * ligne)
 * \brief affiche les lignes de cellules selon leu état (mortes, vivante, age)
 * \param c nomber de colonnes
 * \param ligne pointeur sur la ligne a afficher
 * \return void
 * \post fonction d'affichage
 */
void affiche_ligne (int c, int* ligne, cairo_t *cr, int y){
	int i;
	for (i=0; i<c; ++i) 
	{
		if (ligne[i] == 0 )
		{
			cairo_rectangle(cr, SIZE+(SIZE+1)*i, SIZE+(SIZE+1)*y, SIZE, SIZE);
			cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
			cairo_fill(cr);
		}
		else if  (ligne[i] == -1 )
		{
			cairo_rectangle(cr, SIZE+(SIZE+1)*i, SIZE+(SIZE+1)*y, SIZE, SIZE);
			cairo_set_source_rgb (cr, 1.0, 0.0, 0.0);
			cairo_fill(cr);
		}
		else
		{
			cairo_rectangle(cr, SIZE+(SIZE+1)*i, SIZE+(SIZE+1)*y, SIZE, SIZE);
			cairo_set_source_rgb (cr, 0.0, 0.8, 0.15*(ligne[i]));
			cairo_fill(cr);
		}
	}
	return;
}

/**
 * \fn void affiche_grille (grille g)
 * \brief affiche une grille au complet
 * \param g la grille à afficher
 * \return void
 * \post fonction d(affichage
 */
void affiche_grille (grille g, cairo_t *cr){
	int i, l=g.nbl, c=g.nbc;
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i], cr, i);
	}	
	return;
}


void affiche_cyclisme(cairo_t *cr, int cyclique)
{
	cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
	cairo_move_to(cr, 150, 20);
	if (cyclique)
	{ cairo_show_text(cr, "cyclique"); }
	else
	{ cairo_show_text(cr, "non cyclique"); }
	return;
}


void affiche_vieillissant(cairo_t *cr,int vieillissement)
{
	cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
	cairo_move_to(cr, 220, 20);
	if (vieillissement)
	{ cairo_show_text(cr, "avec vieillissement"); }
	else
	{ cairo_show_text(cr, "sans vieillissement"); }
	return;
}


void affiche_periode(cairo_t *cr, int periode)
{
	char str[50];
	sprintf(str, "periode oscillation %d", periode);
	cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
	cairo_move_to(cr, 50, 40);
	if (periode==0)
	{ cairo_show_text(cr, "grille non oscillante"); }
	else
	{ cairo_show_text(cr, str); }
	return;
}


void affiche_etape(cairo_t *cr, int compteur)
{
	char str[50];
	sprintf(str, "Etape : %d", compteur);
	cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
	cairo_move_to(cr, 50, 20);
	cairo_show_text(cr, str);
	return;
}


/**
 * \fn void debut_jeu (grille *g, grille *gc)
 * \brief fonction qui lance le jeu de la vie et qui gère l'interraction avec l'utilisateur
 * \param g pointeur sur une grille
 * \param gc pointeur sur une grille
 * \return void
 * \pre g et gc doivent avoir les meme dimensions
 * \post fonction contenant des fonctions d'affichage
 */
void debut_jeu(grille *g, grille *gc, cairo_t *cr, cairo_surface_t *cs, Display *dpy, XEvent e){
	// debut du jeu
	int compteur = 0; 
	int vieillissement = 0;
	int cyclique = 1;
	int periode = -1;
	int exit =0;
	while (! exit) // touche 'q' pour quitter
	{ 
		XNextEvent(dpy, &e);	
		if(e.type==Expose && e.xexpose.count<1)
		{ affiche_grille(*g,cr); }	
		else if(e.type==ButtonPress && e.xbutton.button==Button3) exit=1;
		else if(e.type==ButtonPress && e.xbutton.button==Button1)
		{
			compteur++;
			// touche "entree" pour évoluer
			evolue(g,gc,cyclique,vieillissement);
			// background
			cairo_set_source_rgb (cr,0.1,0.1,0.1);
			cairo_paint(cr);
			affiche_etape(cr,compteur);
			affiche_cyclisme(cr,cyclique);
			affiche_vieillissant(cr,vieillissement);
			// grille
			affiche_grille(*g,cr);
		}
		else if(e.type==KeyPress)
		{
			switch (e.xkey.keycode) {
				case 36 :
				{	
					compteur++;
					// touche "entree" pour évoluer
					evolue(g,gc,cyclique,vieillissement);
					// background
					cairo_set_source_rgb (cr,0.1,0.1,0.1);
					cairo_paint(cr);
					affiche_etape(cr,compteur);
					affiche_cyclisme(cr,cyclique);
					affiche_vieillissant(cr,vieillissement);
					// grille
					affiche_grille(*g,cr);
					break;
				}
				case 54 :
				{
					if (cyclique) { cyclique = 0;}
					else { cyclique = 1;}
					break;
				}
				case 55 :
				{
					if (vieillissement) {vieillissement = 0;}
					else {vieillissement = 1;}
					break;
				}
				case 32 :
				{
					periode = est_oscillante(g,gc, cyclique, vieillissement);
					affiche_periode(cr,periode);
				}
				default : 
				{ // touche non traitée
					printf("\n\e[1A");
					break;
				}
			}
		}
	}
	return;	
}
