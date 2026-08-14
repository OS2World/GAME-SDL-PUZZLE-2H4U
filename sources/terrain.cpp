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
#include "terrain.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
CTerrain::CTerrain()
{
    m_pBrick = new CBrick** [NBCASEX];

    for (int i=0;i<NBCASEX;i++)
    {
        m_pBrick[i] = new CBrick*[NBCASEY];
    }

    for (int i=0;i<NBCASEX;i++)
    {
        for (int j=0;j<NBCASEY;j++)
            m_pBrick[i][j] = new CBrick();
    }

    m_pFigBrick[0] = new CBrick();
    m_pFigBrick[1] = new CBrick();
    m_pFigBrick[2] = new CBrick();
    m_pFigBrick[3] = new CBrick();

    m_pBrickVide = new CBrick();

    //Nombre de couleurs : 7
    m_pImgCT = new SDL_Surface* [7];


    m_pImgFigure = new SDL_Surface* [7];
}

void CTerrain::initTerrain(char lang[MAX_LANG][256])
{
    myImgTerrain=IMG_Load("data/images/jeu/terrain.jpg");

    TTF_Font *policeTxt = TTF_OpenFont("data/bgothm.ttf", 22);
    SDL_Color couleurTxt = { 250, 60, 0 };
    SDL_Surface* tempTxt=NULL;
    SDL_Rect centrage;

    int posY[6]={43,193,240,290,340,444};

    for (int i=0;i<6;i++)
    {
        if (tempTxt!=NULL)
        {
            SDL_FreeSurface(tempTxt);
        }
        tempTxt = TTF_RenderText_Blended(policeTxt, lang[i+8], couleurTxt);

        centrage.x=662-(tempTxt->w/2);
        centrage.y=posY[i];
        centrage.w=tempTxt->w;
        centrage.h=tempTxt->h;
        SDL_BlitSurface(tempTxt,NULL,myImgTerrain,&centrage);
    }

    TTF_CloseFont(policeTxt);

    myRectTerrain.x=2;
    myRectTerrain.y=0;

    //ici on charge toutes les images de briques.
    char buffer[256];
    for (int i=0;i<7;i++)
    {
        sprintf(buffer,"data/images/jeu/briques/b%d0.png",i);
        m_pImgCT[i]=IMG_Load(buffer);
    }
    m_pBriqueCassee=IMG_Load("data/images/jeu/briques/bgris.png");

    //Chargement des formes a montrer :
    for (int i=0;i<7;i++)
    {
        sprintf(buffer,"data/images/jeu/formes/%d.png",i);
        m_pImgFigure[i]=IMG_Load(buffer);
    }

    myRectTerrain.w=NBCASEX*m_pBriqueCassee->w; //540
    myRectTerrain.h=600;

    //Taille en pixels d'une brique.
    m_iTailleBrick=m_pBriqueCassee->w;

    for (int i=0;i<NBCASEX;i++)
    {
        for (int j=0;j<NBCASEY;j++)
        {
                m_pBrick[i][j]->initBrick(-1,0);
        }
    }

    int Startingfigure=rand()%7;
    m_iNextFig=rand()%7;

    myFigure.InitFigure(Startingfigure,m_pBrick);


    m_pFigBrick[0]->initBrick(-1,1);
    m_pFigBrick[1]->initBrick(-1,1);
    m_pFigBrick[2]->initBrick(-1,1);
    m_pFigBrick[3]->initBrick(-1,1);

    int ** figure=myFigure.ReturnCaseOccupees();

    m_pBrick[figure[0][0]][figure[0][1]]->initBrick(1,Startingfigure);
    m_pBrick[figure[1][0]][figure[1][1]]->initBrick(1,Startingfigure);
    m_pBrick[figure[2][0]][figure[2][1]]->initBrick(1,Startingfigure);
    m_pBrick[figure[3][0]][figure[3][1]]->initBrick(1,Startingfigure);

    m_bBalleDestructionLigne=false;

    m_iNbBriquesDestroy=0;

}

void CTerrain::rndFillTerrain(int nbLignes)
{
    int jDep=NBCASEY-nbLignes;
    for (int j=jDep;j<NBCASEY;j++)
    {
        for (int i=0;i<NBCASEX;i++)
        {
            if (i!=j) //Pour �viter que toutes les cases soient remplies
            {
                if (rand()%2==0) m_pBrick[i][j]->initBrick(1,rand()%7);
            }
        }
    }
}


