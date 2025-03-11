#pragma once
#include <SFML/Graphics.hpp>
#include "Tetromino.h"
const int ROWS = 20;
const int COLS = 10;

class Game
{
private:
	void initVariables();
	void initWindow();
public:
	Game();
	~Game();

	void render();
	void update();
	void pollEvents();
	bool isRunning();

	void spawnTetromino();
	void updateTetromino();
	void clearLine();
	void renderTetromino();

	bool checkCollision(int x, int y);

private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Clock clock;
	float elapsedTime = 0.f;
	int gameBoard[ROWS][COLS] = { 0 };  // 0: ºó Ä­, 1: ºí·ÏÀÌ ÀÖ´Â Ä­

	Tetromino* currentTetromino;
	std::vector<Tetromino> tetrominoes;
	std::vector<sf::RectangleShape> blocks;

	int points;
	bool endGame;
	int health;

	bool downPressed;
	bool leftPressed;
	bool rightPressed;
	bool spacePressed;

	bool saveTriggered;
	bool blockSpawned;
};