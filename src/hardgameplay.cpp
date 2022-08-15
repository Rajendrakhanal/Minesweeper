#include "hardgameplay.hpp"
#include "Texture.hpp"

// Gameplay variables
int hard_countMineLeft = HARD_MINE_COUNT;
int hard_countTileLeft = HARD_ROW_SIZE * HARD_COLUMN_SIZE;
// Board with mine
int hardboard[HARD_ROW_SIZE][HARD_COLUMN_SIZE];

// Board for showing
int shardBoard[HARD_ROW_SIZE][HARD_COLUMN_SIZE];

Lhardgameplay ghardgameplayButtons[HARD_ROW_SIZE][HARD_COLUMN_SIZE];
Lhardgameplay ghardloadscreen;

bool hardgameOver = false;
bool hardisWinning = false;

SDL_Rect ghardSpriteClips[HARD_BUTTON_SPRITE_TOTAL];

Lhardgameplay::Lhardgameplay()
{
    mPosition.x = 0;
    mPosition.y = 0;
}
void Lhardgameplay::setPosition(int x, int y)
{
    mPosition.x = x;
    mPosition.y = y;
}
void Lhardgameplay::hardloadmedia()
{
    bool success = true;
    // Load sprites
    if (!gButtonSpriteSheetTexture.loadFromFile("bin/Image/Tiles.png"))
    {
        cout << "Failed to load sprites texture!\n";
        success = false;
    }
    else
    {
        // Set sprites
        for (int i = 0; i < HARD_BUTTON_SPRITE_TOTAL; i++)
        {
            ghardSpriteClips[i].x = i * 32;
            ghardSpriteClips[i].y = 0;
            ghardSpriteClips[i].w = HARD_TILE_SIZE;
            ghardSpriteClips[i].h = HARD_TILE_SIZE;
        }
        // Set buttons position
        for (int i = 0; i < HARD_ROW_SIZE; i++)
        {
            for (int j = 0; j < HARD_COLUMN_SIZE; j++)
            {
                ghardgameplayButtons[i][j].setPosition(j * HARD_TILE_SIZE + HARD_DISTANCE_BETWEEN, i * HARD_TILE_SIZE + HARD_DISTANCE_BETWEEN);
            }
        }
    }
}

void Lhardgameplay::render(int i, int j)
{
    // Show current button sprite
    gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y, &ghardSpriteClips[shardBoard[i][j]]);
}

void hreveal(int i, int j)
{
    if (shardBoard[i][j] == 10 || shardBoard[i][j] == 11)
    {
        if (shardBoard[i][j] == 11)
        {
            hard_countMineLeft++;
        }
        shardBoard[i][j] = hardboard[i][j];
        hard_countTileLeft--;
        if (shardBoard[i][j] == 0)
        {
            if (i < HARD_ROW_SIZE - 1)
                hreveal(i + 1, j);
            if (i > 0)
                hreveal(i - 1, j);
            if (j < HARD_COLUMN_SIZE - 1)
                hreveal(i, j + 1);
            if (j > 0)
                hreveal(i, j - 1);
            if (i > 0 && j > 0)
                hreveal(i - 1, j - 1);
            if (i < HARD_ROW_SIZE - 1 && j < HARD_COLUMN_SIZE - 1)
                hreveal(i + 1, j + 1);
            if (i > 0 && j < HARD_COLUMN_SIZE - 1)
                hreveal(i - 1, j + 1);
            if (i < HARD_ROW_SIZE - 1 && j > 0)
                hreveal(i + 1, j - 1);
        }
    }
}

void Lhardgameplay::handleEvent(SDL_Event *e)
{
    // If mouse event happened
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        // Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        int i = (y - HARD_DISTANCE_BETWEEN) / HARD_TILE_SIZE;
        int j = (x - HARD_DISTANCE_BETWEEN) / HARD_TILE_SIZE;

        // Check if mouse is in button
        bool inside = true;

        // Mouse is left of the button
        if (x < mPosition.x)
        {
            inside = false;
        }
        // Mouse is right of the button
        else if (x > mPosition.x + HARD_TILE_SIZE)
        {
            inside = false;
        }
        // Mouse above the button
        else if (y < mPosition.y)
        {
            inside = false;
        }
        // Mouse below the button
        else if (y > mPosition.y + HARD_TILE_SIZE)
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
                    hreveal(i, j);
                    if (hardboard[i][j] == 9)
                    {
                        hardgameOver = true;
                    }
                    break;
                }
                case SDL_BUTTON_RIGHT:
                {
                    if (shardBoard[i][j] >= 10)
                    {
                        if (shardBoard[i][j] == 10)
                        {
                            if (hard_countMineLeft == 0)
                                break;
                            shardBoard[i][j] = 11;
                            hard_countMineLeft--;
                        }
                        else
                        {
                            shardBoard[i][j] = 10;
                            hard_countMineLeft++;
                        }
                    }
                    break;
                }
                }
            }
        }
    }
}

void Lhardgameplay::hardCreateTableWithMine()
{
     srand(time(NULL));
    int mine = 0;
    for (int i = 0; i < HARD_ROW_SIZE; i++)
    {
        for (int j = 0; j < HARD_COLUMN_SIZE; j++)
        {
            shardBoard[i][j] = 10;
            hardboard[i][j] = 0;
        }
    }
    while (mine < HARD_MINE_COUNT)
    {
        int i = rand() % HARD_ROW_SIZE;
        int j = rand() % HARD_COLUMN_SIZE;
        if (hardboard[i][j] == 9)
        {
            continue;
        }
        else
        {
            hardboard[i][j] = 9;
            mine++;
            if (hardboard[i - 1][j] != 9 && i > 0)
                hardboard[i - 1][j]++;
            if (hardboard[i][j - 1] != 9 && j > 0)
                hardboard[i][j - 1]++;
            if (hardboard[i + 1][j] != 9 && i < HARD_ROW_SIZE - 1)
                hardboard[i + 1][j]++;
            if (hardboard[i][j + 1] != 9 && j < HARD_COLUMN_SIZE - 1)
                hardboard[i][j + 1]++;
            if (hardboard[i - 1][j - 1] != 9 && i > 0 && j > 0)
                hardboard[i - 1][j - 1]++;
            if (hardboard[i - 1][j + 1] != 9 && i > 0 && j < HARD_COLUMN_SIZE - 1)
                hardboard[i - 1][j + 1]++;
            if (hardboard[i + 1][j - 1] != 9 && j > 0 && i < HARD_ROW_SIZE - 1)
                hardboard[i + 1][j - 1]++;
            if (hardboard[i + 1][j + 1] != 9 && i < HARD_ROW_SIZE - 1 && j < HARD_COLUMN_SIZE - 1)
                hardboard[i + 1][j + 1]++;
        }
    }
}