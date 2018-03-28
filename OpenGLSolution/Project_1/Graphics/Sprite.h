#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Texture.h"
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

		private:
			Texture		m_texture;
			float		m_fxPos;
			float		m_fyPos;
	};
}
#endif