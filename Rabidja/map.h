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
class Power;

class Map
{
public:

	//Constructeur
	Map();
	~Map();

	//Fonctions
	void DrawBackground(sf::RenderWindow &window);

	void DrawTiles(sf::RenderWindow &window);
	void DrawPowers(sf::RenderWindow &window);
	void UpdatePowers();

	void AddTile(string name, int posX, int posY, int type);

	void GenerateTerrain();
	void GenerateTerrainWithFile();

	Tile* GetTile(int x, int y);

	void LoadLevel(int nb);

	int GetStartX();
	int GetStartY();

	Power* GetPower(int theX, int theY);

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

	sf::Texture tileSetTestTexture;
	sf::Sprite tileSetTest;

	Tile* tile[150][400];

	vector < vector < int > > lignes;

	vector <Tile*> layer1;
	//vector <int> layer2;
	//vector <int> layer3;

	int playerStartX;
	int playerStartY;

	vector <Power*> powers;

};
#endif