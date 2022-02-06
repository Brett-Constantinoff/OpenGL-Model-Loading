#include "SceneObject.h"
#include "../../libraries/imageLoading/stb_image.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void SceneObject::init(void){
    this->genVertexArray();
    this->bindVertexArray();

    //set buffers
    this->genBuffer(&this->vertexPosBuffer);
    this->bindBuffer(this->vertexPosBuffer);
    this->setBufferData(this->vertexPositions.size(), this->vertexPositions);
    
    this->genBuffer(&this->indexBuffer);
    this->bindIndexBuffer(this->indexBuffer);
    this->setIndexBufferData(this->triangles.size(), this->triangles);

    this->setTexture();

    //set vertex positions
    this->setAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    this->enableAttribPointer(0);

    //set normals
    this->setAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    this->enableAttribPointer(1);

    //set uv coordinates
    this->setAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    this->enableAttribPointer(2);
};

void SceneObject::draw(void){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->textBuffer);
    this->bindVertexArray();
    glDrawElements(GL_TRIANGLES, this->triangles.size(), GL_UNSIGNED_INT, 0);
};

void SceneObject::move(float x, float y, float z){
    this->model = glm::translate(this->model, glm::vec3(x, y, z));
};

void SceneObject::updateNormalMat(void){
    this->normalMat = glm::transpose(this->model);
    this->normalMat = glm::inverse(this->normalMat);
};

void SceneObject::genVertexArray(void){
    glGenVertexArrays(1, &this->vao);
};

void SceneObject::bindVertexArray(void){
    glBindVertexArray(this->vao);
};

void SceneObject::genBuffer(unsigned int *buffer){
    glGenBuffers(1, buffer);
};

void SceneObject::bindBuffer(unsigned int buffer){
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
};

void SceneObject::bindIndexBuffer(unsigned int buffer){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
};

void SceneObject::setBufferData(size_t size, std::vector<float> data){
    float positions[size];
    std::copy(data.begin(), data.end(), positions);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
};

void SceneObject::setIndexBufferData(size_t size, std::vector<int> data){
    int indices[size];
    std::copy(data.begin(), data.end(), indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
};

void SceneObject::setAttribPointer(unsigned int index, int size, int type, bool normalized, int stride, const void* offset){
    glVertexAttribPointer(index, size, type, normalized, stride, offset);
};

void SceneObject::enableAttribPointer(unsigned int i){
    glEnableVertexAttribArray(i);
};

void SceneObject::setTexture(void){
    glGenTextures(1, &this->textBuffer);
    glBindTexture(GL_TEXTURE_2D, this->textBuffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(this->texture, &width, &height, &nrChannels, 0);
    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout << "Texture loading failed" << std::endl;
    }
    stbi_image_free(data);
};

void SceneObject::deleteRes(void){
    glDeleteVertexArrays(1, &this->vao);
    glDeleteBuffers(1, &this->vertexPosBuffer);
}