#include "App.h"

//runs once on startup
void App::onStart(){
    /*
    APPLICATION SETTINGS
    */
    enableDepthTesting();
    enableImGui();
    //for fonts
    enableBlending();
    blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /*
    INITIALIZE ANY APP UTILS AND ATTRIBUTES
    */

    //utility attributes
    mSoundEngine = Utils::createSoundEngine();
    mTextRenderer = new TextRenderer(Utils::createShader("src/shaders/glslShaders/textShader.txt"));
    mTextRenderer->loadFont("src/res/fonts/OCRAEXT.TTF", 24);

    //skybox
    mSkyboxShader = Utils::createShader("src/shaders/glslShaders/skybox.txt");
    mSkybox = new Skybox({
        "src/res/skybox/right.jpg",
        "src/res/skybox/left.jpg",
        "src/res/skybox/top.jpg",
        "src/res/skybox/bottom.jpg",
        "src/res/skybox/front.jpg",
        "src/res/skybox/back.jpg",
    });

    //models
    mModelShader = Utils::createShader("src/shaders/glslShaders/mainShader.txt");
    mModels.push_back(new Model("src/res/models/backpack/backpack.obj", "backpack"));
    mModels.push_back(new Model("src/res/models/robot/LowPoly_Futuristic_Prometheus_Alien_Robot.obj", "robot"));
    mModels.push_back(new Model("src/res/models/head/Anna_OBJ.obj", "head"));
    mModels.push_back(new Model("src/res/models/car/Vazz.obj", "car"));
    
    for(auto m : mModels){
        mModelNames.push_back(m->getName());
    }

    //initial model transform
    mModelTransform = {
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        0.0f, 
        1.0f
    }; 

    //light
    mLight = new Light({
        {0.0f, 100.0f, 0.0f},
        {1.0f, 1.0f, 1.0f},
        1.5f, 
        5.0f
    });
}

//runs everyframe
void App::onUpdate(){
    //setup time
    mCurrFrame = glfwGetTime();
    mDeltaTime = mCurrFrame - mLastFrame;
    mLastFrame = mCurrFrame;

    //set wire frame mode for models
    for(auto m : mModels){
        m->setWireFrameMode(mIsWireFrame);
    }

    //projection matrix 
    mProjection = glm::perspective(
        glm::radians(Utils::mCamera->mZoom),
        static_cast<float>(SCREEN_WIDTH)/ static_cast<float>(SCREEN_HEIGHT),
        0.1f,
        500.0f
    );

    //camera
    Utils::mCamera->move(getID(), mDeltaTime);

    //configure imgui with what you want to draw
    {
        ImGui::Begin("Main Window");

        {   
            //drop down menu for models
            if (ImGui::BeginListBox("models")){
                for (int i = 0; i < mModelNames.size(); i++){
                    mIsSelected = (mSelectedItem == i); //set the current selction
                    if (ImGui::Selectable(mModelNames[i].c_str(), mIsSelected)){
                        mSelectedItem = i;
                    }
                }
                ImGui::EndListBox();
            }
        }
        {
            //model transforms
            ImGui::SliderFloat3("Model Size", &mModelTransform.mScale[0], 0.0f, 10.0f);
            ImGui::SliderFloat("Model Scale Factor", &mModelTransform.mScaleFactor, 0.0f, 2.0f);
            ImGui::SliderFloat3("Model Position", &mModelTransform.mTranslation[0], -10.0f, 10.0f);
            ImGui::SliderAngle("Rotation Angle", &mModelTransform.mAngle, -360.0f, 360.0f);
            ImGui::SliderFloat3("Model Rotatin", &mModelTransform.mRotation[0], 0.0f, 1.0f);
            ImGui::Checkbox("Enable wire frame", &mIsWireFrame);
            mModelReset = ImGui::Button("Reset Model");
        }
        ImGui::End();
    }

    //update model
    if(mModelReset){
        //reset model transforms
        mModelTransform = {
            {1.0f, 1.0f, 1.0f},
            {1.0f, 1.0f, 1.0f},
            {1.0f, 1.0f, 1.0f},
            0.0f,
            1.0f
        };
    }
    //update model transforms
    for(auto m : mModels){
        m->scale(mModelTransform.mScale, mModelTransform.mScaleFactor);
        m->translate(mModelTransform.mTranslation);
        m->rotate(mModelTransform.mAngle, mModelTransform.mRotation);
    }
}

//render calls go here
void App::onRender(){

    //render models
    mModelShader->use();
    glm::mat4 view = *Utils::mCamera->getView();
    mModelShader->setMat4("uProjection", mProjection);
    mModelShader->setMat4("uView", view);
    mModelShader->setVec3("uCameraPos", *Utils::mCamera->getPos());
    mModelShader->setVec3("uLightPos", mLight->mPos);
    mModelShader->setVec3("uLightColour", mLight->mColour);
    mModelShader->setFloat("uLightStr",mLight->mStrength);
    mModelShader->setFloat("uN",mLight->mN);
    mModels[mSelectedItem]->drawModel( mModelShader );

    //render skybox
    mSkyboxShader->use();
    setDepthFunc(GL_LEQUAL);
    mSkyboxShader->setMat4("uProjection", mProjection);
    glm::mat4 skyboxView = glm::mat4(glm::mat3(*Utils::mCamera->getView()));
    mSkyboxShader->setMat4("uView", skyboxView);
    mSkybox->draw(mSkyboxShader);
    setDepthFunc(GL_LESS);

    //render text
    std::stringstream camera, frameRate;
    camera << "Camera Position: " << Utils::mCamera->getPos()->x << " " << Utils::mCamera->getPos()->y << " " << Utils::mCamera->getPos()->z;
    frameRate << ImGui::GetIO().Framerate << " fps";
    mTextRenderer->render(camera.str(), {0.0f, 5.0f}, 0.5f, {0.0f, 1.0f, 0.0f}, false);
    mTextRenderer->render(frameRate.str(), {0.0f, 15.0f}, 0.5f, {0.0f, 1.0f, 0.0f}, false);
}


//any memory allocated for the app needs to be deleted
App::~App(){
    delete mTextRenderer;
    delete mSoundEngine;
    delete mSkybox;
    delete mLight;
    mModels.clear();
}