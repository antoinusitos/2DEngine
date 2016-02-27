#include "map.h"

using namespace std;
using namespace sf;

//Constructeur
Map::Map()
{
	//Chargement des ressources graphiques
	//Chargement du background
	if (!backgroundTexture.loadFromFile("graphics/background.png"))
	{
		// Erreur
		cout << "Erreur durant le chargement de l'image de background." << endl;
	}
	else
	{
		background.setTexture(backgroundTexture);
	}

	//Chargement des 2 tilesets n�1
	if (!tileSet1Texture.loadFromFile("graphics/tileset1.png"))
	{
		// Erreur
		cout << "Erreur durant le chargement de l'image du tileset 1." << endl;
	}
	else
		tileSet1.setTexture(tileSet1Texture);

	if (!tileSet1BTexture.loadFromFile("graphics/tileset1b.png"))
	{
		// Erreur
		cout << "Erreur durant le chargement de l'image du tileset 1b." << endl;
	}
	else
		tileSet1B.setTexture(tileSet1BTexture);
}

void Map::drawBackground(RenderWindow &window)
{
	window.draw(background);
}