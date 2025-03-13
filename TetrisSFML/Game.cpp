#include "Game.h"
#include <iostream>

const float FALL_INTERVAL = 0.7f;

void Game::initVariables()
{
	window = nullptr;
	endGame = false;

	health = 100;
	points = 0;

	// key check
	leftPressed = false;
	rightPressed = false;
	downPressed = false;
	spacePressed = false;
	saveTriggered = false;
}

void Game::initWindow()
{
	// Set VideoMode Size
	videoMode.size = sf::Vector2u(COLS * BLOCK_SIZE, ROWS * BLOCK_SIZE);

	// Create Window
	window = new sf::RenderWindow(videoMode, "Tetris", sf::Style::Titlebar | sf::Style::Close);

	// controll framerat
	window->setVerticalSyncEnabled(true); // call it once after creating the window
	window->setFramerateLimit(30); // call it once after creating the window
}

Game::Game()
{
	initVariables();
	initWindow();
	spawnTetromino();
}

Game::~Game()
{
	delete window;
	delete currentTetromino;
}

void Game::render()
{
	window->clear();

	renderTetromino();

	board.draw(*window);

	window->display();
}

void Game::update()
{
	pollEvents();

	updateTetromino();
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
				// Rotate
				spacePressed = true;
				break;
			case sf::Keyboard::Scancode::Down:
				// Fast Down
				downPressed = true;
				break;
			case sf::Keyboard::Scancode::Left:
				// Left
				leftPressed = true;
				break;
			case sf::Keyboard::Scancode::Right:
				// Right
				rightPressed = true;
				break;
			default:
				break;
			}
		}
		else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
			switch (keyReleased->scancode) {
			case sf::Keyboard::Scancode::Space:
				// TODO: Save
				spacePressed = false;
				break;
			case sf::Keyboard::Scancode::Down:
				// Fast Down
				downPressed = false;
				break;
			case sf::Keyboard::Scancode::Left:
				leftPressed = false;
				// Left
				break;
			case sf::Keyboard::Scancode::Right:
				rightPressed = false;
				// Right
				break;
			default:
				break;
			}
		}
	}
}

bool Game::isRunning()
{
	return window->isOpen();
}

void Game::spawnTetromino()
{
	currentTetromino = createTetromino();
	currentTetromino->setPosition(4, 0);
}

void Game::updateTetromino()
{
	// Key Rotate Space
	if (spacePressed) {
		currentTetromino->rotate();
	}

	// Key Move Right
	if (rightPressed && !checkCollisionHorizontal(1)) {
		currentTetromino->move(1, 0);
	} 

	// Key Move Left
	if (leftPressed && !checkCollisionHorizontal(-1)) {
		currentTetromino->move(-1, 0);
	}
	// Key Move Down
	if (downPressed && !checkCollisionVertical(1)) {
		currentTetromino->move(0, 1);
	}

	// Check Fall interval and Move Down
	elapsedTime += clock.restart().asSeconds();
	if (elapsedTime >= FALL_INTERVAL) {
		if (!checkCollisionVertical(1)) {
			currentTetromino->move(0, 1);
		}
		elapsedTime = 0.f;  // Reset Timer
	}

	// if block can't move, stop block
	if (checkCollisionVertical(1)) {
		
		board.addTetromino(*currentTetromino);

		delete currentTetromino;

		spawnTetromino();

		board.debugPrint();
	}
}

void Game::renderTetromino()
{
	currentTetromino->draw(*window);
}

bool Game::checkCollisionHorizontal(int dx)
{
	// get position and shape
	sf::Vector2i currentPosition = currentTetromino->getPosition();
	std::vector<sf::Vector2i> shape = currentTetromino->getShape();

	int newPositionX = currentPosition.x + dx;

	for (int i = 0; i < 4; ++i) {
		if (newPositionX + shape[i].x < 0 || newPositionX + shape[i].x >= COLS) {
			return true;
		}

		if (!board.isEmpty(newPositionX + shape[i].x, currentPosition.y + shape[i].y)) {
			return true;
		}
	}
	return false;
}

bool Game::checkCollisionVertical(int dy)
{
	// get position and shape
	sf::Vector2i currentPosition = currentTetromino->getPosition();
	std::vector<sf::Vector2i> shape = currentTetromino->getShape();

	int newPositionY = currentPosition.y + dy;


	for (int i = 0; i < 4; ++i) {
		if (newPositionY + shape[i].y >= ROWS) {
			return true;
		}

		if (!board.isEmpty(currentPosition.x + shape[i].x, newPositionY + shape[i].y)) {
			return true;
		}
	}
	return false;
}
