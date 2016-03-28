#include "main.h"

int main(int argc, char *argv[])
{
	RenderWindow window(VideoMode(Data::Instance()->SCREEN_WIDTH, Data::Instance()->SCREEN_HEIGHT, 32), "Game");

	window.setFramerateLimit(60);

	window.setVerticalSyncEnabled(false);

	Input* input = new Input();
	Map* map = new Map();
	Player* player = new Player(map);
	player->Initialize();
	player->SetX(100);
	player->SetY(100);
	sf::Clock clock;

	map->LoadLevel(3);
	player->SetStartPos(map->GetStartX(), map->GetStartY());

	// Gameplay loop
	while (window.isOpen())
	{
		input->gestionInputs(window);

		Time time = clock.restart();

		player->Update(input);
		player->mapCollision(map);

		window.clear();

		map->DrawBackground(window);

		map->DrawTiles(window);

		map->UpdatePowers();
		map->DrawPowers(window);

		map->UpdateBlockers();
		map->DrawBlockers(window);

		map->UpdateEnding();
		map->DrawEnding(window);

		map->UpdateBomb();
		map->DrawBomb(window);

		player->Draw(window);

		Debug::Instance()->PrintDebug(window);

		window.display();
	}

	delete input;
	delete map;
	delete player;

	return 0;

}