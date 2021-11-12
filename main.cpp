#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "stdafx.h"
#include <cmath>
using namespace std;
int w = 600, h= 600;
float a = -10, b = 10;
float c = -10, d = 10;
float t = 0, dt = 0.001;
sf::RenderWindow window(sf::VideoMode(w, h), "Func graph", sf::Style::Default);
sf::View view;
float transform_x(float x)
{
    return (x-a)/(b-a)*w;
}
float transform_y(float y)
{
    return (y-d)/(c-d)*h;
}

void drawLine(float x1, float y1, float x2, float y2, sf::Color color = sf::Color::White){
    sf::Vertex line[] =
            {
            sf::Vertex(sf::Vector2f(transform_x(x1), transform_y(y1)), color),
            sf::Vertex(sf::Vector2f(transform_x(x2), transform_y(y2)), color)

            };
    window.draw(line, 2, sf::Lines);
}
float f(float x){
    //return logf(powf(5*M_PI*(x+9), sinf(5*(x+9)))) * 0.5 * asinf(cosf(5*M_PI*(x+2*sinf(t/2))-M_PI/2));
    //return t*sin(x*t);
    return cos(x/3)*sin(x*t) + t;
}
float OX(float x){
    return x = 0;
}
float OY(float y){
    return y = 0;
}
void drawdash(){
    drawLine(a, 0, b, 0, sf::Color::Red);
    drawLine(0, c, 0, d, sf::Color::Red);
    float dash = (int)a + 1;
    float dash_len = 3.;
    while(dash <= b){
        drawLine(dash, -dash_len*(c-d)/h, dash, dash_len*(c-d)/h, sf::Color::White);
        dash += 1;
    }
    dash = (int)c + 1;
    while(dash<=d)
    {
        drawLine(-dash_len*(b-a)/w, dash, dash_len*(d-c)/w,dash,  sf::Color::White);
        dash += 1;
    }
}
void draw(){
    float x=a, prev_x;
    float dx=0.1;
    drawdash();
    //[a, b] -> [0, w]
    //a-> 0, b -> w => x -> x' => (x-a)/(b-a) * w
    //c-> h, d -> 0
    //[c, d] -> [h, 0] => y -> y => (y-d)/(c-d) *h
    while(x<=b){
        prev_x = x;
        x += dx;
        drawLine(prev_x, f(prev_x), x, f(x));
        /*drawLine((prev_x - a)/(b-a)*w, (f(prev_x)-d)/(c-d)*h, (x-a)/(b-a)*w, (f(x)-d)/(c-d)*h);
        drawLine((prev_x - a)/(b-a)*w, (OX(prev_x)-d)/(c-d)*h, (x-a)/(b-a)*w, (OX(x)-d)/(c-d)*h);
        drawLine((OY(prev_x) - a)/(b-a)*w, (prev_x-d)/(c-d)*h, (OY(x)-a)/(b-a)*w, (x-d)/(c-d)*h);*/

    }
}
void move()
{
    if (t > 5 || t < -5) {
        dt = -dt;
    }
    t += dt;
}

int main(){
    srand(time(0));
    view.reset(sf::FloatRect(a, c, b-a, d-c));
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        //check for movement keys pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
            {
                //move up
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            //move down
            view.move(1.0f, 0.0f);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
            {
                //move left
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            //right
            view.move(0.0, 1.0);
        }
        window.clear();
        draw();
        move();
        window.display();
    }
    return 0;
}
