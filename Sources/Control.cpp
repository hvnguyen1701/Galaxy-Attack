#include "../Headers/Control.h"

using namespace std;

Control::Control() {
    initSDL(window, renderer, WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
    setIcon(window, ICON_PATH);
}

void Control::clearPointerVector() {
    for (auto ship: enemyShips) delete ship;
    for (auto bullet: playerBullets) delete bullet;
    for (auto bullet: enemiesBullets) delete bullet;
    for (auto asteroid: asteroids) delete asteroid;
    for (auto explosion: enemyExplosions) delete explosion;

    enemyShips.clear();
    playerBullets.clear();
    enemiesBullets.clear();
    asteroids.clear();
    enemyExplosions.clear();
}

Control::~Control() {
    playerShip.clean();

    SDL_DestroyTexture(asteroidTexture);
    SDL_DestroyTexture(enemyTexture);
    SDL_DestroyTexture(enemyExplosionTexture);
    SDL_DestroyTexture(playerExplosionTexture);
    
    for (int i = 0; i < NUMBER_PLAYER_BULLETS; i++) SDL_DestroyTexture(playerBulletTextures[i]);
    SDL_DestroyTexture(enemyBulletTexture);

    SDL_DestroyTexture(gameTitleLine1);
    SDL_DestroyTexture(gameTitleLine2);
    for (int i = 0; i < NUMBER_STORY_IMAGES; i++) SDL_DestroyTexture(storyTexture[i]);

    SDL_DestroyTexture(continueText);
    SDL_DestroyTexture(backText);
    SDL_DestroyTexture(pausingMessage);

    SDL_DestroyTexture(gameOverTexture);

    clearPointerVector();

    bestScores.clear();

    quitSDL(window, renderer);
}

void Control::loadTtfTexture(SDL_Renderer *renderer, TTF_Font *font, const string &text, SDL_Color color, SDL_Texture* &message) {
    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), color);
    message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);
}

void Control::initFontAndTexture() {
    tarrgetAcademyRegularFont = TTF_OpenFont((FONTS_PATH + "TarrgetAcademyRegular.ttf").c_str(), 1000);;
    ocraextFont = TTF_OpenFont((FONTS_PATH + "OCRAEXT.TTF").c_str(), 1000);;
    sansFont = TTF_OpenFont((FONTS_PATH + "OpenSans-Regular.ttf").c_str(), 1000);

    loadTtfTexture(renderer, tarrgetAcademyRegularFont, "GALAXY", LIGHT_SEA_GREEN_COLOR, gameTitleLine1);
    loadTtfTexture(renderer, tarrgetAcademyRegularFont, "ATTACK", LIGHT_SEA_GREEN_COLOR, gameTitleLine2);

    loadTtfTexture(renderer, sansFont, "CONTINUE", BLACK_COLOR, continueText);
    loadTtfTexture(renderer, sansFont, "BACK TO MENU", BLACK_COLOR, backText);
    loadTtfTexture(renderer, ocraextFont, "PAUSED", ORANGE_RED_COLOR, pausingMessage);

    playerBulletTextures[0] = IMG_LoadTexture(renderer, (BULLET_PATH + "Lawn Green.png").c_str());
    playerBulletTextures[1] = IMG_LoadTexture(renderer, (BULLET_PATH + "Green.png").c_str());
    playerBulletTextures[2] = IMG_LoadTexture(renderer, (BULLET_PATH + "White.png").c_str());
    playerBulletTextures[3] = IMG_LoadTexture(renderer, (BULLET_PATH + "Violet.png").c_str());
    playerBulletTextures[4] = IMG_LoadTexture(renderer, (BULLET_PATH + "Red.png").c_str());
    playerBulletTextures[5] = IMG_LoadTexture(renderer, (BULLET_PATH + "Green Curve.png").c_str());
    playerBulletTextures[6] = IMG_LoadTexture(renderer, (BULLET_PATH + "Blue Curve.png").c_str());
    playerBulletTextures[7] = IMG_LoadTexture(renderer, (BULLET_PATH + "Orange Curve.png").c_str());

    enemyBulletTexture = IMG_LoadTexture(renderer, (BULLET_PATH + "Machine Gun.png").c_str());

    asteroidTexture = IMG_LoadTexture(renderer, (ASTEROID_PATH + "Asteroid.png").c_str());
    enemyTexture = IMG_LoadTexture(renderer, (SHIP_PATH + "Enemy.png").c_str());
    enemyExplosionTexture = IMG_LoadTexture(renderer, (EXPLOSION_PATH + "Enemy Death.png").c_str());
    playerExplosionTexture = IMG_LoadTexture(renderer, (EXPLOSION_PATH + "Player Death.png").c_str());

    storyTexture[0] = IMG_LoadTexture(renderer, (STORY_PATH + "Part 1.png").c_str());
    storyTexture[1] = IMG_LoadTexture(renderer, (STORY_PATH + "Part 2.png").c_str());
    storyTexture[2] = IMG_LoadTexture(renderer, (STORY_PATH + "Part 3.png").c_str());

    gameOverTexture = IMG_LoadTexture(renderer, (BACKGROUND_PATH + "Game Over.png").c_str());

    scoreTexture = IMG_LoadTexture(renderer, (SCORE_IMAGE_PATH + "score text.png").c_str());
    bestScoresTexture = IMG_LoadTexture(renderer, (SCORE_IMAGE_PATH + "top3bestscores text.png").c_str());
    for (int i = 0; i < 10; i++)
        digitTextures[i] = IMG_LoadTexture(renderer, (SCORE_IMAGE_PATH + "numeral" + char(i + '0') + ".png").c_str());
}

