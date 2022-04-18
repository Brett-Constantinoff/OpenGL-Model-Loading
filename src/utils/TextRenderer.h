
   
#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <ft2build.h>
#include FT_FREETYPE_H  
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Utils.h"
#include "../shaders/Shader.h"


typedef struct{
    uint32_t textureID; //handle for the glyph texture
    glm::ivec2 size; //width and height of glyph in pixels
    glm::ivec2 bearing; //x and y position relatice to the origin and baseline
    uint32_t advance; //distance from the origin to the origin of the next glyph
}Character;

class TextRenderer{
    public:
        TextRenderer( Shader* shader );
        void loadFont(std::string font, uint32_t fontSize);
        void render(std::string text, glm::vec2 pos, float size, glm::vec3 colour, bool centered);
    
    private:
        void init( void );
        std::string mFont;
        uint32_t mFontSize;
        std::map<char, Character> mCharacters;
        uint32_t mVao;
        uint32_t mVbo;
        Shader* mShader;
};

#endif