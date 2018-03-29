#ifndef __VECTOR_3_H__
#define __VECTOR_3_H__

namespace nsEngine { namespace nsMaths
{
	class Vector3
	{
		public:
			Vector3(double x = 0, double y = 0, double z = 0);

			Vector3(const Vector3 &);				// Copyable
			Vector3(Vector3 &&);					// Moveable
			Vector3 operator=(const Vector3 &);		// assignable

			// Arithmatic Operators
			Vector3 operator+(const Vector3 &) const;
			Vector3 operator+(const double) const;

			Vector3 operator-(const Vector3 &) const;
			Vector3 operator-(const double) const;

			Vector3 operator*(const Vector3 &) const;
			Vector3 operator*(const double) const;

			Vector3 operator/(const Vector3 &) const;
			Vector3 operator/(const double) const;

			Vector3 operator++(int);		// Postfix
			Vector3 operator++();			// Prefix
			Vector3 operator--(int);		// Postfix
			Vector3 operator--();			// Prefix

			Vector3 operator+=(const Vector3 &);
			Vector3 operator+=(const double);

			Vector3 operator-=(const Vector3 &);
			Vector3 operator-=(const double);
			
			Vector3 operator*=(const Vector3 &);
			Vector3 operator*=(const double);

			Vector3 operator/=(const Vector3 &);
			Vector3 operator/=(const double);

			// Comparision Operators
			bool operator==(const Vector3 &);
			bool operator!=(const Vector3 &);

			bool operator<(const Vector3 &);
			bool operator<=(const Vector3 &);

			bool operator>=(const Vector3 &);
			bool operator>(const Vector3 &);

		public:
			double	m_x;
			double	m_y;
			double	m_z;
	};
}}
#endif