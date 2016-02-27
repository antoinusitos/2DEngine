#include "map.h"
#include "Tile.h"

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

	//Chargement des 2 tilesets n°1
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

	GenerateTerrain();
}

void Map::DrawBackground(RenderWindow &window)
{
	window.draw(background);
}

void Map::DrawTiles(sf::RenderWindow & window)
{
	for (unsigned i = 0; i < layer1.size(); i++)
	{
		layer1.at(i)->Draw(window);
	}
}

void Map::AddTile(string name, int posX, int posY)
{
	layer1.push_back(new Tile(name, posX, posY));
}

void Map::GenerateTerrain()
{
	for (int i = 0; i < 20; ++i)
	{
		AddTile("ground", i * Data::Instance()->TILE_SIZE, 450);
	}
}
