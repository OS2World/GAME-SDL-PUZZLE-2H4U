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
#include "launcher.h"

CLauncher::CLauncher() {}

void CLauncher::initLauncher()
{
    m_pFond[0]=IMG_Load("data/images/launcher/langue.jpg");
    m_pFond[1]=IMG_Load("data/images/launcher/clavier.jpg");

    m_pItem[0]=IMG_Load("data/images/launcher/francais.png");
    m_pItem[1]=IMG_Load("data/images/launcher/english.png");
    m_pItem[2]=IMG_Load("data/images/launcher/azerty.png");
    m_pItem[3]=IMG_Load("data/images/launcher/qwerty.png");

    m_iStep=0;
    m_iChoice=0;
}

void CLauncher::deleteLauncher()
{
    for (int i=0;i<2;i++)
        SDL_FreeSurface(m_pFond[i]);
    for (int i=0;i<4;i++)
        SDL_FreeSurface(m_pItem[i]);
}

void CLauncher::drawLauncher(SDL_Surface* destination)
{

    SDL_Rect pos;
    pos.x=150;
    pos.y=150 + m_iChoice*237;
    pos.w=m_pItem[0]->w;
    pos.h=m_pItem[0]->h;

    SDL_BlitSurface(m_pFond[m_iStep], NULL, destination, NULL);
    SDL_BlitSurface(m_pItem[m_iChoice + m_iStep*2], NULL, destination, &pos);

}

void CLauncher::nextStep()
{
    m_iStep++;
    m_iChoice=0;
}

void CLauncher::change()
{
    m_iChoice+=1;
    m_iChoice%=2;
}

int CLauncher::getStep()
{
    return m_iStep;
}
