#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include "../../shaders/Shader.h"
#include "../../libs/stb_image.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <string>
#include <vector>


class Model 
{
    public:
        Model(std::string path, std::string name);
        void drawModel( Shader* shader );	
        Transforms getTransforms( void );
        std::string getName( void );
        void scale(glm::vec3 scale, float scaleFactor);
        void translate(glm::vec3 transform);
        void rotate(float angle, glm::vec3 rotation);
        bool getWireFrameMode( void );
        void setWireFrameMode( bool mode );

    private:
        std::string mName;
        std::vector<Mesh> mMeshes;
        std::vector<TextureData> mLoadedTextures;
        std::string mDirectory;
        Transforms mTransforms;
        bool mWireFrame = false;
    
    private:
        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<TextureData> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif