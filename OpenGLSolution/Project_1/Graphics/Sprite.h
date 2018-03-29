#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Texture.h"
#include "..\Engine\Maths\Vector3.h"
#include <iostream>

namespace nsGraphics
{
	class Sprite
	{
		public:
			Sprite();
			Sprite(std::string &path);
			Sprite(std::string &path, double x, double y, double z = 1);
			Sprite(std::string &path, const nsEngine::nsMaths::Vector3 &VecPos);

			void Update();
			void Render();

			// TRANSLATE
			void MoveTo(const nsEngine::nsMaths::Vector3 &);
			void MoveBy(const nsEngine::nsMaths::Vector3 &);

			// ROTATE
			void RotateTo(double angle);
			void RotateBy(double angle);

			// SCALE
			void SetScale(const nsEngine::nsMaths::Vector3 &);

			// SPEED
			void SpeedTo(double x);
			void SpeedBy(double x);

			// MOVE left, right, up and down
			void MoveUp();
			void MoveDown();
			void MoveLeft();
			void MoveRight();

		private:
			Texture						m_Texture;

			// TRANSLATE
			nsEngine::nsMaths::Vector3	m_Vec3Pos;

			// ROTATE
			double						m_RotDegree;

			// SCALE
			nsEngine::nsMaths::Vector3	m_Vec3Scale;

			// SPEED
			double						m_Speed;
	};
}
#endif