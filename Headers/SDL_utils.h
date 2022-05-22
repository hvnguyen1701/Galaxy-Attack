#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

void logSDLError(std::ostream &os, const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, std::string windowTitle,
             int screenWidth, int screenHeight);
void setIcon(SDL_Window *window, const std::string &iconPath);
void quitSDL(SDL_Window *window, SDL_Renderer *renderer);

#endif