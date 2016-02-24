#include "GLSLProgram.h"
#include "Errors.h"

#include <fstream>
#include <vector>

GLSLProgram::GLSLProgram() :
    _programID(0),
    _vertexShaderID(0),
    _fragmentShaderID(0),
    _numberOfAttributes(0)
{
    //ctor
}

GLSLProgram::~GLSLProgram()
{
    //dtor
}

void GLSLProgram::compileShader(const std::string& shaderFilePath, GLuint shaderID)
{
    std::ifstream vertexFile(shaderFilePath);
    if(vertexFile.fail())
    {
        perror(shaderFilePath.c_str());
        fatalError("Failed to open " + shaderFilePath);
    }

    std::string fileContent = "";
    std::string line;

    while(std::getline(vertexFile, line))
    {
        fileContent += line + "\n";
    }

    vertexFile.close();

    const char* fileContentPointer = fileContent.c_str();
    glShaderSource(shaderID, 1, &fileContentPointer, nullptr);

    glCompileShader(shaderID);

    GLint success = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

    if(success == false)
    {
        GLint maxLength = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<char> errorLog(maxLength);
        glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader(shaderID); // Don't leak the shader.

        std::printf("%s\n", &errorLog[0]);
        fatalError("Shader " + shaderFilePath + " failed to compile!");
    }
}

void GLSLProgram::compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath)
{
    //Vertex and fragment shaders are successfully compiled.
    //Now time to link them together into a program.
    //Get a program object.
    _programID = glCreateProgram();

    _vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if(_vertexShaderID == 0)
    {
        fatalError("Vertex shader failed to be created!");
    }

    _fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if(_fragmentShaderID == 0)
    {
        fatalError("Fragment shader failed to be created!");
    }

    compileShader(vertexShaderFilePath, _vertexShaderID);
    compileShader(fragmentShaderFilePath, _fragmentShaderID);

}

void GLSLProgram::linkShaders()
{
    //Attach our shaders to our program
    glAttachShader(_programID, _vertexShaderID);
    glAttachShader(_programID, _fragmentShaderID);

    //Link our program
    glLinkProgram(_programID);

    //Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
    if(isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

        //The maxLength includes the NULL character
        std::vector<char> errorLog(maxLength);
        glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

        //We don't need the program anymore.
        glDeleteProgram(_programID);
        //Don't leak shaders either.
        glDeleteShader(_vertexShaderID);
        glDeleteShader(_fragmentShaderID);

        //Use the errorLog as you see fit.
        std::printf("%s\n", &errorLog[0]);
        fatalError("Shaders failed to link!");
    }

    //Always detach shaders after a successful link.
    glDetachShader(_programID, _vertexShaderID);
    glDetachShader(_programID, _fragmentShaderID);
    glDeleteShader(_vertexShaderID);
    glDeleteShader(_fragmentShaderID);
}

void GLSLProgram::addAttribute(const std::string& attributeName)
{
    glBindAttribLocation(_programID, _numberOfAttributes++, attributeName.c_str());
}

void GLSLProgram::use()
{
    glUseProgram(_programID);

    for(int i = 0; i < _numberOfAttributes; i++)
    {
        glEnableVertexAttribArray(i);
    }
}

void GLSLProgram::unuse()
{
    glUseProgram(0);

    for(int i = 0; i < _numberOfAttributes; i++)
    {
        glDisableVertexAttribArray(i);
    }
}
