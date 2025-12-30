#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include <iostream>


// Vertex Shader
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 aPos;

uniform float scale;

void main() {
    vec2 scaledPos = aPos * scale;
    gl_Position = vec4(scaledPos, 0.0, 1.0);
}

)";

// Fragment Shader
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

uniform vec4 ourColor;

void main() {
    FragColor = ourColor;
}
)";

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Square - OpenGL macOS", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // ---------------- SHADERS ----------------
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // ---------------- SQUARE DATA ----------------
    float vertices[] = {
       0.0f, 0.5,   
       -0.5f,-0.5f,
       0.5f, -0.5f
    };

   unsigned int VAO, VBO;
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);

glBindVertexArray(VAO);

glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);


    // ---------------- RENDER LOOP ----------------
    while (!glfwWindowShouldClose(window)) {
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    int colorLoc = glGetUniformLocation(shaderProgram, "ourColor");
int scaleLoc = glGetUniformLocation(shaderProgram, "scale");

// ---- OUTLINE (BIGGER TRIANGLE) ----
glUniform1f(scaleLoc, 1.05f); // slightly bigger
glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f);
glDrawArrays(GL_TRIANGLES, 0, 3);

// ---- FILL (NORMAL TRIANGLE) ----
glUniform1f(scaleLoc, 1.0f);
glUniform4f(colorLoc, 0.0f, 1.0f, 0.0f, 1.0f);
glDrawArrays(GL_TRIANGLES, 0, 3);


    glfwSwapBuffers(window);
    glfwPollEvents();
}


    glfwTerminate();
    return 0;
}
