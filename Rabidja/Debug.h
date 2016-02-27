#ifndef DEBUG_H
#define DEBUG_H

#include "Data.h"
#include "Input.h"
#include <vector>

using namespace std;
using namespace sf;

class Debug
{
public:
	static Debug* Instance();
	Debug();
	~Debug();

	void PrintDebug(sf::RenderWindow &window);

	struct DebugText
	{
		unsigned int size;
		string text;
		Color color;
		DebugText(unsigned int s, string t, Color c)
		{
			size = s;
			text = t;
			color = c;
		}
	};

	void AddDebug(string t, bool left, unsigned int s, Color c);

	vector <DebugText> debugsRight;
	vector <DebugText> debugsLeft;

private :
	Text text;
	Font font;

	unsigned int fontSize;

	Color fontColor;

	int xLeft;
	int yLeft;
	int xRight;
	int yRight;

	static Debug* m_instance;
};

#endif