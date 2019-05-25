#include<SFML/Graphics.hpp>
#include<math.h>

#define PI 3.141592654

class EllipseShape : public sf::Shape{
public:
    explicit EllipseShape(const sf::Vector2f &radius = sf::Vector2f(0.f, 0.f)) : m_radius(radius){
        update();
    }

    void setRadius(const sf::Vector2f &radius){
        m_radius = radius;
        update();
    }

    const sf::Vector2f &getRadius() const{
        return m_radius;
    }

    virtual std::size_t getPointCount() const{
        return 30; // fixed, but could be an attribute of the class if needed
    }

    virtual sf::Vector2f getPoint(std::size_t index) const{
        static const float pi = 3.141592654f;

        float angle = index * 2 * pi / getPointCount() - pi / 2;
        float x = cos(angle) * m_radius.x;
        float y = sin(angle) * m_radius.y;

        return sf::Vector2f(m_radius.x + x, m_radius.y + y);
    }

private:
    sf::Vector2f m_radius;
};

int main(){
    double a = 70, b = 50;
    EllipseShape ellipse(sf::Vector2f(a, b));
    ellipse.setOrigin(sf::Vector2f(a, b));
    sf::RectangleShape rect(sf::Vector2f(800, 2));
    rect.setPosition(sf::Vector2f(0, 300));
    ellipse.setPosition(sf::Vector2f(a, 300-b));

    double th = 0, inc = 3*PI/180., alpha;
    float dx = 100, xn;
    sf::RenderWindow window(sf::VideoMode(800, 400), "Rollll");
    window.setFramerateLimit(10);
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(ellipse);
        window.draw(rect);
        window.display();
        xn = a/sin(th);
        if (isnan(xn)){
            ellipse.setOrigin(sf::Vector2f(a*cos(th), 0));
            ellipse.rotate(90);
            ellipse.setOrigin(sf::Vector2f(a, b));
            ellipse.setPosition(sf::Vector2f(dx, 300));
        }
        else{
            alpha = -atan(b/a*tan(th));
            ellipse.setOrigin(sf::Vector2f(xn, 0));
            ellipse.rotate(alpha);
            ellipse.setOrigin(sf::Vector2f(a, b));
            ellipse.setPosition(sf::Vector2f(xn, 300));
        }
        printf("%lf %lf\n", ellipse.getPosition().x, ellipse.getPosition().y);
        dx += 1;
        th += inc;

    }
    return 0;
}