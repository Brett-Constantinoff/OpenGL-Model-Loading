#ifndef UTILS_H
#define UTILS_H

#include "../shaders/Shader.h"
#include "Camera.h"
#include <irrKlang/include/irrKlang.h>

//change these for you application
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_NAME "Model Loading"
#define SCREEN_COLOUR glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)

class Utils{

    public:
        static Shader* createShader(std::string fileName);
        static uint32_t genTexture();
        static uint32_t genBuffer( void ); 
        static uint32_t genVertexArray( void );
        static uint32_t loadCubeMap( std::vector<std::string> mapFiles );
        static uint32_t loadTexture(std::string fileName);
        static irrklang::ISoundEngine* createSoundEngine( void );
        static Camera* getCamera( void );

        template<class T>
        static T random(T low, T high){
            return low + static_cast <T> (rand()) /( static_cast <T> (RAND_MAX/(high -  low)));
        }

        static void deleteResources( void );

    public:
        static Camera* mCamera;

    private:
  
        static std::vector<uint32_t> mVaos; //vertex arrays
        static std::vector<uint32_t> mVbos; //vertex buffers
        static std::vector<uint32_t> mTbos; //texture buffers
        static std::vector<uint32_t> mPrograms; //shader programs
        static std::vector<Shader*> mShaders; //shader objects
};


#endif