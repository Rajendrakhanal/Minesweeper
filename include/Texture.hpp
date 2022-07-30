#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
using namespace std;

extern TTF_Font *gGameOver;

// Texture wrapper class
class LTexture
{
public:
    // Initializes variables
    LTexture();

    // Deallocates memory
    ~LTexture();

    // Creates image from font string
    bool loadFromRenderedText(string textureText, SDL_Color textColor);

    // Loads image at specified path
    bool loadFromFile(string path);

    // Deallocates texture
    void free();

    // Renders texture at given point
    void render(int x, int y, SDL_Rect *clip = NULL);

    // Gets image dimensions
    int getWidth();
    int getHeight();

private:
    // The actual hardware texture
    SDL_Texture *mTexture;

    // Image dimensions
    int mWidth;
    int mHeight;
};

 extern LTexture gdifficultymenuTexture;