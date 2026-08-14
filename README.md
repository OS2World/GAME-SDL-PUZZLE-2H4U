# 2H4U — Too Hard For You

2H4U is an open source game that mixes a Tetris-like block-dropping mechanic with a wall-breaker. It demands good reflexes, coordination, and a degree of ambidexterity. Will it be too hard for you?

- **Upstream project**: https://sourceforge.net/p/toohardforyou/
- **License**: GNU General Public License v2 or later (see `COPYING.txt`)

---

## Authors

This game was created by team **I4GOT MY BRAIN** between March and May 2006, as part of a second-year engineering project at INSA Rouen (France).

- Pierre Lagouge — developer
- Pierre-Yves Ricau — lead developer, designer, and maintainer

Special thanks to **Kayl** for help with project organization, and to **nxdev** for the English translation of the in-game help pages. The help pages were created using [GeneeWeb](http://www.geneeweb.com).

The `Engine.h` / `Engine.cpp` framework was adapted from a tutorial at:
http://gpwiki.org/index.php/SDL:Tutorials:Simple_Engine_Framework
(written by Anders "Sion" Nissen, available under GNU FDL 1.2)

---

## OS/2 / ArcaOS port — version 1.3 release 2

**Tested on**: OS/2 Warp 4.5, eCS, ArcaOS

**Requirements**:
- GCC core 9.2 (ANPM package `gcc`)
- GCC runtime (ANPM package `gcc-runtime`)
- SDL2, SDL2_image, SDL2_ttf, SDL2_mixer (ANPM or RPM packages)

**Port Authors**:
- Gianfilippo Cimmino - First release.
- Martin Iturbide - SDL2 port.

### Changes in release 2

- **SDL1 → SDL2 migration**: ported the entire engine from SDL 1.2 to SDL2.
- **No console window**: executable is linked as a PM application; the VIO (command-line) window no longer appears on launch.
- **Music format**: background music is loaded from `data/sons/musique.ogg` (OGG Vorbis) with automatic fallback to `musique.mp3`. The SDL2_mixer build for ArcaOS does not include MP3 decoding, so the OGG file must be present for music to play.
- **Music init**: `Mix_Init` is called with the appropriate codec flags before `Mix_OpenAudio`; a missing music file is non-fatal — the game continues without music and logs a warning.
- **Alt+Enter fullscreen**: toggle between windowed and fullscreen at any time without restarting.
- **Working directory**: the executable resolves data paths relative to its own location, so it can be launched from any directory or by double-clicking.
- **Compile warnings fixed**: sign-compare and unused-variable warnings in `jeu.cpp` and `terrain.cpp`.

---

## Building on ArcaOS

```
make -f makefile.os2
```

This produces `2h4u.exe` in the project root.

To disable sound (if audio causes issues), uncomment `//#define NO_SOUND_2H4U` in `sources/sdl_includes.h` before building.

---

## Running

Place `2h4u.exe` in the same directory as the `data/` folder and launch it from there, or simply double-click. The executable changes to its own directory at startup so relative data paths resolve correctly.

---

## Controls

| Key | Action |
|-----|--------|
| Arrow keys | Move / rotate block |
| Space | Drop block |
| Alt+Enter | Toggle fullscreen |
| Escape | Pause / menu |

---

## SDL1 → SDL2 migration notes

The original source used SDL 1.2. The OS/2 port updates the engine to SDL2:

- Window and renderer created with `SDL_CreateWindow` / `SDL_CreateRenderer`.
- A virtual back-buffer surface (`SDL_Surface`) is kept at the game's native 800×600; all game modules blit to it unchanged, requiring no changes to game logic.
- Each frame the surface is uploaded as a texture and presented via `SDL_RenderCopy`.
- `SDL_DisplayFormat` / `SDL_DisplayFormatAlpha` replaced with `SDL_ConvertSurfaceFormat`.
- `SDL_SetAlpha` replaced with `SDL_SetSurfaceAlphaMod`.
- Alt+Enter fullscreen toggle uses `SDL_SetWindowFullscreen(SDL_WINDOW_FULLSCREEN_DESKTOP)` with `SDL_RenderSetLogicalSize` to preserve the 800×600 aspect ratio on any screen.
