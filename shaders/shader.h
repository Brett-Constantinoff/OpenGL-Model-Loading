#ifndef SHADER_H
#define SHADER_H

#include <string>

struct shaderSource{
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader{
    public:
        int ID;
        Shader(const std::string &filepath);
    private:
        shaderSource parseShader(const std::string &filePath);
        unsigned int compileShader(const std::string &source, unsigned int type); 
        
};



#endif