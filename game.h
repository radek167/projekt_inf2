#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "paletka.h"
#include "pilka.h"
#include "brick.h"


class Game {
private:
    sf::RenderWindow window;
    sf::Clock m_deltaClock;
    Paletka paletka;
    Pilka pilka;
    std::vector<Brick> bloki;

    float width = 640.f;
    float height = 480.f;
    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    float ROZMIAR_BLOKU_X = (width -(ILOSC_KOLUMN - 1) * 2.f)/ILOSC_KOLUMN; //uzaleznic od szerokosci ekranu
    float ROZMIAR_BLOKU_Y = 25.f;

    bool gameOver = false;
public:
    Game();
    void run();
};

#endif //GAME_H

