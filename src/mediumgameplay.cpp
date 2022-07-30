#include "mediumgameplay.hpp"
#include "Texture.hpp"
#include "window.hpp"

// Gameplay variables
int medium_countMineLeft = MEDIUM_MINE_COUNT;
int medium_countTileLeft = MEDIUM_ROW_SIZE * MEDIUM_COLUMN_SIZE;
bool gameOver = false;
bool isWinning = false;
// Board with mine
int board[MEDIUM_ROW_SIZE][MEDIUM_COLUMN_SIZE];

// Board for showing
int sBoard[MEDIUM_ROW_SIZE][MEDIUM_COLUMN_SIZE];

Lmediumgameplay gmediumgameplayButtons[MEDIUM_ROW_SIZE][MEDIUM_COLUMN_SIZE];
Lmediumgameplay gmediumloadscreen;

Mix_Chunk *click = NULL;

SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];

Lmediumgameplay::Lmediumgameplay()
{
    mPosition.x = 0;
    mPosition.y = 0;
}
void Lmediumgameplay::setPosition(int x, int y)
{
    mPosition.x = x;
    mPosition.y = y;
}
void Lmediumgameplay::mediumloadmedia()
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
        for (int i = 0; i < BUTTON_SPRITE_TOTAL; i++)
        {
            gSpriteClips[i].x = i * 32;
            gSpriteClips[i].y = 0;
            gSpriteClips[i].w = MEDIUM_TILE_SIZE;
            gSpriteClips[i].h = MEDIUM_TILE_SIZE;
        }
        // Set buttons position
        for (int i = 0; i < MEDIUM_ROW_SIZE; i++)
        {
            for (int j = 0; j < MEDIUM_COLUMN_SIZE; j++)
            {
                gmediumgameplayButtons[i][j].setPosition(j * MEDIUM_TILE_SIZE + MEDIUM_DISTANCE_BETWEEN, i * MEDIUM_TILE_SIZE + MEDIUM_DISTANCE_BETWEEN);
            }
        }
    }
}

void Lmediumgameplay::render(int i, int j)
{
    // Show current button sprite
    gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y, &gSpriteClips[sBoard[i][j]]);
}

void reveal(int i, int j)
{
    if (sBoard[i][j] == 10 || sBoard[i][j] == 11)
    {
        if (sBoard[i][j] == 11)
        {
            medium_countMineLeft++;
        }
        sBoard[i][j] = board[i][j];
        medium_countTileLeft--;
        if (sBoard[i][j] == 0)
        {
            if (i < MEDIUM_ROW_SIZE - 1)
                reveal(i + 1, j);
            if (i > 0)
                reveal(i - 1, j);
            if (j < MEDIUM_COLUMN_SIZE - 1)
                reveal(i, j + 1);
            if (j > 0)
                reveal(i, j - 1);
            if (i > 0 && j > 0)
                reveal(i - 1, j - 1);
            if (i < MEDIUM_ROW_SIZE - 1 && j < MEDIUM_COLUMN_SIZE - 1)
                reveal(i + 1, j + 1);
            if (i > 0 && j < MEDIUM_COLUMN_SIZE - 1)
                reveal(i - 1, j + 1);
            if (i < MEDIUM_ROW_SIZE - 1 && j > 0)
                reveal(i + 1, j - 1);
        }
    }
}

void Lmediumgameplay::handleEvent(SDL_Event *e)
{
    // If mouse event happened
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        // Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        int i = (y - MEDIUM_DISTANCE_BETWEEN) / MEDIUM_TILE_SIZE;
        int j = (x - MEDIUM_DISTANCE_BETWEEN) / MEDIUM_TILE_SIZE;

        // Check if mouse is in button
        bool inside = true;

        // Mouse is left of the button
        if (x < mPosition.x)
        {
            inside = false;
        }
        // Mouse is right of the button
        else if (x > mPosition.x + MEDIUM_TILE_SIZE)
        {
            inside = false;
        }
        // Mouse above the button
        else if (y < mPosition.y)
        {
            inside = false;
        }
        // Mouse below the button
        else if (y > mPosition.y + MEDIUM_TILE_SIZE)
        {
            inside = false;
        }

        // Mouse is inside button
        if (inside)
        {
            if (e->type == SDL_MOUSEBUTTONDOWN)
            {
                // Play the sound effect
                Mix_PlayChannel(-1, click, 0);

                // Set mouse clicked
                switch (e->button.button)
                {
                case SDL_BUTTON_LEFT:
                {
                    reveal(i, j);
                    if (board[i][j] == 9)
                    {
                        gameOver = true;
                    }
                    break;
                }
                case SDL_BUTTON_RIGHT:
                {
                    if (sBoard[i][j] >= 10)
                    {
                        if (sBoard[i][j] == 10)
                        {
                            if (medium_countMineLeft == 0)
                                break;
                            sBoard[i][j] = 11;
                            medium_countMineLeft--;
                        }
                        else
                        {
                            sBoard[i][j] = 10;
                            medium_countMineLeft++;
                        }
                    }
                    break;
                }
                }
            }
        }
    }
}