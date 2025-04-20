#include "engine/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL2/SOIL2.h>

#include "utils/Logger.h"

namespace Engine {
    using namespace Graphics;

    Renderer::Renderer(Window* window, GLuint shader_colored, GLuint shader_textured, GLuint shader_text, std::shared_ptr<GameObjects::Camera> camera) {
        m_coloredBatch = std::make_unique<BatchColored>();
        m_shaderColored = shader_colored;
        m_shaderTextured = shader_textured;
        m_shaderText = shader_text;

        m_activeWindow = window;
        m_activeCamera = camera;

        // TODO : ADD ERROR CHECK
        // TODO : MAKE NAMES "UNIFORM", I.E. FOLLOW A NAMING CONVENTION IN GLSL TOO.
        // TODO : THE NAMES ARE CURRENTLY SEEMS ALMOST RANDOM
        m_ulocTransformationColored  = glGetUniformLocation(shader_colored  , "u_Transformation");
        m_ulocTransformationTextured = glGetUniformLocation(shader_textured , "u_Transformation");
        m_ulocTextProjection         = glGetUniformLocation(shader_text     , "projection");
        m_ulocTextColor              = glGetUniformLocation(shader_text     , "u_Color");

        m_mTextProjection = glm::ortho(0.0f, m_activeWindow->GetWidth(), 0.0f, m_activeWindow->GetHeight());

    }

    void Renderer::SetActiveCamera(std::shared_ptr<GameObjects::Camera> camera) {
        m_activeCamera = camera;
    }

    std::shared_ptr<GameObjects::Camera> Renderer::GetActiveCamera() const {
        return m_activeCamera;
    }

    void Renderer::SubmitMesh(const Mesh& mesh) {
        if (mesh.textureID != 0) {
            if (m_texturedBatches.find(mesh.textureID) != m_texturedBatches.end()) {
                m_texturedBatches[mesh.textureID]->SubmitMesh(mesh);
                Utils::Logger::Log("Added Textured Mesh to an Existing Batch");
            } else {
                m_texturedBatches[mesh.textureID] = std::make_unique<BatchTextured>(mesh.textureID);
                m_texturedBatches[mesh.textureID]->SubmitMesh(mesh);
                Utils::Logger::Log("Added Textured Mesh to a New Batch");
            }
        } else {
            m_coloredBatch->SubmitMesh(mesh);
            Utils::Logger::Log("Added Colored Mesh");
        }
    }

    void Renderer::ApplyMeshChanges() {
        for (auto const& textured_batch : m_texturedBatches) {
            textured_batch.second->ApplyMeshChanges();
        }
        m_coloredBatch->ApplyMeshChanges();
    }

    unsigned int Renderer::AddText(unsigned int font_id, const std::string& text, float x, float y, float scale, glm::vec3 color) {
        std::unique_ptr<Text> new_text = std::make_unique<Text>(font_id, text, x, y, scale, color);
        unsigned int new_text_id = new_text->GetID();
        m_texts[new_text_id] = std::move(new_text);
        return new_text_id;
    }

    void Renderer::ChangeText(unsigned int text_id, const char* new_content) {
       m_texts[text_id]->content = new_content;
    }

    unsigned int Renderer::AddFont(const char* font_path, unsigned int font_size) {
        auto it = m_fonts.begin();
        std::string str_font_path = font_path;
        for (; it != m_fonts.end(); it ++) {
            if (it->second->GetPath() == str_font_path) {
                return it->second->GetID();
            }
        }

        std::unique_ptr<FontRenderer> new_font = std::make_unique<FontRenderer>(font_path, font_size);
        unsigned int new_font_id = new_font->GetID();
        m_fonts[new_font_id] = std::move(new_font);
        return new_font_id;
    }

    GLuint Renderer::AddTexture(const char *texture_path) {

        for (auto const& texture : m_textures) {
            if(texture->path == texture_path) {
                return texture->id;
            }
        }

        GLuint texture_id;
        texture_id = SOIL_load_OGL_texture(texture_path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
        if (texture_id == 0)
            Utils::Logger::Log("could not find texture file", texture_path);

        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glGenerateMipmap(GL_TEXTURE_2D);

        Utils::Logger::Log("Texture Generated:", texture_id);

        return texture_id;
    }

    void Renderer::Render() {

        glm::mat4 camera_transformation = m_activeCamera->GetTransformation();

        glUseProgram(m_shaderColored);
        glUniformMatrix4fv(m_ulocTransformationColored, 1, GL_FALSE, glm::value_ptr(camera_transformation));
        m_coloredBatch->Render();

        glUseProgram(m_shaderTextured);
        glUniformMatrix4fv(m_ulocTransformationTextured, 1, GL_FALSE, glm::value_ptr(camera_transformation));
        for (auto const& textured_batch : m_texturedBatches) {
            textured_batch.second->Render();
        }

        glUseProgram(m_shaderText);
        glUniformMatrix4fv(m_ulocTextProjection, 1, GL_FALSE, glm::value_ptr(m_mTextProjection));
        for (const auto& text : m_texts) {
            glUniform3fv(m_ulocTextColor, 1, glm::value_ptr(text.second->color));
            m_fonts[text.second->fontID]->Render(text.second->content, text.second->x, text.second->y, text.second->scale, text.second->color);
        }
    }

    void Renderer::Clear() {
        m_coloredBatch->Clear();

        for (auto const& textured_batch : m_texturedBatches) {
            textured_batch.second->Clear();
        }
    }

} // namespace Engine
