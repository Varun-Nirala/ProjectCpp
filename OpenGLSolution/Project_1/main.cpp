#include "Engine\Engine.h"
#include "Graphics\Sprite.h"
#include "Engine\IO\Mouse.h"
#include "Engine\IO\Keyboard.h"

using namespace std;

int main(int argc, char *argv[])
{
	nsEngine::Engine gameEngine;
	gameEngine.Initialize("OpenGlWindow");

	nsGraphics::Sprite spriteCloud = nsGraphics::Sprite(string("Assets\\cloud.png"), gameEngine.GetWidth() - 500, gameEngine.GetHeight() - 200);
	nsGraphics::Sprite spritePlane = nsGraphics::Sprite(string("Assets\\Biplane.png"), 0, 0);

	spriteCloud.SetScale(0.25f);
	spritePlane.SetScale(0.25f);

	nsEngine::Mouse *pMouse = nsEngine::Mouse::getInstance();
	nsEngine::Keyboard *pkeyBoard = nsEngine::Keyboard::getInstance();

	if (!pMouse)
	{
		cout << __LINE__ << " ::Error: mouse instance returned NULL." << endl;
		return -1;
	}

	while (!gameEngine.IsWindowClosed())
	{
		gameEngine.Update();
		spriteCloud.Update();
		spritePlane.Update();

		if (pkeyBoard->Key(GLFW_KEY_W))			// Up
		{
			spritePlane.MoveUp();
			spritePlane.RotateBy(1);
			spritePlane.SpeedBy(1);
		}
		else if (pkeyBoard->Key(GLFW_KEY_S))	// Down
		{
			spritePlane.MoveDown();
			spritePlane.RotateBy(-1);
			spritePlane.SpeedBy(-1);
		}
		else if (pkeyBoard->Key(GLFW_KEY_A))	// Left
		{
			spritePlane.MoveLeft();
			spritePlane.SpeedBy(-2);
		}
		else if (pkeyBoard->Key(GLFW_KEY_D))	// Right
		{	
			spritePlane.MoveRight();
			spritePlane.SpeedBy(2);
		}

		gameEngine.BeginRender();
		spriteCloud.Render();
		spritePlane.Render();
		gameEngine.EndRender();
	}

	return 0;
}