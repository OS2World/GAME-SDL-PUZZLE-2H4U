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

#include "menu.h"

CItem::CItem()
{
    m_pSelected=NULL;
}

void CItem::initItem(SDL_Surface* selected,int x,int y)
{
    m_pSelected=selected;
    m_pPosition.x=x;
    m_pPosition.y=y;
}

void CItem::deleteItem()
{
    SDL_FreeSurface(m_pSelected);
    m_pSelected=NULL;
}

void CItem::drawItem(SDL_Surface *destination,bool selected)
{
    if (selected==true)
    {
        SDL_BlitSurface(m_pSelected,NULL,destination,&m_pPosition);
    }
}

CMenu::CMenu()
{
}

void CMenu::initMenu(char lang[MAX_LANG][256])
{
    m_iNbItems=6;
    m_pItems = new CItem[m_iNbItems];

    SDL_Surface* tempSurf[6];
    SDL_Surface* gd,* pt;
    SDL_Surface* tempTxt=NULL;
    SDL_Rect centrage;

    //On écrit le texte grace à TTF.
    TTF_Font *policeTxt = TTF_OpenFont("data/bgothm.ttf", 60);
    SDL_Color couleurTxt = { 250, 60, 0 };
    SDL_Color couleurTxt2 = { 0, 0, 0 };

    //UP
    //On charge les images sans texte à l'intérieur
    gd=IMG_Load("data/images/menu/up_gd.png");
    pt=IMG_Load("data/images/menu/up_pt.png");

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
        tempTxt = TTF_RenderText_Blended(policeTxt, lang[i+1], couleurTxt2);

        centrage.x=(tempSurf[i]->w/2)-(tempTxt->w/2);
        centrage.y=((tempSurf[i]->h/2)-(tempTxt->h/2))-3;
        centrage.w=tempTxt->w;
        centrage.h=tempTxt->h;
        SDL_BlitSurface(tempTxt,NULL,tempSurf[i],&centrage);
    }

    m_pItems[0].initItem(tempSurf[0],150,75);
    m_pItems[1].initItem(tempSurf[1],150,163);
    m_pItems[2].initItem(tempSurf[2],150,250);
    m_pItems[3].initItem(tempSurf[3],150,338);
    m_pItems[4].initItem(tempSurf[4],150,425);
    m_pItems[5].initItem(tempSurf[5],150,512);


    //DOWN :

    m_pFond=IMG_Load("data/images/menu/menu.jpg");

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
    SDL_BlitSurface(tempSurf[0],NULL,m_pFond,&centrage);

    centrage.x=150;
    centrage.y=163;
    centrage.w=tempSurf[1]->w;
    centrage.h=tempSurf[1]->h;
    SDL_BlitSurface(tempSurf[1],NULL,m_pFond,&centrage);

    centrage.x=150;
    centrage.y=250;
    centrage.w=tempSurf[2]->w;
    centrage.h=tempSurf[2]->h;
    SDL_BlitSurface(tempSurf[2],NULL,m_pFond,&centrage);

    centrage.x=150;
    centrage.y=338;
    centrage.w=tempSurf[3]->w;
    centrage.h=tempSurf[3]->h;
    SDL_BlitSurface(tempSurf[3],NULL,m_pFond,&centrage);

    centrage.x=150;
    centrage.y=425;
    centrage.w=tempSurf[4]->w;
    centrage.h=tempSurf[4]->h;
    SDL_BlitSurface(tempSurf[4],NULL,m_pFond,&centrage);

    centrage.x=150;
    centrage.y=512;
    centrage.w=tempSurf[5]->w;
    centrage.h=tempSurf[5]->h;
    SDL_BlitSurface(tempSurf[5],NULL,m_pFond,&centrage);

    for (int i=0;i<6;i++)
        SDL_FreeSurface(tempSurf[i]);

    m_pScores=IMG_Load("data/images/menu/scores.jpg");

    tempTxt = TTF_RenderText_Blended(policeTxt, lang[7], couleurTxt);
    centrage.x=(m_pScores->w/2)-(tempTxt->w/2);
    centrage.y=70;
    centrage.w=tempTxt->w;
    centrage.h=tempTxt->h;
    SDL_BlitSurface(tempTxt,NULL,m_pScores,&centrage);
    SDL_FreeSurface(tempTxt);

    TTF_CloseFont(policeTxt);


    m_pChangeMusique=IMG_Load("data/images/menu/change_musique.png");
    m_pChangeSons=IMG_Load("data/images/menu/change_sons.png");
    m_pChangeAffichage=IMG_Load("data/images/menu/change_affichage.png");

    if (m_pFond==NULL) {SDL_Quit();}

    m_iSelectedItem=0;

    for (int i=0;i<5;i++)
    {
        scoreTxt[i]=NULL;
    }

}

