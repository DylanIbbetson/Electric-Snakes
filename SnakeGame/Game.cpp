#include "Game.h"
#include "snake.h"
#include "Collectable.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "time.h"
#include "PlayerSnake.h"
#include "AISnake.h"
#include "Battery.h"

void Game::Run()
{
	float GameTimer = 0.0f;
	srand((unsigned)time(0));

	//Rendering the window for the game to display on
	sf::RenderWindow window(sf::VideoMode(1200, 900), "C++ Snake ICA : U0018197");

	//Pushing a player snake and some AI snakse into a vector and setting their position and colour
	m_Snakes.push_back(new PlayerSnake(sf::Vector2f(450, 450), sf::Color::Green));
	m_Snakes.push_back(new AISnake(sf::Vector2f(150, 750), sf::Color::Cyan));
	m_Snakes.push_back(new AISnake(sf::Vector2f(750, 750), sf::Color::Magenta));
	m_Snakes.push_back(new AISnake(sf::Vector2f(150, 150), sf::Color::Blue));
	m_Snakes.push_back(new AISnake(sf::Vector2f(750, 150), sf::Color(255, 174, 0, 255)));


	//Creating collectables and a battery and pushing them into a vector, then setting their position
	for (int i = 0; i < 4; i++)
	{
		m_collectables.push_back(new Collectable(sf::Vector2f(-20, -20)));
	}

	for (int i = 0; i < 1; i++)
	{
		m_battery.push_back(new Battery(sf::Vector2f()));
	}




	sf::Clock clock;


	std::cout << "SnakeGame: Starting" << std::endl;

	//Loading the font used for the UI
	sf::Font font;
	font.loadFromFile("SnakeFont.ttf");
	if (!font.loadFromFile("SnakeFont.ttf"))
	{
		std::cerr << "Failed to load font\n";
		return;
	}




	// Main loop that continues until we call window.close()

	while (window.isOpen())
	{
		int counter = 4;

		// Handle any pending SFML events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}


		//Setting the game to end once 90 seconds has passed

		if (GameTimer > 91)
			window.close();

		for (Snake* snake : m_Snakes)
		{
			if (!snake->getIsAlive())
			{
				counter--;
			}
			
			if (counter == 0)
			{
				window.close();
			}
		}



		//Calling the update function and checking the timer for the battery if it is active

		for (Snake* snake : m_Snakes)
		{
			if (snake->SnakeAlive == true)
			{
				snake->GetAllPositions(AllSegments);
				snake->Update();


				if (snake->GetBatteryActive())
				{
					snake->CheckTimer();
				}

			}

		}

		GetAllSegmentPositions();

		//Spawning Collectables and batteries

		if (rand() % 20 == 0)
		{
			for (Collectable* collectable : m_collectables)
			{
				if (!collectable->Collected())
				{

					collectable->Spawn();
					break;
				}
			}
		}

		if (rand() % 20 == 0)
		{
			for (Battery* battery : m_battery)
			{
				if (!battery->Collected())
				{

					battery->Spawn();
					break;
				}
			}
		}


		// We must clear the window each time around the loop
		window.clear();

		//Drawing a line to separate the play area from the UI 

		sf::RectangleShape line(sf::Vector2f(10, 900));
		line.setFillColor(sf::Color::White);
		line.setPosition(900, 0);
		window.draw(line);

		//Drawing text on the screen for the scores of both player snake and AI snake

		//Finding the score for each of the snakes in the game
		int PlayerScore = m_Snakes[0]->FindScore();
		int Snake2Score = m_Snakes[1]->FindScore();
		int Snake3Score = m_Snakes[2]->FindScore();
		int Snake4Score = m_Snakes[3]->FindScore();
		int Snake5Score = m_Snakes[4]->FindScore();

		sf::Text text1;
		text1.setFont(font);
		text1.setString("Player Score - " + std::to_string(PlayerScore) + '\n');
		text1.setCharacterSize(24);
		text1.setFillColor(sf::Color::Green);
		text1.setPosition(950, 70);

		sf::Text text2;
		text2.setFont(font);
		text2.setString("Snake2 Score - " + std::to_string(Snake2Score) + '\n');
		text2.setCharacterSize(24);
		text2.setFillColor(sf::Color::Cyan);
		text2.setPosition(950, 100);

		sf::Text text3;
		text3.setFont(font);
		text3.setString("Snake3 Score - " + std::to_string(Snake3Score) + '\n');
		text3.setCharacterSize(24);
		text3.setFillColor(sf::Color::Magenta);
		text3.setPosition(950, 130);

		sf::Text text4;
		text4.setFont(font);
		text4.setString("Snake4 Score - " + std::to_string(Snake4Score) + '\n');
		text4.setCharacterSize(24);
		text4.setFillColor(sf::Color::Blue);
		text4.setPosition(950, 160);

		sf::Text text5;
		text5.setFont(font);
		text5.setString("Snake5 Score - " + std::to_string(Snake5Score) + '\n');
		text5.setCharacterSize(24);
		text5.setFillColor(sf::Color(255, 174, 0, 255));
		text5.setPosition(950, 190);

		//Drawing the timer on screen
		sf::Text Timer;
		int GameTime2 = 90;
		int GameTime3 = GameTimer;
		Timer.setFont(font);
		Timer.setString(std::to_string(GameTime2 - GameTime3));
		Timer.setCharacterSize(72);
		Timer.setFillColor(sf::Color::White);
		Timer.setPosition(1020, 400);


		window.draw(text1);
		window.draw(text2);
		window.draw(text3);
		window.draw(text4);
		window.draw(text5);
		window.draw(Timer);

		//Checking the vector of snakes against the next index in the vector for collisions with each other

		//for (Snake* snake : m_Snakes)
		//{
		//	if (snake->SnakeAlive == true)
		//	{
		//		for (int Snake1 = 0; Snake1 < m_Snakes.size(); Snake1++)
		//		{
		//			for (int Snake2 = Snake1 + 1; Snake2 < m_Snakes.size(); Snake2++)
		//			{
		//				m_Snakes[Snake1]->CheckOtherCollisions(*m_Snakes[Snake2]);
		//			}
		//		}

		//		for (int Snake2 = 0; Snake2 < m_Snakes.size(); Snake2++)
		//		{
		//			for (int Snake1 = Snake2 + 1; Snake1 < m_Snakes.size(); Snake1++)
		//			{
		//				m_Snakes[Snake2]->CheckOtherCollisions(*m_Snakes[Snake1]);
		//			}
		//		}
		//	}
		//}



		//Checking the vector of snakes against the next index in the vector for collisions with the battery aura
		for (Snake* snake : m_Snakes)
		{
			if ((snake->getIsAlive() && snake->GetBatteryActive()))
			{
				for (int Snake1 = 0; Snake1 < m_Snakes.size(); Snake1++)
				{
					for (int Snake2 = Snake1 + 1; Snake2 < m_Snakes.size(); Snake2++)
					{
						m_Snakes[Snake1]->CheckAuraCollisions(*m_Snakes[Snake2]);
					}
				}

				for (int Snake2 = 0; Snake2 < m_Snakes.size(); Snake2++)
				{
					for (int Snake1 = Snake2 + 1; Snake1 < m_Snakes.size(); Snake1++)
					{
						m_Snakes[Snake2]->CheckAuraCollisions(*m_Snakes[Snake1]);
					}
				}
			}

		}

		//Checking the snakes collisions with collectables, walls, and themselves

		for (Snake* snake : m_Snakes)
			if (snake->SnakeAlive == true)
				snake->CheckCollisions(m_collectables);

		for (Snake* snake : m_Snakes)
			if (snake->SnakeAlive == true)
				snake->CheckBatteryCollisions(m_battery);



		for (Snake* snake : m_Snakes)
			if (snake->SnakeAlive == true)
				snake->CheckWallCollisions(window);

		for (Snake* snake : m_Snakes)
		{
			if (snake->SnakeAlive == true)
				snake->CheckSelfCollisions();
		}


		//Rendering the snake 

		for (Snake* snake : m_Snakes)
		{
			if (snake->SnakeAlive == true)
			{
				snake->render(window);
			}
		}

		//Rendering the aura given by the battery

		for (Snake* snake : m_Snakes)
		{
			if (snake->GetBatteryActive())
			{
				snake->AddAura(window);
			}
		}

		//Rendering the collectables

		for (Collectable* collectable : m_collectables)
		{
			if (collectable->visible == true)
				collectable->Render(window);
		}

		for (Battery* battery : m_battery)
			if (battery->visible == true)
				battery->Render(window);




		// Get the window to display its contents
		window.display();



		//Calculating the game timer and resetting the clock every 100 milliseconds
		while (clock.getElapsedTime().asMilliseconds() < 100);
		{
			GameTimer = GameTimer + 0.10;


			clock.restart();
		}
			
	}

	for (Snake* snake : m_Snakes)
		delete snake;


	std::cout << "SnakeGame: Finished" << std::endl;


}
//A getter for finding all of the segments of every snake
void Game::GetAllSegmentPositions()
{
	for (Snake*snake : m_Snakes)
	{
		for (auto& segments : snake->GetSegments())
		{
			AllSegments.push_back(segments);
		}
	}
}
