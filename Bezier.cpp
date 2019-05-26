/* Program to draw N-order Bezier Curve and roll a circle on it which is to be controlled by keyboard */

#include<iostream>
#include<math.h>
#include<SFML/Graphics.hpp>

using namespace std;

long int nCr(int n, int r){
    long int num = 1, den = 1;
    for (int i = n-r+1; i <= n; i++)
        num *= i;
    for (int i = 1; i <= r; i++)
        den *= i;
    return num/den;
}

void BezierPoints(int n, sf::VertexArray P, int r, sf::VertexArray& points, vector<sf::Vector2f>& locus){
    double t = 0, cosa, sina;
    float x, y, dx, dy;
    double mul;
    int j = 0; 
    while (t <= 1){
        x = 0; y = 0; dx = 0; dy = 0; 
        for (int i=0; i<n; i++){
            mul = nCr(n-1, i) * pow(1-t, n-i-1) * pow(t, i);
            x += mul * P[i].position.x;
            y += mul * P[i].position.y;
            if (!((t == 0 && i == 0) || (i == n-1 && t == 1))){
                dx += P[i].position.x * nCr(n-1, i) * (i - (n-1)*t) * pow(1-t, n-i-2) * pow(t, i-1);
                dy += P[i].position.y * nCr(n-1, i) * (i - (n-1)*t) * pow(1-t, n-i-2) * pow(t, i-1);
            }
        }
        cosa = dy/pow(dx*dx + dy*dy, 0.5);
        sina = -dx/pow(dx*dx + dy*dy, 0.5);
        points[j].position = sf::Vector2f(x, y);
        locus.push_back( sf::Vector2f(x + r*cosa, y + r*sina) );
        j += 1;
        t += 0.01;
    }
}

int main(){
    int n;
    cout<<"No. of Ctrl Points: "; cin>>n;
    sf::VertexArray Control(sf::LineStrip, n);
    int x[2];
    for (int i=0; i<n; i++){
        cout<<"Pt."<<(i+1)<<" : "; cin >> x[0] >> x[1];
        Control[i].position =  sf::Vector2f(x[0], x[1]) ;
        Control[i].color = sf::Color::Cyan;
    }

    sf::VertexArray points(sf::LineStrip, 100);
    vector<sf::Vector2f> locus;
    BezierPoints(n, Control, 20, points, locus); 

    sf::RenderTexture Rtexture;
    Rtexture.create(40, 40);

    sf::Font sans;
    if (!sans.loadFromFile("FreeSansBold.ttf"))
    {
        printf("Error loading font\n");
        exit(0);
    }
    sf::Text text;
    text.setFont(sans);
    text.setString("  1  5\n  7  3");
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(15);

    sf::CircleShape circle(20);
    circle.setOrigin(20, 20);
    circle.move(20, 20);
    circle.setFillColor(sf::Color::Green);

    Rtexture.setSmooth(true);
    Rtexture.clear(sf::Color(0, 0, 0, 0));
    Rtexture.draw(circle);
    Rtexture.draw(text);
    Rtexture.display();

    sf::Sprite spr(Rtexture.getTexture());
    spr.setOrigin(sf::Vector2f(20, 20));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(600, 600), "Bezier Curve", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    int i = 0;
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            i = min(i+1, (int)locus.size()-1);
            spr.rotate(15.0f);
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            i = max(0, i-1);
            spr.rotate(-15.0f);
        }
        spr.setPosition(locus[i]);
        window.clear();
        window.draw(Control);
        window.draw(spr);
        window.draw(points);
        window.display();
    }

    return 0;
}
