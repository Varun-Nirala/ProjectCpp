#ifndef __BATTLESHIP_H__
#define __BATTLESHIP_H__

#include <SFML/Graphics.hpp>

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
            ,m_headPos(headPos)
            ,m_size(size)
        {
            adjustPos();    // always call after changing head as it orient according to head

            // Color is fixed
            m_triangle[HEAD].color = sf::Color::Blue;
            m_triangle[LEFT].color = m_triangle[RIGHT].color = sf::Color::Red;
        }

        void setHead(const sf::Vector2i& head)
        {
            m_headPos = head;
            adjustPos();
        }

        void draw(sf::RenderWindow& w) const
        {
            w.draw(m_triangle);
        }

    private:
        void adjustPos()
        {
            m_triangle[HEAD].position = (sf::Vector2f)m_headPos;

            m_triangle[LEFT].position.x = (float)m_headPos.x - m_size;
            m_triangle[LEFT].position.y = (float)m_headPos.y + m_size;

            m_triangle[RIGHT].position.x = (float)m_headPos.x + m_size;
            m_triangle[RIGHT].position.y = (float)m_headPos.y + m_size;
        }

	private:
        sf::VertexArray     m_triangle;
        sf::Vector2i        m_headPos;
        int                 m_size;
};
}

#endif //__BATTLESHIP_H__