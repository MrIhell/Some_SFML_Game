#include <SFML/Game.hpp>


#include <iostream>


const float Game::PlayerSpeed = 300.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);


Game::Game()
	: mWindow(sf::VideoMode(1920,1080), "SFML Application")
	, mPlayer()
	, mIsMovingUp(false)
	, mIsMovingDown(false)
	, mIsMovingRight(false)
	, mIsMovingLeft(false)

{

	//mWindow.sf::RenderWindow::setVerticalSyncEnabled(true);

	if (!troll_face.loadFromFile("C:/1All_Shit/Visual_Studio_Shit/SFML_New/Cock/Troll_Face.png"))
	{	
		std::cout << "lol";  
	}
	 

	mPlayer.circle.setPosition(960.f, 540.f);
	mPlayer.x = 960;
	mPlayer.y = 540;										/////////////////////////////
	mPlayer.circle.setRadius(40.f);
	mPlayer.radius = 15;


	srand(time(NULL));

	Ball ball;

	ball.circle.setPosition(0.f, 0.f);



	float rand_x = rand() % 1920 + 1;
	float rand_y = rand() % 1080 + 1;
	float rand_rad = rand() % 150 + 5;
	int Now = 15;

	//std::cout << rand_x << " " << rand_y << " " << rand_rad << "????" << std::endl;

	// "if" in the wall or Player 
	while ((Now <= rand_rad)||((rand_x + rand_rad * 2 > 1920) || (rand_y + rand_rad * 2 > 1080)) || ((abs(rand_x + rand_rad - mPlayer.circle.getPosition().x - mPlayer.circle.getRadius()) < (rand_rad + mPlayer.circle.getRadius())) || (abs(rand_y + rand_rad - mPlayer.circle.getPosition().y - mPlayer.circle.getRadius()) < (rand_rad + mPlayer.circle.getRadius()))))
	{
		//std::cout << rand_x << " " << rand_y << " " << rand_rad << " " << "????? FIRST" << std::endl;

		rand_x = rand() % 1920 + 1;
		rand_y = rand() % 1080 + 1;
		rand_rad = rand() % 150 + 5;

	}
	//std::cout << rand_x << " " << rand_y << " " << rand_rad << " " << "!!!!! FIRST" << std::endl;
	ball.circle.setPosition(rand_x, rand_y);
	ball.circle.setRadius(rand_rad);
	balls.push_back(ball);

	rand_x = rand() % 1920 + 1;
	rand_y = rand() % 1080 + 1;
	rand_rad = rand() % 150 + 5;

	
	
	for (int i = 1; i < 10; i++)
	{

		for (int j = i - 1; j >= 0; j--)
		{
			Now += balls[j].circle.getRadius();
		}

		for (int j = i-1; j >= 0; j--)
		{

			//std::cout << rand_x << " " << rand_y << " " << rand_rad << std::endl;

			if (((rand_x + rand_rad * 2 > 1920) || (rand_y + rand_rad * 2 > 1080)) || ((abs(rand_x + rand_rad - mPlayer.circle.getPosition().x - mPlayer.circle.getRadius()) < (rand_rad + mPlayer.circle.getRadius())) || (abs(rand_y + rand_rad - mPlayer.circle.getPosition().y - mPlayer.circle.getRadius()) < (rand_rad + mPlayer.circle.getRadius()))))
			{
				i--;
				//std::cout <<std::endl <<"   Shit    ";
				rand_x = rand() % 1920 + 1;
				rand_y = rand() % 1080 + 1;
				rand_rad = rand() % 150 + 5;

				break;
			}

			//std::cout << "Nice 1  " << j;

			if ((abs(rand_x + rand_rad - balls[j].circle.getPosition().x - balls[j].circle.getRadius()) < (rand_rad + balls[j].circle.getRadius())) || (abs(rand_y + rand_rad - balls[j].circle.getPosition().y - balls[j].circle.getRadius()) < (rand_rad + balls[j].circle.getRadius())))
			{
				i--;
				//std::cout <<std::endl <<"   Shit   ";
				rand_x = rand() % 1920 + 1;
				rand_y = rand() % 1080 + 1;
				rand_rad = rand() % 150 + 5;

				break;
			}

			if (Now <= rand_rad)
			{
				i--;
				//std::cout << std::endl << "   Shit   ";
				rand_x = rand() % 1920 + 1;
				rand_y = rand() % 1080 + 1;
				rand_rad = rand() % 150 + 5;

				break;
			}

			std::cout << "Nice 2  " << j ;

			if (j == 0)
			{
				//std::cout << rand_x << " " << rand_y << " " << rand_rad << " " << i << "!!!!!" << std::endl;
				ball.circle.setPosition(rand_x, rand_y);
				ball.circle.setRadius(rand_rad);
				balls.push_back(ball);

				rand_x = rand() % 1920 + 1;
				rand_y = rand() % 1080 + 1;
				rand_rad = rand() % 150 + 5;
				Now = 15;
			}

		}
		
			
		
		/*ball.circle.setPosition(rand_x, rand_y);
		ball.circle.setRadius(rand_rad);*/

		//balls.push_back(ball);
	}

	

}


void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		
		render();
	}
}


void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		//std::cout << event.type << std::endl;
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			//std::cout << "KeyPressed" << std::endl;
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			//std::cout << "KeyReleased" << std::endl;
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}


