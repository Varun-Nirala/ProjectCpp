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
			Sprite(std::string &path, float _x, float _y);

			void Update();
			void Render();

			// TRANSLATE
			void MoveTo(float x, float y);
			void MoveBy(float x, float y);

			// ROTATE
			void RotateTo(float angle);
			void RotateBy(float angle);

			// SCALE
			void SetScale(float x);
			void SetScale(float x, float y);

			// SPEED
			void SpeedTo(float x);
			void SpeedBy(float x);

			// MOVE left, right, up and down
			void MoveUp();
			void MoveDown();
			void MoveLeft();
			void MoveRight();

		private:
			Texture		m_texture;

			// TRANSLATE
			float		m_PosX;
			float		m_PosY;

			// ROTATE
			float		m_RotDegree;

			// SCALE
			float		m_ScaleX;
			float		m_ScaleY;

			// SPEED
			float		m_Speed;
	};
}
#endif