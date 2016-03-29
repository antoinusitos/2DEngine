#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>
#include "Data.h"

class Input
{

public:

	//Constructeur
	Input();

	//Accesseur
	Data::Button getButton(void) const;

	//Mutateur
	void setButton(int bouton, bool etat);

	//Fonctions
	void gestionInputs(sf::RenderWindow &window);
	void getInput(sf::RenderWindow &window);


private:

	//Variables de la classe en accès privé
	sf::Event event;
	Data::Button button;

	//Enum pour les boutons
	const enum
	{
		up,
		down, 
		right, 
		left, 
		action, 
		jump, 
		start,
		restart
	};

};
#endif