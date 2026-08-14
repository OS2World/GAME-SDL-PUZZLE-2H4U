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
/////////////////////////////////////////////////////////////////////////////////////////////////
#include "brick.h"

CBrick::CBrick(){}

void CBrick::initBrick(int prop, int col)
{
    properties = prop;
    color = col;

}

CBrick::~CBrick(){}

void CBrick::deleteBrick()
{
    properties = -1;
    color=-1;

}

void CBrick::reduire()
{
    properties -= 1;
}


int CBrick::getProperties()
{return properties;}

int CBrick::getColor()
{return color;}
