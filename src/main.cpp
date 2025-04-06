#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>

// Window dimensions
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

// Callback function to adjust viewport when resizing
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Set OpenGL version (4.1 Core Profile, since versions above 4.1 are not supported)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "2D Game Engine", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Load OpenGL functions using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // Set the OpenGL viewport
    glViewport(0, 0, WIDTH, HEIGHT);

    // Enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader shader("../shaders/vertex_shader.txt", "../shaders/fragment_shader.txt");

    // Generate texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load texture and get its aspect ratio
    stbi_set_flip_vertically_on_load(true);
    int texWidth, texHeight, nrChannels;
    unsigned char* data = stbi_load("../include/Images/clipart2634359.png", &texWidth, &texHeight, &nrChannels, 0);
    if (data) {
    GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, texWidth, texHeight, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    std::cout << "Texture loaded successfully: " << texWidth << "x" << texHeight << " with " << nrChannels << " channels" << std::endl;
    } else {
    std::cerr << "Failed to load texture: " << stbi_failure_reason() << std::endl;
    }
    stbi_image_free(data);

    // Calculate texture aspect ratio
    float aspectRatio = (float)texWidth / (float)texHeight;

    // Define triangle vertices with the texture aspect ratio applied to the x positions
    float vertices[] = {
        // positions                // colors             // tex coords
        -0.5f * aspectRatio,  0.5f,     1.0f, 0.0f, 0.0f,   0.0f, 1.0f, // Top-left
         0.5f * aspectRatio,  0.5f,     0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // Top-right
         0.5f * aspectRatio, -0.5f,     0.0f, 0.0f, 1.0f,   1.0f, 0.0f, // Bottom-right
        -0.5f * aspectRatio, -0.5f,     1.0f, 1.0f, 0.0f,   0.0f, 0.0f  // Bottom-left
    };

    // Index data for triangles
    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3,
    };

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
     

    glBindVertexArray(VAO);

    // Bind and fill array buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind and fill element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO
    glBindVertexArray(0); // Unbind VAO

    // Set the texture uniform in the shader
    shader.use();
    shader.setUniform1i("texture1", 1); // Use texture unit 0 (set 2nd parameter to 1  
                                                    //  to use texture in fragment shader)

    // Game loop
    while (!glfwWindowShouldClose(window)) {
        // Process input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // Rendering
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Set background color
        glClear(GL_COLOR_BUFFER_BIT);         // Clear screen

        // Update transform matrix each frame
        float speed = 2.0f;
        float angle = glfwGetTime() * speed; // Time-based rotation
        float cosA = cos(angle);
        float sinA = sin(angle);
        float scale = 1.0f;
        float x = 0.0f, y = 0.0f;

        float transform[] = {
            cosA * scale,  sinA * scale, 0.0f, 0.0f,  // rotates object by angle radians.
        -sinA * scale,  cosA * scale, 0.0f, 0.0f,   // scales it by scale (shrinks or enlarges).
            0.0f,          0.0f,         1.0f, 0.0f,
            x,             y,            0.0f, 1.0f
        };

        shader.use();
        int loc = glGetUniformLocation(shader.ID, "transform");
        glUniformMatrix4fv(loc, 1, GL_FALSE, transform);

        // Activate texture unit 0 and bind texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        // Draw the object
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
