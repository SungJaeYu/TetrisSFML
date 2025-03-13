#include "Game.h"
#include <iostream>

const float FALL_INTERVAL = 0.7f;

void Game::initVariables()
{
	window = nullptr;
	endGame = false;
	score = 0;
}

void Game::initWindow()
{
	// Set VideoMode Size
	videoMode.size = sf::Vector2u(COLS * BLOCK_SIZE, ROWS * BLOCK_SIZE);

	// Create Window
	window = new sf::RenderWindow(videoMode, "Tetris", sf::Style::Titlebar | sf::Style::Close);

	// controll framerat
	window->setVerticalSyncEnabled(true); // call it once after creating the window
	window->setFramerateLimit(60); // call it once after creating the window
}

void Game::initText()
{
	if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
		endGame = true;
		return;
	}
	text = new sf::Text(font);
	text->setString("SCORE : " + std::to_string(score));    // 출력할 텍스트
	text->setCharacterSize(20);         // 글자 크기
	text->setFillColor(sf::Color::White); // 글자 색상
	text->setPosition({ BLOCK_SIZE * COLS - 100, BLOCK_SIZE });        // 위치 조정
}

Game::Game()
{
	initVariables();
	initText();
	initWindow();
	spawnTetromino();
}

Game::~Game()
{
	delete window;
	delete currentTetromino;
	delete text;
}

void Game::render()
{
	window->clear();

	renderTetromino();

	renderBoard();

	renderTexts();

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
				rotate();
				break;
			case sf::Keyboard::Scancode::Down:
				down();
				break;
			case sf::Keyboard::Scancode::Left:
				left();
				break;
			case sf::Keyboard::Scancode::Right:
				right();
				break;
			default:
				break;
			}
		}
		//else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
		//	switch (keyReleased->scancode) {
		//	case sf::Keyboard::Scancode::Space:
		//		// TODO: Save
		//		spacePressed = false;
		//		break;
		//	case sf::Keyboard::Scancode::Down:
		//		// Fast Down
		//		downPressed = false;
		//		break;
		//	case sf::Keyboard::Scancode::Left:
		//		leftPressed = false;
		//		// Left
		//		break;
		//	case sf::Keyboard::Scancode::Right:
		//		rightPressed = false;
		//		// Right
		//		break;
		//	default:
		//		break;
		//	}
		//}
	}
}

bool Game::isRunning()
{
	return !endGame;
}

void Game::spawnTetromino()
{
	currentTetromino = createTetromino();

	// spawn base position
	currentTetromino->setPosition(4, 0);

	if (checkCollisionCurrent()) {
		endGame = true;
	}
}

void Game::left()
{
	// Key Move Left
	if (!checkCollisionHorizontal(-1)) {
		currentTetromino->move(-1, 0);
	}
}

void Game::right()
{
	// Key Move Right
	if (!checkCollisionHorizontal(1)) {
		currentTetromino->move(1, 0);
	}
}

void Game::down()
{
	// Key Move Down
	if (!checkCollisionVertical(1)) {
		currentTetromino->move(0, 1);
	}
}

void Game::rotate()
{
	// Key Rotate Space
	currentTetromino->rotateCW();

	// If Collision Rotate Back
	if (checkCollisionCurrent()) {
		currentTetromino->rotateCCW();
	}
}

void Game::updateTetromino()
{
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
		
		score += board.addTetromino(*currentTetromino);

		delete currentTetromino;

		spawnTetromino();

		board.debugPrint();
	}
}

void Game::renderTetromino()
{
	currentTetromino->draw(*window);
}

void Game::renderBoard()
{
	board.draw(*window);
}

void Game::renderTexts()
{
	window->draw(*text);
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

bool Game::checkCollisionCurrent()
{
	// get position and shape
	sf::Vector2i currentPosition = currentTetromino->getPosition();
	std::vector<sf::Vector2i> shape = currentTetromino->getShape();

	for (int i = 0; i < 4; ++i) {
		if (currentPosition.x + shape[i].x < 0 || currentPosition.x + shape[i].x >= COLS) {
			return true;
		}

		if (currentPosition.y + shape[i].y >= ROWS) {
			return true;
		}

		if (!board.isEmpty(currentPosition.x + shape[i].x, currentPosition.y + shape[i].y)) {
			return true;
		}
	}
	return false;
}
