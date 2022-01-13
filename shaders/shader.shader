##shader vertexShader
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 vertexColour;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 oFragmentColour;

void main()
{
   gl_Position = projection * view * model * vec4(aPos, 1.0);
   oFragmentColour = vertexColour;
}

#shader fragmentShader
#version 330 core
in vec3 oFragmentColour;

out vec4 colour;

void main()
{
   colour = vec4(oFragmentColour, 1.0);
}
