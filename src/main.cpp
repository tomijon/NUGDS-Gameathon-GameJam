#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.hpp"


const int TARGET_MONITOR = 0;


void quit() {
    glfwTerminate();
}


int main(int argc, char* argv[]) {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    int numMonitors;
    GLFWmonitor** monitors = glfwGetMonitors(&numMonitors);

    if (numMonitors <= 0) {
        std::cerr << "Failed to find a monitor.\n";
        return -1;
    }

    GLFWmonitor* fullscreenMonitor = monitors[TARGET_MONITOR];
    const GLFWvidmode* monitorMeta = glfwGetVideoMode(fullscreenMonitor);

    /*GLFWwindow* window = glfwCreateWindow(monitorMeta->width, monitorMeta->height, "", fullscreenMonitor, nullptr);
    if (!window) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }*/

    Windows::Window window(0, 0, "App", fullscreenMonitor, nullptr);
    window.MakeThisContext();


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    while (window.IsOpen()) {
        window.Update();

        glfwPollEvents();
    }

    quit();
    return 0;
}
