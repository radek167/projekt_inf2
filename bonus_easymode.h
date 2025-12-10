#ifndef BONUS_EASYMODE_H
#define BONUS_EASYMODE_H

#include "bonus.h"

class Game;

class BonusModeEasy : public Bonus {
  public:
    BonusModeEasy(float x, float y)
        : Bonus(x, y) {}
    void dodaj(Game& game);
};

#endif // BONUS_EASYMODE_H