#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <string>
#include <map>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace Graphics {

    struct Character {
        glm::vec2 TexOffset;     // UV offset in the atlas
        glm::vec2 TexSize;       // UV size in the atlas
        glm::ivec2 Size;         // Size of glyph
        glm::ivec2 Bearing;      // Offset from baseline to left/top of glyph
        unsigned int Advance;    // Offset to advance to next glyph
    };

    class TextRenderer {
    public:
        TextRenderer();

        void RenderText(const std::string& text, float x, float y, float scale, glm::vec3 color);

        int LoadFont(const char* fontPath, int fontSize);
    private:
        GLuint m_vao = 0, m_vbo = 0;

        std::map<char, Character> m_characters;
        unsigned int m_atlasTexture;

        unsigned int m_atlasWidth = 1024;
        unsigned int m_atlasHeight = 512;



    };

} // namespace Graphics


#endif // TEXT_RENDERER_H