void Game::update(sf::Time deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp && mPlayer.circle.getPosition().y > 0) {
		movement.y -= PlayerSpeed;
		mPlayer.y = mPlayer.circle.getPosition().y - 1;
		mPlayer.y--;
		

	}
	if (mIsMovingDown && mPlayer.circle.getPosition().y + mPlayer.circle.getRadius()*2 < /*mWindow.getSize().y+mPlayer.circle.getRadius()*/1080) {
		movement.y += PlayerSpeed;
		mPlayer.y = mPlayer.circle.getPosition().y + 1;
		mPlayer.y++;
		std::cout << "Yes"<<std::endl;
	
	}
	if (mIsMovingLeft && mPlayer.circle.getPosition().x > 0) {
		movement.x -= PlayerSpeed;
		mPlayer.x = mPlayer.circle.getPosition().x - 1;
		mPlayer.x--;


	}
	if (mIsMovingRight && mPlayer.circle.getPosition().x + 2 * mPlayer.circle.getRadius() < mWindow.getSize().x) {
		movement.x += PlayerSpeed;
		mPlayer.x = mPlayer.circle.getPosition().x + 1;
		mPlayer.x++;

	}

	//mPlayer.move(movement * deltaTime.asSeconds());
	mPlayer.circle.move(movement * deltaTime.asSeconds());
	
	
	for (int i = 0; i < balls.size(); i++)
	{
//		if(((mPlayer.circle.getPosition().x + mPlayer.circle.getRadius() * 2 > 1920) || (mPlayer.circle.getPosition().y + mPlayer.circle.getRadius() * 2 > 1080)) || ((abs(rand_x + rand_rad - mPlayer.circle.getPosition().x + mPlayer.circle.getRadius()) < (rand_rad + mPlayer.circle.getRadius())) || (abs(rand_y + rand_rad - mPlayer.circle.getPosition().y + mPlayer.circle.getRadius()) < (rand_rad + mPlayer.circle.getRadius())))

	

		if (((abs(mPlayer.circle.getPosition().x + mPlayer.circle.getRadius() - balls[i].circle.getPosition().x - balls[i].circle.getRadius()) < (mPlayer.circle.getRadius() + balls[i].circle.getRadius())) && (abs(mPlayer.circle.getPosition().y + mPlayer.circle.getRadius() - balls[i].circle.getPosition().y - balls[i].circle.getRadius()) < (mPlayer.circle.getRadius() + balls[i].circle.getRadius()))))
		{
			if (mPlayer.circle.getRadius() > balls[i].circle.getRadius()) 
			{
				/*std::cout << "Smaller guy"<<std::endl;

				std::cout << mPlayer.circle.getPosition().x << " " << mPlayer.circle.getRadius() << " " << balls[i].circle.getPosition().x << " " << balls[i].circle.getRadius() << std::endl;

				std::cout << mPlayer.circle.getPosition().y << " " << mPlayer.circle.getRadius() << " " << balls[i].circle.getPosition().y << " " << balls[i].circle.getRadius() << std::endl;

				std::cout << abs(mPlayer.circle.getPosition().x + mPlayer.circle.getRadius() - balls[i].circle.getPosition().x - balls[i].circle.getRadius()) << "    " << mPlayer.circle.getRadius() + balls[i].circle.getRadius() << std::endl;
				std::cout << abs(mPlayer.circle.getPosition().y + mPlayer.circle.getRadius() - balls[i].circle.getPosition().y - balls[i].circle.getRadius()) << "    " << mPlayer.circle.getRadius() + balls[i].circle.getRadius() << std::endl;*/
				mPlayer.circle.setRadius(mPlayer.circle.getRadius() + balls[i].circle.getRadius());
				balls.erase(balls.begin()+i);
				if (balls.size() == 0)
				{
					std::exit(NULL);
				}
				
			}
			else
			{
				/*std::cout << "Bigger guy"<<std::endl;
				std::cout << mPlayer.circle.getPosition().x << " " << mPlayer.circle.getRadius() << " " << balls[i].circle.getPosition().x << " " << balls[i].circle.getRadius() << std::endl;

				std::cout << mPlayer.circle.getPosition().y << " " << mPlayer.circle.getRadius() << " " << balls[i].circle.getPosition().y << " " << balls[i].circle.getRadius() << std::endl;

				std::cout << abs(mPlayer.circle.getPosition().x + mPlayer.circle.getRadius() - balls[i].circle.getPosition().x - balls[i].circle.getRadius()) << "    " << mPlayer.circle.getRadius() + balls[i].circle.getRadius() << std::endl;
				std::cout << abs(mPlayer.circle.getPosition().y + mPlayer.circle.getRadius() - balls[i].circle.getPosition().y - balls[i].circle.getRadius()) << "    " << mPlayer.circle.getRadius() + balls[i].circle.getRadius() << std::endl;*/

				exit(NULL);  
			}
		}

	}
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mPlayer.circle);
	
	sf::CircleShape c;
	
	for (int i = 0; i < balls.size()/*Or without "-1"  */; i++)
	{
		mWindow.draw(balls[i].circle);
		/*c = balls[i].circle;
		c.setFillColor(sf::Color::Yellow);
		c.setRadius(10+i*2);
		mWindow.draw(c);*/
	}

	mWindow.display();
}


void Game::handlePlayerInput(sf::Keyboard::Key key,
	bool isPressed)
{
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
}

Ball::Ball()
	:color(sf::Color::Cyan)
{
	circle.setFillColor(color);
}

Player::Player()
{
	color=sf::Color::Red;
	circle.setFillColor(color);
}