#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "Texture.h"
#include "Star.h"
#include "Platform.h"
#include "Wall.h"
#include "TextRenderer.h"

// Constants
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;
const float screenLeft = -1.0f;
const float screenRight = 1.0f;
const float gravityAccel = 2.0f;
const float starGround = -0.9f;

// Globals
float lastFrameTime = 0.0f;
float posX = 0.0f, posY = -0.6f, speed = 1.0f;
int frameCount = 0;
float lastFPSUpdateTime = 0.0f;
int avgFPS = 0;

// Global pointers
Star* star = nullptr;
Platform* platform = nullptr;
TextRenderer* text = nullptr;


// Callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, float& x, float& y, float speed, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        y += speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        y -= speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        x -= speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        x += speed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        
        platform->ResetPlatform(); 
        star->ResetStar();
        
    }
}

int main() {
    // GLFW + OpenGL context
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "2DGameEngine", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // OpenGL settings
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


   //  GLuint VAO, VBO, EBO;
    
    // Shader and texture
    Shader shader("../shaders/vertex_shader.txt", "../shaders/fragment_shader.txt");
    Texture texture("../include/Images/clipart2634359.png");
    float aspectRatio = texture.GetAspectRatio();

    // Text rendering (FPS)
    text = new TextRenderer(WIDTH, HEIGHT);
    text->Load("/System/Library/Fonts/Avenir.ttc", 24);

    // Create star
    glm::vec2 starStartPos(0.0f, 0.7f);
    glm::vec2 starVel(0.1f, 0.9f);
    glm::vec2 starSize(0.5f, 0.05f);
    float gravity = 2.0f;

// Create multiple stars with different starting positions, velocities, etc.
    
      star = new Star(starStartPos, starVel, starSize, gravity);
    //star = new Star(starStartPos, starVel, starSize, gravity);
    
    // Create platform
    glm::vec2 platformPos(0.0f, -0.9f);  // Position (near the bottom)
    glm::vec2 platformSize(0.5f, 0.1f);  // Size (width = 1.0, height = 0.1)
    platform = new Platform(platformPos, platformSize);

    // Create left wall
    glm::vec2 wallPosLeft(-1.0f, 0.0f);  // Position (near the bottom)
    glm::vec2 wallSize(0.5f, 1.5f);  // Size (width = 1.0, height = 0.1)
    Wall* wallLeft = new Wall(wallPosLeft, wallSize);
    //right wall
    glm::vec2 wallPosRight(1.0f, 0.0f);  // Right wall
    glm::vec2 wallSizeRight(0.5f, 1.5f); 
    Wall* wallRight = new Wall(wallPosRight, wallSizeRight);

    // Game loop
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrameTime;
        lastFrameTime = currentFrame;
        frameCount++;

        // Update FPS every second
        if (currentFrame - lastFPSUpdateTime >= 1.0f) {
            avgFPS = frameCount;
            frameCount = 0;
            lastFPSUpdateTime = currentFrame;
        }

        // Input
        processInput(window, posX, posY, 1.0f, deltaTime);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);


        // Render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Draw Walls
        wallLeft->Draw(shader, texture, aspectRatio);
        wallRight->Draw(shader, texture, aspectRatio);
        // Draw star
       
        star->Update(deltaTime);
        star->Draw(shader, texture, aspectRatio, 1.0f, currentFrame * 1.0f);
        star->BounceIfCollidingWith(glm::vec2(posX, posY), platformSize);
    

        // Draw platform
        platform->Update(glm::vec2(posX, posY));
        platform->Draw(shader, texture, aspectRatio);

        processInput(window, posX, posY, speed, deltaTime);
        // Draw FPS
        text->RenderText("FPS: " + std::to_string(avgFPS), 10.0f, HEIGHT - 30.0f, 1.0f, glm::vec3(1.0f,1.0f,1.0f));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    //delete star;
     
    delete star;
    delete text;
    delete wallLeft;
    delete wallRight;
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
