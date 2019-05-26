/* Program to fill a beaker using scanline polygon filling */

#include<SFML/Graphics.hpp>

int main(){
    sf::VertexArray vertices(sf::LineStrip, 4);
    vertices[0].position = sf::Vector2f(100, 100);
    vertices[1].position = sf::Vector2f(100, 500);
    vertices[2].position = sf::Vector2f(450, 500);
    vertices[3].position = sf::Vector2f(450, 100);

    sf::RectangleShape line(sf::Vector2f(350, 1));
    line.setPosition(sf::Vector2f(100, 500));
    line.setFillColor(sf::Color::Cyan);

    sf::RenderWindow window(sf::VideoMode(600, 600), "Beaker");
    window.setFramerateLimit(20);
    window.clear();
    window.draw(vertices);
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type==sf::Event::Closed)
                window.close();
        if (line.getPosition().y > 130)
            line.move(0, -1);
        window.draw(line);
        window.display();
    }
    return 0;
}
