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
#ifndef Terrain
#define Terrain

#include <math.h>
#include <cstdlib>

#include "sdl_includes.h"
#include "brick.h"
#include "figure.h"


//////////////////////////////////////////////////////////////////////////////////////////////

class CTerrain
{

private:

CBrick *** m_pBrick;

CBrick *m_pFigBrick[4];

CBrick *m_pBrickVide;

int m_iTailleBrick;

SDL_Surface* * m_pImgCT;

SDL_Surface* m_pBriqueCassee;

SDL_Surface* myImgTerrain;

SDL_Rect myRectTerrain;

//Surface permettant de stocker les figures a présenter avant :
SDL_Surface* *m_pImgFigure;
int m_iNextFig;

bool m_bBalleDestructionLigne;
int m_iNbBriquesDestroy;

CFigure myFigure;

public :
CTerrain();
void initTerrain(char [MAX_LANG][256]);
void deleteTerrain();
int collisionBriques(int, int, int, int, int);
bool gereCollision(int, int);
bool getBalleDestruction(int &);
void drawTerrain(SDL_Surface*);
SDL_Surface* GetImage();
SDL_Rect* GetRect();

bool rotationFigure();
bool moveFigure(int, int);
bool dropFigure();
void permuterFigure();

void rndFillTerrain(int);
bool isEmptyTerrain();
int findFullLine();
bool isFullLine(int,bool);
int findEmptyLine();
bool isEmptyLine(int,bool);
void deleteLine(const int&,bool);
void permuterLignes(int , int,bool);

};

#endif
