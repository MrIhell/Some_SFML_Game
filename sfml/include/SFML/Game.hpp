#pragma once

#ifndef NEW_GAME_HPP
#define NEW_GAME_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <stdlib.h>




class Ball
{


public:
	float speed;
	float radius;
	float x;
	float y;
	sf::Color color;
	sf::CircleShape circle;


	Ball();

};



class Player : public Ball
{
public:
	Player();
};



class Game
{
public:

	Game();

	void run(); 


private:
	void processEvents();
	void update(sf::Time);	
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
	static const float PlayerSpeed;
	static const sf::Time TimePerFrame;

	sf::RenderWindow mWindow;
	Player mPlayer;
	sf::Texture troll_face;
	sf::Sprite troll_sprite;

private:
	std::vector <Ball> balls;


	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingRight;
	bool mIsMovingLeft;
};




#endif NEW_GAME_HPP
