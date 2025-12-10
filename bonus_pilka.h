#ifndef BONUS_PILKA_H
#define BONUS_PILKA_H

#include "bonus.h"

class Game;

class BonusPilka : public Bonus {
  public:
    BonusPilka(float x, float y)
        : Bonus(x, y) {}
    void dodaj(Game& game);
};

#endif // BONUS_PILKA_H