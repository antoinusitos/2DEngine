#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Data.h"
#include "input.h"
#include "map.h"
#include "Player.h"

using namespace std;
using namespace sf;

Input* input;
Map* theMap;
Player* player;
sf::Clock theClock;
bool inMenu = true;
int indexMenu;
Text lvl1;
Color selectedColor = Color::Color(228, 246, 228, 255);
Color baseColor = Color::Color(228, 246, 228, 0);
Font font;

float timeClignotement;
float timeRemaining;
bool visible;

sf::SoundBuffer bufferSeletion;
sf::Sound soundSeletion;

sf::SoundBuffer bufferEnter;
sf::Sound soundEnter;

sf::SoundBuffer bufferMenu;
sf::Sound soundMenu;

sf::Texture texture;
sf::Sprite sprite;

sf::Texture textureBoutonGauche;
sf::Sprite spriteBoutonGauche;
float offsetBG;
bool monteBG;

sf::Texture textureBoutonDroite;
sf::Sprite spriteBoutonDroite;
float offsetBD;
bool monteBD;

sf::Texture textureBoutonAction;
sf::Sprite spriteBoutonAction;
float offsetBA;
bool monteBA;

sf::Texture textureBoutonStart;
sf::Sprite spriteBoutonStart;
float offsetBS;
bool monteBS;

sf::Texture textureBoutonSaut;
sf::Sprite spriteBoutonSaut;
float offsetBJ; 
bool monteBJ;

sf::Texture textureSplash;
sf::Sprite spriteSplash;

int currentMap = -1;