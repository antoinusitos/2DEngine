#include "Player.h"

using namespace std;
using namespace sf;

Player::Player(Map* map)
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

	theMap = map;

	debug = true;
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
	TileSize = Data::Instance()->TILE_SIZE;
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
	
	if (debug)
	{
		string s;

		Debug::Instance()->AddDebug("X:" + to_string(x), false, 15, Color::Red);
		Debug::Instance()->AddDebug("Y:" + to_string(y), false, 15, Color::Red);

		Debug::Instance()->AddDebug("isGrounding: " + to_string(isGrounding), true, 15, Color::Red);
		Debug::Instance()->AddDebug("canJump: " + to_string(canJump), true, 15, Color::Red);
		Debug::Instance()->AddDebug("hasJump: " + to_string(hasJump), true, 15, Color::Red);
		Debug::Instance()->AddDebug("dirY: " + to_string(dirY), true, 15, Color::Red);
		Debug::Instance()->AddDebug("state: " + to_string(state), true, 15, Color::Red);
	}
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
			if (state == Data::Instance()->LADDER)
			{
				dirY = 0;
				state = Data::Instance()->IDLE;
			}
			else
			{

				dirX -= speed;

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
		}

		//Si on détecte un appui sur la touche fléchée droite
		else if (input->getButton().right == true)
		{
			if (state == Data::Instance()->LADDER)
			{
				dirY = 0;
				state = Data::Instance()->IDLE;
			}
			else
			{

				//On augmente les coordonnées en x du joueur
				dirX += speed;

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
		}

		//Si on n'appuie sur rien et qu'on est sur le sol, on charge l'animation marquant l'inactivité (Idle)
		else if (input->getButton().right == false && input->getButton().left == false && isGrounding == true && state != Data::Instance()->LADDER)
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

		if (state == Data::Instance()->LADDER)
		{
			dirY = 0;
		}

		//jump
		if (input->getButton().jump == true && state != Data::Instance()->JUMP1)
		{
			if (isGrounding == true && canJump)
			{
				dirY -= Data::Instance()->JUMP_HEIGHT;
				isGrounding = false;
				hasJump = true;
				canJump = false;
				input->setButton(jumpState, false);
			}
		}
		else if (input->getButton().up == true)
		{
			if (CheckCollision(theMap))
			{
				if (state != Data::Instance()->LADDER)
					state = Data::Instance()->LADDER;
				dirY = -Data::Instance()->CLIMB_HEIGHT;
			}
		}
		else if (input->getButton().down == true)
		{
			if (CheckCollisionBottom(theMap))
			{
				if (state != Data::Instance()->LADDER)
					state = Data::Instance()->LADDER;
				dirY = Data::Instance()->CLIMB_HEIGHT;
			}
		}

		//is jumping
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

		//On gère le scrolling (fonction ci-dessous)
		//centerScrolling(map);
	}
}

// check on top of the player if there is a ladder tile
bool Player::CheckCollision(Map* map)
{
	int yTemp = (y + height - 1) / TileSize;
	int xTemp = (x - (width / 4)) / TileSize;
	if (map->GetTile(yTemp, xTemp + 1) != nullptr)
	{
		int l = map->GetTile(yTemp, xTemp + 1)->GetType();
		if (map->GetTile(yTemp, xTemp + 1)->GetType() == Data::Instance()->TILE_LADDER)
		{
			return true;
		}
	}
	return false;
}

// check in the bottom of the player if there is a ladder tile
bool Player::CheckCollisionBottom(Map* map)
{
	int yTemp = (y + (height + 1)) / TileSize;
	int xTemp = (x - (width / 4)) / TileSize;
	if (map->GetTile(yTemp, xTemp + 1) != nullptr)
	{
		int l = map->GetTile(yTemp, xTemp + 1)->GetType();
		if (map->GetTile(yTemp, xTemp + 1)->GetType() == Data::Instance()->TILE_LADDER)
		{
			return true;
		}
	}
	return false;
}

