    #ifndef WINDOWHANDLER_H
    #define WINDOWHANDLER_H

    #include <iostream>
    #include <glad/glad.h>
    #include <GLFW/glfw3.h>
    #include <glm/glm.hpp>
    #include <glm/gtc/matrix_transform.hpp>

    GLFWwindow* createCenteredWindow()
    {
        if(!glfwInit()) //Loads GLFW Functions
        {
            std::cout << "Failed to Load GLFW" << std::endl;
            return nullptr;
        }
        //!CHANGE FIRST THREE LINES WHEN EDITING THE CODE AND SET THEM TO THE VERSION YOU DOWNLOADED
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        GLFWmonitor* myMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* myMonitorSettings = glfwGetVideoMode(myMonitor);
        int windowWidth = (int)(myMonitorSettings -> width / 1.5f);
        int windowHeight = (int)(myMonitorSettings -> height / 1.5f);
        GLFWwindow* mainWindow = glfwCreateWindow(windowWidth, windowHeight, "Main Window", NULL, NULL);
        glfwSetWindowSizeLimits(mainWindow, windowWidth, windowHeight, windowWidth, windowHeight);
        if(!mainWindow)
        {
            std::cout << "Failed to Load Main Window" << std::endl;
            return nullptr;
        }
        glfwMakeContextCurrent(mainWindow);
        int centerX = (myMonitorSettings -> width - windowWidth) / 2;
        int centerY = (myMonitorSettings -> height - windowHeight) / 2;
        glfwSetWindowPos(mainWindow, centerX, centerY);
            if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //Loads GLAD Functions using the GLFW function and then casting it to GLAD type
        {
            std::cout << "Failed to Load GLAD" << std::endl;
            return nullptr;
        }
        return mainWindow;
    }

    glm::mat4 createProjectionMatrix(GLFWwindow* window)
    {
        int windowWidth, windowHeight;
        float aspectRatio;
        glm::mat4 projectionMatrix;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        if(windowWidth >= windowHeight)
        {
            aspectRatio = ((float)windowWidth/(float)windowHeight);
            return projectionMatrix = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
        }
        else
        {
            aspectRatio = ((float)windowHeight/(float)windowWidth);
            return projectionMatrix = glm::ortho(-1.0f, 1.0f, -aspectRatio, aspectRatio, -1.0f, 1.0f);
        }
    }

    void getAspectRatio(GLFWwindow* window, float &xBound, float &yBound)
    {
        int windowWidth, windowHeight;
        float aspectRatio;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        if(windowWidth >= windowHeight)
        {
            xBound = aspectRatio = ((float)windowWidth/(float)windowHeight);
            yBound = 1.0f;
        }
        else
        {
            yBound = aspectRatio = ((float)windowHeight/(float)windowWidth);
            xBound = 1.0f;
        }
    }

    #endif // WINDOWHANDLER_H