#include "Model.h"

Model::Model(std::string path, std::string name){
    mName = name;
    mTransforms = {
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        0.0f,
        1.0f
    };
    stbi_set_flip_vertically_on_load(true);
    loadModel(path);
    stbi_set_flip_vertically_on_load(false);
}

void Model::drawModel( Shader* shader ){
    //draw all the models meshes
    for(uint32_t i = 0; i < mMeshes.size(); i++){
        mMeshes[i].drawMesh(shader, mTransforms, mWireFrame);
    }
}

std::string Model::getName( void ){
    return mName;
}

Transforms Model::getTransforms(void){
    return mTransforms;
}

void Model::scale(glm::vec3 scale, float scaleFactor){
    mTransforms.mScale = scale;
    mTransforms.mScaleFactor = scaleFactor;
}

void Model::translate(glm::vec3 translation){
    mTransforms.mTranslation = translation;
}

void Model::rotate(float angle, glm::vec3 rotation){
    mTransforms.mAngle = angle;
    mTransforms.mRotation = rotation;
}

bool Model::getWireFrameMode( void ){
    return mWireFrame;
}

void Model::setWireFrameMode( bool mode ){
    mWireFrame = mode;
}

/*
IMPLEMENTATION DETAILS FOR MODEL LOADING
*/

void Model::loadModel(std::string path){
    //create an interface with assimp
    Assimp::Importer importer;

    //all the object data is loaded into the scene object
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    //check if everything loaded correctly
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    //get the directory of the model file, used for textures later
    mDirectory = path.substr(0, path.find_last_of('/'));

    //recursviley process nodes
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene){
    //process the all the meshes in the node
    for(uint32_t i = 0; i < node->mNumMeshes; i++){
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]]; 
        mMeshes.push_back(processMesh(mesh, scene));			
    }
    //move on to the nodes children
    for(uint32_t i = 0; i < node->mNumChildren; i++){
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene){
    //data per mesh
    std::vector<VertexData> vertices;
    std::vector<unsigned int> indices;
    std::vector<TextureData> textures;
  
    for(uint32_t i = 0; i < mesh->mNumVertices; i++){
        VertexData vd;

        //positions
        vd.mPosition = {
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        };

        //normals
        if (mesh->HasNormals())
        {
           vd.mNormal = {
               mesh->mNormals[i].x,
               mesh->mNormals[i].y,
               mesh->mNormals[i].z
           };
        }
        // texture coordinates
        if(mesh->mTextureCoords[0])
        {
            vd.mUv = {
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
            };
        }
        //mesh has no texture, set the uv's to 0
        else{
            vd.mUv = {
                0.0f, 
                0.0f
            };
        }
        //add the new verted data to the vector of vertices
        vertices.push_back(vd);
    }

    //load all the indices in the mesh
    for(uint32_t i = 0; i < mesh->mNumFaces; i++){
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);        
    }

    
    //get materials for the mesh
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    aiColor4D diffuse;
    aiColor4D ambient;
    aiColor4D specular;

    MaterialData materials;

    //see if the model has a diffuse material
    if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse)){
        materials.mDiffuse = glm::vec3(diffuse.r, diffuse.g, diffuse.g);
    }
    else{
        materials.mDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    }

    //see if the object has a ambient material
    if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambient)){
        materials.mAmbient = glm::vec3(ambient.r, ambient.g, ambient.g);
    }
    else{
        materials.mAmbient = glm::vec3(0.1f, 0.1f, 0.1f);
    }

    //see if the object has specular material
    if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specular)){
        materials.mSpecular = glm::vec3(specular.r, specular.g, specular.g);
    }
    else{
        materials.mSpecular = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    //get the textures and save them using the desired naming convention
    //diffuse
    std::vector<TextureData> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    //specular
    std::vector<TextureData> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    
    
    //return newley created mesh
    return Mesh(vertices, indices, textures, materials);
}

std::vector<TextureData> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName){
    std::vector<TextureData> textures;
    
    for(uint32_t i = 0; i < mat->GetTextureCount(type); i++){
        aiString str;
        mat->GetTexture(type, i, &str);
        bool alreadyLoaded = false;
        
        for(uint32_t j = 0; j < mLoadedTextures.size(); j++){
            if( mLoadedTextures[j].mPath.compare(str.C_Str()) == 0){
                textures.push_back(mLoadedTextures[j]);
                alreadyLoaded = true;
                break;
            }
        }

        if(!alreadyLoaded){
            TextureData td;
            td.mId = Utils::loadTexture(mDirectory + '/' + str.C_Str());
            td.mType = typeName;
            td.mPath = str.C_Str();
            textures.push_back(td);
            mLoadedTextures.push_back(td);
        }
    }

    return textures;
}