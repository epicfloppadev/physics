#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>
#define WINWIDTH 1000
#define WINHEIGHT 800
#define part 10
using namespace sf;
const int gravity = 10;
class object
{
public:
    RectangleShape obj;
    Vector2f pos;
    float mass = 0.5;
    bool physics = true;
    float momentumx=0,momentumy = 0;
    int collisioncoef = 0;
    bool immutable = false;
    object() : obj(Vector2f(100.f, 100.f)) {}
    void create(int x, int y, Color color, bool imm, int Xsize, int Ysize);
};

void object::create(int x, int y, Color color, bool imm = true, int Xsize=100, int Ysize=100)
{
    pos = Vector2f(static_cast<float>(x), static_cast<float>(y));
    obj.setSize({static_cast<float>(Xsize), static_cast<float>(Ysize)});
    std::cout<<pos.y;
    obj.setPosition(pos);
    obj.setFillColor(color);
    immutable = imm;
}
void grav(object &o)
{
    o.momentumy = gravity * (1-o.immutable);
}
std::vector<object> pool;
void pushing(int Xpos = -1, int Ypos = -1, int Xsize = 100, int Ysize = 100, bool imm = false)
{
    object r;

    int getsizex = WINWIDTH - Xsize;
    int getsizey = WINHEIGHT - Ysize;

    if (Xpos == -1 || Ypos == -1)
    {
        Xpos = rand() % getsizex;
        Ypos = rand() % getsizey;
    }

    Color randomcolor(rand() % 256, rand() % 256, rand() % 256);

    r.create(Xpos, Ypos, randomcolor, imm, Xsize, Ysize);


    pool.push_back(r);
}

bool colision(object &o1, object &o2)
{
    if(o1.obj.getGlobalBounds().findIntersection(o2.obj.getGlobalBounds())) 
    {
        if(o1.obj.getPosition().y<o2.obj.getPosition().y)
        {
            o1.obj.setPosition(Vector2f(o1.obj.getPosition().x, o2.obj.getPosition().y) + Vector2f(0,float(-o1.obj.getSize().y)));
        }
        else
        {
            o2.obj.setPosition(Vector2f(o2.obj.getPosition().x, o1.obj.getPosition().y)+ Vector2f(0,float(-o2.obj.getSize().y)));
        }
        return 1;
    }
    return 0;
}