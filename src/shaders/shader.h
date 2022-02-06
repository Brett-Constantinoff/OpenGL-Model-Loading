#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct shaderSource{
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader{
    public:
        int ID;
        Shader(const std::string &filepath);
        void use(void);
        void setMat4(const std::string &name, const glm::mat4 &matrix);
        void setVec3(const std::string &name, const glm::vec3 &color);
        void setFloat(const std::string &name, const float &value);
        void setInt(const std::string &name, const int &value);
    private:
        shaderSource parseShader(const std::string &filePath);
        unsigned int compileShader(const std::string &source, unsigned int type); 
    
};

#endif