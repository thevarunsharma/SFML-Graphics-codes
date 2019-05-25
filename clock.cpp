#include<SFML/Graphics.hpp>
#include<stdio.h>

#define PI 3.141593

int main(){
    sf::CircleShape circle(300.0f);
    circle.setOrigin(300, 300);
    circle.setPosition(sf::Vector2f(400, 400));
    circle.setPointCount(1000);
    circle.setOutlineThickness(3);
    circle.setOutlineColor(sf::Color::White);
    circle.setFillColor(sf::Color(0, 0, 0, 0));

    sf::RectangleShape second(sf::Vector2f(1, 240));
    second.setOrigin(sf::Vector2f(1, 240));
    second.setPosition(sf::Vector2f(400, 400));
    
    sf::RectangleShape minute(sf::Vector2f(2, 290));
    minute.setOrigin(sf::Vector2f(2, 290));
    minute.setPosition(sf::Vector2f(400, 400));
    
    sf::RectangleShape hour(sf::Vector2f(3, 190));
    hour.setOrigin(sf::Vector2f(2, 190));
    hour.setPosition(sf::Vector2f(400, 400));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(800, 800), "CLOCK", sf::Style::Default, settings);
    window.setFramerateLimit(1);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            }
        
        window.clear();
        window.draw(circle);
        window.draw(second);
        window.draw(minute);
        window.draw(hour);
        window.display();
        second.rotate(6);
        minute.rotate(0.1);
        hour.rotate(1.0/60.0);
    }
    return 0;
}