void CTerrain::deleteTerrain()
{

    SDL_FreeSurface(myImgTerrain);

    for (int i=0;i<7;i++)
    {
        SDL_FreeSurface(m_pImgCT[i]);
    }
    SDL_FreeSurface(m_pBriqueCassee);

    for (int i=0;i<7;i++)
    {
        SDL_FreeSurface(m_pImgFigure[i]);
    }

}

/*
Cette fonction permet de g�rer la collision entre la balle et le mur de briques.
Elle recoit en param�tre la position de de la balle avant le mouvement (les oldXb, oldYb),
ainsi que la position apr�s le mouvement (xb, yb).
Il s'agit bien entendu de la position du coin sup�rieur gauche de la balle.
Elle recoit aussi la largeur de la balle (sb), consid�r�e comme un carr�.
Cette fonction retourne un entier indiquant le type de collision :
0 pour pas de collision, 1 pour collision horizontale, 2 pour verticale, 3 pour horizontal et vertical.
Une collision horizontale signifie que la balle a frapp� le dessus d'une ou plusieurs briques.
Une collision verticale signifie que la balle a frapp� le cot� d'une ou plusieurs briques.
Cette fonction est une des plus complexes, a terme, du programme.

Voici en gros le d�roulement qu'elle devrait avoir :
-On regarde sur quelles briques est la balle, sachant qu'elle peut etre sur 1, 2 ou 4 briques.
-On regarde les briques qui existent.
-On r�duit la vie des briques.
-On renvoi la zone d'impact : rien, vertical, horizontal, ou horizontal et vertical (si possible).

*/

//Cette version fonctionne parfaitement.
//Approximation : on suppose que le dx et le dy de la balle sont tr�s petits.
int CTerrain::collisionBriques(int xb, int yb, int oldXb, int oldYb, int sb)
{
    int brickX, brickY, tempX, tempY;

    double cdB, cdO;

    bool collision;

    collision=false;

    if (yb<myRectTerrain.y + m_iTailleBrick*NBCASEY)
    {
        //Coordonn�es de la case dans laquelle est le point en haut a gauche du carr� de la balle.
        tempX=(xb-myRectTerrain.x)/m_iTailleBrick;
        tempY=(yb-myRectTerrain.y)/m_iTailleBrick;
        if (((xb-myRectTerrain.x)%m_iTailleBrick)==0)
        {
            if (((yb-myRectTerrain.y)%m_iTailleBrick)==0)
            {
                //1 case
                if (gereCollision(tempX,tempY)==true)
                {
                    collision=true;
                    brickX=tempX;
                    brickY=tempY;
                }
            }
            else
            {
                //2 cases verticalement
                if (tempY+1<NBCASEY)
                {
                    if (gereCollision(tempX,tempY+1)==true)
                    {
                        collision=true;
                        brickX=tempX;
                        brickY=tempY+1;
                    }
                }
                //Chaque test doit etre fait quoi qu'il arrive.
                if (gereCollision(tempX,tempY)==true)
                {
                    collision=true;
                    brickX=tempX;
                    brickY=tempY;
                }
            }
        }
        else
        {
            if (((yb-myRectTerrain.y)%m_iTailleBrick)==0)
            {
                //2 cases horizontalement
                if (tempX+1<NBCASEX)
                {
                    if (gereCollision(tempX+1,tempY)==true)
                    {
                        collision=true;
                        brickX=tempX+1;
                        brickY=tempY;
                    }
                }
                //Chaque test doit etre fait quoi qu'il arrive.
                if (gereCollision(tempX,tempY)==true)
                {
                    collision=true;
                    brickX=tempX;
                    brickY=tempY;
                }
            }
            else
            {
            //4 cases (le plus courant)
                if (tempX+1<NBCASEX && tempY+1<NBCASEY)
                {
                    if (gereCollision(tempX+1,tempY+1)==true)
                    {
                        collision=true;
                        brickX=tempX+1;
                        brickY=tempY+1;
                    }
                }
                //Chaque test doit etre fait quoi qu'il arrive.
                if (tempX+1<NBCASEX)
                {
                    if (gereCollision(tempX+1,tempY)==true)
                    {
                        collision=true;
                        brickX=tempX+1;
                        brickY=tempY;
                    }
                }
                if (tempY+1<NBCASEY)
                {
                    if (gereCollision(tempX,tempY+1)==true)
                    {
                        collision=true;
                        brickX=tempX;
                        brickY=tempY+1;
                    }
                }
                //Chaque test doit etre fait quoi qu'il arrive.
                if (gereCollision(tempX,tempY)==true)
                {
                    collision=true;
                    brickX=tempX;
                    brickY=tempY;
                }
            }
        }

        //Voyons s'il ya eu une collision.
        if (collision==true)
        {
            int xt=myRectTerrain.x + brickX*m_iTailleBrick;
            int yt=myRectTerrain.y + brickY*m_iTailleBrick;
            //Valeur absolue du coefficient directeur du d�placement de la balle.
            if (xb-oldXb==0) return 2;
            if (oldXb-xt==0) return 2;

            if (oldXb + sb > xt && oldXb < xt + m_iTailleBrick)
            {
                return 2;
            }

            if (oldYb + sb > yt && oldYb < yt + m_iTailleBrick)
            {
                return 1;
            }

            cdB = ((yb-oldYb)*1.0)/(xb-oldXb);
            //Valeur absolue du coefficient directeur du d�placement entre la balle et la brique.
            cdO = ((oldYb-yt)*1.0)/(oldXb-xt);


            cdB=fabs(cdB);
            cdO=fabs(cdO);

            if (cdB>cdO)
            {
                return 1;
            }
            else
                if (cdB<cdO)
                {
                    return 2;
                }
                else return 3;
        }
    }
    //Pas de collision.
    return 0;


}

