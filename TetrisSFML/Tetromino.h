#pragma once
#include <SFML/Graphics.hpp>

#define BLOCK_SIZE 30

class Tetromino
{
public:
    Tetromino(std::vector<sf::Vector2i> s, sf::Color c);
    void draw(sf::RenderWindow& window);
    void move(int dx, int dy);
    void rotateCW();
    void rotateCCW();
    void setPosition(int x, int y);

    sf::Vector2i getPosition();
    std::vector<sf::RectangleShape> getBlocks();
    sf::Color getColor();
    std::vector<sf::Vector2i> getShape();

private:
    std::vector<sf::Vector2i> shape;  // 블록을 이루는 셀들의 상대 좌표
    sf::Color color;
    sf::RectangleShape blocks[4];  // 블록을 구성하는 4개의 정사각형
    sf::Vector2i currentPosition;
};

Tetromino* createTetromino();
