#include "Tetromino.h"

const int BLOCK_SIZE = 30;

Tetromino tetrominoes[7] = {
		Tetromino({{0,0}, {1,0}, {2,0}, {3,0}}, sf::Color::Cyan),  // I ���
		Tetromino({{0,0}, {0,1}, {1,0}, {1,1}}, sf::Color::Yellow),  // O ���
		Tetromino({{0,0}, {1,0}, {2,0}, {1,1}}, sf::Color::Magenta),  // T ���
		Tetromino({{0,0}, {1,0}, {2,0}, {2,1}}, sf::Color::Blue),  // J ���
		Tetromino({{0,0}, {1,0}, {2,0}, {0,1}}, sf::Color(255, 125, 0, 255)),  // L ���
		Tetromino({{0,0}, {1,0}, {1,1}, {2,1}}, sf::Color::Green),  // S ���
		Tetromino({{0,1}, {1,1}, {1,0}, {2,0}}, sf::Color::Red)   // Z ���
};

Tetromino* createTetromino() {
	return new Tetromino(tetrominoes[rand() % 7]);
}

Tetromino::Tetromino(std::vector<sf::Vector2i> s, sf::Color c)
{
	shape = s;
	color = c;

	for (int i = 0; i < 4; ++i) {
		blocks[i].setSize(sf::Vector2f(BLOCK_SIZE - 2, BLOCK_SIZE - 2));  // �׵θ� ȿ��
		blocks[i].setFillColor(color);
	}
}

void Tetromino::setPosition(int x, int y)
{
	for (int i = 0; i < 4; ++i) {
		float windowPositionX = BLOCK_SIZE * (shape[i].x + x);
		float windowPositionY = BLOCK_SIZE * (shape[i].y + y);
		blocks[i].setPosition(sf::Vector2f{windowPositionX, windowPositionY});
	}
	currentPosition.x = x;
	currentPosition.y = y;
}

sf::Vector2i Tetromino::getPosition()
{
	return currentPosition;
}

std::vector<sf::RectangleShape> Tetromino::getBlocks()
{
	std::vector<sf::RectangleShape> outputBlocks;
	for (auto& block : blocks) {
		outputBlocks.push_back(block);
	}
	return outputBlocks;
}

void Tetromino::draw(sf::RenderWindow& window)
{
	for (auto& block : blocks) {
		window.draw(block);
	}
}
