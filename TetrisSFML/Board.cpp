#include "Board.h"

bool Board::isEmpty(int x, int y)
{
	if (board[y][x]) {
		return false;
	}
	return true;
}

void Board::addTetromino(Tetromino& tetromino)
{
	std::vector<sf::Vector2i> shape = tetromino.getShape();
	sf::Vector2i pos = tetromino.getPosition();
	sf::Color color = tetromino.getColor();

	for (int i = 0; i < 4; ++i) {
		addBlock(shape[i].x + pos.x, shape[i].y + pos.y, color);
	}

	clearLine();
}

void Board::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			if (board[i][j]) {
				window.draw(*board[i][j]);
			}
		}
	}
}

void Board::debugPrint()
{
	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			if (board[i][j]) {
				printf("O");
			}
			else {
				printf("X");
			}
		}
		printf("\n");
	}
	printf("\n\n");
}

void Board::addBlock(int x, int y, sf::Color color)
{
	board[y][x] = sf::RectangleShape();
	board[y][x]->setSize(sf::Vector2f(BLOCK_SIZE - 2, BLOCK_SIZE - 2));
	board[y][x]->setPosition(sf::Vector2f( BLOCK_SIZE * x, BLOCK_SIZE * y ));
	board[y][x]->setFillColor(color);
}

void Board::downBlock(int x, int y)
{
	if (board[x - 1][y]) {
		board[x][y] = board[x - 1][y];
		board[x - 1][y].reset();
		board[x][y]->setPosition(sf::Vector2f(BLOCK_SIZE * y, BLOCK_SIZE * x));
	}
}

void Board::clearLine()
{
	int i = ROWS - 1;

	while (i >= 0) {
		bool isFull = true;
		for (int j = 0; j < COLS; ++j) {
			if (!board[i][j]) {
				isFull = false;
				break;
			}
		}

		if (isFull) {
			for (int j = 0; j < COLS; ++j) {
				board[i][j].reset();
			}
			
			for (int k = i; k > 0; --k) {
				for (int j = 0; j < COLS; ++j) {
					downBlock(k, j);
				}
			}
		}
		else {
			--i;
		}


	}

}
