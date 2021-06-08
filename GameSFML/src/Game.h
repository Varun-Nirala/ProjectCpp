#ifndef __GAME_H__
#define __GAME_H__

#include "BattleShip.h"

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
			sf::Vector2i mouse = sf::Mouse::getPosition(m_window);
			m_player.setHead(mouse);
		}

		void render() const
		{
			m_window.clear();
			m_player.draw(m_window);
		}

	private:
		sf::RenderWindow			&m_window;
		BattleShip					m_player;
};
}
#endif //__GAME_H__
