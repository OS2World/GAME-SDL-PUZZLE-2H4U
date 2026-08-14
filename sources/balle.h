/*
    Copyright 2006 Pierre Lagouge, Pierre-Yves Ricau

    This file is part of 2H4U.

    2H4U is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    2H4U is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with 2H4U; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef Balle
#define Balle

#include <cstdlib>

#include "sdl_includes.h"
#include "terrain.h"
#include "son.h"
#include "bonus.h"

///////////////////////////////////////////////////////////////////////////////////////////
class CBalle

{

private :

int properties;
double dX, dY;
double xBalle,yBalle;
SDL_Surface* myImgBalle;
SDL_Surface* myImgBalle2;
SDL_Rect myRectBalle;
int active;

double vitesseBalle;

public :

CBalle();
void initBalle(int prop,SDL_Surface*,SDL_Surface*);
void deleteBalle();
void startBalle(int,int,double);
void stopBalle();
int getStatutBalle();
bool deplacer(const int&,CTerrain &,SDL_Rect*,CSon &, CBonus &);
void rebondi(double CoeffX,double CoeffY);
void setSpeed(double);

void drawBalle(SDL_Surface*);

SDL_Rect* GetRect();
SDL_Surface* getSurface();
};

#endif

