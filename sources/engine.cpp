/*
The CEngine Framework was found on :

http://gpwiki.org/index.php/SDL:Tutorials:Simple_Engine_Framework

It was written by Anders "Sion" Nissen and last updated 14. August 2005.

Content of this file is available under GNU Free Documentation License 1.2. :
http://www.gnu.org/copyleft/fdl.html

We modified the file to make it feet our requirements.
*/

#include "Engine.h"

/** Default constructor. **/
CEngine::CEngine()
{

	m_lLastRender   = 0;
	m_lLastThink    = 0;
	//m_iFrameLenght  = 15; //Dur�e en millisecondes d'une frame.
    m_iFrameLenght=0;
	m_iWidth		= 800;
	m_iHeight		= 600;
	m_czTitle		= NULL;

	m_pWindow		= NULL;
	m_pRenderer		= NULL;
	m_pScreen		= NULL;

	m_bMinimized		= false;
	m_bFullscreen       = false;
}

/** Destructor. **/
CEngine::~CEngine()
{
	if (m_pScreen) SDL_FreeSurface(m_pScreen);
	if (m_pRenderer) SDL_DestroyRenderer(m_pRenderer);
	if (m_pWindow) SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

/** Sets the height and width of the window.
	@param iWidth The width of the window
	@param iHeight The height of the window
**/
void CEngine::SetSize(const int& iWidth, const int& iHeight)
{
	m_iWidth  = iWidth;
	m_iHeight = iHeight;

	if (m_pScreen) { SDL_FreeSurface(m_pScreen); m_pScreen = NULL; }
	if (m_pRenderer) SDL_DestroyRenderer(m_pRenderer);
	if (m_pWindow) SDL_DestroyWindow(m_pWindow);

	m_pWindow = SDL_CreateWindow(m_czTitle ? m_czTitle : "2H4U",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		iWidth, iHeight,
		SDL_WINDOW_SHOWN);

	if (m_pWindow)
	{
		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (!m_pRenderer)
		{
			// Fallback to software renderer
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_SOFTWARE);
		}
	}
	m_pScreen = SDL_CreateRGBSurface(0, iWidth, iHeight, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	if (m_pRenderer)
		SDL_RenderSetLogicalSize(m_pRenderer, iWidth, iHeight);
}

//M�me chose que pr�c�demment, mais en plein �cran.
void CEngine::SetFullScreen(const int& iWidth, const int& iHeight)
{
    m_iWidth  = iWidth;
	m_iHeight = iHeight;

	if (m_pScreen) { SDL_FreeSurface(m_pScreen); m_pScreen = NULL; }
	if (m_pRenderer) SDL_DestroyRenderer(m_pRenderer);
	if (m_pWindow) SDL_DestroyWindow(m_pWindow);

	m_pWindow = SDL_CreateWindow(m_czTitle ? m_czTitle : "2H4U",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		iWidth, iHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);

	if (m_pWindow)
	{
		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (!m_pRenderer)
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_SOFTWARE);
		}
	}
	m_pScreen = SDL_CreateRGBSurface(0, iWidth, iHeight, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	if (m_pRenderer)
		SDL_RenderSetLogicalSize(m_pRenderer, iWidth, iHeight);
}

void CEngine::flipFullScreen(bool fullscreen)
{
    if (m_pScreen) { SDL_FreeSurface(m_pScreen); m_pScreen = NULL; }
    if (fullscreen==true)
    {
        SDL_ShowCursor(false);
		if (m_pRenderer) SDL_DestroyRenderer(m_pRenderer);
		if (m_pWindow) SDL_DestroyWindow(m_pWindow);

		m_pWindow = SDL_CreateWindow(m_czTitle ? m_czTitle : "2H4U",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			m_iWidth, m_iHeight,
			SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);

		if (m_pWindow)
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (!m_pRenderer)
			{
				m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_SOFTWARE);
			}
		}
    }
    else
    {
        SDL_ShowCursor(true);
		if (m_pRenderer) SDL_DestroyRenderer(m_pRenderer);
		if (m_pWindow) SDL_DestroyWindow(m_pWindow);

		m_pWindow = SDL_CreateWindow(m_czTitle ? m_czTitle : "2H4U",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			m_iWidth, m_iHeight,
			SDL_WINDOW_SHOWN);

		if (m_pWindow)
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (!m_pRenderer)
			{
				m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_SOFTWARE);
			}
		}
    }
    m_pScreen = SDL_CreateRGBSurface(0, m_iWidth, m_iHeight, 32,
        0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
}

/** Initialize SDL, the window and the additional data. **/
void CEngine::Init()
{
    //+ �ventuellement d'autres.
	#ifdef NO_SOUND_2H4U
		if ( SDL_Init( SDL_INIT_VIDEO |  SDL_INIT_TIMER ) < 0 )
	#else
	if ( SDL_Init( SDL_INIT_VIDEO |  SDL_INIT_TIMER  | SDL_INIT_AUDIO ) < 0 )
	#endif
	{
		fprintf( stderr, "Impossible d'initialiser SDL: %s\n", SDL_GetError() );
		exit( 1 );
	}

    //Ligne rajout�, au cas ou le programme est quitt� violement (kill).
    atexit(SDL_Quit);

    //Chargement des param�tres, afin de choisir si fen�tre ou plein �cran
    ParamInit(m_iWidth,m_iHeight);

	// If we fail, return error.
	if ( m_pRenderer == NULL || m_pWindow == NULL )
	{
		fprintf( stderr, "Impossible de cr�er la fen�tre/renderer: %s\n", SDL_GetError() );
		exit( 1 );
	}

	// Initialize SDL_image
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		fprintf(stderr, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}

	// Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		fprintf(stderr, "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

	AdditionalInit();
}

