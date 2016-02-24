#include "Sprite.h"

Sprite::Sprite()
{
    _vboID = 0; /**< Always initialize VBO's to 0 */
}

Sprite::~Sprite()
{
    if(_vboID != 0)
    {
        glDeleteBuffers(1, &_vboID); /**< Delete 1 specific VBO */
    }
}

void Sprite::init(float x, float y, float width, float height)
{
    _x = x; /**< x-position of sprite */
    _y = y; /**< y-position of sprite */
    _width = width; /**< Width of sprite */
    _height = height; /**< Height of sprite */

    if(_vboID == 0) /**< Check if VBO is initialized */
    {
        glGenBuffers(1, &_vboID); /**< Generate 1 VBO with an unique ID */
    }

    float vertexData[12]; /**< 6 vertexes(3 for each triangle) required in 2 dimensions = 12 */

    //First triangle
    //*****************************************************************
    vertexData[0] = x + width;
    vertexData[1] = y + height;

    vertexData[2] = x;
    vertexData[3] = y + height;

    vertexData[4] = x;
    vertexData[5] = y;
    //*****************************************************************

    //Second triangle
    //*****************************************************************
    vertexData[6] = x;
    vertexData[7] = y;

    vertexData[8] = x + width;
    vertexData[9] = y;

    vertexData[10] = x + width;
    vertexData[11] = y + height;
    //*****************************************************************

    glBindBuffer(GL_ARRAY_BUFFER, _vboID); /**< Bind buffer to a GL_ARRAY_BUFFER type  */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData) /**< How many bites the buffer will store */, vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); /**< Unbind the buffer */
}

void Sprite::renderSprite()
{
    glBindBuffer(GL_ARRAY_BUFFER, _vboID); /**< NB: Can only have 1 buffer active at a time */

    /**
     * \param 0 is the 0th index in the buffer, in this case the "vertexArray" in init()
     */
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0/**< Index in the buffer */, 2/**< The dimensions */, GL_FLOAT/**< The type of the vertexes */, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES/**< Drawing type */, 0, 6/**< Amount of vertexes to draw */);

    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
