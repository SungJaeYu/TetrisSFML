#pragma once
#include <SFML/Graphics.hpp>
#include "Tetromino.h"

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


private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Clock clock;
	float elapsedTime = 0.f;

	Tetromino* currentTetromino;
	std::vector<Tetromino> tetrominoes;
	std::vector<sf::RectangleShape> blocks;

	int points;
	bool endGame;
	bool health;

	bool downPressed;
	bool leftPressed;
	bool rightPressed;
	bool spacePressed;

	bool saveTriggered;
	bool blockSpawned;
};