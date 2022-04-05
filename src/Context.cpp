#include "Context.h"
#include <iostream>


void Context::start( void ){
    init();
    run();
    destroy();
}

void Context::init( void ){
    initContext();
    initImGui();
}

void Context::destroy( void ){
    destroyRes();
    destroyWindow();
    destroyImGui();
}

void Context::initContext( ){
     /* INIT GLFW */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    /* WINDOW INIT */
    this->mID = glfwCreateWindow(this->mWidth, this->mHeight, "Hello World", NULL, NULL);
    if(!mID){
        std::cerr << "Error creating OpenGL window" << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(mID);
    glViewport(0, 0, mWidth, mHeight);

    /* GLEW INIT */
    glewExperimental = true;
    if(glewInit() != GLEW_OK){
        std::cerr << "ERROR INITIALIZING GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }

    //renders 3D vertices properly
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
}

void Context::initImGui( void ){
      /* IMGUI INIT */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io; //sets up input / output

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(this->mID, true);
    ImGui_ImplOpenGL3_Init("#version 150");
}

void Context::run( void ){
    onStart();
    while(!glfwWindowShouldClose(this->mID)){
        onUpdate();
        onRender();
    }
}

void Context::destroyImGui( void ){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Context::destroyWindow( void ){
    glfwDestroyWindow(this->mID);
    glfwTerminate();
}

void Context::destroyRes( void ){
    for(auto vao: this->mVaos){
        glDeleteVertexArrays(1, &vao);
    }
    for(auto vbo: this->mVbos){
        glDeleteBuffers(1, &vbo);
    }
    for(auto ibo: this->mIbos){
        glDeleteBuffers(1, &ibo);
    }
    for(auto tbo: this->mTbos){
        glDeleteTextures(1, &tbo);
    }
    for(auto program: this->mPrograms){
        glDeleteProgram(program);
    }
}

GLFWwindow** Context::getID( void ){
    return &mID;
}

const glm::mat4* Context::getPersepctiveView( void ){
    return &mPerspective; 
}