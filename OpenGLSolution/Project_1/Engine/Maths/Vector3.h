#ifndef __VECTOR_3_H__
#define __VECTOR_3_H__

namespace nsEngine { namespace nsMaths
{
	class Vector3
	{
		public:
			Vector3(float x = 0, float y = 0, float z = 0);

			Vector3(const Vector3 &);				// Copyable
			Vector3(Vector3 &&);					// Moveable
			Vector3 operator=(const Vector3 &);		// assignable

			Vector3 operator+(const Vector3 &);
			Vector3 operator+(const float);

			Vector3 operator-(const Vector3 &);
			Vector3 operator-(const float);

			Vector3 operator*(const Vector3 &);
			Vector3 operator*(const float);

			Vector3 operator/(const Vector3 &);
			Vector3 operator/(const float);

			Vector3 operator++(int);		// Postfix
			Vector3 operator++();			// Prefix
			Vector3 operator--(int);		// Postfix
			Vector3 operator--();			// Prefix

			bool operator==(const Vector3 &);
			bool operator!=(const Vector3 &);

		public:
			float	m_x;
			float	m_y;
			float	m_z;
	};
}}
#endif