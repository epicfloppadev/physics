#include "header.hpp"
int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode({WINWIDTH, WINHEIGHT}), "Physics");
    window.setFramerateLimit(60);
    Clock clock;
    clock.start();
    while (window.isOpen())
    {
        if (clock.getElapsedTime() >= seconds(1))
        {
            for (int i = 0; i < pool.size(); i++)
            {
                if (pool[i].obj.getPosition().y > WINHEIGHT)
                    pool.erase(pool.begin() + i);
            }
            clock.restart();
        }
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (event->is<Event::MouseButtonPressed>())
            {
                pushing();
                grav(pool[pool.size() - 1]);
            }
        }
        window.clear(Color::Black);
        for (int i = 0; i < pool.size(); i++)
        {
            pool[i].obj.setPosition(pool[i].obj.getPosition() + Vector2f(0, float(pool[i].momentum)));
            window.draw(pool[i].obj);

            std::cout << pool[i].obj.getPosition().y << '\n';
        }
        window.display();
    }

    return 0;
}
