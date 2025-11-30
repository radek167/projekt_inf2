#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "game.h"
#include "pilka.h"
#include "brick.h"
#include "paletka.h"
#include <vector>
#include <SFML/Graphics.hpp>

struct BlockData {
    float x, y;
    int hp;
};

class StanGry {
private:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;
public:
    void capture(const Paletka&, const Pilka&, const std::vector<Brick>&);
    const sf::Vector2f& getPaddlePosition() const {return paddlePosition;};
    const sf::Vector2f& getBallPosition() const {return ballPosition;};
    const sf::Vector2f& getBallVelocity() const {return ballVelocity;};
    const std::vector<BlockData>& getBlocks() const {return blocks;};

    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);

    void apply (Paletka& pal, Pilka& pil, std::vector<Brick>& bloki, float blockWidth, float blockHeight) const;
};
#endif //GAMESTATE_H
