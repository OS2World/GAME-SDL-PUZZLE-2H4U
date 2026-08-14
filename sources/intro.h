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
#ifndef Intro
#define Intro

#include "sdl_includes.h"

//Attente du début
#define I_DEBUT 1000.

//Logo Team
#define I_1 1500.
#define I_2 1500.
#define I_3 1500.

#define I_A 500.

//Logo Jeu
#define I_4 1500.
#define I_5 3000.
#define I_6 1500.

#define I_B 500.

//Menu
#define I_7 800.

class CIntro
{
private:

    SDL_Surface * m_pMenu;
    SDL_Surface * m_pTeam;
    SDL_Surface * m_pJeu;
    SDL_Surface * m_pNoir;

    int etape;
    int alpha;
    long debutAnim;

public :
    CIntro();
    void initIntro(char [MAX_LANG][256]);
    void deleteIntro();
    void drawIntro(SDL_Surface*);
    bool calculateFrame();
};

#endif
