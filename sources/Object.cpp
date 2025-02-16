#include "../includes/Window.hpp"
#include "../includes/Object.hpp"

Object::Object()
{
    this->init_shader_sources();
    this->init_vertices();
    this->init_vertex_shader();
    this->init_fragment_shader();
    this->init_shader_program();
    this->buffers();
}

Object::~Object()
{
}

GLuint &Object::get_VAO()
{
    return (this->VAO);
}

GLuint &Object::get_VBO()
{
    return (this->VBO);
}

GLuint &Object::get_EBO()
{
    return (this->EBO);
}

GLuint &Object::get_shader_program()
{
    return (this->shaderProgram);
}

void Object::init_shader_sources()
{
    this->vertexShaderSource = R"glsl(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        void main()
        {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    )glsl";
    
    this->fragmentShaderSource = R"glsl(
        #version 330 core
        out vec4 FragColor;
        void main()
        {
            FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); // Couleur orange
        }
    )glsl";
}

void Object::init_vertices()
{
    ;
}

void Object::init_vertex_shader()
{
    this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(this->vertexShader, 1, &this->vertexShaderSource, NULL);
    glCompileShader(this->vertexShader);
    this->check_shaders(this->fragmentShader, "vertex shader");
}

void Object::init_fragment_shader()
{
    this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(this->fragmentShader, 1, &this->fragmentShaderSource, NULL);
    glCompileShader(this->fragmentShader);
    this->check_shaders(this->fragmentShader, "fragment shader");
}

void Object::init_shader_program()
{
    this->shaderProgram = glCreateProgram();
    glAttachShader(this->shaderProgram, this->vertexShader);
    glAttachShader(this->shaderProgram, this->fragmentShader);
    glLinkProgram(this->shaderProgram);
    this->check_shaders(this->fragmentShader, "shader program");
    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Object::check_shaders(GLuint shader, std::string shader_name)
{
    GLint  success;
    if (shader_name == "shader program")
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
    else
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        GLchar infoLog[512];
        std::string errorMessage;
        if (shader_name == "shader program")
        {
            glGetProgramInfoLog(shader, 512, NULL, infoLog);
            errorMessage = "Failed to link " + shader_name ": ";
        }
        else
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            errorMessage = "Failed to compile the " + shader_name + ": ";
        }
        errorMessage += infoLog;
        throw(std::runtime_error(errorMessage));
    }
}

void Object::buffers()
{
    GLfloat vertices = {
        -0.5f,  -0.5f * float(sqrt(3)) / 3, 0.0f,  // Lower left corner
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  // Lower right corner
       0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  // Upper corner
       -0.5f / 2,  0.5f * float(sqrt(3)) / 6, 0.0f,   // Inner left
       0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,   // Inner right
       0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f   // Inner down
    };

    GLuint indices = {  // Notons que l’on commence à 0!
       0, 3, 5,   // first triangle
       3, 2, 4,    // second triangle
       5, 4, 1    // third triangle
    };

    glGenVertexArrays(1, &this->VAO);
    // Lier le Vertex Array Object (VAO)
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);
    
    glBindVertexArray(this->VAO);
    
    // Copier les sommets dans un tampon pour qu’OpenGL les utilise
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);
    
    // Copier le tableau d’indices dans un tampon d’éléments
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indices), this->indices, GL_STATIC_DRAW);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indices), this->indices, GL_STATIC_DRAW);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Initialiser les pointeurs d’attributs de sommets
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
