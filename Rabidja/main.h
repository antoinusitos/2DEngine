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
Text lvl2;
Text lvl3;
Text quit;
Text title;
Color selectedColor = Color::Red;
Color baseColor = Color::Green;
Font font;