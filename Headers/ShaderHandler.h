#ifndef SHADERHANDLER_H
#define SHADERHANDLER_H

#include <glad/glad.h>

//! EDIT VERSION IN VERTEX AND SHADER CODE WHEN EDITING CODE
unsigned int createShaderProgram()
{
        const char* vertexShaderCode = R"(
    #version 460 core
    layout(location = 0) in vec2 vertexPositions;
    void main()
        {
            gl_Position = vec4(vertexPositions, 0.0f, 1.0f);
        }
    )";

    const char* fragmentShaderCode = R"(
    #version 460 core
    out vec4 pixelColors;
    void main()
        {
            pixelColors = vec4(1.0f, 1.0f, 1.0f, 1.0f);
        }
    )";

    //Creates Vertex Shader and connects it to the GL Vertex Outlet
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertexShader);

    //Creates Fragment Shader and connects it to the GL Fragment Outlet
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragmentShader);

    //Creats a Program that links both the Vertex and Fragment Shader Together
    unsigned int ShaderProgram = glCreateProgram();
    glAttachShader(ShaderProgram, vertexShader);
    glAttachShader(ShaderProgram, fragmentShader);
    glLinkProgram(ShaderProgram);
    return ShaderProgram;
}

unsigned int createTextureShaderProgram()
{
    const char* vertexShaderCode = R"(
    #version 460 core
    layout(location = 0) in vec2 vertexPositions;
    layout(location = 1) in vec2 texturePositions;
    out vec2 vertexToFragmentTexture;
    uniform mat4 projectionMatrix;
    uniform vec2 newPosVerticies;
    uniform vec2 newPosTexture;
    void main()
        {
            gl_Position = projectionMatrix * vec4(vertexPositions + newPosVerticies, 0.0f, 1.0f);
            vertexToFragmentTexture = texturePositions + newPosTexture;
        }
    )";

    const char* fragmentShaderCode = R"(
    #version 460 core
    out vec4 pixelColors;
    in vec2 vertexToFragmentTexture;
    uniform sampler2D textureData;
    void main()
        {
            pixelColors = texture(textureData, vertexToFragmentTexture);
        }
    )";

    //Creates Vertex Shader and connects it to the GL Vertex Outlet
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertexShader);

    //Creates Fragment Shader and connects it to the GL Fragment Outlet
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragmentShader);

    //Creats a Program that links both the Vertex and Fragment Shader Together
    unsigned int ShaderProgram = glCreateProgram();
    glAttachShader(ShaderProgram, vertexShader);
    glAttachShader(ShaderProgram, fragmentShader);
    glLinkProgram(ShaderProgram);
    return ShaderProgram;
}

#endif // SHADERHANDLER_H