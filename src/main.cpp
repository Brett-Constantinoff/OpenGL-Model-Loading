#include "window/window.h"
#include "shaders/shader.h"
#include "objects/objects.h"
#include "camera/camera.h"
#include "scene/scene.h"

int main(){
    
   Window window(800, 600, "Hello World", glm::vec3(0.1f, 0.1f, 0.1f));
   window.enable3d();

   Shader shader("shaders/shader.shader");
   Scene scene;
   
   scene.setUp(); //add objects
   
   Camera camera(glm::vec3(0.0f, 0.0f ,3.0f), glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
   Light sceneLight{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 5.0f, 0.0f), 2.0f, 2.0f};
   
   while(window.isOpen()){
       camera.move(&window.win);
       scene.setView(&window, &camera);
       window.clearColor(window.color.r, window.color.g, window.color.b, 1.0f);
       window.clearBuffers();
       
       //starts gui frame, all gui calls need to happen after this and before the end call
       window.enableGui();
       //main demo window, each gui window can(not neccessary) have its own scope
       {
        window.startGuiElement("Main Window");
        window.setGuiColor("BackGround Color", &window.color);
        window.displayGuiFloat3("Camera Position", camera.position.x, camera.position.y, camera.position.z);
       }
       //stops gui frame
       window.stopGuiElement();

       shader.use();
       shader.setFloat("lightStr", sceneLight.strength);
       shader.setFloat("n", sceneLight.n);
       shader.setVec3("cameraPosition", camera.position);
       shader.setVec3("ambientVal", sceneLight.ambient);
       shader.setVec3("specularVal", sceneLight.specular);
       shader.setVec3("lightCol", sceneLight.color);
       shader.setVec3("lightPos", sceneLight.position);
       shader.setMat4("projection", scene.projection);
       shader.setMat4("view", scene.view);

       scene.render(&shader); //render objects
       window.renderGui();
       window.swapBuffers();
       window.pollEvents();
   }
   scene.deleteScene();
   window.quitGui();
   window.quit();
}