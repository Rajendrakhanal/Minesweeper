#include "difficultymenu.hpp"
#include "Texture.hpp"
#include "window.hpp"
#include "mediumgameplay.hpp"
#include "hardgameplay.hpp"
#include "easygameplay.hpp"

difficultymenu gdifficultymenu;

void difficultymenu::handleEvent(SDL_Event *e)
{
  // If mouse event happeneddependencies
  if (e->type == SDL_MOUSEBUTTONDOWN)
  {
    // Get mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);

    // To render easy gameplay
    if (x > 51 && x < 150 && y > 159 && y < 273)
    {
      bool quit = false;
      // Render easytablewithmines
      geasyloadscreen.easyCreateTableWithMine();
      // Event handler
      SDL_Event e;
      // While application is running
      while (!quit)
      {
        while (!quit && !easygameOver && !easyisWinning)
        {
          // Handle events on queue
          while (SDL_PollEvent(&e) != 0)
          {
            // User requests quit
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
            {
              quit = true;
            }
            for (int i = 0; i < EASY_ROW_SIZE; i++)
            {
              for (int j = 0; j < EASY_COLUMN_SIZE; j++)
              {
                geasygameplayButtons[i][j].handleEvent(&e);
              }
            }
            easyisWinning = geasyloadscreen.checkWinning();
            if (e.key.keysym.sym == SDLK_s)
            {
              geasyloadscreen.easyCreateTableWithMine();
              easy_countMineLeft = EASY_MINE_COUNT;
            }
          }
          // clear screen
          SDL_RenderClear(gRenderer);
          // Render background
          gBackgroundTexture.render(0, 0);
          // Render Text
          gPlayAgainLoseTexture.render(110, 415);
          geasyloadscreen.easymineManager();
          geasyloadscreen.flagmanager();
          // Render buttons
          for (int i = 0; i < EASY_ROW_SIZE; i++)
          {
            for (int j = 0; j < EASY_COLUMN_SIZE; j++)
            {
              geasygameplayButtons[i][j].render(i, j);
            }
          }
          // update screen
          SDL_RenderPresent(gRenderer);
        }
        easygameOver = false;
        easyisWinning = false;
        easy_countMineLeft = EASY_MINE_COUNT;
      }
    }

    // To Render medium gameplay
    if (x > 178 && x < 282 && y > 159 && y < 273)
    {
      // Main loop flag
      bool quit = false;
      // Render easytablewithmines
      gmediumloadscreen.mediumCreateTableWithMine();
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
          if (e.key.keysym.sym == SDLK_s)
          {
            gmediumloadscreen.mediumCreateTableWithMine();
          }
        }
        // clear screen
        SDL_RenderClear(gRenderer);
        // Render background
        gBackgroundTexture.render(0, 0);
        // Render Text
        gPlayAgainLoseTexture.render(100, 430);
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
      }
    }

    // To Render Hard gameplay
    if (x > 307 && x < 411 && y > 159 && y < 273)
    {
      {
        // Main loop flag
        bool quit = false;
        ghardloadscreen.hardCreateTableWithMine();
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
            for (int i = 0; i < HARD_ROW_SIZE; i++)
            {
              for (int j = 0; j < HARD_COLUMN_SIZE; j++)
              {
                ghardgameplayButtons[i][j].handleEvent(&e);
              }
            }
            // if (e.key.keysym.sym == SDLK_s)
            // {
            //   ghardloadscreen.hardCreateTableWithMine();
            //   Mix_HaltMusic();
            // }
          }

          // clear screen
          SDL_RenderClear(gRenderer);
          // Render background
          gBackgroundTexture.render(0, 0);
          // Render Text
          gPlayAgainLoseTexture.render(100, 432);
          // Render buttons
          for (int i = 0; i < HARD_ROW_SIZE; i++)
          {
            for (int j = 0; j < HARD_COLUMN_SIZE; j++)
            {
              ghardgameplayButtons[i][j].render(i, j);
            }
          }
          // update screen
          SDL_RenderPresent(gRenderer);
        }
      }
    }
  }
}
