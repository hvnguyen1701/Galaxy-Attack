#ifndef CONTROL_H
#define CONTROL_H

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "Asteroid.h"
#include "Background.h"
#include "Bar.h"
#include "Bullet.h"
#include "Button.h"
#include "EnemyShip.h"
#include "Explosion.h"
#include "Gate.h"
#include "Item.h"
#include "SDL_utils.h"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 695

const SDL_Color GRAY_COLOR = {128, 128, 128};
const SDL_Color BLACK_COLOR = {0, 0, 0};
const SDL_Color ORANGE_RED_COLOR = {255, 69, 0};
const SDL_Color LIGHT_SEA_GREEN_COLOR = {32, 178, 170};

const int FPS = 80;
const int DELAY_TIME = ceil(1000.0/FPS);

const int NUMBER_MAPS = 3;
const int NUMBER_PLAYER_BULLETS = 8;
const int NUMBER_STORY_IMAGES = 3;

const int MAX_PLAYER_SHIELD = 5;
const int MAX_SCORE = 1e4 - 1;
const int SCORE_CHANGE_MAP = 10;
const int SPEED_SCROLL_NEBULA_BG = 3;

const int DISTANCE_BETWEEN_2_PLAYER_BULLETS = 25;
const int DISTANCE_BETWEEN_2_ENEMY_BULLETS = 60;
const int DISTANCE_BETWEEN_2_SPAWN_ENEMY = 70;
const int DISTANCE_BETWEEN_2_SPAWN_ASTEROIDS = 100;

const std::string WINDOW_TITLE = "Galaxy Attack";

const std::string IMAGES_PATH = "assets/images/";
const std::string SOUNDS_PATH = "assets/sounds/";
const std::string FONTS_PATH = "assets/fonts/";

const std::string ICON_PATH = IMAGES_PATH + "Icon/";
const std::string BACKGROUND_PATH = IMAGES_PATH + "Background/";
const std::string SPACE_GATE_PATH = IMAGES_PATH + "Space Gate/";
const std::string SHIP_PATH = IMAGES_PATH + "Ship/";
const std::string BULLET_PATH = IMAGES_PATH + "Bullet/";
const std::string ASTEROID_PATH = IMAGES_PATH + "Asteroid/";
const std::string EXPLOSION_PATH = IMAGES_PATH + "Explosion/";
const std::string BUTTON_PATH = IMAGES_PATH + "Button/";
const std::string STORY_PATH = IMAGES_PATH + "Story/";
const std::string BAR_PATH = IMAGES_PATH + "Bar/";
const std::string SCORE_IMAGE_PATH = IMAGES_PATH + "Score Image/";

const std::string SCORE_LOG_FILE_PATH = "Log files/score.log";

class Control {
    SDL_Window *window;
    SDL_Renderer *renderer;

    TTF_Font *tarrgetAcademyRegularFont, *ocraextFont, *sansFont;

    SDL_Texture *asteroidTexture, *enemyTexture, *enemyExplosionTexture, *playerExplosionTexture;
    SDL_Texture *playerBulletTextures[NUMBER_PLAYER_BULLETS], *enemyBulletTexture;
    SDL_Texture *gameTitleLine1, *gameTitleLine2, *storyTexture[NUMBER_STORY_IMAGES];
    SDL_Texture *continueText, *backText, *pausingMessage;
    SDL_Texture *gameOverTexture, *digitTextures[10], *scoreTexture, *bestScoresTexture;

    Mix_Chunk *spawnPlayerBulletChunk, *spawnEnemyBulletChunk, *getItemChunk;
    Mix_Chunk *playerExplosionChunk, *enemyExplosionChunk, *spaceGateChunk;

    Mix_Music *soundtrack;

    SDL_Rect gameTitleLine1Rect, gameTitleLine2Rect;
    SDL_Rect continueTextRect, backTextRect, pausingMessageRect;
    SDL_Rect scoreTextRect, bestScoresTextRect;

    Background nebulaBgs[NUMBER_MAPS], starsBg;
    Gate spaceGates[NUMBER_MAPS];
    Ship playerShip;
    Explosion playerExplosion;
    Item powerItem;
    Button playButton, continueButton, helpButton, backButton, exitButton, nextButton;
    Bar barShield;

    std::vector<int> bestScores;

    std::vector<EnemyShip*> enemyShips;
    std::vector<Bullet*> playerBullets;
    std::vector<Bullet*> enemiesBullets;
    std::vector<Asteroid*> asteroids;
    std::vector<Explosion*> enemyExplosions;

    int mouseX, mouseY, initialPlayerPosX, initialPlayerPosY;

    int countFramePlayerBullet, countFrameEnemyBullet, countFrameSpawnEnemy, countFrameAsteroid;
    int indexCurrentMap, indexCurrentPlayerBullet, score;

    bool isRunningGame, isRunningMenu, isPaused, isGameOver;

    void loadTtfTexture(SDL_Renderer *renderer, TTF_Font *font, 
                        const std::string &text, SDL_Color color, SDL_Texture* &message);
    void clearPointerVector();
    void updateScreen();
    void handleFPS(Uint32 frameStart) const;
    void pauseGame(int playerX, int playerY);
    void gameOverScreen();
    void exitGame();

    void renderTop3BestScores();

    void spawnEnemies();
    void spawnAsteroids();
    void spawnGates();
    void spawnPlayerBullets();
    void spawnEnemiesBullets();
    void spawnEnemyExplosion(int explosionX, int explosionY);
    void spawnPlayerExplosion(int explosionX, int explosionY);
    void spawnPowerItem(int enemyX, int enemyY);

    void scrollAndRenderBackground();
    void moveAndRenderPlayerShip();
    void moveAndRenderPlayerBullets();
    void moveAndRenderEnemies();
    void moveAndRenderEnemiesBullets();
    void moveAndRenderAsteroids();
    void moveAndRenderGates();
    void moveAndRenderItems();
    
    void renderScore();
    void writeScoresToFile();
    void readScoresFromFile();

    void killEnemies();

    void handleCollisionPlayerBulletsAndEnemies();
    void handleCollisionPlayerAndEnemyBullets();
    void handleCollisionPlayerAndEnemies();
    void handleCollisionPlayerAndAsteroids();
    void handleCollisionPlayerAndGates();
    void handleCollisionPlayerAndItems();
    void handleCollisionEnemiesAndAsteroids();

    void handleEnemyExplosions();
    void handlePlayerExplosion();

public:
    Control();
    ~Control();
    void initFontAndTexture();
    void initSoundAndMusic();
    void initBaseObjects();
    void initNewGame();
    void showMenu();
    void playGame();
};

#endif