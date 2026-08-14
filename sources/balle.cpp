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
#include "balle.h"

CBalle::CBalle()
{}

void CBalle::initBalle(int prop,SDL_Surface* ImgBalle,SDL_Surface* ImgBalle2)
{
    active=0;
    myImgBalle = ImgBalle;
    myImgBalle2 = ImgBalle2;
    properties = prop;
    myRectBalle.w = myImgBalle -> w;
    myRectBalle.h = myImgBalle -> h;

}

void CBalle::deleteBalle()
{
    active=0;
    myImgBalle = NULL; //La surface sera free plus haut, auparavant.
    myImgBalle2 = NULL;
}

void CBalle::startBalle(int posX,int posY, double vitesse)
{
    double teta;

    active=1;

    xBalle=(double)posX;
    yBalle=(double)posY;

    myRectBalle.x = posX;
    myRectBalle.y = posY;

    teta=((rand()%170)+90)/100.;

    dX=vitesse*cos(teta);
    dY=-vitesse*sin(teta);

    vitesseBalle=vitesse;
}

void CBalle::stopBalle()
{
    active=0;
}

int CBalle::getStatutBalle()
{
    return active;
}

//Renvoie vrai si la balle est détruite, 0 sinon.
bool CBalle::deplacer(const int& iElapsedTime, CTerrain &terrain, SDL_Rect* RaqRect, CSon &mySon, CBonus &myBonus)
{
    int maxX,maxY,xmid,raqmid,retColl;
    double r,teta,diff,oldX,oldY;
    //On passe par des int pour les cas négatifs.
    double x = xBalle;
    double y = yBalle;

    oldX=x;
    oldY=y;

    SDL_Rect* terrainRect=terrain.GetRect();




    x += (iElapsedTime*dX);
    y += (iElapsedTime*dY);

    int xa=(int)x;
    int ya=(int)y;
    int xDep=(int)oldX;
    int yDep=(int)oldY;

    //Gestion des collisions avec les briques.
    //Attention : la fonction peut modifier x et y, si nécessaire.
    //Cela permet de replacer la balle.
    retColl=terrain.collisionBriques(xa,ya,xDep,yDep,myRectBalle.w);
    switch (retColl)
    {
        case 0:
        break;
        case 1:
            rebondi(-1.0,1.0);
            myBonus.mayAddBonus(xa,ya,vitesseBalle/2);
            x=oldX;
            y=oldY;
        break;
        case 2:
            rebondi(1.0,-1.0);
            myBonus.mayAddBonus(xa,ya,vitesseBalle/2);
            x=oldX;
            y=oldY;
        break;
        case 3:
            rebondi(-1.0,-1.0);
            myBonus.mayAddBonus(xa,ya,vitesseBalle/2);
            x=oldX;
            y=oldY;
        break;
        default:
        fprintf( stderr, "Erreur : Valeur non valable renvoyée par collisionBriques\n");
    }

    maxX=(terrainRect->x+terrainRect->w)-myRectBalle.w;
    maxY=(terrainRect->y+terrainRect->h)-myRectBalle.h;


    //En X
    if (x<terrainRect->x)
    {
        x=terrainRect->x;
        rebondi(-1.0,1.0);
        mySon.playEffet(S_REBOND_MUR);
    }
    else if (x>maxX)
    {
        x=maxX;
        rebondi(-1.0,1.0);
        mySon.playEffet(S_REBOND_MUR);
    }
    //En Y
    if (y<terrainRect->y)
    {
        y=terrainRect->y;
        rebondi(1.0,-1.0);
        mySon.playEffet(S_REBOND_MUR);
    }

    else if (y>maxY)
    {
        stopBalle();
        return true;
    }

    //Gestion des collisions avec la raquette.
    //Si on est dessus dans les Y (arrive moins souvent que les X)
    if ((y>RaqRect->y && y<RaqRect->y+RaqRect->h) || (y+myRectBalle.h>RaqRect->y && y+myRectBalle.h<RaqRect->y+RaqRect->h))
        //Si on est dessus dans les X
        if ((x>RaqRect->x && x<RaqRect->x+RaqRect->w) || (x+myRectBalle.w>RaqRect->x && x+myRectBalle.w<RaqRect->x+RaqRect->w))
        {
            //On joue le son de collision raquette
            mySon.playEffet(S_REBOND_RAQ);
            //Rebond fonctionne
            y=RaqRect->y-myRectBalle.h;
            //r=sqrt(dX*dX + dY*dY);
            r=vitesseBalle;
            xmid = (int)x + myRectBalle.w/2;
            raqmid = RaqRect->x + RaqRect->w/2;

            //Formule qui détermine l'angle de renvoie.
            //A changer si l'on veut changer le style de renvoie.
            diff=(double)(raqmid-xmid);

            //Petite correction empechant l'angle vertical pur.
            if (fabs(diff)<6)
            {
                if (diff<0)
                {
                    diff-=6;
                }
                else
                {
                    diff+=6;
                }
            }

            teta=((diff/ (RaqRect->w/2. + myRectBalle.w/2.))*(M_PI/2.)) + (M_PI/2.);

            //Permet d'éviter les balles trop horizontales.
            if (teta<0.9) {teta=0.9;}
            if (teta>2.60) {teta=2.60;}
            dX=r*cos(teta);
            dY=-r*sin(teta);
        }

    xBalle=x;
    yBalle=y;
    myRectBalle.x=(int)x;
    myRectBalle.y=(int)y;
    return false;
}

void CBalle::rebondi(double CoeffX,double CoeffY)

{
    dX=(CoeffX*dX);
    dY=(CoeffY*dY);
}

void CBalle::drawBalle(SDL_Surface* destination)
{
    if (myRectBalle.y<320)
    {
        SDL_BlitSurface(myImgBalle,NULL,destination,&myRectBalle);
    }
    else
    {
        SDL_BlitSurface(myImgBalle2,NULL,destination,&myRectBalle);
    }
}

void CBalle::setSpeed(double vitesse)
{
    vitesseBalle=vitesse;
}

SDL_Surface* CBalle::getSurface(){return myImgBalle;} // Utile lors du FreeSurface.
SDL_Rect* CBalle::GetRect(){return &myRectBalle;}
