#include<SFML/Graphics.hpp>
#include<stdio.h>

int main(){
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!");
    float r = 100.f;
    sf::CircleShape shape(r);
    shape.setOrigin(sf::Vector2f(-180.0f, -100.0f)); 
    shape.setFillColor(sf::Color::Green);
    window.setFramerateLimit(30);
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
        shape.setRadius(r-2.0f);
        sf::Vector2f origin = shape.getOrigin();
        shape.setOrigin(sf::Vector2f(origin.x- 2.0f, origin.y - 2.0f));
        r = shape.getRadius();
        if (r<=0)
            window.close();
    }

    return 0;
}
/*compile as:
$ g++ -c test.cpp
$ g++ test.o -o test -lsfml-graphics -lsfml-window -lsfml-system
*/