#ifndef MAINGAME_H
#define MAINGAME_H

#include <SDL2/SDL.h>
#include <GL/glew.h>

class MainGame
{
    public:
        MainGame();
        ~MainGame();

        /** \fn void run()
         *  Runs the initSystems() function.
         */
        void run();

        /** \fn void initSystems()
         *  Initializes the various systems used in the game engine.
         */
        void initSystems();

    protected:

    private:
        SDL_Window* _window; /**< Pointer to SDL_Window object that is initialized in the initSystems() function. */
        int _screenWidth;
        int _screenHeight;

};

#endif // MAINGAME_H
