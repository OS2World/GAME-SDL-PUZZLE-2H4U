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
#include "intro.h"

CIntro::CIntro() {}

void CIntro::initIntro(char lang[MAX_LANG][256])
{



    SDL_Surface* tempSurf[6];
    SDL_Surface* gd,* pt;
    SDL_Surface* tempTxt=NULL;
    SDL_Rect centrage;

    //On écrit le texte grace à TTF.
    TTF_Font *policeTxt = TTF_OpenFont("data/bgothm.ttf", 60);
    SDL_Color couleurTxt = { 0, 0, 0 };

    //DOWN :

    m_pMenu=IMG_Load("data/images/menu/menu.jpg");

    //On charge les images sans texte à l'intérieur
    gd=IMG_Load("data/images/menu/down_gd.png");
    pt=IMG_Load("data/images/menu/down_pt.png");

    tempSurf[0]=SDL_ConvertSurfaceFormat(gd, SDL_PIXELFORMAT_ARGB8888, 0);
    tempSurf[1]=SDL_ConvertSurfaceFormat(pt, SDL_PIXELFORMAT_ARGB8888, 0);
    tempSurf[2]=SDL_ConvertSurfaceFormat(pt, SDL_PIXELFORMAT_ARGB8888, 0);
    tempSurf[3]=SDL_ConvertSurfaceFormat(pt, SDL_PIXELFORMAT_ARGB8888, 0);
    tempSurf[4]=SDL_ConvertSurfaceFormat(gd, SDL_PIXELFORMAT_ARGB8888, 0);
    tempSurf[5]=SDL_ConvertSurfaceFormat(gd, SDL_PIXELFORMAT_ARGB8888, 0);

    SDL_FreeSurface(gd);
    SDL_FreeSurface(pt);

    for (int i=0;i<6;i++)
    {
        if (tempTxt!=NULL)
        {
            SDL_FreeSurface(tempTxt);
        }
        tempTxt = TTF_RenderText_Blended(policeTxt, lang[i+1], couleurTxt);

        centrage.x=(tempSurf[i]->w/2)-(tempTxt->w/2);
        centrage.y=((tempSurf[i]->h/2)-(tempTxt->h/2))-3;
        centrage.w=tempTxt->w;
        centrage.h=tempTxt->h;
        SDL_BlitSurface(tempTxt,NULL,tempSurf[i],&centrage);

    }
    if (tempTxt!=NULL)
    {
        SDL_FreeSurface(tempTxt);
    }
    centrage.x=150;
    centrage.y=75;
    centrage.w=tempSurf[0]->w;
    centrage.h=tempSurf[0]->h;
    SDL_BlitSurface(tempSurf[0],NULL,m_pMenu,&centrage);

    centrage.x=150;
    centrage.y=163;
    centrage.w=tempSurf[1]->w;
    centrage.h=tempSurf[1]->h;
    SDL_BlitSurface(tempSurf[1],NULL,m_pMenu,&centrage);

    centrage.x=150;
    centrage.y=250;
    centrage.w=tempSurf[2]->w;
    centrage.h=tempSurf[2]->h;
    SDL_BlitSurface(tempSurf[2],NULL,m_pMenu,&centrage);

    centrage.x=150;
    centrage.y=338;
    centrage.w=tempSurf[3]->w;
    centrage.h=tempSurf[3]->h;
    SDL_BlitSurface(tempSurf[3],NULL,m_pMenu,&centrage);

    centrage.x=150;
    centrage.y=425;
    centrage.w=tempSurf[4]->w;
    centrage.h=tempSurf[4]->h;
    SDL_BlitSurface(tempSurf[4],NULL,m_pMenu,&centrage);

    centrage.x=150;
    centrage.y=512;
    centrage.w=tempSurf[5]->w;
    centrage.h=tempSurf[5]->h;
    SDL_BlitSurface(tempSurf[5],NULL,m_pMenu,&centrage);

    for (int i=0;i<6;i++)
        SDL_FreeSurface(tempSurf[i]);


    m_pTeam=IMG_Load("data/images/menu/team.jpg");

    SDL_Color couleurTxt2 = { 255, 255, 255 };
    tempTxt = TTF_RenderText_Blended(policeTxt, lang[0], couleurTxt2);
    centrage.x=(m_pTeam->w/2)-(tempTxt->w/2);
    centrage.y=450;
    centrage.w=tempTxt->w;
    centrage.h=tempTxt->h;
    SDL_BlitSurface(tempTxt,NULL,m_pTeam,&centrage);
    SDL_FreeSurface(tempTxt);

    TTF_CloseFont(policeTxt);

    m_pJeu=IMG_Load("data/images/menu/jeu.jpg");
    m_pNoir=IMG_Load("data/images/menu/noir.png");

    etape=69;
    alpha=255;
    debutAnim=SDL_GetTicks();
}

void CIntro::deleteIntro()
{
    SDL_FreeSurface(m_pMenu);
    SDL_FreeSurface(m_pTeam);
    SDL_FreeSurface(m_pJeu);
    SDL_FreeSurface(m_pNoir);
}

void CIntro::drawIntro(SDL_Surface* destination)
{
    SDL_SetSurfaceAlphaMod(m_pNoir, alpha);
    switch(etape)
    {
        //Apparition du logo Team.
        case 0:
            SDL_BlitSurface(m_pTeam, NULL, destination, NULL);
        break;
        //Apparition du logo Jeu
        case 1:
            SDL_BlitSurface(m_pJeu, NULL, destination, NULL);
        break;
        //Apparition du Menu
        case 2:
            SDL_BlitSurface(m_pMenu, NULL, destination, NULL);
        break;
        case 69:
        break;
    }
    SDL_BlitSurface(m_pNoir, NULL, destination, NULL);
}

bool CIntro::calculateFrame()
{
    int tempsEcoule=SDL_GetTicks()-debutAnim;
    switch(etape)
    {
        case 69:
            if (tempsEcoule>I_DEBUT)
            {
                debutAnim=SDL_GetTicks();
                etape=0;
            }
        break;
        //Apparition du logo Team.
        case 0:
            if (tempsEcoule<I_1)
            {
                alpha=(int)(255*(1. - tempsEcoule/I_1));
            }
            else if (tempsEcoule<I_1+I_2)
            {
                alpha=0;
            }
            else if (tempsEcoule<I_1+I_2+I_3)
            {
                alpha=(int)(255*((tempsEcoule-(I_1+I_2))/I_3));
            }
            else if (tempsEcoule<I_1+I_2+I_3+I_A)
            {
                alpha=255;
            }
            else
            {
                debutAnim=SDL_GetTicks();
                alpha=255;
                etape=1;
            }
        break;
        //Apparition du logo Jeu.
        case 1:
            if (tempsEcoule<I_4)
            {
                alpha=(int)(255*(1. - tempsEcoule/I_4));
            }
            else if (tempsEcoule<I_4+I_5)
            {
                alpha=0;
            }
            else if (tempsEcoule<I_4+I_5+I_6)
            {
                alpha=(int)(255*((tempsEcoule-(I_4+I_5))/I_6));
            }
            else if (tempsEcoule<I_4+I_5+I_6+I_B)
            {
                alpha=255;
            }
            else
            {
                debutAnim=SDL_GetTicks();
                alpha=255;
                etape=2;
            }
        break;
        //Apparition du Menu.
        case 2:
            if (tempsEcoule<I_7)
            {
                alpha=(int)(255*(1. - tempsEcoule/I_7));
            }
            else
            {
                return false;
            }
        break;
    }
    return true;

}
