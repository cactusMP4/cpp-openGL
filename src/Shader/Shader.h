//
// Created by cactusMP4 on 15.06.2025.
//

#ifndef SHADER_H
#define SHADER_H
#define GLEW_STATIC
#include <string>
#include <GL/GLEW/glew.h>


class Shader {
public:
    Shader(const std::string& vertex, const std::string& fragment);
    [[nodiscard]] GLuint getProgram() const;
private:
    GLuint program;
};



#endif //SHADER_H
