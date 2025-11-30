#include "game.h"
#include <iostream>

Game::Game()
    : window(sf::VideoMode({640u, 480u}), "Arkanoid SFML"),
      menu(640.f, 480.f),
      paletka(320.f, 450.f, 100.f, 20.f, 10.f),
      pilka(320.f, 400.f, 4.f, -4.f, 10.f),
      currentState(GameState::Menu)
{
    window.setFramerateLimit(60);
    resetGame();
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        sf::Time dt = deltaClock.restart();
        if (currentState == GameState::Playing)
            update(dt);
        render();
    }
}

void Game::processEvents() {
    while (auto eventOpt = window.pollEvent()) {
        auto &event = *eventOpt;

        if (event.is<sf::Event::Closed>()) {
            window.close();
        }

        if (auto keyPressed = event.getIf<sf::Event::KeyPressed>()) {
            auto key = keyPressed->scancode;

            if (key == sf::Keyboard::Scan::Escape) {
                if (currentState == GameState::Playing)
                    currentState = GameState::Menu;
                else
                    window.close();
            }

            if (currentState == GameState::Menu) {
                if (key == sf::Keyboard::Scan::Up) menu.przesunG();
                if (key == sf::Keyboard::Scan::Down) menu.przesunD();
                if (key == sf::Keyboard::Scan::Enter) {
                    int sel = menu.getSelectedItem();
                    if (sel == 0) currentState = GameState::Playing;
                    else if (sel == 1) currentState = GameState::Scores;
                    else if (sel == 2) window.close();
                }
            }
        }
    }
}

void Game::update(sf::Time dt) {
    if (currentState != GameState::Playing) return;

    if (!gameOver) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left))
            paletka.moveLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right))
            paletka.moveRight();

        paletka.clampToBounds(640.f);

        pilka.move();
        pilka.collideWalls(640.f, 480.f);

        if (pilka.collidePaddle(paletka))
            std::cout << "HIT PADDLE\n";

        if (pilka.getY() + pilka.getRadius() > 600.f) {
            std::cout << "MISS! KONIEC GRY. SPACJA = RESTART\n";
            gameOver = true;
        }

        for (auto &blk : bloki) {
            if (!blk.m_czyZniszczony() &&
                pilka.shape.getGlobalBounds().findIntersection(blk.getGlobalBounds())) {
                blk.trafienie();
                pilka.bounceY();
                std::cout << "HIT BRICK\n";
            }
        }

        for (int i = bloki.size() - 1; i >= 0; i--) {
            if (bloki[i].m_czyZniszczony())
                bloki.erase(bloki.begin() + i);
        }
    }

    if (gameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space))
        resetGame();
}

void Game::render() {
    window.clear(sf::Color(20, 20, 30));

    if (currentState == GameState::Menu)
        menu.draw(window);
    else if (currentState == GameState::Playing) {
        paletka.draw(window);
        pilka.draw(window);
        for (auto &blk : bloki)
            blk.draw(window);
    }

    window.display();
}

void Game::resetGame() {
    gameOver = false;
    paletka = Paletka(320.f, 450.f, 100.f, 20.f, 10.f);
    pilka = Pilka(320.f, 400.f, 4.f, -4.f, 10.f);

    bloki.clear();
    for (int y = 0; y < ILOSC_WIERSZY; y++) {
        for (int x = 0; x < ILOSC_KOLUMN; x++) {
            float posX = x * (ROZMIAR_BLOKU_X + 2.f);
            float posY = y * (ROZMIAR_BLOKU_Y + 2.f) + 60.f;
            int L = (y == 0) ? 3 : (y < 3) ? 2 : 1;
            bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), L);
        }
    }
}
