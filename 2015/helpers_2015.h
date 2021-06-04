#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

struct SantaPosition
{
	int x=0;
	int y=0;

    SantaPosition(int iX, int iY)
    {
        x=iX;
        y=iY;
    }

	bool operator==(const SantaPosition& other) const
	{
		return this->x==other.x && this->y==other.y;
	}
    
    void Move(char c);
};

void log_err();

void MoveSanta(SantaPosition&);

bool IsOldNiceString(std::string line); // first part
bool IsNewNiceString(std::string line); // second part
