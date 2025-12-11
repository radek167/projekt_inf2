#include "game.h"
#include "gamestate.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

Game::Game()
    : window(sf::VideoMode({640u, 480u}), "Arkanoid SFML"),
      menu(640.f, 480.f),
      paletka(320.f, 450.f, 100.f, 20.f, 10.f),
      pilka(320.f, 400.f, 4.f, -4.f, 10.f),
      currentState(GameState::Menu),
      scoreText(font)
{
    window.setFramerateLimit(60);

    if (!font.openFromFile("arial.ttf")) {
        std::cerr << "BLAD: Nie udalo sie wczytac czcionki arial.ttf!\n";
    }

    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({10.f, 10.f});
    scoreText.setString("Punkty: 0");

    std::ifstream input("wyniki.txt");
    if (input.is_open()) {
        std::string line;
        while (std::getline(input, line)) {
            highScores.push_back(line);
        }
        input.close();
    }

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

            if (key == sf::Keyboard::Scan::F5 && currentState == GameState::Playing) {
                StanGry stan;
                stan.capture(paletka, pilka, bloki);
                stan.saveToFile("zapis.txt");
                std::cout << "Stan gry zapisany do pliku zapis.txt\n";
            }

            if (key == sf::Keyboard::Scan::Escape) {
                if (currentState == GameState::Playing)
                    currentState = GameState::Menu;
                else if (currentState == GameState::Scores)
                    currentState = GameState::Menu;
                else
                    window.close();
            }

            if (currentState == GameState::Menu) {
                if (key == sf::Keyboard::Scan::Up) menu.przesunG();
                if (key == sf::Keyboard::Scan::Down) menu.przesunD();
                if (key == sf::Keyboard::Scan::Enter) {
                    int sel = menu.getSelectedItem();
                    if (sel == 0) {
                        resetGame();
                        currentState = GameState::Playing;
                    }
                    else if (sel == 1) {
                        StanGry stan;
                        if (stan.loadFromFile("zapis.txt")) {
                            stan.apply(paletka, pilka, bloki, ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y);
                            currentState = GameState::Playing;
                            std::cout << "Wczytano zapis!\n";
                            gameOver = false;
                        } else {
                            std::cout << "Uszkodzony zapis lub on nie istnieje\n";
                        }
                    }
                    else if (sel == 2) {
                        currentState = GameState::Scores;
                    }
                    else if (sel == 3) window.close();
                }
            }
        }
    }
}

