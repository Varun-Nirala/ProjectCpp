#include "Sprite.h"

using namespace nsGraphics;
using namespace std;

Sprite::Sprite()
	: m_fxPos(0.0f)
	, m_fyPos(0.0f)
	, m_fRotDegree(0.0f)
	, m_fxScale(1.0f)
	, m_fyScale(1.0f)
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
	m_fxPos = _x;
	m_fyPos = _y;
}

void Sprite::SetPosX(float x)
{
	m_fxPos = x;
}

void Sprite::SetPosY(float y)
{
	m_fyPos = y;
}

void Sprite::SetRotation(float angle)
{
	m_fRotDegree = angle;
}

void Sprite::SetScale(float x)
{
	m_fxScale = m_fyScale = x;
}

void Sprite::SetScale(float x, float y)
{
	m_fxScale = x;
	m_fyScale = y;
}

void Sprite::Update()
{
	m_fRotDegree++;
}

void Sprite::Render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture.GetID());
	glLoadIdentity();

	// Transate, Rotate, Scale
	glTranslatef(m_fxPos, m_fyPos, 0);
	glScalef(m_fxScale, m_fyScale, 1);
	glRotatef(m_fRotDegree, 0, 0, 1);

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