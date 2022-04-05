#ifndef APP_H
#define APP_H

#include "Context.h"
#include "Shader.h"


class App : public Context{
    //define any attirbutes your app needs
    private:
        Shader* mShader;
        unsigned int mAppVao;
        float mCurrFrame;
        float mDeltaTime;
        float mLastFrame = 0.0f;

    //can add additional methods, but these 4 are all you really need
    public:
        virtual void onStart();
        virtual void onUpdate();
        virtual void onRender();
        ~App();

};


#endif