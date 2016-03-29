#include "main.h"

void InitLevel1()
{
	theMap = new Map();
	player = new Player(theMap);
	player->Initialize();
	player->SetX(100);
	player->SetY(100);

	theMap->LoadLevel(3);
	player->SetStartPos(theMap->GetStartX(), theMap->GetStartY());
}

int main(int argc, char *argv[])
{
	RenderWindow window(VideoMode(Data::Instance()->SCREEN_WIDTH, Data::Instance()->SCREEN_HEIGHT, 32), "Game");

	window.setFramerateLimit(60);

	window.setVerticalSyncEnabled(false);

	input = new Input();

	if (!font.loadFromFile("font/arial.ttf"))
	{
		// Error
		cout << "Error while loading the font of the player." << endl;
	}
	else
	{
		lvl1.setFont(font);
		lvl2.setFont(font);
		lvl3.setFont(font);
		quit.setFont(font);
		title.setFont(font);
	}

	// Gameplay loop
	while (window.isOpen())
	{
		input->gestionInputs(window);

		if (inMenu)
		{
			window.clear();

			lvl1.setColor(baseColor);
			lvl2.setColor(baseColor);
			lvl3.setColor(baseColor);
			quit.setColor(baseColor);
			title.setColor(baseColor);

			lvl1.setCharacterSize(20);
			lvl2.setCharacterSize(20);
			lvl3.setCharacterSize(20);
			quit.setCharacterSize(20);
			title.setCharacterSize(40);

			lvl1.setStyle(sf::Text::Bold);
			lvl2.setStyle(sf::Text::Bold);
			lvl3.setStyle(sf::Text::Bold);
			quit.setStyle(sf::Text::Bold);
			title.setStyle(sf::Text::Bold);

			lvl1.setString("Level 1");
			lvl2.setString("Level 2");
			lvl3.setString("Level 3");
			quit.setString("Quit");
			title.setString("BOMB DEFUSER");

			int midWidth = Data::Instance()->SCREEN_WIDTH / 3;
			int midHeight = Data::Instance()->SCREEN_HEIGHT / 3;

			int size = 400;
			sf::RectangleShape rectangle(sf::Vector2f(size, size));
			rectangle.setPosition(midWidth - (size / 4), midHeight - (size / 4));
			rectangle.setFillColor(sf::Color(50, 50, 50));

			window.draw(rectangle);

			if (indexMenu == 0)
			{
				lvl1.setColor(selectedColor);
			}
			else if (indexMenu == 1)
			{
				lvl2.setColor(selectedColor);
			}
			else if (indexMenu == 2)
			{
				lvl3.setColor(selectedColor);
			}
			else if (indexMenu == 3)
			{
				quit.setColor(selectedColor);
			}

			lvl1.setPosition(Vector2f(midWidth, midHeight - 100));
			lvl2.setPosition(Vector2f(midWidth, midHeight));
			lvl3.setPosition(Vector2f(midWidth, midHeight + 100));
			quit.setPosition(Vector2f(midWidth, midHeight + 200));
			title.setPosition(Vector2f(midWidth - 100, midHeight / 8));

			window.draw(lvl1);
			window.draw(lvl2);
			window.draw(lvl3);
			window.draw(quit);
			window.draw(title);

			window.display();

			if (input->getButton().down == true)
			{
				indexMenu ++;
				indexMenu = min(3, indexMenu);
			}
			else if(input->getButton().up == true)
			{
				indexMenu --;
				indexMenu = max(0, indexMenu);
			}
			else if (input->getButton().action == true)
			{
				if (indexMenu == 0)
				{
					inMenu = false;
					InitLevel1();
				}
				else
				{
					return 0;
				}
			}

			sleep(Time(milliseconds(100)));
		}
		else
		{

			if (input->getButton().restart == true)
			{
				InitLevel1();
			}
			else
			{

				Time time = theClock.restart();

				player->Update(input);
				player->mapCollision(theMap);

				window.clear();

				theMap->DrawBackground(window);

				theMap->UpdateBomb();
				theMap->DrawBomb(window);

				theMap->DrawTiles(window);

				theMap->UpdatePowers();
				theMap->DrawPowers(window);

				theMap->UpdateBlockers();
				theMap->DrawBlockers(window);

				theMap->UpdateEnding();
				theMap->DrawEnding(window);

				player->Draw(window);

				Debug::Instance()->PrintDebug(window);

				window.display();

				if (player->GetWantsTheMenu())
				{
					inMenu = true;

					sleep(Time(seconds(1)));
				}
			}
		}
	}

	delete input;
	delete theMap;
	delete player;

	return 0;
}
