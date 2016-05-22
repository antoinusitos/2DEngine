#include "Player.h"
#include "Elevator.h"

using namespace std;
using namespace sf;

Player::Player(Map* map)
{
	//if (!texture.loadFromFile("graphics/testCharactertileset.png"))
	if (!texture.loadFromFile("graphics/TileSetCharacter.png"))
	{
		// Error
		cout << "Error while loading the texture of the player." << endl;
	}
	else
		sprite.setTexture(texture);

	if (!texturePause.loadFromFile("graphics/Pause.png"))
	{
		// Error
		cout << "Error while loading the texture of the player." << endl;
	}
	else
		spritePause.setTexture(texturePause);

	
	if (!bufferJump.loadFromFile("sound/jump.wav"))
	{
		// Error
		cout << "Error while loading the sound jump of the player." << endl;
	}
	else
	{
		soundJump.setBuffer(bufferJump);
	}

	if (!bufferPickup.loadFromFile("sound/pickup.wav"))
	{
		// Error
		cout << "Error while loading the sound pickup of the player." << endl;
	}
	else
	{
		soundPickup.setBuffer(bufferPickup);
	}

	if (!bufferDeath.loadFromFile("sound/death.wav"))
	{
		// Error
		cout << "Error while loading the sound death of the player." << endl;
	}
	else
	{
		soundDeath.setBuffer(bufferDeath);
	}

	if (!bufferDead.loadFromFile("sound/dead.wav"))
	{
		// Error
		cout << "Error while loading the sound dead of the player." << endl;
	}
	else
	{
		soundDead.setBuffer(bufferDead);
	}

	if (!bufferSeletion.loadFromFile("sound/selection.wav"))
	{
		// Error
		cout << "Error while loading the sound selection of the main." << endl;
	}
	else
	{
		soundSeletion.setBuffer(bufferSeletion);
	}

	if (!bufferEnter.loadFromFile("sound/enter.wav"))
	{
		// Error
		cout << "Error while loading the sound enter of the main." << endl;
	}
	else
	{
		soundEnter.setBuffer(bufferEnter);
	}


	if (!bufferFoot.loadFromFile("sound/footstep.wav"))
	{
		// Error
		cout << "Error while loading the sound footstep of the player." << endl;
	}
	else
	{
		soundFoot.setBuffer(bufferFoot);
	}

	fontSize = 30;
	fontColor = Color::Color(115, 157, 99);
	returnText.setCharacterSize(fontSize);
	quitText.setCharacterSize(fontSize);
	returnText.setStyle(sf::Text::Bold);
	quitText.setStyle(sf::Text::Bold);
	returnText.setString("CONTINUE");
	quitText.setString("QUIT");
	int midWidth = Data::Instance()->SCREEN_WIDTH / 3;
	int midHeight = Data::Instance()->SCREEN_HEIGHT / 3;
	returnText.setPosition(Vector2f(midWidth, midHeight));
	quitText.setPosition(Vector2f(midWidth, midHeight + 100));

	if (!font.loadFromFile("font/quartz.ttf"))
	{
		// Error
		cout << "Error while loading the font of the player." << endl;
	}
	else
	{
		returnText.setFont(font);
		quitText.setFont(font);

	}

	jumpState = Data::Instance()->jump;

	theMap = map;

	debug = false;

	Initialize();
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
	frameMax = 2;
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
	takenPower = nullptr;
	pickUpTime = 0.0f;
	currentTime = 0.0f;
	timeInAir = 0;
	timeInAirToDeath = 15;

	animSlower = 2;
	isInMenu = false;
	indexMenu = 0;
	wantsTheMenu = false;

	mapNumber = -1;
}

