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
	videoMode.size = sf::Vector2u(270, 720);

	// Create Window
	window = new sf::RenderWindow(videoMode, "Tetris", sf::Style::Titlebar | sf::Style::Close);

	// controll framerate
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
}

void Game::render()
{
	window->clear();

	renderTetromino();

	window->display();
}

void Game::update()
{
	pollEvents();

	updateTetromino();

	clearLine();
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
				if (spacePressed == false) {
					saveTriggered = true;
				}
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
	//enemy.setPosition(
	//	static_cast<float>(rand() % static_cast<int>(window->getSize().x - enemy.getSize().x)),
	//	static_cast<float>(rand() % static_cast<int>(window->getSize().y - enemy.getSize().y))
	//);
	currentTetromino = createTetromino();
	currentTetromino->setPosition(4, 0);
}

void Game::updateTetromino()
{
	int dx = 0;
	int dy = 0;

	if (downPressed) {
		dy += 1;
	}
	if (rightPressed) {
		dx += 1;
	} 
	if (leftPressed) {
		dx -= 1;
	}

	// 일정 시간마다 블록 자동 낙하
	elapsedTime += clock.restart().asSeconds();
	if (elapsedTime >= FALL_INTERVAL) {
		dy += 1;
		elapsedTime = 0.f;  // 타이머 초기화
	}

	// get position
	sf::Vector2i currentPosition = currentTetromino->getPosition();
	
	int newPositionX = currentPosition.x + dx;
	int newPositionY = currentPosition.y + dy;

	if (newPositionX >= 8) {
		newPositionX = 8;
	}
	else if (newPositionX <= 0) {
		newPositionX = 0;
	}


	// moving down block
	currentTetromino->setPosition(newPositionX, newPositionY);

	// if block can't move, stop block
	// if (block cant'move) {
	if (newPositionY >= 22) {
		for (auto& block : currentTetromino->getBlocks()) {
			blocks.emplace_back(block);
		}

		delete currentTetromino;

		spawnTetromino();
	}
	// save
	// if (saveTriggered) {
	//	   sf::RectangleShape* temp = &currentBlock;
	//     if (saveBlock) {
	//          *currentBlock = saveBlock;
	//     }
	//     saveBlock = *temp;
	//     currentBlock.setPosition({0,0f, 0,0f})
}

void Game::clearLine()
{
	// if line is full, clear line
}

void Game::renderTetromino()
{
	currentTetromino->draw(*window);

	for (auto& block : blocks) {
		window->draw(block);
	}
} 