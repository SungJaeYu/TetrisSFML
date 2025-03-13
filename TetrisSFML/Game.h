#pragma once
#include <SFML/Graphics.hpp>
#include "Tetromino.h"
#include "Board.h"

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

private:
	void spawnTetromino();
	void updateTetromino();
	void renderTetromino();
	bool checkCollisionHorizontal(int dx);
	bool checkCollisionVertical(int dy);

private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Clock clock;
	float elapsedTime = 0.f;
	Board board;
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