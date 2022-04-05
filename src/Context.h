#ifndef CONTEXT_H
#define CONTEXT_H

#define GL_SILENCE_DEPRECATION

#include "libs/imgui.h"
#include "libs/imgui_impl_glfw.h"
#include "libs/imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

class Context{
    protected:
        GLFWwindow* mID;
        
        //change these 3 attributes per project
        const int mWidth = 1280;
        const int mHeight = 720;
        const char* mName = "Hello World";

        const glm::vec4 mColour = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
        glm::mat4 mPerspective = glm::perspective(glm::radians(45.0f), (float)mWidth / (float)mHeight, 0.1f, 500.0f); 
        std::vector<unsigned int> mVaos; //vertex arrays
        std::vector<unsigned int> mVbos; //vertex buffers
        std::vector<unsigned int> mIbos; //index buffers
        std::vector<unsigned int> mTbos; //texture buffers
        std::vector<unsigned int> mPrograms; //shader programs

    public:
        void start();
        void init();
        virtual void onStart( void ) = 0;
        virtual void onUpdate( void ) = 0;
        virtual void onRender( void ) = 0;
        void run( void );
        void destroy( void );
        GLFWwindow** getID( void );
        const glm::mat4* getPersepctiveView( void );

    private:
        void destroyRes( void );
        void destroyImGui( void );
        void destroyWindow( void );
        void initContext( void );
        void initImGui( void );
};

#endif