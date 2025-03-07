#include "engine/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL2/SOIL2.h>

#include "utils/Logger.h"

namespace Engine {
    using namespace Graphics;

    Renderer::Renderer(GLuint texture_id, GLuint shader_colored, GLuint shader_textured, std::shared_ptr<GameObjects::Camera> camera) {
        m_coloredBatch = std::make_unique<BatchColored>();
        m_shaderColored = shader_colored;
        m_shaderTextured = shader_textured;

        m_activeCamera = camera;

        // TODO : ADD ERROR CHECK
        m_ulocTransformationColored = glGetUniformLocation(shader_colored, "u_Transformation");
        m_ulocTransformationTextured = glGetUniformLocation(shader_textured, "u_Transformation");

    }

    void Renderer::SetActiveCamera(std::shared_ptr<GameObjects::Camera> camera) {
        m_activeCamera = camera;
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

        // TODO : IMPROVE THIS, maybe do something with Texture class.
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

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
    }

    void Renderer::Clear() {
        m_coloredBatch->Clear();

        for (auto const& textured_batch : m_texturedBatches) {
            textured_batch.second->Clear();
        }
    }

} // namespace Engine
