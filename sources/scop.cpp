#include "../includes/Scop.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    (void)window;
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

Scop::Scop()
{
    this->init_window();
    this->create_window();
    this->init_glad();
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
    this->infinite_loop();
    glfwTerminate();
}

Scop::~Scop()
{
}

void Scop::init_window()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Scop::create_window()
{
    this->window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (this->window == NULL)
    {
        glfwTerminate();
        throw (std::runtime_error("Failed to create GLFW window."));
    }
    glfwMakeContextCurrent(this->window);
}

void Scop::init_glad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw (std::runtime_error("Failed to initialize GLAD."));
}

void Scop::infinite_loop()
{
    while(!glfwWindowShouldClose(this->window))
    {
        processInput(this->window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(this->window);
        glfwPollEvents();    
    }
}
