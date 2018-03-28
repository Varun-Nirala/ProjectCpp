#include "Engine\Engine.h"

using namespace std;

int main(int argc, char *argv[])
{
	nsEngine::Engine gameEngine;

	gameEngine.Initialize("OpenGlWindow");

	while (1)
	{
		gameEngine.Update();
		gameEngine.Render();
	}

	return 0;
}