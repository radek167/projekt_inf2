#ifndef BONUS_H
#define BONUS_H

#include <SFML/Graphics.hpp>

class Game;

class Bonus {
protected:
  sf::RectangleShape shape;
  float speed;
public:
  Bonus(float x, float y);

  void update();
  void draw(sf::RenderWindow& win);
  sf::FloatRect getBounds() const;
};

#endif