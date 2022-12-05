#include "WindowSystem.h"
#include "Project Config/Config.h"

namespace paperback::system::window
{
    void Instance::Init(void) noexcept
    {
		if (!glfwInit())
		{
			// PPB_ERR_PRINT_N_LOG("GLFW init has failed - Aborting");
			std::exit(EXIT_FAILURE);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
		glfwWindowHint(GLFW_RED_BITS, 8); glfwWindowHint(GLFW_GREEN_BITS, 8);
		glfwWindowHint(GLFW_BLUE_BITS, 8); glfwWindowHint(GLFW_ALPHA_BITS, 8);
		glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

		m_WindowHandle = glfwCreateWindow(config::WINDOW_WIDTH, config::WINDOW_HEIGHT, config::WINDOW_NAME, NULL, NULL);

		if (!m_WindowHandle)
		{
			glfwTerminate();
			std::exit(EXIT_FAILURE);
		}

		auto window_close_callback = [](GLFWwindow* window)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		};

		glfwSetWindowCloseCallback(m_WindowHandle, window_close_callback);
		glfwMakeContextCurrent(m_WindowHandle);
		glfwSwapInterval(0);
		glfwSetInputMode(m_WindowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		// Fullscreen
		//glfwSetWindowMonitor(m_WindowHandle, glfwGetPrimaryMonitor(), 0, 0, config::WINDOW_WIDTH, config::WINDOW_HEIGHT, GLFW_DONT_CARE);
    }

    void Instance::Update(void) noexcept
    {
		while (!glfwWindowShouldClose(m_WindowHandle))
		{
			glfwSwapBuffers(m_WindowHandle);
			glfwPollEvents();
		}
    }

    void Instance::Free(void) noexcept
    {

    }
}