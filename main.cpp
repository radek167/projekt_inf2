#include <SFML/Graphics.hpp>
#include <iostream>
#include "pilka.h"


int main() {
    float width = 640.f;
    float height = 480.f;
    sf::RenderWindow window(sf::VideoMode({640, 480}), "Arkanoid TEST");
    window.setFramerateLimit(30);

    Paletka paletka(320.f, 450.f, 100.f, 20.f, 10.f);
    Pilka pilka(320.f, 240.f, 4.f, -4.f, 10.f);

    bool gameOver = false;

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
            pilka = Pilka(320.f, 240.f, 4.f, -4.f, 10.f);


        }

        window.clear(sf::Color(20, 20, 30));
        paletka.draw(window);
        pilka.draw(window);
        window.display();
    }

    return 0;
}
