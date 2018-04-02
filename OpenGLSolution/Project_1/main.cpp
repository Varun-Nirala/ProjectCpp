#include "Engine\Engine.h"
#include "Graphics\Sprite.h"
#include "Engine\Common.h"
#include "Engine\IO\Mouse.h"
#include "Engine\IO\Keyboard.h"
#include "Engine\Maths\Vector3.h"
#include "Engine\Physics\RigidBody.h"

using namespace std;
using namespace nsEngine;
using namespace nsGraphics;

int main(int argc, char *argv[])
{
	Engine gameEngine;
	gameEngine.Initialize("OpenGlWindow");

	Sprite spriteCloud = Sprite(string("Assets\\cloud.png"), nsMaths::Vector3(gameEngine.GetWidth() - 500, gameEngine.GetHeight() - 200));
	Sprite spritePlane = Sprite(string("Assets\\Biplane.png"), nsMaths::Vector3());

	spriteCloud.SetScale(nsMaths::Vector3(0.25, 0.25, 0.25));
	spritePlane.SetScale(nsMaths::Vector3(0.25, 0.25, 0.25));

	nsPhysics::RigidBody rbPlan;
	rbPlan.Initialize(&spritePlane, nsCommon::gGRAVITY, nsCommon::gFRICTION);

	/*Mouse *pMouse = Mouse::getInstance();
	if (!pMouse)
	{
		cout << __LINE__ << " ::Error: mouse instance returned NULL." << endl;
		return -1;
	}*/
	
	Keyboard *pkeyBoard = Keyboard::getInstance();
	if (!pkeyBoard)
	{
		cout << __LINE__ << " ::Error: keyboard instance returned NULL." << endl;
		return -1;
	}

	
	nsMaths::Vector3 planeForce;
	rbPlan.AddForce(planeForce);

	while (!gameEngine.IsWindowClosed())
	{
		gameEngine.Update();
		spriteCloud.Update();
		spritePlane.Update();
		rbPlan.Update();

		double speed = 5;

		if (pkeyBoard->Key(GLFW_KEY_W))			// Up
		{
			spritePlane.IncrementRotation(1);
			planeForce.m_y += speed;
		}
		else if (pkeyBoard->Key(GLFW_KEY_S))	// Down
		{
			spritePlane.IncrementRotation(-1);
			planeForce.m_y -= speed;
		}
		else if (pkeyBoard->Key(GLFW_KEY_A))	// Left
		{
			planeForce.m_x -= speed;
		}
		else if (pkeyBoard->Key(GLFW_KEY_D))	// Right
		{
			planeForce.m_x += speed;
		}

		rbPlan.AddForce(planeForce);

		gameEngine.BeginRender();
		spriteCloud.Render();
		spritePlane.Render();
		rbPlan.Render(nsMaths::Vector3(0, 0, 0));
		gameEngine.EndRender();
	}

	return 0;
}