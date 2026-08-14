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
#include "bonus.h"

CBonus::CBonus(){}
CBonus::~CBonus(){}


void CBonus::initBonus()
{

    char buffer[256];

    //Chargement des images de Bonus.
    for (int i=0;i<NB_BONUS;i++)
    {
        sprintf(buffer,"data/images/jeu/bonus/%d.png",i);
        m_pBonus[i]=IMG_Load(buffer);
    }

    //Tableau qui gère les bonus.
    for (int i=0;i<MAX_BONUS;i++)
    {
        m_stBonusInfo[i].actif=false;
    }

}

void CBonus::deleteBonus()
{
    for (int i=0;i<NB_BONUS;i++)
    {
        SDL_FreeSurface(m_pBonus[i]);
    }
}

void CBonus::mayAddBonus(int x,int y,double vitesse)
{
    int i;
    bool continuer;
    continuer=true;
    i=0;
    while ( continuer )
    {
        if (i<MAX_BONUS)
        {
            if (m_stBonusInfo[i].actif==false)
            {
                continuer=false;
            }
            else i++;
        }
        else
        {
            continuer=false;
            i=-1;
        }
    }
    //S'il ya des bonus libres, on va peut être en créer un.
    if (i!=-1)
    {
        //Ca donne une chance sur 10 d'avoir un bonus.
        if (rand()%CHANGES_BONUS==0)
        {
            m_stBonusInfo[i].actif=true;
            m_stBonusInfo[i].x=(double)x;
            m_stBonusInfo[i].y=(double)y;
            m_stBonusInfo[i].vitesse=vitesse;
            m_stBonusInfo[i].type=rand()%NB_BONUS;
        }
    }
}

//Penser a modifier l'indice du tableau dans la fonction appellante si nécessaire.
int CBonus::deplacerBonus(int bonusObtenu[], const int& iElapsedTime, SDL_Rect* RaqRect)
{
    int nbObtenus=0;

    for (int i=0;i<MAX_BONUS;i++)
    {
        if (m_stBonusInfo[i].actif==true)
        {
            //On bouge les bonus.
            m_stBonusInfo[i].y += (iElapsedTime*m_stBonusInfo[i].vitesse);
            if (m_stBonusInfo[i].y<=600)
            {

                //Gestion des collisions avec la raquette.
                //Si on est dessus dans les Y (arrive moins souvent que les X)
                if ((int)m_stBonusInfo[i].y+m_pBonus[0]->h>RaqRect->y)
                    //Si on est dessus dans les X
                    if (((int)m_stBonusInfo[i].x>RaqRect->x && (int)m_stBonusInfo[i].x<RaqRect->x+RaqRect->w) || ((int)m_stBonusInfo[i].x+m_pBonus[0]->w>RaqRect->x && (int)m_stBonusInfo[i].x+m_pBonus[0]->w<RaqRect->x+RaqRect->w))
                    {
                        m_stBonusInfo[i].actif=false;
                        bonusObtenu[nbObtenus]=m_stBonusInfo[i].type;
                        nbObtenus++;
                    }
            }
            else
            {
                m_stBonusInfo[i].actif=false;
            }
        }
    }

    return nbObtenus;
}

void CBonus::drawBonus(SDL_Surface* destination)
{
    SDL_Rect pos;
    pos.w=m_pBonus[0]->w;
    pos.h=m_pBonus[0]->h;
    for (int i=0;i<MAX_BONUS;i++)
    {
        if (m_stBonusInfo[i].actif==true)
        {
            pos.x=(int)m_stBonusInfo[i].x;
            pos.y=(int)m_stBonusInfo[i].y;
            SDL_BlitSurface(m_pBonus[m_stBonusInfo[i].type],NULL,destination,&pos);
        }
    }
}

SDL_Surface* CBonus::GetSurface(){return m_pBonus[0];}
