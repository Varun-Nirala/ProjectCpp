#include "Sprite.h"
#include "..\Engine\Common.h"

using namespace nsEngine;
using namespace nsEngine::nsMaths;
using namespace nsGraphics;
using namespace std;

Sprite::Sprite()
	: m_RotDegree(0.0)
	, m_Speed(nsCommon::gFPS)
{}

Sprite::Sprite(string &path)
	:Sprite()
{
	m_Texture = Texture(path);
}

Sprite::Sprite(string &path, double x, double y, double z)
	: Sprite(path)
{
	m_Vec3Pos = Vector3(x, y, z);
}

Sprite::Sprite(string &path, const Vector3 &VecPos)
	: Sprite(path)
{
	m_Vec3Pos = VecPos;
}

void Sprite::MoveTo(const Vector3 &vec)
{
	m_Vec3Pos = vec;
}

void Sprite::MoveBy(const Vector3 &vec)
{
	m_Vec3Pos += (vec * nsCommon::getElapsedTime());
}

void Sprite::RotateTo(double angle)
{
	m_RotDegree = angle;
}

void Sprite::RotateBy(double angle)
{
	m_RotDegree += (angle * nsCommon::getElapsedTime());
}

void Sprite::SetScale(const Vector3 &vec)
{
	m_Vec3Scale = vec;
}

void Sprite::SpeedTo(double x)
{
	m_Speed = x;
}

void Sprite::SpeedBy(double x)
{
	m_Speed += (x * nsCommon::getElapsedTime());
}

void Sprite::MoveUp()
{
	m_Vec3Pos.m_y += (m_Speed * nsCommon::getElapsedTime());
}

void Sprite::MoveDown()
{
	m_Vec3Pos.m_y -= (m_Speed * nsCommon::getElapsedTime());
}

void Sprite::MoveLeft()
{
	m_Vec3Pos.m_x -= (m_Speed * nsEngine::nsCommon::getElapsedTime());
}

void Sprite::MoveRight()
{
	m_Vec3Pos.m_x += (m_Speed * nsEngine::nsCommon::getElapsedTime());
}

void Sprite::Update()
{}

void Sprite::Render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_Texture.GetID());
	glLoadIdentity();

	// Transate, Rotate, Scale
	glTranslatef((GLfloat)m_Vec3Pos.m_x, (GLfloat)m_Vec3Pos.m_y, (GLfloat)m_Vec3Pos.m_z);
	glScalef((GLfloat)m_Vec3Scale.m_x, (GLfloat)m_Vec3Scale.m_x, (GLfloat)m_Vec3Scale.m_x);
	glRotatef((GLfloat)m_RotDegree, 0, 0, 1);

	//Rendering
	glColor4f(1, 1, 1, 1);

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0);
		glVertex2f(0, 0);

		glTexCoord2f(1, 0);
		glVertex2f((GLfloat)m_Texture.GetWidth(), 0);

		glTexCoord2f(1, 1);
		glVertex2f((GLfloat)m_Texture.GetWidth(), (GLfloat)m_Texture.GetHeight());

		glTexCoord2f(0, 1);
		glVertex2f(0, (GLfloat)m_Texture.GetHeight());
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}