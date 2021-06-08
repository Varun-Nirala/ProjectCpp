#ifndef __BATTLESHIP_H__
#define __BATTLESHIP_H__

#include <SFML/Graphics.hpp>
#include "Bullet.h"

namespace AsteroidNS
{
class BattleShip
{
    enum Orient
    {
        LEFT,
        HEAD,
        RIGHT,
    };
    public:
        BattleShip(const sf::Vector2f& headPos = {0, 0}, int size = 50)
            :m_triangle(sf::Triangles, 3)
            ,m_originPos(headPos)
            ,m_size(size)
        {
            adjustPos();    // always call after changing head as it orient according to head

            // Color is fixed
            m_triangle[HEAD].color = sf::Color::Blue;
            m_triangle[LEFT].color = m_triangle[RIGHT].color = sf::Color::Red;
        }

        void setPosition(const sf::Vector2i& head)
        {
            m_originPos = head;
            adjustPos();
        }

        Bullet* fire() const
        {
            Bullet* b = new Bullet();
            b->setPosition(m_triangle[HEAD].position);
            return b;
        }

        void render(sf::RenderWindow& w) const
        {
            w.draw(m_triangle);
        }

    private:
        void adjustPos()
        {
            m_triangle[HEAD].position.x = m_originPos.x;
            m_triangle[HEAD].position.y = m_originPos.y - m_size;

            m_triangle[LEFT].position.x = m_originPos.x - m_size;
            m_triangle[LEFT].position.y = m_originPos.y + m_size;

            m_triangle[RIGHT].position.x = m_originPos.x + m_size;
            m_triangle[RIGHT].position.y = m_originPos.y + m_size;
        }

	private:
        sf::VertexArray     m_triangle;
        sf::Vector2i        m_originPos;
        int                 m_size;
};
}

#endif //__BATTLESHIP_H__