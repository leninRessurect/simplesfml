#include "Game.h"

// private functions
void Game::initVariables()
{
	this->window = nullptr;

	// game logic
	this->points = 0;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(videoMode, "My Window", sf::Style::Titlebar | sf::Style::Close);
	
	this->window->setFramerateLimit(60);
}


void Game::initEnemies()
{	
	this->enemy.setPosition(100.f, 100.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Cyan);
	//this->enemy.setOutlineColor(sf::Color::Green);
	//this->enemy.setOutlineThickness(1.f);
}

// constructors / destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}

// accessors
const bool Game::running() const
{
	return this->window->isOpen();
}



// functions 
void Game::spawnEnemy()
{
	/*
	@return void
	
	spawns enemies and sets their colors and positions
	-sets a random position
	-sets a random color
	-adds enemy to the vector
	*/

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

	this->enemy.setFillColor(sf::Color::Green);

	//spawn enemy
	this->enemies.push_back(this->enemy);

	// remove enemies at end of screen
	
}

void Game::pollEvents()
{
	// event polling
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::updateMousePositions()
{
	/*
	return void
	updates mouse positions
	-relative to window (vector2i)
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

}

void Game::updateEnemies()
{
	/*
	@return void
	updates the enemy spawn timer and spawns enemies
	when the total amount of enemies is smaller that the maxim
	moves the enemies downwards
	removes the enemies at the edge of the screen. //TODO
	*/

	//updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//spawn enemy and reset timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	//moving and updating enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;

		this->enemies[i].move(0.5f, 5.f);

		// check if clicked upon
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
			{
				deleted = true;

				//gain points
				this->points += 10.f;
				std::cout << this->points << std::endl;
			}
		}

		// if the enemy is past the bottom of the screen
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			deleted = true;
		}

		//final delete
		if (deleted)
		{
			this->enemies.erase(this->enemies.begin() + i);
		}
	}
}

void Game::update()
{
	this->pollEvents();

	this->updateMousePositions();

	this->updateEnemies();

}

void Game::renderEnemies()
{
	// rendering all the enemies
	for (auto &e : this->enemies)
	{
		this->window->draw(e);
	}
}

void Game::render()
{
	/*
	renders the game objects
	-clear old frame
	-render objects
	-display frame in window
	return void
	*/

	this->window->clear(sf::Color::Black);

	// draw game objects
	this->renderEnemies();

	this->window->display();
}


