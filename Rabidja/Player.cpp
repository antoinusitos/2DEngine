#include "Player.h"

using namespace std;
using namespace sf;

Player::Player()
{
	if (!texture.loadFromFile("graphics/rabidja.png"))
	{
		// Error
		cout << "Error while loading the texture of the player." << endl;
	}
	else
		sprite.setTexture(texture);

	directionX = 0;
	directionY = 0;
	life = 3;
	x = 0;
	y = 0;
	height = 0;
	width = 0;
	isGrounding = false;
	speed = 1;
	direction = Data::Instance()->RIGHT;
	state = Data::Instance()->IDLE;
	frameNumber = 0;
	frameTimer = 0;
	frameMax = 0;

	jumpState = Data::Instance()->jump;
}


Player::~Player()
{
}

void Player::Initialize()
{
	directionX = 0;
	directionY = 0;
	dirY = 0;
	dirX = 0;
	life = 3;
	frameNumber = 0;
	frameTimer = Data::Instance()->TIME_BETWEEN_2_FRAMES_PLAYER;
	frameMax = 8;
	x = 0;
	y = 0;
	height = Data::Instance()->PLAYER_HEIGTH;
	width = Data::Instance()->PLAYER_WIDTH;
	isGrounding = false;
	speed = 5.0f;
	direction = Data::Instance()->RIGHT;
	state = Data::Instance()->IDLE;
	width = Data::Instance()->PLAYER_WIDTH;
	height = Data::Instance()->PLAYER_HEIGTH;
	hasJump = false;
	canJump = false;
}

void Player::SetLife(int theLife)
{
	life = theLife;
}

void Player::SetSpeed(float theSpeed)
{
	speed = theSpeed;
}

int Player::GetLife()
{
	return life;
}

float Player::GetSpeed()
{
	return speed;
}

void Player::Draw(RenderWindow &window)
{
	if (frameTimer <= 0)
	{
		//On le réinitialise
		frameTimer = Data::Instance()->TIME_BETWEEN_2_FRAMES_PLAYER;

		//Et on incrémente notre variable qui compte les frames de 1 pour passer à la suivante
		frameNumber++;

		//Mais si on dépasse la frame max, il faut revenir à la première :
		if (frameNumber >= frameMax)
			frameNumber = 0;
	}
	//Sinon, on décrémente notre timer
	else
		frameTimer--;

	sprite.setPosition(Vector2f((float)x, (float)y));

	if (state == Data::Instance()->WALK)
	{
		if (direction == Data::Instance()->LEFT)
		{
			sprite.setTextureRect(sf::IntRect((frameNumber + 1) * width, height, -width, height));
		}
		else
		{
			sprite.setTextureRect(sf::IntRect(frameNumber * width, height, width, height));
		}
	}
	else if (state == Data::Instance()->IDLE)
	{
		if (direction == Data::Instance()->LEFT)
		{
			sprite.setTextureRect(sf::IntRect((frameNumber + 1) * width, 0, -width, height));
		}
		else
		{
			sprite.setTextureRect(sf::IntRect(frameNumber * width, 0, width, height));
		}
	}
	else if (state == Data::Instance()->JUMP1)
	{
		if (direction == Data::Instance()->LEFT)
		{
			sprite.setTextureRect(sf::IntRect((frameNumber + 1) * width, 2 * height, -width, height));
		}
		else
		{
			sprite.setTextureRect(sf::IntRect(frameNumber * width, 2 * height, width, height));
		}
	}
	window.draw(sprite);
}

