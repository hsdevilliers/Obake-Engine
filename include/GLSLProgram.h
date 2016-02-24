#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include <string>
#include <GL/glew.h>

/** \class GLSLProgram
 * \brief OpenGL Shader Language Program (GLSLProgram)
 * Class that handles the shader pipelining
 * Source: <a href="https://www.opengl.org/wiki/Shader_Compilation">Shader Object Compilation</a>
 */


class GLSLProgram
{
    public:
        GLSLProgram();
        ~GLSLProgram();

        void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
        void linkShaders();

        void addAttribute(const std::string& attributeName); /**< Order in which attributes are added is important */

        void use();
        void unuse();

    protected:

    private:
        void compileShader(const std::string& shaderFilePath, GLuint shaderID);

        GLuint _programID; /**< ID for the GLSLProgram */
        GLuint _vertexShaderID; /**< ID for the vertex shader */
        GLuint _fragmentShaderID; /**< ID for the fragment shader */

        int _numberOfAttributes; /**< Number of attributes a shader file contains */

};

#endif // GLSLPROGRAM_H
