#include "Debug.h"

Debug* Debug::m_instance = nullptr;

Debug::Debug()
{
	fontSize = 15;
	fontColor = Color::Red;
	text.setCharacterSize(fontSize);

	if (!font.loadFromFile("font/arial.ttf"))
	{
		// Error
		cout << "Error while loading the font of the player." << endl;
	}
	else
		text.setFont(font);
}


Debug::~Debug()
{

}

void Debug::PrintDebug(sf::RenderWindow & window)
{
	xLeft = 50;
	yLeft = 0;

	for (unsigned i = 0; i < debugsLeft.size(); i++)
	{
		text.setPosition(Vector2f(xLeft, yLeft));
		text.setCharacterSize(debugsLeft.at(i).size);
		text.setColor(debugsLeft.at(i).color);
		text.setString(debugsLeft.at(i).text);

		window.draw(text);

		yLeft += debugsLeft.at(i).size;
	}

	xRight = 500;
	yRight = 0;

	for (unsigned i = 0; i < debugsRight.size(); i++)
	{
		text.setPosition(Vector2f(xRight, yRight));
		text.setCharacterSize(debugsRight.at(i).size);
		text.setColor(debugsRight.at(i).color);
		text.setString(debugsRight.at(i).text);

		window.draw(text);

		yRight += debugsRight.at(i).size;
	}

	debugsRight.clear();
	debugsLeft.clear();
}

void Debug::AddDebug(string t, bool left, unsigned int s = 15, Color c = Color::Red)
{
	if(left)
		debugsLeft.push_back(DebugText(s, t, c));
	else
		debugsRight.push_back(DebugText(s, t, c));
}

Debug* Debug::Instance()
{
	if (m_instance == nullptr)
		m_instance = new Debug();
	return m_instance;
}