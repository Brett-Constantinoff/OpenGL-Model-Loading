#include "Shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(const std::string &filepath){
    mID = glCreateProgram(); //creates current shader program

    shaderSource source = Shader::parseShader(filepath);
    unsigned int vShader = Shader::compileShader(source.vertexSource, GL_VERTEX_SHADER); //compiles vertex source
    unsigned int fShader = Shader::compileShader(source.fragmentSource, GL_FRAGMENT_SHADER); //compiles fragment source

    //attaches shaders to program
    glAttachShader(mID, vShader);
    glAttachShader(mID, fShader);
    //links the shader program
    glLinkProgram(mID);
    //ensures successful linking
    glValidateProgram(mID);

    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

unsigned int Shader::getId( void ){
    return mID;
}

unsigned int Shader::compileShader(const std::string &source, unsigned int type){
    
    const char* src = source.c_str(); //returns a pointer to source

    unsigned int shadermID = glCreateShader(type); //generates a shader mID
    glShaderSource(shadermID, 1, &src, nullptr); //fills source code for desired shader
    glCompileShader(shadermID); //compiles shader

    //ensures succesful compilation
    int success;
    char infoLog[512];
    glGetShaderiv(shadermID, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(shadermID
, 512, NULL, infoLog);
        std::cout << "ERROR:SHADER::" + std::to_string(type) + "::COMPILATION_FAILED\n" << infoLog << std::endl;
        glDeleteShader(shadermID
);
        exit(EXIT_FAILURE);
    }

    return shadermID; 
}

shaderSource Shader::parseShader(const std::string &filePath){

    enum class ShaderType{
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    ShaderType type = ShaderType::NONE;
    std::ifstream stream(filePath); //gets current input stream
    if(!stream){
        std::cout << "ERROR::CANNOT FIND FILE" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string line; //string to hold each line from file
    std::stringstream ss[2];

   
    while(getline(stream, line)){
    
        if(line.find("#shader") != std::string::npos){ //finds "#shader" in file
           if(line.find("vertexShader") != std::string::npos){ //the current line holds "vertexShader" set type 
               type = ShaderType::VERTEX;
           }
           else if(line.find("fragmentShader") != std::string::npos){//the current line holds "fragmentShader" set type 
               type = ShaderType::FRAGMENT;
           }    
        }
        else{
            ss[(int)type] << line << '\n'; //push the line into the given array based on the index
        }
    }

    return {ss[0].str(), ss[1].str()};
}

void Shader::setVec4(const char* location, glm::vec4 uniform){
    int result = glGetUniformLocation(mID, location);
    assert(result != -1);
    glUniform4fv(result, 1, &uniform[0]);
}

void Shader::setVec3(const char* location, glm::vec3 uniform){
    int result = glGetUniformLocation(mID, location);
    assert(result != -1);
    glUniform3fv(result, 1, &uniform[0]);
}

void Shader::setMat4(const char* location, glm::mat4 uniform){
    int result = glGetUniformLocation(mID, location);
    assert(result != -1);
    glUniformMatrix4fv(result, 1, GL_FALSE, &uniform[0][0]);
}

void Shader::setInt(const char* location, int uniform){
    int result = glGetUniformLocation(mID, location);
    assert(result != -1);
    glUniform1i(result, uniform);
}
