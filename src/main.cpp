#include <iostream>
#include <cstring>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.hpp"
#include "mesh.hpp"
#include "shader.hpp"


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

    Windows::Window window(0, 0, "App", fullscreenMonitor, nullptr);
    window.MakeThisContext();


    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    float quadVertices[8] = {
        -1, -1,
        1, -1,
        -1, 1,
        1, 1
    };

    std::unique_ptr<float[]> quadBuffer = std::make_unique<float[]>(12);
    std::memcpy(quadBuffer.get(), quadVertices, 8);
    UniqueBuffer<float> vertices(8, std::move(quadBuffer));

    Mesh quadMesh(std::move(vertices));
    quadMesh.InitialiseBufferObjects();

    ShaderStage vertex("shaders/vertex.glsl", GL_VERTEX_SHADER);
    ShaderStage fragment("shaders/fragment.glsl", GL_FRAGMENT_SHADER);
    Shader program(vertex, fragment);
    //program.BindShader();

    // GAME EVENT LOOP.
    while (window.IsOpen()) {
        window.Update();
        quadMesh.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 8);



        glfwPollEvents();
    }

    quit();
    return 0;
}
