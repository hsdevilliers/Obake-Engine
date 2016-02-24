#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>

class Sprite
{
    public:
        Sprite();
        virtual ~Sprite();

        void init(float x, float y, float width, float height);
        void renderSprite();

    protected:

    private:
        float _x;
        float _y;
        float _width;
        float _height;

        GLuint _vboID;
};

#endif // SPRITE_H
