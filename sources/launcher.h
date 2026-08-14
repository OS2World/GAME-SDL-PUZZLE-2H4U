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
#ifndef Launcher
#define Launcher

#include "sdl_includes.h"

class CLauncher
{
private:
    SDL_Surface * m_pFond[2];
    SDL_Surface * m_pItem[4];
    int m_iStep;
    int m_iChoice;

public :
    CLauncher();
    void initLauncher();
    void deleteLauncher();
    void drawLauncher(SDL_Surface*);
    void nextStep();
    void change();
    int getStep();
};

#endif
