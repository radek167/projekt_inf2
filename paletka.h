
#include <iostream>
#define sfml_paletka_h
#include <SFML/Graphics.hpp>

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
};
