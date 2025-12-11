#include "bonus_paletka.h"
#include "game.h"
#include <iostream>

void BonusPaletka::dodaj(Game& game) {
    game.dodajPaletka();
    std::cout << "Paletka zostala powiekszona!\n";
}

