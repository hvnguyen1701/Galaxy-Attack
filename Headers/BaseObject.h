#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class BaseObject {
protected:
    SDL_Renderer *renderer;
    SDL_Texture *image;
    SDL_Rect src, dst;
    
public:
    BaseObject();
    BaseObject(SDL_Renderer *renderer);
    void setRenderer(SDL_Renderer *renderer);
    void loadImage(const std::string &path);
    void setImage(SDL_Texture *image);
    void setPositionDst(int x, int y);
    void setWidthHeightDst(int w, int h);
    SDL_Rect getDst() const;
    int getWidthDst() const;
    int getHeightDst() const;
    void render() const;
};

#endif