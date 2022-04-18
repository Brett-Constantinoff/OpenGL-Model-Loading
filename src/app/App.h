#ifndef APP_H
#define APP_H

#include "../utils/Context.h"
#include "../utils/Light.h"
#include "objects/Model.h"
#include "objects/Skybox.h"
#include "../utils/TextRenderer.h"
#include "../shaders/Shader.h"

class App : public Context{
    //define any attirbutes your app needs
    private:
        //utility attributes
        glm::mat4 mProjection;
        irrklang::ISoundEngine* mSoundEngine;
        TextRenderer* mTextRenderer;
        float mCurrFrame;
        float mDeltaTime;
        float mLastFrame = 0.0f;
        bool mIsWireFrame = false;
        bool mIsSelected;
        uint32_t mSelectedItem;
       
        //object attributes
        Shader* mModelShader;
        std::vector<std::string> mModelNames;
        std::vector<Model*> mModels;
        std::vector<Light*> mLights;
        Transforms mModelTransform;
        bool mModelReset;

        //skybox
        Shader* mSkyboxShader;
        Skybox* mSkybox;

        //light
        Light* mLight;
    
       
    //can add additional methods, but these 4 are all you really need
    public:
        virtual void onStart();
        virtual void onUpdate();
        virtual void onRender();
        ~App();
};
#endif