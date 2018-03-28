#include "Engine\Engine.h"
#include "Graphics\Sprite.h"

using namespace std;

int main(int argc, char *argv[])
{
	nsEngine::Engine gameEngine;
	gameEngine.Initialize("OpenGlWindow");

	nsGraphics::Sprite spriteCloud = nsGraphics::Sprite(string("Assets\\cloud.png"), 300, 300);
	nsGraphics::Sprite spritePlane = nsGraphics::Sprite(string("Assets\\Biplane.png"), 50, 50);

	while (!gameEngine.IsWindowClosed())
	{
		gameEngine.Update();
		spriteCloud.Update();
		spritePlane.Update();

		gameEngine.BeginRender();
		spriteCloud.Render();
		spritePlane.Render();
		gameEngine.EndRender();
	}

	return 0;
}