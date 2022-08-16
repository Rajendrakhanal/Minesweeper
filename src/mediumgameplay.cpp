#include "mediumgameplay.hpp"
#include "Texture.hpp"
#include "window.hpp"

// Gameplay variables
int medium_countMineLeft = MEDIUM_MINE_COUNT;
int medium_countTileLeft = MEDIUM_ROW_SIZE * MEDIUM_COLUMN_SIZE;

// Board with mine
int mediumboard[MEDIUM_ROW_SIZE][MEDIUM_COLUMN_SIZE];

// Board for showing
int smediumBoard[MEDIUM_ROW_SIZE][MEDIUM_COLUMN_SIZE];

Lmediumgameplay gmediumgameplayButtons[MEDIUM_ROW_SIZE][MEDIUM_COLUMN_SIZE];
Lmediumgameplay gmediumloadscreen;

bool mediumgameOver = false;
bool mediumisWinning = false;

SDL_Rect gmediumSpriteClips[MEDIUM_BUTTON_SPRITE_TOTAL];

// In memory text stream
stringstream mediummineLeft;

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
    bool success = true; // Load sprites
    if (!gButtonSpriteSheetTexture.loadFromFile("resources/Image/Tiles.png"))
    {
        cout << "Failed to load sprites texture!\n";
        success = false;
    }
    else
    {
        // Set sprites
        for (int i = 0; i < MEDIUM_BUTTON_SPRITE_TOTAL; i++)
        {
            gmediumSpriteClips[i].x = i * 32;
            gmediumSpriteClips[i].y = 0;
            gmediumSpriteClips[i].w = MEDIUM_TILE_SIZE;
            gmediumSpriteClips[i].h = MEDIUM_TILE_SIZE;
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
    gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y, &gmediumSpriteClips[smediumBoard[i][j]]);
}

