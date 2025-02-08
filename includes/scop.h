#pragma once

#include "../libraries/glad/glad.h"
#include "../libraries/KHR/khrplatform.h"
#include "../libraries/GLFW/glfw3.h"
#include <iostream>
#include <exception>

class Scop
{
    public:
        Scop();
        ~Scop();
        void init_window();
        void create_window();
        void init_glad();
        void infinite_loop();
    
    private:
        GLFWwindow* window;
};
