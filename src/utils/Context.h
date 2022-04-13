#ifndef CONTEXT_H
#define CONTEXT_H

#define GL_SILENCE_DEPRECATION

#include "../libs/imgui.h"
#include "../libs/imgui_impl_glfw.h"
#include "../libs/imgui_impl_opengl3.h"
#include "../utils/Utils.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Context{
    public:
        virtual ~Context() = 0;
        void start();
        void init();
        virtual void onStart( void ) = 0;
        virtual void onUpdate( void ) = 0;
        virtual void onRender( void ) = 0;
        void renderImGui( void );
        void run( void );
        void destroy( void );
        GLFWwindow** getID( void );
        void disableDepthTesting( void );
        void enableDepthTesting( void );
        void disableBlending( void );
        void enableBlending( void );
        void enableCullFace( void );
        void disableCullFace( void );
        void blendFunc( uint32_t sFactor, uint32_t dFactor );
        void enableImGui( void );
        void disableImGui( void );

    private:
        void startFrame( void );
        void endFrame( void );
        void destroyRes( void );
        void destroyImGui( void );
        void destroyWindow( void );
        void initContext( void );
        void initImGui( void );

    private:
        GLFWwindow* mID;
        bool is2Dapplication = true;
        bool isEnableImGui = true;
};

#endif