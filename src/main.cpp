#include "header.hpp"

int main()
{
    sf::FloatRect inters;
    tex1.loadFromFile("Image/red.png");
    tex2.loadFromFile("Image/yellow.png");

    srand(time(NULL));
    RenderWindow window(sf::VideoMode({WINWIDTH, WINHEIGHT}), "Physics");

    std::vector<Object> obj; // 20 for failsafe
    Object obt(tex1, 0, 799);
    obt.mass = 1000000000000;
    obt.sprite.setScale({10, 8});
    obt.immobile = true;
    obj.push_back(obt);
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (event->is<Event::MouseButtonPressed>())
            {
                Vector2i mousePos = Mouse::getPosition(window);
                Vector2f mousePosF(static_cast<double>(mousePos.x), static_cast<double>(mousePos.y));
                Object obt(tex1, mousePosF.x, mousePos.y);
                obt.vx = rand() % 10 * (1 - 2 * int(rand() % 2));
                obt.vy = rand() % 10 * (1 - 2 * int(rand() % 2));
                obj.push_back(obt);
            }
        }

        window.clear();
        drawvec2(obj, window);
        for (int i = 0; i < obj.size(); i++)
        {
            for (int j = i + 1; j < obj.size(); j++)
            {
                if (obj[i].con2(obj[j]))
                {
                    obj[i].setTexture(tex2);
                    // aici vine formula complicata
                    ryc(obj[i], obj[j]);
                    rxc(obj[i], obj[j]);
                    obj[j].setTexture(tex2);
                }
            }
        }
        drawvec(obj, window);
        window.display();
    }

    return 0;
}
