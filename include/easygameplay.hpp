#pragma once
#include "Texture.hpp"
#include "window.hpp"

const int EASY_BUTTON_SPRITE_TOTAL =12;
const int EASY_ROW_SIZE = 11;
const int EASY_COLUMN_SIZE = 11;
const int EASY_TILE_SIZE = 32;
const int EASY_MINE_COUNT = 11;

// Gameplay variables
extern int easy_countMineLeft ;
extern int easy_countTileLeft ;

extern bool easygameOver ;
extern bool easyisWinning;

const int EASY_DISTANCE_BETWEEN = (SCREEN_WIDTH - EASY_ROW_SIZE * EASY_TILE_SIZE) / 2;

class Leasygameplay
{
public:
    // handles media , clips and sprites
    void easyloadmedia();
    // Handles mouse event for easygameplay
    void handleEvent(SDL_Event *e);
    // Initializes internal variables
    Leasygameplay();

    // Sets top left position
    void setPosition(int x, int y);

    void easyCreateTableWithMine();

    // Shows button sprite
    void render(int i, int j);

private:
    // Top left position
    SDL_Point mPosition;
};

extern SDL_Rect geasySpriteClips[EASY_BUTTON_SPRITE_TOTAL];

extern Leasygameplay geasygameplayButtons[EASY_ROW_SIZE][EASY_COLUMN_SIZE];

extern Leasygameplay geasyloadscreen;