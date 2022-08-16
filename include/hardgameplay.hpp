#pragma once
#include "window.hpp"

const int HARD_BUTTON_SPRITE_TOTAL = 12;
const int HARD_ROW_SIZE = 16;
const int HARD_COLUMN_SIZE = 16;
const int HARD_TILE_SIZE = 26;
const int HARD_MINE_COUNT = 20;
const int HARD_DISTANCE_BETWEEN = (SCREEN_WIDTH - HARD_ROW_SIZE * HARD_TILE_SIZE) / 2;

// Gameplay variables
extern int hard_countMineLeft;
extern int hard_countTileLeft;

// In memory text stream
extern stringstream hardmineLeft;

extern bool hardgameOver;
extern bool hardisWinning;

class Lhardgameplay
{
public:
    // handles media , clips and sprites
    void hardloadmedia();
    // Handles mouse event for hardgameplay
    void handleEvent(SDL_Event *e);
    // Initializes internal variables
    Lhardgameplay();

    // Sets top left position
    void setPosition(int x, int y);

    // Shows button sprite
    void render(int i, int j);

    void hardCreateTableWithMine();

    // quitegame
    void flagmanager();

    bool checkWinning();

    void hardmineManager();

private:
    // Top left position
    SDL_Point mPosition;
};

extern SDL_Rect ghardSpriteClips[HARD_BUTTON_SPRITE_TOTAL];

extern Lhardgameplay ghardgameplayButtons[HARD_ROW_SIZE][HARD_COLUMN_SIZE];

extern Lhardgameplay ghardloadscreen;