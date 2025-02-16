#pragma once

#include "Window.hpp"
#include "../libraries/glad/glad.h"
#include "../libraries/KHR/khrplatform.h"
#include "../libraries/GLFW/glfw3.h"

class Object
{
    public:
        Object();
        ~Object();
        GLuint &get_VAO();
        GLuint &get_VBO();
        GLuint &get_EBO();
        GLuint &get_shader_program();

    private:
        GLuint VAO;
        GLuint VBO;
        GLuint EBO;
        const char* vertexShaderSource;
        const char* fragmentShaderSource;
        GLuint vertexShader;
        GLuint fragmentShader;
        GLuint shaderProgram;
    
        void init_shader_sources();
        void init_vertices();
        void init_vertex_shader();
        void init_fragment_shader();
        void init_shader_program();
        void buffers();
};;
