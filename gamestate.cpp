#include "gamestate.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "paletka.h"
#include "pilka.h"

void StanGry::capture(const Paletka& pal, const Pilka& pil, const std::vector<Brick>& bloki) {
    paddlePosition = sf::Vector2f(pal.getX(), pal.getY());
    ballPosition = sf::Vector2f(pil.getX_b(), pil.getY());
    ballVelocity = pil.getVelocity();

    blocks.clear();
    for (const auto& brick : bloki) {
        BlockData dane;
        dane.x = brick.getPosition().x;
        dane.y = brick.getPosition().y;
        dane.hp = brick.getHP();
        blocks.push_back(dane);
    }
}
bool StanGry::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Nie można otworzyć pliku do zapisu: " << filename << std::endl;
        return false;
    };
    outFile << "PADDLE" << " " << paddlePosition.x << " " << paddlePosition.y << "\n";
    outFile << "BALL" << " " << ballPosition.x << " " << ballPosition.y << " " << ballVelocity.x << " " << ballVelocity.y << "\n";
    outFile << "BLOCKS_COUNT" << " " << blocks.size() << "\n";
    for (const auto& block : blocks) {
        outFile << "BLOCK" << " " << block.x << " " << block.y << " " << block.hp << "\n";
    }
    outFile.close();
    return true;
}
bool StanGry::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    std::string label;

    file >> label;
    if (label != "PADDLE") return false;
    file >> paddlePosition.x >> paddlePosition.y;

    file >> label;
    if (label != "BALL") return false;
    file >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y;

    file >> label;
    if (label != "BLOCKS_COUNT") return false;
    int blocksCount;
    file >> blocksCount;

    blocks.clear();
    for (int i = 0; i < blocksCount; ++i) {
        float x, y;
        int hp;
        file >> label >> x >> y >> hp; // spodziewamy się "BLOCK"
        if (label != "BLOCK") return false;
        blocks.push_back({x, y, hp});
    }
    return true;
}

void StanGry::apply(Paletka& p, Pilka& b, std::vector<Brick>& bricks, float blockWidth, float blockHeight) const
{
    p.setPosition(paddlePosition.x, paddlePosition.y);
    b.reset(ballPosition.x, ballPosition.y, ballVelocity.x, ballVelocity.y);
    bricks.clear();

    for (const auto& data : blocks) {
        if (blockWidth <= 0.f || blockHeight <= 0.f) {
            continue;
        }
        int hp = std::clamp(data.hp, 0, 3);
        bricks.emplace_back(
            sf::Vector2f(data.x, data.y),
            sf::Vector2f(blockWidth, blockHeight),
            data.hp
        );
    }
}
