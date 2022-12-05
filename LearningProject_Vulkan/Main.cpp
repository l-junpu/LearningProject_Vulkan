#include "Window System/WindowSystem.h"

int main()
{
	paperback::system::window::Instance window_inst;

	std::cout << "System Launched" << std::endl;

	window_inst.Init();
	window_inst.Update();

	std::cout << "System Terminated" << std::endl;
}