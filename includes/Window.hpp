#pragma once

#include "Object.hpp"
#include "../libraries/glad/glad.h"
#include "../libraries/KHR/khrplatform.h"
#include "../libraries/GLFW/glfw3.h"
#include <iostream>
#include <exception>
#include <string>
#include <cmath>

class Window
{
    public:
        Window();
        ~Window();
        GLFWwindow* get_window();
        
    private:
        GLFWwindow* window;
        
        void init_window();
        void create_window();
        void init_glad();
        static void adjust_window_size_event(GLFWwindow* window, int width, int height);
        void handle_input_keys();
        void infinite_loop(Object object);
        void destroy_window(Object object);
};
