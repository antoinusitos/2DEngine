#include "map.h"
#include "Tile.h"
#include "Power.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace sf;

//Constructeur
Map::Map()
{
	//Chargement des ressources graphiques
	//Chargement du background
	//if (!backgroundTexture.loadFromFile("graphics/backgroundTest.png"))
	if (!backgroundTexture.loadFromFile("graphics/backg.png"))
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

	if (!tileSetTestTexture.loadFromFile("graphics/level1TileSheet.png"))
	{
		// Erreur
		cout << "Erreur durant le chargement de l'image du tileset 1b." << endl;
	}
	else
		tileSetTest.setTexture(tileSetTestTexture);

	//GenerateTerrain();
	playerStartX = 0;
	playerStartY = 0;
}

Map::~Map()
{

	for (unsigned i = 0; i < powers.size(); i++)
	{
		delete powers.at(i);
	}
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

void Map::DrawPowers(sf::RenderWindow & window)
{
	for (unsigned i = 0; i < powers.size(); i++)
	{
		powers.at(i)->Draw(window);
	}
}

void Map::UpdatePowers()
{
	for (unsigned i = 0; i < powers.size(); i++)
	{
		powers.at(i)->Update(nullptr);
	}
}

void Map::AddTile(string name, int posX, int posY, int type)
{
	//create tile
	Tile* t = new Tile(name, posX * Data::Instance()->TILE_SIZE, posY * Data::Instance()->TILE_SIZE, type);
	//put it in the first layer
	layer1.push_back(t);
	//put it in the array for the collision
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

void Map::GenerateTerrainWithFile()
{
	int x = Data::Instance()->TILE_X;
	int y = Data::Instance()->TILE_Y;

	for (int i = 0; i < y ; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			bool canDraw = true;
			if (lignes[i][j] == 19)
			{
				playerStartX = j;
				playerStartY = i;
			}
			else if (lignes[i][j] == 11)
			{
				powers.push_back(new Power(Power::type::green, 10.0f, j, i, this));
				canDraw = false;
			}
			else if (lignes[i][j] == 12)
			{
				powers.push_back(new Power(Power::type::red, 15.0f, j, i, this));
				canDraw = false;
			}
			else if (lignes[i][j] == 13)
			{
				powers.push_back(new Power(Power::type::yellow, 15.0f, j, i, this));
				canDraw = false;
			}
			if(canDraw)
				AddTile("level1TileSheet2", j, i, lignes[i][j]);
		}
	}
}

Tile* Map::GetTile(int x, int y)
{
	return tile[x][y];
}

Tile* Map::GetTile(int tileNumber)
{
	int x = Data::Instance()->TILE_X;
	int y = Data::Instance()->TILE_Y;

	for (int i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			if(tile[j][i] != nullptr && tile[j][i]->GetTileType() == tileNumber)
				return tile[j][i];
		}
	}
	return nullptr;
}

void Map::LoadLevel(int nb)
{
	string name = "map/map" + to_string(nb) + ".txt";

	fstream file;

	vector < int > vectTemp;

	string strBuf, strTmp;

	stringstream iostr;

	file.open(name, fstream::in);

	if (!file.is_open())
	{
		cerr << "Erreur de chargement du fichier.\n";
		exit(1);
	}

	while (!file.eof())
	{
		getline(file, strBuf);

		if (!strBuf.size())
			continue;

		iostr.clear();

		iostr.str(strBuf);

		vectTemp.clear();

		while (true)
		{
			// get tile number with delimiter
			getline(iostr, strTmp, ' ');

			//put the number in the vector
			vectTemp.push_back(atoi(strTmp.c_str()));

			//quit the while if finished
			if (!iostr.good()) break;
		}

		//put the vector in the final one
		if (vectTemp.size())
			lignes.push_back(vectTemp);

	}
	file.close();

	GenerateTerrainWithFile();
}

int Map::GetStartX()
{
	return playerStartX;
}

int Map::GetStartY()
{
	return playerStartY;
}

Power* Map::GetPower(int theX, int theY)
{
	Power* retour = nullptr;

	for (unsigned i = 0; i < powers.size(); i++)
	{
		if (powers.at(i)->GetX() == (theX * Data::Instance()->TILE_SIZE) && powers.at(i)->GetY() == (theY * Data::Instance()->TILE_SIZE))
		{
			retour = powers.at(i);
		}
	}

	return retour;
}

void Map::SetRunningPower(Power * thePower)
{
	runningPower = thePower;
	runningPower->Activate();
}

void Map::ResetRunningPower()
{
	runningPower = nullptr;
}

Power* Map::GetRunningPower()
{
	return runningPower;
}
