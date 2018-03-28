#include "Engine\Engine.h"
#include "Graphics\Sprite.h"
#include "Engine\IO\Mouse.h"

using namespace std;

int main(int argc, char *argv[])
{
	nsEngine::Engine gameEngine;
	gameEngine.Initialize("OpenGlWindow");

	nsGraphics::Sprite spriteCloud = nsGraphics::Sprite(string("Assets\\cloud.png"), gameEngine.GetWidth() - 500, gameEngine.GetHeight() - 200);
	nsGraphics::Sprite spritePlane = nsGraphics::Sprite(string("Assets\\Biplane.png"), 0, 0);

	spriteCloud.SetScale(0.25f);
	spritePlane.SetScale(0.25f);

	nsEngine::Mouse *mouse = nsEngine::Mouse::getInstance();
	if (!mouse)
	{
		cout << __LINE__ << " ::Error: mouse instance returned NULL." << endl;
		return -1;
	}

	while (!gameEngine.IsWindowClosed())
	{
		gameEngine.Update();
		spriteCloud.Update();
		spritePlane.Update();

		spritePlane.SetPosX(mouse->GetPosX());
		spritePlane.SetPosY(mouse->GetPosY());

		gameEngine.BeginRender();
		spriteCloud.Render();
		spritePlane.Render();
		gameEngine.EndRender();
	}

	return 0;
}