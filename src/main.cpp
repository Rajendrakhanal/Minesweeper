#include "window.hpp"
#include "difficultymenu.hpp"
#include "mediumgameplay.hpp"
#include "hardgameplay.hpp"
#include "easygameplay.hpp"

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

bool loadMedia()
{
    // Loading success flag
    bool success = true;

    // Load PNG texture
    if (!gdifficultymenuTexture.loadFromFile("../bin/Image/menu.png"))
    {
        printf("Failed to load texture image!\n");
        success = false;
    }
    if (!gBackgroundTexture.loadFromFile("../bin/Image/Background.png"))
    {
        cout << "Failed to load background texture!\n";
        success = false;
    }
    // Open the font
    gGameOver = TTF_OpenFont("../bin/Font/DTM-Sans.ttf", 23);
    if (gGameOver == NULL)
    {
        cout << "Failed to load DTM-Sans font! SDL_ttf Error: " << TTF_GetError() << endl;
        success = false;
    }
    else
    {
        // Render text
        SDL_Color textColor = {140, 140, 140};
        if (!gTextTexture.loadFromRenderedText("GAME OVER :(", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }
    }

    gPlayAgainWin = TTF_OpenFont("../bin/Font/DTM-Sans.ttf", 40);
    if (gPlayAgainWin == NULL)
    {
        cout << "Failed to load DTM-Sans font! SDL_ttf Error: " << TTF_GetError() << endl;
        success = false;
    }
    else
    {
        // Render text
        SDL_Color playAgainWin = {30, 100, 100};
        if (!gPlayAgainWinTexture.loadFromRenderedText("Press s to play again!", playAgainWin))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }
    }

    gPlayAgainLose = TTF_OpenFont("../bin/Font/DTM-Sans.ttf", 40);
    if (gPlayAgainLose == NULL)
    {
        cout << "Failed to load DTM-Sans font! SDL_ttf Error: " << TTF_GetError() << endl;
        success = false;
    }
    else
    {
        // Render text
        SDL_Color playAgainLose = {140, 140, 140};
        if (!gPlayAgainLoseTexture.loadFromRenderedText("Press s to play again!", playAgainLose))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }
    }

    // Load scene
    if (!gWinningTexture.loadFromFile("../bin/Image/Winner.png"))
    {
        cout << "Failed to load winning texture!\n";
        success = false;
    }
    gmediumloadscreen.mediumloadmedia();
    ghardloadscreen.hardloadmedia();
    geasyloadscreen.easyloadmedia();

    return success;
}

void close()
{
    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *args[])
{
    // Start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        // Load media
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            // Main loop flag
            bool quit = false;

            // Event handler
            SDL_Event e;

            // While application is running
            while (!quit)
            {
                // Handle events on queue
                while (SDL_PollEvent(&e) != 0)
                {
                    // User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    gdifficultymenu.handleEvent(&e);
                }

                // clear screen
                SDL_RenderClear(gRenderer);
                // Render texture to screen
                gdifficultymenuTexture.render(0, 120);

                // update screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }

    // Free resources and close SDL
    close();

    return 0;
}