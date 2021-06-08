#ifndef __BULLET_H__
#define __BULLET_H__

#include <SFML/Graphics.hpp>

namespace AsteroidNS
{
class Bullet
{
	public:
		Bullet(int size = 5)
			:m_shape(size)
		{
			m_shape.setOrigin({ m_shape.getPosition().x + size, m_shape.getPosition().y + size });
		}

		void setPosition(const sf::Vector2i& pos)
		{
			m_shape.setPosition((sf::Vector2f)pos);
		}

		void setPosition(const sf::Vector2f& pos)
		{
			m_shape.setPosition(pos);
		}

		void render(sf::RenderWindow& w) const
		{
			w.draw(m_shape);
		}

	private:
		sf::CircleShape		m_shape;
		sf::Vector2f		m_direction;

};
}
#endif //__BULLET_H__