// :D Permet de savoir si la balle a d�truite une ligne.
bool CTerrain::getBalleDestruction(int &nbBriquesCassees)
{
    nbBriquesCassees=m_iNbBriquesDestroy;
    m_iNbBriquesDestroy=0;
    if (m_bBalleDestructionLigne==true)
    {
        m_bBalleDestructionLigne=false;
        return true;
    }
    else return false;
}

bool CTerrain::gereCollision(int tempX, int tempY)
{
    if (m_pBrick[tempX][tempY]->getProperties()>0)
    {
        m_iNbBriquesDestroy++;
        m_pBrick[tempX][tempY]->reduire();

        permuterFigure();
        if (isEmptyLine(tempY,true))
        {
            m_bBalleDestructionLigne=true;
            deleteLine(tempY,true);
        }
        if (isEmptyLine(tempY,false))
        {
            m_bBalleDestructionLigne=true;
            deleteLine(tempY,false);
        }
        permuterFigure();

        return true;
     }
     else return false;
}

void CTerrain::drawTerrain(SDL_Surface* destination)
{
    SDL_Rect posTemp,nulRect;

    nulRect.x=0;
    nulRect.y=0;
    nulRect.w=800;
    nulRect.h=600;

    SDL_BlitSurface(myImgTerrain,&nulRect,destination,&nulRect);

    //On dessine les briques.
    posTemp.w=m_iTailleBrick;
    posTemp.h=m_iTailleBrick;
    for (int i=0;i<NBCASEX;i++)
    {
        for (int j=0;j<NBCASEY;j++)
        {
            //On affiche la brique, si elle existe.
            //Sert aussi a l'affichage des objets qui descendent.
            if(m_pBrick[i][j]->getProperties()>-1)
            {
                posTemp.x=myRectTerrain.x + i*m_iTailleBrick;
                posTemp.y=myRectTerrain.y + j*m_iTailleBrick;
                if(m_pBrick[i][j]->getProperties()==0)
                    SDL_BlitSurface(m_pBriqueCassee,NULL,destination,&posTemp);
                else
                    SDL_BlitSurface(m_pImgCT[m_pBrick[i][j]->getColor()],NULL,destination,&posTemp);
            }
        }
    }

    posTemp.x=630;
    posTemp.y=80;
    posTemp.w=m_pImgFigure[m_iNextFig]->w;
    posTemp.h=m_pImgFigure[m_iNextFig]->h;
    //On dessine la next forme.
    SDL_BlitSurface(m_pImgFigure[m_iNextFig],NULL,destination,&posTemp);
}

SDL_Rect* CTerrain::GetRect() {return &myRectTerrain;}


void CTerrain::permuterFigure()
{
    int ** figure=myFigure.ReturnCaseOccupees();

    for (int i=0;i<4;i++)
    {
        m_pBrickVide=m_pFigBrick[i];
        m_pFigBrick[i]=m_pBrick[figure[i][0]][figure[i][1]];
        m_pBrick[figure[i][0]][figure[i][1]]=m_pBrickVide;
    }
}


bool CTerrain::rotationFigure()
{
    return myFigure.Rotation(m_pBrick);
}

