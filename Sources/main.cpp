#include <ctime>

#include "../Headers/Control.h"

int main(int argc, char **argv) {
    srand(time(nullptr));
    
    Control gameProject;

    gameProject.initFontAndTexture();
    gameProject.initSoundAndMusic();
    gameProject.initBaseObjects();
    gameProject.initNewGame();
    
    gameProject.showMenu();

    // If user don't exit
    gameProject.playGame();

    return 0;
}