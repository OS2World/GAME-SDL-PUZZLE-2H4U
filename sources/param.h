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

#ifndef Param
#define Param

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sdl_includes.h"

class CParam
{
private:

int m_iSon;
int m_iMusique;
int m_iFullscreen;
int m_iClavier;
int m_iLangue;
bool m_bNew;
const char* m_czChemin;


public:
    //Constructeur
    CParam();
    //Initialisation (on charge le fichier et on remplie les variables).
    void initParam(const char*);
    //Une fois des modifications effectuée (donc juste avant de lancer le jeu), on sauve les modifications.
    void saveParam();

    //Fonctions pour modifier et récupérer des paramètres :

    void flipSon();
    void flipMusique();
    void flipFullscreen();
    void flipLangue();
    void flipClavier();

    int getSon();
    int getMusique();
    int getFullscreen();
    int getClavier();
    int getLangue();
    bool getNew();

    void getTxtLang(char [MAX_LANG][256]);

};
#endif
