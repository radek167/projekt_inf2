#define sfml_paletka_h
#ifndef PALETKA_H
#define PALETKA_H
#include <SFML/Graphics.hpp>
#include <iostream>
class Paletka {
    private :
    float x;
    float y;
    float szerokosc;
    float wysokosc;
    float predkosc;
    sf::RectangleShape shape;
public:
    Paletka(float startX, float startY, float szer, float wys, float pred)
        : x(startX), y(startY), szerokosc(szer), wysokosc(wys), predkosc(pred) {
        shape.setSize({szerokosc, wysokosc});
        shape.setOrigin(sf::Vector2f(szerokosc / 2, wysokosc / 2));
        shape.setPosition(sf::Vector2f(x, y));
        shape.setFillColor(sf::Color::Blue);
    };
    void moveLeft() {
        x = x - predkosc;
        shape.setPosition(sf::Vector2f(x, y));
    }
    void moveRight() {
        x = x + predkosc;
        shape.setPosition(sf::Vector2f(x, y));
    }
    void clampToBounds(float width) {
        if (x - szerokosc / 2 < 0) {
            x = szerokosc / 2;
        }
        if (x + szerokosc / 2 > width) {
            x = width - szerokosc / 2;
        }
        shape.setPosition(sf::Vector2f(x, y));
    }
    void draw(sf::RenderTarget &target) {
        target.draw(shape);
    }
    float getX() const {
        return x;
    }
    float getY() const{
        return y;
    }
    float getSzerokosc() const {
        return szerokosc;
    }
    float getWysokosc() const {
        return wysokosc;
    }
    void setPosition(float newX, float newY) {
        x = newX;
        y = newY;
        shape.setPosition(sf::Vector2f(x, y));
    }
    void reset(float startX, float startY) {
        x = startX;
        y = startY;
        shape.setPosition(sf::Vector2f(x, y));
    }
};
#endif //PALETKA_H
