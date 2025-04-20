#include "graphics/FontRenderer.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "utils/Logger.h"

namespace Graphics {

    FontRenderer::FontRenderer(const char* font_path, unsigned int font_size) {
        m_path = font_path;
        m_AssignID();
        m_InitGLBuffers();
        m_LoadFont(font_path, font_size);
    }

    void FontRenderer::m_AssignID() {
        static unsigned int s_fontCount = 0;
        s_fontCount ++;
        m_id = s_fontCount;
    }

    unsigned int FontRenderer::GetID() const {
        return m_id;
    }

    const std::string& FontRenderer::GetPath() const {
        return m_path;
    }

    int FontRenderer::m_LoadFont(const char* fontPath, unsigned int fontSize) {
        FT_Library ft;
        if (FT_Init_FreeType(&ft)) {
            Utils::Logger::Log(Utils::Logger::LogLevel::Error, "FREETYPE: Could not init FreeType Library");
            return -1;
        }

        FT_Face face;
        if (FT_New_Face(ft, fontPath, 0, &face)) {
            Utils::Logger::Log(Utils::Logger::LogLevel::Error, "FREETYPE: Failed to load font");
            return -1;
        }

        FT_Set_Pixel_Sizes(face, 0, fontSize);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // Create empty texture for the atlas
        glGenTextures(1, &m_atlasTextureID);
        glBindTexture(GL_TEXTURE_2D, m_atlasTextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_atlasWidth, m_atlasHeight, 0, GL_RED, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int offsetX = 0;
        int offsetY = 0;
        unsigned int rowHeight = 0;

        for (unsigned char c = 32; c < 128; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                Utils::Logger::Log(Utils::Logger::LogLevel::Error, "FREETYTPE: Failed to load Glyph");
                continue;
            }

            if (offsetX + face->glyph->bitmap.width > m_atlasWidth) {
                offsetX = 0;
                offsetY += rowHeight;
                rowHeight = 0;
            }

            glTexSubImage2D(GL_TEXTURE_2D, 0, offsetX, offsetY, face->glyph->bitmap.width, face->glyph->bitmap.rows,
                            GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

            m_characters[c] = {
                glm::vec2((float)offsetX / m_atlasWidth, (float)offsetY / m_atlasHeight),
                glm::vec2((float)face->glyph->bitmap.width / m_atlasWidth, (float)face->glyph->bitmap.rows / m_atlasHeight),
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x // TODO, CHECK THIS LINE
            };

            offsetX += face->glyph->bitmap.width;
            rowHeight = std::max(rowHeight, face->glyph->bitmap.rows);
        }

        FT_Done_Face(face);
        FT_Done_FreeType(ft);

        return 0;
    }

    // TODO MAKE THIS STATIC OR SOMETHING, I.E. SAVE THE GENERATED MESHES SO WE DONT GENERATE THEM IN EACH FRAME
    // TODO MAYBE THERE CAN BE TWO TYPES OF TEXTS WHICH ONE OF THEM IS GENERATED IN EACH FRAME BUT OTHER IS STATIC
    void FontRenderer::Render(const std::string& text, float x, float y, float scale, glm::vec3 color) {
        glBindTexture(GL_TEXTURE_2D, m_atlasTextureID);
        glBindVertexArray(m_vao);

        for (char c : text) {
            if (m_characters.find(c) == m_characters.end()) continue;

            Character ch = m_characters[c];

            float xpos = x + ch.Bearing.x * scale;
            float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;

            float vertices[6][4] = {
                { xpos,     ypos + h,   ch.TexOffset.x,                ch.TexOffset.y },
                { xpos,     ypos,       ch.TexOffset.x,                ch.TexOffset.y + ch.TexSize.y },
                { xpos + w, ypos,       ch.TexOffset.x + ch.TexSize.x, ch.TexOffset.y + ch.TexSize.y },

                { xpos,     ypos + h,   ch.TexOffset.x,                ch.TexOffset.y },
                { xpos + w, ypos,       ch.TexOffset.x + ch.TexSize.x, ch.TexOffset.y + ch.TexSize.y },
                { xpos + w, ypos + h,   ch.TexOffset.x + ch.TexSize.x, ch.TexOffset.y }
            };

            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

            glDrawArrays(GL_TRIANGLES, 0, 6);

            x += (ch.Advance >> 6) * scale;
        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    int FontRenderer::m_InitGLBuffers() {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        return 0;
    }

} // namespace Graphics
