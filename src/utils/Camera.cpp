#include "Camera.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up){
    mPosition = position;
    mFront = front;
    mUp = up;
};

//moves the camera with WASD and arrow keys
void Camera::move(GLFWwindow **win, float dt){
    mFront.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    mFront.y = sin(glm::radians(mPitch));
    mFront.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    mFront = glm::normalize(mFront);

    const float cameraSpeed = 3.0f * dt;

    if (glfwGetKey(*win, GLFW_KEY_W) == GLFW_PRESS)
    {
        mPosition += cameraSpeed * mFront;
    }
    if (glfwGetKey(*win, GLFW_KEY_S) == GLFW_PRESS)
    {
        mPosition -= cameraSpeed * mFront;
    }
    if (glfwGetKey(*win, GLFW_KEY_A) == GLFW_PRESS)
    {
        mPosition -= glm::normalize(glm::cross(mFront, mUp)) * cameraSpeed;
    }
    if (glfwGetKey(*win, GLFW_KEY_D) == GLFW_PRESS)
    {
        mPosition += glm::normalize(glm::cross(mFront, mUp)) * cameraSpeed;
    }
    if (glfwGetKey(*win, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        mYaw += 2.0f;
    }
    if (glfwGetKey(*win, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        mYaw -= 2.0f;
    }
    if (glfwGetKey(*win, GLFW_KEY_UP) == GLFW_PRESS)
    {
        mPitch += 2.0f;
    }
    if (glfwGetKey(*win, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        mPitch -= 2.0f;
    }
}

//returns a current view matrix
glm::mat4 *Camera::getView(){
    mView = glm::lookAt(mPosition, mPosition + mFront, mUp);
    return &mView;
}