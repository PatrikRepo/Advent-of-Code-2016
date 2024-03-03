#include <iostream>
#include <fstream>
#include <vector>

void parseInput(std::vector<std::string> &map)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input, line);
		std::string mapRow = '.' + line + '.';
		map.push_back(mapRow);
		for(unsigned int i=0; i<mapRow.length(); i++)
		{
			mapRow[i] = '.';
		}
		for(int i=0; i<39; i++)
		{
			map.push_back(mapRow);
		}
	}
	input.close();
}

void buildMap(std::vector<std::string> &map)
{
	for(unsigned int j=1; j<map.size(); j++)
	{
		for(unsigned int i=1; i<map[0].length()-1; i++)
		{
			if(map[j-1][i-1] != map[j-1][i+1])
			{
				map[j][i] = '^';
			}
		}
	}
}

uint64_t checkSafeTiles(const std::vector<std::string> &map)
{
	uint64_t result = 0;
	
	for(unsigned int j=0; j<map.size(); j++)
	{
		for(unsigned int i=1; i<map[0].length()-1; i++)
		{
			if(map[j][i] == '.')
			{
				result++;
			}
		}
	}
	
	return result;
}

void buildBigMap(std::vector<std::string> &map)
{
	std::string newRowBase;
	
	for(unsigned int i=0; i<map[0].length(); i++)
	{
		newRowBase += '.';
	}
	for(int i=0; i<400000-40;i++)
	{
		map.push_back(newRowBase);
	}
	for(unsigned int j=40; j<map.size(); j++)
	{
		for(unsigned int i=1; i<map[0].length()-1; i++)
		{
			if(map[j-1][i-1] != map[j-1][i+1])
			{
				map[j][i] = '^';
			}
		}
	}
}

int main()
{
	uint64_t resultA;
	uint64_t resultB;
	std::vector<std::string> map;

	parseInput(map);
	buildMap(map);
	
	resultA = checkSafeTiles(map);
	
	buildBigMap(map);
	resultB = checkSafeTiles(map);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
