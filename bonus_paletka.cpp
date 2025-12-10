#include "bonus_paletka.h"
#include "game.h"
#include <iostream>

void BonusPaletka::dodaj(Game& game) {
    game.dodajPaletka();
    std::cout << "Paletka została powiększona!\n";
}

