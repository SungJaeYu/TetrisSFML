#include "Game.h"
#include <iostream>

const float FALL_INTERVAL = 0.7f;

const int BLOCK_SIZE = 30;


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
	// Key Move Right
	if (rightPressed && !checkCollision(1, 0)) {
		currentTetromino->move(1, 0);
	} 

	// Key Move Left
	if (leftPressed && !checkCollision(-1, 0)) {
		currentTetromino->move(-1, 0);
	}
	// Key Move Down
	if (downPressed && !checkCollision(0, 1)) {
		currentTetromino->move(0, 1);
	}

	// Check Fall interval and Move Down
	elapsedTime += clock.restart().asSeconds();
	if (elapsedTime >= FALL_INTERVAL) {
		if (!checkCollision(0, 1)) {
			currentTetromino->move(0, 1);
		}
		elapsedTime = 0.f;  // Reset Timer
	}

	// TODO : Save Tetromino
	// if (saveTriggered) {
	//	   sf::RectangleShape* temp = &currentBlock;
	//     if (saveBlock) {
	//          *currentBlock = saveBlock;
	//     }
	//     saveBlock = *temp;
	//     currentBlock.setPosition({0,0f, 0,0f})


	// if block can't move, stop block
	if (checkCollision(0, 1)) {
		for (auto& block : currentTetromino->getBlocks()) {
			blocks.emplace_back(block);
		}

		std::vector<sf::Vector2i> shape = currentTetromino->getShape();
		sf::Vector2i pos = currentTetromino->getPosition();

		for (int i = 0; i < 4; ++i) {
			gameBoard[shape[i].y + pos.y][shape[i].x + pos.x] = 1;
		}

		delete currentTetromino;

		spawnTetromino();

		// For Debug
		printf("\n");
		for (int i = 0; i < ROWS; ++i) {
			for (int j = 0; j < COLS; ++j) {
				printf("%d", gameBoard[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}



}

void Game::clearLine()
{
	// if line is full, clear line
	for (int i = 0; i < ROWS; ++i) {
		bool isFull = true;
		for (int j = 0; j < COLS; ++j) {
			if (gameBoard[i][j] == 0) {
				isFull = false;
				break;
			}
		}
		if (isFull) {
			// remove line
			
		}
	}
}

void Game::renderTetromino()
{
	currentTetromino->draw(*window);

	for (auto& block : blocks) {
		window->draw(block);
	}
}
bool Game::checkCollision(int dx, int dy)
{
	// get position
	sf::Vector2i currentPosition = currentTetromino->getPosition();
	sf::Vector2i size = currentTetromino->getSize();

	int newPositionX = currentPosition.x + dx;
	int newPositionY = currentPosition.y + dy;


	if (newPositionX < 0 || newPositionX + size.x >= COLS) {
		return true;
	}
	
	std::vector<sf::Vector2i> shape = currentTetromino->getShape();

	for (int i = 0; i < 4; ++i) {
		if (newPositionY + shape[i].y >= ROWS) {
			return true;
		}
		if (gameBoard[newPositionY + shape[i].y][newPositionX + shape[i].x]) {
			return true;
		}
	}
	return false;

	
}