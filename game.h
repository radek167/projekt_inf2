#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "paletka.h"
#include "pilka.h"
#include "brick.h"
#include "menu.h"
#include "bonus_easymode.h"
#include "bonus_paletka.h"
#include "bonus_pilka.h"

enum class GameState { Menu, Playing, Scores, Exiting };

enum class typBonus { Brak, Pilka, Paletka, EasyMode };


class Game {
private:
    sf::RenderWindow window;
    sf::Clock deltaClock;
    Paletka paletka;
    Pilka pilka;
    std::vector<Brick> bloki;

    Menu menu;

    const float width = 640.f;
    const float height = 480.f;

    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    float ROZMIAR_BLOKU_X = (width - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;
    float ROZMIAR_BLOKU_Y = 25.f;

    bool gameOver = false;
    GameState currentState = GameState::Menu;
    typBonus activeBonus = typBonus::Brak;
    float timeBonus = 0.0f;
    void processEvents();
    void update(sf::Time dt);
    void render();;
    void resetGame();
    void offActiveBonus();
public:
    std::vector<BonusPilka> bonusPilka;
    std::vector<BonusPaletka> bonusPaletka;
    std::vector<BonusModeEasy> bonusEasyMode;
    Game();
    void run();

    void dodajPilka();
    void dodajPaletka();
    void dodajEasyMode();
};


#endif // GAME_H
