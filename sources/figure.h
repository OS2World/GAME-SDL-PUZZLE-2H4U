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
#ifndef Figure
#define Figure

#include <cstdlib>

#include "brick.h"
#include "sdl_includes.h"

class CFigure
{
private :

SDL_Rect myRectFigure1;
int forme,state,posX,posY;

int CaseOccupees[4][2];

public :

CFigure(); // consttructeur qui ne fait rien
bool InitFigure(int,CBrick *** &);
int Forme();
/*
0 : carre
1 : line
2 : LD
3 : LG cad _|
4 : ZG cad Z
5 : ZD cad 5
6 : T
*/

int State();

bool FCaseOccupees(CBrick *** &,bool); // renvoi le num des cases occupees par la figure

bool Rotation(CBrick *** &);   // incremente State en utilisant ModifState()

bool collision(int[][2],CBrick *** &); //Renvoie true si collision ou hors map.

bool ModifCoord(int, int,CBrick *** &);

int ** ReturnCaseOccupees();


};
#endif
