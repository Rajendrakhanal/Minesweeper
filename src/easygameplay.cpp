#include "easygameplay.hpp"
#include "Texture.hpp"
#include "window.hpp"

// Gameplay variables
int easy_countMineLeft = EASY_MINE_COUNT;
int easy_countTileLeft = EASY_ROW_SIZE * EASY_COLUMN_SIZE;
// Board with mine
int easyboard[EASY_ROW_SIZE][EASY_COLUMN_SIZE];

// Board for showing
int seasyBoard[EASY_ROW_SIZE][EASY_COLUMN_SIZE];

Leasygameplay geasygameplayButtons[EASY_ROW_SIZE][EASY_COLUMN_SIZE];
Leasygameplay geasyloadscreen;

Mix_Chunk *eclick = NULL;

bool easygameOver=false ;
bool easyisWinning=false;

SDL_Rect geasySpriteClips[EASY_BUTTON_SPRITE_TOTAL];

Leasygameplay::Leasygameplay()
{
    mPosition.x = 0;
    mPosition.y = 0;
}
void Leasygameplay::setPosition(int x, int y)
{
    mPosition.x = x;
    mPosition.y = y;
}
void Leasygameplay::easyloadmedia()
{
    bool success = true;
    // Load sprites
    if (!gButtonSpriteSheetTexture.loadFromFile("../bin/Image/Tiles.png"))
    {
        cout << "Failed to load sprites texture!\n";
        success = false;
    }
    if (!gBackgroundTexture.loadFromFile("../bin/Image/Background.png"))
    {
        cout << "Failed to load background texture!\n";
        success = false;
    }
    else
    {
        // Set sprites
        for (int i = 0; i < EASY_BUTTON_SPRITE_TOTAL; i++)
        {
            geasySpriteClips[i].x = i * 32;
            geasySpriteClips[i].y = 0;
            geasySpriteClips[i].w = EASY_TILE_SIZE;
            geasySpriteClips[i].h = EASY_TILE_SIZE;
        }
        // Set buttons position
        for (int i = 0; i < EASY_ROW_SIZE; i++)
        {
            for (int j = 0; j < EASY_COLUMN_SIZE; j++)
            {
                geasygameplayButtons[i][j].setPosition(j * EASY_TILE_SIZE + EASY_DISTANCE_BETWEEN, i * EASY_TILE_SIZE + EASY_DISTANCE_BETWEEN);
            }
        }
    }
}

void Leasygameplay::render(int i, int j)
{
    // Show current button sprite
    gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y, &geasySpriteClips[seasyBoard[i][j]]);
}

void ereveal(int i, int j)
{
    if (seasyBoard[i][j] == 10 || seasyBoard[i][j] == 11)
    {
        if (seasyBoard[i][j] == 11)
        {
            easy_countMineLeft++;
        }
        seasyBoard[i][j] = easyboard[i][j];
        easy_countTileLeft--;
        if (seasyBoard[i][j] == 0)
        {
            if (i < EASY_ROW_SIZE - 1)
                ereveal(i + 1, j);
            if (i > 0)
                ereveal(i - 1, j);
            if (j < EASY_COLUMN_SIZE - 1)
                ereveal(i, j + 1);
            if (j > 0)
                ereveal(i, j - 1);
            if (i > 0 && j > 0)
                ereveal(i - 1, j - 1);
            if (i < EASY_ROW_SIZE - 1 && j < EASY_COLUMN_SIZE - 1)
                ereveal(i + 1, j + 1);
            if (i > 0 && j < EASY_COLUMN_SIZE - 1)
                ereveal(i - 1, j + 1);
            if (i < EASY_ROW_SIZE - 1 && j > 0)
                ereveal(i + 1, j - 1);
        }
    }
}

void Leasygameplay::handleEvent(SDL_Event *e)
{
    // If mouse event happened
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        // Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        int i = (y - EASY_DISTANCE_BETWEEN) / EASY_TILE_SIZE;
        int j = (x - EASY_DISTANCE_BETWEEN) / EASY_TILE_SIZE;

        // Check if mouse is in button
        bool inside = true;

        // Mouse is left of the button
        if (x < mPosition.x)
        {
            inside = false;
        }
        // Mouse is right of the button
        else if (x > mPosition.x + EASY_TILE_SIZE)
        {
            inside = false;
        }
        // Mouse above the button
        else if (y < mPosition.y)
        {
            inside = false;
        }
        // Mouse below the button
        else if (y > mPosition.y + EASY_TILE_SIZE)
        {
            inside = false;
        }

        // Mouse is inside button
        if (inside)
        {
            if (e->type == SDL_MOUSEBUTTONDOWN)
            {
                // Play the sound effect
                Mix_PlayChannel(-1, eclick, 0);

                // Set mouse clicked
                switch (e->button.button)
                {
                case SDL_BUTTON_LEFT:
                {
                    ereveal(i, j);
                    if (easyboard[i][j] == 9)
                    {
                        easygameOver = true;
                    }
                    break;
                }
                case SDL_BUTTON_RIGHT:
                {
                    if (seasyBoard[i][j] >= 10)
                    {
                        if (seasyBoard[i][j] == 10)
                        {
                            if (easy_countMineLeft == 0)
                                break;
                            seasyBoard[i][j] = 11;
                            easy_countMineLeft--;
                        }
                        else
                        {
                            seasyBoard[i][j] = 10;
                            easy_countMineLeft++;
                        }
                    }
                    break;
                }
                }
            }
        }
    }
}