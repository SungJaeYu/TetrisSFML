#include "Game.h"
#include <iostream>

void Game::initVariables()
{
	window = nullptr;
	endGame = false;
	health = 100;
	points = 0;
	leftPressed = false;
	rightPressed = false;
	downPressed = false;
	spacePressed = false;
	saveTriggered = false;

}

void Game::initWindow()
{
	// Set VideoMode Size
	videoMode.size = sf::Vector2u(480, 720);

	// Create Window
	window = new sf::RenderWindow(videoMode, "Tetris", sf::Style::Titlebar | sf::Style::Close);

	// controll framerate
	window->setVerticalSyncEnabled(true); // call it once after creating the window
	window->setFramerateLimit(60); // call it once after creating the window
}

Game::Game()
{
	initVariables();
	initWindow();
	spawnBlock();
}

Game::~Game()
{
	delete window;
	for (auto& block : blocks) {
		delete block;
	}
}

void Game::render()
{
	window->clear();

	renderBlocks();

	window->display();
}

void Game::update()
{
	pollEvents();

	updateBlock();

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

void Game::spawnBlock()
{
	//enemy.setPosition(
	//	static_cast<float>(rand() % static_cast<int>(window->getSize().x - enemy.getSize().x)),
	//	static_cast<float>(rand() % static_cast<int>(window->getSize().y - enemy.getSize().y))
	//);
	currentBlock = new sf::RectangleShape(sf::Vector2f(200.f, 100.f));
	currentBlock->setPosition({ 100.f, 100.f });  // 위치 (300, 250)
	currentBlock->setFillColor(sf::Color::Green);  // 색상 설정

	blockSpawned = true;

}

void Game::updateBlock()
{
	// If no moving block on screen
	if (!blockSpawned) {
		spawnBlock();
	}

	// moving down block
	float moveSpeed = 1.f;
	if (downPressed) {
		moveSpeed *= 2;
	}

	float direction = 0.f;
	if (rightPressed) {
		direction = 1.f;
	} 
	if (leftPressed) {
		direction = -1.f;
	}

	// moving down block
	currentBlock->move({ direction, moveSpeed });

	// if block can't move, stop block
	// if (block cant'move) {
	auto position = currentBlock->getPosition();
	if (position.y >= 500.f) {
		blocks.push_back(currentBlock);
		blockSpawned = false;
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

void Game::renderBlocks()
{
	window->draw(*currentBlock);

	for (auto& block : blocks) {
		window->draw(*block);
	}
} 