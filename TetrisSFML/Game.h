#pragma once
#include <SFML/Graphics.hpp>

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

	void spawnBlock();
	void updateBlock();
	void clearLine();
	void renderBlocks();


private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Clock clock;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	
	sf::RectangleShape* currentBlock;
	std::vector<sf::RectangleShape*> blocks;

	int points;
	bool endGame;
	bool health;

	bool downPressed;
	bool leftPressed;
	bool rightPressed;
	bool spacePressed;

	bool saveTriggered;
	bool blockSpawned;

	sf::RectangleShape enemy;
};