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
#ifndef Bonus
#define Bonus

#include <cstdlib>

#include "sdl_includes.h"

//Nombre de types de bonus différents
#define NB_BONUS 11
//Liste des bonus
#define B_ADD_BALLE 0
#define B_ACC_BALLE 1
#define B_RAL_BALLE 2
#define B_ADD_SCORE 3
#define B_ADD_LIFE 4
#define B_DELETE_LINE 5
#define B_BLOQUE_STRAFE 6
#define B_SMALL_RAQ 7
#define B_LARGE_RAQ 8
#define B_EXTRA_LARGE_RAQ 9
#define B_EXTRA_SMALL_RAQ 10

//Nombre maximum de bonus en jeu en même temps.
#define MAX_BONUS 3

//On a une chance sur X d'avoir un bonus.
#define CHANGES_BONUS 20


struct CBonusInfo
{
    bool actif;
    double x;
    double y;
    double vitesse;
    int type;


};

class CBonus
{
private :

SDL_Surface* m_pBonus[NB_BONUS];
CBonusInfo m_stBonusInfo[MAX_BONUS];

public :

    CBonus(); // constructeur
    ~CBonus();
    void initBonus();
    void deleteBonus();
    void drawBonus(SDL_Surface*);
    void mayAddBonus(int x,int y,double);
    int deplacerBonus(int [], const int&, SDL_Rect*);
    SDL_Surface* GetSurface();
};










#endif