void Player::Update(Input * input)
{
	if (state != Data::Instance()->DEAD)
	{
		dirX = 0;
		dirY += Data::Instance()->GRAVITY_SPEED;

		if (dirY >= Data::Instance()->MAX_FALL_SPEED)
			dirY = Data::Instance()->MAX_FALL_SPEED;

		if (input->getButton().left == true)
		{
			x -= speed;

			//Et on indique qu'il va à gauche (pour le flip
			//de l'affichage, rappelez-vous).
			direction = Data::Instance()->LEFT;

			//Si ce n'était pas son état auparavant et qu'il est bien sur
			//le sol (car l'anim' sera différente s'il est en l'air)
			if (state != Data::Instance()->WALK && isGrounding == true)
			{
				//On enregistre l'anim' de la marche et on l'initialise à 0
				state = Data::Instance()->WALK;
				frameNumber = 0;
				frameTimer = Data::Instance()->TIME_BETWEEN_2_FRAMES_PLAYER;
				frameMax = 8;
			}
		}

		//Si on détecte un appui sur la touche fléchée droite
		else if (input->getButton().right == true)
		{
			//On augmente les coordonnées en x du joueur
			x += speed;

			//Et on indique qu'il va à droite (pour le flip
			//de l'affichage, rappelez-vous).
			direction = Data::Instance()->RIGHT;

			//Si ce n'était pas son état auparavant et qu'il est bien sur
			//le sol (car l'anim' sera différente s'il est en l'air)
			if (state != Data::Instance()->WALK && isGrounding == true)
			{
				//On enregistre l'anim' de la marche et on l'initialise à 0
				state = Data::Instance()->WALK;
				frameNumber = 0;
				frameTimer = Data::Instance()->TIME_BETWEEN_2_FRAMES_PLAYER;
				frameMax = 8;
			}
		}

		//Si on n'appuie sur rien et qu'on est sur le sol, on charge l'animation marquant l'inactivité (Idle)
		else if (input->getButton().right == false && input->getButton().left == false && isGrounding == true)
		{
			//On teste si le joueur n'était pas déjà inactif, pour ne pas recharger l'animation
			//à chaque tour de boucle
			if (state != Data::Instance()->IDLE)
			{
				//On enregistre l'anim' de l'inactivité et on l'initialise à 0
				state = Data::Instance()->IDLE;
				frameNumber = 0;
				frameTimer = Data::Instance()->TIME_BETWEEN_2_FRAMES_PLAYER;
				frameMax = 8;
			}

		}

		if (input->getButton().jump == true)
		{
			if (isGrounding == true && canJump)
			{
				dirY -= Data::Instance()->JUMP_HEIGHT;
				isGrounding = false;
				hasJump = true;
				canJump = false;
				input->setButton(jumpState, false);
			}
			else
			{
				//ralentissement
				input->setButton(jumpState, false);
			}
		}
		else if (isGrounding == false)
		{
			if (y < Data::Instance()->MAX_MAP_Y)
				y += dirY;
			else if (hasJump)
			{
				y += dirY;
				hasJump = false;
			}
			else
			{
				isGrounding = true;
				hasJump = false;
				canJump = true;
			}
		}

		if (isGrounding == false)
		{
			if (state != Data::Instance()->JUMP1)
			{
				state = Data::Instance()->JUMP1;
				frameNumber = 0;
				frameTimer = Data::Instance()->TIME_BETWEEN_2_FRAMES_PLAYER;
				frameMax = 2;
			}
		}

		//mapCollision(map);

		//On gère le scrolling (fonction ci-dessous)
		//centerScrolling(map);
	}
}