void mreveal(int i, int j)
{
    if (smediumBoard[i][j] == 10 || smediumBoard[i][j] == 11)
    {
        if (smediumBoard[i][j] == 11)
        {
            medium_countMineLeft++;
        }
        smediumBoard[i][j] = mediumboard[i][j];
        medium_countTileLeft--;
        if (smediumBoard[i][j] == 0)
        {
            if (i < MEDIUM_ROW_SIZE - 1)
                mreveal(i + 1, j);
            if (i > 0)
                mreveal(i - 1, j);
            if (j < MEDIUM_COLUMN_SIZE - 1)
                mreveal(i, j + 1);
            if (j > 0)
                mreveal(i, j - 1);
            if (i > 0 && j > 0)
                mreveal(i - 1, j - 1);
            if (i < MEDIUM_ROW_SIZE - 1 && j < MEDIUM_COLUMN_SIZE - 1)
                mreveal(i + 1, j + 1);
            if (i > 0 && j < MEDIUM_COLUMN_SIZE - 1)
                mreveal(i - 1, j + 1);
            if (i < MEDIUM_ROW_SIZE - 1 && j > 0)
                mreveal(i + 1, j - 1);
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
                    mreveal(i, j);
                    if (mediumboard[i][j] == 9)
                    {
                        mediumgameOver = true;
                    }
                    break;
                }
                case SDL_BUTTON_RIGHT:
                {
                    if (smediumBoard[i][j] >= 10)
                    {
                        if (smediumBoard[i][j] == 10)
                        {
                            if (medium_countMineLeft == 0)
                                break;
                            smediumBoard[i][j] = 11;
                            medium_countMineLeft--;
                        }
                        else
                        {
                            smediumBoard[i][j] = 10;
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

void Lmediumgameplay::mediumCreateTableWithMine()
{
    srand(time(NULL));
    int mine = 0;
    for (int i = 0; i < MEDIUM_ROW_SIZE; i++)
    {
        for (int j = 0; j < MEDIUM_COLUMN_SIZE; j++)
        {
            smediumBoard[i][j] = 10;
            mediumboard[i][j] = 0;
        }
    }
    while (mine < MEDIUM_MINE_COUNT)
    {
        int i = rand() % MEDIUM_ROW_SIZE;
        int j = rand() % MEDIUM_COLUMN_SIZE;
        if (mediumboard[i][j] == 9)
        {
            continue;
        }
        else
        {
            mediumboard[i][j] = 9;
            mine++;
            if (mediumboard[i - 1][j] != 9 && i > 0)
                mediumboard[i - 1][j]++;
            if (mediumboard[i][j - 1] != 9 && j > 0)
                mediumboard[i][j - 1]++;
            if (mediumboard[i + 1][j] != 9 && i < MEDIUM_ROW_SIZE - 1)
                mediumboard[i + 1][j]++;
            if (mediumboard[i][j + 1] != 9 && j < MEDIUM_COLUMN_SIZE - 1)
                mediumboard[i][j + 1]++;
            if (mediumboard[i - 1][j - 1] != 9 && i > 0 && j > 0)
                mediumboard[i - 1][j - 1]++;
            if (mediumboard[i - 1][j + 1] != 9 && i > 0 && j < MEDIUM_COLUMN_SIZE - 1)
                mediumboard[i - 1][j + 1]++;
            if (mediumboard[i + 1][j - 1] != 9 && j > 0 && i < MEDIUM_ROW_SIZE - 1)
                mediumboard[i + 1][j - 1]++;
            if (mediumboard[i + 1][j + 1] != 9 && i < MEDIUM_ROW_SIZE - 1 && j < MEDIUM_COLUMN_SIZE - 1)
                mediumboard[i + 1][j + 1]++;
        }
    }
}

void Lmediumgameplay::flagmanager()
{
    // Check if win
    if (mediumisWinning && !mediumgameOver)
    {
        // Update screen
        SDL_RenderPresent(gRenderer);

        // Delay loading screen
        SDL_Delay(500);

        // Play victory music
        Mix_PlayMusic(winner, 0);

        // Render winning scene
        gWinningTexture.render(0, 0);

        // Render playAgain
        gPlayAgainWinTexture.render((SCREEN_WIDTH - gPlayAgainWinTexture.getWidth()) / 2, SCREEN_HEIGHT - gPlayAgainWinTexture.getHeight());
    }
    if (mediumgameOver)
    {
        // Render background
        gBackgroundTexture.render(0, 0);
        // Play losing music
        Mix_PlayMusic(loser, 0);

        for (int i = 0; i < MEDIUM_ROW_SIZE; i++)
        {
            for (int j = 0; j < MEDIUM_COLUMN_SIZE; j++)
            {
                smediumBoard[i][j] = mediumboard[i][j];
                gmediumgameplayButtons[i][j].render(i, j);
            }
        }
        // Render game over text
        gTextTexture.render((SCREEN_WIDTH - gTextTexture.getWidth()) / 2, 0);
        // Render play again
        gPlayAgainLoseTexture.render((SCREEN_WIDTH - gPlayAgainLoseTexture.getWidth()) / 2, SCREEN_HEIGHT - gPlayAgainLoseTexture.getHeight());
        // update screen
        SDL_RenderPresent(gRenderer);
        SDL_Delay(2000);
    }
}

bool Lmediumgameplay::checkWinning()
{
    bool win = false;
    if (medium_countTileLeft == MEDIUM_MINE_COUNT)
    {
        win = true;
    }
    return win;
}
void Lmediumgameplay::mediummineManager()
{
    // Render text
    if (!mediumgameOver && !mediumisWinning)
    {
        // Set text color
        SDL_Color textColor = {140, 140, 140, 255};

        // Erase the buffer
        mediummineLeft.str("");
        mediummineLeft << "Flag left: " << medium_countMineLeft;
        if (!gMineLeftTexture.loadFromRenderedText(mediummineLeft.str().c_str(), textColor))
        {
            cout << "Unable to render mine left texture!\n";
        }

        // Render text
        gMineLeftTexture.render((SCREEN_WIDTH - gMineLeftTexture.getWidth()) / 2, 0);
    }
}