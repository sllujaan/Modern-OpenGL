#pragma once
#include"pch.h"
#include"GlfEvents.h"
//#define CHECK
bool windowReady = false;

#define WINDOW_READY GLF_WINDOW && !windowReady
#define WINDOW_IS_READY windowReady = true

int main2() {


	while (true)
	{
		if (SHOULD_CLOSE_ALL_THREADS) return 1;
		std::cout << "main2 is runing..." << GLF_WINDOW << std::endl;

		if (WINDOW_READY) {
			glfwSetKeyCallback(GLF_WINDOW, GLF_EVENTS::key_callback);
			WINDOW_IS_READY;
		}


		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}

	return 0;
}