#include "MatrixManager.h"

#include <cstdio>
MatrixManager::MatrixManager()
{
    currentMatrix = glm::mat4(1.0);
    matrixStack = &modelStack;
    modelUniform = -1;
    viewUniform = -1;
    projectionUniform = -1;
    glm::mat4 mat(1.0f);
    viewStack.push(mat);
    projectionStack.push(mat);
}

MatrixManager::~MatrixManager()
{
    //dtor
}

void MatrixManager::setMode(int matrixMode)
{
    pushMatrix();
    if(matrixMode == matrixModel)
        matrixStack = &modelStack;
    if(matrixMode == matrixView)
        matrixStack = &viewStack;
    if(matrixMode == matrixProjection)
        matrixStack = &projectionStack;
    popMatrix();
}

void MatrixManager::setUniforms(GLint _modelUniform, GLint _viewUniform, GLint _projectionUniform)
{
    modelUniform = _modelUniform;
    viewUniform = _viewUniform;
    projectionUniform = _projectionUniform;

    setMatrixs();
    GLenum error = glGetError();
    if(error !=GL_NO_ERROR)
    {
        printf("%s\n",gluErrorString(error));
        printf("MatrixManager: Invalid Uniform or shader program!\n");
    }
}

void MatrixManager::pushMatrix()
{
    matrixStack->push(currentMatrix);
}

void MatrixManager::popMatrix()
{
    currentMatrix = matrixStack->top();
    matrixStack->pop();
}

void MatrixManager::translate(glm::vec3 translation)
{
    currentMatrix = glm::translate(currentMatrix,translation);
}

void MatrixManager::rotate(float angle, glm::vec3 axis)
{
   currentMatrix = glm::rotate(currentMatrix,angle,axis);
}

void MatrixManager::scale(glm::vec3 factors)
{
    currentMatrix = glm::scale(currentMatrix,factors);
}

void MatrixManager::loadIdentity()
{
    currentMatrix = glm::mat4(1.0);
}

void MatrixManager::perspective(float fovy, float aspect, float near, float far)
{
    currentMatrix = glm::perspective(fovy,aspect,near,far);
}

void MatrixManager::lookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
    currentMatrix = glm::lookAt(eye,center,up);
}

void MatrixManager::setMatrixs(GLint _modelUniform, GLint _viewUniform, GLint _projectionUniform)
{
    pushMatrix();
    glm::mat4 mm = modelStack.top();
    glm::mat4 vm = viewStack.top();
    glm::mat4 pm = projectionStack.top();

    if(modelUniform != -1) glUniformMatrix4fv(_modelUniform, 1, GL_FALSE, glm::value_ptr(mm));
    if(viewUniform != -1) glUniformMatrix4fv(_viewUniform, 1, GL_FALSE, glm::value_ptr(vm));
    if(projectionUniform != -1) glUniformMatrix4fv(_projectionUniform, 1, GL_FALSE, glm::value_ptr(pm));

    popMatrix();
}

void MatrixManager::setMatrixs()
{
    setMatrixs(modelUniform,viewUniform,projectionUniform);
}
