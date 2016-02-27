//Rabidja 3 - nouvelle version intégralement en SFML 2
//Copyright / Droits d'auteur : www.meruvia.fr - Jérémie F. Bellanger

#include "input.h"

using namespace std;
using namespace sf;

//Constructeur
Input::Input()
{
	button.left = false;
	button.right = false;
	button.up = false; 
	button.down = false;
	button.jump = false;
	button.action = false; 
	button.start = false;
}


//Accesseur
Data::Button Input::getButton(void) const { return button; }


//Mutateur
void Input::setButton(int bouton, bool etat)
{
	switch (bouton)
	{
	case up:
		button.up = etat;
		break;

	case down:
		button.down = etat;
		break;

	case right:
		button.right = etat;
		break;

	case left:
		button.left = etat;
		break;

	case action:
		button.action = etat;
		break;

	case jump:
		button.jump = etat;
		break;

	case start:
		button.start = etat;
		break;

	}

}


//Fonctions
void Input::gestionInputs(RenderWindow &window)
{
	//Pour l'instant, on ne gère que le clavier.
	//On gèrera les joysticks plus tard, s'il y en a
	//un de branché.
	//Pour l'instant, cette fonction n'est donc pas indispensable.
	getInput(window);
}


void Input::getInput(RenderWindow &window)
{

	// Tant qu'il y a des évènements à traiter...
	while (window.pollEvent(event))
	{
		// on regarde le type de l'évènement...
		switch (event.type)
		{
			// On ferme la fenêtre
		case Event::Closed:
			window.close();
			break;

			// Touche pressée
		case Event::KeyPressed:
			switch (event.key.code) // La touche qui a été pressée
			{
			case Keyboard::Escape: // Echap
				window.close();
				break;

			case Keyboard::C:
				button.jump = true;
				break;

			case Keyboard::Left:
				button.left = true;
				break;

			case Keyboard::Right:
				button.right = true;
				break;

			case Keyboard::Down:
				button.down = true;
				break;

			case Keyboard::Up:
				button.up = true;
				break;

			case Keyboard::E:
				button.action = true;
				break;

			case Keyboard::P:
				button.start = true;
				break;

			default:
				break;
			}
			break;

			// Touche relâchée
		case Event::KeyReleased:
			switch (event.key.code)
			{
			case Keyboard::Space:
				button.jump = false;
				break;

			case Keyboard::Left:
				button.left = false;
				break;

			case Keyboard::Right:
				button.right = false;
				break;

			case Keyboard::Down:
				button.down = false;
				break;

			case Keyboard::Up:
				button.up = false;
				break;

			case Keyboard::E:
				button.action = false;
				break;

			case Keyboard::P:
				button.start = false;
				break;

			default:
				break;
			}
			break;

			// on ne traite pas les autres types d'évènements
		default:
			break;
		}
	}
}

