#pragma once
#include <SFML/Graphics.hpp>

#define BLOCK_SIZE 30

class Tetromino
{
public:
    Tetromino(std::vector<sf::Vector2i> s, sf::Color c);
    void draw(sf::RenderWindow& window);
    void move(int dx, int dy);
    void rotate();
    void setPosition(int x, int y);

    sf::Vector2i getPosition();
    std::vector<sf::RectangleShape> getBlocks();
    sf::Color getColor();
    sf::Vector2i getSize();
    std::vector<sf::Vector2i> getShape();

private:
    void updateSize();
private:
    std::vector<sf::Vector2i> shape;  // ����� �̷�� ������ ��� ��ǥ
    sf::Color color;
    sf::RectangleShape blocks[4];  // ����� �����ϴ� 4���� ���簢��
    sf::Vector2i currentPosition;
    int width;
    int height;
};

Tetromino* createTetromino();
