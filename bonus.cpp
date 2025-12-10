#include "bonus.h"

Bonus::Bonus(float x, float y) :speed(3.f)
{
    shape.setSize(sf::Vector2f({20.f, 20.f}));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(sf::Vector2f{x, y});
}

void Bonus::update() {
    shape.move({0.f, speed});
}

void Bonus::draw(sf::RenderWindow& win) {
    win.draw(shape);
}

sf::FloatRect Bonus::getBounds() const {
    return shape.getGlobalBounds();
}
