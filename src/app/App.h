#ifndef APP_H
#define APP_H

#include "../utils/Context.h"
#include "../utils/TextRenderer.h"
#include "../shaders/Shader.h"

class App : public Context{
    //define any attirbutes your app needs
    private:
        //utility attributes
        irrklang::ISoundEngine* mSoundEngine;
        TextRenderer* mTextRenderer;
        float mCurrFrame;
        float mDeltaTime;
        float mLastFrame = 0.0f;
       
        //object attributes
    

        //game attributes
    
       
    //can add additional methods, but these 4 are all you really need
    public:
        virtual void onStart();
        virtual void onUpdate();
        virtual void onRender();
        ~App();
};
#endif