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
//Fichier qui contient tous les includes de SDL.

//Uncomment the following line to disables sounds in 2H4U.
//#define NO_SOUND_2H4U

//IF compiling with MAC
#ifdef MAC_OS

    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #include <SDL2/SDL_mixer.h>

#else

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #ifndef NO_SOUND_2H4U
        #include <SDL2/SDL_mixer.h>
    #endif

#endif

#include <cstdlib>

//Nombre de lignes dans les fichiers de langue
#define MAX_LANG 19

// SDL1 to SDL2 compatibility macros
#ifndef SDL_HWSURFACE
#define SDL_HWSURFACE 0
#endif
#ifndef SDL_SWSURFACE
#define SDL_SWSURFACE 0
#endif
#ifndef SDL_DOUBLEBUF
#define SDL_DOUBLEBUF 0
#endif
#ifndef SDL_ANYFORMAT
#define SDL_ANYFORMAT 0
#endif
#ifndef SDL_FULLSCREEN
#define SDL_FULLSCREEN SDL_WINDOW_FULLSCREEN
#endif
#ifndef SDL_OPENGL
#define SDL_OPENGL SDL_WINDOW_OPENGL
#endif
#ifndef SDL_RESIZABLE
#define SDL_RESIZABLE SDL_WINDOW_RESIZABLE
#endif
#ifndef SDL_NOFRAME
#define SDL_NOFRAME SDL_WINDOW_BORDERLESS
#endif

// SDL_KEYDOWN, SDL_KEYUP are the same in SDL2
// SDLK_* constants are the same in SDL2

// SDL_ACTIVEEVENT is removed in SDL2, use SDL_WINDOWEVENT instead
// SDL_APPACTIVE -> SDL_WINDOWEVENT_FOCUS_GAINED/LOST
// SDL_APPINPUTFOCUS -> SDL_WINDOWEVENT_FOCUS_GAINED/LOST