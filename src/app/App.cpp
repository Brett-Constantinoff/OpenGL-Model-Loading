#include "App.h"

//runs once on startup
void App::onStart(){
    /*
    APPLICATION SETTINGS
    */


    /*
    INITIALIZE ANY APP UTILS AND ATTRIBUTES
    */

    //utility attributes
    mSoundEngine = Utils::createSoundEngine();
    mTextRenderer = new TextRenderer();
    mTextRenderer->loadFont("src/res/fonts/OCRAEXT.TTF", 24);

}

//runs everyframe
void App::onUpdate(){
    //setup time
    mCurrFrame = glfwGetTime();
    mDeltaTime = mCurrFrame - mLastFrame;
    mLastFrame = mCurrFrame;
    

}

//render calls go here
void App::onRender(){


}


//any memory allocated for the app needs to be deleted
App::~App(){
    delete mTextRenderer;
    delete mSoundEngine;
}