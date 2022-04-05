#shader vertexShader
#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 fColor;

void main()
{
    gl_Position = vec4(aPos, 1.0);
}

#shader fragmentShader
#version 330 core

out vec4 fragColour;

void main(){
    fragColour = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}