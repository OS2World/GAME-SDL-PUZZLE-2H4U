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
#include"figure.h"



CFigure::CFigure(){}


bool CFigure::InitFigure(int f,CBrick *** &MurBrick)
{

forme=f;
state=0;

posX=(rand()%(NBCASEX-6))+2;

posY=1;

return FCaseOccupees(MurBrick,true); //Doit obligatoirement renvoyer true, sinon ca foire tout. Pensez a faire une gestion d'erreur.

}

//////////////////////////////////////////////////////////

int CFigure::Forme()
{return forme;}

/////////////////////////////////////////////////////////

int CFigure::State()
{return state;}

//A toi de calculer s'il ya collision et si les cases sont bien dans la map.
//Renvoie true si collision ou cases hors de la map.
bool CFigure::collision(int cases[4][2],CBrick *** &MurBrick)
{
    int cx=NBCASEX;
    int cy=NBCASEY;
    int a,b,c,d,e,f,g,h;
    int c1,c2,c3,c4;

    a=cases[0][0];b=cases[0][1];
    c=cases[1][0];d=cases[1][1];
    e=cases[2][0];f=cases[2][1];
    g=cases[3][0];h=cases[3][1];

if((a<0||a>cx-1)||(c<0||c>cx-1)||(e<0||e>cx-1)||(g<0||g>cx-1)||(b<0||b>cy-1)||(d<0||d>cy-1)||(f<0||f>cy-1)||(h<0||h>cy-1))
       return true;
else{
    c1=MurBrick[a][b]->getProperties();
    c2=MurBrick[c][d]->getProperties();
    c3=MurBrick[e][f]->getProperties();
    c4=MurBrick[g][h]->getProperties();

    if((c1>=0)||(c2>=0)||(c3>=0)||(c4>=0))return true;
    else return false;

}
}

