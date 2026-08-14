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
#include "highscore.h"

CHighscore::CHighscore() {}

void CHighscore::loadHighscore(const char* czChemin)
{
    FILE* fichier = NULL;

    m_czChemin=czChemin;

    fichier = fopen(m_czChemin, "r");

    if (fichier != NULL)
    {
        //On r�cup�re la chaine
        fscanf(fichier, "%ld %ld %ld %ld %ld", &hs[0], &hs[1],&hs[2], &hs[3], &hs[4]);
        fclose(fichier);

        if (uncryptScores()==false)
        {
            fprintf(stderr,"Erreur non critique : fichier de highscores corrompu\n");
            for (int i=0;i<5;i++)   hs[i]=0;
            //Cr�ation du fichier.
            creerFichierHighscore();
        }
    }
    else
    {
        //Si le fichier n'existe pas, on va ignorer l'erreur
        fprintf( stderr, "Erreur non critique : fichier de highscores n'existe pas --> Cr��.\n");
        for (int i=0;i<5;i++)   hs[i]=0;
        //Cr�ation du fichier.
        creerFichierHighscore();
    }

}

//Fonction de d�cryptage du fichier de higscore.
bool CHighscore::uncryptScores()
{
    long cle=CLE;
    long ajout=AJOUT;
    for (int i=0;i<5;i++)
    {
        hs[i]^=cle;

        hs[i]-=ajout-cle;
        if ((hs[i]%ajout)==0)
        {

            hs[i]/=ajout;
            hs[i]-= (i+1);

        }
        else return false;

    }

    return true;
}

//Fonction de cryptage du fichier de highscore.
void CHighscore::cryptScores()
{
    long cle=CLE;
    long ajout=AJOUT;
    for (int i=0;i<5;i++)
    {
        //On multiplie le score par un nombre premier, et on ajoute une valeur pour que 0 ne donne pas 0.

        hs[i]+=(i+1);
        hs[i]*=ajout;
        hs[i]+=ajout-cle;
        //On fais un cryptage XOR (il faut que hs diff�rent de 0 sinon faille).
        hs[i]^=cle;
    }
}

//Pour sauvegarder les scores, crypt�s.
void CHighscore::creerFichierHighscore()
{
    FILE* fichier = NULL;

    fichier = fopen(m_czChemin, "w");

    if (fichier != NULL)
    {
        cryptScores();

        fprintf(fichier, "%ld %ld %ld %ld %ld",hs[0],hs[1],hs[2],hs[3],hs[4]);
        fclose(fichier);

        uncryptScores();
    }
    else
    {
        //Si le fichier n'existe pas, on va ignorer l'erreur
        fprintf( stderr, "Erreur non critique : Cr�ation du fichier de Highscore impossible. Tant pis.\n");
    }
}

void CHighscore::AjouterScore(int score)
{
    int position=-1;
    for (int i=4;i>=0;i--)
    {
        if (score>hs[i]) position=i;
    }
    if (position!=-1)
    {
        for (int i=4;i>position;i--)
        {
            hs[i]=hs[i-1];
        }
        hs[position]=score;
    }
}

int CHighscore::getScore(int position)
{
    return hs[position];
}
