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
	theMap->PlayMusic();
}

int main(int argc, char *argv[])
{
	RenderWindow window(VideoMode(Data::Instance()->SCREEN_WIDTH, Data::Instance()->SCREEN_HEIGHT, 32), "Bomb Defuser");

	window.setFramerateLimit(60);

	window.setVerticalSyncEnabled(false);

	input = new Input();

	if (!font.loadFromFile("font/TourDeForce.ttf"))
	{
		// Error
		cout << "Error while loading the font of the main." << endl;
	}
	else
	{
		lvl1.setFont(font);
	}

	if (!texture.loadFromFile("graphics/menu2.png"))
	{
		// Error
		cout << "Error while loading the texture of the main." << endl;
	}
	else
		sprite.setTexture(texture);

	if (!bufferSeletion.loadFromFile("sound/selection.wav"))
	{
		// Error
		cout << "Error while loading the sound selection of the main." << endl;
	}
	else
	{
		soundSeletion.setBuffer(bufferSeletion);
	}

	if (!bufferEnter.loadFromFile("sound/enter.wav"))
	{
		// Error
		cout << "Error while loading the sound enter of the main." << endl;
	}
	else
	{
		soundEnter.setBuffer(bufferEnter);
	}

	if (!bufferMenu.loadFromFile("sound/menu2.wav"))
	{
		// Error
		cout << "Error while loading the sound menu of the main." << endl;
	}
	else
	{
		soundMenu.setBuffer(bufferMenu);
		soundMenu.play();
	}

	timeClignotement = 60;
	timeRemaining = timeClignotement;
	visible = true;

	// Gameplay loop
	while (window.isOpen())
	{
		input->gestionInputs(window);

		if (inMenu)
		{
			window.clear();

			lvl1.setCharacterSize(20);

			lvl1.setStyle(sf::Text::Bold);

			lvl1.setString("PRESS START");

			int midWidth = Data::Instance()->SCREEN_WIDTH / 6;
			int midHeight = Data::Instance()->SCREEN_WIDTH / 4;

			sprite.setTextureRect(sf::IntRect(0, 0, Data::Instance()->SCREEN_WIDTH, Data::Instance()->SCREEN_HEIGHT));

			window.draw(sprite);

			lvl1.setPosition(Vector2f(midWidth, midHeight));

			window.draw(lvl1);

			window.display();
			
			if (input->getButton().action == true)
			{
				if (indexMenu == 0)
				{
					soundEnter.play();
					inMenu = false;
					InitLevel1();
					soundMenu.stop();
				}
				else
				{
					return 0;
				}
			}

			timeRemaining--;
			if (timeRemaining <= 0)
			{
				visible = !visible;
				if (visible)
				{
					lvl1.setColor(baseColor);
				}
				else
				{
					lvl1.setColor(selectedColor);
				}
				timeRemaining = timeClignotement;
			}
		}
		else
		{

			if (input->getButton().restart == true)
			{
				InitLevel1();
			}
			else if (theMap->GetGameOver())
			{
				theMap->StopMusic();
				soundMenu.play();
				inMenu = true;
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
