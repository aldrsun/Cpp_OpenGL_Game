#ifndef BATCH_H
#define BATCH_H

#include <vector>

#include <GL/glew.h>

#include "graphics/Mesh.h"

namespace Graphics {

    class Batch {
    public:
        virtual ~Batch() = default;

        virtual void SubmitMesh(const Mesh& mesh) = 0;
        virtual void ApplyMeshChanges() = 0;

        virtual void Render() const = 0;

        virtual void Clear() = 0;
    };

}

#endif // BATCH_H