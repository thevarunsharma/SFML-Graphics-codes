#include<stdio.h>
#include<SFML/Graphics.hpp>

class Point{
public:
    Point(int x, int y) : x(x), y(y){}
    int x=0, y=0;
};

class Line{
public:
    Line(Point p1, Point p2) : p1(p1), p2(p2) {}
    Point p1, p2;
};

class Rectangle{
public:
    Rectangle(int top, int left, int bottom, int right):
    top(top), left(left), bottom(bottom), right(right){}
    int top, left, bottom, right;
};

void drawLine(Line line, sf::RenderTexture &texture){
    // sf::sleep(sf::milliseconds(1000));
    sf::Vertex lineVec[] = { sf::Vector2f(line.p1.x, line.p1.y),
                          sf::Vector2f(line.p2.x, line.p2.y) };
    texture.draw(lineVec, 2, sf::Lines);
    texture.display();
    return;
}

short getCode(Point p, Rectangle rect){
    int code = 0b0000;
    if (p.x < rect.left)   code |= 0b0001;
    if (p.x > rect.bottom) code |= 0b0100;
    if (p.x > rect.right)  code |= 0b0010;
    if (p.x < rect.top)    code |= 0b1000;
    return code;
}

void MidPointSubdiv(Line line, Rectangle rect, sf::RenderTexture& texture){
    Point p1 = line.p1, p2 = line.p2;
    short code1 = getCode(p1, rect), code2 = getCode(p2, rect);
    printf("%d %d \n", code1, code2);
    if ( code1 == 0b0000 && code2 == 0b0000 ){
        printf("%d %d %d %d\n", p1.x, p1.y, p2.x, p2.y);
        // drawLine(line, texture);
        return;
    }
    short res = code1 & code2;
    // printf("res %d\n", res);
    // printf("%d %d %d %d\n", p1.x, p1.y, p2.x, p2.y);
    if (res != 0b0000){
        printf("Reject % d % d % d % d\n ", p1.x, p1.y, p2.x, p2.y);
        return;
    }
    // else clipping needed 
    Point mp((p1.x + p2.x)/2.0, (p1.y + p2.y)/2.0);

    MidPointSubdiv(Line(p1, mp), rect, texture);
    MidPointSubdiv(Line(mp, p2), rect, texture);
    return;
}

int main(){
    sf::RenderWindow window(sf::VideoMode(400, 400), "MPSD");
    Line line(Point(50, 40), Point(250, 300));
    Rectangle rect(100, 100, 200, 200);

    sf::RenderTexture rtexture;
    rtexture.create(400, 400);

    sf::RectangleShape shape(sf::Vector2f(100, 100));
    shape.setPosition(sf::Vector2f(100, 100));
    shape.setFillColor(sf::Color(0, 0, 0, 0));
    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::Yellow);

    rtexture.clear();
    rtexture.draw(shape);
    MidPointSubdiv(line, rect, rtexture);

    // while (window.isOpen()){
    //     window.clear();
    //     window.draw(sf::Sprite(rtexture.getTexture()));
    //     window.display();
    //     // MidPointSubdiv(line, rect, window);
    //     // while (window.isOpen()){
    //         sf::Event event;
    //         while (window.pollEvent(event))
    //             window.display();
    //             if (event.type == sf::Event::Closed)
    //                 window.close();
    //     // }
    // }
}
