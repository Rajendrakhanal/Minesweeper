#pragma once
#include "Texture.hpp"
#include "window.hpp"

const int MEDIUM_BUTTON_SPRITE_TOTAL =12;
const int MEDIUM_ROW_SIZE = 14;
const int MEDIUM_COLUMN_SIZE = 14;
const int MEDIUM_TILE_SIZE = 29;
const int MEDIUM_MINE_COUNT = 14;

extern bool gameOver ;
extern bool isWinning;

const int MEDIUM_DISTANCE_BETWEEN = (SCREEN_WIDTH - MEDIUM_ROW_SIZE * MEDIUM_TILE_SIZE) / 2;

class Lmediumgameplay
{
public:
    // handles media , clips and sprites
    void mediumloadmedia();
    // Handles mouse event for mediumgameplay
    void handleEvent(SDL_Event *e);
    // Initializes internal variables
    Lmediumgameplay();

    // Sets top left position
    void setPosition(int x, int y);

    // Shows button sprite
    void render(int i, int j);

private:
    // Top left position
    SDL_Point mPosition;
};

extern SDL_Rect gmediumSpriteClips[MEDIUM_BUTTON_SPRITE_TOTAL];

extern Lmediumgameplay gmediumgameplayButtons[MEDIUM_ROW_SIZE][MEDIUM_COLUMN_SIZE];

extern Lmediumgameplay gmediumloadscreen;



