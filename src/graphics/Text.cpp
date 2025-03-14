#include "graphics/Text.h"

namespace Graphics {

    Text::Text(unsigned int _font_id, const std::string& _content, float _x, float _y, float _scale, glm::vec3 _color) {
        m_AssignID();
        fontID = _font_id;
        content = _content;
        x = _x;
        y = _y;
        scale = _scale;
        color = _color;
    }

    unsigned int Text::GetID() const {
        return m_id;
    }

    void Text::m_AssignID() {
        static unsigned int s_textCount = 0;
        s_textCount ++;
        m_id = s_textCount;
    }
} // namespace Graphics
