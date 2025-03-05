#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>

namespace Graphics {

    class Texture {
    public:
        GLuint id;
        std::string type;
        std::string path;
    };

}

#endif
