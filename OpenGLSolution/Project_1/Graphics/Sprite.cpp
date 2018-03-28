#include "Sprite.h"

using namespace nsGraphics;
using namespace std;

Sprite::Sprite()
	: m_fxPos(0.0)
	, m_fyPos(0.0)
	, m_texture(Texture())
{}

Sprite::Sprite(string &path)
{
	m_texture = Texture(path);
	m_fxPos = 0.0;
	m_fyPos = 0.0;
}

Sprite::Sprite(string &path, float _x, float _y)
{
	m_texture = Texture(path);
	m_fxPos = _x;
	m_fyPos = _y;
}

void Sprite::Update()
{}

void Sprite::Render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture.GetID());
	glLoadIdentity();

	// Transate, Rotate, Scale
	glTranslatef(m_fxPos, m_fyPos, 0);

	//Rendering
	glColor4f(1, 1, 1, 1);

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0);
		glVertex2f(-1, -1);

		glTexCoord2f(1, 0);
		glVertex2f(m_texture.GetWidth()/2, -1);

		glTexCoord2f(1, 1);
		glVertex2f(m_texture.GetWidth()/2, m_texture.GetHeight()/2);

		glTexCoord2f(0, 1);
		glVertex2f(-1, m_texture.GetHeight()/2);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}