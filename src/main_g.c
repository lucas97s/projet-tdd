/**
 * \file main.c
 * \brief code principal
 * \author Lucas Schott
 */

#include <stdio.h>
#include "grille.h"
#include "io_g.h"
#include "jeu.h"

#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>

#define SIZE 50


/**
 * \fn int main (int argc, char ** argv)
 * \brief fonction principale du programme
 * \param argc le nombre d'arguments
 * \param argv un fichier texte contenant les données pour initialiser la grille
 * \return o un code de retour standard
 */
int main (int argc, char ** argv) {

	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}

	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);

	// X11 display
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;
	
	// init the display
	if(!(dpy=XOpenDisplay(NULL))) {
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, (2*SIZE)+(SIZE+1)*g.nbc, (2*SIZE)+(SIZE+1)*g.nbl, 0, 
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "jeu de la vie");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyPressMask);
	XMapWindow(dpy, win);

	// create cairo surface
	cairo_surface_t *cs; 
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), (2*SIZE)+(SIZE+1)*g.nbc, (2*SIZE)+(SIZE+1)*g.nbl);
	
	// Mask
	cairo_t *cr;
	cr=cairo_create(cs);

	// background
	cairo_set_source_rgb(cr,0.1,0.1,0.1);
	cairo_paint(cr);

	//affiche grille

	affiche_grille(g,cr);
	
	debut_jeu(&g, &gc, cr, cs, dpy, e);

	libere_grille(&g);
	libere_grille(&gc);

	cairo_destroy(cr);
	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display

	return 0;
}
