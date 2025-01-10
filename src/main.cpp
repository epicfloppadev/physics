#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>
#define WINHEIGHT 1000
#define WINWIDTH 800
using namespace sf;
class object {
public:
    RectangleShape obj; // Declare the object
    Vector2f pos;

    bool physics = true;
    int momentum = 0;
    int collisioncoef = 0;
    bool immutable;
    object() : obj(Vector2f(100.f, 100.f)) {} // Initialize with default size

    void create(int x, int y, Color color, bool imm);
};

void object::create(int x, int y, Color color, bool imm) {
    pos = Vector2f(static_cast<float>(x), static_cast<float>(y)); // Set position
    obj.setPosition(pos); // Apply position to the rectangle
    obj.setFillColor(color); // Set the color
    immutable = imm;
}
std::vector <object> pool;
void pushing() {
    object obj; // Create an instance of the class
    int xPos, yPos;

    xPos = rand() % WINHEIGHT; // Generate random x-coordinate
    yPos = rand() % WINWIDTH;  // Generate random y-coordinate
    int imm = false;
    Color randomcolor = Color(rand() % 255, rand() % 255, rand() % 255);
    obj.create(xPos, yPos, randomcolor, imm); // Initialize the object
    
    pool.push_back(obj); // Add the object to the pool
}
int main()
{
    srand (time(NULL));
    // Create the window
    sf::RenderWindow window(sf::VideoMode({WINHEIGHT, WINWIDTH}), "My window");
   
    // Main loop
    while (window.isOpen())
    {
        // Event loop
        while (const std::optional event = window.pollEvent())
        {

            if (event->is<sf::Event::Closed>())
                window.close();
            else if(event->is<Event::MouseButtonPressed>())
            {
                pushing();
            }
        }
        // Clear the window
        window.clear(Color::Black);
        // Display the contents of the window
        for(int i = 0; i< pool.size(); i++)
        {
            window.draw(pool[i].obj);
        }
        window.display();
    }

    return 0;
}
