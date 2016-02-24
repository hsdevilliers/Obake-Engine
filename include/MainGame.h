#ifndef MAINGAME_H
#define MAINGAME_H

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "Sprite.h"
#include "GLSLProgram.h"

/** \enum Various game states
 */
enum class GameState
{
    PLAY,
    EXIT
};

class MainGame
{
    public:
        MainGame();
        ~MainGame();

        /** \fn void run()
         *  Runs the initSystems() function.
         */
        void run();

    protected:

    private:
        void initSystems(); /**< Initializes the various systems required to run the game */
        void initShaders(); /**< Initializes the various shaders used in the game */
        void gameLoop();/**< Tracks the passage of time to control the rate of gameplay */
        void processInput();/**< Handles user input since the function was last called */
        void update(); /**< Advances the game simulation with one step */
        void render(); /**< Draws the game */

        SDL_Window* _window; /**< Pointer to SDL_Window object that is initialized in the initSystems() function. */
        int _screenWidth; /**< Screen width of the window. */
        int _screenHeight; /**< Screen height of the window. */

        GameState _gameState;

        Sprite _sprite;

        GLSLProgram _colorShaderProgram;

};

#endif // MAINGAME_H
