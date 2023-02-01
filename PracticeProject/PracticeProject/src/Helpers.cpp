#include "Header.hpp"




GLFWwindow* InitialiseWindow(const unsigned int width, const unsigned int height, const char* name)
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (window == NULL)
    {
        LOG("Failed to create GLFW window")
            glfwTerminate();
        return window;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG("Failed to initialize GLAD")
            return window;
    }
    return window;
}

//takes source scripts, compiles them and links them into a program and sets it as active
void CreateShaderProgram(const char* &vertexShaderSource, const char* &fragmentShaderSource) 
{
    //create vertex shader
    unsigned int vertexShader;
    //instantiate
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //add script
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    //compile
    glCompileShader(vertexShader);
    //log compilation results
    char infoLog[512];
    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        //display error if failed
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        LOG("failed vertex shader compilation")
            LOG(infoLog)
    }
    //create a fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //log errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        LOG("failed fragment shader compilation")
            LOG(infoLog)
    }
    unsigned int shaderProgram;
    //instantiate program
    shaderProgram = glCreateProgram();
    //attach shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    //link program
    glLinkProgram(shaderProgram);
    //log errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        LOG("failed shader program linking")
            LOG(infoLog)
    }
    //set active
    glUseProgram(shaderProgram);
    //delete redundant shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}