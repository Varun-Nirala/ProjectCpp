#include "Vector3.h"

using namespace nsEngine::nsMaths;

Vector3::Vector3(float x, float y, float z)
	: m_x(x)
	, m_y(y)
	, m_z(z)
{}

Vector3::Vector3(const Vector3 &vec)
	: m_x(vec.m_x)
	, m_y(vec.m_y)
	, m_z(vec.m_z)
{}

Vector3::Vector3(Vector3 &&vec)
	: m_x(vec.m_x)
	, m_y(vec.m_y)
	, m_z(vec.m_z)
{
	vec.m_x = vec.m_y = vec.m_z = 0;
}

Vector3 Vector3::operator=(const Vector3 &vec)
{
	if (this == &vec)
	{
		return *this;
	}
	m_x = vec.m_x;
	m_y = vec.m_y;
	m_z = vec.m_z;
}

Vector3 Vector3::operator+(const Vector3 &vec)
{
	Vector3 ret(*this);
	ret.m_x += vec.m_x;
	ret.m_y += vec.m_y;
	ret.m_z += vec.m_z;

	return ret;
}

Vector3 Vector3::operator+(const float val)
{
	Vector3 ret(*this);
	ret.m_x += val;
	ret.m_y += val;
	ret.m_z += val;

	return ret;
}

Vector3 Vector3::operator-(const Vector3 &vec)
{
	Vector3 ret(*this);
	ret.m_x -= vec.m_x;
	ret.m_y -= vec.m_y;
	ret.m_z -= vec.m_z;

	return ret;
}

Vector3 Vector3::operator-(const float val)
{
	Vector3 ret(*this);
	ret.m_x -= val;
	ret.m_y -= val;
	ret.m_z -= val;

	return ret;
}

Vector3 Vector3::operator*(const Vector3 &vec)
{
	Vector3 ret(*this);
	ret.m_x *= vec.m_x;
	ret.m_y *= vec.m_y;
	ret.m_z *= vec.m_z;

	return ret;
}

Vector3 Vector3::operator*(const float val)
{
	Vector3 ret(*this);
	ret.m_x *= val;
	ret.m_y *= val;
	ret.m_z *= val;

	return ret;
}

Vector3 Vector3::operator/(const Vector3 &vec)
{
	Vector3 ret(*this);
	ret.m_x /= vec.m_x;
	ret.m_y /= vec.m_y;
	ret.m_z /= vec.m_z;

	return ret;
}

Vector3 Vector3::operator/(const float val)
{
	Vector3 ret(*this);
	ret.m_x /= val;
	ret.m_y /= val;
	ret.m_z /= val;

	return ret;
}

Vector3 Vector3::operator++()
{
	m_x++;
	m_y++;
	m_z++;
	return *this;
}

Vector3 Vector3::operator++(int)
{
	Vector3 ret(*this);
	m_x++;
	m_y++;
	m_z++;

	return ret;
}

Vector3 Vector3::operator--()
{
	m_x--;
	m_y--;
	m_z--;
	return *this;
}

Vector3 Vector3::operator--(int)
{
	Vector3 ret(*this);
	m_x--;
	m_y--;
	m_z--;

	return ret;
}