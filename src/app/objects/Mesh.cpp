#include "Mesh.h"

Mesh::Mesh(std::vector<VertexData> vertices, std::vector<uint32_t> indices, std::vector<TextureData> textures, MaterialData materials){
    mVertices = vertices;
    mIndices = indices;
    mTextures = textures;
    mMaterials = materials;
    initMesh();
}

void Mesh::initMesh( void ){
    //setup buffers
    mVao = Utils::genVertexArray();
    mVbo = Utils::genBuffer();
    mIbo = Utils::genBuffer();
    
    glBindVertexArray(mVao);

    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(VertexData), &mVertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(uint32_t),&mIndices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);	
    //offsetof calculates the offset from the start of the struct to the start of the second argument in bytes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, mNormal));
    // vertex texture coords
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, mUv));

    glBindVertexArray(0);
}

void Mesh::drawMesh( Shader* shader, Transforms transforms, bool wireFrame){
    uint32_t diffuseNr = 1;
    uint32_t specularNr = 1;
    
    shader->setInt("uTextures", mTextures.size());

    
    for(uint32_t i = 0; i < mTextures.size(); i++){
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = mTextures[i].mType;
        if(name == "texture_diffuse"){
            number = std::to_string(diffuseNr++);
           
        }
        else if(name == "texture_specular")
            number = std::to_string(specularNr++);

        shader->setInt((name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, mTextures[i].mId);
    }
    

    shader->setVec3("uDiffuse", mMaterials.mDiffuse);
    shader->setVec3("uAmbient", mMaterials.mAmbient);
    shader->setVec3("uSpecular", mMaterials.mSpecular);
    

    // render the loaded model
    glm::mat4 transform = glm::mat4(1.0f);

    transform = glm::translate(transform, transforms.mTranslation) *
                glm::rotate(transform, transforms.mAngle, transforms.mRotation) *
                glm::scale(transform, transforms.mScale * transforms.mScaleFactor);

    shader->setMat4("uTransform", transform);

    glm::mat4 normal = glm::mat4(1.0f);
    normal = glm::transpose(transform);
    normal = glm::inverse(normal);

    shader->setMat4("uNormalMatrix", normal);

    //draw mesh
    //draw in wire frame mode
    if(wireFrame){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else{
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    glBindVertexArray(mVao);
    glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

