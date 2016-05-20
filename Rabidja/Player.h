#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Power.h"
#include "Tile.h"

class Player : public Entity
{
public:
	Player(Map* map);
	~Player();

	void Initialize();

	// setter

	void SetLife(int theLife);
	void SetSpeed(float theSpeed);

	// getter

	int GetLife();
	float GetSpeed();

	void Draw(sf::RenderWindow &window) override;
	void Update(Input* input, sf::Time time) override;
	bool CheckCollision(Map* map);
	bool CheckCollisionBottom(Map* map);
	void mapCollision(Map* map);
	void SetStartPos(int X, int Y);
	void TakePower();

	bool GetWantsTheMenu();
	void ResetEntity() override;

private:
	float dirX;
	float dirY;

	int directionX;
	int directionY;
	bool isGrounding;

	int direction;
	int state;

	int frameNumber;
	int frameTimer;
	int frameMax;

	float speed;

	int life;

	bool hasJump;
	bool canJump;

	int jumpState;

	int TileSize;
	
	Map* theMap;

	Power* takenPower;
	float pickUpTime;
	float currentTime;

	bool isInMenu;
	int indexMenu;
	bool drawMenu;
	Text returnText;
	Text quitText;
	Font font;
	unsigned int selectedfontSize;
	unsigned int fontSize;
	Color selectedFontColor;
	Color fontColor;

	bool wantsTheMenu;

	sf::SoundBuffer bufferJump;
	sf::Sound soundJump;

	sf::SoundBuffer bufferPickup;
	sf::Sound soundPickup;

	sf::SoundBuffer bufferFoot;
	sf::Sound soundFoot;

	sf::SoundBuffer bufferDeath;
	sf::Sound soundDeath;

	sf::SoundBuffer bufferDead;
	sf::Sound soundDead;

	float timeInAir;
	float timeInAirToDeath;
	float prevY;

	sf::SoundBuffer bufferSeletion;
	sf::Sound soundSeletion;

	sf::SoundBuffer bufferEnter;
	sf::Sound soundEnter;

	int animSlower;
};

#endif