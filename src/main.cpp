#include "header.hpp"
// std::vector<int> div[part + 1][part + 1];
int main()
{
    pushing(0,WINHEIGHT-1, WINWIDTH,100, 1);
    //std::cout<<pool[0].obj.getPosition().y<<' '<<pool[0].obj.getPosition().y;
    grav(pool[0]);
    
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
                if (pool[i].obj.getPosition().y > WINHEIGHT || pool[i].obj.getPosition().y < 0 )
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
                int Mousex,Mousey;
                Mousex = Mouse::getPosition(window).x;
                Mousey = Mouse::getPosition(window).y;
                pushing(Mousex,Mousey);
                grav(pool[pool.size() - 1]);
            }
        }
        window.clear(Color::Black);
        for (int i = 0; i < pool.size(); i++)
        {
            pool[i].obj.setPosition(pool[i].obj.getPosition() + Vector2f(0, float(pool[i].momentumy)));
            for(int j = i + 1; j<pool.size(); j++)
            {
                
                if(colision(pool[i], pool[j]) == 1)
                { 
                    pool[i].momentumx=pool[i].momentumy=0;
                    pool[j].momentumx=pool[j].momentumy=0; 
                   
                }
            }  
           
           
        }
        for(int i = 0; i<pool.size(); i++) window.draw(pool[i].obj);
        window.display();
    }

    return 0;
}
