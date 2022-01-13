#include "shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


Shader::Shader(const std::string &filepath){
    ID = glCreateProgram(); //creates current shader program

    shaderSource source = Shader::parseShader(filepath);
    unsigned int vShader = Shader::compileShader(source.vertexSource, GL_VERTEX_SHADER); //compiles vertex source
    unsigned int fShader = Shader::compileShader(source.fragmentSource, GL_FRAGMENT_SHADER); //compiles fragment source

    //attaches shaders to program
    glAttachShader(ID, vShader);
    glAttachShader(ID, fShader);
    //links the shader program
    glLinkProgram(ID);
    //ensures successful linking
    glValidateProgram(ID);

    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

unsigned int Shader::compileShader(const std::string &source, unsigned int type){
    
    const char* src = source.c_str(); //returns a pointer to source

    unsigned int shaderID = glCreateShader(type); //generates a shader ID
    glShaderSource(shaderID, 1, &src, nullptr); //fills source code for desired shader
    glCompileShader(shaderID); //compiles shader

    //ensures succesful compilation
    int success;
    char infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        std::cout << "ERROR:SHADER::" + std::to_string(type) + "::COMPILATION_FAILED\n" << infoLog << std::endl;
        glDeleteShader(shaderID);
        exit(EXIT_FAILURE);
    }

    return shaderID; 
}

shaderSource Shader::parseShader(const std::string &filePath){

    enum class ShaderType{
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    ShaderType type = ShaderType::NONE;
    std::ifstream stream(filePath); //gets current input stream
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

