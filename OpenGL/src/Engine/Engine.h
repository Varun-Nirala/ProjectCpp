#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <GLFW\glfw3.h>

#pragma comment(lib, "opengl32.lib")

namespace nsEngine
{
	class Engine
	{
		public:
			Engine(int w = 1024, int h = 768);
			~Engine();

			bool Initialize(char *windowTitle);

			void Update();
			void Render();
		private:
			GLFWwindow		*m_pWindow;
			const int		m_iWIDTH;
			const int		m_iHEIGHT;
	};
}
#endif