void Player::mapCollision(Map* map)
{
	int x1;
	int x2;
	int y1;
	int y2;
	int i;

	int MAX_MAP_X = Data::Instance()->MAX_MAP_X;
	int MAX_MAP_Y = Data::Instance()->MAX_MAP_Y;

	int BLANK_TILE = Data::Instance()->BLANK_TILE;
	int TILE_TRAVERSABLE = Data::Instance()->TILE_TRAVERSABLE;

	if (height > TileSize)
		i = TileSize;
	else
		i = height;

	for (;;)
	{

		x1 = (x + dirX) / TileSize;
		x2 = (x + dirX + width) / TileSize;

		y1 = y / TileSize;
		y2 = (y + i - 1) / TileSize;

		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
		{
			//Si on a un mouvement à droite
			if (dirX > 0)
			{
				//On vérifie si les tiles recouvertes sont solides
				if (map->GetTile(y1, x2)!= nullptr &&  map->GetTile(y1, x2)->GetType() > BLANK_TILE || map->GetTile(y2, x2) != nullptr && map->GetTile(y2, x2)->GetType() > BLANK_TILE)
				{
					// Si c'est le cas, on place le joueur aussi près que possible
					// de ces tiles, en mettant à jour ses coordonnées. Enfin, on
					//réinitialise son vecteur déplacement (dirX).

					x = x2 * TileSize;
					x -= width + 1;
					dirX = 0;
				}
			}

			//Même chose à gauche
			else if (dirX < 0)
			{
				if (map->GetTile(y1, x1) != nullptr && map->GetTile(y1, x1)->GetType() > BLANK_TILE || map->GetTile(y2, x1) != nullptr && map->GetTile(y2, x1)->GetType() > BLANK_TILE)
				{
					x = (x1 + 1) * TileSize;
					dirX = 0;
				}
			}

			if (i == height)
			{
				break;
			}

			i += TileSize;

			if (i > height)
			{
				i = height;
			}
		}
	}

	if (width > TileSize)
		i = TileSize;
	else
		i = width;


	for (;;)
	{
		x1 = (x) / TileSize;
		x2 = (x + i) / TileSize;

		y1 = (y + dirY) / TileSize;
		y2 = (y + dirY + height) / TileSize;

		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
		{
			if (dirY > 0 && state != Data::Instance()->LADDER)
			{
				// Déplacement en bas
				//Gestion des plateformes traversables : elles se situent juste avant
				//les tiles bloquantes dans notre tileset (dont la valeur butoire est
				//BLANK_TILE). Il suffit donc d'utiliser le numéro de la première tile
				//traversable au lieu de BLANK_TILE pour bloquer le joueur,
				//seulement quand il tombe dessus (sinon, il passe au-travers
				//et le test n'est donc pas effectué dans les autres directions
				if ((map->GetTile(y2, x1) != nullptr && map->GetTile(y2, x1)->GetType() > TILE_TRAVERSABLE) || (map->GetTile(y2, x2) != nullptr && map->GetTile(y2, x2)->GetType() > TILE_TRAVERSABLE))
				{
					//Si la tile est une plateforme ou une tile solide, on y colle le joueur et
					//on le déclare sur le sol (onGround).
					y = y2 * TileSize;
					y -= height;
					dirY = 0;
					isGrounding = true;
					hasJump = false;
					canJump = true;
				}
				else if(map->GetTile(y2, x1) != nullptr || map->GetTile(y2, x2) != nullptr)
				{
					//lol
					cout << endl;
				}
			}

			else if (dirY < 0 && state != Data::Instance()->LADDER)
			{
				// Déplacement vers le haut
				if (map->GetTile(y2, x1) != nullptr && map->GetTile(y2, x1)->GetType() > BLANK_TILE || map->GetTile(y2, x1) != nullptr && map->GetTile(y2, x1)->GetType() > BLANK_TILE)
				{
					y = (y1 + 1) * TileSize;
					dirY = 0;
				}
			}
		}

		//On teste la largeur du sprite (même technique que pour la hauteur précédemment)
		if (i == width)
		{
			break;
		}

		i += TileSize;

		if (i > width)
		{
			i = width;
		}
	}

	x += dirX;
	y += dirY;

	if (x < 0)
	{
		x = 0;
	}
	else if (x + width >= MAX_MAP_X)
	{
		x = MAX_MAP_X - width;
	}
}

void Player::SetStartPos(int startX, int startY)
{
	x = startX * TileSize;
	y = startY * TileSize;
}
