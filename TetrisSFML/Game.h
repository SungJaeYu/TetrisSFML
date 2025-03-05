#pragma once
#include <SFML/Graphics.hpp>

class Game
{
private:
	void initVariables();
	void initWindow();
	void initEnemies();
public:
	Game();
	~Game();

	void render();
	void update();
	void pollEvents();
	void updateMousePosition();
	bool isRunning();

	void spawnBlock();
	void updateBlocks();
	void renderBlocks();


private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Clock clock;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	std::vector<sf::RectangleShape> enemies;
	int points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;
	bool endGame;
	bool health;

	sf::RectangleShape enemy;
};