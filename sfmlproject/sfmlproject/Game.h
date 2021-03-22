#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


/*
	class that acts as the game engine.
	wrapper class.
*/
class Game
{
private:

	// variables
	// window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	// mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// game logic
	int points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;


	// game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	//private functions
	void initVariables();
	void initWindow();
	void initEnemies();


public:
	// constructors / destructors
	Game();
	virtual ~Game();

	// accessors
	const bool running() const;

	// functions
	void spawnEnemy();
	void pollEvents();
	void updateMousePositions();
	void updateEnemies();
	void update();
	void renderEnemies();
	void render();
};

