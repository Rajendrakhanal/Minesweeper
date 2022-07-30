#include "difficultymenu.hpp"
#include "Texture.hpp"
#include "window.hpp"
#include "mediumgameplay.hpp"

difficultymenu gdifficultymenu;

void difficultymenu::handleEvent(SDL_Event *e)
{
  if (e->type == SDL_MOUSEBUTTONDOWN)
  {
    // Get mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);

    // Check if mouse is in button
    bool inside = true;

    // To render easy gameplay
    if (x > 51 && x < 150 && y > 159 && y < 273)
    {
      cout << "EASY";
    }
    // To Render medium gameplay
    if (x > 178 && x < 282 && y > 159 && y < 273)
    {
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
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
            {
              quit = true;
            }
            for (int i = 0; i < MEDIUM_ROW_SIZE; i++)
            {
              for (int j = 0; j < MEDIUM_COLUMN_SIZE; j++)
              {
                gmediumgameplayButtons[i][j].handleEvent(&e);
              }
            }
          }

          // clear screen
          SDL_RenderClear(gRenderer);
          // Render background
          gBackgroundTexture.render(0, 0);
          // Render buttons
          for (int i = 0; i < MEDIUM_ROW_SIZE; i++)
          {
            for (int j = 0; j < MEDIUM_COLUMN_SIZE; j++)
            {
              gmediumgameplayButtons[i][j].render(i, j);
            }
          }
          // update screen
          SDL_RenderPresent(gRenderer);

          // Render backgroun
        }
      }
    }
    // To Render Hard gameplay
    if (x > 307 && x < 411 && y > 159 && y < 273)
    {
      cout << "HARD";
      gBackgroundTexture.render(0, 0);
    }
  }
}
