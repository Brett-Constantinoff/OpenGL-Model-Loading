#include "TextRenderer.h"

TextRenderer::TextRenderer(){
    mShader = Utils::createShader("src/shaders/textShader.txt");
}

void TextRenderer::loadFont(std::string font, uint32_t fontSize){
    mFont = font;
    mFontSize = fontSize;
    //clear any previous characters
    mCharacters.clear();
    init();
}

void TextRenderer::init( void ){
    //initialize free type library
    FT_Library freeType;
    if(FT_Init_FreeType(&freeType)){
        std::cout << "ERROR INITIALIZING FREETYPE LIBRARY!\n";
        exit(EXIT_FAILURE);
    }

    //load font into a face
    FT_Face face;
    if(FT_New_Face(freeType, mFont.c_str(), 0, &face)){
        std::cout << "ERROR LOADING " << mFont << " FILE!\n";
        exit(EXIT_FAILURE);
    }

    //define pixel font size
    //setting the width to 0 lets the face calculate the width dynamically based on height
    FT_Set_Pixel_Sizes(face, 0, mFontSize);

    //disbales the byte alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //generate data for each ASCII character
    for(uint8_t c = 0; c < 128; c++){
        
        //load the character glyph
        if(FT_Load_Char(face, c, FT_LOAD_RENDER)){
            std::cout << "ERROR LOADING GLYPH!\n";
            exit(EXIT_FAILURE);
        }

        //load texture
        uint32_t textureID = Utils::genTexture();
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 
                     face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, 
                     GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //create a new character
        Character character = {
            textureID, 
            {face->glyph->bitmap.width, face->glyph->bitmap.rows},
            {face->glyph->bitmap_left, face->glyph->bitmap_top}, 
            static_cast<uint32_t>(face->glyph->advance.x)
        };

        //insert into map with its associated ASCII value
        mCharacters.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    //deallocate res
    FT_Done_Face(face);
    FT_Done_FreeType(freeType);

     //create our projection matrix
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f);

    //load and setup shader
    mShader->use();
    mShader->setMat4("uProjection", projection);
    mShader->setInt("uTexture", 0);

    //setup buffers
    mVao = Utils::genVertexArray();
    glBindVertexArray(mVao);
    mVbo = Utils::genBuffer();
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    //the data will change often so use GL_DYNAMIC_DRAW
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextRenderer::render(std::string text, glm::vec2 pos, float size, glm::vec3 colour, bool centered){
    //set the render state
    mShader->use();
    mShader->setVec3("uColour", colour);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(mVao);

    //get the tallest character to use as a baseline
    Character tallest = mCharacters['H'];
    std::string::const_iterator c;

    //center text
    if(centered){
        int length = 0;
        for(c = text.begin(); c != text.end(); c++){
            Character ch = mCharacters[*c];
            length += (ch.advance >> 6) * size;
        }
        int half = length / 2;
        pos.x -= half;
    }

    //iterate through characters in text
    for(c = text.begin(); c != text.end(); c++){
        Character ch = mCharacters[*c];

        float xPos = pos.x + ch.bearing.x * size;
        float yPos = pos.y + (tallest.bearing.y - ch.bearing.y) * size;

        float w = ch.size.x * size;
        float h = ch.size.y * size;

        float vertexData[6][4]{
            {xPos, yPos + h, 0.0f, 1.0f},
            {xPos + w, yPos, 1.0f, 0.0f},
            {xPos, yPos,     0.0f, 0.0f},
            {xPos, yPos + h, 0.0f, 1.0f},
            {xPos + w, yPos + h, 1.0f, 1.0f},
            {xPos + w, yPos, 1.0f, 0.0f}
        };

        //render texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.textureID);

        //update vbo
        glBindBuffer(GL_ARRAY_BUFFER, mVbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexData), vertexData);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        //render
        glDrawArrays(GL_TRIANGLES, 0, 6);

        //advance by number of pixles, >> 6 = 2^6 = 64 since advance is in 1/64 pixels
        pos.x += (ch.advance >> 6) * size;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}