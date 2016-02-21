#include <cstdio>

#include "MainGame.h"

MainGame::MainGame()
{
    _window = nullptr; //Set to nullptr to handle exception of window not being created
    _screenWidth = 1024; //Temporarily hard-coded
    _screenHeight = 768; //Temporarily hard-coded
    _gameState = GameState::PLAY;
}

MainGame::~MainGame()
{
    //dtor
}

void MainGame::run()
{
    initSystems();
    gameLoop();
}

void MainGame::initSystems()
{
    SDL_Init(SDL_INIT_EVERYTHING); //Initialize SDL
    _window = SDL_CreateWindow("Obake Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL); //Creates SDL window
}

void MainGame::gameLoop()
{
    while(_gameState != GameState::EXIT)
    {
        processInput();
    }
}

void MainGame::processInput()
{
    SDL_Event inputEvent;
    while(SDL_PollEvent(&inputEvent))
    {
        switch(inputEvent.type)
        {
        case SDL_QUIT:
            {
                _gameState = GameState::EXIT;
                break;
            }
        case SDL_MOUSEMOTION:
            {
                printf("(%i, %i)\n", inputEvent.motion.x, inputEvent.motion.y); //Print the mouse coordinates (relative to the SDL_Window) to the console
                break;
            }
        }
    }
}
