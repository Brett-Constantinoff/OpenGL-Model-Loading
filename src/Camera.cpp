#include "Camera.h"

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up){
    this->mPosition = position;
    this->mFront = front;
    this->mUp = up;
};

void Camera::move(GLFWwindow **win, float dt){


    this->mFront.x = cos(glm::radians(this->mYaw)) * cos(glm::radians(this->mPitch));
    this->mFront.y = sin(glm::radians(this->mPitch));
    this->mFront.z = sin(glm::radians(this->mYaw)) * cos(glm::radians(this->mPitch));
    this->mFront = glm::normalize(this->mFront);

    const float cameraSpeed = 3.0f * dt;

    if(glfwGetKey(*win, GLFW_KEY_W) == GLFW_PRESS){
        this->mPosition += cameraSpeed * this->mFront;
    }
    if(glfwGetKey(*win, GLFW_KEY_S) == GLFW_PRESS){
        this->mPosition -= cameraSpeed * this->mFront;
    }
    if(glfwGetKey(*win, GLFW_KEY_A) == GLFW_PRESS){
        this->mPosition -= glm::normalize(glm::cross(this->mFront, this->mUp)) * cameraSpeed;
    }
    if(glfwGetKey(*win, GLFW_KEY_D) == GLFW_PRESS){
        this->mPosition += glm::normalize(glm::cross(this->mFront, this->mUp)) * cameraSpeed;
    }
    if(glfwGetKey(*win, GLFW_KEY_RIGHT) == GLFW_PRESS){
         this->mYaw += 2.0f;
    }
    if(glfwGetKey(*win, GLFW_KEY_LEFT) == GLFW_PRESS){
         this->mYaw -= 2.0f;
    }
    if(glfwGetKey(*win, GLFW_KEY_UP) == GLFW_PRESS){
         this->mPitch += 2.0f;
    }
    if(glfwGetKey(*win, GLFW_KEY_DOWN) == GLFW_PRESS){
         this->mPitch -= 2.0f;
    }
}

glm::mat4* Camera::getView(){
    mView = glm::lookAt(mPosition, mPosition + mFront, mUp);
    return &mView;
}