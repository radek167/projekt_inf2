#ifndef BONUS_PALETKA_H
#define BONUS_PALETKA_H

#include "bonus.h"
class Game;
class BonusPaletka : public Bonus {
  public:
    BonusPaletka(float x, float y)
        : Bonus(x, y) {}
    void dodaj(Game& game);
};

#endif // BONUS_PALETKA_H