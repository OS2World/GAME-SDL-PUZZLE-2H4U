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

#include "Param.h"

CParam::CParam()
{
    m_czChemin=NULL;
}

void CParam::initParam(const char* czChemin)
{
    m_czChemin=czChemin;

    FILE* fichier = NULL;
    fichier = fopen(m_czChemin, "r");

    if (fichier != NULL)
    {
        // On peut lire et écrire dans le fichier
        fscanf(fichier, "%d %d %d %d %d", &m_iSon, &m_iMusique, &m_iFullscreen, &m_iClavier, &m_iLangue);
        fclose(fichier);
        m_bNew=false;
    }
    else
    {
        //Si le fichier n'existe pas, on va ignorer l'erreur
        fprintf( stderr, "Creating file : config.dat\n");
        //Et on va créer le fichier.
        m_iSon=1; //ON
        m_iMusique=1; //ON
        m_iFullscreen=0; //ON
        m_iClavier=0; //Azerty
        m_iLangue=0; //Français
        m_bNew=true;
        saveParam();
    }
}

void CParam::getTxtLang(char lang[MAX_LANG][256])
{

    char buffer[256];
    int l;
    FILE* fichier = NULL;

    sprintf(buffer,"data/lang/%d.txt",m_iLangue);

    fichier = fopen(buffer, "r");
    if (fichier != NULL)
    {
        for (int i=0;i<MAX_LANG;i++)
        {
            fgets (lang[i], 100 ,fichier);
            l=strlen(lang[i]);
            lang[i][l-1]='\0';
        }
    }
    else
    {
        //Si le fichier n'existe pas --> On quitte
        fprintf( stderr, "Error : Lang file number %d doesn't exist in CParam->initLang() Path is : %s\n",m_iLangue,buffer);
        exit(-1);
    }
}

void CParam::saveParam()
{
    FILE* fichier = NULL;
    fichier = fopen(m_czChemin, "w");
    if (fichier != NULL)
    {
        fprintf(fichier, "%d %d %d %d %d", m_iSon, m_iMusique, m_iFullscreen, m_iClavier, m_iLangue);
        fclose(fichier);
    }
    else
    {
        //On note l'erreur, mais on ne quitte pas.
        fprintf( stderr, "Uncritical error in saveParam() : cannot create parameter file.\n");
    }
}

//Pour changer les paramètres de l'extérieur.
void CParam::flipSon()
{
    if (m_iSon==0) m_iSon=1;
    else m_iSon=0;
}

void CParam::flipMusique()
{
    if (m_iMusique==0) m_iMusique=1;
    else m_iMusique=0;
}

void CParam::flipFullscreen()
{
    if (m_iFullscreen==0) m_iFullscreen=1;
    else m_iFullscreen=0;
}

void CParam::flipClavier()
{
    if (m_iClavier==0) m_iClavier=1;
    else m_iClavier=0;
}

void CParam::flipLangue()
{
    if (m_iLangue==0) m_iLangue=1;
    else m_iLangue=0;
}

int CParam::getSon()
{
    return m_iSon;
}

int CParam::getMusique()
{
    return m_iMusique;
}

int CParam::getFullscreen()
{
    return m_iFullscreen;
}

int CParam::getClavier()
{
    return m_iClavier;
}

int CParam::getLangue()
{
    return m_iLangue;
}

bool CParam::getNew()
{
    return m_bNew;
}
