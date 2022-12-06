#include "WindowSystem.h"
#include "Project Config/Config.h"

namespace paperback::system::window
{
    void Instance::Init(void) noexcept
    {
		if (!glfwInit())
		{
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

		// Create Window
		m_WindowHandle = glfwCreateWindow( config::WINDOW_WIDTH, config::WINDOW_HEIGHT
										 , config::WINDOW_NAME, nullptr, nullptr );

		// Unable To Create Window - Terminate Program
		if (!m_WindowHandle)
		{
			glfwTerminate();
			std::exit(EXIT_FAILURE);
		}

		//// Automatic Cleanup Callback
		//auto window_close_callback = [](GLFWwindow* window)
		//{
		//	glfwSetWindowShouldClose(window, GLFW_TRUE);
		//};

		//glfwSetWindowCloseCallback(m_WindowHandle, window_close_callback);
		glfwMakeContextCurrent(m_WindowHandle);
		glfwSwapInterval(0);
		glfwSetInputMode(m_WindowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

	void Instance::InitVulkan(void) noexcept
	{
		// Purely Optional - Provides Information To Driver To Optimize Our Application
		VkApplicationInfo ApplicationInfo{};
		ApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		ApplicationInfo.pApplicationName = config::WINDOW_NAME;
		ApplicationInfo.applicationVersion = VK_MAKE_VERSION(1, 3, 231);
		ApplicationInfo.pEngineName = config::WINDOW_NAME;
		ApplicationInfo.engineVersion = VK_MAKE_VERSION(1, 3, 231);
		ApplicationInfo.apiVersion = VK_API_VERSION_1_3;

		// Extend Vulkan Information
		VkInstanceCreateInfo CreateInfo{};
		CreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		CreateInfo.pApplicationInfo = &ApplicationInfo;

		// Specify Global Extensions
		uint32_t GlfwExtensionCount = 0;
		const char** GlfwExtensions;
		GlfwExtensions = glfwGetRequiredInstanceExtensions(&GlfwExtensionCount);
		CreateInfo.enabledExtensionCount = GlfwExtensionCount;				// Specify Desired Global Validation Layers To Enable
		CreateInfo.ppEnabledExtensionNames = GlfwExtensions;				// Specify Desired Global Extensions
		CreateInfo.enabledLayerCount = 0;

		// Check For Extension Support
		uint32_t ExtensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &ExtensionCount, nullptr);				// Get Total Extension Count
		std::vector<VkExtensionProperties> Extensions(ExtensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &ExtensionCount, Extensions.data());	// Query Extension Details

		// Print All Required Extensions If Debug Mode
		if (_DEBUG)
		{
			std::cout << "Required Vulkan Extensions:" << std::endl;
			for (const auto& Ext : Extensions)
			{
				std::cout << Ext.extensionName << std::endl;
			}
		}

		// Create Vulkan Instance
		if (vkCreateInstance(&CreateInfo, nullptr, &m_VkInstance) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create instance!");
		}
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
		vkDestroyInstance(m_VkInstance, nullptr);
		glfwDestroyWindow(m_WindowHandle);
		glfwTerminate();
    }
}