//////////////////////////////////////////////////////////
//Cf a la fin pour le modification du  tablo des cases.
//Fcaseoccupée renvoie true si tout c'est bien passé, false si ca a pa pu pour cause de collision
bool CFigure::FCaseOccupees(CBrick *** &MurBrick,bool force=false)
{

int TCaseOccupees[4][2];

switch(forme)
{
case 0 :
    if(state==0)
    {
        TCaseOccupees[0][0]=posX;TCaseOccupees[0][1]=posY;
        TCaseOccupees[1][0]=posX;TCaseOccupees[1][1]=posY+1;
        TCaseOccupees[2][0]=posX+1;TCaseOccupees[2][1]=posY+1;
        TCaseOccupees[3][0]=posX+1;TCaseOccupees[3][1]=posY;
    }
    else if(state==1)
    {
        TCaseOccupees[0][0]=posX+1;TCaseOccupees[0][1]=posY;
        TCaseOccupees[1][0]=posX;TCaseOccupees[1][1]=posY;
        TCaseOccupees[2][0]=posX;TCaseOccupees[2][1]=posY+1;
        TCaseOccupees[3][0]=posX+1;TCaseOccupees[3][1]=posY+1;
    }
    else if(state==2)
    {
        TCaseOccupees[0][0]=posX+1;TCaseOccupees[0][1]=posY+1;
        TCaseOccupees[1][0]=posX+1;TCaseOccupees[1][1]=posY;
        TCaseOccupees[2][0]=posX;TCaseOccupees[2][1]=posY;
        TCaseOccupees[3][0]=posX;TCaseOccupees[3][1]=posY+1;
    }
    else if(state==3)
    {
        TCaseOccupees[0][0]=posX;TCaseOccupees[0][1]=posY+1;
        TCaseOccupees[1][0]=posX+1;TCaseOccupees[1][1]=posY+1;
        TCaseOccupees[2][0]=posX+1;TCaseOccupees[2][1]=posY;
        TCaseOccupees[3][0]=posX;TCaseOccupees[3][1]=posY;
    }
break;

case 1 :
    if(state==0)
    {
        TCaseOccupees[0][0]=posX-1;TCaseOccupees[0][1]=posY;
        TCaseOccupees[1][0]=posX;TCaseOccupees[1][1]=posY;
        TCaseOccupees[2][0]=posX+1;TCaseOccupees[2][1]=posY;
        TCaseOccupees[3][0]=posX+2;TCaseOccupees[3][1]=posY;
        break;
    }
    if(state==1)
    {
        TCaseOccupees[0][0]=posX;TCaseOccupees[0][1]=posY-2;
        TCaseOccupees[1][0]=posX;TCaseOccupees[1][1]=posY-1;
        TCaseOccupees[2][0]=posX;TCaseOccupees[2][1]=posY;
        TCaseOccupees[3][0]=posX;TCaseOccupees[3][1]=posY+1;
        break;
    }


case 2 :
    if(state==0){TCaseOccupees[0][0]=posX-1;TCaseOccupees[0][1]=posY;
                 TCaseOccupees[2][0]=posX;TCaseOccupees[2][1]=posY;
                 TCaseOccupees[1][0]=posX+1;TCaseOccupees[1][1]=posY;
                 TCaseOccupees[3][0]=posX-1;TCaseOccupees[3][1]=posY+1;
                 break;
                }
    if(state==1){TCaseOccupees[0][0]=posX-1;TCaseOccupees[0][1]=posY-1;
                TCaseOccupees[1][0]=posX;TCaseOccupees[1][1]=posY-1;
                TCaseOccupees[2][0]=posX;TCaseOccupees[2][1]=posY;
                TCaseOccupees[3][0]=posX;TCaseOccupees[3][1]=posY+1;
                break;
                }
    if(state==2){TCaseOccupees[0][0]=posX-1;TCaseOccupees[0][1]=posY;
                TCaseOccupees[1][0]=posX;TCaseOccupees[1][1]=posY;
                TCaseOccupees[2][0]=posX+1;TCaseOccupees[2][1]=posY;
                TCaseOccupees[3][0]=posX+1;TCaseOccupees[3][1]=posY-1;
                break;
                }
    if(state==3){TCaseOccupees[0][0]=posX;TCaseOccupees[0][1]=posY-1;
                TCaseOccupees[1][0]=posX;TCaseOccupees[1][1]=posY;
                TCaseOccupees[2][0]=posX;TCaseOccupees[2][1]=posY+1;
                TCaseOccupees[3][0]=posX+1;TCaseOccupees[3][1]=posY+1;
                break;
                }



case 3 :
    if(state==0){TCaseOccupees[0][0]=posX-1;TCaseOccupees[0][1]=posY;
                TCaseOccupees[1][0]=posX;TCaseOccupees[1][1]=posY;
                TCaseOccupees[2][0]=posX+1;TCaseOccupees[2][1]=posY;
                TCaseOccupees[3][0]=posX+1;TCaseOccupees[3][1]=posY+1;
                break;
                }
    if(state==1){TCaseOccupees[0][0]=posX;TCaseOccupees[0][1]=posY-1;
                TCaseOccupees[1][0]=posX;TCaseOccupees[1][1]=posY;
                TCaseOccupees[2][0]=posX;TCaseOccupees[2][1]=posY+1;
                TCaseOccupees[3][0]=posX-1;TCaseOccupees[3][1]=posY+1;
                break;
                }
    if(state==2){TCaseOccupees[0][0]=posX-1;TCaseOccupees[0][1]=posY;
                TCaseOccupees[1][0]=posX;TCaseOccupees[1][1]=posY;
                TCaseOccupees[2][0]=posX+1;TCaseOccupees[2][1]=posY;
                TCaseOccupees[3][0]=posX-1;TCaseOccupees[3][1]=posY-1;
                break;
                }
    if(state==3){TCaseOccupees[0][0]=posX;TCaseOccupees[0][1]=posY-1;
                TCaseOccupees[1][0]=posX;TCaseOccupees[1][1]=posY;
                TCaseOccupees[2][0]=posX;TCaseOccupees[2][1]=posY+1;
                TCaseOccupees[3][0]=posX+1;TCaseOccupees[3][1]=posY-1;
                break;
                }

case 4 :
    if(state==0){TCaseOccupees[0][0]=posX;TCaseOccupees[0][1]=posY;
                TCaseOccupees[1][0]=posX+1;TCaseOccupees[1][1]=posY;
                TCaseOccupees[2][0]=posX+1;TCaseOccupees[2][1]=posY+1;
                TCaseOccupees[3][0]=posX+2;TCaseOccupees[3][1]=posY+1;
                break;
                }
    if(state==1){TCaseOccupees[0][0]=posX;TCaseOccupees[0][1]=posY;
                TCaseOccupees[1][0]=posX+1;TCaseOccupees[1][1]=posY;
                TCaseOccupees[2][0]=posX;TCaseOccupees[2][1]=posY+1;
                TCaseOccupees[3][0]=posX+1;TCaseOccupees[3][1]=posY-1;
                break;
                }

case 5 :
    if(state==0){TCaseOccupees[0][0]=posX;TCaseOccupees[0][1]=posY;
                TCaseOccupees[1][0]=posX;TCaseOccupees[1][1]=posY+1;
                TCaseOccupees[2][0]=posX+1;TCaseOccupees[2][1]=posY;
                TCaseOccupees[3][0]=posX-1;TCaseOccupees[3][1]=posY+1;
                break;
                }
    if(state==1){TCaseOccupees[0][0]=posX;TCaseOccupees[0][1]=posY;
                TCaseOccupees[1][0]=posX;TCaseOccupees[1][1]=posY+1;
                TCaseOccupees[2][0]=posX-1;TCaseOccupees[2][1]=posY;
                TCaseOccupees[3][0]=posX-1;TCaseOccupees[3][1]=posY-1;
                break;
                }
case 6 :
     if (state==0){TCaseOccupees[0][0]=posX;TCaseOccupees[0][1]=posY;
                TCaseOccupees[1][0]=posX+1;TCaseOccupees[1][1]=posY;
                TCaseOccupees[2][0]=posX-1;TCaseOccupees[2][1]=posY;
                TCaseOccupees[3][0]=posX;TCaseOccupees[3][1]=posY+1;
                break;
                }
     if (state==1){TCaseOccupees[0][0]=posX;TCaseOccupees[0][1]=posY;
                TCaseOccupees[1][0]=posX;TCaseOccupees[1][1]=posY-1;
                TCaseOccupees[2][0]=posX;TCaseOccupees[2][1]=posY+1;
                TCaseOccupees[3][0]=posX-1;TCaseOccupees[3][1]=posY;
                break;
                }
     if (state==2){TCaseOccupees[0][0]=posX;TCaseOccupees[0][1]=posY;
                TCaseOccupees[1][0]=posX-1;TCaseOccupees[1][1]=posY;
                TCaseOccupees[2][0]=posX+1;TCaseOccupees[2][1]=posY;
                TCaseOccupees[3][0]=posX;TCaseOccupees[3][1]=posY-1;
                break;
                }
      if (state==3){TCaseOccupees[0][0]=posX;TCaseOccupees[0][1]=posY;
                TCaseOccupees[1][0]=posX;TCaseOccupees[1][1]=posY-1;
                TCaseOccupees[2][0]=posX;TCaseOccupees[2][1]=posY+1;
                TCaseOccupees[3][0]=posX+1;TCaseOccupees[3][1]=posY;
                break;
                }

} // fin switch

//Mettre ici l'appel a une fonction qui recoit TCaseOccupees[0][0] et le tableau de briques en paramètres
//et renvoie true si pas de collision
if (!collision(TCaseOccupees,MurBrick))
{
    CaseOccupees[0][0]=TCaseOccupees[0][0];
    CaseOccupees[1][0]=TCaseOccupees[1][0];
    CaseOccupees[2][0]=TCaseOccupees[2][0];
    CaseOccupees[3][0]=TCaseOccupees[3][0];
    CaseOccupees[0][1]=TCaseOccupees[0][1];
    CaseOccupees[1][1]=TCaseOccupees[1][1];
    CaseOccupees[2][1]=TCaseOccupees[2][1];
    CaseOccupees[3][1]=TCaseOccupees[3][1];
    return true;
}
else
{
    //force permet de forcer la case a etre a cet endroit quand meme--> pour init, quand on a game over.
    if (force==true)
    {
    CaseOccupees[0][0]=TCaseOccupees[0][0];
    CaseOccupees[1][0]=TCaseOccupees[1][0];
    CaseOccupees[2][0]=TCaseOccupees[2][0];
    CaseOccupees[3][0]=TCaseOccupees[3][0];
    CaseOccupees[0][1]=TCaseOccupees[0][1];
    CaseOccupees[1][1]=TCaseOccupees[1][1];
    CaseOccupees[2][1]=TCaseOccupees[2][1];
    CaseOccupees[3][1]=TCaseOccupees[3][1];
    }
    return false; // et case occupée renvoi la valeur d'avant.
}

} // fin CaseOccupees()


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//renvoie true si la rotation a pu etre réalisé.
bool CFigure::Rotation(CBrick *** &MurBrick)
{

int old_state=state;//Si jamais ca passe pas.
int oldPosX=posX;
int oldPosY=posY;

state+=1;


switch(forme)
{
    case 0 : state%=4;break;
    case 1 : state%=2;break;
    case 2 : state%=4;break;
    case 3 : state%=4;break;
    case 4 : state%=2;break;
    case 5 : state%=2;break;
    case 6 : state%=4;break;
}

//On appelle FCaseOccupees(); une fois que c'est fait.
//Renvoie true si ca s'est bien passé.
if (FCaseOccupees(MurBrick)==true)
{
    return true;
}
else
{
    state = old_state;
    posX=oldPosX;
    posY=oldPosY;
    return false;
}


}//Fin rotation
//////////////////////////////////////////////////////////////////////
//renvoie true si le mouvement a pu etre réalisé.
bool CFigure::ModifCoord(int a, int b,CBrick *** &MurBrick)
{
    int oldPosX=posX;
    int oldPosY=posY;

    posX = posX + a;
    posY = posY + b;
    if(FCaseOccupees(MurBrick)==true)
    {
        return true;
    }
    else
    {
        posX=oldPosX;
        posY=oldPosY;
        return false;
    }
}
/////////////////////////////////////////////////////////////////////////////

int ** CFigure::ReturnCaseOccupees()
{
int **myNewTab;
myNewTab = new int*[4];
for(int i=0;i<4;i++)
        {
        myNewTab[i] = new int[2];
        }
for (int i=0;i<4;i++)
    {
    for(int j=0;j<2;j++)
            {
            myNewTab[i][j]= CaseOccupees[i][j];
             }
    }

return myNewTab;
}
