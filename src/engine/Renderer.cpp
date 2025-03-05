#include "engine/Renderer.h"

#include "utils/Logger.h"

#include <SOIL2/SOIL2.h>

namespace Engine {
    using namespace Graphics;

    Renderer::Renderer(GLuint texture_id, GLuint shader_colored, GLuint shader_textured) {
        m_coloredBatch = std::make_unique<BatchColored>(shader_colored);
    	m_shaderColored = shader_colored;
		m_shaderTextured = shader_textured;
    }

    void Renderer::SubmitMesh(const Mesh& mesh) {
        if (mesh.textureID != 0) {
            if (m_texturedBatches.find(mesh.textureID) != m_texturedBatches.end()) {
				m_texturedBatches[mesh.textureID]->SubmitMesh(mesh);
				Utils::Logger::Log("Added Textured Mesh to an Existing Batch");
	    	} else {
				m_texturedBatches[mesh.textureID] = std::make_unique<BatchTextured>(mesh.textureID, m_shaderTextured);
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

	// TEMP, TODO
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	Utils::Logger::Log("Texture Generated:", texture_id);

	return texture_id;
    }


    void Renderer::Render() {
        m_coloredBatch->Render();
        
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
