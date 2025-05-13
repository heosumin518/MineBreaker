#include "GameApp.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>


//int main() {
//    if (!glfwInit()) {
//        std::cerr << "GLFW 초기화 실패\n";
//        return -1;
//    }
//
//    GLFWwindow* window = glfwCreateWindow(800, 600, "Mine Breaker", nullptr, nullptr);
//    if (!window) {
//        std::cerr << "윈도우 생성 실패\n";
//        glfwTerminate();
//        return -1;
//    }
//
//    glfwMakeContextCurrent(window);
//
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//        std::cerr << "Failed to initialize GLAD\n";
//        return -1;
//    }
//
//    int major = 0, minor = 0;
//    glGetIntegerv(GL_MAJOR_VERSION, &major);
//    glGetIntegerv(GL_MINOR_VERSION, &minor);
//    std::cout << "OpenGL Version: " << major << "." << minor << std::endl;
//
//    while (!glfwWindowShouldClose(window)) {
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    glfwDestroyWindow(window);
//    glfwTerminate();
//    return 0;
//}
