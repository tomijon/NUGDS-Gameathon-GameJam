#pragma once

class GLFWmonitor;
class GLFWwindow;

namespace Windows {
	enum class WindowMode {
		FULLSCREEN,
		BORDERLESS,
		WINDOWED,
		ERROR,
		CLOSED
	};


	class Window {
	public:
		Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
		~Window();

		void SetWindowMode(WindowMode targetMode);
		void SetFullscreenMonitor(int monitorIndex);
		void MakeThisContext();

		void Update();
		bool IsOpen();

	private:
		void SetFullscreen();
		void SetBorderless();
		void SetWindowed();
		void SetWindow(GLFWwindow* newWindow);

		GLFWwindow* window;
		GLFWwindow* shared;
		GLFWmonitor* monitor;

		WindowMode mode;
	};
}
