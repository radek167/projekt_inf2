#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#define MAX_LICZBA_POZIOMOW 3

class Menu {
private:
    sf::Font font;
    std::vector<sf::Text> menu;
    int selectedItem = 0;

public:
    Menu(float width, float height);
    ~Menu() {};
    void przesunG();
    void przesunD();
    int getSelectedItem() const { return selectedItem; }
    void draw(sf::RenderWindow &window) const;
};

inline Menu::Menu(float width, float height) {
    if (!font.openFromFile("arial.ttf"))
        return;

    sf::Text t(font);

    t.setFont(font);
    t.setFillColor(sf::Color::Cyan);
    t.setString("Nowa gra");
    t.setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 1));
    menu.push_back(t);

    t.setFillColor(sf::Color::White);
    t.setString("Ostatnie wyniki");
    t.setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 2));
    menu.push_back(t);

    t.setFillColor(sf::Color::White);
    t.setString(L"Wyjście");
    t.setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 3));
    menu.push_back(t);
}

inline void Menu::draw(sf::RenderWindow &window) const {
    for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
        window.draw(menu[i]);
}

inline void Menu::przesunG() {
    menu[selectedItem].setFillColor(sf::Color::White);
    menu[selectedItem].setStyle(sf::Text::Regular);
    selectedItem--;
    if (selectedItem < 0)
        selectedItem = MAX_LICZBA_POZIOMOW - 1;
    menu[selectedItem].setFillColor(sf::Color::Cyan);
    menu[selectedItem].setStyle(sf::Text::Bold);
}

inline void Menu::przesunD() {
    menu[selectedItem].setFillColor(sf::Color::White);
    menu[selectedItem].setStyle(sf::Text::Regular);
    selectedItem++;
    if (selectedItem >= MAX_LICZBA_POZIOMOW)
        selectedItem = 0;
    menu[selectedItem].setFillColor(sf::Color::Cyan);
    menu[selectedItem].setStyle(sf::Text::Bold);
}