void Control::initSoundAndMusic() {
    spawnPlayerBulletChunk = Mix_LoadWAV((SOUNDS_PATH + "Spawn Player Bullet.wav").c_str());
    spawnEnemyBulletChunk = Mix_LoadWAV((SOUNDS_PATH + "Spawn Enemy Bullet.wav").c_str());
    playerExplosionChunk = Mix_LoadWAV((SOUNDS_PATH + "Player Explosion.wav").c_str());
    enemyExplosionChunk = Mix_LoadWAV((SOUNDS_PATH + "Enemy Explosion.wav").c_str());

    spaceGateChunk = Mix_LoadWAV((SOUNDS_PATH + "Use Space Gate.wav").c_str());
    getItemChunk = Mix_LoadWAV((SOUNDS_PATH + "Get Item.wav").c_str());

    soundtrack = Mix_LoadMUS((SOUNDS_PATH + "Soundtrack.mp3").c_str());
}

void Control::initBaseObjects() {
    readScoresFromFile();

    for (int i = 0; i < NUMBER_MAPS; i++) {
        nebulaBgs[i].setRenderer(renderer);
        spaceGates[i].setRenderer(renderer);
    }
    starsBg.setRenderer(renderer);
    playerShip.setRenderer(renderer);
    playerExplosion.setRenderer(renderer);
    powerItem.setRenderer(renderer);

    playButton.setRenderer(renderer);
    continueButton.setRenderer(renderer);
    helpButton.setRenderer(renderer);
    backButton.setRenderer(renderer);
    exitButton.setRenderer(renderer);
    nextButton.setRenderer(renderer);

    barShield.setRenderer(renderer);

    playerShip.loadImage(SHIP_PATH + "Player.png");
    nebulaBgs[0].loadImage(BACKGROUND_PATH + "Red Nebula.png");
    nebulaBgs[1].loadImage(BACKGROUND_PATH + "Blue Nebula.png");
    nebulaBgs[2].loadImage(BACKGROUND_PATH + "Aqua-Pink Nebula.png");
    starsBg.loadImage(BACKGROUND_PATH + "Plentiful Stars.png");
    powerItem.loadImage(ICON_PATH + "Power Up.png");

    spaceGates[0].loadImage(SPACE_GATE_PATH + "Blue Gate.png");
    spaceGates[1].loadImage(SPACE_GATE_PATH + "Yellow Gate.png");
    spaceGates[2].loadImage(SPACE_GATE_PATH + "Red Gate.png");

    playButton.loadImage(BUTTON_PATH + "play.png");
    helpButton.loadImage(BUTTON_PATH + "help.png");
    exitButton.loadImage(BUTTON_PATH + "exit.png");
    continueButton.loadImage(BUTTON_PATH + "continue.png");
    backButton.loadImage(BUTTON_PATH + "back.png");
    nextButton.loadImage(BUTTON_PATH + "next.png");

    barShield.loadImage(BAR_PATH + "Bar Shield.png", MAX_PLAYER_SHIELD + 1);

    playerExplosion.setImage(playerExplosionTexture, 8, 8);

    playerExplosion.setWidthHeightDst(300, 300);

    playButton.setWidthHeightDst(100, 80);
    helpButton.setWidthHeightDst(playButton.getWidthDst(), playButton.getHeightDst());
    exitButton.setWidthHeightDst(playButton.getWidthDst(), playButton.getHeightDst());
    
    continueButton.setWidthHeightDst(100, 100);
    backButton.setWidthHeightDst(continueButton.getWidthDst(), continueButton.getHeightDst());
    
    nextButton.setWidthHeightDst(70, 70);

    playButton.setPositionDst(SCREEN_WIDTH/2 - playButton.getWidthDst()/2, SCREEN_HEIGHT - 500);
    helpButton.setPositionDst(playButton.getDst().x, playButton.getDst().y + playButton.getHeightDst() + 50);
    exitButton.setPositionDst(playButton.getDst().x, helpButton.getDst().y + helpButton.getHeightDst() + 50);
    continueButton.setPositionDst(SCREEN_WIDTH/6, 250);
    backButton.setPositionDst(SCREEN_WIDTH - continueButton.getDst().x - backButton.getWidthDst(), continueButton.getDst().y);
    
    nextButton.setPositionDst(SCREEN_WIDTH - nextButton.getWidthDst() - 30, SCREEN_HEIGHT - nextButton.getHeightDst() - 30);

    barShield.setWidthHeightDst(200, 23);
    barShield.setPositionDst(0, SCREEN_HEIGHT - barShield.getHeightDst() - 10);

    gameTitleLine1Rect = {SCREEN_WIDTH/8, 10, 3*SCREEN_WIDTH/4, SCREEN_HEIGHT/12};
    gameTitleLine2Rect = {gameTitleLine1Rect.x, gameTitleLine1Rect.y + 70, gameTitleLine1Rect.w, gameTitleLine1Rect.h};

    continueTextRect.w = 150;
    continueTextRect.h = 50;
    continueTextRect.x = continueButton.getDst().x - continueTextRect.w/2 + continueButton.getWidthDst()/2;
    continueTextRect.y = continueButton.getDst().y + continueButton.getHeightDst() + 25;

    backTextRect.w = continueTextRect.w + 20;
    backTextRect.h = continueTextRect.h;
    backTextRect.x = backButton.getDst().x - backTextRect.w/2 + backButton.getWidthDst()/2;
    backTextRect.y = continueTextRect.y;

    pausingMessageRect = {SCREEN_WIDTH/8, 120, 3*SCREEN_WIDTH/4, SCREEN_HEIGHT/12};

    scoreTextRect = {SCREEN_WIDTH/2 + 40, barShield.getDst().y - 10, 70, barShield.getHeightDst() + 10};
    bestScoresTextRect = {playButton.getDst().x + playButton.getWidthDst() + 20, playButton.getDst().y + 10, 175, 60};

    initialPlayerPosX = SCREEN_WIDTH/2 - playerShip.getWidthDst()/2;
    initialPlayerPosY = SCREEN_HEIGHT - playerShip.getHeightDst() - 40;
}

