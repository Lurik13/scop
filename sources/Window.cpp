#include "../includes/Window.hpp"
#include "../includes/Object.hpp"

Window::Window()
{
    this->init_window();
    this->create_window();
    this->init_glad();
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(this->window, this->adjust_window_size_event);
    Object object;
    this->infinite_loop(object);
    this->destroy_window(object);
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

void Window::infinite_loop(Object object)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    while(!glfwWindowShouldClose(this->window))
    {
        this->handle_input_keys();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(object.get_shader_program());
        glBindVertexArray(object.get_VAO());
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        glfwSwapBuffers(this->window);
        glfwPollEvents();    
    }
    
}
void Window::destroy_window(Object object)
{
    glDeleteVertexArrays(1, &object.get_VAO());
    glDeleteBuffers(1, &object.get_VBO());
    glDeleteBuffers(1, &object.get_EBO());
    glDeleteProgram(object.get_shader_program());
    glfwDestroyWindow(window);
    glfwTerminate();
}
