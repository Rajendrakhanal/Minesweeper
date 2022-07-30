#include "window.hpp"
#include "difficultymenu.hpp"
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