#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/Mesh.h"
#include "graphics/Texture.h"
#include "graphics/BatchColored.h"
#include "graphics/BatchTextured.h"
#include "graphics/Text.h"
#include "graphics/FontRenderer.h"

#include "gameobjects/Camera.h"

#include <map>
#include <vector>
#include <memory>

namespace Engine {

    using namespace Graphics;

    class Renderer {
    public:
        Renderer(GLuint shader_colored, GLuint shader_textured, GLuint shader_text, std::shared_ptr<GameObjects::Camera> camera);

        void SetActiveCamera(std::shared_ptr<GameObjects::Camera> camera);
        std::shared_ptr<GameObjects::Camera> GetActiveCamera() const;

        void SubmitMesh(const Mesh& mesh);
        void ApplyMeshChanges();

        unsigned int AddText(unsigned int font_id, const std::string& text, float x, float y, float scale, glm::vec3 color);
        void ChangeText(unsigned int text_id, const char* new_content);
        unsigned int AddFont(const char* font_path, unsigned int font_size);

        GLuint AddTexture(const char* texture_path);
        void Render();

        void Clear();

    private:
        std::shared_ptr<GameObjects::Camera> m_activeCamera;
        GLuint m_ulocTransformationColored;
        GLuint m_ulocTransformationTextured;
        GLuint m_ulocTextProjection;
        GLuint m_ulocTextColor;

        GLuint m_shaderColored, m_shaderTextured, m_shaderText;
        std::vector<std::unique_ptr<Texture>> m_textures;

        std::unique_ptr<BatchColored> m_coloredBatch;
        std::map<GLuint, std::unique_ptr<BatchTextured>> m_texturedBatches;

        std::map<unsigned int, std::unique_ptr<FontRenderer>> m_fonts;
        std::map<unsigned int, std::unique_ptr<Text>> m_texts;
    };

} // namespace Engine

#endif // RENDERER_H
