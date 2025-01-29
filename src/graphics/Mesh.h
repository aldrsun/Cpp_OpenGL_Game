//
// Created by linuxmint on 1/27/25.
//

#ifndef MESH_H
#define MESH_H
#include <GL/glew.h>

namespace Graphics {

class Mesh {
public:
    int Generate(float x, float y, float width, float height);
    void Render() const;
    void Clear() const;
private:
    GLuint vao = 0, vbo = 0;
};

} // Engine

#endif //MESH_H
