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
    std::vector<sf::Vector2i> shape;  // ����� �̷�� ������ ��� ��ǥ
    sf::Color color;
    sf::RectangleShape blocks[4];  // ����� �����ϴ� 4���� ���簢��
    sf::Vector2i currentPosition;
};

Tetromino* createTetromino();
