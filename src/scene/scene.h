#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../objects/objects.h"
#include "../objects/SceneObject.h"
#include "../window/window.h"
#include "../camera/camera.h"
#include "../shaders/shader.h"

#define OBJECTS 10


class Scene{
    private:
        std::vector<SceneObject> objects;
    
    public:
        glm::mat4 projection;
        glm::mat4 view;
        void add(SceneObject shape);
        void render(Shader* shader);
        void setView(Window *win, Camera *cam);
        void deleteScene(void);
        void setUp(void);
        std::vector<SceneObject> getObjects(void);
};

#endif