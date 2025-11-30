
#include <iostream>

#define sfml_pilka_h
#ifndef PILKA_H
#define PILKA_H

#include <SFML/Graphics.hpp>
#include "paletka.h"

class Pilka {
private:
    float x;
    float y;
    float vx;
    float vy;
    float radius;

public:
    sf::CircleShape shape;
    Pilka(float startX, float startY, float startVx, float startVy, float r)
        : x(startX), y(startY), vx(startVx), vy(startVy), radius(r) {
        shape.setRadius(radius);
        shape.setOrigin(sf::Vector2f(radius, radius));
        shape.setPosition(sf::Vector2f(x, y));
        shape.setFillColor(sf::Color::Red);
    }
    void move() {
        x = x + vx;
        y = y + vy;
        shape.setPosition(sf::Vector2f(x, y));
    }
    void bounceX() {
        vx = -vx;
    }
    void bounceY() {
        vy = -vy;
    }
    void collideWalls(float width, float height) {
        if (x - radius < 0 || x + radius > width) {
            bounceX();
        }
        if (y - radius < 0) {
            bounceY();
        }
    }
    bool collidePaddle(const Paletka& pal) {
        float palX = pal.getX();
        float palY = pal.getY();
        float palW = pal.getSzerokosc();
        float palH = pal.getWysokosc();

        if (x >= palX - palW / 2.0f &&
            x <= palX + palW / 2.0f &&
            (y + radius) >= (palY - palH / 2.0f) &&
            (y - radius) <  (palY - palH / 2.0f))
        {
            vy = -std::abs(vy);

            y = (palY - palH / 2.0f) - radius;
            shape.setPosition(sf::Vector2f(x, y));

            return true;
        }
        return false;
    }
    void draw(sf::RenderTarget &target) {
        target.draw(shape);
    }
    float getX_b() const {
        return x;
    };
    float getY() const {
        return y;
    };
    float getVx() const {
        return vx;
    };
    float getVy() const {
        return vy;
    };
    sf::Vector2f getVelocity() const {
        return sf::Vector2f(vx, vy);
    }
    float getRadius() const {
        return radius;
    };
    void reset(float newX, float newY, float newVx, float newVy) {
        x = newX;
        y = newY;
        vx = newVx;
        vy = newVy;
        shape.setPosition(sf::Vector2f(x, y));
    }
    };
#endif
