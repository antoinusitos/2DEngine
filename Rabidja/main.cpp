#include "main.h"

int main(int argc, char *argv[])
{
	// Création d'une fenêtre en SFML 
	RenderWindow window(VideoMode(Data::Instance()->SCREEN_WIDTH, Data::Instance()->SCREEN_HEIGHT, 32), "Game");

	//Limite les fps à 60 images / seconde
	window.setFramerateLimit(60);

	//On active la synchro verticale
	window.setVerticalSyncEnabled(true);

	//Instanciation des classes
	Input* input = new Input();
	Map* map = new Map();
	Player* player = new Player();
	player->Initialize();
	player->SetX(100);
	player->SetY(100);

	// Boucle infinie, principale, du jeu 
	while (window.isOpen())
	{
		/** GESTION DES INPUTS (CLAVIER, JOYSTICK) **/
		input->gestionInputs(window);

		player->Update(input);

		/**  DESSIN - DRAW  **/
		//On dessine tout
		window.clear();

		//On affiche le background
		map->drawBackground(window);

		player->Draw(window);

		window.display();
	}

	delete input;
	delete map;

	// On quitte
	return 0;

}