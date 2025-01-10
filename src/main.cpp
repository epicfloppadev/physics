#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>
#define WINWIDTH 1000
#define WINHEIGHT 800
using namespace sf;
const int gravity = 10;
class object
{
public:
    RectangleShape obj;
    Vector2f pos;
    float mass = 0.5;
    bool physics = true;
    int momentum = 0;
    int collisioncoef = 0;
    bool immutable;
    object() : obj(Vector2f(100.f, 100.f)) {}
    void create(int x, int y, Color color, bool imm);
};

void object::create(int x, int y, Color color, bool imm)
{
    pos = Vector2f(static_cast<float>(x), static_cast<float>(y));
    obj.setPosition(pos);
    obj.setFillColor(color);
    immutable = imm;
}
void grav(object &o)
{
    o.momentum = gravity * o.mass;
}
std::vector<object> pool;

void pushing()
{
    object r;
    int xPos, yPos;
    int getsizex = WINWIDTH - r.obj.getSize().x, getsizey = WINHEIGHT - r.obj.getSize().y;
    xPos = rand() % getsizex;
    yPos = rand() % getsizey;
    int imm = false;
    Color randomcolor = Color(rand() % 255, rand() % 255, rand() % 255);
    r.create(xPos, yPos, randomcolor, imm);
    pool.push_back(r);
}

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

            std::cout<<pool[i].obj.getPosition().y<<'\n';
        }
        window.display();
    }

    return 0;
}
