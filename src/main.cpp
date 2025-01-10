#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>
#define WINHEIGHT 1000
#define WINWIDTH 800
using namespace sf;

class object {
public:
    RectangleShape obj;
    Vector2f pos;
    bool physics = true;
    int momentum = 0;
    int collisioncoef = 0;
    bool immutable;
    object() : obj(Vector2f(100.f, 100.f)) {}
    void create(int x, int y, Color color, bool imm);
};

void object::create(int x, int y, Color color, bool imm) {
    pos = Vector2f(static_cast<float>(x), static_cast<float>(y));
    obj.setPosition(pos);
    obj.setFillColor(color);
    immutable = imm;
}

std::vector<object> pool;

void pushing() {
    object obj;
    int xPos, yPos;
    xPos = rand() % WINHEIGHT;
    yPos = rand() % WINWIDTH;
    int imm = false;
    Color randomcolor = Color(rand() % 255, rand() % 255, rand() % 255);
    obj.create(xPos, yPos, randomcolor, imm);
    pool.push_back(obj);
}

int main() {
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode({WINHEIGHT, WINWIDTH}), "My window");

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (event->is<Event::MouseButtonPressed>()) {
                pushing();
            }
        }
        window.clear(Color::Black);
        for (int i = 0; i < pool.size(); i++) {
            window.draw(pool[i].obj);
        }
        window.display();
    }

    return 0;
}
