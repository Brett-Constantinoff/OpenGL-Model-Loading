#include "Context.h"
#include <iostream>

Context::~Context(){}

//main method for starting your application
void Context::start( void ){
    init();
    run();
    destroy();
}

//initializes the current context and imgui
void Context::init( void ){
    initContext();
    initImGui();
}

//destroys all resources allocated for application
void Context::destroy( void ){
    destroyRes();
    destroyWindow();
    destroyImGui();
}

//inits glfw and glew and sets up opengl initial state
void Context::initContext( ){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    this->mID = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NAME, NULL, NULL);
    if(!mID){
        std::cerr << "Error creating OpenGL window" << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(mID);
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    glewExperimental = true;
    if(glewInit() != GLEW_OK){
        std::cerr << "ERROR INITIALIZING GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
}

//inits imgui with dark mode 
void Context::initImGui( void ){
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io; 
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(this->mID, true);
    ImGui_ImplOpenGL3_Init("#version 150");
}

//starts frame, clears the colour / depth buffer and starts a new imgui frame if neccessary
void Context::startFrame(){
    glClearColor(SCREEN_COLOUR.r, SCREEN_COLOUR.g, SCREEN_COLOUR.b, SCREEN_COLOUR.a);
    if(is2Dapplication){
        glClear(GL_COLOR_BUFFER_BIT);
    }
    else{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    if(isEnableImGui){
        //setup imgui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }
}

//ends frame by swapping buffers and pollion IO events
void Context::endFrame(){
    glfwSwapBuffers(*getID());
    glfwPollEvents();
}

//main application loop
void Context::run( void ){
    onStart();
    while(!glfwWindowShouldClose(this->mID)){
        startFrame();
        onUpdate();
        onRender();
        if(isEnableImGui){
            renderImGui();
        }
        endFrame();
    }
}

//renderes whatever imgui code you write
void Context::renderImGui( void ){
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

//destroys imgui resources
void Context::destroyImGui( void ){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

//quits glfw and destroys contex ID
void Context::destroyWindow( void ){
    glfwDestroyWindow(this->mID);
    glfwTerminate();
}

//destroys all app resources
void Context::destroyRes( void ){
    Utils::deleteResources();
}

//returns the context ID
GLFWwindow** Context::getID( void ){
    return &mID;
}

//disbales depth testing
void Context::disableDepthTesting( void ){
    glDisable(GL_DEPTH_TEST);
}

//enables depth testing
void Context::enableDepthTesting( void ){
    is2Dapplication = false;
    glEnable(GL_DEPTH_TEST);
}

//disables blending
void Context::disableBlending( void ){
    glDisable(GL_BLEND);
}

//enables blending
void Context::enableBlending( void ){
    glEnable(GL_BLEND);
}

//disable face culling
void Context::disableCullFace( void ){
    glDisable(GL_CULL_FACE);
}

//enables face culling
void Context::enableCullFace( void ){
    glEnable(GL_CULL_FACE);
}

//sets a blend function
void Context::blendFunc(uint32_t sFactor, uint32_t dFactor){
    glBlendFunc(sFactor, dFactor);
}

//disables imgui
void Context::disableImGui( void ){
    isEnableImGui = false;
}

//enables imgui
void Context::enableImGui( void ){
    isEnableImGui = true;
}