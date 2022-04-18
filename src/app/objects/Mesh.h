#ifndef MESH_H
#define MESH_H

#include "../../utils/Utils.h"
#include "../../shaders/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>
#include <iostream>

typedef struct {
    glm::vec3 mPosition; //position coord
    glm::vec3 mNormal;   //normal coord
    glm::vec2 mUv;       //texture coord
}VertexData;

typedef struct {
    uint32_t mId;        //texture id
    std::string mType;   //type of texture
    std::string mPath;   //path of the texture
}TextureData;

typedef struct{
    glm::vec3 mDiffuse;
    glm::vec3 mAmbient;
    glm::vec3 mSpecular;
}MaterialData;

typedef struct{
    glm::vec3 mTranslation;
    glm::vec3 mScale;
    glm::vec3 mRotation;
    float mAngle;
    float mScaleFactor;
}Transforms;


class Mesh{
    public:
        std::vector<VertexData> mVertices;
        std::vector<uint32_t> mIndices;
        std::vector<TextureData> mTextures;
        MaterialData mMaterials;
    
    public:
        Mesh(std::vector<VertexData> vertices, std::vector<uint32_t> indices, std::vector<TextureData> textures, MaterialData materials);
        void drawMesh( Shader* shader , Transforms transforms, bool wireFrame);

    private:
        uint32_t mVao, mVbo, mIbo;
        
    
    private:
        void initMesh( void );
};

#endif