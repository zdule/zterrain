#include "ShaderUtils.h"
GLuint loadShaderProgram(const char* vertexShaderPath,const char* fragmentShaderPath, ...)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLint testVal;
    GLuint program;

    if(loadShaderFile(vertexShaderPath, vertexShader) == false)
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        std::cout << "The shader at " << vertexShaderPath<< " could not be found.\n";
        return (GLuint)NULL;
    }
    if(loadShaderFile(fragmentShaderPath, fragmentShader) == false)
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        std::cout << "The shader at " << fragmentShaderPath<< " could not be found.\n";
        return (GLuint)NULL;
    }

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &testVal);
    if(testVal == GL_FALSE)
    {
        char infoLog[1024];
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
        std::cout << "The shader at " << vertexShaderPath << " failed to compile with the following error:\n"
        << infoLog << "\n";
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return (GLuint)NULL;
    }

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &testVal);
    if(testVal == GL_FALSE)
    {
        char infoLog[1024];
        glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
        std::cout << "The shader at " << fragmentShaderPath << " failed to compile with the following error:\n"
        << infoLog << "\n";
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return (GLuint)NULL;
    }

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    va_list attributeList;
    va_start(attributeList, fragmentShaderPath);

    int argNum = va_arg(attributeList, int);
    for(int i = 0; i < argNum; i++)
    {
        int index = va_arg(attributeList, int);
        char* szNextArg = va_arg(attributeList, char*);
        glBindAttribLocation(program, index, szNextArg);
    }
    va_end(attributeList);

    glLinkProgram(program);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGetProgramiv(program, GL_LINK_STATUS, &testVal);
    if(testVal == GL_FALSE)
    {
        char infoLog[1024];
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        std::cout << "The program " << program << "failed to link with the following error:\n"
        << infoLog << "\n";
        glDeleteProgram(program);
        return (GLuint)NULL;
    }
    return program;
}

bool loadShaderFile(const char* ShaderPath, GLuint shader)
{
    std::ifstream infile;
    infile.open (ShaderPath, std::ifstream::in);
    std::string str((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    const char* source = str.c_str();
    glShaderSource(shader, 1, &source, NULL);
    infile.close();
    return true;
}
