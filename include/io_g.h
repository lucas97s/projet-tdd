/**
 * \file io_g.h
 * \brief header pour les entrees et sorties mode graphique
 * \author Lucas Schott
 */

#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>

// affichage d'une ligne de la grille
void affiche_ligne (int c, int* ligne, cairo_t *cr, int y);

// affichage d'une grille
void affiche_grille (grille g, cairo_t *cr);

void affiche_cyclisme(cairo_t *cr, int cyclique);

void affiche_vieillissement(cairo_t *cr, int vieillissement);

void affiche_etape(cairo_t *cr, int compteur);

void affiche_oscillant(cairo_t *cr, int periode);

// debute le jeu
void debut_jeu(grille *g, grille *gc, cairo_t *cr, cairo_surface_t *cs,  Display *dpy, XEvent e);

#endif
