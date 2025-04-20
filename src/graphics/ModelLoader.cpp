#include "graphics/ModelLoader.h"

#include <fstream>
#include <sstream>

namespace Graphics {

    bool ModelLoader::Load(const std::string& filename, float scale) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string prefix;
            ss >> prefix;

            if (prefix == "v") {
                glm::vec3 vertex;
                ss >> vertex.x >> vertex.y >> vertex.z;
                m_tmpVertices.push_back(vertex);
            } else if (prefix == "vt") {
                glm::vec2 uv;
                ss >> uv[0] >> uv[1];
                m_tmpUVs.push_back(uv);
            } else if (prefix == "f") {
                Face face;
                char slash;
                for (int i = 0; i < 3; ++i) {
                    ss >> face.vertexIndices[i] >> slash >> face.uvIndices[i];
                    // OBJ indices are 1-based; convert to 0-based
                    --face.vertexIndices[i];
                    --face.uvIndices[i];
                }
                m_tmpFaces.push_back(face);
            }
        }

        // Apply scale
        for (int i = 0; i < m_tmpVertices.size(); i ++) {
            m_tmpVertices[i][0] *= scale;
            m_tmpVertices[i][1] *= scale;
            m_tmpVertices[i][2] *= scale;
        }

        file.close();
        size_t face_count = m_tmpFaces.size();
        unsigned int index_count = 0;
        for(int j = 0; j < face_count; j ++) {
            for (int i = 0; i < 3; i ++)
                vertices.emplace_back(m_tmpVertices[m_tmpFaces[j].vertexIndices[i]]);
            for (int i = 0; i < 3; i ++) {
                if (m_tmpFaces[j].uvIndices[i] <= -1) {
                    return false;
                    // TODO Add error checking etc.
                } else {
                    uvs.emplace_back(m_tmpUVs[m_tmpFaces[j].uvIndices[i]]);
                }
            }
            indices.emplace_back(index_count + 0);
            indices.emplace_back(index_count + 1);
            indices.emplace_back(index_count + 2);
            index_count += 3;
        }
        return true;
    }
} // namespace Graphics
