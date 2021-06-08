#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include <algorithm>
#include "BattleShip.h"
#include "Bullet.h"

namespace AsteroidNS
{
class Game
{
	public:
		Game(sf::RenderWindow &rw)
			:m_window(rw)
		{}

		void update()
		{
			// handle events
			sf::Event event;
			while (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					m_window.close();
				}

				sf::Vector2i mouse = sf::Mouse::getPosition(m_window);
				m_player.setPosition(mouse);

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					m_bullets.push_back(m_player.fire());
				}
			}
		}

		void render() const
		{
			m_window.clear();
			m_player.render(m_window);
			
			for (size_t i = 0; i < m_bullets.size(); ++i)
			{
				m_bullets[i]->render(m_window);
			}
		}

	private:
		sf::RenderWindow				&m_window;
		BattleShip						m_player;
		std::vector<Bullet *>			m_bullets;
};
}
#endif //__GAME_H__