void CMenu::deleteMenu()
{
    for (int i=0;i<6;i++)
    {
        m_pItems[i].deleteItem();
    }

    delete[] m_pItems;

    SDL_FreeSurface(m_pFond);
    SDL_FreeSurface(m_pScores);
    SDL_FreeSurface(m_pChangeMusique);
    SDL_FreeSurface(m_pChangeSons);
    SDL_FreeSurface(m_pChangeAffichage);

    for (int i=0;i<5;i++)
    {
        if (scoreTxt[i]!=NULL) SDL_FreeSurface(scoreTxt[i]);
    }
}

void CMenu::drawMenu(SDL_Surface* destination, bool musique, bool sons, bool pleinEcran)
{

    SDL_Rect position;
    position.x=0;
    position.y=0;
    SDL_BlitSurface(m_pFond,NULL,destination,&position);
    for (int i=0;i<6;i++)
    {
        m_pItems[i].drawItem(destination,(m_iSelectedItem==i));
    }
    if (musique==false)
    {
        position.x=500;
        position.y=163;
        SDL_BlitSurface(m_pChangeMusique,NULL,destination,&position);
    }
    if (sons==false)
    {
        position.x=500;
        position.y=250;
        SDL_BlitSurface(m_pChangeSons,NULL,destination,&position);
    }
    if (pleinEcran==false)
    {
        position.x=500;
        position.y=338;
        SDL_BlitSurface(m_pChangeAffichage,NULL,destination,&position);
    }
}

int CMenu::getSelectedItem()
{
    return m_iSelectedItem;
}
int CMenu::getNbItems()
{
    return m_iNbItems;
}

void CMenu::selectNextItem()
{
    m_iSelectedItem+=1;
    if(m_iSelectedItem==m_iNbItems){m_iSelectedItem=0;}
}

void CMenu::selectPreviousItem()
{
    m_iSelectedItem-=1;
    if(m_iSelectedItem==-1){m_iSelectedItem=(m_iNbItems-1);}
}

void CMenu::makeScores(CHighscore m_Highscore)
{

    SDL_Color couleurChiffres = { 255, 50, 0 };
    TTF_Font *policeChiffres = TTF_OpenFont("data/DS-DIGIB.TTF", 60);
    char buffer[256];

    for (int i=0;i<5;i++)
    {
        sprintf(buffer,"%d",m_Highscore.getScore(i));

        if (scoreTxt[i]!=NULL) SDL_FreeSurface(scoreTxt[i]);

        scoreTxt[i] = TTF_RenderText_Blended(policeChiffres, buffer, couleurChiffres);
    }
}

void CMenu::drawScores(SDL_Surface* destination)
{
    SDL_Rect position;
    position.x=0;
    position.y=0;
    SDL_BlitSurface(m_pScores,NULL,destination,&position);
    position.x=310;
    for (int i=0;i<5;i++)
    {
        position.y=175 + i*72;
        SDL_BlitSurface(scoreTxt[i],NULL,destination,&position);
    }
}

