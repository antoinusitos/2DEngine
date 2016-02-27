#ifndef MAP_H
#define MAP_H

#include "Data.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


class Map
{
public:

	//Constructeur
	Map();

	//Fonctions
	void drawBackground(sf::RenderWindow &window);


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

	//vector <int> layer1;
	//vector <int> layer2;
	//vector <int> layer3;

};
#endif