void Control::initNewGame() {
    isRunningGame = true;
    isPaused = isGameOver = false;

    countFramePlayerBullet = countFrameEnemyBullet = 0;
    countFrameSpawnEnemy = countFrameAsteroid = 0;
    indexCurrentPlayerBullet = indexCurrentMap = score = 0;

    barShield.setState(MAX_PLAYER_SHIELD);
    playerShip.setShield(MAX_PLAYER_SHIELD, MAX_PLAYER_SHIELD);

    for (Background &bg: nebulaBgs) {
        bg.setValueDst(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        bg.setValueNextDst(0, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    starsBg.setValueDst(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    starsBg.setValueNextDst(0, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);

    powerItem.setActivation(false);
    for (Gate &spaceGate: spaceGates) spaceGate.setActivation(false);

    clearPointerVector();
}

void Control::exitGame() {
    isRunningMenu = isRunningGame = isPaused = false;
}

void Control::updateScreen() {
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

void Control::handleFPS(Uint32 frameStart) const {
    Uint32 frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < DELAY_TIME) SDL_Delay(DELAY_TIME - frameTime);
}

void Control::renderTop3BestScores() {
    SDL_RenderCopy(renderer, bestScoresTexture, nullptr, &bestScoresTextRect);

    int tempDigitDstY = bestScoresTextRect.y + bestScoresTextRect.h + 4;
    for (int score: bestScores) {
        string scoreString = to_string(score);

        SDL_Rect digitDst;
        digitDst.w = digitDst.h = 25;
        digitDst.x = bestScoresTextRect.x + bestScoresTextRect.w/2 - digitDst.w*scoreString.size()/2;
        digitDst.y = tempDigitDstY;

        for (char digit: scoreString) {
            SDL_RenderCopy(renderer, digitTextures[digit - '0'], nullptr, &digitDst);
            digitDst.x += digitDst.w + 2;
        }
        
        tempDigitDstY += digitDst.h + 10;
    }
}

void Control::showMenu() {
    readScoresFromFile();
    Mix_PlayMusic(soundtrack, -1);

    int indexPageStory = 0;
    bool isOnHelpScreen = false;

    isRunningMenu = true;
    while (isRunningMenu) {
        Uint32 frameStart = SDL_GetTicks();

	    // Event processing
        SDL_Event event;
        while (SDL_PollEvent(&event))
            switch (event.type) {
                case SDL_QUIT:
                    exitGame();
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (!isOnHelpScreen) {
                        if (playButton.isMouseOnButton(mouseX, mouseY)) {
                            SDL_WarpMouseInWindow(window, initialPlayerPosX + playerShip.getWidthDst()/2,
                                                initialPlayerPosY + playerShip.getHeightDst()/2);
                            isRunningMenu = false;
                            SDL_ShowCursor(SDL_DISABLE);
                        }
                        else if (helpButton.isMouseOnButton(mouseX, mouseY)) isOnHelpScreen = true;
                        else if (exitButton.isMouseOnButton(mouseX, mouseY)) exitGame();
                    }
                    else {
                        if (nextButton.isMouseOnButton(mouseX, mouseY)) indexPageStory++;
                        if (indexPageStory >= NUMBER_STORY_IMAGES) {
                            indexPageStory = 0;
                            isOnHelpScreen = false;
                        }
                    }
                    break;
            }
        
        if (!isRunningMenu) {
            SDL_RenderClear(renderer);
            break;
        }


        // Update and render
        SDL_GetMouseState(&mouseX, &mouseY);

        scrollAndRenderBackground();
        
        playerShip.setPositionDst(initialPlayerPosX, initialPlayerPosY);
        playerShip.render();

        if (!isOnHelpScreen) {
            SDL_RenderCopy(renderer, gameTitleLine1, nullptr, &gameTitleLine1Rect);
            SDL_RenderCopy(renderer, gameTitleLine2, nullptr, &gameTitleLine2Rect);

            if (playButton.isMouseOnButton(mouseX, mouseY)) playButton.animate();
            if (helpButton.isMouseOnButton(mouseX, mouseY)) helpButton.animate();
            if (exitButton.isMouseOnButton(mouseX, mouseY)) exitButton.animate();

            playButton.render();
            helpButton.render();
            exitButton.render();

            renderTop3BestScores();
        }
        else {
            if (nextButton.isMouseOnButton(mouseX, mouseY)) nextButton.animate();
            nextButton.render();
            SDL_RenderCopy(renderer, storyTexture[indexPageStory], nullptr, nullptr);
        }

        updateScreen();
        handleFPS(frameStart);
    }
}

void Control::pauseGame(int playerX, int playerY) {
    SDL_ShowCursor(SDL_ENABLE);
    SDL_SetWindowGrab(window, SDL_FALSE);   

    isPaused = true;
    while (isPaused) {
        Uint32 frameStart = SDL_GetTicks();

	    // Event processing
        SDL_Event event;
        while (SDL_PollEvent(&event))
            switch (event.type) {
                case SDL_QUIT:
                    exitGame();
                    return;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) isPaused = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (continueButton.isMouseOnButton(mouseX, mouseY)) isPaused = false;
                    else if (backButton.isMouseOnButton(mouseX, mouseY)) {
                        isPaused = false;
                        initNewGame();
                        showMenu();
                        
                        // Fix the error that the ship is in the wrong position when 
                        // from the pause screen -> menu screen -> play game
                        playerX = -1;
                    }
                    break;
            }
            
        if (!isPaused) {
            SDL_RenderClear(renderer);
            break;
        }

        // Update
        SDL_GetMouseState(&mouseX, &mouseY);

        if (continueButton.isMouseOnButton(mouseX, mouseY)) continueButton.animate();
        if (backButton.isMouseOnButton(mouseX, mouseY)) backButton.animate();

        // Render
        SDL_SetRenderDrawColor(renderer, GRAY_COLOR.r, GRAY_COLOR.g, GRAY_COLOR.b, 0);

        continueButton.render();
        backButton.render();

        SDL_RenderCopy(renderer, continueText, nullptr, &continueTextRect);
        SDL_RenderCopy(renderer, backText, nullptr, &backTextRect);
        SDL_RenderCopy(renderer, pausingMessage, nullptr, &pausingMessageRect);

        updateScreen();
        handleFPS(frameStart);
    }

    SDL_ShowCursor(SDL_DISABLE);
    SDL_SetWindowGrab(window, SDL_TRUE);

    if (playerX > -1) SDL_WarpMouseInWindow(window, playerX, playerY);
}

void Control::spawnEnemies() {
    if (countFrameSpawnEnemy == DISTANCE_BETWEEN_2_SPAWN_ENEMY) {
        enemyShips.push_back(new EnemyShip(renderer, SCREEN_WIDTH));
        enemyShips.back()->setImage(enemyTexture);
        countFrameSpawnEnemy = 0;
    }
}

void Control::spawnAsteroids() {
    if (countFrameAsteroid == DISTANCE_BETWEEN_2_SPAWN_ASTEROIDS) {
        asteroids.push_back(new Asteroid(renderer, SCREEN_WIDTH, SCREEN_HEIGHT));
        asteroids.back()->setImage(asteroidTexture);
        countFrameAsteroid = 0;
    }
}

void Control::spawnGates() {
    if (score > 0 && score%SCORE_CHANGE_MAP == 0 && !spaceGates[indexCurrentMap].getActivation()) {
        spaceGates[indexCurrentMap].setActivation(true);
        spaceGates[indexCurrentMap].setPositionDst(SCREEN_WIDTH/2 - spaceGates[indexCurrentMap].getWidthDst()/2, 
                                                   -spaceGates[indexCurrentMap].getHeightDst());
    }
}

void Control::spawnPlayerBullets() {
    if (countFramePlayerBullet == DISTANCE_BETWEEN_2_PLAYER_BULLETS) {
        playerBullets.push_back(new Bullet(renderer));
        playerBullets.back()->setImage(playerBulletTextures[indexCurrentPlayerBullet]);
        playerBullets.back()->setActivation(true);
        playerBullets.back()->setPositionDst(mouseX - playerBullets.back()->getWidthDst()/2,
                                            mouseY - playerShip.getHeightDst()/2);
        countFramePlayerBullet = 0;

        Mix_PlayChannel(-1, spawnPlayerBulletChunk, 0);
    }
}

void Control::spawnEnemiesBullets() {
    if (countFrameEnemyBullet != DISTANCE_BETWEEN_2_ENEMY_BULLETS) return;
    countFrameEnemyBullet = 0;

    for (auto enemy: enemyShips)
        if (enemy->getActivation()) {
            enemiesBullets.push_back(new Bullet(renderer));
            enemiesBullets.back()->setImage(enemyBulletTexture);
            enemiesBullets.back()->setActivation(true);
            enemiesBullets.back()->setPositionDst(enemy->getDst().x + enemy->getWidthDst()/2 - enemiesBullets.back()->getWidthDst()/2,
                                                  enemy->getDst().y + enemy->getHeightDst() - 20);            
        }
    
    Mix_PlayChannel(-1, spawnEnemyBulletChunk, 0);
}

void Control::spawnEnemyExplosion(int explosionX, int explosionY) {
    enemyExplosions.push_back(new Explosion(renderer));
    enemyExplosions.back()->setImage(enemyExplosionTexture, 1, 15);
    enemyExplosions.back()->setPositionDst(explosionX, explosionY);
    enemyExplosions.back()->setActivation(true);

    Mix_PlayChannel(-1, enemyExplosionChunk, 0);
}

void Control::spawnPlayerExplosion(int explosionX, int explosionY) {
    playerExplosion.setPositionDst(explosionX, explosionY);
    playerExplosion.setActivation(true);
    
    Mix_PlayChannel(-1, playerExplosionChunk, 0);
}

void Control::spawnPowerItem(int enemyX, int enemyY) {
    if (!powerItem.getActivation() && rand()%7 == 0) {
        powerItem.setActivation(true);
        powerItem.setPositionDst(enemyX, enemyY);
    }
}

void Control::scrollAndRenderBackground() {
    nebulaBgs[indexCurrentMap].slip(SPEED_SCROLL_NEBULA_BG, SCREEN_HEIGHT);
    starsBg.slip(SPEED_SCROLL_NEBULA_BG - 1, SCREEN_HEIGHT);
        
    nebulaBgs[indexCurrentMap].render();
    starsBg.render();
}

void Control::moveAndRenderPlayerShip() {
    playerShip.setPositionDst(mouseX - playerShip.getWidthDst()/2, mouseY - playerShip.getHeightDst()/2);
    playerShip.render();
}

void Control::moveAndRenderPlayerBullets() {
    for (int i = 0; i < playerBullets.size(); i++) {
        playerBullets[i]->move(true, SCREEN_HEIGHT);
        if (!playerBullets[i]->getActivation()) {
            delete playerBullets[i];
            playerBullets.erase(playerBullets.begin() + i);
            i--;
        }
        else playerBullets[i]->render();
    }
}

void Control::moveAndRenderEnemies() {
    for (int i = 0; i < enemyShips.size(); i++) {
        enemyShips[i]->move(SCREEN_WIDTH, SCREEN_HEIGHT);
        if (!enemyShips[i]->getActivation()) {
            delete enemyShips[i];
            enemyShips.erase(enemyShips.begin() + i);
            i--;
        }
        else enemyShips[i]->render();
    }
}

void Control::moveAndRenderEnemiesBullets() {
    for (int i = 0; i < enemiesBullets.size(); i++) {
        enemiesBullets[i]->move(false, SCREEN_HEIGHT);
        if (!enemiesBullets[i]->getActivation()) {
            delete enemiesBullets[i];
            enemiesBullets.erase(enemiesBullets.begin() + i);
            i--;
        }
        else enemiesBullets[i]->render();
    }
}

void Control::moveAndRenderAsteroids() {
    for (int i = 0; i < (int)asteroids.size(); i++) {
        asteroids[i]->move(SCREEN_WIDTH, SCREEN_HEIGHT);
        asteroids[i]->animate();
        if (!asteroids[i]->getActivation()) {
            delete asteroids[i];
            asteroids.erase(asteroids.begin() + i);
            i--;
        }
        else asteroids[i]->render();
    }
}

void Control::moveAndRenderGates() {
    if (!spaceGates[indexCurrentMap].getActivation()) return;

    spaceGates[indexCurrentMap].move(SCREEN_HEIGHT);
    spaceGates[indexCurrentMap].animate();
    spaceGates[indexCurrentMap].render();
}

void Control::moveAndRenderItems() {
    powerItem.move(SCREEN_HEIGHT);
    powerItem.render();
}

void Control::renderScore() {
    SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreTextRect);

    string scoreString = to_string(score);
    SDL_Rect digitDst = {scoreTextRect.x + scoreTextRect.w + 5, scoreTextRect.y + 7, 
                         scoreTextRect.h - 10, scoreTextRect.h - 10};
    for (size_t i = 0; i < scoreString.size(); i++) {
        int digit = scoreString[i] - '0';
        SDL_RenderCopy(renderer, digitTextures[digit], nullptr, &digitDst);
        digitDst.x += digitDst.w + 2;
    }
}

void Control::writeScoresToFile() {
    ofstream outfile(SCORE_LOG_FILE_PATH);

    bestScores.push_back(score);
    sort(bestScores.begin(), bestScores.end(), greater<int>());
    if (bestScores.size() > 3) bestScores.pop_back();

    for (int score: bestScores) outfile << score << "\n";

    outfile.close();
}

void Control::readScoresFromFile() {
    ifstream infile(SCORE_LOG_FILE_PATH);

    bestScores.clear();
    int score;
    while (infile >> score) bestScores.push_back(score);

    infile.close();
}

void Control::killEnemies() {
    for (int i = 0; i < (int)enemyShips.size(); i++) 
        if (enemyShips[i]->getDead()) {
            delete enemyShips[i];
            enemyShips.erase(enemyShips.begin() + i);
            i--;
        }
}

void Control::handleCollisionPlayerBulletsAndEnemies() {
    for (auto bullet: playerBullets)
        if (bullet->getActivation())
            for (auto enemy: enemyShips)
                if (enemy->getActivation()) {
                    SDL_Rect bulletDst = bullet->getDst();
                    SDL_Rect enemyDst = enemy->getDst();

                    // Collision
                    if (SDL_HasIntersection(&bulletDst, &enemyDst)) {
                        bullet->setActivation(false);
                        enemy->setActivation(false);
                        enemy->setDead(true);

                        spawnEnemyExplosion(enemyDst.x, enemyDst.y);
                        spawnPowerItem(enemyDst.x, enemyDst.y);

                        score++;
                        if (indexCurrentPlayerBullet >= 5) score++;

                        if (score > MAX_SCORE) score = MAX_SCORE;
                    }
                }
}

void Control::handleCollisionPlayerAndEnemyBullets() {
    for (auto bullet: enemiesBullets)
        if (bullet->getActivation()) {
            SDL_Rect playerDst = playerShip.getDst();
            SDL_Rect bulletDst = bullet->getDst();

            // Handling image errors and reducing difficulty
            SDL_Rect tempPlayerDst = playerShip.getDst();
            tempPlayerDst.x += tempPlayerDst.w/3;
            tempPlayerDst.y += tempPlayerDst.h/3;
            tempPlayerDst.w -= 2*tempPlayerDst.w/3;
            tempPlayerDst.h -= 2*tempPlayerDst.h/3;

            // Collision
            if (SDL_HasIntersection(&tempPlayerDst, &bulletDst)) {
                bullet->setActivation(false);
                playerShip.setShield(barShield.getState() - 1, MAX_PLAYER_SHIELD);
                barShield.setState(barShield.getState() - 1);

                spawnPlayerExplosion(playerDst.x - playerExplosion.getWidthDst()/4,
                                     playerDst.y - playerExplosion.getHeightDst()/4);
            }
        }
}

void Control::handleCollisionPlayerAndEnemies() {
    for (auto enemy: enemyShips)
        if (enemy->getActivation()) {
            SDL_Rect playerDst = playerShip.getDst();
            SDL_Rect enemyDst = enemy->getDst();

            // Handling image errors and reducing difficulty
            enemyDst.x += enemyDst.w/3;
            enemyDst.y += enemyDst.h/3;
            enemyDst.w -= 2*enemyDst.w/3;
            enemyDst.h -= 2*enemyDst.h/3;

            // Collision
            if (SDL_HasIntersection(&playerDst, &enemyDst)) {
                barShield.setState(0);
                playerShip.setShield(-1, MAX_PLAYER_SHIELD);
                spawnPlayerExplosion(playerDst.x - playerExplosion.getWidthDst()/4,
                                     playerDst.y - playerExplosion.getHeightDst()/4);
            }
        }
}

void Control::handleCollisionPlayerAndAsteroids() {
    for (auto asteroid: asteroids)
        if (asteroid->getActivation()) {
            SDL_Rect playerDst = playerShip.getDst();
            SDL_Rect asteroidDst = asteroid->getDst();

            // Handling image errors and reducing difficulty
            asteroidDst.x += asteroidDst.w/3;
            asteroidDst.y += asteroidDst.h/3;
            asteroidDst.w -= 2*asteroidDst.w/3;
            asteroidDst.h -= 2*asteroidDst.h/3;

            // Collision
            if (SDL_HasIntersection(&playerDst, &asteroidDst)) {
                barShield.setState(0);
                playerShip.setShield(-1, MAX_PLAYER_SHIELD);
                spawnPlayerExplosion(playerDst.x - playerExplosion.getWidthDst()/4,
                                     playerDst.y - playerExplosion.getHeightDst()/4);
            }
        }
}

void Control::handleCollisionPlayerAndGates() {
    if (!spaceGates[indexCurrentMap].getActivation()) return;

    SDL_Rect playerDst = playerShip.getDst();
    SDL_Rect gateDst = spaceGates[indexCurrentMap].getDst();

    if (SDL_HasIntersection(&playerDst, &gateDst)) {
        spaceGates[indexCurrentMap].setActivation(false);

        int tempIndexCurrentMap = (indexCurrentMap + 1)%NUMBER_MAPS;
        int tempIndexCurrentPlayerBullet = indexCurrentPlayerBullet;
        int tempScore = score;

        Mix_PlayChannel(-1, spaceGateChunk, 0);

        // Changing map
        for (int i = 0; i < 2*NUMBER_MAPS; i++) {
            SDL_Delay(30);
            nebulaBgs[i%NUMBER_MAPS].render();
            SDL_RenderPresent(renderer);
        }
        initNewGame();
        indexCurrentMap = tempIndexCurrentMap;
        indexCurrentPlayerBullet = tempIndexCurrentPlayerBullet;
        score = tempScore;
    }
}

void Control::handleCollisionPlayerAndItems() {
    if (!powerItem.getActivation()) return;

    SDL_Rect playerDst = playerShip.getDst();
    SDL_Rect itemDst = powerItem.getDst();

    // Collision
    if (SDL_HasIntersection(&playerDst, &itemDst)) {
        Mix_PlayChannel(-1, getItemChunk, 0);

        powerItem.setActivation(false);

        if (indexCurrentPlayerBullet < NUMBER_PLAYER_BULLETS - 1) 
            indexCurrentPlayerBullet++;

        playerShip.setShield(barShield.getState() + 1, MAX_PLAYER_SHIELD);
        barShield.setState(barShield.getState() + 1);
    }
    else moveAndRenderItems();
}

void Control::handleCollisionEnemiesAndAsteroids() {
    for (auto enemy: enemyShips)
        for (auto asteroid: asteroids)
            if (enemy->getActivation() && asteroid->getActivation()) {
                SDL_Rect enemyDst = enemy->getDst();
                SDL_Rect asteroidDst = asteroid->getDst();

                // Handling image errors
                asteroidDst.x += asteroidDst.w/3;
                asteroidDst.y += asteroidDst.h/3;
                asteroidDst.w -= 2*asteroidDst.w/3;
                asteroidDst.h -= 2*asteroidDst.h/3;

                // Collision
                if (SDL_HasIntersection(&enemyDst, &asteroidDst)) {
                    enemy->setActivation(false);
                    enemy->setDead(true);
                    spawnEnemyExplosion(enemyDst.x, enemyDst.y);
                }
            }
}

void Control::handleEnemyExplosions() {
    for (int i = 0; i < (int)enemyExplosions.size(); i++)
        if (enemyExplosions[i]->getActivation()) {
            enemyExplosions[i]->animate();
            enemyExplosions[i]->render();
        }
        else {
            delete enemyExplosions[i];
            enemyExplosions.erase(enemyExplosions.begin() + i);
            i--;
        }
}

void Control::handlePlayerExplosion() {
    if (playerExplosion.getActivation()) {
        playerExplosion.animate();
        playerExplosion.render();
    }
}

void Control::playGame() {
    SDL_ShowCursor(SDL_DISABLE);
    SDL_SetWindowGrab(window, SDL_TRUE);

    // Game loop
    while (isRunningGame) {
        Uint32 frameStart = SDL_GetTicks();

        countFramePlayerBullet++;
        countFrameEnemyBullet++;
        countFrameSpawnEnemy++;
        countFrameAsteroid++;

	    // Event processing
        SDL_Event event;
        while (SDL_PollEvent(&event))
            switch (event.type) {
                case SDL_QUIT:
                    exitGame();
                    break;
                case SDL_KEYDOWN: 
                    if (!isGameOver && event.key.keysym.sym == SDLK_ESCAPE) pauseGame(mouseX, mouseY);
                    break;
                case SDL_WINDOWEVENT:
                    if (!isGameOver && event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) pauseGame(mouseX, mouseY);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (isGameOver) {
                        writeScoresToFile();
                        isGameOver = false;
                        initNewGame();
                        showMenu();
                    }
                    break;
            }

        // Update and render
        SDL_GetMouseState(&mouseX, &mouseY);

        scrollAndRenderBackground();

        spawnEnemies();
        moveAndRenderEnemies();
        handleEnemyExplosions();
        killEnemies();

        spawnAsteroids();
        moveAndRenderAsteroids();

        moveAndRenderGates();

        handleCollisionEnemiesAndAsteroids();

        if (!playerShip.getDead()) {
            moveAndRenderPlayerShip();

            spawnPlayerBullets();
            moveAndRenderPlayerBullets();
            handleCollisionPlayerBulletsAndEnemies();

            spawnEnemiesBullets();
            moveAndRenderEnemiesBullets();

            spawnGates();
            handleCollisionPlayerAndGates();

            handleCollisionPlayerAndEnemyBullets();
            handleCollisionPlayerAndAsteroids();
            handleCollisionPlayerAndEnemies();
            handleCollisionPlayerAndItems();
        }

        handlePlayerExplosion();

        barShield.render();

        renderScore();
    
        if (isGameOver) SDL_RenderCopy(renderer, gameOverTexture, nullptr, nullptr);
        
        if (!playerExplosion.getActivation() && playerShip.getDead()) {
            isGameOver = true;
            SDL_ShowCursor(SDL_ENABLE);
        }

        updateScreen();
        handleFPS(frameStart);
    }
}