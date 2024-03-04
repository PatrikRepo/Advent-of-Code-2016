#include <iostream>
#include <fstream>
#include <vector>

struct Node
{
	unsigned int x = 0;
	unsigned int y = 0;
	unsigned int used = 0;
	unsigned int avail = 0;
};

void parseInput(std::vector<Node> &nodes)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input,line);
		getline(input,line);
		while(getline(input, line))
		{
			size_t pos = 0;
			size_t endpos = 0;
			Node node;
			
			pos = line.find_first_of("1234567890");
			endpos = line.find_first_of("-", pos);
			node.x = std::stoi(line.substr(pos, endpos-pos));
			
			pos = line.find_first_of("1234567890", endpos);
			endpos = line.find_first_of(" ", pos);
			node.y = std::stoi(line.substr(pos, endpos-pos));
			
			pos = line.find_first_of("T", endpos);
			pos = line.find_first_of("1234567890", pos);
			endpos = line.find_first_of("T", pos);
			node.used = std::stoi(line.substr(pos, endpos-pos));
			
			pos = line.find_first_of("1234567890", endpos);
			endpos = line.find_first_of("T", pos);
			node.avail = std::stoi(line.substr(pos, endpos-pos));
			
			nodes.push_back(node);
		}
	}
	input.close();
}

uint64_t findPairs(std::vector<Node> &node)
{
	uint64_t result = 0;
	
	for(unsigned int i=0; i<node.size(); i++)
	{
		for(unsigned int j=0; j<node.size(); j++)
		{
			if(i != j && node[i].used > 0 && node[i].used < node[j].avail)
			{
				result++;
			}
		}
	}
	
	return result;
}

void buildMap(std::vector<std::string> &map, std::vector<Node> &nodes)
{
	unsigned int maxX = 0;
	unsigned int maxY = 0;
	for(auto it=nodes.begin(); it!=nodes.end(); it++)
	{
		if(it->x > maxX)
		{
			maxX = it->x;
		}
		if(it->y > maxY)
		{
			maxY = it->y;
		}
	}
	std::string row;
	for(unsigned int i=0; i<=maxX; i++)
	{
		row += ".";
	}
	for(unsigned int i=0; i<=maxY; i++)
	{
		map.push_back(row);
	}
	
	for(auto it=nodes.begin(); it!=nodes.end(); it++)
	{
		if(it->used >= 100)
		{
			map[it->y][it->x] = '#';
		}
		else if(it->used == 0)
		{
			map[it->y][it->x] = '_';
		}
	}
}

uint64_t moveData(std::vector<std::string> &map)
{
	uint64_t result = 0;
	
	unsigned int emptyX = 0;
	unsigned int emptyY = 0;
	unsigned int fullX = 0;
	unsigned int fullY = 0;
	
	for(unsigned int i=0; i<map.size(); i++)
	{
		for(unsigned int j=0; j<map[0].length(); j++)
		{
			if(map[i][j] == '_')
			{
				emptyX = j;
				emptyY = i;
				i=map.size();
				break;
			}
		}
	}
	
	for(unsigned int i=0; i<map.size(); i++)
	{
		if(map[i][emptyX] == '#')
		{
			fullY = i;
		}
	}
	for(unsigned int i=0; i<map.size(); i++)
	{
		if(map[fullY][i] == '#')
		{
			fullX = i;
			break;
		}
	}
	
	result += emptyY + map[0].length() - emptyX - 2;
	result += (emptyX - (fullX-1))*2;
	result += 1;
	result += 5*(map[0].length()-2);
	
	return result;
}

int main()
{
	uint64_t resultA;
	uint64_t resultB;
	std::vector<Node> nodes;
	std::vector<std::string> map;
	
	parseInput(nodes);

	resultA = findPairs(nodes);
	
	buildMap(map, nodes);
	
	resultB = moveData(map);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
