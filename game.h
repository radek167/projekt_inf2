#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "paletka.h"
#include "pilka.h"
#include "brick.h"
#include "menu.h"

enum class GameState { Menu, Playing, Scores, Exiting };

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

private:
    void processEvents();
    void update(sf::Time dt);
    void render();;
    void resetGame();

public:
    Game();
    void run();
};

#endif // GAME_H
