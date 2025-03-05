#include "Game.h"
#include <iostream>

void Game::initVariables()
{
	window = nullptr;
	endGame = false;
	health = 100;
	points = 0;
	enemySpawnTimerMax = 1000.f;
	enemySpawnTimer = enemySpawnTimerMax;
	maxEnemies = 10;
	mouseHeld = false;
}

void Game::initWindow()
{
	// Set VideoMode Size
	videoMode.size = sf::Vector2u(720, 480);

	// Create Window
	window = new sf::RenderWindow(videoMode, "Tetris", sf::Style::Titlebar | sf::Style::Close);

	// controll framerate
	window->setVerticalSyncEnabled(true); // call it once after creating the window
	window->setFramerateLimit(60); // call it once after creating the window
}

void Game::initEnemies()
{
	//enemy.setPosition(10.f, 10.f);
	//enemy.setSize(sf::Vector2f(100.f, 100.f));
	//enemy.setFillColor(sf::Color::Cyan);
	//enemy.setOutlineColor(sf::Color::Green);
	//enemy.setOutlineThickness(1.f);

	//blueFootedBooby.init();
	//landscape.init();
}

Game::Game()
{
	initVariables();
	initWindow();
	initEnemies();
}

Game::~Game()
{
	delete window;
}



void Game::render()
{
	window->clear();

	//window->draw();

	window->display();
}

void Game::update()
{
	pollEvents();

	//updateMousePosition();

	updateBlocks();

	// relative to screen
	//std::cout << "Mouse Pos : " << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << "\n";

	// relative to window
	//std::cout << "Mouse Pos : " << sf::Mouse::getPosition(*window).x << " " << sf::Mouse::getPosition(*window).y << "\n";
}

void Game::pollEvents()
{
	while (const std::optional event = window->pollEvent())
	{
		if (event->is <sf::Event::Closed>()) {
			window->close();
		}
		else if (const auto* keyPressed = event->getIf < sf::Event::KeyPressed>()) {
			switch (keyPressed->scancode) {
			case sf::Keyboard::Scancode::Escape:
				window->close();
				break;
			case sf::Keyboard::Scancode::Space:
				// Save
				break;
			case sf::Keyboard::Scancode::Down:
				// Fast Down
				break;
			case sf::Keyboard::Scancode::Left:
				// Left
				break;
			case sf::Keyboard::Scancode::Right:
				// Right
				break;
			default:
				break;
			}
		}
	}
}

void Game::updateMousePosition()
{
	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(mousePosWindow);
}

bool Game::isRunning()
{
	return window->isOpen();
}

void Game::spawnBlock()
{
	//enemy.setPosition(
	//	static_cast<float>(rand() % static_cast<int>(window->getSize().x - enemy.getSize().x)),
	//	static_cast<float>(rand() % static_cast<int>(window->getSize().y - enemy.getSize().y))
	//);
}

void Game::updateBlocks()
{

	//if (enemies.size() < maxEnemies) {
	//	if (enemySpawnTimer >= enemySpawnTimerMax) {
	//		spawnEnemy();
	//		enemySpawnTimer = 0.0f;
	//	}
	//	else {
	//		enemySpawnTimer += 1.f;
	//	}
	//}

	//for (auto& e : enemies) {
	//	bool deleted = false;


	//	//e.move(0.0f, 0.1f);
	//}

	//if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
	//	if (mouseHeld = false) {
	//		bool deleted = false;
	//		mouseHeld = true;
	//		for (auto e : enemies) {
	//			if (e.getGlobalBounds().contains(mousePosView)) {
	//				deleted = true;

	//				points += 10.f;

	//			}
	//		}
	//	}
	//}
	//else {
	//	mouseHeld = false;
	//}

	//if (e.getPosition().y > window->getSize().y) {
	//	deleted = true;

	//}

	//if (deleted) {
	//	// enemies.erase(enemies.begin() + i);
	//}
}

void Game::renderBlocks()
{
}