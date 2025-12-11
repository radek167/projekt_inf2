#include "menu.h"
#include <iostream>

Menu::Menu(float width, float height) : selectedItem(0) {
    if (!font.openFromFile("arial.ttf")) {
      return;
    }

    std::string opcje[MAX_LICZBA_POZIOMOW] = { "Nowa gra", "Wczytaj gre", "Ostatnie wyniki", "Wyjscie" };

    for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++) {
        sf::Text t(font);
        t.setString(opcje[i]);
        
        if (i == 0) t.setFillColor(sf::Color::Cyan);
        else t.setFillColor(sf::Color::White);

        t.setPosition({width / 4.f, height / (MAX_LICZBA_POZIOMOW + 1) * (i + 1.f)});
        menu.push_back(t);
    }
}

void Menu::przesunG() {
    if (menu.empty()) return;

    menu[selectedItem].setFillColor(sf::Color::White);
    menu[selectedItem].setStyle(sf::Text::Regular);
    
    selectedItem--;
    if (selectedItem < 0)
       selectedItem = MAX_LICZBA_POZIOMOW - 1;
       
    menu[selectedItem].setFillColor(sf::Color::Cyan);
    menu[selectedItem].setStyle(sf::Text::Bold);
}

void Menu::przesunD() {
    if (menu.empty()) return;

    menu[selectedItem].setFillColor(sf::Color::White);
    menu[selectedItem].setStyle(sf::Text::Regular);
    
    selectedItem++;
    if (selectedItem >= MAX_LICZBA_POZIOMOW)
       selectedItem = 0;
       
    menu[selectedItem].setFillColor(sf::Color::Cyan);
    menu[selectedItem].setStyle(sf::Text::Bold);
}

int Menu::getSelectedItem() const {
    return selectedItem;
}

void Menu::draw(sf::RenderWindow &window) const {
    for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
       window.draw(menu[i]);
}

void Menu::drawScores(sf::RenderWindow &window, const std::vector<std::string>& scores) {
    sf::Text title(font, "OSTATNIE WYNIKI", 30);
    title.setFillColor(sf::Color::Cyan);

    sf::FloatRect tr = title.getLocalBounds();
    title.setOrigin({tr.size.x / 2.f, tr.size.y / 2.f});
    title.setPosition({320.f, 50.f});
    window.draw(title);

    float y = 100.f;
    for(size_t i = 0; i < scores.size(); ++i) {
        std::string line = std::to_string(i + 1) + ". " + scores[i];

        sf::Text t(font, line, 20);
        t.setFillColor(sf::Color::White);
        t.setPosition({100.f, y});
        window.draw(t);
        
        y += 30.f;
        if (i >= 9) break;
    }
}