//On d�place la figure en x et y
bool CTerrain::moveFigure(int a,int b)
{
    return myFigure.ModifCoord(a, b, m_pBrick);
}

//On pose la figure sur le terrain, en dur.
//On initialise une nouvelle figure.
bool CTerrain::dropFigure()
{
    bool possible;

    permuterFigure();

    possible=myFigure.InitFigure(m_iNextFig, m_pBrick);



    m_pFigBrick[0]->initBrick(1,m_iNextFig);
    m_pFigBrick[1]->initBrick(1,m_iNextFig);
    m_pFigBrick[2]->initBrick(1,m_iNextFig);
    m_pFigBrick[3]->initBrick(1,m_iNextFig);

    m_iNextFig=rand()%7;

    return possible;
}

//Renvoie le nombre de lignes pleines.
int CTerrain::findFullLine()
{
    int nbFull=0;
    for (int y=0;y<NBCASEY;y++)
    {
        if (isFullLine(y,true))
        {
            nbFull++;
            deleteLine(y,true);
        }
        if (isFullLine(y,false))
        {
            nbFull++;
            deleteLine(y,false);
        }
    }
    return nbFull;
}

bool CTerrain::isEmptyTerrain()
{
    for (int y=0;y<NBCASEY;y++)
    {
        for (int x=0;x<NBCASEX;x++)
        {
            if (m_pBrick[x][y]->getProperties()!=-1) return false;
        }
    }
    return true;
}

//Indique si une ligne est totalement pleine.
//Donc remplie par casse brique
bool CTerrain::isFullLine(int y,bool gauche)
{
    if (gauche==true)
    {
        for (int x=0;x<NBCASEX/2;x++)
        {
            if (m_pBrick[x][y]->getProperties()<0) return false;
        }
    }
    else
    {
        for (int x=NBCASEX/2;x<NBCASEX;x++)
        {
            if (m_pBrick[x][y]->getProperties()<0) return false;
        }
    }
    return true;

}

//Renvoie le nombre de lignes totalement cass�es
int CTerrain::findEmptyLine()
{
    int nbEmpty=0;
    for (int y=0;y<NBCASEY;y++)
    {
        if (isEmptyLine(y,true) && isEmptyLine(y,false))
        {
            nbEmpty++;
            deleteLine(y,true);
            deleteLine(y,false);
        }
    }
    return nbEmpty;
}

//Indique si une ligne est totalement vide
//Donc vid�e par la balle.
bool CTerrain::isEmptyLine(int y,bool gauche)
{
    int somme=0;
    if (gauche==true)
    {
        for (int x=0;x<NBCASEX/2;x++)
        {
            if (m_pBrick[x][y]->getProperties()>0) return false;
            if (m_pBrick[x][y]->getProperties()==0) somme++;
        }
    }
    else
    {
        for (int x=NBCASEX/2;x<NBCASEX;x++)
        {
            if (m_pBrick[x][y]->getProperties()>0) return false;
            if (m_pBrick[x][y]->getProperties()==0) somme++;
        }
    }
    if (somme!=0) return true;
    else return false;
}


//Supprime une ligne.
void CTerrain::deleteLine(const int& yDel,bool gauche)
{
    //On vide la ligne en question.
    if (gauche==true)
    {
        for (int x=0;x<NBCASEX/2;x++)
        {
            m_pBrick[x][yDel]->initBrick(-1,1);
        }
    }
    else
    {
        for (int x=NBCASEX/2;x<NBCASEX;x++)
        {
            m_pBrick[x][yDel]->initBrick(-1,1);
        }
    }


    for (int y=yDel;y>0;y--)
    {
        permuterLignes(y,y-1,gauche);
    }

}

//Permute deux lignes. -->circulaire.
void CTerrain::permuterLignes(int y1, int y2,bool gauche)
{
    //On vide la ligne en question.
    if (gauche==true)
    {
        for (int x=0;x<NBCASEX/2;x++)
        {
            m_pBrickVide=m_pBrick[x][y1];
            m_pBrick[x][y1]=m_pBrick[x][y2];
            m_pBrick[x][y2]=m_pBrickVide;
        }
    }
    else
    {
        for (int x=NBCASEX/2;x<NBCASEX;x++)
        {
            m_pBrickVide=m_pBrick[x][y1];
            m_pBrick[x][y1]=m_pBrick[x][y2];
            m_pBrick[x][y2]=m_pBrickVide;
        }
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////
