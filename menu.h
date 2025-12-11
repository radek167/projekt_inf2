#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#define MAX_LICZBA_POZIOMOW 4

class Menu {
private:
    sf::Font font;
    std::vector<sf::Text> menu;
    int selectedItem;

public:
    Menu(float width, float height);

    void przesunG();
    void przesunD();
    int getSelectedItem() const;

    void draw(sf::RenderWindow &window) const;
    void drawScores(sf::RenderWindow &window, const std::vector<std::string>& scores);
};

#endif // MENU_H