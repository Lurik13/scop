#include "../includes/Window.h"

Window::Window()
{
    this->init_window();
    this->create_window();
    this->init_glad();
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(this->window, this->adjust_window_size_event);
    this->infinite_loop();
    glfwDestroyWindow(window);
    glfwTerminate();
}

Window::~Window()
{
}

GLFWwindow* Window::get_window()
{
    return (this->window);
}

void Window::init_window()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::create_window()
{
    this->window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (this->window == NULL)
    {
        glfwTerminate();
        throw (std::runtime_error("Failed to create GLFW window."));
    }
    glfwMakeContextCurrent(this->window);
}

void Window::init_glad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw (std::runtime_error("Failed to initialize GLAD."));
}

void Window::adjust_window_size_event(GLFWwindow* window, int width, int height)
{
    (void)window;
    glViewport(0, 0, width, height);
}

void Window::handle_input_keys()
{
    if(glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(this->window, true);
}

const char* vertexShaderSource = R"glsl(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)glsl";

const char* fragmentShaderSource = R"glsl(
    #version 330 core
    out vec4 FragColor;
    void main()
    {
        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); // Couleur orange
    }
)glsl";

void Window::infinite_loop()
{
    GLfloat vertices[] = {
        // first triangle
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f,  0.5f, 0.0f,  // top left 
        // second triangle
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    GLint  success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::string errorMessage = "Failed to compile the vertex shader: ";
        errorMessage += infoLog;
        throw(std::runtime_error(errorMessage));
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // GLint  success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::string errorMessage = "Failed to compile the fragment shader: ";
        errorMessage += infoLog;
        throw(std::runtime_error(errorMessage));
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // GLint  success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::string errorMessage = "Failed to link shader program: ";
        errorMessage += infoLog;
        throw(std::runtime_error(errorMessage));
    }
    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);



    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    // Lier le Vertex Array Object (VAO)
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    // Copier les sommets dans un tampon pour qu’OpenGL les utilise
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Initialiser les pointeurs d’attributs de sommets
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    while(!glfwWindowShouldClose(this->window))
    {
        this->handle_input_keys();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(this->window);
        glfwPollEvents();    
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}
