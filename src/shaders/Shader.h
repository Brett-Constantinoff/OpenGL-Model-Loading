#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm/glm.hpp>

struct shaderSource{
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader{
    public:
        Shader(const std::string &filepath);
        unsigned int getId( void );
        void setVec3(const char* location, glm::vec3 uniform);
        void setVec4(const char* location, glm::vec4 uniform);
        void setMat4(const char* location, glm::mat4 uniform);
        void setInt(const char* location, int uniform);
        void use( void );
        
    private:
        int mID;
        shaderSource parseShader(const std::string &filePath);
        unsigned int compileShader(const std::string &source, unsigned int type); 
        
};



#endif