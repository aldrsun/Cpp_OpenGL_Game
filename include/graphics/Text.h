#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <glm/glm.hpp>

namespace Graphics {

    class Text {
    public:
        Text(unsigned int font_id, const std::string& content, float x, float y, float scale, glm::vec3 color);

        std::string content;
        unsigned int fontID;
        float x, y, scale;
        glm::vec3 color;

        unsigned int GetID() const;
    private:
        unsigned int m_id;
        void m_AssignID();
    };

} // namespace Graphics


#endif // TEXT_H