/*void Player::mapCollision(Map * map)
{
	int i, x1, x2, y1, y2;

	// D'abord, on considère le joueur en l'air jusqu'à temps
	//d'être sûr qu'il touche le sol 
	isGrounding = 0;

	// Ensuite, on va tester les mouvements horizontaux en premier
	//(axe des X). On va se servir de i comme compteur pour notre boucle.
	//En fait, on va découper notre sprite en blocs de tiles pour voir
	//quelles tiles il est susceptible de recouvrir.
	//On va donc commencer en donnant la valeur de Tile_Size à i pour qu'il
	//teste la tile où se trouve le x du joueur mais aussi la suivante SAUF
	//dans le cas où notre sprite serait inférieur à la taille d'une tile.
	//Dans ce cas, on lui donnera la vraie valeur de la taille du sprite
	//Et on testera ensuite 2 fois la même tile. Mais comme ça notre code
	//sera opérationnel quelle que soit la taille de nos sprites ! 

	if (height > Data::Instance()->TILE_SIZE)
		i = Data::Instance()->TILE_SIZE;
	else
		i = height;


	//On lance alors une boucle for infinie car on l'interrompra selon
	//les résultats de nos calculs
	for (;;)
	{
		//On va calculer ici les coins de notre sprite à gauche et à
		//droite pour voir quelle tile ils touchent.
		x1 = (x + dirX) / Data::Instance()->TILE_SIZE;
		x2 = (x + dirX + width - 1) / Data::Instance()->TILE_SIZE;

		//Même chose avec y, sauf qu'on va descendre au fur et à mesure
		//pour tester toute la hauteur de notre sprite, grâce à notre
		//fameuse variable i.
		y1 = (y) / Data::Instance()->TILE_SIZE;
		y2 = (y + i - 1) / Data::Instance()->TILE_SIZE;

		//De là, on va tester les mouvements initiés dans updatePlayer
		//grâce aux vecteurs dirX et dirY, tout en testant avant qu'on
		//se situe bien dans les limites de l'écran.
		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
		{
			//Si on a un mouvement à droite
			if (dirX > 0)
			{
				//On vérifie si les tiles recouvertes sont solides
				if (map->getTile(y1, x2) > BLANK_TILE || map->getTile(y2, x2) > BLANK_TILE)
				{
					// Si c'est le cas, on place le joueur aussi près que possible
					// de ces tiles, en mettant à jour ses coordonnées. Enfin, on
					//réinitialise son vecteur déplacement (dirX).

					x = x2 * Data::Instance()->TILE_SIZE;
					x -= width + 1;
					dirX = 0;
				}
			}

			//Même chose à gauche
			else if (dirX < 0)
			{
				if (map->getTile(y1, x1) > Data::Instance()->BLANK_TILE || map->getTile(y2, x1) > Data::Instance()->BLANK_TILE)
				{
					x = (x1 + 1) * Data::Instance()->TILE_SIZE;
					dirX = 0;
				}
			}

		}

		//On sort de la boucle si on a testé toutes les tiles le long de la hauteur du sprite.
		if (i == height)
		{
			break;
		}

		//Sinon, on teste les tiles supérieures en se limitant à la heuteur du sprite.
		i += Data::Instance()->TILE_SIZE;

		if (i > height)
		{
			i = height;
		}
	}


	//On recommence la même chose avec le mouvement vertical (axe des Y)
	if (width > Data::Instance()->TILE_SIZE)
		i = Data::Instance()->TILE_SIZE;
	else
		i = width;


	for (;;)
	{
		x1 = (x) / Data::Instance()->TILE_SIZE;
		x2 = (x + i) / Data::Instance()->TILE_SIZE;

		y1 = (y + dirY) / Data::Instance()->TILE_SIZE;
		y2 = (y + dirY + height) / Data::Instance()->TILE_SIZE;

		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
		{
			if (dirY > 0)
			{
				// Déplacement en bas
				//Gestion des plateformes traversables : elles se situent juste avant
				//les tiles bloquantes dans notre tileset (dont la valeur butoire est
				//BLANK_TILE). Il suffit donc d'utiliser le numéro de la première tile
				//traversable au lieu de BLANK_TILE pour bloquer le joueur,
				//seulement quand il tombe dessus (sinon, il passe au-travers
				//et le test n'est donc pas effectué dans les autres directions
				if (map->getTile(y2, x1) > Data::Instance()->TILE_TRAVERSABLE || map->getTile(y2, x2) > Data::Instance()->TILE_TRAVERSABLE)
				{
					//Si la tile est une plateforme ou une tile solide, on y colle le joueur et
					//on le déclare sur le sol (onGround).
					y = y2 * Data::Instance()->TILE_SIZE;
					y -= height;
					dirY = 0;
					isGrounding = 1;
				}
			}

			else if (dirY < 0)
			{
				// Déplacement vers le haut
				if (map->getTile(y1, x1) > Data::Instance()->BLANK_TILE || map->getTile(y1, x2) > Data::Instance()->BLANK_TILE)
				{
					y = (y1 + 1) * Data::Instance()->TILE_SIZE;
					dirY = 0;
				}
			}
		}

		//On teste la largeur du sprite (même technique que pour la hauteur précédemment)
		if (i == width)
		{
			break;
		}

		i += Data::Instance()->TILE_SIZE;

		if (i > width)
		{
			i = width;
		}
	}

	// Maintenant, on applique les vecteurs de mouvement si le sprite n'est pas bloqué 
	x += dirX;
	y += dirY;

	//Et on contraint son déplacement aux limites de l'écran.
	if (x < 0)
	{
		x = 0;
	}

	else if (x + width >= map->getMaxX())
	{
		//Si on touche le bord droit de l'écran, on passe au niveau sup
		map->setLevel(map->getLevel() + 1);

		//Si on dépasse le niveau max, on annule et on limite le déplacement du joueur
		if (map->getLevel() > Data::Instance()->LEVEL_MAX)
		{
			map->setLevel(Data::Instance()->LEVEL_MAX);
			x = map->getMaxX() - width - 1;
		}

		//Sinon, on passe au niveau sup, on charge la nouvelle map et on réinitialise le joueur
		else
		{
			//map.changeLevel();
			Initialize();
		}
	}

	//Maintenant, s'il sort de l'écran par le bas (chute dans un trou sans fond), on lance le timer
	//qui gère sa mort et sa réinitialisation (plus tard on gèrera aussi les vies).
	if (y > map->getMaxY())
	{
		//timerMort = 60;
	}
}*/
