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
#ifndef Son
#define Son

//A modifier pour chaque nouveau effet ajouté.
#define MAX_SONS 11

#define S_CASSE_BRIQUE 0
#define S_REBOND_RAQ 1 //Non encore utilisé.
#define S_CASSE_LIGNE 2
#define S_POSE_BRIQUE 3
#define S_REBOND_MUR 4
#define S_ROTATION 5
#define S_STRAFE 6
#define S_NIVEAU 7
#define S_GAME_OVER 8
#define S_PERDU_BALLE 9
#define S_GAGNE_BONUS 10

#include <cstdlib>

#include "sdl_includes.h"


class CSon
{
private :

#ifndef NO_SOUND_2H4U
Mix_Music* musique;
Mix_Chunk * *effet;
#endif
bool m_bSonOn;
bool m_bMusiqueOn;


public :

CSon();//constructeur, ne fait rien
~CSon();//destructeur
void initSon(bool,bool);
void deleteSon();

void pauseMusic();//prevu pour une seule musique de jeu
void resumeMusic();
void playEffet(int);

};


#endif