//Le jeu sera en fait appell� par le menu.
//Pour revenir au menu, on fera un return.
/** The main loop. **/
void CEngine::Start()
{
	m_lLastRender = SDL_GetTicks();
	m_lLastThink = SDL_GetTicks();
	m_bQuit = false;

	// Main loop: loop forever.
	while ( !m_bQuit )
	{
		// Handle mouse and keyboard input
		HandleInput();

		if ( m_bMinimized ) {
			// Release some system resources if the app. is minimized.
		    SDL_Delay(100);
		} else {
			// Do some thinking
			DoThink();

			// Render stuff
			DoRender();

		}
        //On se passe du Delay, car l'affichage est limit� (60 images par secondes)
	}

	AdditionalEnd();
	End(); //Lorsque l'on quitte le programme.

}

void CEngine::Quit()
{
    m_bQuit = true;
}

void CEngine::End()
{
	if (m_pScreen) { SDL_FreeSurface(m_pScreen); m_pScreen = NULL; }
	if (m_pRenderer) SDL_DestroyRenderer(m_pRenderer);
	if (m_pWindow) SDL_DestroyWindow(m_pWindow);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	exit(0);
}

/** Handles all controller inputs.
	@remark This function is called once per frame.
**/
void CEngine::HandleInput()
{
	// Poll for events, and handle the ones we care about.
	SDL_Event event;
	while ( SDL_PollEvent( &event ) )
	{
		switch ( event.type )
		{
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_RETURN &&
				(event.key.keysym.mod & KMOD_ALT))
			{
				toggleFullScreen();
			}
			else
			{
				KeyDown( event.key.keysym.sym );
			}
			break;

		case SDL_KEYUP:
			KeyUp( event.key.keysym.sym );
			break;

        //Rajouter la gestion de 4 ou 5 touches suppl�mentaires.

		case SDL_QUIT:
			m_bQuit = true;
			break;

        //Si on minimize la fen�tre, le jeu passera en pause.
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST ||
				event.window.event == SDL_WINDOWEVENT_MINIMIZED)
			{
				m_bMinimized = true;
				WindowInactive();
			}
			else if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED ||
					 event.window.event == SDL_WINDOWEVENT_RESTORED)
			{
				m_bMinimized = false;
				WindowActive();
			}
			break;
		} // switch
	} // while (handling input)
}

/** Handles the updating routine. **/
void CEngine::DoThink()
{
    long iElapsedThink = SDL_GetTicks() - m_lLastThink;
	m_lLastThink = SDL_GetTicks();

	Think( iElapsedThink );

}


/** Handles the rendering and FPS calculations. **/
void CEngine::DoRender()
{
    long iElapsedRender = SDL_GetTicks() - m_lLastRender;

    if (iElapsedRender >= m_iFrameLenght)
    {
        m_lLastRender = SDL_GetTicks();

        if (m_pScreen && m_pRenderer)
        {
            SDL_FillRect(m_pScreen, NULL, 0);
            Render(m_pScreen);

            SDL_Texture* tex = SDL_CreateTextureFromSurface(m_pRenderer, m_pScreen);
            if (tex)
            {
                SDL_RenderClear(m_pRenderer);
                SDL_RenderCopy(m_pRenderer, tex, NULL, NULL);
                SDL_DestroyTexture(tex);
            }
            SDL_RenderPresent(m_pRenderer);
        }
    }
}

/** Sets the title of the window
	@param czTitle A character array that contains the text that the window title should be set to.
**/

void CEngine::SetTitle(const char* czTitle)
{
	m_czTitle = czTitle;
	if (m_pWindow)
		SDL_SetWindowTitle(m_pWindow, czTitle);
}

/** Retrieve the title of the application window.
	@return The last set windows title as a character array.
	@remark Only the last set title is returned. If another application has changed the window title, then that title won't be returned.
**/
const char* CEngine::GetTitle()
{
	return m_czTitle;
}

//N�cessite SDL_Image. Recoit le chemin d'acc�s de l'icone en param�tre.
void CEngine::SetIcon(const char* czChemin)
{
	if (m_pWindow)
	{
		SDL_Surface* icon = IMG_Load(czChemin);
		if (icon)
		{
			SDL_SetWindowIcon(m_pWindow, icon);
			SDL_FreeSurface(icon);
		}
	}
}

/** Retrieve the main screen surface.
	@return A pointer to the SDL_Surface surface
	@remark The surface is not validated internally.
**/
void CEngine::toggleFullScreen()
{
	m_bFullscreen = !m_bFullscreen;
	if (m_bFullscreen)
	{
		SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
		SDL_ShowCursor(SDL_DISABLE);
	}
	else
	{
		SDL_SetWindowFullscreen(m_pWindow, 0);
		SDL_ShowCursor(SDL_ENABLE);
	}
	SDL_RenderSetLogicalSize(m_pRenderer, m_iWidth, m_iHeight);
}

SDL_Surface* CEngine::GetSurface()
{
	return m_pScreen;
}

