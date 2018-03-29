#ifndef __COMMON_H__
#define __COMMON_H__

#include <GLFW\glfw3.h>

namespace nsEngine
{
	double const PIXEL_PER_SECOND = 5;
	double const FPS = 60 * PIXEL_PER_SECOND;

	static double getElapsedTime()
	{
		static double lastTime = 0;
		double dt = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();
		return dt;
	}
}
#endif