#ifndef MAP_H
#define MAP_H

#include "Data.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Tile;
class Power;
class Blocker;
class EndingPlateform;
class Bomb;
class Elevator;

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
	void DrawBlockers(sf::RenderWindow &window);
	void DrawElevators(sf::RenderWindow &window);
	void DrawEnding(sf::RenderWindow &window);
	void DrawBomb(sf::RenderWindow &window);
	void UpdatePowers(sf::Time time);
	void UpdateBlockers(sf::Time time);
	void UpdateElevators(sf::Time time);
	void UpdateEnding(sf::Time time);
	void UpdateBomb(sf::Time time);

	void AddTile(string name, int posX, int posY, int type);

	void GenerateTerrain();
	void GenerateTerrainWithFile();

	Tile* GetTile(int x, int y);
	Tile* GetTile(int tileNumber);

	void LoadLevel(int nb);

	int GetStartX();
	int GetStartY();

	Power* GetPower(int theX, int theY);
	void SetRunningPower(Power* thePower);
	void ResetRunningPower();
	Power* GetRunningPower();

	Elevator* GetElevator();

	vector<Blocker*> GetBlockers();
	EndingPlateform* GetEnding();

	void SetCanFinish(bool state);
	bool GetCanFinish();

	void PlayMusic();
	void StopMusic();

	bool GetGameOver();
	void SetGameOver(bool state);

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
	Power* runningPower;

	vector <Blocker*> blockers;

	EndingPlateform* theEndingPlateform;

	Elevator* theElevator;

	Bomb* theBomb;

	bool canFinish;

	sf::SoundBuffer bufferMusic;
	sf::Sound soundMusic;

	bool gameOver;
};
#endif