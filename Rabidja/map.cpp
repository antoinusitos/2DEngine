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

void Map::AddTile(string name, int posX, int posY, int type)
{
	Tile* t = new Tile(name, posX * Data::Instance()->TILE_SIZE, posY * Data::Instance()->TILE_SIZE, type);
	layer1.push_back(t);
	tile[posY][posX] = t;
}

void Map::GenerateTerrain()
{
	for (int i = 0; i < 20; ++i)
	{
		AddTile("ground", i, 13, 2);
	}

	AddTile("groundLeft", 10, 10, 2);
	AddTile("groundMiddle", 11, 10, 2);
	AddTile("groundRight", 12, 10, 2);

	AddTile("Ladder", 10, 12, 3);
	AddTile("Ladder", 10, 11, 3);
	AddTile("Ladder", 10, 10, 3);

	AddTile("groundLeft", 13, 7, 2);
	AddTile("groundMiddle", 14, 7, 2);
	AddTile("groundRight", 15, 7, 2);
}

Tile* Map::GetTile(int x, int y)
{
	return tile[x][y];
}
