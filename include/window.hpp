#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// Screen dimension constants
const int SCREEN_WIDTH = 460;
const int SCREEN_HEIGHT = 460;

// The window we'll be rendering to
extern SDL_Window *gWindow;

// The window renderer
extern SDL_Renderer *gRenderer;

//The sound effects that will be used
extern Mix_Music *winner;
extern Mix_Music *loser;

using namespace std;

bool init();