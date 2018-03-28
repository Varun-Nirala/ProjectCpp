#include "Engine\Engine.h"
#include "Graphics\Sprite.h"

using namespace std;

int main(int argc, char *argv[])
{
	nsEngine::Engine gameEngine;
	gameEngine.Initialize("OpenGlWindow");

	nsGraphics::Sprite spriteCloud = nsGraphics::Sprite(string("Assets\\cloud.png"), 100, 100);

	while (1)
	{
		gameEngine.Update();
		spriteCloud.Update();

		gameEngine.BeginRender();
		spriteCloud.Render();
		gameEngine.EndRender();
	}

	return 0;
}