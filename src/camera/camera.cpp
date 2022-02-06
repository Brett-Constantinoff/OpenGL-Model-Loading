#include "camera.h"

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up){
    this->position = position;
    this->front = front;
    this->up = up;
};

void Camera::move(GLFWwindow **win){

    float currentFrame = glfwGetTime();

    this->deltaTime = currentFrame - this->lastFrame;
    this->lastFrame = currentFrame; 

    this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->front.y = sin(glm::radians(this->pitch));
    this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->front = glm::normalize(this->front);

    const float cameraSpeed = 3.0f * this->deltaTime;

    if(glfwGetKey(*win, GLFW_KEY_W) == GLFW_PRESS){
        this->position += cameraSpeed * this->front;
    }
    if(glfwGetKey(*win, GLFW_KEY_S) == GLFW_PRESS){
        this->position -= cameraSpeed * this->front;
    }
    if(glfwGetKey(*win, GLFW_KEY_A) == GLFW_PRESS){
        this->position -= glm::normalize(glm::cross(this->front, this->up)) * cameraSpeed;
    }
    if(glfwGetKey(*win, GLFW_KEY_D) == GLFW_PRESS){
        this->position += glm::normalize(glm::cross(this->front, this->up)) * cameraSpeed;
    }
    if(glfwGetKey(*win, GLFW_KEY_RIGHT) == GLFW_PRESS){
         this->yaw += 2.0f;
    }
    if(glfwGetKey(*win, GLFW_KEY_LEFT) == GLFW_PRESS){
         this->yaw -= 2.0f;
    }
    if(glfwGetKey(*win, GLFW_KEY_UP) == GLFW_PRESS){
         this->pitch += 2.0f;
    }
    if(glfwGetKey(*win, GLFW_KEY_DOWN) == GLFW_PRESS){
         this->pitch -= 2.0f;
    }

}