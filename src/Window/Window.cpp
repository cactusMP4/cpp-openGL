//
// Created by cactusMP4 on 07.06.2025.
//

#include <iostream>
#define GLEW_STATIC
#include <GL/GLEW/glew.h>

#include "Window.h"

#include "../Shader/Shader.h"


void GLCheckErrors() {
    while (const GLenum error = glGetError()) {
        std::cout << "OpenGL error occurred: "<< std::endl << error << std::endl;
    }
}

Window::Window(const std::string& title, const int width, const int height) {
    this->title = title;
    this->width = width;
    this->height = height;
}

void Window::init() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW?? oh fuck" << std::endl;
    }

    //config window
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
    //V-Sync
    glfwSwapInterval(1);

    //create window
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window lmao" << std::endl;
    }

    glfwMakeContextCurrent(window);
    glfwShowWindow(window);

    std::cout << "welcome to opengl "<< glGetString(GL_VERSION) << std::endl;

    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
    }

    //shader!
    const std::string vertexShader =
        "#version 330 core\n"
        "layout (location = 0) in vec4 aPos;\n"
        "void main() {\n"
        "   gl_Position = aPos;\n"
        "}";
    const std::string fragmentShader =
        "#version 330 core\n"
        "out vec4 color;\n"
        "void main() {\n"
        "   color = vec4(0.0, 1.0, 0.0, 1.0);\n"
        "}";

    const auto shader = new Shader("assets/shaders/default.glsl");
    glUseProgram(shader->getProgram());


    // lets make a triangle :p
    constexpr float positions[] = {
        0.0f, 0.0f, //0
        0.2f, 0.0f, //1
        0.0f, 0.2f, //2
        0.2f, 0.2f, //3
    };
    constexpr unsigned int indices[] = {
        /*
            2-------3
            |       |
            |       |
            0-------1
        */
        0,3,1,
        0,3,2
    };




    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, nullptr);
    glEnableVertexAttribArray(0);

    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    loop();

    std::cout << "window closed.";
    glDeleteProgram(shader->getProgram());
    glfwTerminate();
}
void Window::loop() {
    auto prevTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)){
        glClearColor(0.11f,0.11f,0.18f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        GLCheckErrors();

        glfwSwapBuffers(window);
        glfwPollEvents();

        const auto currentTime = glfwGetTime();
        const double dt = currentTime - prevTime;
        prevTime = currentTime;
    }
}

