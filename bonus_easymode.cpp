#include "bonus_easymode.h"
#include "game.h"
#include <iostream>

void BonusModeEasy::dodaj(Game& game) {
    game.dodajEasyMode();
    std::cout << "Tryb latwy aktywowany!\n";
}
