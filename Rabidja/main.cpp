#include "main.h"

void InitLevel1(int mapNumber)
{
	if (theMap != nullptr)
	{
		theMap->StopMusic();
		theMap->ResetLevel();
		delete theMap;
	}

	theMap = new Map();
	player = new Player(theMap);
	player->Initialize();
	player->SetX(100);
	player->SetY(100);

	int mapToLoad = mapNumber;
	currentMap = mapNumber;
	theMap->SetMapNumber(mapToLoad);
	theMap->LoadLevel(mapToLoad);
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

	if (!texture.loadFromFile("graphics/menufinal.png"))
	{
		// Error
		cout << "Error while loading the texture of the main." << endl;
	}
	else
		sprite.setTexture(texture);

	if (!textureSplash.loadFromFile("graphics/splash.png"))
	{
		// Error
		cout << "Error while loading the texture splash of the main." << endl;
	}
	else
		spriteSplash.setTexture(textureSplash);

	if (!textureBoutonGauche.loadFromFile("graphics/buttonP.png"))
	{
		// Error
		cout << "Error while loading the texture buttonleft of the main." << endl;
	}
	else
		spriteBoutonGauche.setTexture(textureBoutonGauche);

	if (!textureBoutonDroite.loadFromFile("graphics/buttonR.png"))
	{
		// Error
		cout << "Error while loading the texture buttonright of the main." << endl;
	}
	else
		spriteBoutonDroite.setTexture(textureBoutonDroite);

	if (!textureBoutonAction.loadFromFile("graphics/buttonS.png"))
	{
		// Error
		cout << "Error while loading the texture buttonaction of the main." << endl;
	}
	else
		spriteBoutonAction.setTexture(textureBoutonAction);

	if (!textureBoutonStart.loadFromFile("graphics/buttonS.png"))
	{
		// Error
		cout << "Error while loading the texture buttonstart of the main." << endl;
	}
	else
		spriteBoutonStart.setTexture(textureBoutonStart);

	if (!textureBoutonSaut.loadFromFile("graphics/buttonE.png"))
	{
		// Error
		cout << "Error while loading the texture buttonjump of the main." << endl;
	}
	else
		spriteBoutonSaut.setTexture(textureBoutonSaut);

	if (!textureS.loadFromFile("graphics/buttonS.png"))
	{
		// Error
		cout << "Error while loading the texture buttonstart of the main." << endl;
	}
	else
		spriteS.setTexture(textureS);

	if (!textureT.loadFromFile("graphics/buttonT.png"))
	{
		// Error
		cout << "Error while loading the texture buttonjump of the main." << endl;
	}
	else
		spriteT.setTexture(textureT);

	if (!textureA.loadFromFile("graphics/buttonA.png"))
	{
		// Error
		cout << "Error while loading the texture buttonstart of the main." << endl;
	}
	else
		spriteA.setTexture(textureA);

	if (!textureR.loadFromFile("graphics/buttonR.png"))
	{
		// Error
		cout << "Error while loading the texture buttonstart of the main." << endl;
	}
	else
		spriteR.setTexture(textureR);

	if (!textureT2.loadFromFile("graphics/buttonT.png"))
	{
		// Error
		cout << "Error while loading the texture buttonjump of the main." << endl;
	}
	else
		spriteT2.setTexture(textureT2);

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
	offsetBG = 0;
	offsetBD = -4.f;
	offsetBJ = -8.f;
	offsetBA = -12.f;
	offsetBS = -16.f;
	monteBG = true;
	monteBA = true;
	monteBD = true;
	monteBJ = true;
	monteBS = true;

	float limit = 15;
	float smoothDeplacement = 0.5f;

	int midWidth = Data::Instance()->SCREEN_WIDTH / 6;
	int midHeight = Data::Instance()->SCREEN_WIDTH / 1.3f;

	spriteBoutonGauche.setPosition(Vector2f(midWidth / 2, (midHeight / 2) + offsetBG));
	spriteBoutonDroite.setPosition(Vector2f((midWidth / 2) + 50, (midHeight / 2) + offsetBD));
	spriteBoutonSaut.setPosition(Vector2f((midWidth / 2) + 100, (midHeight / 2) + offsetBJ));
	spriteBoutonAction.setPosition(Vector2f((midWidth / 2) + 150, (midHeight / 2) + offsetBA));
	spriteBoutonStart.setPosition(Vector2f((midWidth / 2) + 200, (midHeight / 2) + offsetBS));

	spriteS.setPosition(Vector2f(midWidth * 2, (midHeight / 2) + offsetBG));
	spriteT.setPosition(Vector2f((midWidth * 2) + 50, (midHeight / 2) + offsetBD));
	spriteA.setPosition(Vector2f((midWidth * 2) + 100, (midHeight / 2) + offsetBJ));
	spriteR.setPosition(Vector2f((midWidth * 2) + 150, (midHeight / 2) + offsetBA));
	spriteT2.setPosition(Vector2f((midWidth * 2) + 200, (midHeight / 2) + offsetBS));

	timeClignotement = 60;
	timeRemaining = timeClignotement;
	visible = true;

	inMenu = true;

	bool begin = true;
	float currentTimeSplah = 0.0f;

	// Gameplay loop
	while (window.isOpen())
	{
		input->gestionInputs(window);

		if (inMenu)
		{

			window.clear();

			if (begin)
			{

				spriteSplash.setPosition(Vector2f((float)0, (float)0));
				spriteSplash.setTextureRect(sf::IntRect(0, 0, Data::Instance()->SCREEN_WIDTH, Data::Instance()->SCREEN_HEIGHT));

				window.draw(spriteSplash);

				currentTimeSplah += theClock.restart().asMilliseconds();
				if (currentTimeSplah/1000 >= 7.0f)
				{

					begin = false;
				}

			}
			else
			{

				lvl1.setCharacterSize(20);

				lvl1.setStyle(sf::Text::Bold);

				lvl1.setString("PRESS START");

				sprite.setTextureRect(sf::IntRect(0, 0, Data::Instance()->SCREEN_WIDTH, Data::Instance()->SCREEN_HEIGHT));

				window.draw(sprite);

				lvl1.setPosition(Vector2f(midWidth, midHeight*1.2f));

				//window.draw(lvl1);

				if (monteBG)
				{
					offsetBG += smoothDeplacement;
					if (offsetBG >= limit)
					{
						monteBG = false;
					}
				}
				else
				{
					offsetBG -= smoothDeplacement;
					if (offsetBG <= -limit)
					{
						monteBG = true;
					}
				}

				if (monteBD)
				{
					offsetBD += smoothDeplacement;
					if (offsetBD >= limit)
					{
						monteBD = false;
					}
				}
				else
				{
					offsetBD -= smoothDeplacement;
					if (offsetBD <= -limit)
					{
						monteBD = true;
					}
				}

				if (monteBJ)
				{
					offsetBJ += smoothDeplacement;
					if (offsetBJ >= limit)
					{
						monteBJ = false;
					}
				}
				else
				{
					offsetBJ -= smoothDeplacement;
					if (offsetBJ <= -limit)
					{
						monteBJ = true;
					}
				}

				if (monteBA)
				{
					offsetBA += smoothDeplacement;
					if (offsetBA >= limit)
					{
						monteBA = false;
					}
				}
				else
				{
					offsetBA -= smoothDeplacement;
					if (offsetBA <= -limit)
					{
						monteBA = true;
					}
				}

				if (monteBS)
				{
					offsetBS += smoothDeplacement;
					if (offsetBS >= limit)
					{
						monteBS = false;
					}
				}
				else
				{
					offsetBS -= smoothDeplacement;
					if (offsetBS <= -limit)
					{
						monteBS = true;
					}
				}

				spriteBoutonGauche.setPosition(Vector2f(midWidth / 2, (midHeight) + offsetBG));
				spriteBoutonDroite.setPosition(Vector2f((midWidth / 2) + 50, (midHeight) + offsetBD));
				spriteBoutonSaut.setPosition(Vector2f((midWidth / 2) + 100, (midHeight ) + offsetBJ));
				spriteBoutonAction.setPosition(Vector2f((midWidth / 2) + 150, (midHeight) + offsetBA));
				spriteBoutonStart.setPosition(Vector2f((midWidth / 2) + 200, (midHeight ) + offsetBS));

				spriteS.setPosition(Vector2f(midWidth * 2 + 150, (midHeight)+offsetBG));
				spriteT.setPosition(Vector2f((midWidth * 2) + 200, (midHeight)+offsetBD));
				spriteA.setPosition(Vector2f((midWidth * 2) + 250, (midHeight)+offsetBJ));
				spriteR.setPosition(Vector2f((midWidth * 2) + 300, (midHeight)+offsetBA));
				spriteT2.setPosition(Vector2f((midWidth * 2) + 350, (midHeight)+offsetBS));

				window.draw(spriteBoutonGauche);
				window.draw(spriteBoutonDroite);
				window.draw(spriteBoutonSaut);
				window.draw(spriteBoutonAction);
				window.draw(spriteBoutonStart);

				window.draw(spriteS);
				window.draw(spriteT);
				window.draw(spriteA);
				window.draw(spriteR);
				window.draw(spriteT2);
			}

			window.display();
			
			if (input->getButton().start == true && begin == false)
			{
				if (indexMenu == 0)
				{
					soundEnter.play();
					inMenu = false;
					InitLevel1(1);
					soundMenu.stop();
				}
				else
				{
					return 0;
				}
			}

			

			/*timeRemaining--;
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
			}*/
		}
		else
		{

			if (input->getButton().restart == true)
			{
				theMap->StopMusic();
				theMap->ResetLevel();
				InitLevel1(currentMap);
			}
			else if (theMap->GetGameOver())
			{
				theMap->StopMusic();
				if (theMap->GetWin())
				{
					InitLevel1(1);
				}
				else
				{
					theMap->ResetLevel();
					InitLevel1(currentMap);
				}
			}
			else
			{

				theMap->Start(theClock.getElapsedTime());

				Time time = theClock.restart();

				player->Update(input, time);
				player->mapCollision(theMap);

				window.clear();

				theMap->DrawBackground(window);

				theMap->UpdateBomb(time);
				theMap->DrawBomb(window);

				theMap->DrawTiles(window);

				theMap->UpdatePowers(time);
				theMap->DrawPowers(window);

				theMap->UpdateBlockers(time);
				theMap->DrawBlockers(window);

				theMap->UpdateEnding(time);
				theMap->DrawEnding(window);

				theMap->DrawTuto(window);

				theMap->UpdateElevators(time);
				theMap->DrawElevators(window);

				theMap->UpdatePanneaux(time);
				theMap->DrawPanneaux(window);

				theMap->DrawDoors(window);

				player->Draw(window);

				Debug::Instance()->PrintDebug(window);

				window.display();

				if (player->GetWantsTheMenu())
				{
					inMenu = true;
					theMap->StopMusic();
					soundMenu.play();
					sleep(Time(seconds(1)));
				}

				if (player->MustLoadLevel() != -1)
				{
					InitLevel1(player->MustLoadLevel());
				}
			}
		}
	}

	delete input;
	delete theMap;
	delete player;

	return 0;
}