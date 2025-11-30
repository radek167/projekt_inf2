#ifndef BRICK_H
#define BRICK_H


#include <SFML/Graphics.hpp>
#include <array>//prosta tablica stalego rozmiaru
class Brick : public sf::RectangleShape {
private:
    int m_punktyZycia;//0-3
    bool m_jestZniszczony;// jesli zniszczony to true
    inline static const std::array<sf::Color,4> m_colorLUT = {
        sf::Color::Transparent,
        sf::Color::Yellow,
        sf::Color::Magenta,
        sf::Color::Red
    };//tablica Look-up
public:
    Brick(sf::Vector2f startPos, sf::Vector2f rozmiar, int L);
    void aktualizujKolor();
    void trafienie();
    void draw(sf::RenderTarget &target) const;
    bool m_czyZniszczony(){return m_jestZniszczony;}

};


inline Brick::Brick(sf::Vector2f startPos, sf::Vector2f rozmiar, int L) {
    m_punktyZycia = L;
    m_jestZniszczony = false;
    this->setPosition(startPos);
    this->setSize(rozmiar);
    setOutlineThickness(2.f);
    aktualizujKolor();
}

inline void Brick::trafienie() {
    if (m_jestZniszczony==true)
        return;// zakonczenie funkcji
    m_punktyZycia--;
    aktualizujKolor();
    if (m_punktyZycia<=0)
        m_jestZniszczony=true;// jest zniszczony
}

inline void Brick::aktualizujKolor() {
    if (m_punktyZycia>=0 && m_punktyZycia<=3)
        this->setFillColor(m_colorLUT[m_punktyZycia]);
}

inline void Brick::draw(sf::RenderTarget &target) const {
    if (!m_jestZniszczony)
        target.draw(*this);
}

#endif //BRICK_H