void Player::ResetEntity()
{
	ResetPos();
	Initialize();
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
		if(state == Data::Instance()->WALK)
			soundFoot.play();
		//On le réinitialise
		frameTimer = Data::Instance()->TIME_BETWEEN_2_FRAMES_PLAYER;

		//Et on incrémente notre variable qui compte les frames de 1 pour passer à la suivante
		if (state != Data::Instance()->JUMP1 && state != Data::Instance()->LADDER)
			frameNumber++;

		//Mais si on dépasse la frame max, il faut revenir à la première :
		if ((frameNumber / animSlower) >= frameMax)
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
			sprite.setTextureRect(sf::IntRect(((frameNumber/ animSlower) + 1) * width, height * 3, -width, height));
		}
		else
		{
			sprite.setTextureRect(sf::IntRect((frameNumber / animSlower) * width, height * 3 , width, height));
		}
	}
	else if (state == Data::Instance()->IDLE)
	{
		if (direction == Data::Instance()->LEFT)
		{
			sprite.setTextureRect(sf::IntRect(((frameNumber / animSlower) * width) + width, height * 2, -width, height));
		}
		else
		{
			sprite.setTextureRect(sf::IntRect((frameNumber / animSlower) * width, height * 2, width, height));
		}
	}
	else if (state == Data::Instance()->JUMP1)
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
	else if (state == Data::Instance()->LADDER)
	{
		sprite.setTextureRect(sf::IntRect((frameNumber + 1) * width, height, width, height));
	}
	else if (state == Data::Instance()->DEAD)
	{
		sprite.setTextureRect(sf::IntRect(0, height * 4, width, height));
	}
	window.draw(sprite);
	
	if (debug)
	{
		string s;

		Debug::Instance()->AddDebug("X:" + to_string(x) + "(" + to_string(x/32) + ")", false, 15, Color::Red);
		Debug::Instance()->AddDebug("Y:" + to_string(y) + "(" + to_string(y / 32) + ")", false, 15, Color::Red);

		Debug::Instance()->AddDebug("isGrounding: " + to_string(isGrounding), true, 15, Color::Red);
		Debug::Instance()->AddDebug("canJump: " + to_string(canJump), true, 15, Color::Red);
		Debug::Instance()->AddDebug("hasJump: " + to_string(hasJump), true, 15, Color::Red);
		Debug::Instance()->AddDebug("dirY: " + to_string(dirY), true, 15, Color::Red);
		Debug::Instance()->AddDebug("state: " + to_string(state), true, 15, Color::Red);
		Debug::Instance()->AddDebug("PickUpTime: " + to_string(pickUpTime / 1000.0f), true, 15, Color::Red);
		Debug::Instance()->AddDebug("Power Attached: " + to_string(takenPower != nullptr ? true : false), true, 15, Color::Red);
	}

	if (isInMenu)
	{
		int midWidth = Data::Instance()->SCREEN_WIDTH / 3;
		int midHeight = Data::Instance()->SCREEN_HEIGHT / 3;

		int size = 300;
		//sf::RectangleShape rectangle(sf::Vector2f(size, size));
		spritePause.setPosition(midWidth - (size / 4), midHeight - (size / 2));
		//rectangle.setFillColor(sf::Color(50, 50, 50));

		if (indexMenu == 0)
		{
			quitText.setColor(selectedFontColor);
			returnText.setColor(fontColor);
		}
		else if (indexMenu == 1)
		{
			quitText.setColor(fontColor);
			returnText.setColor(selectedFontColor);
		}

		window.draw(spritePause);
		window.draw(quitText);
		window.draw(returnText);
	}
}

