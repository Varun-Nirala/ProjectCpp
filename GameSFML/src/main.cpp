#include <iostream>
#include <fstream>
#include <cstring>

#include <SFML/Graphics.hpp>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(512, 256), "Particles");

    // create a clock to track the elapsed time
    sf::Clock clock;

    sf::CircleShape circle(30.0f);
    // run the main loop
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // make the particle system emitter follow the mouse
        sf::Vector2i mouse = sf::Mouse::getPosition(window);

        circle.setPosition(mouse.x, mouse.y);

        // update it
        sf::Time elapsed = clock.restart();

        // draw it
        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}