void Game::update(sf::Time dt) {
    if (currentState != GameState::Playing) return;

    scoreText.setString("Punkty: " + std::to_string(score));

    if (activeBonus != typBonus::Brak) {
        timeBonus -= dt.asSeconds();
        if (timeBonus <= 0.0f) {
            offActiveBonus();
            std::cout << "Czas bonusu minal.\n";
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
        StanGry zapisanyStan;
        zapisanyStan.capture(paletka, pilka, bloki);
        zapisanyStan.saveToFile("zapis.txt");
        std::cout << "Stan gry zapisany.\n";
    }

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

            auto t = std::time(nullptr);
            std::tm tm = *std::localtime(&t);
            char buf[64];
            std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", &tm);
            std::string wpis = std::string(buf) + " - " + std::to_string(score) + " pkt";
            highScores.push_back(wpis);
            std::ofstream outfile("wyniki.txt", std::ios::app);
            if (outfile.is_open()) {
                outfile << wpis << std::endl;
                outfile.close();
            } else {
                std::cerr << "Blad zapisu wynikow!\n";
            }
        }

        for (int i = bloki.size() - 1; i >= 0; i--) {
            auto &blk = bloki[i];
            if (!blk.m_czyZniszczony() &&
                pilka.shape.getGlobalBounds().findIntersection(blk.getGlobalBounds())) {
                if (activeBonus == typBonus::EasyMode) {
                    blk.setHP(0);
                } else {
                    blk.trafienie();
                }

                pilka.bounceY();
                std::cout << "HIT BRICK\n";

                if (blk.m_czyZniszczony()) {
                    score += 10;
                }

                if (rand() % 100 < 20) {
                    int r = rand() % 2;
                    if (r == 0)
                        bonusPaletka.emplace_back(blk.getPosition().x, blk.getPosition().y);
                    else if (r == 1)
                        bonusEasyMode.emplace_back(blk.getPosition().x, blk.getPosition().y);

                    std::cout << "Wypadl bonus!\n";
                }
            }

            if (blk.m_czyZniszczony())
                bloki.erase(bloki.begin() + i);
        }
    }

    if (gameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space))
        resetGame();

    sf::FloatRect palRect(
        sf::Vector2f(paletka.getX() - paletka.getSzerokosc()/2, paletka.getY() - paletka.getWysokosc()/2),
        sf::Vector2f(paletka.getSzerokosc(), paletka.getWysokosc())
    );

    for (int i = 0; i < bonusPaletka.size(); i++) {
        bonusPaletka[i].update();
        if (bonusPaletka[i].getBounds().findIntersection(palRect)) {
            bonusPaletka[i].dodaj(*this);
            bonusPaletka.erase(bonusPaletka.begin() + i);
            i--;
        }
    }

    for (int i = 0; i < bonusEasyMode.size(); i++) {
        bonusEasyMode[i].update();
        if (bonusEasyMode[i].getBounds().findIntersection(palRect)) {
            bonusEasyMode[i].dodaj(*this);
            bonusEasyMode.erase(bonusEasyMode.begin() + i);
            i--;
        }
    }
}

void Game::render() {
    window.clear(sf::Color(20, 20, 30));

    if (currentState == GameState::Menu) {
        menu.draw(window);
    }
    else if (currentState == GameState::Playing) {
        paletka.draw(window);
        pilka.draw(window);
        for (auto &blk : bloki)
            blk.draw(window);
        window.draw(scoreText);

        for (auto &b : bonusPilka) b.draw(window);
        for (auto &b : bonusPaletka) b.draw(window);
        for (auto &b : bonusEasyMode) b.draw(window);

    }
    else if (currentState == GameState::Scores) {
        menu.drawScores(window, highScores);
    }

    window.display();
}

void Game::resetGame() {
    gameOver = false;
    score = 0;

    if (activeBonus != typBonus::Brak) {
        offActiveBonus();
    }
    activeBonus = typBonus::Brak;
    timeBonus = 0.0f;

    bonusPaletka.clear();
    bonusPilka.clear();
    bonusEasyMode.clear();

    paletka.setPosition(320.f, 450.f);
    pilka.reset(320.f, 400.f, 4.f, -4.f);

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

void Game::dodajPilka() {
   // nieużywane
}

void Game::dodajPaletka() {
    if (activeBonus == typBonus::Paletka) {
        timeBonus = 10.0f;
        std::cout << "Bonus Paletka przedluzony o 10s\n";
        return;
    }

    if (activeBonus != typBonus::Brak) {
         std::cout << "Inny bonus jest aktywny\n";
         return;
    }

    activeBonus = typBonus::Paletka;
    timeBonus = 10.0f;
    paletka.scale(1.3f);
    std::cout << "START: Paletka powiekszona (10s)\n";
}

void Game::dodajEasyMode() {
    int ile_blokow = 0;
    for (auto &b : bloki) {
        if (b.getHP() > 1) {
            b.setHP(1);
            ile_blokow++;
        }
    }
    std::cout << "EASY MODE ACTIVATED: Oslabiono " << ile_blokow << " klockow!\n";
}

void Game::offActiveBonus() {
    if (activeBonus == typBonus::Paletka) {
        paletka.scale(1.0f / 1.3f);
        std::cout << "Paletka wrocila do normy\n";
    }
    activeBonus = typBonus::Brak;
    timeBonus = 0.0f;
}