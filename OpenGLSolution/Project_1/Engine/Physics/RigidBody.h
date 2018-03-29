#ifndef __RIGID_BODY_H__
#define __RIGID_BODY_H__

#include "..\Maths\Vector3.h"

namespace nsEngine { namespace nsPhysics
{
	class RigidBody
	{
		public:
			RigidBody();

			void Initialize(const nsEngine::nsMaths::Vector3 &pos, 
							const nsEngine::nsMaths::Vector3 &scale,
							const double rotation,
							const nsEngine::nsMaths::Vector3 &velocity,
							const double gravity,
							const double friction);

			void Update();
			void Render();

		private:
			nsEngine::nsMaths::Vector3	m_Vec3Pos;
			nsEngine::nsMaths::Vector3	m_Vec3Scale;
			double						m_RotDegree;

			nsEngine::nsMaths::Vector3	m_Vec3Velocity;
			double						m_Gravity;
			double						m_Friction;
	};
}}
#endif