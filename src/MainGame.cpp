#include <cstdio>
#include <string>
#include <iostream>

#include "MainGame.h"

void fatalError(std::string errorString)
{
    printf("%s\n", errorString.c_str());
    printf("A fatal error occurred!\nEnter any key to quit...\n");
    int tmp;
    std::cin >> tmp;

    SDL_Quit(); //SDL function that can quit the program from any point in the code
}

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

    if(!_window)
    {
        fatalError("SDL_Window could not be created!");
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(_window); //Attach the SDL_GLContext to the SDL_Window
    if(!glContext)
    {
        fatalError("SDL_GLContext could not be created!");
    }

    GLenum error = glewInit(); //Initialize GLEW, fetching all of the necessary extensions
    if(error != GLEW_OK)
    {
        fatalError("Could not initialize GLEW!");
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //Initializes the Double Buffer pattern

    glClearColor(0.0f, 0.0f, 1.0f, 1.0); //Set the color to be switched to with glClear() in drawGame()
}

void MainGame::gameLoop()
{
    while(_gameState != GameState::EXIT)
    {
        processInput();
        drawGame();
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

void MainGame::drawGame()
{
    glClearDepth(1.0); //Sets OpenGL's clear depth
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Each time the game is draw, the buffer is cleared

    //Temporary piece of code using deprecated OpenGL method of drawing
    //***********************************************************************************
    glEnableClientState(GL_COLOR_ARRAY);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0, 0);
    glVertex2f(0, 500);
    glVertex2f(500, 500);
    glEnd();
    //***********************************************************************************

    SDL_GL_SwapWindow(_window);
}
