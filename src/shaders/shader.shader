##shader vertexShader
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aUv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 normalMatrix;
uniform vec3 cameraPosition;

out vec3 oNormal;
out vec3 oCameraPosition;
out vec3 oFragPosition;
out vec2 oUv;

void main()
{
   gl_Position = projection * view * model * vec4(aPos, 1.0);
   oFragPosition = (model * vec4(aPos, 0.0)).xyz;
   oNormal = (normalMatrix * vec4(aNorm, 0.0)).xyz;
   oCameraPosition = cameraPosition;
   oUv = aUv;
}

#shader fragmentShader
#version 330 core

uniform vec3 diffuseVal;
uniform vec3 ambientVal;
uniform vec3 specularVal;
uniform float lightStr;
uniform float n;
uniform vec3 lightCol;
uniform vec3 lightPos;
uniform sampler2D myTexture;

in vec3 oNormal;
in vec3 oCameraPosition;
in vec3 oFragPosition;
in vec2 oUv;

out vec4 colour;

void main()
{  
   vec4 textureCol = texture(myTexture, oUv);

   vec3 normal = normalize(oNormal);
   vec3 lightDir = normalize(lightPos - oFragPosition);
   vec3 viewDir = normalize(oCameraPosition - oFragPosition);
   vec3 ambient = ambientVal * lightCol * lightStr;

   float diff = max(dot(lightDir, normal), 0.0);
   vec3 diffuse = diffuseVal * lightCol * diff;

   vec3 halfVec = normalize(lightDir + viewDir);
   float spec = max(dot(halfVec, normal), 0.0);
   vec3 specular = specularVal * lightCol * pow(spec, n);

   colour = vec4(diffuse + ambient + specular,  1.0) * textureCol;
}
