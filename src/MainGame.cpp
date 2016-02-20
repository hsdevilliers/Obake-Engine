#include "MainGame.h"

MainGame::MainGame()
{
    _window = nullptr; //Set to nullptr to handle exception of window not being created
    _screenWidth = 1024; //Temporarily hard-coded
    _screenHeight = 768; //Temporarily hard-coded
}

MainGame::~MainGame()
{
    //dtor
}

void MainGame::run()
{
    initSystems();
}

void MainGame::initSystems()
{
    SDL_Init(SDL_INIT_EVERYTHING); //Initialize SDL
    _window = SDL_CreateWindow("Obake Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL); //Creates SDL window
}
