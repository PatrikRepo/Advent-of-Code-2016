#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <unordered_map>

void parseInput(std::vector<std::pair<char,int>> &directions)
{
	std::string line;

	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input, line);
		{
			size_t pos = 0;
			size_t endpos = 0;
			char d = 0;
			int steps = 0;

			while(pos != std::string::npos)
			{
				endpos = line.find_first_of(",", pos);
				d = line[pos];
				steps = std::stoi(line.substr(pos+1,endpos-pos-1));
				directions.push_back(std::make_pair(d,steps));
				pos = line.find_first_of("RL",endpos);
			}
		}
	}
	input.close();
}

uint64_t calculateDistance(const std::vector<std::pair<char,int>> &directions)
{
	uint64_t result = 0;
	int x = 0;
	int y = 0;
	int direction = 0;

	for(auto it=directions.begin(); it!=directions.end(); it++)
	{ 	
		if(it->first == 'R')
		{
			direction = (direction+1)%4;
		}
		else
		{
			direction = (direction+3)%4;
		}
		switch(direction)
		{
			case 0:
				y -= it->second;
				break;
			case 1:
				x += it->second;
				break;
			case 2:
				y += it->second;
				break;
			case 3:
				x -= it->second;
		}
	}
	if(x<0)
	{
		x = -x;
	}
	if(y<0)
	{
		y = -y;
	}
	
	result = x + y;

	return result;
}

uint64_t findFirstVisitedTwice(const std::vector<std::pair<char,int>> &directions)
{
	uint64_t result = 0;
	int x = 0;
	int y = 0;
	int direction = 0;
	std::unordered_map<int64_t,int> cache;
	for(auto it=directions.begin(); it!=directions.end(); it++)
	{ 
		if(it->first == 'R')
		{
			direction = (direction+1)%4;
		}
		else
		{
			direction = (direction+3)%4;
		}
		switch(direction)
		{
			case 0:
				for(int i=0; i<it->second; i++)
				{
					y--;
					int64_t cacheNumber = x*10000 + y;
					if(cache.count(cacheNumber) == 1)
					{
						it = directions.end() - 1;
						break;
					}
					else
					{
						cache[cacheNumber] += 1;
					}
				}
				break;
			case 1:
				for(int i=0; i<it->second; i++)
				{
					x++;
					int64_t cacheNumber = x*10000 + y;
					if(cache.count(cacheNumber) == 1)
					{
						it = directions.end() - 1;
						break;
					}
					else
					{
						cache[cacheNumber] += 1;
					}
				}
				break;

			case 2:
				for(int i=0; i<it->second; i++)
				{
					y++;
					int64_t cacheNumber = x*10000 + y;
					if(cache.count(cacheNumber) == 1)
					{
						it = directions.end() - 1;
						break;
					}
					else
					{
						cache[cacheNumber] += 1;
					}
				}
				break;

			case 3:
				for(int i=0; i<it->second; i++)
				{
					x--;
					int64_t cacheNumber = x*10000 + y;
					if(cache.count(cacheNumber) == 1)
					{
						it = directions.end() - 1;
						break;
					}
					else
					{
						cache[cacheNumber] += 1;
					}
				}
				break;
		}
	}
	
	if(x<0)
	{
		x = -x;
	}
	if(y<0)
	{
		y = -y;
	}
	
	result = x + y;

	return result;
}
int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<std::pair<char,int>> directions;

	parseInput(directions);

	resultA = calculateDistance(directions);	
	resultB = findFirstVisitedTwice(directions);	
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;	
}

