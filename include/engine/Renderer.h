#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/Mesh.h"
#include "graphics/Texture.h"
#include "graphics/BatchColored.h"
#include "graphics/BatchTextured.h"

#include <map>
#include <vector>
#include <memory>

namespace Engine {

    using namespace Graphics;

    class Renderer {
    public:
        Renderer(GLuint texture_id, GLuint shader_colored, GLuint shader_textured);
    
        void SubmitMesh(const Mesh& mesh);
        void ApplyMeshChanges();
	
    	GLuint AddTexture(const char* texture_path);	
        void Render();
    
        void Clear();
    
    private:
	GLuint m_shaderColored, m_shaderTextured;
	std::vector<std::unique_ptr<Texture>> m_textures;

        std::unique_ptr<BatchColored> m_coloredBatch;
	    std::map<GLuint, std::unique_ptr<BatchTextured>> m_texturedBatches;
    };

} // namespace Engine

#endif // RENDERER_H
