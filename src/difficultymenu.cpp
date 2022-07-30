#include "difficultymenu.hpp"
#include "Texture.hpp"
#include "window.hpp"

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
      
    }
    // To Render medium gameplay
    if (x > 178 && x < 282 && y > 159 && y < 273)
    {
      
    }
    // To Render Hard gameplay
    if (x > 307 && x < 411 && y > 159 && y < 273)
    {
      
    }
  }
}
