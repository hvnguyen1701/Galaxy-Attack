#include "../Headers/SDL_utils.h"

using namespace std;

void logSDLError(ostream &os, const string &msg, bool fatal) {
    os << msg << " Error: " << SDL_GetError() << "\n";
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, string windowTitle,
             int SCREEN_WIDTH, int SCREEN_HEIGHT) {
    // Error SDL Init
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) logSDLError(cout, "SDL_Init", true);

    // Error Window
    window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError(cout, "CreateWindow", true);

    // Error renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) logSDLError(cout, "CreateRenderer", true);

    // Error TrueType Font
    if (TTF_Init() != 0) {
		cout << "TTF_Init Error: " << TTF_GetError() << "\n";
        quitSDL(window, renderer);
		exit(1);
	}

    // Error Image
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initStatus = IMG_Init(flags);
    if ((initStatus & flags) != flags) {
        cout << "IMG_Init Error: " << IMG_GetError() << "\n";
        quitSDL(window, renderer);
		exit(1);
    }

    // Error Mixer
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) != 0) {
		cout << "Mix_OpenAudio Error: " << Mix_GetError() << "\n";
        quitSDL(window, renderer);
		exit(1);
	}
}

void setIcon(SDL_Window *window, const string &iconPath) {
    SDL_Surface *icon = IMG_Load((iconPath + "Icon Game.png").c_str());
    SDL_SetWindowIcon(window, icon);
}

void quitSDL(SDL_Window *window, SDL_Renderer *renderer) {
    Mix_CloseAudio();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}