#pragma once
#include "Tetromino.h"

#define ROWS 20
#define COLS 10

class Board
{
public:
	Board() = default;
	bool isEmpty(int x, int y);
	int addTetromino(Tetromino& tetromino);
	void draw(sf::RenderWindow& window);
#ifndef NDEBUG
	void debugPrint();
#endif
private:
	void addBlock(int x, int y, sf::Color color);
	void downBlock(int x, int y);
	int clearLine();
private:
	std::optional<sf::RectangleShape> board[ROWS][COLS];
};

