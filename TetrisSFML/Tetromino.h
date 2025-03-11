#pragma once
#include <SFML/Graphics.hpp>

class Tetromino
{
public:
    Tetromino(std::vector<sf::Vector2i> s, sf::Color c);
    void setPosition(int x, int y);
    sf::Vector2i getPosition();
    std::vector<sf::RectangleShape> getBlocks();
    void draw(sf::RenderWindow& window);
private:
    std::vector<sf::Vector2i> shape;  // ����� �̷�� ������ ��� ��ǥ
    sf::Color color;
    sf::RectangleShape blocks[4];  // ����� �����ϴ� 4���� ���簢��
    sf::Vector2i currentPosition;
};

Tetromino* createTetromino();
