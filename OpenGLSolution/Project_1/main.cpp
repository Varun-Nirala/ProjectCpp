#include "Engine\Engine.h"
#include "Graphics\Sprite.h"
#include "Engine\IO\Mouse.h"
#include "Engine\IO\Keyboard.h"
#include "Engine\Maths\Vector3.h"

using namespace std;
using namespace nsEngine;
using namespace nsGraphics;

int main(int argc, char *argv[])
{
	Engine gameEngine;
	gameEngine.Initialize("OpenGlWindow");

	Sprite spriteCloud = Sprite(string("Assets\\cloud.png"), nsMaths::Vector3(gameEngine.GetWidth() - 500, gameEngine.GetHeight() - 200));
	Sprite spritePlane = Sprite(string("Assets\\Biplane.png"), nsMaths::Vector3());

	spriteCloud.SetScale(nsMaths::Vector3(0.25));
	spritePlane.SetScale(nsMaths::Vector3(0.25));

	Mouse *pMouse = Mouse::getInstance();
	Keyboard *pkeyBoard = Keyboard::getInstance();

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