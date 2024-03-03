#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

void parseInput(unsigned int &magicNumber)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input,line);
		magicNumber = std::stoi(line);
	}
	input.close();
}

void createMap(std::vector<std::string> &map, const unsigned int magicNumber)
{
	for(unsigned int j=0; j<map.size(); j++)
	{
		for(unsigned int i=0; i<map[j].length(); i++)
		{
			std::bitset<16> binaryRep((i*i) + (3*i) + (2*i*j) + j + (j*j) + magicNumber);
			std::string binaryString = binaryRep.to_string();
			unsigned int numberOf1s = 0;
			for(unsigned int k=0; k<binaryString.length(); k++)
			{
				if(binaryString[k] == '1')
				{
					numberOf1s++;
				}
			}
			if(numberOf1s % 2 == 0)
			{
				map[j][i] = '.';
			}
		}
	}
}

void walk(std::vector<std::string> map, const size_t posX, const size_t posY, const unsigned int steps, const size_t goalX, const size_t goalY, uint64_t &minStep)
{
	if(posX == goalX && posY == goalY)
	{
		if(steps<minStep)
		{
			minStep = steps;
		}
	}
	else
	{
		map[posY][posX] = '#';
		if(posY > 0 && map[posY-1][posX] == '.' && steps+1 < minStep)
		{	
			walk(map, posX, posY-1, steps+1, goalX, goalY, minStep);
		}
		if(posY+1 < map.size() && map[posY+1][posX] == '.' && steps+1 < minStep)
		{	
			walk(map, posX, posY+1, steps+1, goalX, goalY, minStep);
		}
		if(posX > 0 && map[posY][posX-1] == '.' && steps+1 < minStep)
		{	
			walk(map, posX-1, posY, steps+1, goalX, goalY, minStep);
		}
		if(posX+1 < map[0].length() && map[posY][posX+1] == '.' && steps+1 < minStep)
		{	
			walk(map, posX+1, posY, steps+1, goalX, goalY, minStep);
		}
	}
}

uint64_t walkMap(std::vector<std::string> &map, const size_t goalX, const size_t goalY)
{
	uint64_t result = UINT64_MAX;
	size_t posX = 1;
	size_t posY = 1;
	
	walk(map, posX, posY, 0, goalX, goalY, result);
	
	return result;
}

void walkSteps(std::vector<std::string> &map, const size_t posX, const size_t posY, const unsigned int steps, const uint64_t maxSteps)
{
	map[posY][posX] = '0' + steps;
	if(posY > 0 && map[posY-1][posX] != '#' && steps < maxSteps && (map[posY-1][posX] == '.' || steps + 1 + (unsigned char) '0' < (unsigned char) map[posY-1][posX]))
	{	
		walkSteps(map, posX, posY-1, steps+1, maxSteps);
	}
	if(posY+1 < map.size() && map[posY+1][posX] != '#' && steps < maxSteps && (map[posY+1][posX] == '.' || steps + 1 + (unsigned char) '0' < (unsigned char) map[posY+1][posX]))
	{	
		walkSteps(map, posX, posY+1, steps+1, maxSteps);
	}
	if(posX > 0 && map[posY][posX-1] != '#' && steps < maxSteps && (map[posY][posX-1] == '.' || steps + 1 + (unsigned char) '0' < (unsigned char) map[posY][posX-1]))
	{	
		walkSteps(map, posX-1, posY, steps+1, maxSteps);
	}
	if(posX+1 < map[0].length() && map[posY][posX+1] != '#' && steps < maxSteps && (map[posY][posX+1] == '.' || steps + 1 + (unsigned char) '0' < (unsigned char) map[posY][posX+1]))
	{	
		walkSteps(map, posX+1, posY, steps+1, maxSteps);
	}
}

uint64_t reachInSteps(std::vector<std::string> &map, const unsigned int maxSteps)
{
	uint64_t result = 0;
	size_t posX = 1;
	size_t posY = 1;
	
	walkSteps(map, posX, posY, 0, maxSteps);
	
	for(unsigned int j=0; j<map.size(); j++)
	{
		for(unsigned int i=0; i<map[0].length(); i++)
		{
			if(map[j][i] != '#' && map[j][i] != '.')
			{
				result++;
			}
		}
	}
	
	return result;
}

int main()
{
	int64_t resultA = 0;
	int64_t resultB = 0;
	size_t goalX = 31;
	size_t goalY = 39;
	unsigned int magicNumber;
	std::vector<std::string> map;
	parseInput(magicNumber);
	
	std::string line;
	for(int i=0; i<50; i++)
	{
		line += '#';
	}
	for(int i=0; i<50; i++)
	{
		map.push_back(line);
	}
	
	createMap(map, magicNumber);
	
	resultA = walkMap(map, goalX, goalY);
	resultB = reachInSteps(map, 50);
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
