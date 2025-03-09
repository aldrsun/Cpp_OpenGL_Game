#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include <glm/glm.hpp>

#include "graphics/Mesh.h"

namespace Graphics {

    struct Face {
        int vertexIndices[3];
        int uvIndices[3];
    };

    class ModelLoader {
    public:
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<unsigned int> indices;

        bool Load(const std::string& filename);

    private:
        std::vector<glm::vec3> m_tmpVertices;
        std::vector<glm::vec2> m_tmpUVs;
        std::vector<glm::vec3> m_tmpNormals;
        std::vector<Face> m_tmpFaces;
    };

} // namespace Graphics

#endif // MODEL_LOADER_H
