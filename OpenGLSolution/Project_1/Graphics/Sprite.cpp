#include "Sprite.h"
#include "..\Engine\Common.h"

using namespace nsGraphics;
using namespace std;

Sprite::Sprite()
	: m_PosX(0.0f)
	, m_PosY(0.0f)
	, m_RotDegree(0.0f)
	, m_ScaleX(1.0f)
	, m_ScaleY(1.0f)
	, m_Speed(nsEngine::FPS)
{
}

Sprite::Sprite(string &path)
	:Sprite()
{
	m_texture = Texture(path);
}

Sprite::Sprite(string &path, float _x, float _y)
	: Sprite(path)
{
	m_PosX = _x;
	m_PosY = _y;
}

void Sprite::MoveTo(float x, float y)
{
	m_PosX = x;
	m_PosY = y;
}

void Sprite::MoveBy(float x, float y)
{
	m_PosX += (x * nsEngine::getElapsedTime());
	m_PosY += (y * nsEngine::getElapsedTime());
}

void Sprite::RotateTo(float angle)
{
	m_RotDegree = angle;
}

void Sprite::RotateBy(float angle)
{
	m_RotDegree += (angle * nsEngine::getElapsedTime());
}

void Sprite::SetScale(float x)
{
	m_ScaleX = m_ScaleY = x;
}

void Sprite::SetScale(float x, float y)
{
	m_ScaleX = x;
	m_ScaleY = y;
}

void Sprite::SpeedTo(float x)
{
	m_Speed = x;
}

void Sprite::SpeedBy(float x)
{
	m_Speed += (x * nsEngine::getElapsedTime());
}

void Sprite::MoveUp()
{
	m_PosY += (m_Speed * nsEngine::getElapsedTime());
}

void Sprite::MoveDown()
{
	m_PosY -= (m_Speed * nsEngine::getElapsedTime());
}

void Sprite::MoveLeft()
{
	m_PosX -= (m_Speed * nsEngine::getElapsedTime());
}

void Sprite::MoveRight()
{
	m_PosX += (m_Speed * nsEngine::getElapsedTime());
}

void Sprite::Update()
{}

void Sprite::Render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture.GetID());
	glLoadIdentity();

	// Transate, Rotate, Scale
	glTranslatef(m_PosX, m_PosY, 0);
	glScalef(m_ScaleX, m_ScaleY, 1);
	glRotatef(m_RotDegree, 0, 0, 1);

	//Rendering
	glColor4f(1, 1, 1, 1);

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0);
		glVertex2f(0, 0);

		glTexCoord2f(1, 0);
		glVertex2f(m_texture.GetWidth(), 0);

		glTexCoord2f(1, 1);
		glVertex2f(m_texture.GetWidth(), m_texture.GetHeight());

		glTexCoord2f(0, 1);
		glVertex2f(0, m_texture.GetHeight());
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}