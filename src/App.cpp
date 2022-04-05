#include "App.h"
#include <iostream>

//runs once on startup
void App::onStart(){
    //initialize any app attributes
    mShader = new Shader("src/shaders/mainShader.txt");
    mPrograms.push_back(mShader->getId()); //add to programs, for deallocation later
    
}

//runs everyframe
void App::onUpdate(){

    
}

//render calls go here
void App::onRender(){
    //setup time
    mCurrFrame = glfwGetTime();
    mDeltaTime = mCurrFrame - mLastFrame;
    mLastFrame = mCurrFrame;

    glClearColor(mColour.r, mColour.g, mColour.b, mColour.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //setup imgui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //render geometry
    glUseProgram(mShader->getId());
    glBindVertexArray(mAppVao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //render imgui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    //swap front and back buffers and poll IO events(buttons presses, mouse movement etc)
    glfwSwapBuffers(*getID());
    glfwPollEvents();
}


//any memory allocated for the app needs to be deleted
App::~App(){
    delete mShader;
}