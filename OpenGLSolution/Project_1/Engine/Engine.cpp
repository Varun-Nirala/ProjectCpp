#include "Engine.h"
#include <iostream>

using namespace std;
using namespace nsEngine;

Engine::Engine(int w, int h)
	: m_iWIDTH(w)
	, m_iHEIGHT(h)
	, m_pWindow(NULL)
{}

Engine::~Engine()
{
	glfwTerminate();
}

bool Engine::Initialize(char *windowTitle)
{
	if (!glfwInit())
	{
		cout << __LINE__ << " :: Error Initializing glfw." << endl;
		return false;
	}

	if (!(m_pWindow = glfwCreateWindow(m_iWIDTH, m_iHEIGHT, windowTitle, NULL, NULL)))
	{
		cout << __LINE__ << " :: Error creating window." << endl;
		glfwTerminate();
		return false;
	}

	// GLFW initial Setup Start
	glfwMakeContextCurrent(m_pWindow);

	int width, height;
	glfwGetFramebufferSize(m_pWindow, &width, &height);
	glfwSwapInterval(1);

	const GLFWvidmode *pVidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	int xPos, yPos;
	xPos = (pVidMode->width - m_iWIDTH) / 2;
	yPos = (pVidMode->height - m_iHEIGHT) / 2;
	glfwSetWindowPos(m_pWindow, xPos, yPos);
	// GLFW initial Setup END


	// OpenGL Setup Start
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -10, 10);
	glDepthRange(-10, 10);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// OpenGL Setup End

	return true;
}

void Engine::Update()
{
	glfwPollEvents();
}

void Engine::BeginRender()
{
	glClearColor(0, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::EndRender()
{
	glfwSwapBuffers(m_pWindow);
}

bool Engine::IsWindowClosed()
{
	return glfwWindowShouldClose(m_pWindow);
}

int Engine::GetWidth() const
{
	return m_iWIDTH;
}

int Engine::GetHeight() const
{
	return m_iHEIGHT;
}