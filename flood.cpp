#include<SFML/Graphics.hpp>

void drawPoint(sf::Sprite sprite, sf::RenderWindow& window){
    sf::Event event;
    while (window.pollEvent(event))
        if (event.type == sf::Event::Closed)
            window.close();
    window.draw(sprite);
    window.display();
}

void floodFill(int x, int y, std::vector<sf::Uint8> &pixels, sf::RenderWindow &window)
{
    // sf::sleep(sf::milliseconds(50));
    window.display();
    if (x<0 || x>=400 || y<0 || y>=400)
        return;
    sf::Color col(pixels[4*(400*x+y)], pixels[4*(400*x+y)+1], pixels[4*(400*x+y)+2], pixels[4*(400*x+y)+3]);
    if (col==sf::Color::White || col==sf::Color::Cyan)
        return;
    sf::Uint32 color = sf::Color::Cyan.toInteger();
    pixels[4*(400*x+y) + 0] = (color >> 24);
    pixels[4*(400*x+y) + 1] = (color << 8) >> 24;
    pixels[4*(400*x+y) + 2] = (color << 16) >> 24;
    pixels[4*(400*x+y) + 3] = (color << 24) >> 24;
    sf::Texture texture;
    texture.update(&pixels[0]);
    sf::Sprite sprite;
    sprite.setTexture(texture, true);
    drawPoint(sprite, window);
    floodFill(x - 1, y - 1, pixels, window);
    floodFill(x + 1, y - 1, pixels, window);
    floodFill(x    , y - 1, pixels, window);
    floodFill(x - 1, y + 1, pixels, window);
    floodFill(x + 1, y + 1, pixels, window);
    floodFill(x    , y + 1, pixels, window);
    floodFill(x - 1, y    , pixels, window);
    floodFill(x + 1, y    , pixels, window);
}

int main(){
    sf::ConvexShape convex;
    convex.setPointCount(6);
    convex.setPoint(0, sf::Vector2f(0.f, 0.f));
    convex.setPoint(1, sf::Vector2f(150.f, 10.f));
    convex.setPoint(2, sf::Vector2f(120.f, 90.f));
    convex.setPoint(3, sf::Vector2f(30.f, 100.f));
    convex.setPoint(4, sf::Vector2f(0.f, 50.f));
    convex.move(100, 100);
    convex.scale(sf::Vector2f(1.8, 1.8));
    convex.setFillColor(sf::Color::Black);
    convex.setOutlineThickness(1);
    convex.setOutlineColor(sf::Color::White);

    sf::RenderTexture rtexture;
    rtexture.create(400, 400);
    rtexture.draw(convex);

    sf::Image image = rtexture.getTexture().copyToImage();
    std::vector<sf::Uint8> pixels(400 * 400 * 4);
    for (int i=0; i<400 * 400; i+=4){
            sf::Uint8 col = image.getPixel(i, i).toInteger();
            pixels.push_back((sf::Uint8)(col >> 24));
            pixels.push_back((sf::Uint8)((col << 8 ) >> 24));
            pixels.push_back((sf::Uint8)((col << 16) >> 24));
            pixels.push_back((sf::Uint8)((col << 24) >> 24));
    }
    sf::Texture texture;
    texture.update(&pixels[0]);
    sf::Sprite sprite;
    sprite.setTexture(texture, true);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(400, 400), "Flood Fill",sf::Style::Default ,settings);
    window.clear();
    bool done = false;
    // window.setFramerateLimit(20);
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        window.display();
        if (!done){
            // floodFill(310, 200, pixels, window);
            done = true;
        }
    }
    return 0;
}