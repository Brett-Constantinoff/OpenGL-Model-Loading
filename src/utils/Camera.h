#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Camera{
    private:
        glm::mat4 mView;
        glm::vec3 mPosition;
        glm::vec3 mFront;
        glm::vec3 mUp;
        float mYaw = -90.0f;
        float mPitch = 0.0f;
    public:
        Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up);
        void move(GLFWwindow **win, float dt);
        glm::mat4* getView( void );
        glm::vec3* getPos( void );
    public:
        float mZoom = 45.0f;

};


#endif