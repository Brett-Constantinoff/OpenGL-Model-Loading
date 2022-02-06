#include "scene.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Scene::add(SceneObject object){
    this->objects.push_back(object);
};

std::vector<SceneObject> Scene::getObjects(void){
    return this->objects;
};

void Scene::setView(Window *win, Camera *cam){
     this->projection = glm::perspective(glm::radians(45.0f), (float)(*win).height/ (float)(*win).width, 1.0f, 100.0f); //creates perspective viewing
     this->view = glm::lookAt(cam->position, cam->position + cam->front, cam->up);
};

void Scene::deleteScene(void){
    for(SceneObject object : this->objects){
        object.deleteRes();
    }
};

void Scene::setUp(void){

};

void Scene::render(Shader* shader){

};