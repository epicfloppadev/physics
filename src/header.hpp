#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#define WINWIDTH 1000
#define WINHEIGHT 800
#define part 5
#define m !o1.immoble
using namespace sf;
const float ct = 0.8;
const float gravity = 0.1;
Texture tex1("Image/red.png"), tex2("Image/yellow.png");
sf::Color getRandomColor()
{
    return sf::Color(
        rand() % 256,
        rand() % 256,
        rand() % 256);
}
class Object
{
public:
    Sprite sprite;
    float mass = 1;
    float vx = 0.1f, vy = 0.1f; // suficient pentru coliziuni
    bool immobile = false;
    Object(const Texture &tex = tex1, float x = 0.f, float y = 0.f) : sprite(tex)
    {
        sprite.setPosition({x, y});
    }

    void draw(RenderWindow &window)
    {
        window.draw(sprite);
    }

    bool con(Vector2f point) // contains point
    {
        return sprite.getGlobalBounds().contains(point);
    }
    bool con2(const Object &other) const // contains 4 sprite
    {
        auto rect1 = sprite.getGlobalBounds();
        auto rect2 = other.sprite.getGlobalBounds();
        return rect1.findIntersection(rect2).has_value();
    }
    void setTexture(const Texture &tex)
    {
        sprite.setTexture(tex);
    }
};
void drawvec(std::vector<Object> &v, sf::RenderWindow &window)
{
    window.draw(v[0].sprite);
    for (auto i = 1; i < v.size(); i++)
    {
        v[i].vy += gravity;
        v[i].sprite.move({!v[i].immobile * v[i].vx, !v[i].immobile * v[i].vy});
        window.draw(v[i].sprite);
    }
}
// folosit chatgpt pe ideea mea asa ca na
void ryc(Object &o1, Object &o2)
{
    constexpr float ct = 0.8f;
    constexpr float epsilon = 0.1f;

    const auto &rect1 = o1.sprite.getGlobalBounds();
    const auto &rect2 = o2.sprite.getGlobalBounds();

    const auto intersection = rect1.findIntersection(rect2);
    if (!intersection.has_value())
        return;

    const float overlapY = intersection->size.y;

    float moveAmount = (overlapY / 2.0f) + epsilon;

    if (rect1.position.y < rect2.position.y)
    {
        if (!o1.immobile)
            o1.sprite.move(sf::Vector2f(0.f, -moveAmount));
        if (!o2.immobile)
            o2.sprite.move(sf::Vector2f(0.f, moveAmount));
    }
    else
    {
        if (!o1.immobile)
            o1.sprite.move(sf::Vector2f(0.f, moveAmount));
        if (!o2.immobile)
            o2.sprite.move(sf::Vector2f(0.f, -moveAmount));
    }

    const float m1 = o1.mass;
    const float m2 = o2.mass;
    const float v1y = o1.vy;
    const float v2y = o2.vy;

    const float new_v1y = (v1y * (m1 - m2) + 2.f * m2 * v2y) / (m1 + m2);
    const float new_v2y = (v2y * (m2 - m1) + 2.f * m1 * v1y) / (m1 + m2);

    if (!o1.immobile)
        o1.vy = new_v1y * ct;
    if (!o2.immobile)
        o2.vy = new_v2y * ct;
}
// la fel
void rxc(Object &o1, Object &o2)
{
    float m1 = o1.mass, m2 = o2.mass;
    float v1x = o1.vx, v2x = o2.vx;

    float x1 = o1.sprite.getPosition().x;
    float x2 = o2.sprite.getPosition().x;

    // Only respond if moving toward each other horizontally
    if ((v1x - v2x) * (x1 - x2) < 0)
    {
        float new_v1x = (v1x * (m1 - m2) + 2 * m2 * v2x) / (m1 + m2);
        float new_v2x = (v2x * (m2 - m1) + 2 * m1 * v1x) / (m1 + m2);

        o1.vx = new_v1x * (1 - o1.immobile) * ct;
        o2.vx = new_v2x * (1 - o2.immobile) * ct;
    }
}
