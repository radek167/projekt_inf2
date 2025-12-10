#include "Bonus_pilka.h"
#include "game.h"
#include <iostream>

void BonusPilka::dodaj(Game& game) {
    game.dodajPilka();
    std::cout << "Dodano dodatkową piłkę do gry!\n";
}