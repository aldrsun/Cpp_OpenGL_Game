#ifndef FONT_RENDERER_H
#define FONT_RENDERER_h

#include <string>
#include <map>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace Graphics {

    struct Character {
        glm::vec2 TexOffset;
        glm::vec2 TexSize;
        glm::ivec2 Size;
        glm::ivec2 Bearing;
        unsigned int Advance;
    };

    class FontRenderer {
    public:
        FontRenderer(const char* font_path, unsigned int font_size);

        void Render(const std::string& text, float x, float y, float scale, glm::vec3 color);

        unsigned int GetID() const;
        const std::string& GetPath() const;

    private:
        std::string m_path;
        unsigned int m_id;
        void m_AssignID();

        std::string m_fontPath;

        GLuint m_vao = 0, m_vbo = 0;
        std::map<char, Character> m_characters;

        unsigned int m_atlasTextureID;
        unsigned int m_atlasWidth = 1024;
        unsigned int m_atlasHeight = 512;

        int m_LoadFont(const char* font_path, unsigned int font_size);
        int m_InitGLBuffers();

    };


}


#endif // FONT_RENDERER_H
