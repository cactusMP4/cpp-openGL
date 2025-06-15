//
// Created by cactusMP4 on 11.06.2025.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(const std::string &title, int width, int height);

    void init();
    void loop();
private:
    int width, height;
    std::string title;
    GLFWwindow *window{};
};


#endif //WINDOW_H