void Player::Update(Input * input, sf::Time time)
{
	pickUpTime += time.asMilliseconds();

	if (debug)
	{
		Debug::Instance()->AddDebug("Touche E:" + to_string(input->getButton().action), false, 15, Color::Red);
	}

	if (state != Data::Instance()->DEAD && !isInMenu)
	{
		if (input->getButton().start)
		{
			isInMenu = true;
			return;
		}

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
					frameMax = 2;
					animSlower = 1;
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
					frameMax = 2;
					animSlower = 1;
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
				frameMax = 2;
				animSlower = 2;
			}

		}

		if (input->getButton().action == true && pickUpTime/1000.0f >= 0.5f)
		{
			pickUpTime = 0.0f;
			input->setButton(Input::action, false);
			TakePower();
			ActivateLevel();
		}

		if (state == Data::Instance()->LADDER)
		{
			timeInAir = 0;
			dirY = 0;
		}

		//jump
		if (input->getButton().jump == true && state != Data::Instance()->JUMP1)
		{
			if (isGrounding == true && canJump)
			{
				frameMax = 0;
				prevY = y;
				soundJump.play();
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
				{
					state = Data::Instance()->LADDER;
					//frameNumber = 0;
					frameMax = 2;
				}
				dirY = -Data::Instance()->CLIMB_HEIGHT;
			}
		}
		else if (input->getButton().down == true)
		{
			if (CheckCollisionBottom(theMap))
			{
				if (state != Data::Instance()->LADDER)
				{
					state = Data::Instance()->LADDER;
					//frameNumber = 0;
					frameMax = 2;
				}
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
			if (prevY <= y)
			{
				timeInAir++;
				prevY = y;
			}
		}

		else if(timeInAir >= timeInAirToDeath && state != Data::Instance()->LADDER)
		{
   			cout << endl;
			soundDeath.play();
			state = Data::Instance()->DEAD;
			sprite.setTextureRect(sf::IntRect(3 * width, 0, width, height));
		}
		else
		{
			timeInAir = 0;
		}

		//On gère le scrolling (fonction ci-dessous)
		//centerScrolling(map);
	}
	else if(isInMenu)
	{
		if (input->getButton().action == true)
		{
			soundEnter.play();
			if (indexMenu == 0)
			{
				isInMenu = false;
			}
			else if(indexMenu == 1)
			{
				wantsTheMenu = true;
			}
		}
		else if (input->getButton().up == true && indexMenu > 0)
		{
			soundSeletion.play();
			indexMenu--;
			indexMenu = max(indexMenu, 0);
			input->setButton(Input::up, false);
		}
		else if (input->getButton().down == true && indexMenu < 1)
		{
			soundSeletion.play();
			indexMenu++;
			indexMenu = min(indexMenu, 1);
			input->setButton(Input::down, false);
		}
	}
	else
	{
		sleep(Time(milliseconds(500)));
		soundDead.play();
		sleep(Time(milliseconds(1000)));
		theMap->SetGameOver(true, false);
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
			x = map->GetTile(yTemp, xTemp + 1)->GetX();
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
			x = map->GetTile(yTemp, xTemp + 1)->GetX();
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
				bool hitEntity = false;

				if (map->GetElevator() != nullptr)
				{
					if (x2 * 32 > map->GetElevator()->GetX() && x2 * 32 < (map->GetElevator()->GetX() + map->GetElevator()->GetWidth()) && y2 * 32 > map->GetElevator()->GetY() && y2 * 32 < map->GetElevator()->GetY() + map->GetElevator()->GetHeight())
					{
						hitEntity = true;
						map->GetElevator()->SetPlayer(this);
					}
					else if ((x2 * 32 < map->GetElevator()->GetX() || x2 * 32 > map->GetElevator()->GetX() + map->GetElevator()->GetWidth()) && map->GetElevator()->GetPlayer() != nullptr)
					{
						map->GetElevator()->SetPlayer(nullptr);
					}
				}

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
				else if (hitEntity == true)
				{
					x = x2 * TileSize;
					x -= width + 1;
					dirX = 0;
				}
				else
				{
					//pose le power dans le generateur
					if (map->GetTile(y1, x2) != nullptr && map->GetTile(y1, x2)->GetTileType() == 89 && takenPower != nullptr)
					{
						Tile* theTile = map->GetTile(y1, x2);
						int theX = theTile->GetX() - theTile->GetWidth() / 2;
						int theY = theTile->GetY() - theTile->GetHeight();
						takenPower->SetPosition(theX, theY);
						
						if (map->GetRunningPower() != nullptr)
						{
							map->GetRunningPower()->Reset();
						}

						map->SetRunningPower(takenPower);
						takenPower = nullptr;

					}
				}
			}

			//Même chose à gauche
			else if (dirX < 0)
			{
				bool hitEntity = false;
				if (map->GetElevator() != nullptr)
				{

					if (x2 * 32 > map->GetElevator()->GetX() && x2 * 32 < (map->GetElevator()->GetX() + map->GetElevator()->GetWidth()) && y2 * 32 > map->GetElevator()->GetY() && y2 * 32 < map->GetElevator()->GetY() + map->GetElevator()->GetHeight())
					{
						hitEntity = true;
						map->GetElevator()->SetPlayer(this);
					}
					else if ((x2 * 32 < map->GetElevator()->GetX() || x2 * 32 > map->GetElevator()->GetX() + map->GetElevator()->GetWidth()) && map->GetElevator()->GetPlayer() != nullptr)
					{
						map->GetElevator()->SetPlayer(nullptr);
					}
				}

				if (map->GetTile(y1, x1) != nullptr && map->GetTile(y1, x1)->GetType() > BLANK_TILE || map->GetTile(y2, x1) != nullptr && map->GetTile(y2, x1)->GetType() > BLANK_TILE)
				{
					x = (x1 + 1) * TileSize;
					dirX = 0;
				}
				/*else if (x2 * 32 > map->GetElevator()->GetX() && x2 * 32 < (map->GetElevator()->GetX() + map->GetElevator()->GetWidth()) && y2 * 32 > map->GetElevator()->GetY() && y2 * 32 < map->GetElevator()->GetY() + map->GetElevator()->GetHeight())
				{
					x = (x1 + 1) * TileSize;
					dirX = 0;
				}*/
				else
				{
					//pose le power dans le generateur
					if (map->GetTile(y1, x2) != nullptr && map->GetTile(y1, x2)->GetTileType() == 89 && takenPower != nullptr)
					{
						Tile* theTile = map->GetTile(y1, x2);
						int theX = theTile->GetX() - theTile->GetWidth() / 2;
						int theY = theTile->GetY() - theTile->GetHeight();
						takenPower->SetPosition(theX, theY);

						if (map->GetRunningPower() != nullptr)
						{
							map->GetRunningPower()->Reset();
						}

						map->SetRunningPower(takenPower);
						takenPower = nullptr;

					}
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
		/*x1 = (x) / TileSize;
		x2 = (x + i) / TileSize;
		int x3 = (x / TileSize) + ((width / 2) / TileSize);


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
				//if ((map->GetTile(y2, x1) != nullptr && map->GetTile(y2, x1)->GetType() > TILE_TRAVERSABLE) || (map->GetTile(y2, x2) != nullptr && map->GetTile(y2, x2)->GetType() > TILE_TRAVERSABLE))
				if ((map->GetTile(y2, x3) != nullptr && map->GetTile(y2, x3)->GetType() > TILE_TRAVERSABLE)/* || (map->GetTile(y2, x2) != nullptr && map->GetTile(y2, x2)->GetType() > TILE_TRAVERSABLE))
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
				//else if(map->GetTile(y2, x1) != nullptr || map->GetTile(y2, x2) != nullptr)
				//{
				//	cout << endl;
				//}
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
		}*/

		int xTemp = (x + (width / 2)) / TileSize;
		int xMod = (x + (width/2)) % TileSize;

		//on est sur la partie gauche de la tile
		if (xMod < TileSize * 0.01)
		{
			xTemp--;
			xTemp = max(xTemp, 0);
		}
		//on est sur la partie droite de la tile
		//else if (xMod > TileSize * 0.99)
		else if (xMod > TileSize * 0.99)
		{
			xTemp++;
			xTemp = min(xTemp, Data::Instance()->TILE_X);
		}

		y1 = (y + dirY + height) / TileSize;

		// Déplacement en bas
		if (dirY > 0 && state != Data::Instance()->LADDER)
		{
			if ((map->GetTile(y1, xTemp) != nullptr && map->GetTile(y1, xTemp)->GetType() > TILE_TRAVERSABLE))
			{
				//Si la tile est une plateforme ou une tile solide, on y colle le joueur et
				//on le déclare sur le sol (onGround).
				y = y1 * TileSize;
				y -= height;
				dirY = 0;
				isGrounding = true;
				hasJump = false;
				canJump = true;
			}
			else if (map->GetElevator() != nullptr && (x2 * 32 < map->GetElevator()->GetX() || x2 * 32 > map->GetElevator()->GetX() + map->GetElevator()->GetWidth()) && map->GetElevator()->GetPlayer() != nullptr)
			{
				map->GetElevator()->SetPlayer(nullptr);
			}
			/*else if (x2 * 32 > map->GetElevator()->GetX() && x2 * 32 < (map->GetElevator()->GetX() + map->GetElevator()->GetWidth()) && y2 * 32 < map->GetElevator()->GetY() + map->GetElevator()->GetHeight())
			{
				x = (x1 + 1) * TileSize;
				dirX = 0;
				y = map->GetElevator()->GetY() - map->GetElevator()->GetHeight() - 5;
			}*/
		}
		// Déplacement vers le haut
		else if (dirY < 0 && state != Data::Instance()->LADDER)
		{
			if (map->GetTile(y1, xTemp) != nullptr && map->GetTile(y1, xTemp)->GetType() > BLANK_TILE)
			{
				y = (y1 + 1) * TileSize;
				dirY = 0;
			}
			else if (map->GetElevator() != nullptr && (x2 * 32 < map->GetElevator()->GetX() || x2 * 32 > map->GetElevator()->GetX() + map->GetElevator()->GetWidth()) && map->GetElevator()->GetPlayer() != nullptr)
			{
				map->GetElevator()->SetPlayer(nullptr);
			}
			/*else if (x2 * 32 > map->GetElevator()->GetX() && x2 * 32 < (map->GetElevator()->GetX() + map->GetElevator()->GetWidth()) && y2 * 32 < map->GetElevator()->GetY() + map->GetElevator()->GetHeight())
			{
				y = map->GetElevator()->GetY() - map->GetElevator()->GetHeight() - 5;
			}*/
		}
		else if (map->GetElevator() != nullptr && (x2 * 32 < map->GetElevator()->GetX() || x2 * 32 > map->GetElevator()->GetX() + map->GetElevator()->GetWidth()) && map->GetElevator()->GetPlayer() != nullptr)
		{
			map->GetElevator()->SetPlayer(nullptr);
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

	if (takenPower != nullptr)
	{
		if (!takenPower->GetIsAttached())
		{
			takenPower->SetPosition(x, y);
		}
		else
		{
			takenPower = nullptr;
		}
	}
}

void Player::SetStartPos(int startX, int startY)
{
	x = startX * TileSize;
	y = startY * TileSize;
}

void Player::TakePower()
{
	if (takenPower != nullptr)
	{
		takenPower->PlayPut();
		takenPower->Release();
		takenPower = nullptr;
	}

	else
	{
		Power* retour = nullptr;
		/* check de la collision et ramassage*/

		int xPos = x / 32;
		int yPos = (int)floor(y / 32);

		retour = theMap->GetPower(xPos, yPos);

		if (retour != nullptr)
		{
			takenPower = retour;
			takenPower->Take();
			soundPickup.play();
		}
	}
}

bool Player::GetWantsTheMenu()
{
	return wantsTheMenu;
}

void Player::ActivateLevel()
{
	int retour = -1;

	int xPos = x / 32;
	int yPos = (int)floor(y / 32);

	retour = theMap->GetDoor(xPos, yPos);

	if (retour != -1)
	{
		mapNumber = retour;
	}
}

int Player::MustLoadLevel()
{
	return mapNumber;
}
