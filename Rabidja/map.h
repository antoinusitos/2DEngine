#ifndef MAP_H
#define MAP_H

#include "Data.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Tile;

class Map
{
public:

	//Constructeur
	Map();

	//Fonctions
	void DrawBackground(sf::RenderWindow &window);

	void DrawTiles(sf::RenderWindow &window);

	void AddTile(string name, int posX, int posY, int type);

	void GenerateTerrain();

	Tile* GetTile(int x, int y);

private:
	//Variables de la classe en accès privé

	//Background
	sf::Texture backgroundTexture;
	sf::Sprite background;

	//Tilesets
	sf::Texture tileSet1Texture;
	sf::Sprite tileSet1;
	sf::Texture tileSet1BTexture;
	sf::Sprite tileSet1B;

	Tile* tile[150][400];

	vector <Tile*> layer1;
	//vector <int> layer2;
	//vector <int> layer3;

};
#endif