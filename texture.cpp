#include<SFML/Graphics.hpp>
#include<stdio.h>
#include<stdlib.h>

int main(){
    sf::Texture texture;
    if (!(texture.loadFromFile("sun-horizon.jpg", sf::IntRect(400, 400, 700, 600)))){
        printf("Couldn't load image file\n");
        exit(0);
    }
    sf::RenderTexture Rtexture;
    Rtexture.create(60, 60);
    
    sf::CircleShape circle(30.0);
    circle.setTexture(&texture);

    sf::Font sans;
    if (!sans.loadFromFile("FreeSansBold.ttf"))
    {
        printf("Error loading font\n");
        exit(0);
    }
    sf::Text text;
    text.setFont(sans);
    text.setString("  1  5\n  7  3");
    text.setCharacterSize(20);

    Rtexture.setSmooth(true);
    Rtexture.clear(sf::Color(0, 0, 0, 0));
    Rtexture.draw(circle);
    Rtexture.draw(text);
    Rtexture.display();
    
    sf::Sprite spr(Rtexture.getTexture());
    spr.setOrigin(sf::Vector2f(30, 30));
    spr.setPosition(sf::Vector2f(230, 230));
    
    sf::RectangleShape rect(sf::Vector2f(300, 200));
    rect.setPosition(200, 200);
    rect.setOutlineColor(sf::Color(0, 220, 220));
    rect.setOutlineThickness(5);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Sprite and Texture", sf::Style::Default, settings);
    window.setFramerateLimit(30);

    while (window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            spr.rotate(-15.0f);
            spr.move(sf::Vector2f(-5, 0));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            spr.rotate(15.0f);
            spr.move(sf::Vector2f(5, 0));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            spr.rotate(-15.0f);
            spr.move(sf::Vector2f(0, -5));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            spr.rotate(15.0f);
            spr.move(sf::Vector2f(0, 5));
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            spr.scale(sf::Vector2f(1.15, 1.15));
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            spr.scale(sf::Vector2f(0.85, 0.85));

        window.clear();
        window.draw(rect);
        window.draw(spr);
        window.display();
        // sf::Vector2f org = spr.getPosition();
        // if (org.x == 230)
        //     if (org.y == 370)
        //         spr.move(sf::Vector2f( 5, 0));
        //     else
        //         spr.move(sf::Vector2f( 0, 5));
        // else if (org.x == 470)
        //     if (org.y == 230)
        //         spr.move(sf::Vector2f(-5, 0));
        //     else
        //         spr.move(sf::Vector2f(0, -5));
        // else if (org.y == 230)
        //     spr.move(sf::Vector2f(-5, 0));
        // else if (org.y == 370)
        //     spr.move(sf::Vector2f( 5, 0));
    }
    return 0;
}