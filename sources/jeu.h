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
#ifndef Jeu
#define Jeu

#define MAX_BALLES 4
#define MAX_VIES 10

//Points de score
#define SC_NIVEAU 10000
#define SC_LIGNE_1 600
#define SC_LIGNE_2 2500
#define SC_LIGNE_3 10000
#define SC_LIGNE_4 50000
#define SC_LIGNE_BALLE 300
#define SC_CASE_CASSEE 10
#define SC_DESCENTE 10
#define SC_BONUS 1000 //Chaque bonus donne des points
#define SC_BONUS_SCORE 10000 //Bonus spécial.
#define SC_EMPTY_TERRAIN 100000 //Terrain a été vidé.

#include "sdl_includes.h"

#include "figure.h"
#include "brick.h"
#include "balle.h"
#include "terrain.h"
#include "son.h"
#include "bonus.h"

/////////////////////////////////////////////////////////////////////////////////////////////

class CRaquette

{
private:

int properties;
double dX;
SDL_Rect myRectRaquette;
SDL_Surface* m_pRaqGauche;
SDL_Surface* m_pRaqCentre;
SDL_Surface* m_pRaqDroite;
int largeur;


public:

CRaquette();
void initRaquette(int,int,int,double);
void deleteRaquette();
void deplacer(const int&, const int&, SDL_Rect*);
void drawRaquette(SDL_Surface*);
void changerLargeur(int, SDL_Rect *);
SDL_Rect* GetRect();
};

class CJeu
{

private:

CSon mySon;
CRaquette myRaquette;
CBalle * myBalle;
CTerrain myTerrain;
CBrick myBrick;
CBonus myBonus;

//Infos sur le jeu.
int m_iNbVies; //Nombre de vies
int m_iNbBalles; //Nombre de balles en jeu
long m_iLastDescente; //Timer du dernier moment ou le bloc est descendu.
int m_iDureeAttente; //Temps entre deux descente d'un bloc.
long m_iLastStrafe; //Timer du dernier moment ou le bloc a bougé latéralement.
int m_iDureeStrafe; //Temps entre deux déplacements latéraux.
long m_iLastChute; //Timer du dernier moment ou le bloc est descendu par le joueur.
int m_iDureeChute; //Temps entre deux descentes.
int m_iNbLignesDetruites;
int m_iScore;
int m_iNiveau;
int m_iTempsPause;

long m_iTimerPause;

//Pour la police des chiffres
TTF_Font *policeChiffres;

SDL_Surface* m_pScore;
SDL_Surface* m_pNiveau;
SDL_Surface* m_pSuivant;
SDL_Surface* m_pLignes;

SDL_Surface* m_pImgMasque;

bool playing;

long modifRaquette;


SDL_Surface* m_pScreenshot;
SDL_Surface* m_pSpriteOver;
bool affiche;
long m_iLastAffiche; //Timer
int m_iDureeAffiche; //Temps

public:

    CJeu();
    void initJeu(bool,bool,char [MAX_LANG][256]);
    void deleteJeu();
    void drawJeu(SDL_Surface*);
    void deplacerRaquette(const int&, const int&);
    void flipFigure();
    void deplacerBalle(const int&);
    bool allMoveFigure(int, bool, bool, bool);
    bool gameOver();
    void saveLastDisplay(char [MAX_LANG][256]);
    void drawGameOver(SDL_Surface*);
    void niveauSuivant();
    void addLignes(int);
    void makeChiffre(SDL_Surface*&, int);
    void addToScore(int);
    void pauseJeu(char [MAX_LANG][256]);
    void drawPause(SDL_Surface*);
    void reprendreJeu();
    void setDureeAttente();
    double getVitesseBalle();
    int getScore();

};


///////////////////////////////////////////////////////////////////////////////////////////


#endif

