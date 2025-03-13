#include "Tetromino.h"


Tetromino tetrominoes[7] = {
		Tetromino({{0,0}, {1,0}, {2,0}, {3,0}}, sf::Color::Cyan),  // I 블록
		Tetromino({{0,0}, {0,1}, {1,0}, {1,1}}, sf::Color::Yellow),  // O 블록
		Tetromino({{0,0}, {1,0}, {2,0}, {1,1}}, sf::Color::Magenta),  // T 블록
		Tetromino({{0,0}, {1,0}, {2,0}, {2,1}}, sf::Color::Blue),  // J 블록
		Tetromino({{0,0}, {1,0}, {2,0}, {0,1}}, sf::Color(255, 125, 0, 255)),  // L 블록
		Tetromino({{0,0}, {1,0}, {1,1}, {2,1}}, sf::Color::Green),  // S 블록
		Tetromino({{0,1}, {1,1}, {1,0}, {2,0}}, sf::Color::Red)   // Z 블록
};

Tetromino* createTetromino() {
	return new Tetromino(tetrominoes[rand() % 7]);
}

Tetromino::Tetromino(std::vector<sf::Vector2i> s, sf::Color c)
{
	shape = s;
	color = c;

	for (int i = 0; i < 4; ++i) {
		blocks[i].setSize(sf::Vector2f(BLOCK_SIZE - 2, BLOCK_SIZE - 2));  // 테두리 효과
		blocks[i].setFillColor(color);
	}

	updateSize();
}

void Tetromino::draw(sf::RenderWindow& window)
{
	for (auto& block : blocks) {
		window.draw(block);
	}
}

void Tetromino::move(int dx, int dy)
{
	setPosition(currentPosition.x + dx, currentPosition.y + dy);
}

void Tetromino::rotate()
{
	std::vector<sf::Vector2i> newShape;

	for (int i = 0; i < 4; ++i) {
		int tempX = shape[i].x - 1;
		int tempY = shape[i].y;

		newShape.push_back(sf::Vector2i(tempY + 1, -tempX));
	}

	shape = newShape;

	updateSize();
	
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

sf::Color Tetromino::getColor()
{
	return color;
}


sf::Vector2i Tetromino::getSize()
{
	return sf::Vector2i(width, height);
}

std::vector<sf::Vector2i> Tetromino::getShape()
{
	return shape;
}

void Tetromino::updateSize()
{
	width = 0;
	height = 0;

	for (int i = 0; i < 4; ++i) {
		width = std::max(shape[i].x, width);
		height = std::max(shape[i].y, height);
	}
}
