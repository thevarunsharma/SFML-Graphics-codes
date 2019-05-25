#include<SFML/Graphics.hpp>
#include<math.h>

// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>

#define PI 3.141592654

class EllipseShape : public sf::Shape
{
public:
    explicit EllipseShape(const sf::Vector2f &radius = sf::Vector2f(0.f, 0.f)) : m_radius(radius)
    {
        update();
    }

    void setRadius(const sf::Vector2f &radius)
    {
        m_radius = radius;
        update();
    }

    const sf::Vector2f &getRadius() const
    {
        return m_radius;
    }
    
    virtual void setPointCount(std::size_t pc)
    {
        point_count = pc;  
        update(); 
    }
    
    virtual std::size_t getPointCount() const
    {
        return point_count; // fixed, but could be an attribute of the class if needed
    }

    virtual sf::Vector2f getPoint(std::size_t index) const
    {

        float angle = index * 2 * PI / getPointCount() - PI / 2;
        float x = cos(angle) * m_radius.x;
        float y = sin(angle) * m_radius.y;

        return sf::Vector2f(m_radius.x + x, m_radius.y + y);
    }

private:
    sf::Vector2f m_radius;
    std::size_t point_count = 30;
};

int main(){
    sf::CircleShape circle(150.0f, 50);
    circle.setOrigin(sf::Vector2f(150, 150));
    circle.setPosition(sf::Vector2f(200, 200));
    circle.setOutlineThickness(3);
    circle.setOutlineColor(sf::Color::Red);
    circle.setFillColor(sf::Color(0, 0, 0, 0));
    circle.setPointCount(100);
    
    EllipseShape ellipse1(sf::Vector2f(75, 150));
    ellipse1.setOrigin(sf::Vector2f(75, 150));
    ellipse1.setPosition(sf::Vector2f(200, 200));
    ellipse1.setOutlineThickness(3);
    ellipse1.setOutlineColor(sf::Color::Red);
    ellipse1.setFillColor(sf::Color(0, 0, 0, 0));
    ellipse1.setPointCount(100);

    EllipseShape ellipse2(sf::Vector2f(75, 150));
    ellipse2.setOrigin(sf::Vector2f(75, 150));
    ellipse2.setPosition(sf::Vector2f(200, 200));
    ellipse2.rotate(60.0f);
    ellipse2.setOutlineThickness(3);
    ellipse2.setOutlineColor(sf::Color::Red);
    ellipse2.setFillColor(sf::Color(0, 0, 0, 0));
    ellipse2.setPointCount(100);
    
    EllipseShape ellipse3(sf::Vector2f(75, 150));
    ellipse3.setOrigin(sf::Vector2f(75, 150));
    ellipse3.setPosition(sf::Vector2f(200, 200));
    ellipse3.rotate(-60.0f);
    ellipse3.setOutlineThickness(3);
    ellipse3.setOutlineColor(sf::Color::Red);
    ellipse3.setFillColor(sf::Color(0, 0, 0, 0));
    ellipse3.setPointCount(100);
    
    double cos60 = cos(60*PI/180.0), sin60 = sin(60*PI/180.0);
    float a = 75.0f, b = 150.0f;
    sf::CircleShape electron1(5), electron2(5), electron3(5);
    electron1.setOrigin(sf::Vector2f(5, 5));
    electron1.setFillColor(sf::Color::Red);
    electron2.setOrigin(sf::Vector2f(5, 5));
    electron2.setFillColor(sf::Color::Red);
    electron3.setOrigin(sf::Vector2f(5, 5));
    electron3.setFillColor(sf::Color::Red);

    // sf::VertexArray N(sf::LinesStrip, 4);
    // N[1].position = sf::Vector2f(150, 180);
    // N[0].position = sf::Vector2f(150, 220);
    // N[2].position = sf::Vector2f(170, 220);
    // N[3].position = sf::Vector2f(170, 180);

    // sf::VertexArray S(sf::LinesStrip, 6);
    // S[0].position = sf::Vector2f(175, 220);
    // S[1].position = sf::Vector2f(195, 220);
    // S[2].position = sf::Vector2f(195, 200);
    // S[3].position = sf::Vector2f(175, 200);
    // S[4].position = sf::Vector2f(175, 180);
    // S[5].position = sf::Vector2f(195, 180);

    // sf::VertexArray U(sf::LinesStrip, 4);
    // U[0].position = sf::Vector2f(205, 180);
    // U[1].position = sf::Vector2f(205, 220);
    // U[2].position = sf::Vector2f(225, 220);
    // U[3].position = sf::Vector2f(225, 180);

    // sf::VertexArray T(sf::LinesStrip, 5);
    // T[0].position = sf::Vector2f(235, 180);
    // T[1].position = sf::Vector2f(245, 180);
    // T[2].position = sf::Vector2f(245, 220);
    // T[3].position = sf::Vector2f(245, 180);
    // T[4].position = sf::Vector2f(255, 180);

    sf::Font sans;
    if (!sans.loadFromFile("FreeSansBold.ttf"))
    {
        printf("Error loading font\n");
        exit(0);
    }
    sf::Text text;
    text.setFont(sans);
    text.setFillColor(sf::Color::Red);
    text.setString("NSUT");
    text.setCharacterSize(40);
    text.setPosition(sf::Vector2f(145, 175));

    float th = 0;
    sf::ContextSettings setting;
    setting.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(400, 400), "NSUT", sf::Style::Default, setting);
    window.setFramerateLimit(15);
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type==sf::Event::Closed)
                window.close();

        float x = a*cos(th), y = b*sin(th);
        th += 0.1;
        electron1.setPosition(sf::Vector2f(200 + x, 200 + y));
        electron2.setPosition(sf::Vector2f(200 -( x*cos60 - y*sin60), 200 -( x*sin60 + y*cos60)));
        electron3.setPosition(sf::Vector2f(200 -( x*cos60 + y*sin60), 200 -( -x*sin60 + y*cos60)));

        window.clear(sf::Color::White);
        window.draw(circle);
        window.draw(ellipse1);
        window.draw(ellipse2);
        window.draw(ellipse3);
        window.draw(electron1);
        window.draw(electron2);
        window.draw(electron3);
        // window.draw(N);
        // window.draw(S);
        // window.draw(U);
        // window.draw(T);
        window.draw(text);
        window.display();
    }
    return 0;
}
