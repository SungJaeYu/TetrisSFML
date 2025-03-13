#pragma once
#include <SFML/Graphics.hpp>
#include "Tetromino.h"
#include "Board.h"

class Game
{
private:
	void initVariables();
	void initWindow();
	void initText();

public:
	Game();
	~Game();
	void render();
	void update();
	void pollEvents();
	bool isRunning();

private:
	void spawnTetromino();
	void left();
	void right();
	void down();
	void rotate();

	void updateTetromino();

	void renderTetromino();
	void renderBoard();
	void renderTexts();

	bool checkCollisionHorizontal(int dx);
	bool checkCollisionVertical(int dy);
	bool checkCollisionCurrent();

private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Clock clock;
	float elapsedTime = 0.f;
	Board board;
	Tetromino* currentTetromino;
	sf::Font font;
	sf::Text* text;


	int score;
	bool endGame;
};