#pragma once
#include "Texture.hpp"

class difficultymenu
{
public:
    //Enters easy  gameplay
    bool easy();
    //Enters medium gameplay
    bool medium();
     //Enters hard gameplay
    bool hard();
    //Handles mouse event
    void handleEvent(SDL_Event *e);
};

extern difficultymenu gdifficultymenu;
