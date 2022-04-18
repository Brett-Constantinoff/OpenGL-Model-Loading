#ifndef SKYBOX_H
#define SKYBOX_H
#include "../../shaders/Shader.h"
#include "../../utils/Utils.h"
#include <vector>
#include <string>

class Skybox{
    public:
        Skybox( std::vector<std::string> files );
        void draw( Shader* shader );
    private:
        void init( void );
    private:
        uint32_t mVao;
        uint32_t mTextureID;
        std::vector<std::string> mFiles;
};

#endif