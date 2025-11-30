#include "game.h"
#include "brick.h"
#include "paletka.h"
#include "pilka.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Game::Game()
    : window(sf::VideoMode({640, 480}), "Arkanoid TEST"),
      paletka(320.f, 450.f, 100.f, 20.f, 10.f),
      pilka(320.f, 400.f, 4.f, -4.f, 10.f)
{
    window.setFramerateLimit(60);

    for (int y=0; y<ILOSC_WIERSZY; y++) {
        for (int x=0; x<ILOSC_KOLUMN; x++) {
            float posX = x * (ROZMIAR_BLOKU_X +2.f);//2px na przerwe
            float posY = y * (ROZMIAR_BLOKU_Y +2.f)+60.f;//50px od gory
            //kolor L
            int L;
            if (y == 0) {
                L = 3;
            } else if (y < 3) {
                L = 2;
            } else {
                L = 1;
            }

            bloki.emplace_back(sf::Vector2f(posX,posY), sf::Vector2f(ROZMIAR_BLOKU_X,ROZMIAR_BLOKU_Y), L);
        }
    }
}
void Game::run() {
   while (window.isOpen()) {
            while (auto event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) window.close();
            }

            if (!gameOver) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
                    paletka.moveLeft();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
                    paletka.moveRight();

                paletka.clampToBounds(width);
                pilka.move();
                pilka.collideWalls(width, height);

                if (pilka.collidePaddle(paletka))
                    std::cout << "HIT PADDLE\n";

                if (pilka.getY() + pilka.getRadius() > height) {
                    std::cout << "MISS! KONIEC GRY\n SPACJA = RESTART\n";
                    gameOver = true;


                }

            }
            if (gameOver == true && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                gameOver = false;
                paletka = Paletka(320.f, 450.f, 100.f, 20.f, 10.f);
                pilka = Pilka(320.f, 400.f, 4.f, -4.f, 10.f);
                bloki.clear();
                for (int y=0; y<ILOSC_WIERSZY; y++) {
                    for (int x=0; x<ILOSC_KOLUMN; x++) {
                        float posX = x * (ROZMIAR_BLOKU_X +2.f);//2px na przerwe
                        float posY = y * (ROZMIAR_BLOKU_Y +2.f)+60.f;//50px od gory
                        //algorytm ustalania koloru wzgledem zycia L
                        int L;
                        if (y == 0) {
                            L = 3; // górny wiersz – 3 życia
                        } else if (y < 3) {
                            L = 2; // wiersze 1 i 2 – 2 życia
                        } else {
                            L = 1; // pozostałe wiersze – 1 życie
                        }

                        bloki.emplace_back(sf::Vector2f(posX,posY), sf::Vector2f(ROZMIAR_BLOKU_X,ROZMIAR_BLOKU_Y), L);
                    }
                }

            }

            // --- Kolizje Piłki z Blokami

            for (auto& blk : bloki) {
                if (!blk.m_czyZniszczony() && pilka.shape.getGlobalBounds().findIntersection(blk.getGlobalBounds()) ) {
                    blk.trafienie();
                    pilka.bounceY();
                    std::cout << "HIT BRICK\n";//cos tu kuzwa nie dziala
                }
                for (int i = bloki.size() -1; i >=0; i--) {
                    if (bloki[i].m_czyZniszczony()){
                        bloki.erase(bloki.begin() + i);
                    }
                }
            }
            //bloki cegly


            window.clear(sf::Color(20, 20, 30));
            paletka.draw(window);
            pilka.draw(window);


            for (auto& blk : bloki) {
                blk.draw(window);
            }

            window.display();
        }
}
