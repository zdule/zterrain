#ifndef MATRIXMANAGER_H
#define MATRIXMANAGER_H

#include <stack>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
enum {matrixModel,matrixView,matrixProjection};
class MatrixManager
{
    public:
        MatrixManager();
        virtual ~MatrixManager();
        void setMode(int matrixMode);
        void setUniforms(GLint _modelUniform, GLint _viewUniform, GLint _projectionUniform);
        void pushMatrix();
        void popMatrix();
        void rotate(float angle, glm::vec3 axis);
        void scale(glm::vec3 factors);
        void translate(glm::vec3 translation);
        void loadIdentity();
        void perspective(float fovy, float aspect, float near, float far);
        void lookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
        void setMatrixs();
        void setMatrixs(GLint _modelUniform, GLint _viewUniform, GLint _projectionUniform);
    protected:
    private:
        std::stack<glm::mat4> modelStack;
        std::stack<glm::mat4> viewStack;
        std::stack<glm::mat4> projectionStack;
        std::stack<glm::mat4>* matrixStack;
        glm::mat4 currentMatrix;
        GLint modelUniform;
        GLint viewUniform;
        GLint projectionUniform;

} ;

#endif // MATRIXMANAGER_H
